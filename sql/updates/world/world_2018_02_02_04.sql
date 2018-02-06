
REPLACE INTO spell_script_names VALUES (-31785, "spell_pal_spiritual_attunement");
REPLACE INTO spell_script_names VALUES (40470, "spell_pal_item_t6_trinket");
UPDATE spell_proc SET SpellFamilyMask = 3229614080, AttributesMask = 0x2 WHERE SpellId = 40470;
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (40470, 0x04000000 + 0x80000, "Added SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED flag to pal T6 trinket");

REPLACE INTO spell_script_names VALUES (28789, "spell_pal_t3_6p_bonus");
UPDATE spell_proc SET SpellFamilyMask = 3221225472, SpellTypeMask = 0x2, HitMask = 0 WHERE SpellId = 28789;
REPLACE INTO spell_script_names VALUES (31801, "spell_pal_seal_of_vengeance");
REPLACE INTO spell_script_names VALUES (31892, "spell_pal_seal_of_blood");
REPLACE INTO spell_script_names VALUES (-20154, "spell_pal_seal_of_righteousness");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (27156, 0x40000 | 0x20000000, "Added SPELL_ATTR3_NO_DONE_BONUS, calculation is done in script");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (25742, 0x40000 | 0x20000000, "Added SPELL_ATTR3_NO_DONE_BONUS, calculation is done in script");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (25740, 0x40000 | 0x20000000, "Added SPELL_ATTR3_NO_DONE_BONUS, calculation is done in script");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (25739, 0x40000 | 0x20000000, "Added SPELL_ATTR3_NO_DONE_BONUS, calculation is done in script");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (25738, 0x40000 | 0x20000000, "Added SPELL_ATTR3_NO_DONE_BONUS, calculation is done in script");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (25737, 0x40000 | 0x20000000, "Added SPELL_ATTR3_NO_DONE_BONUS, calculation is done in script");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (25736, 0x40000 | 0x20000000, "Added SPELL_ATTR3_NO_DONE_BONUS, calculation is done in script");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (25735, 0x40000 | 0x20000000, "Added SPELL_ATTR3_NO_DONE_BONUS, calculation is done in script");
REPLACE INTO spell_template_override (entry, AttributesEx3, Comment) VALUES (25713, 0x40000 | 0x20000000, "Added SPELL_ATTR3_NO_DONE_BONUS, calculation is done in script");
REPLACE INTO spell_ranks VALUES (21084, 21084, 1);
REPLACE INTO spell_ranks VALUES (21084, 20287, 2);
REPLACE INTO spell_ranks VALUES (21084, 20288, 3);
REPLACE INTO spell_ranks VALUES (21084, 20289, 4);
REPLACE INTO spell_ranks VALUES (21084, 20290, 5);
REPLACE INTO spell_ranks VALUES (21084, 20291, 6);
REPLACE INTO spell_ranks VALUES (21084, 20292, 7);
REPLACE INTO spell_ranks VALUES (21084, 20293, 8);
REPLACE INTO spell_ranks VALUES (21084, 27155, 9);
REPLACE INTO spell_script_names VALUES (-21084, "spell_pal_seal_of_righteousness");
REPLACE INTO spell_script_names VALUES (20375, "spell_pal_seal");
REPLACE INTO spell_script_names VALUES (21084, "spell_pal_seal");
REPLACE INTO spell_script_names VALUES (31801, "spell_pal_seal");
REPLACE INTO spell_script_names VALUES (31892, "spell_pal_seal");
REPLACE INTO spell_script_names VALUES (33127, "spell_pal_seal");
REPLACE INTO spell_script_names VALUES (38008, "spell_pal_seal");
REPLACE INTO spell_script_names VALUES (41459, "spell_pal_seal");

REPLACE INTO spell_script_names VALUES (-20210, "spell_pal_illumination");
REPLACE INTO spell_script_names VALUES (37705, "spell_pal_item_healing_discount");
REPLACE INTO spell_proc VALUES (37705, 0, 0, 0, 0x4000, 0x2, 0x2, 0, 0, 0, 2, 0, 0);
REPLACE INTO spell_proc VALUES (37706, 0, 0, 0, 0x4000, 0x2, 0x2, 0, 0, 0, 0, 0, 0);
DELETE FROM spell_affect WHERE entry = 37706;
REPLACE INTO spell_template_override (entry, SpellFamilyName, Comment) VALUES (37706, 0, "Removed priest family name from spell, should proc for all classes");
REPLACE INTO spell_script_names VALUES (-20185, "spell_pal_judgement_of_light_heal");
REPLACE INTO spell_script_names VALUES (-20186, "spell_pal_judgement_of_wisdom_mana");


-- check avec les familyspellflags 2 et 3
