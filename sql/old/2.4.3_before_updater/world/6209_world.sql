REPLACE INTO creature_loot_template (entry,item,ChanceOrQuestChance) VALUES (16948,23621,0.02),(25368,23621,0.01);

#any target for illidan visual beam cage spell
UPDATE spell_template SET effectImplicitTargetA1 = 25 WHERE id =40713;

REPLACE INTO npc_text (ID,text0_0) VALUES (450,"We are ready to face Illidan");
REPLACE INTO locales_npc_text (entry,Text0_0_loc2) VALUES (450,"Nous sommes prêts à affronter Illidan.");

REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566000,"Be wary, friends. The Betrayer meditates in the court just beyond.","Prenez garde mes amis, le Traître ressasse ses pensées dans la cour devant nous.",11388,1,"SAY_AKAMA_BEWARE");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566001,"Come, my minions. Deal with this traitor as he deserves!","Venez, mes serviteurs. Occupez-vous de ce traître comme il le mérite !",11465,1,"SAY_AKAMA_MINION");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566002,"I will deal with these mongrels! Strike now, friends! Strike at the Betrayer!","Je vais m'occuper de ces dégénérés. Frappez maintenant, mes amis ! Frappez le Traître !",11390,1,"SAY_AKAMA_LEAVE");

REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566003,"Who shall be next to taste my blades?","Qui sera le prochain à tâter de mes lames ?!",11473,1,"SAY_KILL1");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566004,"This is too easy!","C'est vraiment trop facile !",11472,1,"SAY_KILL2");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566005,"I will not be touched by rabble such as you!","Je ne me laisserai pas atteindre par la racaille !",11479,1,"SAY_TAKEOFF");

REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566006,"Behold the flames of Azzinoth!","Contemplez les flammes d'Azzinoth !",11480,1,"SAY_SUMMONFLAMES");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566007,"Stare into the eyes of the Betrayer!","Soutenez le regard du Traître !",11481,1,"SAY_EYE_BLAST");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566008,"Behold the power of the power... of the demon within!","Contemplez la puissance... du démon intérieur !",11475,1,"SAY_MORPH");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566009,"You've wasted too much time mortals, now you shall fall!","Vous avez perdu trop de temps, mortels. Vous allez succomber !",11474,1,"SAY_ENRAGE");

REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566010,"I can feel your hatred!","Je sens votre haine !",11467,1,"Illidan random taunt 1");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566011,"Give in to your fear!","Laissez parler votre peur !",11468,1,"Illidan random taunt 2");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566012,"You know nothing of power!","Vous ne savez rien de la puissance !",11469,1,"Illidan random taunt 3");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566013,"Such arrogance!","Quelle arrogance !",11471,1,"Illidan random taunt 4");


REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566014,"That is for Naisha!","Voilà pour Naisha !",11493,1,"Maiev random taunt 1");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566015,"Bleed as I have bled!","Saigne comme j'ai saigné !",11494,1,"Maiev random taunt 2");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566016,"There shall be no prison for you this time!","Tu n'auras pas droit à la prison cette fois !",11495,1,"Maiev random taunt 3");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,comment) VALUES (-1566017,"Meet your end, demon!","Affronte ton destin, démon !",11500,1,"Maiev random taunt 4");

REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566018,"Akama. Your duplicity is hardly surprising, I should have slaughtered you and your malformed brethren long ago.","Akama. Ta duplicité n'est pas très étonnante. J'aurais dû vous massacrer depuis longtemps, toi et ton frère déformé.",11463,1,396,"Illidan encounter conversation 1");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566019,"We've come to end your reign, Illidan. My people, and all Outland, shall be free!","Nous sommes venus mettre fin à ton règne, Illidan. Mon peuple et l'Outreterre toute entière seront libres !",11389,1,66,"Illidan encounter conversation 2");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566020,"Boldly said. But i remain... unconvinced.","Bien parlé, mais je ne suis pas convaincu...",11464,1,396,"Illidan encounter conversation 3");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566021,"The time has come! The moment is at hand!","L'heure est venue ! C'est le moment !",11380,1,22,"Illidan encounter conversation 4");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566022,"You are not prepared!","Vous n'êtes pas prêts !",11466,1,22,"Illidan encounter conversation 5");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566023,"Is this it, mortals? Is this all the fury you can muster?","C'est tout, mortels ? Est-ce là toute la fureur que vous pouvez évoquer ?",11476,1,22,"Illidan encounter conversation 6");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566024,"Their fury pales before mine, Illidan. We have some unsettled business between us.","Leur fureur n'est rien à côté de la mienne, Illidan. Nous avons de vieilles querelles à régler.",11491,1,22,"Illidan encounter conversation 7");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566025,"Maiev... How is it even possible?","Maiev... Comment est-ce possible ?",11477,1,22,"Illidan encounter conversation 8");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566026,"My long hunt is finally over. Today, Justice will be done!","Ah... Ma longue chasse est enfin terminée. Aujourd'hui, justice sera faite !",11492,1,22,"Illidan encounter conversation 9");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566027,"Feel the hatred of ten thousand years!","Goûtez à dix mille ans de haine !",11470,1,22,"Illidan encounter conversation 10");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566028,"It is finished. You are beaten.","Ahh... C'est fini. Tu es vaincu !",11496,1,22,"Illidan encounter conversation 11");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566029,"You have won... Maiev. But the huntress... is nothing without the hunt. You... are nothing... without me.","Tu as gagné... Maiev... Mais la chasseresse... n'est rien... sans la chasse... Tu... n'es rien... sans moi...",11478,1,22,"Illidan encounter conversation 12");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566030,"He's right. I feel nothing... I am... nothing.","Il a raison. Je ne ressens rien... Je ne suis plus rien...",11497,1,22,"Illidan encounter conversation 13");
REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566031,"The Light will bless these dismal halls once again... I swear it.","La lumière viendra bénir ces salles lugubres. J'en fais le serment.",11387,1,22,"Illidan encounter conversation 14");

#armor for Maiev
UPDATE creature_template SET armor = 7700 WHERE entry = 23197;

replace into `creature_template` values ('9','0','11686','0','11686','0','Invisible dummy x1','',NULL,'1','1','50000','50000','0','0','0','35','35','0','1','1','0','0','0','0','0','0','0',0x02000000,'0','0','0','0','0','0','0','0','0','10','1024','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','NullCreatureAI','0','3','0','1','0','0','0','','0');