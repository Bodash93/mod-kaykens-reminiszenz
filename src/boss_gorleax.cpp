/*
 * Gorleax Boss - Kaykens Reminiszenz
 * Converted from Lua to C++ - Complex multi-phase boss with tsunami and brand mechanics
 */

#include "kaykens_reminiszenz.h"

struct GorleaxPosition
{
    float x, y, z, o;
};

class boss_gorleax : public CreatureScript
{
public:
    boss_gorleax() : CreatureScript("boss_gorleax") { }

    struct boss_gorleaxAI : public ScriptedAI
    {
        boss_gorleaxAI(Creature* creature) : ScriptedAI(creature)
        {
            _instance = me->GetInstanceScript();
        }

        void Initialize()
        {
            _phase = 0;  // Start with phase 0 (H-0815)
            
            // Tsunami spawn positions from Lua
            _tsunamiPositions = {
                { -6940.393066f, -1248.153320f, 145.003448f, 2.202164f }, // Entrance tsunami
                { -6927.440918f, -1193.048340f, 144.820419f, 3.808778f }, // Back
                { -6961.249512f, -1234.024536f, 144.381805f, 0.722126f }, // Left side
                { -6976.764648f, -1218.121094f, 144.381409f, 0.608243f }  // Right side
            };
        }

        void Reset() override
        {
            events.Reset();
            Initialize();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            me->Yell(GorleaxTexts::SAY_AGGRO, LANG_UNIVERSAL);
            
            // Spawn entrance tsunami immediately
            me->SummonCreature(NPC_TSUNAMI_ENTRANCE, _tsunamiPositions[0].x, _tsunamiPositions[0].y, 
                              _tsunamiPositions[0].z, _tsunamiPositions[0].o);
            
            // Start phase 0 (H-0815 protocol)
            events.ScheduleEvent(EVENT_GORLEAX_RANDOM_SPELL, 4000);
            events.ScheduleEvent(EVENT_GORLEAX_MELT, 1000);
            events.ScheduleEvent(EVENT_GORLEAX_BRAND_SPELL, 15000);
            events.ScheduleEvent(EVENT_GORLEAX_PHASE_CHECK, 1000);
        }

