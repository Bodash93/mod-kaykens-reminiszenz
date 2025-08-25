/*
 * Kaykens Reminiszenz - Custom Raid Instance
 * Instance ID: 804
 */

#ifndef KAYKENS_REMINISZENZ_H_
#define KAYKENS_REMINISZENZ_H_

#include "CreatureScript.h"
#include "ScriptedCreature.h"
#include "InstanceScript.h"
#include "InstanceMapScript.h"

enum KRCreatures
{
    // Original Polydeuces NPCs
    NPC_POLYDEUCES              = 100004,
    NPC_DIONE                   = 100007,
    NPC_HEXENMEISTER            = 100005,
    
    // Kayken Gossip NPC
    NPC_KAYKEN                  = 100002,
    
    // Gorleax Boss and related NPCs
    NPC_GORLEAX                 = 5000013,
    NPC_TSUNAMI_ENTRANCE        = 500014,
    NPC_TSUNAMI_BACK            = 500015,
    NPC_TSUNAMI_LEFT            = 500016,
    NPC_TSUNAMI_RIGHT           = 500017,
    NPC_BRAND_PHASE1            = 500040,
    NPC_BRAND_PHASE2            = 500041,
    NPC_BRAND_PHASE3            = 500042,
    NPC_BRAND_PHASE4            = 500043,
    NPC_BRAND_PHASE5            = 500044,
    
    // Portalmeister Boss and related NPCs
    NPC_PORTALMEISTER           = 500011,
    NPC_PORTAL_ADD1             = 500012,
    NPC_PORTAL_ADD2             = 500013,
    NPC_PORTAL_ADD3             = 500018,
    NPC_HORDE_PORTAL            = 500034,
    NPC_HELLFIRE_SPAWNER        = 500035,
    NPC_HELLBEAST               = 500036,
    
    // Treppen Event NPCs
    NPC_TREPPEN_TRIGGER         = 500010,
    
    // Trash Mobs
    NPC_TRASH_DEFEATER          = 500000,  // Zerstörer
    NPC_TRASH_DEFENDER          = 500001,  // Verteidiger
    NPC_TRASH_MAGE              = 500002,  // Mage
    NPC_TRASH_ROUGE             = 500003,  // Schurke
    NPC_TRASH_WARLOCK           = 50005,   // Hexer
    NPC_TRASH_SHAMAN            = 50006    // Dunkelschamane
};

enum KRData
{
    DATA_POLYDEUCES             = 0,
    DATA_HEXENMEISTER_KILLED    = 1,
    MAX_KR_DATA                 = 2
};

enum KREvents
{
    // Polydeuces (1-25)
    EVENT_CHECK_WITCHES         = 1,
    EVENT_FLAME_BREATH          = 2,
    EVENT_RANDOM_SPELL          = 3,
    EVENT_FIRE_BOMB             = 4,
    EVENT_WINGBUFFET            = 5,  // Onyxia-style safe wingbuffet (replaces tail smash)
    EVENT_UNROOT                = 6,  // DEPRECATED: Was for tail sweep sequence
    EVENT_FLY_MOVEMENT          = 7,
    EVENT_FIREBALL_CAST         = 8,  // Old single fireball cast
    EVENT_SPAWN_DIONE           = 9,
    EVENT_CHECK_DIONE_DEATH     = 10,
    EVENT_WAKEUP_DELAYED        = 11,
    EVENT_TAKEOFF_SEQUENCE      = 18,
    EVENT_LANDING_FALLBACK      = 19,
    EVENT_FIREBALL_BOMBARDMENT  = 20, // New: 4-5 fireballs per waypoint
    EVENT_NEXT_WAYPOINT         = 21, // New: Move to next waypoint after bombardment

    // Dione (12-14)
    EVENT_DIONE_TRAP            = 12,
    EVENT_DIONE_FROSTBOLT1      = 13,
    EVENT_DIONE_FROSTBOLT2      = 14,

    // Hexenmeister (15-17)
    EVENT_SHADOW_BOLT           = 15,
    EVENT_CORRUPTION            = 16,
    EVENT_DARK_ENERGY_CAST      = 17,
    
    // Gorleax Boss Events (26-40)
    EVENT_GORLEAX_RANDOM_SPELL  = 26,
    EVENT_GORLEAX_STOMP         = 27,
    EVENT_GORLEAX_MELT          = 28,
    EVENT_GORLEAX_TSUNAMI       = 29,
    EVENT_GORLEAX_BRAND_SPELL   = 30,
    EVENT_GORLEAX_PHASE_CHECK   = 31,
    EVENT_TSUNAMI_MOVE          = 32,
    EVENT_TSUNAMI_DESPAWN       = 33,
    EVENT_BRAND_DESPAWN_CHECK   = 34,
    
