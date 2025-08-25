-- Fix Polydeuces creature_template flags for proper ground/air movement
-- BOSS_MOB flag removed to prevent movement issues
-- Keep essential flags but allow normal movement transitions

UPDATE `creature_template` SET 
    `type_flags` = 76,      -- DO_NOT_PLAY_WOUND_ANIM + MORE_AUDIBLE + SPELL_ATTACKABLE (no BOSS_MOB)
    `speed_walk` = 2.5,     -- Moderate walking speed for ground phase
    `speed_run` = 2.0       -- Moderate running speed (NO speed_flight to prevent initial flying)
WHERE `entry` = 100004;

-- Also update Hexenmeister for consistency (they support the boss)
UPDATE `creature_template` SET 
    `type_flags` = 68,      -- DO_NOT_PLAY_WOUND_ANIM + MORE_AUDIBLE + SPELL_ATTACKABLE (no BOSS_MOB)
    `speed_walk` = 1.2,     -- Slightly faster than default
    `speed_run` = 1.4       -- Slightly faster than default
WHERE `entry` = 100005;

-- Update Dione (add) with proper flags - Remove BOSS_MOB for reliable spawning
UPDATE `creature_template` SET 
    `type_flags` = 8,       -- DO_NOT_PLAY_WOUND_ANIM only (no BOSS_MOB to prevent spawn issues)
    `speed_walk` = 1.5,
    `speed_run` = 1.5,
    `speed_flight` = 2.0    -- Normal flight speed
WHERE `entry` = 100007;