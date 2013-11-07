/* Corrected Najentus HP & melee damage */
UPDATE creature_template SET minhealth = 3800000, maxhealth = 3800000, mindmg = 14422, maxdmg = 19038 WHERE entry = 22887;
/* Tidal Burst can't miss */
UPDATE spell_template SET attributesEx3 = 0x00040000 WHERE id = 39878;