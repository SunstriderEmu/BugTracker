
REPLACE INTO spell_script_names VALUES (-27285, "spell_warl_seed_of_corruption_proc");
REPLACE INTO spell_script_names VALUES (5246, "spell_warr_intimidating_shout");
REPLACE INTO spell_script_names VALUES (44866, "spell_kalecgos_spectral_blast2");

REPLACE INTO spell_script_names VALUES (37476, "spell_chess_cleave");
REPLACE INTO spell_script_names VALUES (37474, "spell_chess_cleave");
DELETE FROM spell_template_override WHERE entry IN (37454, 37461);
REPLACE INTO spell_script_names VALUES (37454, "spell_chess_3_front");
REPLACE INTO spell_script_names VALUES (37461, "spell_chess_3_front");
REPLACE INTO spell_script_names VALUES (37453, "spell_chess_3_front");
REPLACE INTO spell_script_names VALUES (37459, "spell_chess_3_front");
REPLACE INTO spell_script_names VALUES (37413, "spell_chess_front");
REPLACE INTO spell_script_names VALUES (37406, "spell_chess_front");


REPLACE INTO spell_script_names VALUES (-29441, "spell_mage_magic_absorption");
REPLACE INTO spell_script_names VALUES (-29074, "spell_mage_master_of_elements");
REPLACE INTO spell_script_names VALUES (-1463, "spell_mage_mana_shield"); 
REPLACE INTO spell_script_names VALUES (37424, "spell_mage_improved_mana_shield");
REPLACE INTO spell_script_names VALUES (-11119, "spell_mage_ignite");
REPLACE INTO spell_script_names VALUES (11129, "spell_mage_combustion");
REPLACE INTO spell_script_names VALUES (28682, "spell_mage_combustion_proc");

DELETE FROM spell_proc WHERE spellid = -1463;
REPLACE INTO spell_proc (SpellId, ProcFlags, SpellTypeMask, SpellPhaseMask, HitMask, AttributesMask, Chance) VALUES (37424, 0x00100000, 0x1, 0x0000002, 0x0000400, 0x0000002, 20);
UPDATE spell_proc SET SchoolMask = 0x4, SpellFamilyMask = 0, HitMask = 2 WHERE SpellId = 11129;