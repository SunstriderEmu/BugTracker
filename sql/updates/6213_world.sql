REPLACE INTO script_texts (entry,content_default,content_loc2,sound,type,emote,comment) VALUES (-1566019,"We've come to end your reign, Illidan. My people, and all Outland, shall be free!","Nous sommes venus mettre fin à ton règne, Illidan. Mon peuple et l'Outreterre toute entière seront libres !",11389,1,66,"Illidan encounter conversation 2");

#SPELL_ATTR_EX3_NO_DONE_BONUS
update spell_template set AttributesEx3 = 0x20000000 where id = 40932;