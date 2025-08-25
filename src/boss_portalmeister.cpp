/*
 * Portalmeister Boss - Kaykens Reminiszenz
 * Converted from Lua to C++ - Boss with add spawning and movement phases
 */

#include "kaykens_reminiszenz.h"

struct PortalmeisterPosition
{
    float x, y, z, o;
};

class boss_portalmeister : public CreatureScript
{
public:
    boss_portalmeister() : CreatureScript("boss_portalmeister") { }

    struct boss_portalmeisterAI : public ScriptedAI
    {
        boss_portalmeisterAI(Creature* creature) : ScriptedAI(creature)
        {
            _instance = me->GetInstanceScript();
            Initialize();
        }

        void Initialize()
        {
            _currentPhase = 0;
            _isRooted = false;
            
            // Phase positions from original Lua
            _phasePositions = {
                { -7045.540527f, -1086.796631f, 241.666656f, 5.062332f }, // Phase 1 - Hellfire position
                { -7044.364746f, -1038.363525f, 240.930710f, 0.0f },      // Phase 2
                { -7092.933105f, -1077.697632f, 244.814148f, 0.0f },      // Phase 3
                { -7170.511230f, -1102.531372f, 241.247086f, 0.0f }       // Phase 4
            };
            
            _hellfirePositions = {
                { -7038.318848f, -1077.861206f, 241.667191f, 5.062332f },
                { -7034.277832f, -1089.978149f, 241.667191f, 5.062332f },
                { -7036.610352f, -1104.988525f, 242.046234f, 1.304492f }
            };
        }

        void Reset() override
        {
            events.Reset();
            Initialize();
            _isRooted = false;
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            _isRooted = true;
            me->SetReactState(REACT_PASSIVE);
            
            events.ScheduleEvent(EVENT_PORTAL_SHADOWBOLT, 1000);
            events.ScheduleEvent(EVENT_PORTAL_MOVE_PHASE, 1000); // Check for phase transitions
        }

        void JustSummoned(Creature* summon) override
        {
            switch (summon->GetEntry())
            {
                case NPC_PORTAL_ADD1:
                case NPC_PORTAL_ADD2:
                case NPC_PORTAL_ADD3:
                    // Adds will handle their own AI
                    break;
                case NPC_HORDE_PORTAL:
                    // Portal spawns adds continuously
                    break;
            }
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/, DamageEffectType /*damagetype*/, SpellSchoolMask /*damageSchoolMask*/) override
        {
            // Phase transitions based on HP
            if (me->HealthBelowPct(90) && _currentPhase == 0)
            {
                StartPhase(1);
            }
            else if (me->HealthBelowPct(80) && _currentPhase == 1)
            {
                StartPhase(2);
            }
            else if (me->HealthBelowPct(70) && _currentPhase == 2)
            {
                StartPhase(3);
            }
            else if (me->HealthBelowPct(60) && _currentPhase == 3)
            {
                StartPhase(4);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_PORTAL_SPAWN_ADDS:
                        SpawnRandomAdd();
                        events.Repeat(Milliseconds(500)); // Continuous spawning
                        break;
                    case EVENT_PORTAL_SHADOWBOLT:
                        CastShadowBolt();
                        events.Repeat(Milliseconds(urand(3000, 5000)));
                        break;
                    case EVENT_PORTAL_FEAR_CAST:
                        CastFearOnMultipleTargets();
                        events.Repeat(Milliseconds(15000));
                        break;
                    case EVENT_PORTAL_HELLFIRE:
                        SpawnHellfireArea();
                        break;
                    case EVENT_PORTAL_MOVE_PHASE:
                        // Continuous phase checking
                        events.Repeat(Milliseconds(1000));
                        break;
                }
            }

            if (!_isRooted)
                DoMeleeAttackIfReady();
        }

    private:
        EventMap events;
        InstanceScript* _instance;
        uint8 _currentPhase;
        bool _isRooted;
        std::vector<PortalmeisterPosition> _phasePositions;
        std::vector<PortalmeisterPosition> _hellfirePositions;

