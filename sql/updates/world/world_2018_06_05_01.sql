-- Add custom family flags to Vampiric Embrace to allow talent shadow affinity to affect it (but not improved_vampiric_embrace)
REPLACE INTO spell_template_override (entry, SpellFamilyName, SpellFamilyFlags, Comment) VALUES (15290, 6, 0x200000000000, "Add custom SpellFamilyFlags to allow shadow affinity to affect it");

UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask & ~0x4 WHERE entry = 15318;
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x200000000000 WHERE entry = 15318;