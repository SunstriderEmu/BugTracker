/* Corrected Najentus HP & melee damage*/
UPDATE creature_template SET mindmg = 8364, maxdmg = 11826 WHERE entry = 22898;
REPLACE INTO script_texts(entry,content_default,content_loc2,TYPE,COMMENT) VALUES ('-1563999',"You hear a loud rumble of metal grinding on stone...","Vous entendez le lourd grondement de l'acier raclant la pierre.",3,"Najentus door opening on death");

/* Supremus health & damage & no crush */
UPDATE creature_template SET minhealth = 4500000, maxhealth = 4500000, mindmg = 11250, maxdmg = 15750, flags_extra = 0x00000021 WHERE entry = 22898;

/* civilian volcano */
UPDATE creature_template SET flags_extra = 0x2 WHERE entry = 23085;

/* Mark akama as boss & correct hp/mana & dual wield & correct model */
UPDATE creature_template SET minhealth = 1252020, maxhealth = 1252020, minmana = 338700, maxmana = 338700, npcflag = 2, rank = 3, flags_extra = 0x00200000, modelid_A = 21318, modelid_H = 21318, scale = 1 WHERE entry = 22990;
REPLACE INTO npc_text(ID,text0_0) VALUES (393,"Illidan's grasp over my tribe is strong, $N. It shall be over soon, one way or another.$b$bAre you ready, $N? My people's future depends on us.");
REPLACE INTO locales_npc_text(entry,Text0_0_loc2) VALUES (393,"L'emprise d'Illidan sur ma tribu est puissante, $N. Tout sera bientôt fini, d'une manière ou d'une autre.$b$bÊtes-vous prêt$g:e;, $N ? L'avenir de mon peuple est entre vos mains."); 
REPLACE INTO npc_text(ID,text0_0) VALUES (394,"I'm with you, Akama. ");
REPLACE INTO locales_npc_text(entry,Text0_0_loc2) VALUES (394,"Je suis avec vous, Akama. "); 
REPLACE INTO creature_onkill_reputation (creature_id,RewOnKillRepFaction1,MaxStanding1,RewOnKillRepValue1) VALUE (22990,1012,7,250);
 
 /* Shadow hp & damage & dual wield  & immune taunt*/
UPDATE creature_template SET minhealth = 1000000, maxhealth = 1000000, mindmg = 18000, maxdmg = 25500, flags_extra = 0x00210000 WHERE entry = 22841; 
 
 /* delete channelers (these are now summoned) */
DELETE FROM creature WHERE id = 23421;
 
/* Akama's canalist reputation on kill */
REPLACE INTO creature_onkill_reputation (creature_id,RewOnKillRepFaction1,MaxStanding1,RewOnKillRepValue1) VALUE (23421,1012,7,15);

/* Lieur d'esprit cendrelangue */
UPDATE creature_template SET minhealth =  23000, maxhealth = 23000, equipment_id = 987 WHERE entry = 23524; -- arme 5613 baton
update creature_onkill_reputation set RewOnKillRepValue1 = 15 where creature_id = 23524;

/*Elémentaliste cendrelangue */
UPDATE creature_template SET minhealth =  23000, maxhealth = 23000, equipment_id = 91467 WHERE entry = 23523;
REPLACE INTO creature_equip_template (entry,equipmodel1,equipinfo1,equipslot1) VALUES (91467,20412,50268674,529); -- arme 3902 baton

/* Ensorceleur cendrelangue */
UPDATE creature_template SET minhealth =  100500, maxhealth = 100500, mechanic_immune_mask = 617299803, equipment_id = 91468 WHERE entry = 23215;
REPLACE INTO creature_onkill_reputation (creature_id,RewOnKillRepFaction1,MaxStanding1,RewOnKillRepValue1) VALUE (23215,1012,7,15);
REPLACE INTO creature_equip_template (entry,equipmodel1,equipinfo1,equipslot1) VALUES (91468,39105,50268674,529); -- arme 25176 baton

/* Voleur cendrelangue */
UPDATE creature_template SET minhealth =  28000, maxhealth = 28000, mindmg = 2932, maxdmg = 5994, equipment_id = 91469, flags_extra = 0x00200000 WHERE entry = 23318;
REPLACE INTO creature_equip_template VALUES (91469,28789,28789,0,33492738,33490690,0,781,781,0);-- armes 12582 dagues x2

/* Défenseur cendrelangue */
UPDATE creature_template SET minhealth =  79000, maxhealth = 79000, mindmg = 4146, maxdmg = 8476, equipment_id = 91470 WHERE entry = 23216;
REPLACE INTO creature_equip_template VALUES (91470,12284,47250,0,33490690,33490436,0,781,1038,0); -- armes 32660 (épée), 34011 (bouclier)