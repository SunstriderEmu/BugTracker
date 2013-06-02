DELETE FROM creature_scripts WHERE entryorguid = 12056;
INSERT INTO creature_scripts VALUES (12056, 'Boss_Baron_Geddon');

UPDATE creature_template SET minhealth = 586256, maxhealth = 586256, minmana = 0, maxmana = 0, AIName = 'NullCreatureAI', ScriptName = '' WHERE entry = 12056;
UPDATE `creature_template` SET 
    `mindmg` = 8000, 
    `maxdmg` = 10000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 12056;
