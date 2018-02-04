
REPLACE INTO spell_script_names VALUES (-18094, "spell_warl_nightfall");
REPLACE INTO spell_script_names VALUES (-30293, "spell_warl_soul_leech");
REPLACE INTO spell_script_names VALUES (37377, "spell_warl_t4_2p_bonus_shadow");
REPLACE INTO spell_script_names VALUES (39437, "spell_warl_t4_2p_bonus_fire");
REPLACE INTO spell_script_names VALUES (37381, "spell_item_pet_healing");

UPDATE spell_proc SET HitMask = 0x2 WHERE Spellid = -17793;
UPDATE spell_proc SET SpellFamilyMask = 0 WHERE SpellId IN (37377, 39437);