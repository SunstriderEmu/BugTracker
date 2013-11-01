#Various fixes on Hyjal Alliance camp
UPDATE creature_template SET minrangedmg = 600, maxrangedmg = 800, AIName = "SmartAI", ScriptName = "", minhealth = 41916, maxhealth = 41916, armor = 4700 WHERE entry = 17921;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "", minhealth = 83832, maxhealth = 83832, armor = 7700 WHERE entry = 17920;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "", minhealth = 41916, maxhealth = 41916, armor = 7700 WHERE entry = 17919;
UPDATE creature_template SET minhealth = 6986, maxhealth = 6986, armor = 3800 WHERE entry = 17931;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "", minhealth = 41916, maxhealth = 41916, armor = 3800 WHERE entry = 17922;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "", minhealth = 41916, maxhealth = 41916, armor = 3800 WHERE entry = 17928;
UPDATE creature_template SET armor = 6200 WHERE entry = 17772;
UPDATE creature_template SET armor = 7700 WHERE entry = 17932;
UPDATE creature_template SET armor = 3800 WHERE entry = 17936;
UPDATE creature_template SET armor = 4700 WHERE entry = 17934;

UPDATE creature_equip_template SET equipmodel1 = 22105, equipinfo1 = 33489154 WHERE entry = 10;
UPDATE creature_equip_template SET equipinfo1 = 33489154 WHERE entry = 1407;

REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(17921,0,0,0,37,0,100,0,0,0,0,0,58,1,32103,2500,2500,28,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance Rifleman - Set ranged & cast shoot"),
(17921,0,1,0,37,0,100,0,0,0,0,0,87,28,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance Rifleman - Set ranged visual"),
(17921,0,2,0,0,0,100,0,2000,5000,10000,15000,11,7896,5,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance Rifleman - cast exploding shot");
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES (17920,0,0,0,0,0,100,0,500,500,30000,30000,11,31732,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance knight - Rallying cry"),
(17920,0,0,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance knight - Say on aggro"),
(17920,0,1,0,5,0,100,0,1000,60000,0,0,1,2,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance knight - Say on kill"),
(17920,0,2,0,6,0,25,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance knight - Say on death");
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES (17919,0,0,0,32,0,100,0,0,50000,30000,30000,11,31731,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance footman - Shield Wall on damage taken"),
(17919,0,0,0,4,0,10,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance footman - Say on aggro"),
(17919,0,1,0,5,0,100,0,1000,60000,0,0,1,2,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance footman - Say on kill"),
(17919,0,2,0,6,0,20,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance footman - Say on death");
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(17922,0,0,0,0,0,100,0,1500,1500,15000,15000,11,31741,5,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance sorceress - Slow"),
(17922,0,1,0,37,0,100,0,0,0,0,0,58,1,31743,1000,1000,35,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance sorceress - Caster template (with arcane projectile)");
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(17928,0,0,0,14,0,100,0,8000,35,10000,15000,11,31739,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Alliance Priest - Heal"),
(17928,0,1,0,37,0,100,0,0,0,0,0,58,1,31740,1000,1000,35,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance priest - Caster template (with smite)");

replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17919','0','1','Let these monsters taste cold steel!','Que ces monstres goûtent au froid de l\'acier !','0','0','50','0','0','0','Hyjal Footman - Aggro 1');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17919','0','0','Back, hold them back!','Allez, repoussez-les !','0','0','50','0','0','0','Hyjal Footman - Aggro 2');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17919','1','0','I... can\'t....','Je ne… peux pas…','0','0','50','0','0','0','Hyjal Footman - Death 1');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17919','1','1','Argghh !','Argghh !','0','0','50','0','0','0','Hyjal Footman - Death 2');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17919','2','0','Back to the void with you!','Retourne au Vide !','0','0','50','0','0','0','Hyjal Footman - Kill 1');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17919','2','1','One less demon to contend with! ','Un démon de moins à combattre !','0','0','50','0','0','0','Hyjal Footman - Kill 2');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17920','0','0','For the Light!','Pour la Lumière !','0','0','50','0','0','0','Hyjal Knight - Aggro 1');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17920','0','1','Rout these demons!','Boutez ces démons !','0','0','50','0','0','0','Hyjal Knight - Aggro 2');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17920','1','0','Good will... prevail.','Le bien… triomphera.','0','0','0','0','0','0','Hyjal Knight - Death 1');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17920','1','1','Light receive me!','Que la Lumière me reçoive...','0','0','0','0','0','0','Hyjal Knight - Death 2');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17920','2','0','Justice is served!','Justice est faite !','0','0','0','0','0','0','Hyjal Knight - Kill 1');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17920','2','1','For Lordaeron! For victory!','Pour Lordaeron ! Pour la victoire !','0','0','0','0','0','0','Hyjal Knight - Kill 2');

UPDATE creature_template SET equipment_id = 291 WHERE entry = 17931;

#bad guys
UPDATE creature_template SET minhealth = 80000, maxhealth = 80000, flags_extra = 0x00000020 WHERE entry = 17905;
replace into `eventai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) values('1790503','17905','0','0','80','3','15000','20000','25000','35000','11','31662','0','0','0','0','0','0','0','0','0','0','Banshee - Cast Anti-Magic Shell');
replace into `eventai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) values('1790605','17905','6','0','20','2','0','0','0','0','1','-691','-690','0','0','0','0','0','0','0','0','0','Banshee - Say on death');

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17903;
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES (17903,0,0,0,37,0,100,0,0,0,0,0,58,1,31618,2000,2000,35,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance priest - Caster template (with smite)");
UPDATE creature_template SET dmgschool = 2 WHERE entry = 17908;