        void StartPhase(uint8 phase)
        {
            _currentPhase = phase;
            events.CancelEvent(EVENT_PORTAL_SPAWN_ADDS);
            
            if (phase == 1)
            {
                // Phase 1: Move to hellfire position and spawn hellfire
                _isRooted = false;
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->MovePoint(1, _phasePositions[0].x, _phasePositions[0].y, _phasePositions[0].z);
                events.ScheduleEvent(EVENT_PORTAL_HELLFIRE, 10000);
            }
            else
            {
                // Other phases: Move to position and start combat
                _isRooted = false;
                me->SetReactState(REACT_AGGRESSIVE);
                me->GetMotionMaster()->MovePoint(phase, _phasePositions[phase-1].x, _phasePositions[phase-1].y, _phasePositions[phase-1].z);
                
                events.ScheduleEvent(EVENT_PORTAL_SHADOWBOLT, phase >= 4 ? 10000 : 8000);
                events.ScheduleEvent(EVENT_PORTAL_FEAR_CAST, 15000);
            }
        }

        void SpawnRandomAdd()
        {
            uint32 addEntry;
            uint32 randomAdd = urand(1, 3);
            switch (randomAdd)
            {
                case 1: addEntry = NPC_PORTAL_ADD1; break;
                case 2: addEntry = NPC_PORTAL_ADD2; break;
                case 3: addEntry = NPC_PORTAL_ADD3; break;
                default: addEntry = NPC_PORTAL_ADD1; break;
            }
            
            me->SummonCreature(addEntry, -6972.828613f, -1099.007202f, 238.938965f, 5.050551f);
        }

        void CastShadowBolt()
        {
            if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, 250.0f, true))
                DoCast(target, SPELL_PORTAL_SHADOWBOLT);
        }

        void CastFearOnMultipleTargets()
        {
            // Cast fear on up to 3 random targets (from original Lua logic)
            std::list<Unit*> targets;
            SelectTargetList(targets, 3, SelectTargetMethod::Random, 0, 533.0f, true);
            
            for (Unit* target : targets)
            {
                DoCast(target, SPELL_PORTAL_FEAR);
            }
        }

        void SpawnHellfireArea()
        {
            // Set rooted for hellfire phase
            _isRooted = true;
            
            // Spawn hellfire spawner
            if (Creature* spawner = me->SummonCreature(NPC_HELLFIRE_SPAWNER, -7045.540527f, -1086.796631f, 271.666656f, 5.062332f))
            {
                // The spawner will handle the hellfire mechanics
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_portalmeisterAI(creature);
    }
};

// Portalmeister Add Spawner
class npc_portalmeister_spawner : public CreatureScript
{
public:
    npc_portalmeister_spawner() : CreatureScript("npc_portalmeister_spawner") { }

    struct npc_portalmeister_spawnerAI : public ScriptedAI
    {
        npc_portalmeister_spawnerAI(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            me->Yell(PortalmeisterTexts::SAY_SPAWN_ADDS, LANG_UNIVERSAL);
            me->HandleEmoteCommand(EMOTE_STATE_SPELL_CHANNEL_OMNI);
            
            events.ScheduleEvent(EVENT_PORTAL_SPAWN_ADDS, 500);
            
            // Spawn horde portal
            me->SummonCreature(NPC_HORDE_PORTAL, -6972.828613f, -1099.007202f, 238.938965f, 5.050551f);
        }

        void JustReachedHome() override
        {
            me->HandleEmoteCommand(EMOTE_STATE_SPELL_CHANNEL_OMNI);
            events.ScheduleEvent(EVENT_PORTAL_SPAWN_ADDS, 30000); // Restart after 30 seconds
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_PORTAL_SPAWN_ADDS:
                        SpawnRandomAdd();
                        events.Repeat(Milliseconds(500));
                        break;
                }
            }
        }

    private:
        EventMap events;

        void SpawnRandomAdd()
        {
            uint32 addEntry;
            uint32 randomAdd = urand(1, 3);
            switch (randomAdd)
            {
                case 1: addEntry = NPC_PORTAL_ADD1; break;
                case 2: addEntry = NPC_PORTAL_ADD2; break;
                case 3: addEntry = NPC_PORTAL_ADD3; break;
                default: addEntry = NPC_PORTAL_ADD1; break;
            }
            
            me->SummonCreature(addEntry, -6972.828613f, -1099.007202f, 238.938965f, 5.050551f);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_portalmeister_spawnerAI(creature);
    }
};

// Hellfire Spawner NPC
class npc_hellfire_spawner : public CreatureScript
{
public:
    npc_hellfire_spawner() : CreatureScript("npc_hellfire_spawner") { }

