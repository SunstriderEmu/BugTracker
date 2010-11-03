UPDATE gameobject_template SET flags = 32, scriptname = "go_ethereum_chamber" WHERE name = "Ethereum Stasis Chamber";

UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry IN (22828, 22826, 22827, 20888, 22825);

UPDATE creature_template SET mindmg = 1251, maxdmg = 1602, attackpower = 658 WHERE entry = 20888;
UPDATE creature_template SET mindmg = 1002, maxdmg = 1282, attackpower = 527 WHERE entry = 22825;
UPDATE creature_template SET mindmg = 1348, maxdmg = 1727, attackpower = 710 WHERE entry = 22826;
UPDATE creature_template SET mindmg = 1251, maxdmg = 1602, attackpower = 658 WHERE entry = 22827;
UPDATE creature_template SET mindmg = 1618, maxdmg = 2074, attackpower = 852 WHERE entry = 22828;
