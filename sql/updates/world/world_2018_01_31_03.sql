-- Pyroclasm can prog on triggered (for hellfire)
UPDATE spell_proc SET AttributesMask = 0x2 WHERE SpellId = -18096;

REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (20335, 0x04000000, "Add SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED to Heart of the Crusader");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (20336, 0x04000000, "Add SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED to Heart of the Crusader");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (20337, 0x04000000, "Add SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED to Heart of the Crusader");
 
 
REPLACE INTO spell_script_names VALUES (-18096, "spell_warl_pyroclasm");
REPLACE INTO spell_script_names VALUES (-1120, "spell_warl_drainsoul");
REPLACE INTO spell_script_names VALUES (-27243, "spell_warl_seed_of_corruption");

-- some creatures seed of corruptions
REPLACE INTO spell_script_names VALUES (32863, "spell_warl_seed_of_corruption");
REPLACE INTO spell_script_names VALUES (32865, "spell_warl_seed_of_corruption");
REPLACE INTO spell_script_names VALUES (36123, "spell_warl_seed_of_corruption");
REPLACE INTO spell_script_names VALUES (38252, "spell_warl_seed_of_corruption");
REPLACE INTO spell_script_names VALUES (39367, "spell_warl_seed_of_corruption");
REPLACE INTO spell_script_names VALUES (44141, "spell_warl_seed_of_corruption");
