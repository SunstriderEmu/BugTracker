-- Remulos
UPDATE creature_template SET minhealth = 119000, maxhealth = 119000, minmana = 115000, maxmana = 115000, flags_extra = 262144, ScriptName = 'npc_keeper_remulos' WHERE entry = 11832;

-- Eranikus
UPDATE creature_template SET spell1 = 24839, spell2 = 24818, spell3 = 25586, spell4 = 0, unit_flags = 2, flags_extra = 262144, InhabitType = 5, RegenHealth = 0, ScriptName='npc_eranikus_tyrant_of_the_dream' WHERE entry = 15491;
DELETE FROM creature_template_addon WHERE entry = 15491;
INSERT INTO creature_template_addon VALUES (15491, 0, 0, 0, 0, 0, 0, 1536, '');

-- Nightmare phantasms
UPDATE creature_template SET faction_A = 14, faction_H = 14, spell1 = 17228, flags_extra = 262144, ScriptName = 'npc_nightmare_phantasm' WHERE entry = 15629;

-- Eranikus the Redeemed
UPDATE creature_template SET modelid_A = 6984, modelid_H = 6984, minhealth = 1665000, maxhealth = 1665000, RegenHealth = 0, flags_extra = 2 WHERE entry = 15628;

-- Tyrande
UPDATE creature_template SET minhealth = 900000, maxhealth = 100000, minmana = 67740, maxmana = 67740, ScriptName = 'npc_tyrande' WHERE entry = 15633;

-- Priestess of the moon
UPDATE creature_template SET rangeattacktime = 3000, rangedattackpower = 1466, minrangedmg = 1000, maxrangedmg = 2000, flags_extra = 262144, ScriptName = 'npc_priestess_of_the_moon' WHERE entry = 15634;
