REPLACE INTO spell_script_names VALUES (-30108, "spell_unstable_affliction");
REPLACE INTO spell_script_names VALUES (43522, "spell_unstable_affliction");
-- Remove coef for proc, value is already calculated when casting the spell as custom spell
REPLACE INTO spell_bonus_data VALUES (31117, 0, 0, -1, -1, "Unstable Affliction dispel proc");