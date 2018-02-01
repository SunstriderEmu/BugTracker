-- Fix some warnings
DELETE FROM spell_ranks WHERE first_spell_id IN (1038, 20217, 25895, 25898);
REPLACE INTO spell_script_names VALUES (20577, "spell_gen_cannibalize");

-- Drain Soul spell group fix
DELETE FROM spell_group WHERE id IN (1123, 1124, 1125, 1126);
REPLACE INTO spell_group VALUES (1123, 1120);
DELETE FROM spell_group_stack_rules WHERE group_id IN (1124, 1125, 1126);

DELETE FROM spell_ranks WHERE spell_id IN (10660, 10658, 10656, 28672, 28675, 28677, 31896);