-- Empowered Healing higher ranks
DELETE FROM spell_affect WHERE entry IN (33159, 33160, 33161, 33162);
-- Add binding heal
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x400000000 WHERE entry = 33158 and effectId = 1;
