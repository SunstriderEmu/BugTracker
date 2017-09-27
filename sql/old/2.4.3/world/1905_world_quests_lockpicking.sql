UPDATE `gameobject` SET `spawnMask` = '0' WHERE `id` = 123334;
UPDATE `gameobject_template` SET `data7` = '0' WHERE `entry` IN (123331,123332,178246);
UPDATE `gameobject_template` SET `ScriptName` = 'go_practice_lockbox' WHERE `entry` IN (123330,123331,123332,123333,178244,178245,178246);
