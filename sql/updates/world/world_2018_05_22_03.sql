-- Shadow affinity higher ranks
DELETE FROM spell_affect WHERE entry IN (15272, 15320);

-- Add Touch of Weakness to Shadow affinity
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x80000 WHERE entry = 15318;

-- Add family flags to Vampiric Embrace to allow talent to affect it
REPLACE INTO spell_template_override (entry, SpellFamilyName, SpellFamilyFlags, Comment) VALUES (15290, 6, 0x4, "Add SpellFamilyFlags to allow talents to affect it");
