-- Add SWD and Smite to Force of Will crit effect
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x200000000 | 0x80 WHERE entry = 18544 and effectId = 0;
-- Add SWD to Force of Will damage effect
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x200000000 WHERE entry = 18544 and effectId = 1;
-- delete higher ranks
DELETE FROM spell_affect WHERE entry IN (18547, 18548, 18549, 18550);