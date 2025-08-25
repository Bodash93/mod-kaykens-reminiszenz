-- Kaykens Reminiszenz - New Creatures from Lua conversion
-- Creature templates for all converted Lua scripts

-- =============================================
-- Kayken Gossip NPC (already exists, just script assignment)
-- =============================================
UPDATE `creature_template` SET `ScriptName` = 'npc_kayken' WHERE `entry` = 100002;

-- =============================================
-- Gorleax Boss and related NPCs
-- =============================================

-- Gorleax Boss
DELETE FROM `creature_template` WHERE `entry` = 5000013;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(5000013, 0, 0, 0, 0, 0, 21635, 0, 0, 0, 'Gorleax', 'Reinigungsprotokoll', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 3, 0, 4.5, 2000, 2000, 1, 1, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 2, 76, 0, 0, 0, 0, 0, 25000, 35000, 'SmartAI', 0, 1, 25, 10, 1, 0, 0, 1, 0, 0, 1, 'boss_gorleax', 12340);

-- Tsunami NPCs
DELETE FROM `creature_template` WHERE `entry` IN (500014, 500015, 500016, 500017);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(500014, 0, 0, 0, 0, 0, 1825, 0, 0, 0, 'Tsunami (Entrance)', '', '', 0, 80, 80, 2, 14, 0, 1, 1, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554432, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_gorleax_tsunami', 12340),
(500015, 0, 0, 0, 0, 0, 1825, 0, 0, 0, 'Tsunami (Back)', '', '', 0, 80, 80, 2, 14, 0, 1, 1, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554432, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_gorleax_tsunami', 12340),
(500016, 0, 0, 0, 0, 0, 1825, 0, 0, 0, 'Tsunami (Left)', '', '', 0, 80, 80, 2, 14, 0, 1, 1, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554432, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_gorleax_tsunami', 12340),
(500017, 0, 0, 0, 0, 0, 1825, 0, 0, 0, 'Tsunami (Right)', '', '', 0, 80, 80, 2, 14, 0, 1, 1, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554432, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_gorleax_tsunami', 12340);

-- Brand NPCs
DELETE FROM `creature_template` WHERE `entry` IN (500040, 500041, 500042, 500043, 500044);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(500040, 0, 0, 0, 0, 0, 1825, 0, 0, 0, 'Brand Phase 1', '', '', 0, 80, 80, 2, 14, 0, 0, 0, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554688, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_gorleax_brand', 12340),
(500041, 0, 0, 0, 0, 0, 1825, 0, 0, 0, 'Brand Phase 2', '', '', 0, 80, 80, 2, 14, 0, 0, 0, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554688, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_gorleax_brand', 12340),
(500042, 0, 0, 0, 0, 0, 1825, 0, 0, 0, 'Brand Phase 3', '', '', 0, 80, 80, 2, 14, 0, 0, 0, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554688, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_gorleax_brand', 12340),
(500043, 0, 0, 0, 0, 0, 1825, 0, 0, 0, 'Brand Phase 4', '', '', 0, 80, 80, 2, 14, 0, 0, 0, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554688, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_gorleax_brand', 12340),
(500044, 0, 0, 0, 0, 0, 1825, 0, 0, 0, 'Brand Phase 5', '', '', 0, 80, 80, 2, 14, 0, 0, 0, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554688, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_gorleax_brand', 12340);

-- =============================================
-- Portalmeister Boss and related NPCs
-- =============================================

-- Portalmeister Boss
DELETE FROM `creature_template` WHERE `entry` = 500011;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(500011, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Portalmeister', 'Horde des Schwarzfelses', '', 0, 82, 82, 2, 14, 0, 1, 1.14286, 1, 3, 0, 3.8, 2000, 2000, 1, 1, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 7, 72, 0, 0, 0, 0, 0, 20000, 30000, 'SmartAI', 0, 1, 20, 15, 1, 0, 0, 1, 0, 0, 1, 'boss_portalmeister', 12340);

-- Portal Adds
DELETE FROM `creature_template` WHERE `entry` IN (500012, 500013, 500018);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(500012, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Portal Add 1', '', '', 0, 80, 80, 2, 14, 0, 1, 1, 1, 1, 0, 2, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1000, 2000, 'SmartAI', 0, 1, 3, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_treppen_add', 12340),
(500013, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Portal Add 2', '', '', 0, 80, 80, 2, 14, 0, 1, 1, 1, 1, 0, 2, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1000, 2000, 'SmartAI', 0, 1, 3, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_treppen_add', 12340),
(500018, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Portal Add 3', '', '', 0, 80, 80, 2, 14, 0, 1, 1, 1, 1, 0, 2, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1000, 2000, 'SmartAI', 0, 1, 3, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_treppen_add', 12340);

-- Portal related NPCs
DELETE FROM `creature_template` WHERE `entry` IN (500034, 500035, 500036);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(500034, 0, 0, 0, 0, 0, 8606, 0, 0, 0, 'Horde Portal', '', '', 0, 80, 80, 2, 14, 0, 0, 0, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554688, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_horde_portal', 12340),
(500035, 0, 0, 0, 0, 0, 1825, 0, 0, 0, 'Hellfire Spawner', '', '', 0, 80, 80, 2, 14, 0, 0, 0, 1, 0, 0, 1, 2000, 0, 1, 1, 1, 33554688, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 'npc_hellfire_spawner', 12340),
(500036, 0, 0, 0, 0, 0, 17311, 0, 0, 0, 'Hellbeast', '', '', 0, 79, 79, 2, 14, 0, 1, 1.14286, 1, 1, 0, 2.5, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 800, 1200, 'SmartAI', 0, 1, 4, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_hellbeast', 12340);

-- =============================================
-- Treppen Event NPCs
-- =============================================

-- Treppen Trigger
DELETE FROM `creature_template` WHERE `entry` = 500010;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(500010, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Treppen Trigger', 'Wächter', '', 0, 81, 81, 2, 14, 0, 1, 1.14286, 1, 2, 0, 3, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 5000, 8000, 'SmartAI', 0, 1, 8, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_treppen_trigger', 12340);

-- =============================================
-- Trash Mobs
-- =============================================

-- Zerstörer (Defeater)
DELETE FROM `creature_template` WHERE `entry` = 500000;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(500000, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Zerstörer', 'Berserker', '', 0, 79, 79, 2, 14, 0, 1, 1.14286, 1, 1, 0, 2.2, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1500, 2500, 'SmartAI', 0, 1, 4, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_defeater', 12340);

-- Verteidiger (Defender)
DELETE FROM `creature_template` WHERE `entry` = 500001;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(500001, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Verteidiger', 'Wächter', '', 0, 79, 79, 2, 14, 0, 1, 1.14286, 1, 1, 0, 2.2, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1500, 2500, 'SmartAI', 0, 1, 4, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_defender', 12340);

-- Mage
DELETE FROM `creature_template` WHERE `entry` = 500002;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(500002, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Kampfmagier', '', '', 0, 78, 78, 2, 14, 0, 1, 1.14286, 1, 1, 0, 2.0, 2000, 2000, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1200, 2000, 'SmartAI', 0, 1, 3, 8, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_mage', 12340);

-- Schurke (Rouge)
DELETE FROM `creature_template` WHERE `entry` = 500003;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(500003, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Schatten-Assassine', '', '', 0, 78, 78, 2, 14, 0, 1, 1.14286, 1, 1, 0, 2.5, 1800, 1800, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1800, 2800, 'SmartAI', 0, 1, 3.5, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_rouge', 12340);

-- Hexer (Warlock)
DELETE FROM `creature_template` WHERE `entry` = 50005;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(50005, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Dunkelmagier', '', '', 0, 78, 78, 2, 14, 0, 1, 1.14286, 1, 1, 0, 2.0, 2200, 2200, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1200, 2000, 'SmartAI', 0, 1, 3, 8, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_warlock', 12340);

-- Dunkelschamane (Dark Shaman)
DELETE FROM `creature_template` WHERE `entry` = 50006;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(50006, 0, 0, 0, 0, 0, 16925, 0, 0, 0, 'Dunkelschamane', 'Heiler', '', 0, 79, 79, 2, 14, 0, 1, 1.14286, 1, 1, 0, 1.8, 2500, 2500, 1, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1000, 1800, 'SmartAI', 0, 1, 4, 10, 1, 0, 0, 1, 0, 0, 0, 'npc_trash_shaman', 12340);

-- =============================================
-- Update existing NPCs with new script names
-- =============================================

-- Update Polydeuces Spawner (if exists)
UPDATE `creature_template` SET `ScriptName` = 'npc_portalmeister_spawner' WHERE `entry` = 500011 AND `name` LIKE '%Spawner%';

-- Set movement data for flying creatures
DELETE FROM `creature_template_movement` WHERE `CreatureId` IN (5000013, 500011);
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Chase`, `Random`, `InteractionPauseTimer`) VALUES
(5000013, 1, 0, 0, 0, 0, 0, NULL), -- Gorleax (ground only)
(500011, 1, 0, 0, 0, 0, 0, NULL);  -- Portalmeister (ground only)