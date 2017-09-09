ALTER TABLE `creature` ADD COLUMN `ScriptName` CHAR(64) NULL DEFAULT '' AFTER `pool_id`;
ALTER TABLE `gameobject` ADD COLUMN `ScriptName` CHAR(64) NULL DEFAULT '' AFTER `state`;