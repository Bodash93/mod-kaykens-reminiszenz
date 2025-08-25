/*
 * Kayken NPC - Kaykens Reminiszenz
 * Converted from Lua to C++ - Gossip NPC with teleport and GM functions
 */

#include "kaykens_reminiszenz.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "QuestDef.h"
#include "TaskScheduler.h"

// Kayken uses database-driven gossip menus (60000-60007)
// Only Menu 60007 requires script intervention for teleportation

// Visual Effects for dramatic teleportation
enum KaykenSpells
{
    SPELL_VOID_PORTAL_VISUAL    = 33569,    // Dark portal visual effect
    SPELL_SHADOWMOURNE_VISUAL   = 72521,    // Shadow visual effect  
    SPELL_TELEPORT_EFFECT       = 64446     // Generic teleport visual
};

class npc_kayken : public CreatureScript
{
public:
    npc_kayken() : CreatureScript("npc_kayken") { }

    struct npc_kaykenAI : public ScriptedAI
    {
        npc_kaykenAI(Creature* creature) : ScriptedAI(creature) { }

        TaskScheduler _scheduler;

        void PerformDramaticTeleport(Player* player)
        {
            // Stage 1: Initial shadow gathering - longer duration
            ChatHandler(player->GetSession()).SendSysMessage("|cffFF6B35Kayken hebt die Hände... Schatten beginnen sich um ihn zu sammeln...|r");
            me->CastSpell(me, SPELL_SHADOWMOURNE_VISUAL, true);
            player->CastSpell(player, SPELL_SHADOWMOURNE_VISUAL, true);
            player->CastSpell(player, SPELL_VOID_PORTAL_VISUAL, true);
            
            _scheduler.Schedule(2s, [this, player](TaskContext /*context*/)
            {
                // Refresh shadow effect to prevent fade
                me->CastSpell(me, SPELL_SHADOWMOURNE_VISUAL, true);
                
                // Stage 2: Portal opening
                ChatHandler(player->GetSession()).SendSysMessage("|cffFF6B35Die Luft reißt auf... Ein Portal zur Reminiszenz öffnet sich!|r");
                me->CastSpell(me, SPELL_VOID_PORTAL_VISUAL, true);
                
                _scheduler.Schedule(2s, [this, player](TaskContext /*context*/)
                {
                    // Refresh both effects
                    me->CastSpell(me, SPELL_SHADOWMOURNE_VISUAL, true);
                    me->CastSpell(me, SPELL_VOID_PORTAL_VISUAL, true);
                    player->CastSpell(player, SPELL_SHADOWMOURNE_VISUAL, true);
                    player->CastSpell(player, SPELL_VOID_PORTAL_VISUAL, true);
                    
                    // Stage 3: Final teleportation
                    ChatHandler(player->GetSession()).SendSysMessage("|cffFF6B35Die Realität verschwimmt... Ihr werdet in Kaykens Erinnerungen gezogen!|r");
                    player->CastSpell(player, SPELL_TELEPORT_EFFECT, true);
                    
                    _scheduler.Schedule(1s, [this, player](TaskContext /*context*/)
                    {
                        // Final teleport with effect cleanup
                        player->RemoveAurasDueToSpell(SPELL_SHADOWMOURNE_VISUAL);
                        player->RemoveAurasDueToSpell(SPELL_VOID_PORTAL_VISUAL);
                        player->TeleportTo(804, -6557.960449f, -1955.508301f, 255.098969f, 0.0f);
                        
                        // Clean up Kayken's visual effects after teleport
                        me->RemoveAurasDueToSpell(SPELL_SHADOWMOURNE_VISUAL);
                        me->RemoveAurasDueToSpell(SPELL_VOID_PORTAL_VISUAL);
                    });
                });
            });
        }

        void UpdateAI(uint32 diff) override
        {
            _scheduler.Update(diff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kaykenAI(creature);
    }

    // Remove OnGossipHello to let the database handle gossip menu loading automatically

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        uint32 currentMenuId = player->PlayerTalkClass->GetGossipMenu().GetMenuId();
        
        // ONLY handle the final teleport - Menu 60007 is the end of the chain
        if (currentMenuId == 60006)
        {           
            CloseGossipMenuFor(player);
            
            // Get the AI instance and trigger dramatic teleport sequence
            if (npc_kaykenAI* kaykenAI = dynamic_cast<npc_kaykenAI*>(creature->AI()))
            {
                kaykenAI->PerformDramaticTeleport(player);
            }
            else
            {
                // Fallback if AI is not available
                ChatHandler(player->GetSession()).SendSysMessage("|cffFF6B35Kayken beginnt eine dunkle Beschwörung... Die Realität verschwimmt um Euch herum...|r");
                player->TeleportTo(804, -6557.960449f, -1955.508301f, 255.098969f, 0.0f);
            }
            return true;
        }
        
        // Handle quest interactions (action >= GOSSIP_ACTION_INFO_DEF means quest)
        if (action >= GOSSIP_ACTION_INFO_DEF)
        {
            uint32 questId = action - GOSSIP_ACTION_INFO_DEF;
            if (Quest const* quest = sObjectMgr->GetQuestTemplate(questId))
            {
                if (player->GetQuestStatus(questId) == QUEST_STATUS_NONE && player->CanAddQuest(quest, true))
                {
                    player->PlayerTalkClass->SendQuestGiverQuestDetails(quest, creature->GetGUID(), true);
                }
                else if (player->GetQuestStatus(questId) == QUEST_STATUS_INCOMPLETE && player->CanCompleteQuest(questId))
                {
                    player->PlayerTalkClass->SendQuestGiverRequestItems(quest, creature->GetGUID(), player->CanCompleteRepeatableQuest(quest), true);
                }
            }
            return true;
        }
        
        // For ALL other gossip interactions: Let the database handle it normally
        // DO NOT return false here as it causes auto-navigation through ActionMenuIDs
        return false;
    }

    // Quest handling callbacks - ensure quest functionality is preserved
    bool OnQuestAccept(Player* /*player*/, Creature* /*creature*/, Quest const* /*quest*/) override
    {
        // Custom quest accept logic can be added here if needed
        return false; // Let default quest system handle it
    }

    bool OnQuestComplete(Player* /*player*/, Creature* /*creature*/, Quest const* /*quest*/) override
    {
        // Custom quest completion logic can be added here if needed  
        return false; // Let default quest system handle it
    }

    bool OnQuestReward(Player* /*player*/, Creature* /*creature*/, Quest const* /*quest*/, uint32 /*opt*/) override
    {
        // Custom quest reward logic can be added here if needed
        return false; // Let default quest system handle it
    }
};

void AddSC_npc_kayken()
{
    new npc_kayken();
}