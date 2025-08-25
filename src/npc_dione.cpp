/*
 * Dione NPC - Kaykens Reminiszenz 
 * Ported from Lua script with original spell behavior
 */

#include "kaykens_reminiszenz.h"

class npc_dione : public CreatureScript
{
public:
    npc_dione() : CreatureScript("npc_dione") { }

    struct npc_dioneAI : public ScriptedAI
    {
        npc_dioneAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            // Set Dione as rooted but don't immediately start combat
            // Combat will be initiated by the boss spawn function
            me->SetControlled(true, UNIT_STATE_ROOT);
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            // Ensure Dione is rooted during combat
            me->SetControlled(true, UNIT_STATE_ROOT);
            
            // Simplified continuous spell rotation
            events.ScheduleEvent(EVENT_DIONE_TRAP, urand(3000, 6000));    // Faster start
            events.ScheduleEvent(EVENT_DIONE_FROSTBOLT1, urand(2000, 4000));  // Quicker first cast
            events.ScheduleEvent(EVENT_DIONE_FROSTBOLT2, urand(8000, 12000)); // Earlier strong attack
            
            // Debug message
            me->Say("Dione joins the battle!", LANG_UNIVERSAL);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DIONE_TRAP:
                        // Cast AOE trap on random target (like Lua)
                        if (Unit* target = SelectTarget(SelectTargetMethod::Random))
                            DoCast(target, SPELL_DIONE_TRAP);
                        events.ScheduleEvent(EVENT_DIONE_TRAP, urand(8000, 16000));
                        break;
                    case EVENT_DIONE_FROSTBOLT1:
                        // Cast single target frostbolt on victim
                        if (Unit* target = me->GetVictim())
                            DoCast(target, SPELL_DIONE_FROSTBOLT1, true);
                        events.ScheduleEvent(EVENT_DIONE_FROSTBOLT1, urand(5000, 10000));
                        break;
                    case EVENT_DIONE_FROSTBOLT2:
                        // Stronger frostbolt on random target  
                        if (Unit* target = SelectTarget(SelectTargetMethod::Random))
                            DoCast(target, SPELL_DIONE_FROSTBOLT2, true);
                        events.ScheduleEvent(EVENT_DIONE_FROSTBOLT2, urand(18000, 22000));
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) override
        {
            // Clean up events and despawn after 1 second (like Lua)
            events.Reset();
            me->DespawnOrUnsummon(1000);
        }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            // Like Lua Dione_OnWipe - remove events and despawn
            events.Reset();
            me->DespawnOrUnsummon(1000);
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dioneAI(creature);
    }
};

void AddSC_npc_dione()
{
    new npc_dione();
}