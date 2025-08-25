/*
 * Trash Mobs - Kaykens Reminiszenz
 * Converted from Lua to C++ - 6 different trash mob classes with unique abilities
 */

#include "kaykens_reminiszenz.h"

// ===========================================
// Schurke (Rouge) - Stealth, Vanish, Blind
// ===========================================
class npc_trash_rouge : public CreatureScript
{
public:
    npc_trash_rouge() : CreatureScript("npc_trash_rouge") { }

    struct npc_trash_rougeAI : public ScriptedAI
    {
        npc_trash_rougeAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
            DoCastSelf(SPELL_STEALTH);
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_TRASH_VANISH, urand(30000, 60000));
            events.ScheduleEvent(EVENT_TRASH_BLIND, urand(10000, 20000));
        }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            ScriptedAI::EnterEvadeMode(EVADE_REASON_OTHER);
            events.ScheduleEvent(EVENT_TRASH_VANISH, 100); // Re-stealth when out of combat
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TRASH_VANISH:
                        DoCastSelf(SPELL_VANISH);
                        events.Repeat(Milliseconds(urand(30000, 60000)));
                        break;
                    case EVENT_TRASH_BLIND:
                        if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, 30.0f, true))
                            DoCast(target, SPELL_BLIND);
                        events.Repeat(Milliseconds(urand(10000, 20000)));
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustReachedHome() override
        {
            DoCastSelf(SPELL_STEALTH);
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trash_rougeAI(creature);
    }
};

// ========================================================
// Zerstörer (Defeater) - Bladestorm, Charge, Mortal Strike
// ========================================================
class npc_trash_defeater : public CreatureScript
{
public:
    npc_trash_defeater() : CreatureScript("npc_trash_defeater") { }

    struct npc_trash_defeaterAI : public ScriptedAI
    {
        npc_trash_defeaterAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
            DoCastSelf(SPELL_INTIMIDATING_SHOUT);
            DoCastSelf(SPELL_BERSERKER_STANCE);
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_TRASH_RANDOM_SPELL, 4000);
            events.ScheduleEvent(EVENT_TRASH_CHARGE, 100);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TRASH_CHARGE:
                        if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, 50.0f, true))
                        {
                            // Only charge if target is at least 5 yards away
                            if (me->GetDistance2d(target) >= 5.0f)
                            {
                                DoCast(target, SPELL_CHARGE, true);
                                // Switch threat to charged target without clearing all threat
                                me->GetThreatMgr().AddThreat(target, 10000.0f);
                            }
                        }
                        events.Repeat(Milliseconds(10000));
                        break;
                    case EVENT_TRASH_RANDOM_SPELL:
                        CastRandomSpell();
                        events.Repeat(Milliseconds(4000));
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustReachedHome() override
        {
            DoCastSelf(SPELL_BERSERKER_STANCE);
        }

    private:
        EventMap events;

        void CastRandomSpell()
        {
            uint32 randomSpell = urand(1, 100);
            if (randomSpell <= 25)
                events.ScheduleEvent(EVENT_TRASH_MORTAL_STRIKE, 1000);
            else if (randomSpell <= 89)
                events.ScheduleEvent(EVENT_TRASH_SUNDER_ARMOR, 1000);
            else
                events.ScheduleEvent(EVENT_TRASH_BLADESTORM, 1000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trash_defeaterAI(creature);
    }
};

// ====================================================
// Verteidiger (Defender) - Disarm, Overpower, Charge
// ====================================================
class npc_trash_defender : public CreatureScript
{
public:
    npc_trash_defender() : CreatureScript("npc_trash_defender") { }

    struct npc_trash_defenderAI : public ScriptedAI
    {
        npc_trash_defenderAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
            DoCastSelf(SPELL_INTIMIDATING_SHOUT);
            DoCastSelf(SPELL_DEFENSIVE_STANCE);
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_TRASH_RANDOM_SPELL, 6000);
            events.ScheduleEvent(EVENT_TRASH_CHARGE, 100);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TRASH_CHARGE:
                        if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, 50.0f, true))
                        {
                            // Only charge if target is at least 5 yards away
                            if (me->GetDistance2d(target) >= 5.0f)
                            {
                                DoCast(target, SPELL_CHARGE, true);
                                // Switch threat to charged target without clearing all threat
                                me->GetThreatMgr().AddThreat(target, 10000.0f);
                            }
                        }
                        events.Repeat(Milliseconds(10000));
                        break;
                    case EVENT_TRASH_RANDOM_SPELL:
                        CastRandomSpell();
                        events.Repeat(Milliseconds(6000));
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustReachedHome() override
        {
            DoCastSelf(SPELL_DEFENSIVE_STANCE);
        }

    private:
        EventMap events;

        void CastRandomSpell()
        {
            uint32 randomSpell = urand(1, 3);
            if (randomSpell == 1)
                events.ScheduleEvent(EVENT_TRASH_MORTAL_STRIKE, 1000);
            else if (randomSpell == 2)
                events.ScheduleEvent(EVENT_TRASH_OVERPOWER, 1000);
            else
                events.ScheduleEvent(EVENT_TRASH_DISARM, 1000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trash_defenderAI(creature);
    }
};

