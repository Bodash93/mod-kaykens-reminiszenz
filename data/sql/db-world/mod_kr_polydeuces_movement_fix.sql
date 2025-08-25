-- Fix Polydeuces flight mechanics
-- Based on Onyxia's movement configuration (ID 10184)
-- Ground=1 (can move on ground), Flight=1 (can fly when enabled), others=0

DELETE FROM `creature_template_movement` WHERE `CreatureId` = 100004;
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Chase`, `Random`, `InteractionPauseTimer`) VALUES
(100004, 1, 0, 1, 0, 0, 0, NULL);