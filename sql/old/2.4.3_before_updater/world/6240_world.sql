UPDATE creature SET `MovementType`=0 WHERE `spawndist` = 0 and `MovementType`=1;
UPDATE creature SET equipment_id = 0 WHERE id = 18320;
DELETE FROM smart_scripts WHERE entryorguid >= 4872 AND source_type = 2;
DELETE FROM smart_scripts WHERE action_type = 11 AND action_param1 > 53090;
ALTER TABLE uptime MODIFY COLUMN `maxplayers` smallint(5) unsigned NOT NULL DEFAULT '1';
UPDATE creature_template SET AIName = '' WHERE AIName = "SmartAI" AND entry NOT IN (select entryorguid from smart_scripts where source_type = 0 group by entryorguid);