-- fixed some more wrong spell_procs
UPDATE spell_proc SET SpellFamilyMask = 0 WHERE SpellFamilyName = 0 OR SpellId IN (16164);
UPDATE spell_proc SET SpellFamilyMask = 2097185 WHERE SpellId IN (22007);

REPLACE INTO spell_script_names VALUES (40442, "spell_dru_item_t6_trinket");
REPLACE INTO spell_script_names VALUES (28719, "spell_dru_t3_8p_bonus");
UPDATE spell_proc SET SpellFamilyMask = 32 WHERE SpellId = 28719;
REPLACE INTO spell_script_names VALUES (28847, "spell_item_healing_touch_refund");
UPDATE spell_proc SET SpellFamilyMask = 32 WHERE SpellId = 28847;
REPLACE INTO spell_script_names VALUES (37288, "spell_dru_t4_2p_bonus");
REPLACE INTO spell_script_names VALUES (37295, "spell_dru_t4_2p_bonus");
REPLACE INTO spell_script_names VALUES (37336, "spell_dru_forms_trinket");
