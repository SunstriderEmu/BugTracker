UPDATE creature_template SET ScriptName = "npc_curator_astral_flare" WHERE entry IN (17096,19781,19782,19783);


replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('17225','0','0','An ancient being awakens in the distance...','16','0','100','0','0','0','13647','3','Nightbane - EMOTE_SUMMON');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('17225','1','0','What fools! I shall bring a quick end to your suffering!','14','0','100','0','0','0','13649','3','Nightbane - YELL_AGGRO');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('17225','2','0','Miserable vermin. I shall exterminate you from the air!','14','0','100','0','0','0','20023','3','Nightbane - YELL_FLY_PHASE');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('17225','3','0','Enough! I shall land and crush you myself!','14','0','100','0','0','0','13676','3','Nightbane - YELL_LAND_PHASE');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('17225','3','1','Insects! Let me show you my strength up close!','14','0','100','0','0','0','13677','3','Nightbane - YELL_LAND_PHASE');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('17225','4','0','%s takes a deep breath.','41','7','100','0','0','0','24548','3','Nightbane - EMOTE_BREATH');

REPLACE INTO locales_creature_text (entry, groupid, id, text_loc2) VALUES ('17225','0','0','Un être ancien apparait au loin...');
REPLACE INTO locales_creature_text (entry, groupid, id, text_loc2) VALUES ('17225','1','0','Pauvres fous ! Je devrais apporter une fin rapide à votre souffrance !');
REPLACE INTO locales_creature_text (entry, groupid, id, text_loc2) VALUES ('17225','2','0','Misérable vermine. Je vais vous exterminer depuis les airs !');
REPLACE INTO locales_creature_text (entry, groupid, id, text_loc2) VALUES ('17225','3','0','Assez ! Je vais atterrir et vous écraser moi-même !');
REPLACE INTO locales_creature_text (entry, groupid, id, text_loc2) VALUES ('17225','3','1','Insectes ! Laissez-moi vous montrer ma force !');
REPLACE INTO locales_creature_text (entry, groupid, id, text_loc2) VALUES ('17225','4','0','%s prend une profonde respiration.');