    // Portalmeister Events (41-55)
    EVENT_PORTAL_SPAWN_ADDS     = 41,
    EVENT_PORTAL_SHADOWBOLT     = 42,
    EVENT_PORTAL_FEAR_CAST      = 43,
    EVENT_PORTAL_MOVE_PHASE     = 44,
    EVENT_PORTAL_HELLFIRE       = 45,
    EVENT_HELLFIRE_SPAWN        = 46,
    EVENT_HELLFIRE_DESPAWN      = 47,
    
    // Trash Mob Events (56-80)
    EVENT_TRASH_VANISH          = 56,
    EVENT_TRASH_BLIND           = 57,
    EVENT_TRASH_MORTAL_STRIKE   = 58,
    EVENT_TRASH_SUNDER_ARMOR    = 59,
    EVENT_TRASH_BLADESTORM      = 60,
    EVENT_TRASH_CHARGE          = 61,
    EVENT_TRASH_RANDOM_SPELL    = 62,
    EVENT_TRASH_OVERPOWER       = 63,
    EVENT_TRASH_DISARM          = 64,
    EVENT_TRASH_HELLFIRE        = 65,
    EVENT_TRASH_CURSE           = 66,
    EVENT_TRASH_FEAR            = 67,
    EVENT_TRASH_FROSTBOLT       = 68,
    EVENT_TRASH_BLIZZARD        = 69,
    EVENT_TRASH_POLYMORPH       = 70,
    EVENT_TRASH_ICE_BLOCK       = 71,
    EVENT_TRASH_HEALING_WAVE    = 72,
    EVENT_TRASH_RIPTIDE         = 73,
    EVENT_TRASH_HEX             = 74,
    EVENT_TRASH_BLOODLUST       = 75,
    EVENT_TRASH_MANA_RESET      = 76,
    
    // Treppen Event (81-85)
    EVENT_TREPPEN_WAYPOINT      = 81,
    EVENT_TREPPEN_DESPAWN       = 82,
    EVENT_HELLBEAST_SPAWN       = 83
};

enum KRPhases
{
    PHASE_PREPARATION           = 0,
    PHASE_ONE                   = 1,
    PHASE_TWO                   = 2
};

enum KRSpells
{
    // Polydeuces Spells
    SPELL_FIRE_BOMB             = 20475,
    SPELL_FIREBALL              = 28884,
    SPELL_FLAME_BREATH          = 23461,
    SPELL_BOLT_OF_MAGMA         = 18435,
    SPELL_LAVA_BLAST            = 178179, // NPC Lava Blast ability
    SPELL_MOLTEN_BLAST          = 19983,
    SPELL_WINGBUFFET            = 18500,  // Onyxia's wingbuffet for safe knockback
    SPELL_TAIL_SMASH            = 71077,  // DEPRECATED: Tail sweep causes map-wide knockback

    // Dione Spells (from original Lua script)
    SPELL_DIONE_TRAP            = 73539,  // AOE Trap 
    SPELL_DIONE_FROSTBOLT1      = 28479,  // Single target
    SPELL_DIONE_FROSTBOLT2      = 28478,  // Event reset frostbolt

    // Hexenmeister Spells
    SPELL_SHADOW_BOLT           = 12471,
    SPELL_CORRUPTION            = 11672,
    SPELL_DARK_ENERGY_VISUAL    = 74768,
    
    // Gorleax Boss Spells
    SPELL_GOR_WING_BUFFET       = 62546,
    SPELL_GOR_MORTAL_STRIKE     = 66725,
    SPELL_GOR_STOMP             = 60880,
    SPELL_GOR_MELT              = 62680,
    SPELL_TSUNAMI_VISUAL        = 57494,
    SPELL_TSUNAMI_AURA          = 57492,
    SPELL_BRAND_AURA            = 64561,
    
    // Portalmeister Spells
    SPELL_PORTAL_SHADOWBOLT     = 29317,
    SPELL_PORTAL_FEAR           = 41001,
    SPELL_PORTAL_DARK_ENERGY    = 74768,
    SPELL_HELLFIRE_AOE          = 33814,
    
