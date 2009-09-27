-- Add script for them
UPDATE `gameobject_template` SET `ScriptName`='go_fel_crystalforge' WHERE `entry`=185919;
UPDATE `gameobject_template` SET `ScriptName`='go_bashir_crystalforge' WHERE `entry`=185921;

-- Spawn missing crystalforge
DELETE FROM gameobject WHERE id = 185919;
INSERT INTO gameobject(id, map, spawnMask, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state)
    VALUES(185919, 530, 1, 1475.36, 7245.71, 374.421, 4.11401, 0, 0, 0.88411, -0.467278, 25, 0, 1);
