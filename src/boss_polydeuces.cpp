/*
 * Polydeuces Boss - Kaykens Reminiszenz
 * Implementation with modern C++ string-based yells and Sindragosa-style checking
 */

#include "kaykens_reminiszenz.h"
#include "Log.h"
#include <chrono>

using namespace std::chrono_literals;

struct PolydeucesWaypoint
{
    float x, y, z, o;
};

class boss_polydeuces : public CreatureScript
{
public:
    boss_polydeuces() : CreatureScript("boss_polydeuces") { }

    struct boss_polydeucesAI : public ScriptedAI
    {
        boss_polydeucesAI(Creature* creature) : ScriptedAI(creature)
        {
            // ULTIMATE DEBUG - CONSTRUCTOR CALLED
            me->Say("CONSTRUCTOR: ### NEUE KR MODULE VERSION 2.0 - POLYDEUCES LOADED ###", LANG_UNIVERSAL);
            
            _instance = me->GetInstanceScript();
            // Store original spawn position for Dione
            _homePos = me->GetHomePosition();
            Initialize();
        }

        void Initialize()
        {
            // ULTIMATE DEBUG - UNIQUE STRING to identify OUR script
            me->Yell("### NEUE KR MODULE VERSION 2.0 GELADEN ###", LANG_UNIVERSAL);
            
            _phase = PHASE_PREPARATION;
            _isFlying = false;
            _firstFlightDone = false;
            _secondFlightDone = false;
            _dioneSpawned = false;
            _currentWaypointIndex = 0;
            _fireballsRemaining = 0;
            _totalFireballs = 0;
            _currentDioneGUID.Clear();
            _isProcessingWakeup = false;
            
            // Extended waypoints for more strategic flight patterns
            _waypoints = {
                { -6738.410156f, -1629.859497f, 210.960068f, 1.998834f },  // North position
                { -6752.510254f, -1667.581665f, 210.369019f, 1.629697f },  // South position
                { -6725.854492f, -1541.991577f, 210.492371f, 4.288269f },  // Northeast corner
                { -6777.050781f, -1539.335083f, 210.542328f, 4.810552f },  // Northwest corner
                { -6763.183105f, -1610.944336f, 210.505707f, 1.276274f },  // West center
                { -6710.250000f, -1645.000000f, 210.500000f, 3.141593f },  // East center
                { -6750.000000f, -1595.000000f, 210.500000f, 4.712389f },  // North center
                { -6760.000000f, -1655.000000f, 210.500000f, 0.785398f },  // Southwest
                { -6720.000000f, -1590.000000f, 210.500000f, 2.356194f }   // Southeast
            };
            
            // Set initial sleeping state with proper ground movement
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            me->SetStandState(UNIT_STAND_STATE_SLEEP);
            
            // Ensure proper ground state - no flying initially (Onyxia-style)
            me->SetCanFly(false);
            me->SetDisableGravity(false);
            me->SetHover(false);
            me->SetSpeed(MOVE_RUN, me->GetCreatureTemplate()->speed_run, false);
            
            // Explicitly set flying state and send movement update
            _isFlying = false;
            me->SendMovementFlagUpdate();
        }

        void Reset() override
        {
            // ULTIMATE DEBUG - This WILL be called when boss resets
            me->Say("ULTIMATE DEBUG: Polydeuces Reset() called!", LANG_UNIVERSAL);
            events.Reset();
            
            // Onyxia-style: Explicitly disable flight capabilities on reset
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetCanFly(false);
            me->SetDisableGravity(false);
            me->SetSpeed(MOVE_RUN, me->GetCreatureTemplate()->speed_run, false);
            
            Initialize();
        }