    // Trash Mob Spells - Schurke
    SPELL_STEALTH               = 1784,
    SPELL_VANISH                = 29448,
    SPELL_BLIND                 = 34694,
    
    // Trash Mob Spells - Zerstörer
    SPELL_BLADESTORM            = 65947,
    SPELL_MORTAL_STRIKE         = 65926,
    SPELL_SUNDER_ARMOR          = 65936,
    SPELL_CHARGE                = 20616,
    SPELL_INTIMIDATING_SHOUT    = 65930,
    SPELL_BERSERKER_STANCE      = 2458,
    
    // Trash Mob Spells - Verteidiger
    SPELL_DISARM                = 65935,
    SPELL_OVERPOWER             = 65924,
    SPELL_DEFENSIVE_STANCE      = 7164,
    
    // Trash Mob Spells - Hexer
    SPELL_HELLFIRE              = 65816,
    SPELL_CURSE_OF_AGONY        = 65814,
    SPELL_FEAR                  = 65809,
    SPELL_SUMMON_IMP            = 67514,
    
    // Trash Mob Spells - Mage
    SPELL_BLIZZARD              = 41482,
    SPELL_FROSTBOLT             = 65807,
    SPELL_MAGE_SHIELD           = 12544,
    SPELL_POLYMORPH             = 65801,
    SPELL_ICE_BLOCK             = 65802,
    
    // Trash Mob Spells - Schamane
    SPELL_RIPTIDE               = 66053,
    SPELL_HEX                   = 66054,
    SPELL_EARTH_SHIELD          = 66063,
    SPELL_BLOODLUST             = 65980,
    SPELL_HEALING_WAVE          = 66055
};

enum KRMovementPoints
{
    POINT_AIR_PHASE             = 2,
    POINT_LAND_GROUND           = 4,
    POINT_WAYPOINT_BASE         = 10  // Waypoints use 10+
};

enum KRActions
{
    ACTION_HEXENMEISTER_DIED    = 1
};

// C++ String-based Yells (shared between scripts)
struct PolydeucesTexts
{
    // Polydeuces Yells
    static constexpr const char* SAY_AWAKEN = "Wer wagt es, meinen Schlummer zu stören?!";
    static constexpr const char* SAY_AGGRO = "Ihr werdet für euren Frevel büßen!";
    static constexpr const char* SAY_FLIGHT_PHASE = "Brennt in den Flammen der Vergeltung!";
    static constexpr const char* SAY_FLIGHT_DIONE = "Dione! Vernichte diese Eindringlinge!";
    static constexpr const char* SAY_LAND = "Genug gespielt! Ihr sterbt JETZT!";
    static constexpr const char* SAY_DEATH = "Mein... Meister... verzeiht mir...";
    
    // Hexenmeister Yells
    static constexpr const char* SAY_HEXEN_AGGRO_1 = "Für die dunklen Mächte!";
    static constexpr const char* SAY_HEXEN_AGGRO_2 = "Ihr werdet unseren Meister nicht stören!";
    static constexpr const char* SAY_HEXEN_AGGRO_3 = "Die Schatten werden euch verschlingen!";
    static constexpr const char* SAY_HEXEN_DEATH = "Meister... wacht auf...";
};

struct GorleaxTexts
{
    // Gorleax Boss Yells
    static constexpr const char* SAY_AGGRO = "Verunreinigungen im Fertigungsbereich wurden registriert. Führe Reinigungsprotokoll H-0815 durch";
    static constexpr const char* SAY_PHASE_TWO = "Protokoll H-0815 fehlgeschlagen. Initialisiere Protokoll E-420Y.";
    static constexpr const char* SAY_PHASE_THREE = "Protokoll E-420Y fehlgeschlagen. Initialisiere Protokoll D-0UK.";
    static constexpr const char* SAY_PHASE_FOUR = "Protokoll D-0UK fehlgeschlagen. Initialisiere Protokoll AC-7C.";
    static constexpr const char* SAY_PHASE_FIVE = "Protokoll AC-7C fehlgeschlagen. Initialisiere Protokoll KN-00B.";
    static constexpr const char* SAY_DEATH = "Prtkll.. KN-000000...";
};

struct PortalmeisterTexts
{
    // Portalmeister Yells
    static constexpr const char* SAY_SPAWN_ADDS = "Sehet die Horde des Schwarzfelses!";
};

struct TreppenEventTexts
{
    // Treppen Event Trigger
    static constexpr const char* SAY_TRIGGER_DEATH = "Das war ein Fehler...Sie kommen.";
};

#endif