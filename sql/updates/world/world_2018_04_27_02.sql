-- Delete some useless entries, rank 1 exists
-- frost bolt
DELETE FROM spell_bonus_data WHERE entry IN (205,837,7322,8406,8407,8408,10179,10180,10181,25304,27071,27072);
--pyroblast
DELETE FROM spell_bonus_data WHERE entry IN (12505, 12522, 12523, 12524,12525,12526,18809,27132,33938);
-- Life tap
DELETE FROM spell_bonus_data WHERE entry IN (1455, 1456, 11687, 11688, 11689, 27222);
-- Soul Fire
DELETE FROM spell_bonus_data WHERE entry IN (17924, 27211, 30545);
-- Curse of agony
DELETE FROM spell_bonus_data WHERE entry IN (1014, 6217,11711, 11712,11713,27218);
-- Drain mana
DELETE FROM spell_bonus_data WHERE entry IN (6226, 11703,11704,27221,30908);
-- Drain soul
DELETE FROM spell_bonus_data WHERE entry IN (8288, 8289, 11675, 27217);
-- Holy Nova
DELETE FROM spell_bonus_data WHERE entry IN (23458, 23459, 25329, 27803, 27804, 27805);
-- Shadowguard
DELETE FROM spell_bonus_data WHERE entry IN (28378, 28379, 28380, 28381, 28382, 28385);
-- Touch of Weakeness
DELETE FROM spell_bonus_data WHERE entry IN (19249, 19251, 19252, 19253, 19254, 25460);
-- Regrowth
DELETE FROM spell_bonus_data WHERE entry IN (8938, 8939, 8940, 8941, 9750, 9856, 9857, 9858, 26980);
-- Blessing of Sanctuary
DELETE FROM spell_bonus_data WHERE entry IN (20912, 20913, 20914, 27168);
-- Earth Shield
DELETE FROM spell_bonus_data WHERE entry IN (32593, 32594);