-- Dark Portal Event Controller
DELETE FROM creature_template WHERE entry = 26837;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `pool_id`) values('26837','0','15880','0','0','0','Dark Portal Event Controller',NULL,NULL,'0','1','1','0','35','0','1','1','0','0','2000','0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1','1','1','1','1','0','1','0','0','130','dark_portal_event_controller','0');

DELETE FROM creature WHERE guid = 311414;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `pool_id`, `ScriptName`) values('311414','26837','530','1','11686','0','-249.429','1185.27','111.76','4.71298','25','0','0','42','0','0','0','');

-- Remove creature with wrong path
UPDATE creature SET MovementType = 0 WHERE guid = 98123;

-- Remove existing demons creatures in front of dark portal
DELETE FROM creature WHERE position_x < -189 AND position_x > -314 AND position_y < 1186 AND position_y > 1141 AND id IN (18944,18345,18945);