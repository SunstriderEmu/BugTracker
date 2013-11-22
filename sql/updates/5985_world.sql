#new paladin passive. -50% threat on healing spells
replace into spell_template  values('53087','0','0','0','464','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','101','0','0','1','1','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','-1','0','0','6','0','0','1','0','0','1','0','0','0','0','0','0','0','0','-51','0','0','0','0','0','1','0','0','0','0','0','0','0','0','108','0','0','0','0','0','0','0','0','0','0','0','0','0','0','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0','Salvation (passive)','','Salut (passif)','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','0','0','0','0','10','0','0','0','0','0','1','1','1','0','0','0','1');
replace into spell_affect values (53087,0,3223322640);
REPLACE INTO playercreateinfo_spell VALUES (1,2,53087,"salvation (passive -50% threat on healing spells)",1);
REPLACE INTO playercreateinfo_spell VALUES (3,2,53087,"salvation (passive -50% threat on healing spells)",1);
REPLACE INTO playercreateinfo_spell VALUES (10,2,53087,"salvation (passive -50% threat on healing spells)",1);
REPLACE INTO playercreateinfo_spell VALUES (11,2,53087,"salvation (passive -50% threat on healing spells)",1);

#holy shield & shield threat
REPLACE INTO spell_threat VALUES (20925,0,1.35),
(20927,0,1.35),
(20928,0,1.35),
(27179,0,1.35),
(17,22,0),
(592,44,0),
(600,79,0),
(3747,117,0),
(6065,151,0),
(6066,191,0),
(10898,243,0),
(10899,303,0),
(10900,382,0),
(25217,574,0),
(25218,658,0),
(10901,471,0);