-- Kaykens Reminiszenz - Converted Old SQL NPCs to Modern AzerothCore Format
-- All NPCs from old_sql folder converted to modern creature_template structure
-- Original NPCs from legacy server format (creature_names/creature_proto) → modern format

-- =============================================
-- TRASH MOBS (Main ones - already exist, updating for completeness)
-- =============================================

-- Zerstörer des Schwarzfels (Entry: 50000) - bereits konvertiert, aber mit korrekten alten Werten
DELETE FROM `creature_template` WHERE `entry` = 50000;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(50000, 0, 0, 0, 0, 0, 'Zerstörer des Schwarzfels', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1, 1, 0, 2.5, 1800, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1500, 2500, 'SmartAI', 0, 1, 4, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_defeater', 12340);

-- Verteidiger des Schwarzfels (Entry: 50001)
DELETE FROM `creature_template` WHERE `entry` = 50001;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(50001, 0, 0, 0, 0, 0, 'Verteidiger des Schwarzfels', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1, 0, 0, 2.2, 1800, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1500, 2500, 'SmartAI', 0, 1, 4, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_defender', 12340);

-- Magielord des Schwarzfels (Entry: 50002)  
DELETE FROM `creature_template` WHERE `entry` = 50002;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(50002, 0, 0, 0, 0, 0, 'Magielord des Schwarzfels', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1, 0, 0, 2.0, 1800, 2000, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1200, 2000, 'SmartAI', 0, 1, 4, 10, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_mage', 12340);

-- Schurke des Schwarzfels (Entry: 50003) - bereits konvertiert, aktualisiere Name
DELETE FROM `creature_template` WHERE `entry` = 50003;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(50003, 0, 0, 0, 0, 0, 'Schurke des Schwarzfels', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1, 1, 0, 2.5, 1800, 1800, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1800, 2800, 'SmartAI', 0, 1, 4, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_rouge', 12340);

-- Kommandant des Schwarzfels (Entry: 50004)
DELETE FROM `creature_template` WHERE `entry` = 50004;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(50004, 0, 0, 0, 0, 0, 'Kommandant des Schwarzfels', '', '', 0, 81, 81, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1, 1, 0, 3.0, 1800, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 2500, 4000, 'SmartAI', 0, 1, 5, 1, 1.2, 0, 0, 1, 0, 0, 0, 'npc_trash_defeater', 12340);

-- Hexer des Schwarzfels (Entry: 50005) - bereits konvertiert als Dunkelmagier, korrigiere Namen
DELETE FROM `creature_template` WHERE `entry` = 50005;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(50005, 0, 0, 0, 0, 0, 'Hexer des Schwarzfels', '', '', 0, 78, 78, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1, 1, 0, 2.0, 2200, 2200, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1200, 2000, 'SmartAI', 0, 1, 3, 8, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_warlock', 12340);

-- Dunkelschamane des Schwarzfels (Entry: 50006) - bereits konvertiert, korrigiere maxlevel Bug aus alter SQL
DELETE FROM `creature_template` WHERE `entry` = 50006;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(50006, 0, 0, 0, 0, 0, 'Dunkelschamane des Schwarzfels', 'Heiler', '', 0, 81, 81, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1, 1, 0, 1.8, 2500, 2500, 1, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1000, 1800, 'SmartAI', 0, 1, 4, 10, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_shaman', 12340);

-- Wundheiler des Schwarzfels (Entry: 50007)
DELETE FROM `creature_template` WHERE `entry` = 50007;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(50007, 0, 0, 0, 0, 0, 'Wundheiler des Schwarzfels', 'Sanitäter', '', 0, 81, 81, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1, 1, 0, 1.5, 1800, 2000, 1, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1500, 2500, 'SmartAI', 0, 1, 4, 12, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_shaman', 12340);

-- Versklavte Brutwache (Entry: 50008)
DELETE FROM `creature_template` WHERE `entry` = 50008;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(50008, 0, 0, 0, 0, 0, 'Versklavte Brutwache', '', '', 0, 82, 82, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1, 1, 0, 4.0, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 3000, 5000, 'SmartAI', 0, 1, 8, 5, 1.5, 0, 0, 1, 0, 0, 0, '', 12340);

-- Versklavte Todeskralle (Entry: 50009) 
DELETE FROM `creature_template` WHERE `entry` = 50009;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(50009, 0, 0, 0, 0, 0, 'Versklavte Todeskralle', '', '', 0, 82, 82, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1.5, 1, 0, 5.0, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4000, 6000, 'SmartAI', 0, 1, 10, 1, 2, 0, 0, 1, 0, 0, 0, '', 12340);

-- =============================================  
-- BOSS NPCS (Entry: 500010-500018)
-- =============================================

-- Verräter des Schwarzfels - korrigiere Entry ID conflict (war 500010)
-- Neue Entry: 500050 um Konflikt mit Treppen Trigger zu vermeiden
DELETE FROM `creature_template` WHERE `entry` = 500050;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(500050, 0, 0, 0, 0, 0, 'Verräter des Schwarzfels', 'Renegat', '', 0, 81, 81, 2, 14, 0, 1, 1.14286, 1, 1, 20, 1, 1, 0, 3.5, 1800, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 2500, 4000, 'SmartAI', 0, 1, 5, 1, 1.2, 0, 0, 1, 0, 0, 0, 'npc_trash_defeater', 12340);

-- Gorleax Boss (500013) - bereits vorhanden, aber mit korrekten Werten aus alten SQL
UPDATE `creature_template` SET 
    `name` = 'Gorleax',
    `subname` = 'Der Brenner',
    `minlevel` = 83,
    `maxlevel` = 83,
    `HealthModifier` = 12,
    `rank` = 1,
    `mingold` = 25000,
    `maxgold` = 35000
WHERE `entry` = 5000013;

-- Portalmeister (500011) - bereits vorhanden, korrigiere Namen und Stats 
UPDATE `creature_template` SET
    `name` = 'Portalmeister des Schwarzfels',
    `minlevel` = 81,
    `maxlevel` = 81, 
    `HealthModifier` = 8,
    `ManaModifier` = 5
WHERE `entry` = 500011;

-- Peon des Schwarzfels (500012) - bereits als Portal Add definiert, korrigiere Namen
UPDATE `creature_template` SET
    `name` = 'Peon des Schwarzfels',
    `minlevel` = 80,
    `maxlevel` = 80,
    `HealthModifier` = 2,
    `type` = 7
WHERE `entry` = 500012;

-- =============================================
-- CREATURE TEMPLATE MODEL ENTRIES (Display IDs)  
-- =============================================

-- Delete existing entries to avoid conflicts
DELETE FROM `creature_template_model` WHERE `CreatureID` BETWEEN 50000 AND 50009 OR `CreatureID` = 500050;

-- Insert Display ID mappings from old SQL files
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
-- Trash Mobs
(50000, 0, 6049, 1, 1, 12340),   -- Zerstörer des Schwarzfels
(50001, 0, 7025, 1, 1, 12340),   -- Verteidiger des Schwarzfels
(50002, 0, 6046, 1, 1, 12340),   -- Magielord des Schwarzfels
(50003, 0, 9691, 1, 1, 12340),   -- Schurke des Schwarzfels
(50004, 0, 9696, 1, 1, 12340),   -- Kommandant des Schwarzfels
(50005, 0, 16925, 1, 1, 12340),  -- Hexer des Schwarzfels
(50006, 0, 9849, 1, 1, 12340),   -- Dunkelschamane des Schwarzfels
(50007, 0, 9690, 1, 1, 12340),   -- Wundheiler des Schwarzfels
(50008, 0, 14308, 1, 1, 12340),  -- Versklavte Brutwache
(50009, 0, 14544, 1.5, 1, 12340), -- Versklavte Todeskralle (scaled up)
-- Boss NPCs  
(500050, 0, 9686, 1, 1, 12340),  -- Verräter des Schwarzfels
(5000013, 0, 9189, 1.1, 1, 12340), -- Gorleax (scaled up for boss)
(500011, 0, 6048, 1, 1, 12340),   -- Portalmeister des Schwarzfels  
(500012, 0, 6033, 1, 1, 12340);   -- Peon des Schwarzfels

-- =============================================
-- CLEANUP AND NOTES
-- =============================================

-- Note: All NPCs now have proper modern AzerothCore structure
-- Display IDs preserved from original old_sql files
-- Stats balanced for level 78-83 ICC-level content
-- Script assignments link to converted C++ implementations where available
-- Entry IDs: 50000-50009 for main trash, 500050 for Verräter (conflict resolution)