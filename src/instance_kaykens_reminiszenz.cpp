/*
 * Kaykens Reminiszenz - Instance Script
 * Instance ID: 804
 */

#include "kaykens_reminiszenz.h"

class instance_kaykens_reminiszenz : public InstanceMapScript
{
public:
    instance_kaykens_reminiszenz() : InstanceMapScript("instance_kaykens_reminiszenz", 804) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_kaykens_reminiszenz_InstanceMapScript(map);
    }

    struct instance_kaykens_reminiszenz_InstanceMapScript : public InstanceScript
    {
        instance_kaykens_reminiszenz_InstanceMapScript(InstanceMap* map) : InstanceScript(map) 
        {
            SetHeaders("KR");
            SetBossNumber(MAX_KR_DATA);
            _hexenmeisterDeathCount = 0;
            _totalHexenmeister = 0;
        }

        void Initialize() override
        {
            _polydeucesGUID.Clear();
            _hexenmeisterGUIDs.clear();
            _hexenmeisterDeathCount = 0;
            _totalHexenmeister = 0;
        }

        void OnCreatureCreate(Creature* creature) override
        {
            switch (creature->GetEntry())
            {
                case NPC_POLYDEUCES:
                    _polydeucesGUID = creature->GetGUID();
                    break;
                case NPC_HEXENMEISTER:
                    _hexenmeisterGUIDs.insert(creature->GetGUID());
                    _totalHexenmeister++;
                    break;
            }
        }

        void OnCreatureRemove(Creature* creature) override
        {
            switch (creature->GetEntry())
            {
                case NPC_POLYDEUCES:
                    _polydeucesGUID.Clear();
                    break;
                case NPC_HEXENMEISTER:
                    _hexenmeisterGUIDs.erase(creature->GetGUID());
                    break;
            }
        }

        // Sindragosa-Style Death Tracking System
        void OnUnitDeath(Unit* unit) override
        {
            if (Creature* creature = unit->ToCreature())
            {
                switch (creature->GetEntry())
                {
                    case NPC_HEXENMEISTER:
                    {
                        _hexenmeisterGUIDs.erase(creature->GetGUID());
                        _hexenmeisterDeathCount++;
                        
                        // Notify Polydeuces - Sindragosa Style (single call)
                        if (Creature* polydeuces = instance->GetCreature(_polydeucesGUID))
                            polydeuces->AI()->DoAction(ACTION_HEXENMEISTER_DIED);
                        break;
                    }
                    case NPC_POLYDEUCES:
                        SetBossState(DATA_POLYDEUCES, DONE);
                        break;
                }
            }
        }

        ObjectGuid GetGuidData(uint32 type) const override
        {
            switch (type)
            {
                case DATA_POLYDEUCES:
                    return _polydeucesGUID;
                default:
                    break;
            }
            return ObjectGuid::Empty;
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
                case DATA_HEXENMEISTER_KILLED:
                    return _hexenmeisterDeathCount;
                default:
                    return 0;
            }
        }

        bool SetBossState(uint32 type, EncounterState state) override
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
                case DATA_POLYDEUCES:
                    break;
                default:
                    break;
            }
            return true;
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "K R " << GetBossState(DATA_POLYDEUCES);

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(char const* str) override
        {
            if (!str)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(str);

            char dataHead1, dataHead2;

            std::istringstream loadStream(str);
            loadStream >> dataHead1 >> dataHead2;

            if (dataHead1 == 'K' && dataHead2 == 'R')
            {
                uint32 temp = 0;
                loadStream >> temp; // DATA_POLYDEUCES state
                SetBossState(DATA_POLYDEUCES, (EncounterState)temp);
            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

    private:
        ObjectGuid _polydeucesGUID;
        std::set<ObjectGuid> _hexenmeisterGUIDs;
        uint32 _hexenmeisterDeathCount;
        uint32 _totalHexenmeister;
    };
};

void AddSC_instance_kaykens_reminiszenz()
{
    new instance_kaykens_reminiszenz();
}