// =====================================================
// Hexer (Warlock) - Hellfire, Fear, Curse, Shadow Bolt
// =====================================================
class npc_trash_warlock : public CreatureScript
{
public:
    npc_trash_warlock() : CreatureScript("npc_trash_warlock") { }

    struct npc_trash_warlockAI : public ScriptedAI
    {
        npc_trash_warlockAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_TRASH_RANDOM_SPELL, 6000);
            events.ScheduleEvent(EVENT_SHADOW_BOLT, 4000);
            events.ScheduleEvent(EVENT_TRASH_MANA_RESET, 1000);
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
                    case EVENT_SHADOW_BOLT:
                        if (Unit* target = me->GetVictim())
                        {
                            // Cast corruption on random target first
                            if (Unit* randomTarget = SelectTarget(SelectTargetMethod::Random, 0, 50.0f, true))
                                DoCast(randomTarget, SPELL_CORRUPTION);
                            DoCast(target, SPELL_SHADOW_BOLT);
                        }
                        events.Repeat(Milliseconds(4000));
                        break;
                    case EVENT_TRASH_RANDOM_SPELL:
                        CastRandomSpell();
                        events.Repeat(Milliseconds(6000));
                        break;
                    case EVENT_TRASH_MANA_RESET:
                        if (me->GetPowerPct(POWER_MANA) <= 20)
                            me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                        events.Repeat(Milliseconds(1000));
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap events;

        void CastRandomSpell()
        {
            uint32 randomSpell = urand(1, 3);
            if (randomSpell == 1)
                events.ScheduleEvent(EVENT_TRASH_HELLFIRE, 1000);
            else if (randomSpell == 2)
                events.ScheduleEvent(EVENT_TRASH_FEAR, 1000);
            else
                events.ScheduleEvent(EVENT_TRASH_CURSE, 1000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trash_warlockAI(creature);
    }
};

// ======================================================
// Mage - Blizzard, Frostbolt, Polymorph, Ice Block
// ======================================================
class npc_trash_mage : public CreatureScript
{
public:
    npc_trash_mage() : CreatureScript("npc_trash_mage") { }

    struct npc_trash_mageAI : public ScriptedAI
    {
        npc_trash_mageAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
            DoCastSelf(SPELL_MAGE_SHIELD);
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_TRASH_RANDOM_SPELL, 7000);
            events.ScheduleEvent(EVENT_TRASH_FROSTBOLT, 5000);
            events.ScheduleEvent(EVENT_TRASH_ICE_BLOCK, 1000); // HP check
            events.ScheduleEvent(EVENT_TRASH_MANA_RESET, 1000);
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
                    case EVENT_TRASH_FROSTBOLT:
                        DoCastVictim(SPELL_FROSTBOLT);
                        events.Repeat(Milliseconds(5000));
                        break;
                    case EVENT_TRASH_RANDOM_SPELL:
                        CastRandomSpell();
                        events.Repeat(Milliseconds(7000));
                        break;
                    case EVENT_TRASH_ICE_BLOCK:
                        if (me->HealthBelowPct(10))
                        {
                            events.Reset();
                            DoCastSelf(SPELL_ICE_BLOCK);
                            events.ScheduleEvent(EVENT_TRASH_RANDOM_SPELL, 10000); // Resume after ice block
                        }
                        else
                            events.Repeat(Milliseconds(1000));
                        break;
                    case EVENT_TRASH_MANA_RESET:
                        if (me->GetPowerPct(POWER_MANA) <= 20)
                            me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                        events.Repeat(Milliseconds(1000));
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustReachedHome() override
        {
            DoCastSelf(SPELL_MAGE_SHIELD);
        }

    private:
        EventMap events;

        void CastRandomSpell()
        {
            uint32 randomSpell = urand(1, 2);
            if (randomSpell == 1)
                events.ScheduleEvent(EVENT_TRASH_BLIZZARD, 1000);
            else
                events.ScheduleEvent(EVENT_TRASH_POLYMORPH, 1000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trash_mageAI(creature);
    }
};

// ========================================================
// Dunkelschamane (Dark Shaman) - Healer with offensive spells
// ========================================================
class npc_trash_shaman : public CreatureScript
{
public:
    npc_trash_shaman() : CreatureScript("npc_trash_shaman") { }

