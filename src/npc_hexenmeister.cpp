/*
 * Hexenmeister NPC - Kaykens Reminiszenz
 * Modern implementation with proper spell timing and emotes
 */

#include "kaykens_reminiszenz.h"

#ifdef DEBUG
#define KR_DEBUG_SAY(text) me->Say(text, LANG_UNIVERSAL)
#else
#define KR_DEBUG_SAY(text)
#endif

class npc_hexenmeister : public CreatureScript
{
public:
    npc_hexenmeister() : CreatureScript("npc_hexenmeister") { }

    struct npc_hexenmeisterAI : public ScriptedAI
    {
        npc_hexenmeisterAI(Creature* creature) : ScriptedAI(creature) 
        {
            _instance = me->GetInstanceScript();
        }

        void Reset() override
        {
            // ULTIMATE DEBUG - Test if Hexenmeister script runs
            KR_DEBUG_SAY("ULTIMATE DEBUG: Hexenmeister Reset() called!");
            
            events.Reset();
            
            // Clear any existing emotes before setting new ones
            me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
            KR_DEBUG_SAY("DEBUG: Emotes cleared on Reset!");
            
            CastDarkEnergyOnPolydeuces();
            // Start continuous dark energy casting
            events.ScheduleEvent(EVENT_DARK_ENERGY_CAST, 4000); // Exact spell cast time
        }
        
        void JustEngagedWith(Unit* /*who*/) override
        {
            // ULTIMATE DEBUG - Test if combat works
            KR_DEBUG_SAY("ULTIMATE DEBUG: Hexenmeister Combat started!");
            
            // Random modern C++ string yell
            uint8 randomYell = urand(1, 3);
            switch (randomYell)
            {
                case 1:
                    me->Yell(PolydeucesTexts::SAY_HEXEN_AGGRO_1, LANG_UNIVERSAL);
                    break;
                case 2:
                    me->Yell(PolydeucesTexts::SAY_HEXEN_AGGRO_2, LANG_UNIVERSAL);
                    break;
                case 3:
                    me->Yell(PolydeucesTexts::SAY_HEXEN_AGGRO_3, LANG_UNIVERSAL);
                    break;
            }
            
            // Cancel dark energy when entering combat
            events.CancelEvent(EVENT_DARK_ENERGY_CAST);
            
            // Interrupt any active casting immediately
            me->InterruptNonMeleeSpells(false);
            
            // Explicitly clear casting emotes and set to combat stance
            me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
            KR_DEBUG_SAY("DEBUG: Emotes cleared for combat!");
            me->SetStandState(UNIT_STAND_STATE_STAND);
            
            events.ScheduleEvent(EVENT_SHADOW_BOLT, urand(2000, 4000));
            events.ScheduleEvent(EVENT_CORRUPTION, urand(5000, 8000));
        }
        
        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            ScriptedAI::EnterEvadeMode(EVADE_REASON_OTHER);
            
            // Clear emotes first, then set casting emote with delay for proper transition
            me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
            KR_DEBUG_SAY("DEBUG: Evade mode - emotes cleared, will resume casting!");
            
            // Delay the casting emote to avoid conflicts
            events.ScheduleEvent(EVENT_DARK_ENERGY_CAST, 2000); // Longer delay for stable transition
        }
        
        void CastDarkEnergyOnPolydeuces()
        {
            if (Creature* polydeuces = me->FindNearestCreature(NPC_POLYDEUCES, 533.0f))
            {
                if (polydeuces->IsAlive())
                {
                    // Set permanent casting stance
                    me->SetStandState(UNIT_STAND_STATE_STAND);
                    
                    // Use Trial of Crusader style spell precast emote (more reliable)
                    me->HandleEmoteCommand(EMOTE_STATE_SPELL_PRECAST);
                    KR_DEBUG_SAY("DEBUG: Cast emote set - should see casting animation!");
                    
                    // Cast visual dark energy spell
                    DoCast(polydeuces, SPELL_DARK_ENERGY_VISUAL, true);
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SHADOW_BOLT:
                        if (Unit* target = me->GetVictim())
                            DoCast(target, SPELL_SHADOW_BOLT);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT, urand(3000, 5000));
                        break;
                    case EVENT_CORRUPTION:
                        if (Unit* target = me->GetVictim())
                            DoCast(target, SPELL_CORRUPTION);
                        events.ScheduleEvent(EVENT_CORRUPTION, urand(8000, 12000));
                        break;
                    case EVENT_DARK_ENERGY_CAST:
                        // Only cast dark energy when NOT in combat
                        if (!me->IsInCombat())
                        {
                            CastDarkEnergyOnPolydeuces();
                            events.ScheduleEvent(EVENT_DARK_ENERGY_CAST, 4000); // Exact spell duration
                        }
                        break;
                }
            }

            if (UpdateVictim())
            {
                DoMeleeAttackIfReady();
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
            me->Yell(PolydeucesTexts::SAY_HEXEN_DEATH, LANG_UNIVERSAL);
            
            // Notify instance script (Sindragosa style)
            if (_instance)
            {
                if (Creature* polydeuces = _instance->GetCreature(DATA_POLYDEUCES))
                    polydeuces->AI()->DoAction(ACTION_HEXENMEISTER_DIED);
            }
        }

    private:
        EventMap events;
        InstanceScript* _instance;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hexenmeisterAI(creature);
    }
};

void AddSC_npc_hexenmeister()
{
    new npc_hexenmeister();
}