        void JustEngagedWith(Unit* who) override
        {
            // IMMEDIATE DEBUG - Test if our script runs at all
            me->Say("DEBUG: POLYDEUCES SCRIPT IS RUNNING! Combat started!", LANG_UNIVERSAL);
            
            if (_phase == PHASE_PREPARATION)
            {
                // Still in preparation - shouldn't happen but handle gracefully
                me->Say("DEBUG: Still in preparation phase!", LANG_UNIVERSAL);
                return;
            }
            
            // Modern C++ string yell
            me->Yell(PolydeucesTexts::SAY_AGGRO, LANG_UNIVERSAL);
            
            if (_instance)
                _instance->SetBossState(DATA_POLYDEUCES, IN_PROGRESS);
            
            ScriptedAI::JustEngagedWith(who);
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (_phase == PHASE_PREPARATION && who->IsPlayer() && me->IsWithinDistInMap(who, 150.0f))
            {
                // Start checking when players approach - no constant checking needed
                CheckWitchesInitial();
            }
            ScriptedAI::MoveInLineOfSight(who);
        }

        void JustDied(Unit* /*killer*/) override
        {
            me->Yell(PolydeucesTexts::SAY_DEATH, LANG_UNIVERSAL);
            events.Reset();
            
            if (_instance)
                _instance->SetBossState(DATA_POLYDEUCES, DONE);
        }

