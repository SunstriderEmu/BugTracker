DELETE FROM `creature_template` WHERE (`entry`=23109);
INSERT INTO `creature_template` (`entry`, `heroic_entry`, `modelid_A`, `modelid_A2`, `modelid_H`, `modelid_H2`, `name`, `subname`, `IconName`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `baseattacktime`, `rangeattacktime`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `class`, `race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `RacialLeader`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES (23109, 0, 21300, 0, 21300, 0, 'Vengeful Spirit', '', '', 70, 70, 20000000, 20000000, 0, 0, 0, 35, 35, 0, 1, 1, 1, 0, 0, 0, 0, 1000000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40314, 40175, 40325, 40157, 0, 0, 0, '', 0, 1, 0, 1, 0, 8388624, 0, 'vengeful_spirit');

DELETE FROM spell_script_target WHERE ENTRY = 40268;
INSERT INTO spell_script_target VALUES (40268, 1, 23109);
           

UPDATE `creature_template` SET 
    `mindmg` = 2500, 
    `maxdmg` = 3000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 23111;

UPDATE `creature_template` SET `baseattacktime` = 2000 WHERE `entry` = 23111;
UPDATE `creature_template` SET `faction_A` = 1813, `faction_H` = 1813 WHERE `entry` = 23111;

UPDATE `creature_template` SET `speed` = 0.8 WHERE `entry` = 23111;
