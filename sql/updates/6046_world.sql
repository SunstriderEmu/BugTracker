#cant miss for SPELL_DEADLY_POISON from Veras
UPDATE spell_template SET AttributesEx3 = 0x00040000 WHERE id = 41485;
#remove  SPELL_ATTR_EX_NEGATIVE from deadly strike
UPDATE spell_template SET AttributesEx = 0x8 WHERE id = 41480;
#remove teleport effect
UPDATE spell_template SET effect1 = 0 WHERE id = 41479;

#Illidan HP
UPDATE creature_template SET minhealth = 6070400, maxhealth = 6070400 WHERE entry = 22917;

ALTER TABLE spell_template
	ALTER powerType SET DEFAULT '0'; 

replace into `spell_template` values('53088','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','9','0','0','0','101','1','0','0','70','66','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','-1','0','0','6','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','12','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','Self stun (2,5s)','','Self stun (2,5s)','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','1');

#lot of Hyjal stuff (horde camp)
UPDATE creature_template SET minhealth = 55888, maxhealth = 55888, AIName = "SmartAI", ScriptName = "" WHERE entry = 17932;
UPDATE creature_template SET minhealth = 41916, maxhealth = 41916, equipment_id = 17934, AIName = "SmartAI", ScriptName = "" WHERE entry = 17934;
UPDATE creature_template SET minhealth = 41916, maxhealth = 41916, minmana = 25240, maxmana = 25240, equipment_id = 17936, AIName = "SmartAI", ScriptName = "" WHERE entry = 17936;
UPDATE creature_template SET minhealth = 41916, maxhealth = 41916, minmana = 25240, maxmana = 25240, equipment_id = 17936, AIName = "SmartAI", ScriptName = "" WHERE entry = 17935;
UPDATE creature_template SET minhealth = 83832, maxhealth = 83832 WHERE entry = 17933;
UPDATE creature_template SET minhealth = 41916, maxhealth = 41916 WHERE entry = 17937;
UPDATE creature_template SET minhealth = 569100, maxhealth = 569100 WHERE entry = 17852;
UPDATE creature_template SET type = 11, spell1 =  31761 WHERE entry = 18036;

replace into `creature_equip_template` (`entry`, `equipmodel1`, `equipmodel2`, `equipmodel3`, `equipinfo1`, `equipinfo2`, `equipinfo3`, `equipslot1`, `equipslot2`, `equipslot3`) values('17934','22671','0','22671','1538','0','33492994','781','0','25');
replace into `creature_equip_template` (`entry`, `equipmodel1`, `equipinfo1`, `equipslot1`) values('17936','20419','2562','17');

replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17932','0','0','Destroy them all!','Détruisez-les tous !','0','0','50','0','0','0','Horde Grunt - Aggro 1');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17932','0','1','Demon filth!','Pourriture démoniaque !','0','0','50','0','0','0','Horde Grunt - Aggro 2');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17932','0','2','Have at them! Lok-Tar! ','Sus à l\'ennemi ! Lok-Tar !','0','0','50','0','0','0','Horde Grunt - Aggro 3');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17932','1','0','Another one down!','Et un de moins !','0','0','0','0','0','0','Horde Grunt - Kill');

replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17934','0','0','Take their heads!','Prenez leurs têtes !','0','0','50','0','0','0','Horde Headhunter - Aggro');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17934','1','0','We kill \'em good, mon.','Toi t\'es mort !','0','0','0','0','0','0','Horde Headhunter - Kill');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17934','2','0','Dis no good....','Ça pas bon...','0','0','0','0','0','0','Horde Headhunter - Death');

replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17936','0','0','My spirit will fight on...','Mon esprit poursuivra la lutte...','0','0','0','0','0','0','Horde Shaman - Death');

replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17935','0','0','It all over for you, mon.','Fin pour toi démon.','0','0','0','0','0','0','Horde Witch Doctor - Kill');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17935','1','0','I no gonna make it....','Pas pouvoir aller plus loin...','0','0','0','0','0','0','Horde Witch Doctor - Death 1');
replace into `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) values('17935','1','1','Bad mojo.','Mauvais mojo.','0','0','0','0','0','0','Horde Witch Doctor - Death 2');

REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(17932,0,0,0,0,0,100,0,2000,5000,8000,14000,11,31754,5,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Grunt - cast strike"),
(17932,0,1,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Hyjal alliance knight - Say on aggro"),
(17932,0,2,0,5,0,100,0,1000,60000,0,0,1,1,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Headhunter - Say on kill");

REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(17934,0,0,0,37,0,100,0,0,0,0,0,58,1,31758,2500,2500,28,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Headhunter - Set ranged & cast Spear Throw"),
(17934,0,1,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Headhunter - Say on aggro"),
(17934,0,2,0,5,0,100,0,1000,60000,0,0,1,1,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Headhunter - Say on kill"),
(17934,0,3,0,6,0,25,0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Headhunter - Say on death");

REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(17936,0,0,0,0,0,100,0,1000,1000,14000,16000,11,6742,1,0,0,0,0,19,17932,30,0,0.0,0.0,0.0,0.0,"Hyjal Horde Shaman - Bloodlust"),
(17936,0,1,0,37,0,100,0,0,0,0,0,58,1,31764,1000,1000,35,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Shaman - Caster template (with 
Lightning Bolt)"),
(17936,0,2,0,60,0,100,0,0,0,600000,600000,11,31765,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Shaman - Lightning Shield"),
(17920,0,3,0,6,0,25,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Shaman - Say on death");

REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(17935,0,0,0,0,0,100,0,1000,1000,32000,33000,11,31760,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Witch Doctor - Healing Ward"),
(17935,0,1,0,37,0,100,0,0,0,0,0,58,1,31759,1000,1000,35,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Witch Doctor - Caster template (with 
Holy Bolt)"),
(17935,0,2,0,5,0,100,0,1000,60000,0,0,1,0,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Witch Doctor - Say on kill"),
(17935,0,3,0,6,0,25,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Hyjal Horde Witch Doctor - Say on death");

#BT dead wolf
UPDATE creature_template_addon set auras = "41290 0" WHERE entry = 23232;