        void JustDied(Unit* /*killer*/) override
        {
            me->Yell(GorleaxTexts::SAY_DEATH, LANG_UNIVERSAL);
            events.Reset();
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/, DamageEffectType /*damagetype*/, SpellSchoolMask /*damageSchoolMask*/) override
        {
            // Phase transitions based on HP
            if (me->HealthBelowPct(80) && _phase == 0)
            {
                StartPhase(1); // E-420Y Protocol
            }
            else if (me->HealthBelowPct(60) && _phase == 1)
            {
                StartPhase(2); // D-0UK Protocol
            }
            else if (me->HealthBelowPct(42) && _phase == 2)
            {
                StartPhase(3); // AC-7C Protocol
            }
            else if (me->HealthBelowPct(20) && _phase == 3)
            {
                StartPhase(4); // KN-00B Protocol (final phase)
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
                    case EVENT_GORLEAX_RANDOM_SPELL:
                        CastRandomSpell();
                        events.Repeat(Milliseconds(15000));
                        break;
                    case EVENT_GORLEAX_STOMP:
                        DoCastVictim(SPELL_GOR_STOMP);
                        events.Repeat(Milliseconds(urand(15000, 25000)));
                        break;
                    case EVENT_GORLEAX_MELT:
                        DoCastVictim(SPELL_GOR_MELT);
                        // Schedule next melt based on phase
                        if (_phase >= 3)
                            events.Repeat(Milliseconds(12000));
                        else if (_phase >= 1)
                            events.Repeat(Milliseconds(22000));
                        break;
                    case EVENT_GORLEAX_TSUNAMI:
                        SpawnTsunamiWave();
                        // Tsunami frequency increases with phases
                        if (_phase >= 4)
                            events.Repeat(Milliseconds(8000));
                        else if (_phase >= 2)
                            events.Repeat(Milliseconds(10000));
                        break;
                    case EVENT_GORLEAX_BRAND_SPELL:
                        SpawnBrandAtRandomTarget();
                        // Brand frequency increases with phases
                        if (_phase >= 4)
                            events.Repeat(Milliseconds(10000));
                        else if (_phase >= 3)
                            events.Repeat(Milliseconds(12000));
                        else if (_phase >= 2)
                            events.Repeat(Milliseconds(13000));
                        else if (_phase >= 1)
                            events.Repeat(Milliseconds(14000));
                        else
                            events.Repeat(Milliseconds(15000));
                        break;
                    case EVENT_GORLEAX_PHASE_CHECK:
                        // Continuous phase checking
                        events.Repeat(Milliseconds(1000));
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap events;
        InstanceScript* _instance;
        uint8 _phase;
        std::vector<GorleaxPosition> _tsunamiPositions;

        void StartPhase(uint8 phase)
        {
            _phase = phase;
            events.Reset();
            
            // Phase-specific yells
            switch (phase)
            {
                case 1:
                    me->Yell(GorleaxTexts::SAY_PHASE_TWO, LANG_UNIVERSAL);
                    break;
                case 2:
                    me->Yell(GorleaxTexts::SAY_PHASE_THREE, LANG_UNIVERSAL);
                    break;
                case 3:
                    me->Yell(GorleaxTexts::SAY_PHASE_FOUR, LANG_UNIVERSAL);
                    break;
                case 4:
                    me->Yell(GorleaxTexts::SAY_PHASE_FIVE, LANG_UNIVERSAL);
                    break;
            }
            
            // Restart events with phase-specific timings
            events.ScheduleEvent(EVENT_GORLEAX_RANDOM_SPELL, phase >= 3 ? 1000 : (phase >= 1 ? 3000 : 4000));
            events.ScheduleEvent(EVENT_GORLEAX_MELT, phase >= 3 ? 5000 : (phase >= 1 ? 22000 : 1000));
            events.ScheduleEvent(EVENT_GORLEAX_STOMP, 1000);
            
            if (phase >= 1)
                events.ScheduleEvent(EVENT_GORLEAX_TSUNAMI, phase >= 4 ? 8000 : 10000);
                
            events.ScheduleEvent(EVENT_GORLEAX_BRAND_SPELL, 
                                phase >= 4 ? 10000 : (phase >= 3 ? 12000 : (phase >= 2 ? 13000 : (phase >= 1 ? 14000 : 15000))));
            events.ScheduleEvent(EVENT_GORLEAX_PHASE_CHECK, 1000);
        }

        void CastRandomSpell()
        {
            uint32 randomSpell = urand(1, 2);
            if (randomSpell == 1)
                DoCastVictim(SPELL_GOR_WING_BUFFET);
            else
                DoCastVictim(SPELL_GOR_MORTAL_STRIKE);
        }

        void SpawnTsunamiWave()
        {
            uint32 tsunamiType;
            
            // Different tsunami patterns based on phase
            switch (_phase)
            {
                case 1: // Phase 2: Random 2 tsunamis
                    tsunamiType = urand(1, 2);
                    if (tsunamiType == 1)
                        me->SummonCreature(NPC_TSUNAMI_LEFT, _tsunamiPositions[2].x, _tsunamiPositions[2].y, _tsunamiPositions[2].z, _tsunamiPositions[2].o);
                    else
                        me->SummonCreature(NPC_TSUNAMI_RIGHT, _tsunamiPositions[3].x, _tsunamiPositions[3].y, _tsunamiPositions[3].z, _tsunamiPositions[3].o);
                    break;
                    
                case 2: // Phase 3: Random 3 tsunamis
                    tsunamiType = urand(1, 3);
                    if (tsunamiType == 1)
                        me->SummonCreature(NPC_TSUNAMI_BACK, _tsunamiPositions[1].x, _tsunamiPositions[1].y, _tsunamiPositions[1].z, _tsunamiPositions[1].o);
                    else if (tsunamiType == 2)
                        me->SummonCreature(NPC_TSUNAMI_LEFT, _tsunamiPositions[2].x, _tsunamiPositions[2].y, _tsunamiPositions[2].z, _tsunamiPositions[2].o);
                    else
                        me->SummonCreature(NPC_TSUNAMI_RIGHT, _tsunamiPositions[3].x, _tsunamiPositions[3].y, _tsunamiPositions[3].z, _tsunamiPositions[3].o);
                    break;
                    
                case 3:
                case 4: // Phase 4 & 5: Dual tsunamis
                    tsunamiType = urand(1, 2);
                    if (tsunamiType == 1)
                    {
                        me->SummonCreature(NPC_TSUNAMI_LEFT, _tsunamiPositions[2].x, _tsunamiPositions[2].y, _tsunamiPositions[2].z, _tsunamiPositions[2].o);
                        me->SummonCreature(NPC_TSUNAMI_BACK, _tsunamiPositions[1].x, _tsunamiPositions[1].y, _tsunamiPositions[1].z, _tsunamiPositions[1].o);
                    }
                    else
                    {
                        me->SummonCreature(NPC_TSUNAMI_RIGHT, _tsunamiPositions[3].x, _tsunamiPositions[3].y, _tsunamiPositions[3].z, _tsunamiPositions[3].o);
                        me->SummonCreature(NPC_TSUNAMI_BACK, _tsunamiPositions[1].x, _tsunamiPositions[1].y, _tsunamiPositions[1].z, _tsunamiPositions[1].o);
                    }
                    break;
            }
        }

        void SpawnBrandAtRandomTarget()
        {
            if (Unit* target = SelectTarget(SelectTargetMethod::Random))
            {
                Position pos = target->GetPosition();
                
                // Different brand NPCs based on phase
                uint32 brandNPC = NPC_BRAND_PHASE1 + _phase; // 500040 + phase
                if (Creature* brand = me->SummonCreature(brandNPC, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation()))
                    brand->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_gorleaxAI(creature);
    }
};

// Tsunami NPCs
class npc_gorleax_tsunami : public CreatureScript
{
public:
    npc_gorleax_tsunami() : CreatureScript("npc_gorleax_tsunami") { }

    struct npc_gorleax_tsunamiAI : public ScriptedAI
    {
        npc_gorleax_tsunamiAI(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            // Apply visual effects
            DoCastSelf(SPELL_TSUNAMI_VISUAL);
            DoCastSelf(SPELL_TSUNAMI_AURA);
            
            // Start movement based on NPC type
            events.ScheduleEvent(EVENT_TSUNAMI_MOVE, 3000);
            
            // Check if boss is still alive
            if (me->GetEntry() == NPC_TSUNAMI_ENTRANCE)
                events.ScheduleEvent(EVENT_TSUNAMI_DESPAWN, 1000);
            else
                events.ScheduleEvent(EVENT_TSUNAMI_DESPAWN, 7500);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TSUNAMI_MOVE:
                        MoveTsunamiToTarget();
                        break;
                    case EVENT_TSUNAMI_DESPAWN:
                        if (me->GetEntry() == NPC_TSUNAMI_ENTRANCE)
                        {
                            // Special check for entrance tsunami
                            if (Creature* gorleax = me->FindNearestCreature(NPC_GORLEAX, 533.0f))
                            {
                                if (gorleax->IsAlive() && gorleax->IsInCombat())
                                {
                                    events.Repeat(Milliseconds(1000));
                                    return;
                                }
                            }
                        }
                        me->DespawnOrUnsummon(1000);
                        break;
                }
            }
        }

    private:
        EventMap events;

        void MoveTsunamiToTarget()
        {
            // Movement patterns based on tsunami type
            switch (me->GetEntry())
            {
                case NPC_TSUNAMI_ENTRANCE:
                    me->GetMotionMaster()->MovePoint(1, -6973.884766f, -1205.018799f, 144.381393f);
                    break;
                case NPC_TSUNAMI_BACK:
                    me->GetMotionMaster()->MovePoint(1, -6933.352539f, -1191.399170f, 144.790009f);
                    break;
                case NPC_TSUNAMI_LEFT:
                    me->GetMotionMaster()->MovePoint(1, -6921.375488f, -1195.240723f, 144.818832f);
                    break;
                case NPC_TSUNAMI_RIGHT:
                    me->GetMotionMaster()->MovePoint(1, -6960.881348f, -1219.388672f, 144.417847f);
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gorleax_tsunamiAI(creature);
    }
};

// Brand NPCs
class npc_gorleax_brand : public CreatureScript
{
public:
    npc_gorleax_brand() : CreatureScript("npc_gorleax_brand") { }

    struct npc_gorleax_brandAI : public ScriptedAI
    {
        npc_gorleax_brandAI(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            DoCastSelf(SPELL_BRAND_AURA);
            events.ScheduleEvent(EVENT_BRAND_DESPAWN_CHECK, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BRAND_DESPAWN_CHECK:
                        if (Creature* gorleax = me->FindNearestCreature(NPC_GORLEAX, 533.0f))
                        {
                            uint32 requiredHpPct = GetRequiredBossHpForPhase();
                            if (gorleax->GetHealthPct() <= requiredHpPct || !gorleax->IsAlive() || !gorleax->IsInCombat())
                            {
                                me->DespawnOrUnsummon(100);
                                return;
                            }
                        }
                        events.Repeat(Milliseconds(1000));
                        break;
                }
            }
        }

    private:
        EventMap events;

        uint32 GetRequiredBossHpForPhase()
        {
            switch (me->GetEntry())
            {
                case NPC_BRAND_PHASE1: return 80;
                case NPC_BRAND_PHASE2: return 60;
                case NPC_BRAND_PHASE3: return 42;
                case NPC_BRAND_PHASE4: return 20;
                case NPC_BRAND_PHASE5: return 0;
                default: return 100;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gorleax_brandAI(creature);
    }
};

void AddSC_boss_gorleax()
{
    new boss_gorleax();
    new npc_gorleax_tsunami();
    new npc_gorleax_brand();
}