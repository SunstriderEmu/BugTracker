#hp for attumen
UPDATE creature_template SET minhealth = 379400, maxhealth = 379400 WHERE entry IN (16152,15550);
#no crush for midnight
UPDATE creature_template SET minhealth = 379400, maxhealth = 379400, flags_extra = 0x10020 WHERE entry = 16151;

REPLACE INTO script_texts (entry,content_default,content_loc2,`type`,`comment`) VALUES (-1999933,"Midnight calls for her master!","Minuit appelle son maître !",2,"EMOTE_CALL_ATTUMEN");
REPLACE INTO script_texts (entry,content_default,content_loc2,`type`,`comment`) VALUES (-1999934,"Midnight rushes to her master's aid.","Minuit se rue au secours de son maître.",2,"EMOTE_MOUNT");

#SPELL_INFERNAL_RELAY_ERASE
REPLACE INTO spell_script_target VALUES (30835,1,17646);

#new custom spell to trigger new inferno
REPLACE INTO spell_script_target VALUES (53108,1,17645);
UPDATE creature_template SET ScriptName = "npc_infernal_relay" where entry = 17645;

replace into `spell_template` values('53108','0','0','0','256','524288','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','101','0','0','0','0','0','0','0','0','0','0','13','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','-1','0','0','77','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','22','0','0','7','0','0','22','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','Infernal Relay','','Relais de l\'infernal','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','1');