UPDATE instance_template SET script = "instance_ramparts" WHERE map = 543;

replace into `gameobject` (`guid`, `id`, `map`, `spawnMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`) values('165991','185168','543','1','-1429.81','1772.92','82.0765','5.044','0','0','0.580703','-0.814115','7200','255','1','');
replace into `gameobject` (`guid`, `id`, `map`, `spawnMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`) values('165992','185169','543','2','-1429.81','1772.92','82.0765','5.044','0','0','0.580703','-0.814115','7200','255','1','');

UPDATE gameobject_template SET flags = 16 WHERE entry IN (185168, 185169);