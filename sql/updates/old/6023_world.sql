UPDATE version SET core_version = "Winrunner Rev: 6023";

#no crush for Gathios 
UPDATE creature_template SET flags_extra = 0x1 + 0x20 WHERE entry = 22949;
#no crush & dual wield for Veras & can be stunned
UPDATE creature_template SET mechanic_immune_mask = 617299803 - 0x800, flags_extra = 0x1 + 0x20 + 0x200000 WHERE entry = 22952;

#reputation for all 4 members
REPLACE INTO creature_onkill_reputation (creature_id, RewOnKillRepFaction1, MaxStanding1, RewOnKillRepValue1)
VALUES (22951,1012,7,250),
(22949,1012,7,250),
(22952,1012,7,250),
(22950,1012,7,250);

#fixed HP
UPDATE creature_template SET minhealth = 2600000, maxhealth = 2600000 WHERE entry IN (22951,22949,22952,22950);

#some non interruptible spells
UPDATE spell_template SET preventionType = 0 WHERE id IN (41471,41472,41481,41482,41483,41524);