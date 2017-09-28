UPDATE instance_template SET script = 'instance_zulfarrak' WHERE map = 209;
UPDATE gameobject_template SET scriptName = 'go_troll_cage' WHERE entry BETWEEN 141070 AND 141075;

DELETE FROM script_texts WHERE entry IN (-1209000, -1209001, -1209002, -1209003, -1209004);
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc2`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
('-1209000','Oh no! Here they come!','Oh non, ils arrivent !','0','0','1','0','Weegli Blastfuse SAY_WEEGLI_OHNO'),
('-1209001','OK. Here I go.','Ok, c\'est parti.','0','0','1','0','Weegli Blastfuse SAY_WEEGLI_OK_I_GO'),
('-1209002','What? How dare you say that to me?!?','Quoi ?! Comment osez-vous me dire ça ?!','0','0','1','0','Sergeant Bly SAY_1'),
('-1209003','After all we\'ve been through? Well, I didn\'t like you anyway!!','Après tout ce que nous avons traversé ? Bien, de toute façon je ne vous aimais pas !','0','0','1','0','Sergeant Bly SAY_2'),
('-1209004','I\'m out of here!','Je suis libre !','0','0','1','0','Weegli Blastfuse SAY_WEEGLI_OK_I_GO');

DELETE FROM waypoint_data WHERE id = 81555;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`) VALUES
('81555','1','1884.869','1228.621','9.70','0','1','0','100','0'),
('81555','2','1887.53','1263','41.52','0','1','0','100','0');

UPDATE eventai_scripts SET event_type = 11 WHERE id IN (887601,760601);
UPDATE eventai_scripts SET action1_type = 29, action1_param1 = 15 WHERE creature_id IN (8876,7606) AND action1_type = 21 AND action1_param1 = 0;

UPDATE creature_template SET regenhealth = 0 WHERE entry IN (7608,7606,7605,7604,7607);

DELETE FROM `eventai_scripts` WHERE `id` = '760805';
INSERT INTO `eventai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
('760805','7608','2','0','85','3','0','50','10000','12000','11','11642','0','0','0','0','0','0','0','0','0','0','Murta Grimgut - Cast Heal on Self');

DELETE FROM event_scripts WHERE id = 2609 AND (delay > 0 OR command != 11);

-- UPDATE gameobject SET spawnMask = 1 WHERE id = 146084;
