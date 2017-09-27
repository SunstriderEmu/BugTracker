DELETE FROM creature_scripts WHERE entryorguid IN (11988, 11672);
INSERT INTO creature_scripts VALUES (11988, 'Boss_Golemagg');
INSERT INTO creature_scripts VALUES (11672, 'Mob_Core_Rager');

UPDATE creature_template SET AIName = 'NullCreatureAI', ScriptName = '' WHERE entry = 11988;
UPDATE creature_template SET AIName = 'NullCreatureAI', ScriptName = '' WHERE entry = 11672;

UPDATE `creature_template` SET 
    `mindmg` = 8000, 
    `maxdmg` = 10000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 11988;