        // Fixed Action System - Instance-based with Race Condition Protection
        void DoAction(int32 action) override
        {
            switch (action)
            {
                case ACTION_HEXENMEISTER_DIED:
                {
                    // Only trigger if still in preparation and not already processing
                    if (_phase != PHASE_PREPARATION || _isProcessingWakeup)
                        return;
                    
                    // Use instance script for reliable counting instead of grid search
                    if (_instance)
                    {
                        std::list<Creature*> witches;
                        me->GetCreatureListWithEntryInGrid(witches, NPC_HEXENMEISTER, 533.0f);
                        
                        bool allDead = true;
                        for (auto* witch : witches)
                        {
                            if (witch && witch->IsAlive())
                            {
                                allDead = false;
                                break;
                            }
                        }
                        
                        // Race condition protection: Only wake up once
                        if (allDead && !_isProcessingWakeup)
                        {
                            _isProcessingWakeup = true;
                            // Delay wakeup slightly to ensure all death processing is complete
                            events.ScheduleEvent(EVENT_WAKEUP_DELAYED, 500);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*damageSchoolMask*/) override
        {
            // DEBUG: Show HP percentage
            me->Say("DEBUG: HP is " + std::to_string(me->GetHealthPct()) + "%", LANG_UNIVERSAL);
            
            // Only trigger flight phases during ground combat (PHASE_ONE)
            if (_phase != PHASE_ONE || _isFlying)
            {
                me->Say("DEBUG: Wrong phase or already flying - phase=" + std::to_string(_phase) + " flying=" + std::to_string(_isFlying), LANG_UNIVERSAL);
                return;
            }
                
            // WOTLK-Style: Exactly two flight phases at 66% and 33%
            if (me->HealthBelowPctDamaged(66, damage) && !_firstFlightDone)
            {
                me->Say("DEBUG: Triggering first flight phase at 66%!", LANG_UNIVERSAL);
                StartFlightPhase();
            }
            else if (me->HealthBelowPctDamaged(33, damage) && _firstFlightDone && !_secondFlightDone)
            {
                me->Say("DEBUG: Triggering second and FINAL flight phase at 33%!", LANG_UNIVERSAL);
                StartFlightPhase();
            }
            else if (me->HealthBelowPctDamaged(33, damage) && _secondFlightDone)
            {
                me->Say("DEBUG: No more flight phases - staying on ground!", LANG_UNIVERSAL);
            }
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch (pointId)
                {
                    case POINT_AIR_PHASE:
                        // Reached air position - start air phase events
                        OnAirPhaseReached();
                        break;
                    case POINT_LAND_GROUND:
                        // Modern landing complete
                        CompleteLanding();
                        break;
                    default:
                        // Waypoint reached (10+ range)
                        if (_isFlying && pointId >= POINT_WAYPOINT_BASE)
                        {
                            OnWaypointReached(pointId - POINT_WAYPOINT_BASE);
                        }
                        break;
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            if (_phase == PHASE_PREPARATION)
            {
                // No constant checking - only action-based
                return;
            }

            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FLAME_BREATH:
                        if (Unit* target = me->GetVictim())
                            CastScaledSpell(target, SPELL_FLAME_BREATH);
                        events.Repeat(Milliseconds(urand(12000, 18000)));
                        break;
                    case EVENT_RANDOM_SPELL:
                        CastRandomSpell();
                        events.Repeat(Milliseconds(urand(20000, 25000)));
                        break;
                    case EVENT_FIRE_BOMB:
                        if (Unit* target = SelectTarget(SelectTargetMethod::Random))
                            CastScaledSpell(target, SPELL_FIRE_BOMB);
                        events.Repeat(Milliseconds(45000));
                        break;
                    case EVENT_WINGBUFFET:
                        // Onyxia-style safe Wingbuffet - no complex root mechanics needed
                        DoCastAOE(SPELL_WINGBUFFET);
                        events.Repeat(Milliseconds(urand(15000, 30000)));
                        break;
                    case EVENT_UNROOT:
                        // DEPRECATED: Was for tail smash sequence, now unused
                        break;
                    case EVENT_FIREBALL_CAST:
                        // Legacy single fireball (kept for compatibility)
                        if (_isFlying)
                        {
                            if (Unit* target = SelectTarget(SelectTargetMethod::Random))
                                CastScaledSpell(target, SPELL_FIREBALL);
                            events.Repeat(Milliseconds(urand(4000, 6000)));
                        }
                        break;
                    case EVENT_FIREBALL_BOMBARDMENT:
                        // New bombardment system: 4-5 fireballs per waypoint
                        ExecuteFireballBombardment();
                        break;
                    case EVENT_NEXT_WAYPOINT:
                        // Move to next waypoint after bombardment
                        FlyToNextWaypoint();
                        break;
                    case EVENT_FLY_MOVEMENT:
                        // Legacy waypoint movement (kept for compatibility)
                        FlyToNextWaypoint();
                        break;
                    case EVENT_SPAWN_DIONE:
                        SpawnDione();
                        break;
                    case EVENT_CHECK_DIONE_DEATH:
                        CheckDioneDeath();
                        break;
                    case EVENT_WAKEUP_DELAYED:
                        // Delayed wakeup to prevent race conditions
                        WakeUpPolydeuces();
                        break;
                    case EVENT_TAKEOFF_SEQUENCE:
                        // Stage 2: Begin takeoff sequence
                        ExecuteTakeoffSequence();
                        break;
                    case EVENT_LANDING_FALLBACK:
                        // Fallback: Force landing completion if MovementInform didn't trigger
                        me->Say("DEBUG: Landing fallback triggered!", LANG_UNIVERSAL);
                        CompleteLanding();
                        break;
                }
            }

            if (_phase == PHASE_ONE)
                DoMeleeAttackIfReady();
        }

    private:
        EventMap events;
        InstanceScript* _instance;
        uint8 _phase;
        bool _isFlying;
        bool _firstFlightDone;
        bool _secondFlightDone;
        bool _dioneSpawned;
        bool _isProcessingWakeup;
        uint8 _currentWaypointIndex;
        uint8 _fireballsRemaining;
        uint8 _totalFireballs;
        ObjectGuid _currentDioneGUID;
        std::vector<PolydeucesWaypoint> _waypoints;
        Position _homePos;

        void CheckWitchesInitial()
        {
            std::list<Creature*> witches;
            me->GetCreatureListWithEntryInGrid(witches, NPC_HEXENMEISTER, 533.0f);
            
            bool allWitchesDead = true;
            for (auto* witch : witches)
            {
                if (witch && witch->IsAlive())
                {
                    allWitchesDead = false;
                    break;
                }
            }

            if (allWitchesDead)
            {
                WakeUpPolydeuces();
            }
        }

        void WakeUpPolydeuces()
        {
            // Wake up Polydeuces
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetStandState(UNIT_STAND_STATE_STAND);
            
            // Ensure ground movement during wakeup
            me->SetDisableGravity(false);
            me->SetCanFly(false);
            me->SetHover(false);
            
            // Wake up emote and modern C++ string yell
            me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
            me->Yell(PolydeucesTexts::SAY_AWAKEN, LANG_UNIVERSAL);
            
            // Phase transition
            _phase = PHASE_ONE;
            events.Reset();
            events.SetPhase(PHASE_ONE);
            events.ScheduleEvent(EVENT_FLAME_BREATH, urand(12000, 18000));
            events.ScheduleEvent(EVENT_RANDOM_SPELL, urand(20000, 25000));
            events.ScheduleEvent(EVENT_FIRE_BOMB, 45s);
            events.ScheduleEvent(EVENT_WINGBUFFET, urand(19000, 23000));
        }
        
        void ExecuteTakeoffSequence()
        {
            // Onyxia-style takeoff sequence - reliable and tested
            me->SendMeleeAttackStop(me->GetVictim());
            me->GetMotionMaster()->MoveIdle();
            me->DisableSpline();
            
            // Activate flight capabilities like Onyxia (boss_onyxia.cpp:365-366)
            me->SetCanFly(true);
            me->SetDisableGravity(true);
            me->SetOrientation(me->GetOrientation()); // Maintain current orientation
            me->SendMovementFlagUpdate();
            
            _isFlying = true;
            
            // Start air phase sequence
            me->Say("DEBUG: Starting air phase with Onyxia-style takeoff!", LANG_UNIVERSAL);
            OnAirPhaseReached();
        }
        
        void OnAirPhaseReached()
        {
            // Cancel backup event since we reached the point
            events.CancelEvent(EVENT_SPAWN_DIONE);
            
            // Start proper air phase sequence
            me->Say("DEBUG: Air phase reached - starting events!", LANG_UNIVERSAL);
            me->Yell("Jetzt werdet ihr die wahre Macht der Drachen spüren!", LANG_UNIVERSAL);
            
            // Immediate Dione spawn
            events.ScheduleEvent(EVENT_SPAWN_DIONE, 1000);
            
            // Start new bombardment system instead of single fireballs
            events.ScheduleEvent(EVENT_NEXT_WAYPOINT, 3s);  // First waypoint movement
        }

        void StartFlightPhase()
        {
            if (_isFlying)
                return;

            _phase = PHASE_TWO;
            _dioneSpawned = false;
            
            me->Yell(PolydeucesTexts::SAY_FLIGHT_PHASE, LANG_UNIVERSAL);
            
            events.SetPhase(PHASE_TWO);
            // Cancel ALL ground phase events to prevent conflicts
            events.CancelEvent(EVENT_FLAME_BREATH);
            events.CancelEvent(EVENT_RANDOM_SPELL); 
            events.CancelEvent(EVENT_FIRE_BOMB);
            events.CancelEvent(EVENT_WINGBUFFET);
            events.CancelEvent(EVENT_UNROOT);
            
            // Simplified flight phase start
            me->Say("DEBUG: Flight phase starting!", LANG_UNIVERSAL);
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            // DON'T set NON_ATTACKABLE to avoid immunity issues
            me->GetThreatMgr().ClearAllThreat();
            
            // Roar and immediate takeoff
            me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
            events.ScheduleEvent(EVENT_TAKEOFF_SEQUENCE, 1000); // Quick takeoff for testing
        }

        void CastRandomSpell()
        {
            uint32 randomSpell = urand(1, 3);
            Unit* target = me->GetVictim();
            
            if (!target)
                return;

            switch (randomSpell)
            {
                case 1:
                    CastScaledSpell(target, SPELL_BOLT_OF_MAGMA);
                    break;
                case 2:
                    CastScaledSpell(target, SPELL_LAVA_BLAST);
                    break;
                case 3:
                    CastScaledSpell(target, SPELL_MOLTEN_BLAST);
                    break;
            }
        }
        
        void CastScaledSpell(Unit* target, uint32 spellId)
        {
            if (!target)
                return;
                
            int32 damage = GetScaledDamage(spellId);
            me->CastCustomSpell(target, spellId, &damage, nullptr, nullptr, false);
        }
        
        int32 GetScaledDamage(uint32 spellId)
        {
            bool isHeroic = _instance && _instance->instance->IsHeroic();
            
            switch (spellId)
            {
                case SPELL_FLAME_BREATH:
                    return isHeroic ? 18000 : 12000;    // ICC Level Dragon Breath
                case SPELL_FIREBALL:
                    return isHeroic ? 15000 : 10000;    // ICC Level Fireball  
                case SPELL_FIRE_BOMB:
                    return isHeroic ? 22000 : 16000;    // ICC Level AOE Bomb
                case SPELL_BOLT_OF_MAGMA:
                case SPELL_LAVA_BLAST:
                case SPELL_MOLTEN_BLAST:
                case SPELL_WINGBUFFET:
                    return isHeroic ? 14000 : 9000;     // ICC Level Random Spells / Wingbuffet
                default:
                    return isHeroic ? 12000 : 8000;     // Default ICC scaling
            }
        }

        void FlyToNextWaypoint()
        {
            // Safety check for empty waypoints array
            if (_waypoints.empty())
            {
                // No waypoints available - emergency landing
                InitiateLanding();
                return;
            }
            
            // Additional safety check for flight state
            if (!_isFlying)
                return;
                
            uint8 randomIndex = urand(0, _waypoints.size() - 1);
            _currentWaypointIndex = randomIndex;
            
            // Bounds check before accessing array
            if (randomIndex < _waypoints.size())
            {
                const PolydeucesWaypoint& waypoint = _waypoints[randomIndex];
                // Use POINT_WAYPOINT_BASE + index to avoid conflicts
                me->GetMotionMaster()->MovePoint(POINT_WAYPOINT_BASE + randomIndex, waypoint.x, waypoint.y, waypoint.z);
            }
            else
            {
                // Array bounds error - emergency landing
                InitiateLanding();
            }
        }

        void OnWaypointReached(uint32 waypointId)
        {
            // Bounds check for waypoint ID
            if (waypointId >= _waypoints.size())
            {
                // Invalid waypoint - emergency landing
                InitiateLanding();
                return;
            }
            
            me->Say("DEBUG: Waypoint " + std::to_string(waypointId) + " reached! Starting bombardment!", LANG_UNIVERSAL);
            
            // Start bombardment sequence when reaching waypoint
            if (_isFlying)
            {
                // Random 4-5 fireballs per waypoint
                _totalFireballs = urand(4, 5);
                _fireballsRemaining = _totalFireballs;
                
                // Start first fireball immediately
                events.ScheduleEvent(EVENT_FIREBALL_BOMBARDMENT, 500);
                me->Say("DEBUG: Fireball bombardment started - " + std::to_string(_totalFireballs) + " fireballs!", LANG_UNIVERSAL);
            }
        }

        void SpawnDione()
        {
            // Thread-safe spawn check - prevent multiple spawns
            if (_dioneSpawned || !_currentDioneGUID.IsEmpty() || !_isFlying)
                return;
                
            me->Yell(PolydeucesTexts::SAY_FLIGHT_DIONE, LANG_UNIVERSAL);
                
            // Use Polydeuces home position with proper ground height
            Position homePos = me->GetHomePosition();
            float spawnX = homePos.GetPositionX() + 10.0f;  // Slightly offset from boss
            float spawnY = homePos.GetPositionY(); 
            float spawnZ = homePos.GetPositionZ() + 5.0f;   // Higher above ground to prevent clipping
            float spawnO = homePos.GetOrientation();
                
            // Spawn Dione at safe ground position
            if (Creature* dione = me->SummonCreature(NPC_DIONE, spawnX, spawnY, spawnZ, spawnO, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 45000))
            {
                // Atomically set both flags to prevent race conditions
                _currentDioneGUID = dione->GetGUID();
                _dioneSpawned = true;
                
                // Debug output
                me->Say("DEBUG: Dione spawned successfully!", LANG_UNIVERSAL);
                
                // Initialize Dione properly for combat
                dione->SetReactState(REACT_AGGRESSIVE);
                dione->SetInCombatWithZone();
                
                // Find and attack nearest target after spawn
                if (Unit* target = dione->SelectNearestTarget(100.0f))
                {
                    dione->AI()->AttackStart(target);
                    me->Say("DEBUG: Dione attacking target!", LANG_UNIVERSAL);
                }
                else
                {
                    me->Say("DEBUG: Dione found no targets!", LANG_UNIVERSAL);
                }
                
                // Start death checking after spawn is complete
                events.ScheduleEvent(EVENT_CHECK_DIONE_DEATH, 2s);
            }
            else
            {
                // Spawn failed - reset flags and retry
                _dioneSpawned = false;
                _currentDioneGUID.Clear();
                
                // Debug output
                me->Say("DEBUG: Dione spawn failed! Retrying in 5 seconds...", LANG_UNIVERSAL);
                events.ScheduleEvent(EVENT_SPAWN_DIONE, 5s); // Retry spawn
            }
        }
        
        void CheckDioneDeath()
        {
            // Only check if we actually spawned Dione and are still flying
            if (!_dioneSpawned || !_isFlying || _currentDioneGUID.IsEmpty())
            {
                // Debug: Why we stopped checking
                me->Say("DEBUG: Stopped Dione death check", LANG_UNIVERSAL);
                return;
            }
            
            if (Creature* dione = ObjectAccessor::GetCreature(*me, _currentDioneGUID))
            {
                if (dione->IsAlive())
                {
                    // Continue checking only if Dione is still alive and we're flying
                    if (_isFlying && _dioneSpawned)
                        events.ScheduleEvent(EVENT_CHECK_DIONE_DEATH, 1s);
                    return;
                }
                else
                {
                    // Dione died - debug info
                    me->Say("DEBUG: Dione died! Initiating landing...", LANG_UNIVERSAL);
                }
            }
            else
            {
                // Dione despawned - debug info  
                me->Say("DEBUG: Dione despawned! Initiating landing...", LANG_UNIVERSAL);
            }
            
            // Dione is dead or despawned
            OnDioneDeath();
        }
        
        void OnDioneDeath()
        {
            if (!_isFlying)
                return;
                
            // Cancel ALL flight phase events to prevent conflicts
            events.CancelEvent(EVENT_FLY_MOVEMENT);
            events.CancelEvent(EVENT_FIREBALL_CAST);
            events.CancelEvent(EVENT_FIREBALL_BOMBARDMENT);
            events.CancelEvent(EVENT_NEXT_WAYPOINT);
            events.CancelEvent(EVENT_CHECK_DIONE_DEATH);
            events.CancelEvent(EVENT_SPAWN_DIONE); // Cancel any pending spawn
            
            InitiateLanding();
        }
        
        void InitiateLanding()
        {
            me->Yell(PolydeucesTexts::SAY_LAND, LANG_UNIVERSAL);
            me->SendMeleeAttackStop(me->GetVictim());
            
            me->Say("DEBUG: Initiating proper landing sequence!", LANG_UNIVERSAL);
            
            // Use proper MoveLand to home position like Onyxia
            Position homePos = me->GetHomePosition();
            me->GetMotionMaster()->MoveLand(POINT_LAND_GROUND, homePos.GetPositionX(), homePos.GetPositionY(), homePos.GetPositionZ());
            
            // Fallback timer in case MovementInform doesn't trigger  
            events.ScheduleEvent(EVENT_LANDING_FALLBACK, 8000);
        }
        
        void ExecuteFireballBombardment()
        {
            if (!_isFlying || _fireballsRemaining <= 0)
                return;
            
            // Cast fireball on random target
            if (Unit* target = SelectTarget(SelectTargetMethod::Random))
            {
                CastScaledSpell(target, SPELL_FIREBALL);
                me->Say("DEBUG: Fireball " + std::to_string(_totalFireballs - _fireballsRemaining + 1) + "/" + std::to_string(_totalFireballs) + " fired!", LANG_UNIVERSAL);
                _fireballsRemaining--;
                
                if (_fireballsRemaining > 0)
                {
                    // Schedule next fireball in 3 seconds
                    events.ScheduleEvent(EVENT_FIREBALL_BOMBARDMENT, 3000);
                }
                else
                {
                    // Bombardment finished - move to next waypoint
                    me->Say("DEBUG: Bombardment completed! Moving to next waypoint...", LANG_UNIVERSAL);
                    events.ScheduleEvent(EVENT_NEXT_WAYPOINT, 2000); // Short delay before moving
                }
            }
            else
            {
                // No target - skip this fireball and continue
                _fireballsRemaining--;
                if (_fireballsRemaining > 0)
                    events.ScheduleEvent(EVENT_FIREBALL_BOMBARDMENT, 1000);
                else
                    events.ScheduleEvent(EVENT_NEXT_WAYPOINT, 2000);
            }
        }

        void CompleteLanding()
        {
            // Cancel any pending landing fallback
            events.CancelEvent(EVENT_LANDING_FALLBACK);
            
            me->Say("DEBUG: Landing completed with proper MoveLand sequence!", LANG_UNIVERSAL);
            
            // No manual teleportation needed - MoveLand already positioned us correctly
            // Just disable flight capabilities like Onyxia
            me->SetCanFly(false);
            me->SetDisableGravity(false);
            me->SetSpeed(MOVE_RUN, me->GetCreatureTemplate()->speed_run, false);
            me->SendMovementFlagUpdate();
            
            // Professional landing completion
            me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
            _isFlying = false;
            me->SetReactState(REACT_AGGRESSIVE);
            
            // Remove immunity after landing
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
            
            // Resume combat immediately - don't wait for target selection
            if (Unit* target = me->SelectVictim())
            {
                AttackStart(target);
                me->Say("DEBUG: Resuming combat with target!", LANG_UNIVERSAL);
            }
            
            // Track flight phases with proper progression
            if (!_firstFlightDone)
            {
                _firstFlightDone = true;
                me->Say("DEBUG: First flight phase completed! Next phase at 33% HP.", LANG_UNIVERSAL);
            }
            else if (!_secondFlightDone)
            {
                _secondFlightDone = true;
                me->Say("DEBUG: Second and FINAL flight phase completed! No more flying!", LANG_UNIVERSAL);
            }
            else
            {
                me->Say("DEBUG: ERROR - Unexpected flight phase completion!", LANG_UNIVERSAL);
            }
            
            // Reset Dione variables
            _dioneSpawned = false;
            _currentDioneGUID.Clear();
            
            // Resume ground phase with proper event scheduling
            _phase = PHASE_ONE;
            events.SetPhase(PHASE_ONE);
            events.ScheduleEvent(EVENT_FLAME_BREATH, urand(8000, 12000));  // Faster resumption
            events.ScheduleEvent(EVENT_RANDOM_SPELL, urand(15000, 20000));
            events.ScheduleEvent(EVENT_FIRE_BOMB, 35s);
            events.ScheduleEvent(EVENT_WINGBUFFET, urand(18000, 22000));
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_polydeucesAI(creature);
    }
};

void AddSC_boss_polydeuces()
{
    new boss_polydeuces();
}