    struct npc_trash_shamanAI : public ScriptedAI
    {
        npc_trash_shamanAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
            DoCastSelf(SPELL_EARTH_SHIELD);
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            me->SetReactState(REACT_PASSIVE); // Stay back and heal
            events.ScheduleEvent(EVENT_TRASH_BLOODLUST, 15000);
            events.ScheduleEvent(EVENT_TRASH_RANDOM_SPELL, 8000);
        }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            ScriptedAI::EnterEvadeMode(EVADE_REASON_OTHER);
            me->SetReactState(REACT_AGGRESSIVE);
            events.ScheduleEvent(EVENT_TRASH_RANDOM_SPELL, 3000); // Reset earth shield
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TRASH_BLOODLUST:
                        DoCastSelf(SPELL_BLOODLUST);
                        break;
                    case EVENT_TRASH_RANDOM_SPELL:
                        CastRandomSpell();
                        events.Repeat(Milliseconds(8000));
                        break;
                }
            }
        }

        void JustReachedHome() override
        {
            me->SetReactState(REACT_AGGRESSIVE);
            DoCastSelf(SPELL_EARTH_SHIELD);
        }

    private:
        EventMap events;

        void CastRandomSpell()
        {
            // Priority: Healing > Offensive
            std::list<Creature*> allies;
            me->GetCreatureListWithEntryInGrid(allies, NPC_TRASH_MAGE, 35.0f);
            
            std::list<Creature*> moreAllies;
            me->GetCreatureListWithEntryInGrid(moreAllies, NPC_TRASH_DEFEATER, 35.0f);
            allies.splice(allies.end(), moreAllies);
            
            me->GetCreatureListWithEntryInGrid(moreAllies, NPC_TRASH_DEFENDER, 35.0f);
            allies.splice(allies.end(), moreAllies);
            
            me->GetCreatureListWithEntryInGrid(moreAllies, NPC_TRASH_WARLOCK, 35.0f);
            allies.splice(allies.end(), moreAllies);
            
            me->GetCreatureListWithEntryInGrid(moreAllies, NPC_TRASH_ROUGE, 35.0f);
            allies.splice(allies.end(), moreAllies);
            
            Creature* woundedAlly = nullptr;
            for (Creature* ally : allies)
            {
                if (ally->IsAlive() && ally->IsInCombat() && ally->HealthBelowPct(70))
                {
                    uint32 allyEntry = ally->GetEntry();
                    if (allyEntry == NPC_TRASH_MAGE || allyEntry == NPC_TRASH_DEFEATER ||
                        allyEntry == NPC_TRASH_DEFENDER || allyEntry == NPC_TRASH_WARLOCK ||
                        allyEntry == NPC_TRASH_ROUGE)
                    {
                        woundedAlly = ally;
                        break;
                    }
                }
            }

            if (woundedAlly)
            {
                if (woundedAlly->HealthBelowPct(70))
                    DoCast(woundedAlly, SPELL_HEALING_WAVE);
                else if (woundedAlly->HealthBelowPct(90))
                    DoCast(woundedAlly, SPELL_RIPTIDE);
            }
            else
            {
                // No wounded allies, cast offensive spell
                if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, 50.0f, true))
                    DoCast(target, SPELL_HEX);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trash_shamanAI(creature);
    }
};

// Event handlers for spell execution (needed for the event system)
class npc_trash_spell_handler : public CreatureScript
{
public:
    npc_trash_spell_handler() : CreatureScript("npc_trash_spell_handler") { }

    struct npc_trash_spell_handlerAI : public ScriptedAI
    {
        npc_trash_spell_handlerAI(Creature* creature) : ScriptedAI(creature) { }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TRASH_MORTAL_STRIKE:
                        if (Unit* victim = me->GetVictim())
                            DoCast(victim, SPELL_MORTAL_STRIKE);
                        break;
                    case EVENT_TRASH_SUNDER_ARMOR:
                        if (Unit* victim = me->GetVictim())
                            DoCast(victim, SPELL_SUNDER_ARMOR);
                        break;
                    case EVENT_TRASH_BLADESTORM:
                        if (Unit* victim = me->GetVictim())
                            DoCast(victim, SPELL_BLADESTORM);
                        break;
                    case EVENT_TRASH_OVERPOWER:
                        if (Unit* victim = me->GetVictim())
                            DoCast(victim, SPELL_OVERPOWER);
                        break;
                    case EVENT_TRASH_DISARM:
                        if (Unit* victim = me->GetVictim())
                            DoCast(victim, SPELL_DISARM);
                        break;
                    case EVENT_TRASH_HELLFIRE:
                        DoCastSelf(SPELL_HELLFIRE);
                        break;
                    case EVENT_TRASH_FEAR:
                        if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, 50.0f, true))
                            DoCast(target, SPELL_FEAR);
                        break;
                    case EVENT_TRASH_CURSE:
                        if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, 50.0f, true))
                            DoCast(target, SPELL_CURSE_OF_AGONY);
                        break;
                    case EVENT_TRASH_BLIZZARD:
                        if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, 50.0f, true))
                            DoCast(target, SPELL_BLIZZARD);
                        break;
                    case EVENT_TRASH_POLYMORPH:
                        if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, 50.0f, true))
                            DoCast(target, SPELL_POLYMORPH);
                        break;
                }
            }
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trash_spell_handlerAI(creature);
    }
};

void AddSC_npc_trash_mobs()
{
    new npc_trash_rouge();
    new npc_trash_defeater();
    new npc_trash_defender();
    new npc_trash_warlock();
    new npc_trash_mage();
    new npc_trash_shaman();
    new npc_trash_spell_handler();
}