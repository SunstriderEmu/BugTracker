-- Shadowsword Guardian Sunwell
UPDATE creature_template SET unit_flags = 0x2008140 WHERE entry = 25954;
-- Drain effect
REPLACE INTO creature_addon (guid, auras) VALUES (311447, "46410");

-- Blue orbs
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`) values('81495','188415','585','3','18.9777','-593.47','-63.6464','3.17294','0','0','0.999877','-0.0156708','25','0','1','');
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`) values('81496','188415','585','3','-19.6255','-552.207','-63.7666','4.54739','0','0','0.762973','-0.64643','25','0','1','');
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`) values('81497','188415','585','3','-32.1472','-644.201','-63.7468','1.4921','0','0','0.678745','0.734374','25','0','1','');
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`) values('81498','188415','585','3','-70.9116','-601.727','-63.7659','0.00303221','0','0','0.0015161','0.999999','25','0','1','');