    struct npc_hellfire_spawnerAI : public ScriptedAI
    {
        npc_hellfire_spawnerAI(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            events.ScheduleEvent(EVENT_HELLFIRE_DESPAWN, 1000);
            events.ScheduleEvent(EVENT_HELLFIRE_SPAWN, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_HELLFIRE_SPAWN:
                        SpawnHellfireWaves();
                        events.Repeat(Milliseconds(11000)); // Every 11 seconds
                        break;
                    case EVENT_HELLFIRE_DESPAWN:
                        CheckPortalmeisterAlive();
                        events.Repeat(Milliseconds(1000));
                        break;
                    case EVENT_HELLBEAST_SPAWN:
                        SpawnHellbeasts();
                        break;
                }
            }
        }

    private:
        EventMap events;

        void SpawnHellfireWaves()
        {
            // Cast AoE hellfire at 3 positions
            me->CastSpell(-7038.318848f, -1077.861206f, 241.667191f, SPELL_HELLFIRE_AOE, true);
            me->CastSpell(-7034.277832f, -1089.978149f, 241.667191f, SPELL_HELLFIRE_AOE, true);
            me->CastSpell(-7036.610352f, -1104.988525f, 242.046234f, SPELL_HELLFIRE_AOE, true);
            
            // Spawn hellbeasts at those positions after 3 seconds
            events.ScheduleEvent(EVENT_HELLBEAST_SPAWN, 3000);
        }

        void SpawnHellbeasts()
        {
            // Spawn hellbeasts at the hellfire positions
            me->SummonCreature(NPC_HELLBEAST, -7038.318848f, -1077.861206f, 241.667191f, 5.062332f);
            me->SummonCreature(NPC_HELLBEAST, -7034.277832f, -1089.978149f, 241.667191f, 5.062332f);
            me->SummonCreature(NPC_HELLBEAST, -7036.610352f, -1104.988525f, 242.046234f, 1.304492f);
        }

        void CheckPortalmeisterAlive()
        {
            if (Creature* portalmeister = me->FindNearestCreature(NPC_PORTALMEISTER, 533.0f))
            {
                if (!portalmeister->IsAlive() || !portalmeister->IsInCombat())
                {
                    me->DespawnOrUnsummon(100);
                }
            }
            else
            {
                me->DespawnOrUnsummon(100);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hellfire_spawnerAI(creature);
    }
};

// Hellbeast NPCs
class npc_hellbeast : public CreatureScript
{
public:
    npc_hellbeast() : CreatureScript("npc_hellbeast") { }

    struct npc_hellbeastAI : public ScriptedAI
    {
        npc_hellbeastAI(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            events.ScheduleEvent(EVENT_HELLFIRE_DESPAWN, 1000);
            
            // Attack nearest target
            if (Unit* target = me->SelectNearestTarget(533.0f))
                me->AI()->AttackStart(target);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_HELLFIRE_DESPAWN:
                        CheckPortalmeisterAlive();
                        events.Repeat(Milliseconds(1000));
                        break;
                }
            }

            if (UpdateVictim())
                DoMeleeAttackIfReady();
        }

    private:
        EventMap events;

        void CheckPortalmeisterAlive()
        {
            if (Creature* portalmeister = me->FindNearestCreature(NPC_PORTALMEISTER, 533.0f))
            {
                if (!portalmeister->IsAlive() || !portalmeister->IsInCombat())
                {
                    me->DespawnOrUnsummon(100);
                }
            }
            else
            {
                me->DespawnOrUnsummon(100);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hellbeastAI(creature);
    }
};

// Horde Portal NPC
class npc_horde_portal : public CreatureScript
{
public:
    npc_horde_portal() : CreatureScript("npc_horde_portal") { }

    struct npc_horde_portalAI : public ScriptedAI
    {
        npc_horde_portalAI(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            events.ScheduleEvent(EVENT_HELLFIRE_DESPAWN, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_HELLFIRE_DESPAWN:
                        CheckPortalmeisterAlive();
                        events.Repeat(Milliseconds(1000));
                        break;
                }
            }
        }

    private:
        EventMap events;

        void CheckPortalmeisterAlive()
        {
            if (Creature* portalmeister = me->FindNearestCreature(NPC_PORTALMEISTER, 533.0f))
            {
                if (!portalmeister->IsAlive() || !portalmeister->IsInCombat())
                {
                    me->DespawnOrUnsummon(100);
                }
            }
            else
            {
                me->DespawnOrUnsummon(100);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_horde_portalAI(creature);
    }
};

void AddSC_boss_portalmeister()
{
    new boss_portalmeister();
    new npc_portalmeister_spawner();
    new npc_hellfire_spawner();
    new npc_hellbeast();
    new npc_horde_portal();
}