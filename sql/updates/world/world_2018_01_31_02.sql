-- Shaman Tier 6 Trinket
UPDATE spell_proc SET SpellFamilyMask = 68719476865 WHERE SpellId = 40463;

REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (19184, 0x04000000, "Add SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED to hunter Entrapment talent");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (19387, 0x04000000, "Add SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED to hunter Entrapment talent");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (19388, 0x04000000, "Add SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED to hunter Entrapment talent");
 
UPDATE spell_proc SET HitMask = 1 WHERE SpellId = -19184;

REPLACE INTO spell_script_names VALUES (-19184, "spell_hun_entrapment");