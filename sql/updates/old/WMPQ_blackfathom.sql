UPDATE `instance_template` SET `script`='instance_blackfathom_deeps' WHERE `map`=48;

UPDATE `gameobject_template` SET `ScriptName`='go_blackfathom_fire' WHERE `entry` IN (21118,21119,21120,21121);
UPDATE `gameobject_template` SET `ScriptName`='go_blackfathom_altar' WHERE `entry` IN (103015,103016);

UPDATE `creature_template` SET `ScriptName`='boss_gelihast' WHERE `entry`=6243;
UPDATE `creature_template` SET `ScriptName`='boss_kelris' WHERE `entry`=4832;
UPDATE `creature_template` SET `ScriptName`='boss_aku_mai' WHERE `entry`=4829;
