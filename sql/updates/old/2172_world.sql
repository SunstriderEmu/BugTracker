-- Areatriggers
DELETE FROM `areatrigger_scripts` WHERE `entry`=4016;
INSERT INTO `areatrigger_scripts` (`entry`,`ScriptName`) VALUES (4016,'at_malfurion_stormrage');

UPDATE `instance_template` SET `script`='instance_sunken_temple' WHERE `map`=109;
UPDATE `gameobject_template` SET `ScriptName`='go_atalai_statue' WHERE `entry` IN (148830,148831,148832,148833,148834,148835);
DELETE FROM `areatrigger_scripts` WHERE `entry`=4016;

