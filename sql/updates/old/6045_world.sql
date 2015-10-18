UPDATE version SET core_version = "Winrunner Rev: 6045";

REPLACE INTO creature_onkill_reputation (creature_id, RewOnKillRepFaction1, MaxStanding1, RewOnKillRepValue1)
VALUES (23426,1012,7,250);
UPDATE creature_template SET minlevel = 73, maxlevel = 73 WHERE entry = 23426;

DELETE FROM creature_onkill_reputation WHERE creature_id IN (22952,22950,22949,22951);

#re ordering spell for Vengeful Spirit (teron fight)
UPDATE creature_template SET spell2 = 0, spell3 = 40157, spell4 = 40175, spell5 = 40314, spell6 = 0, spell7 = 40322 WHERE entry = 23109;

UPDATE creature_template SET InhabitType = 7 WHERE entry = 23123;

UPDATE spell_template SET Attributes = 0 WHERE id IN (40157,40314);
UPDATE spell_template SET Attributes = 0x100000 WHERE id = 40175;
