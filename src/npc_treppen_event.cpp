/*
 * Treppen Event NPCs - Kaykens Reminiszenz
 * Converted from Lua to C++ - Event trigger and waypoint-based add movement
 */

#include "kaykens_reminiszenz.h"

struct TreppenWaypoint
{
    float x, y, z;
};

// Trigger NPC that spawns boss when killed
class npc_treppen_trigger : public CreatureScript
{
public:
    npc_treppen_trigger() : CreatureScript("npc_treppen_trigger") { }

    struct npc_treppen_triggerAI : public ScriptedAI
    {
        npc_treppen_triggerAI(Creature* creature) : ScriptedAI(creature) { }

        void JustDied(Unit* /*killer*/) override
        {
            me->Yell(TreppenEventTexts::SAY_TRIGGER_DEATH, LANG_UNIVERSAL);

            // Spawn the Portalmeister boss and the spawner that handles add waves
            me->SummonCreature(NPC_PORTALMEISTER, -6974.344727f, -1094.695068f, 239.659103f, 5.062332f);
            me->SummonCreature(NPC_PORTALMEISTER_SPAWNER, -6974.344727f, -1094.695068f, 239.659103f, 5.062332f);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_treppen_triggerAI(creature);
    }
};

// Base class for treppen adds (500012, 500013, 500018)
class npc_treppen_add : public CreatureScript
{
public:
    npc_treppen_add() : CreatureScript("npc_treppen_add") { }

    struct npc_treppen_addAI : public ScriptedAI
    {
        npc_treppen_addAI(Creature* creature) : ScriptedAI(creature) 
        {
            InitializeWaypoints();
        }

        void InitializeWaypoints()
        {
            // Waypoint path from original Lua script
            _waypoints = {
                // WP1 - two random paths
                { -6958.987793f, -1154.238159f, 233.687210f },
                { -6966.362793f, -1153.190674f, 233.859695f },
                
                // WP2 - two random paths
                { -6990.481934f, -1187.078491f, 221.640381f },
                { -7003.160645f, -1182.895752f, 219.402618f },
                
                // WP3 - two random paths
                { -7009.167969f, -1208.836304f, 210.101532f },
                { -7020.695801f, -1220.333130f, 206.371948f },
                
                // WP4 - two random paths
                { -6992.294922f, -1232.589355f, 198.362869f },
                { -6992.239746f, -1243.651123f, 195.448257f },
                
                // WP5 - two random paths
                { -6964.606445f, -1257.964722f, 184.145844f },
                { -6972.582031f, -1265.775757f, 185.116440f },
                
                // WP6 - two random paths
                { -6947.762695f, -1263.718140f, 180.451782f },
                { -6952.549316f, -1282.492065f, 176.796097f },
                
                // WP7B (Bottom exit)
                { -6918.900391f, -1257.722412f, 178.717957f },
                { -6918.656738f, -1264.428589f, 178.722961f },
                
                // WP7T (Top exit)
                { -6930.964844f, -1311.983521f, 166.585342f },
                { -6935.612793f, -1316.787109f, 166.622299f }
            };
            
            _currentWP = 0;
        }

        void InitializeAI() override
        {
            events.ScheduleEvent(EVENT_TREPPEN_WAYPOINT, 1000);
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            events.Reset(); // Stop waypoint movement when in combat
        }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            ScriptedAI::EnterEvadeMode(EVADE_REASON_OTHER);
            // Resume from WP4 when leaving combat
            _currentWP = 4;
            events.ScheduleEvent(EVENT_TREPPEN_WAYPOINT, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TREPPEN_WAYPOINT:
                        MoveToNextWaypoint();
                        break;
                    case EVENT_TREPPEN_DESPAWN:
                        me->DespawnOrUnsummon(100);
                        break;
                }
            }

            if (UpdateVictim())
                DoMeleeAttackIfReady();
        }

    private:
        EventMap events;
        std::vector<TreppenWaypoint> _waypoints;
        uint8 _currentWP;

        void MoveToNextWaypoint()
        {
            if (_currentWP >= _waypoints.size())
            {
                events.ScheduleEvent(EVENT_TREPPEN_DESPAWN, 5000);
                return;
            }

            uint32 delay = 0;
            uint32 waypointIndex = 0;
            
            switch (_currentWP)
            {
                case 0: // WP1
                    waypointIndex = urand(0, 1);
                    delay = 6500;
                    break;
                case 1: // WP2
                    waypointIndex = urand(2, 3);
                    delay = waypointIndex == 2 ? 5200 : 5000;
                    break;
                case 2: // WP3
                    waypointIndex = urand(4, 5);
                    delay = 4500;
                    break;
                case 3: // WP4
                    waypointIndex = urand(6, 7);
                    delay = waypointIndex == 6 ? 5000 : 4000;
                    break;
                case 4: // WP5
                    waypointIndex = urand(8, 9);
                    delay = 4500;
                    break;
                case 5: // WP6
                    waypointIndex = urand(10, 11);
                    delay = 4500;
                    break;
                case 6: // WP7 - Final waypoint with two exits
                    {
                        uint32 exitChoice = urand(1, 2);
                        if (exitChoice == 1)
                        {
                            // Bottom exit (WP7B)
                            waypointIndex = urand(12, 13);
                        }
                        else
                        {
                            // Top exit (WP7T)  
                            waypointIndex = urand(14, 15);
                        }
                        delay = 5000;
                    }
                    break;
                default:
                    events.ScheduleEvent(EVENT_TREPPEN_DESPAWN, 5000);
                    return;
            }

            // Move to the selected waypoint
            if (waypointIndex < _waypoints.size())
            {
                const TreppenWaypoint& wp = _waypoints[waypointIndex];
                me->GetMotionMaster()->MovePoint(_currentWP, wp.x, wp.y, wp.z);
                
                _currentWP++;
                events.ScheduleEvent(EVENT_TREPPEN_WAYPOINT, delay);
            }
        }

        void MovementInform(uint32 type, uint32 /*pointId*/) override
        {
            if (type == POINT_MOTION_TYPE)
            {
                // Waypoint reached, timer will handle next movement
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_treppen_addAI(creature);
    }
};

void AddSC_npc_treppen_event()
{
    new npc_treppen_trigger();
    new npc_treppen_add();
}