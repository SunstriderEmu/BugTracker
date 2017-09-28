UPDATE spell_template SET effectBasePoints1 = effectBasePoints1 * 2, effectDieSides1 = effectDieSides1 * 2 WHERE id = 26093;
UPDATE creature_template SET speed = 1.5 where entry = 15517;
UPDATE creature_template SET minlevel = 73,maxlevel = 73,minhealth = 50000,maxhealth = 50000,faction_A = 14,faction_H = 14,speed = 1.5, ScriptName = 'boss_ouro_mound' where entry = 15712;
UPDATE creature_template SET mindmg = 220, maxdmg = 270, attackpower = 430 where entry = 15718;
