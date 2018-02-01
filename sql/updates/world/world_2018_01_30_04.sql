-- Fixed Holy Concentration hitmask
UPDATE spell_proc SET HitMask = 0 WHERE SpellId = -34753;

-- Seed of corruption proc on procs damage
UPDATE spell_proc SET AttributesMask = 0x2 WHERE SpellId = -27243;
REPLACE INTO spell_template_override (entry, attributesEx3, COMMENT) VALUES (27243, 0x04000000, "Seed of corruption, add SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED");
