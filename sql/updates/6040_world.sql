UPDATE version SET core_version = "Winrunner Rev: 6040";

#teron & council & shahraz
UPDATE creature_template SET speed = 2.0, mindmg = 14775, maxdmg = 20868 WHERE entry = 22871;
UPDATE creature_template SET speed = 2.0, mindmg = 16623, maxdmg = 23478 WHERE entry = 22947;
UPDATE creature_template SET speed = 2.0, mindmg = 4617, maxdmg = 6522 WHERE entry = 22951;
UPDATE creature_template SET speed = 2.0, mindmg = 19566, maxdmg = 6522 WHERE entry = 22949;
UPDATE creature_template SET speed = 2.0, mindmg = 7965, maxdmg = 11262 WHERE entry = 22952;
UPDATE creature_template SET speed = 2.0, mindmg = 2955, maxdmg = 4173 WHERE entry = 22950;

#some updates on illidan fight
UPDATE creature_template SET minhealth = 6800000, maxhealth = 6800000, minmana = 0, maxmana = 0, mindmg = 14934, maxdmg = 21117, flags_extra = 33 + 0x00010000 WHERE entry = 22917;
REPLACE INTO creature_onkill_reputation (creature_id, RewOnKillRepFaction1, MaxStanding1, RewOnKillRepValue1)
VALUES (22917,1012,7,500),(23375,1012,7,15);
UPDATE creature_template SET minhealth = 22000, maxhealth = 22000, equipment_id = 2197 WHERE entry = 23226;
UPDATE creature_template SET speed = 1, minhealth = 22000, maxhealth = 22000 WHERE entry = 23375;
UPDATE creature_template SET flags_extra = 0x00010000 WHERE entry = 22997;
UPDATE creature_template SET minhealth = 379400 , maxhealth = 379400 , minmana = 33870, maxmana = 33870, flags_extra = 0x00010000 WHERE entry = 23089;