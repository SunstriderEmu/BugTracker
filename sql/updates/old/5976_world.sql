#Discretion talent (added lifebloom & swiftmend)
UPDATE spell_affect
SET SpellFamilyMask = 4509999143425010
WHERE (entry <= 17122 AND entry >= 17118)
AND effectId = 0;

#Lifebloom threat
REPLACE INTO spell_threat values (33763,0,0.5);