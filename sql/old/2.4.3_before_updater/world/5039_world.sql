DELETE FROM `command` WHERE `name` = 'spectator';
INSERT INTO `command` (`name`, `security`, `help`) VALUES ('spectator', 0, 'Syntax: .spectator $subcommand.\nUse .help spectator');
DELETE FROM `command` WHERE `name` = 'spectator watch';
INSERT INTO `command` (`name`, `security`, `help`) VALUES ('spectator watch', 0, 'Syntax: .spectator watch #player\nAllow player to spectate arena from anotherplayer.');
DELETE FROM `command` WHERE `name` = 'spectator version';
INSERT INTO `command` (`name`, `security`, `help`) VALUES ('spectator version', 0, 'Syntax: .spectator version\nSee version of spectator addon.');
DELETE FROM `command` WHERE `name` = 'spectator leave';
INSERT INTO `command` (`name`, `security`, `help`) VALUES ('spectator leave', 0, 'Syntax: .spectator leave\nDisable spectator mode.');
DELETE FROM `command` WHERE `name` = 'spectator spectate';
INSERT INTO `command` (`name`, `security`, `help`) VALUES ('spectator spectate', 0, 'Syntax: .spectator spectate #player\nAllow to spectate player.');
DELETE FROM `command` WHERE `name` = 'spectator reset';
INSERT INTO `command` (`name`, `security`, `help`) VALUES ('spectator reset', 0, 'Syntax: .spectator reset\nSend addon data.');

UPDATE `gameobject_template` SET `flags` = 36 WHERE entry IN (185918, 185917, 183970, 183971, 183972, 183973, 183977, 183979, 183978, 183980);

DELETE FROM creature_template WHERE entry = '15';
INSERT INTO creature_template (entry, modelid_A, modelid_A2, modelid_H, modelid_H2, name, subname, IconName, minlevel, maxlevel, minhealth, maxhealth, armor, faction_A, faction_H, npcflag, speed, scale, rank, class, unit_flags, type, type_flags, InhabitType, RegenHealth, flags_extra, ScriptName) VALUES 
('15', '5566', '5566', '5566', '5566', "Arena Spectator", "Use addon!", 'Speak', 71, 71, 10000, 10000, 1000, 35, 35, 3, 1, 1.25, 1, 1, 2, 7, 138936390, 3, 1, 2, 'npc_spectate');

