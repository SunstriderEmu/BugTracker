# SmartAIMgr: Entry 23438 SourceType 0 Event 0 Action 33 Kill Credit: There is a killcredit spell for creatureEntry 23438 (SpellId: 41427 effect: 0)
-- NPC 23438
SET @ENTRY = 23438;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 11, 41427, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 'Nether Ray Feed Credit - On Just Summoned - Cast "<a href="http://wowhead.com/spell=41427">Lucille Feed Credit Trigger</a>" '),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 19, 4, 23439, 10, 0, 0, 0, 0, 0, 'Nether Ray Feed Credit - On Just Summoned - Set Data 0 1 '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nether Ray Feed Credit - On Just Summoned - Despawn In 1000ms ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 50001 SourceType 0, Event 2, Missing Repeat flag.
DELETE FROM smart_scripts WHERE entryorguid = 50001 AND source_type = 0;

# SmartAIMgr::LoadSmartAIFromDB: Entry 50004 SourceType 0, Event 5, Missing Repeat flag.
DELETE FROM smart_scripts WHERE entryorguid = 50004 AND source_type = 0;

# SmartAIMgr: Entry 50005 SourceType 0 Event 0 Action 43 uses non-existent Model id 5, skipped.
DELETE FROM smart_scripts WHERE entryorguid = 50005 AND source_type = 0;

# SmartAIMgr: EntryOrGuid 50115 using event(3) has invalid action type (0), skipped.
DELETE FROM smart_scripts WHERE entryorguid = 50115 AND source_type = 0 AND id = 3;

# SmartAIMgr::LoadSmartAIFromDB: Entry 50116 SourceType 0, Event 5, Missing Repeat flag.
# SmartAIMgr::LoadSmartAIFromDB: Entry 50116 SourceType 0, Event 6, Missing Repeat flag.
-- NPC 50116
SET @ENTRY = 50116;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 53, 0, 1741701, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Respawn - Start Waypoint 1741701 '),
  (@ENTRY, 0, 1, 2, 40, 0, 100, 0, 2, 1741701, 0, 0, 54, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Waypoint 2 Reached - Pause Waypoint 10000ms '),
  (@ENTRY, 0, 2, 3, 61, 0, 100, 0, 2, 1741701, 0, 0, 80, 5011601, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Waypoint 2 Reached - Run Script <a href="/smartai/script/5011601">5011601</a> '),
  (@ENTRY, 0, 3, 4, 40, 0, 100, 0, 3, 1741701, 0, 0, 55, 0, 0, 0, 0, 0, 0, 1, 0, 17418, 0, 15, 0, 0, 0, 0, 'Mag&#039;har Escort - On Waypoint 3 Reached - Stop Waypoint '),
  (@ENTRY, 0, 4, 0, 61, 0, 100, 0, 3, 1741701, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Waypoint 3 Reached - Set Event Phase 1 '),
  (@ENTRY, 0, 5, 0, 103, 1, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 0, 17418, 0, 10, 0, 0, 0, 0, 'Mag&#039;har Escort - On Enter Phase 0 - Start Attacking (Phase 1)'),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 0, 0, 0, 0, 0, 39, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Aggro - Call For Help ');

# SmartAIMgr: Entry 153556 SourceType 1 Event 0 Action 86 uses non-existent Spell entry 153556, skipped.
DELETE FROM smart_scripts WHERE entryorguid = 153556 AND source_type = 1;

# SmartAIMgr: EntryOrGuid 182164, event type 54 can not be used for Script type 1
# SmartAIMgr: EntryOrGuid 182164, event type 54 can not be used for Script type 1
-- GO 182164
SET @ENTRY = 182164;
UPDATE gameobject_template SET AIName='SmartGameObjectAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 1;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 1, 0, 0, 63, 0, 100, 0, 0, 0, 0, 0, 11, 24985, 2, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1177.52, 8130.9, 19.5231, 1.0651, 'Murloc Cage - On Just Created - Cast "<a href="http://wowhead.com/spell=24985">Summon Baby Murloc (Blue)</a>" '),
  (@ENTRY, 1, 1, 0, 63, 0, 100, 0, 0, 0, 0, 0, 12, 18152, 2, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1178.42, 8130.27, 19.5962, 1.10437, 'Murloc Cage - On Just Created - Summon "<a href="http://wowhead.com/npc=18152">Baby Murloc</a>" '),
  (@ENTRY, 1, 2, 0, 63, 0, 100, 0, 0, 0, 0, 0, 11, 24989, 2, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1179.26, 8130.01, 19.6145, 0.96507, 'Murloc Cage - On Just Created - Cast "<a href="http://wowhead.com/spell=24989">Summon Baby Murloc (Pink)</a>" '),
  (@ENTRY, 1, 3, 0, 63, 0, 100, 0, 0, 0, 0, 0, 12, 18152, 2, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1180.14, 8129.44, 19.5593, 1.02005, 'Murloc Cage - On Just Created - Summon "<a href="http://wowhead.com/npc=18152">Baby Murloc</a>" ');

# SmartAIMgr: Entry 186332 SourceType 1 Event 0 Action 12 creature summon: There is a summon spell for creature entry 23786 (SpellId: 42421, effect: 0)
-- GO 186332
SET @ENTRY = 186332;
UPDATE gameobject_template SET AIName='SmartGameObjectAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 1;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 1, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 11, 42421, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ogre Remains - On Gossip Hello - Cast "<a href="http://wowhead.com/spell=42421">Summon Stonemaul Spirit</a>" ');

# SmartAIMgr: Entry 1741000 SourceType 9 Event 102 Action 11 uses min/max params wrong (7000/0), skipped.
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 25035, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Stillpine Ancestor Vark - In Combat - Cast "<a href="http://wowhead.com/spell=25035">Elemental Spawn-in</a>" '),
  (@ENTRY, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Stillpine Ancestor Vark - In Combat - Say Line 0 '),
  (@ENTRY, 9, 102, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 11, 25035, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Stillpine Ancestor Vark - In Combat - Cast "<a href="http://wowhead.com/spell=25035">Elemental Spawn-in</a>" ');

# SmartAIMgr: Entry 1811000 SourceType 9 Event 9 Action 12 creature summon: There is a summon spell for creature entry 18109 (SpellId: 31928, effect: 0)
UPDATE smart_scripts SET action_type = 11, action_param1 = 31928, action_param2 = 0, action_param3 = 0, action_param4 = 0, action_param5 = 0, action_param6 = 0 WHERE entryorguid = 1811000 AND source_type = 9 AND id = 9;

# SmartAIMgr: Entry 1814200 SourceType 9 Event 7 Action 12 creature summon: There is a summon spell for creature entry 18109 (SpellId: 31928, effect: 0)
UPDATE smart_scripts SET action_type = 11, action_param1 = 31928, action_param2 = 0, action_param3 = 0, action_param4 = 0, action_param5 = 0, action_param6 = 0 WHERE entryorguid = 1814200 AND source_type = 9 AND id = 7;

# SmartAIMgr: Entry 1814300 SourceType 9 Event 7 Action 12 creature summon: There is a summon spell for creature entry 18109 (SpellId: 31928, effect: 0)
UPDATE smart_scripts SET action_type = 11, action_param1 = 31928, action_param2 = 0, action_param3 = 0, action_param4 = 0, action_param5 = 0, action_param6 = 0 WHERE entryorguid = 1814300 AND source_type = 9 AND id = 7;

# SmartAIMgr: Entry 1814400 SourceType 9 Event 6 Action 12 creature summon: There is a summon spell for creature entry 18109 (SpellId: 31928, effect: 0)
UPDATE smart_scripts SET action_type = 11, action_param1 = 31928, action_param2 = 0, action_param3 = 0, action_param4 = 0, action_param5 = 0, action_param6 = 0 WHERE entryorguid = 1814400 AND source_type = 9 AND id = 6;

# SmartAIMgr: Warning: Entry 1824000 SourceType 9 Event 1 Action 50 gameobject summon: There is a summon spell for gameobject entry 182533 (SpellId: 30928, effect: 0)
UPDATE smart_scripts SET action_type = 11, action_param1 = 30928, action_param2 = 0, action_param3 = 0, action_param4 = 0, action_param5 = 0, action_param6 = 0 WHERE entryorguid = 1824000 AND source_type = 9 AND id = 1;

# SmartAIMgr: Entry 1921000 SourceType 9 Event 2 Action 26 uses non-existent Quest entry 19210, skipped.
UPDATE smart_scripts SET action_param1 = 10011 WHERE entryorguid = 1921000 AND source_type = 9 AND id = 2;

# SmartAIMgr: Warning: Entry 2020601 SourceType 9 Event 2 Action 50 gameobject summon: There is a summon spell for gameobject entry 185303 (SpellId: 39216, effect: 0)
UPDATE smart_scripts SET action_type = 11, action_param1 = 39216, action_param2 = 0, action_param3 = 0, action_param4 = 0, action_param5 = 0, action_param6 = 0 WHERE entryorguid = 2020601 AND source_type = 9 AND id = 2;

# SmartAIMgr: Warning: Entry 2020602 SourceType 9 Event 2 Action 50 gameobject summon: There is a summon spell for gameobject entry 185303 (SpellId: 39216, effect: 0)
UPDATE smart_scripts SET action_type = 11, action_param1 = 39216, action_param2 = 0, action_param3 = 0, action_param4 = 0, action_param5 = 0, action_param6 = 0 WHERE entryorguid = 2020602 AND source_type = 9 AND id = 2;

# SmartAIMgr: Warning: Entry 2020603 SourceType 9 Event 2 Action 50 gameobject summon: There is a summon spell for gameobject entry 185303 (SpellId: 39216, effect: 0)
UPDATE smart_scripts SET action_type = 11, action_param1 = 39216, action_param2 = 0, action_param3 = 0, action_param4 = 0, action_param5 = 0, action_param6 = 0 WHERE entryorguid = 2020603 AND source_type = 9 AND id = 2;

# SmartAIMgr: Entry 2021806 SourceType 9 Event 0 Action 66 uses min/max params wrong (1/0), skipped.
UPDATE smart_scripts SET event_param1 = 0 WHERE entryorguid = 2021806 AND source_type = 9 AND id = 0;

# SmartAIMgr: Entry 2127901 SourceType 9 Event 4 Action 12 creature summon: There is a summon spell for creature entry 21306 (SpellId: 36555, effect: 0)
UPDATE smart_scripts SET action_type = 11, action_param1 = 36555, action_param2 = 0, action_param3 = 0, action_param4 = 0, action_param5 = 0, action_param6 = 0 WHERE entryorguid = 2127901 AND source_type = 9 AND id = 4;

# SmartAIMgr: Entry 2141100 SourceType 9 Event 8 Action 11 uses non-existent Spell entry 0, skipped.
# SmartAIMgr: Entry 2141100 SourceType 9 Event 9 Action 11 uses non-existent Spell entry 0, skipped.
SET @ENTRY = 21411;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s cracks the rotten egg open and - to the horror and dismay of all around him - begins to drink from its putrid core.", 16, 0, 100, 7, 0, "Tobias the Filth Gorger - "),
  (@ENTRY, 1, 0, "That was life-changing... Excuse me for one minute.", 12, 0, 100, 273, 0, "Tobias the Filth Gorger - "),
  (@ENTRY, 2, 0, "%s lets loose the most foul belch ever heard or smelled.", 16, 0, 100, 15, 0, "Tobias the Filth Gorger - "),
  (@ENTRY, 3, 0, "Ok then, back to business.", 12, 0, 100, 1, 0, "Tobias the Filth Gorger - ");
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Set NPC Flag Quest Giver '),
  (@ENTRY, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Set Run Off '),
  (@ENTRY, 9, 10, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Say Line 0 '),
  (@ENTRY, 9, 20, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Play Emote 7 '),
  (@ENTRY, 9, 30, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Play Emote 7 '),
  (@ENTRY, 9, 40, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 66, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Set Orientation 0 '),
  (@ENTRY, 9, 50, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Say Line 1 '),
  (@ENTRY, 9, 60, 0, 0, 0, 100, 0, 1500, 1500, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2079.63, 5296.84, -37.3236, 5.17342, 'Tobias the Filth Gorger - In Combat - Move To Pos '),
  (@ENTRY, 9, 70, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Say Line 2 '),
  (@ENTRY, 9, 80, 0, 0, 0, 100, 0, 0, 0, 0, 0, 75, 36823, 0, 0, 0, 0, 0, 9, 0, 0, 0, 80, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Add Aura "<a href="http://wowhead.com/spell=36823">Overwhelming Odor</a>" '),
  (@ENTRY, 9, 90, 0, 0, 0, 100, 0, 0, 0, 0, 0, 75, 36823, 0, 0, 0, 0, 0, 17, 0, 0, 80, 80, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Add Aura "<a href="http://wowhead.com/spell=36823">Overwhelming Odor</a>" '),
  (@ENTRY, 9, 91, 0, 0, 0, 100, 0, 0, 0, 0, 0, 75, 36823, 0, 0, 0, 0, 0, 1, 0, 0, 0, 80, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Add Aura "<a href="http://wowhead.com/spell=36823">Overwhelming Odor</a>" '),
  (@ENTRY, 9, 100, 0, 0, 0, 100, 0, 8000, 8000, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2083.83, 5299.95, -37.3236, 0.314159, 'Tobias the Filth Gorger - In Combat - Move To Pos '),
  (@ENTRY, 9, 101, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Say Line 3 '),
  (@ENTRY, 9, 102, 0, 0, 0, 100, 0, 0, 0, 0, 0, 81, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tobias the Filth Gorger - In Combat - Set NPC Flag Quest Giver ');

# SmartAIMgr: Warning: Entry 2309300 SourceType 9 Event 1 Action 50 gameobject summon: There is a summon spell for gameobject entry 185856 (SpellId: 40164, effect: 0) -- Complete rescript of the quest "The Soul Cannon of Reth'hedron"
DELETE FROM gameobject WHERE id = 185863;
INSERT INTO gameobject (guid, id, map, spawnMask, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state, ScriptName) VALUES
  (81394,	185863,	530,	1,	-2466.34,	4700.5,	155.796,	3.20174,	0,	0,	0.999548,	-0.0300692,	25,	0,	1,	'');
DELETE FROM gossip_menu_option WHERE menu_id = 11030;
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, OptionBroadcastTextID, option_id, npc_option_npcflag, action_menu_id, action_poi_id, box_coded, box_money, box_text, BoxBroadcastTextID) VALUES
  (11030, 0, 0, 'I am an envoy of Balthas. He has sent me to collect a flawless arcane essence.', 0, 1, 1, NULL, 0, 0, 0, NULL, 0);
-- NPC 23093
SET @ENTRY = 23093;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "So my blood was not a sufficient payment, eh? Fine, let us recover your arcane essence. After this, I owe Balthas nothing.", 12, 0, 100, 1, 0, "Sar'this"),
  (@ENTRY, 1, 0, "%s places a fetish at the ritual pile.", 16, 0, 100, 1, 0, "Sar'this"),
  (@ENTRY, 2, 0, "The process is arduous. We must first summon forth acolytes of the elements. You must then destroy these acolytes so that my minions can make preparations.", 12, 0, 100, 1, 0, "Sar'this"),
  (@ENTRY, 3, 0, "Well done! Let's continue.", 12, 0, 100, 1, 0, "Sar'this"),
  (@ENTRY, 4, 0, "Prepare yourself! The acolyte of water is soon to come...", 12, 0, 100, 1, 0, "Sar'this"),
  (@ENTRY, 5, 0, "Come forth, acolyte of earth!", 12, 0, 100, 1, 0, "Sar'this"),
  (@ENTRY, 6, 0, "Fire, show yourself!", 12, 0, 100, 1, 0, "Sar'this"),
  (@ENTRY, 7, 0, "Now we call forth the arcane acolyte.", 12, 0, 100, 1, 0, "Sar'this"),
  (@ENTRY, 8, 0, "It is yours my Lord!", 12, 0, 100, 1, 0, "Sar'this");
UPDATE creature_template SET AIName='SmartAI', ScriptName='', flags_extra = 262144 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 62, 0, 100, 0, 11030, 0, 0, 0, 80, 2309301, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, -2473.52, 4699.96, 155.472, 0, 'Sar&#039;this - On Gossip 11030 Option 0 Selected - Run Script <a href="/smartai/script/2309301">2309301</a> '),
  (@ENTRY, 0, 1, 0, 40, 0, 100, 0, 3, 23093, 0, 0, 80, 2309302, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Waypoint 3 Reached - Run Script <a href="/smartai/script/2309302">2309302</a> '),
  (@ENTRY, 0, 2, 0, 40, 0, 100, 0, 5, 23093, 0, 0, 80, 2309303, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Waypoint 5 Reached - Run Script <a href="/smartai/script/2309303">2309303</a> '),
  (@ENTRY, 0, 3, 0, 38, 0, 100, 0, 1, 1, 0, 0, 80, 2309304, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Data Set 1 1 - Run Script <a href="/smartai/script/2309304">2309304</a> '),
  (@ENTRY, 0, 4, 0, 40, 0, 100, 0, 5, 2309301, 0, 0, 80, 2309305, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Waypoint 5 Reached - Run Script <a href="/smartai/script/2309305">2309305</a> '),
  (@ENTRY, 0, 5, 0, 38, 0, 100, 0, 2, 1, 0, 0, 80, 2309306, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Data Set 2 1 - Run Script <a href="/smartai/script/2309306">2309306</a> '),
  (@ENTRY, 0, 6, 0, 40, 0, 100, 0, 6, 2309302, 0, 0, 80, 2309307, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Waypoint 6 Reached - Run Script <a href="/smartai/script/2309307">2309307</a> '),
  (@ENTRY, 0, 7, 0, 38, 0, 100, 0, 3, 1, 0, 0, 80, 2309308, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Data Set 3 1 - Run Script <a href="/smartai/script/2309308">2309308</a> '),
  (@ENTRY, 0, 8, 0, 40, 0, 100, 0, 6, 2309303, 0, 0, 80, 2309309, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Waypoint 6 Reached - Run Script <a href="/smartai/script/2309309">2309309</a> '),
  (@ENTRY, 0, 9, 0, 38, 0, 100, 0, 4, 1, 0, 0, 80, 2309310, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Data Set 4 1 - Run Script <a href="/smartai/script/2309310">2309310</a> '),
  (@ENTRY, 0, 10, 0, 40, 0, 100, 0, 13, 2309304, 0, 0, 80, 2309311, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Waypoint 13 Reached - Run Script <a href="/smartai/script/2309311">2309311</a> '),
  (@ENTRY, 0, 11, 12, 38, 0, 100, 0, 6, 6, 0, 0, 28, 40129, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Data Set 6 6 - Remove Aura "<a href="http://wowhead.com/spell=40129">Summon Air Elemental</a>" '),
  (@ENTRY, 0, 12, 0, 61, 0, 100, 0, 6, 6, 0, 0, 69, 66, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2528.15, 4661.22, 170.499, 5.55015, 'Sar&#039;this - On Data Set 6 6 - Move To Pos '),
  (@ENTRY, 0, 13, 14, 34, 0, 100, 0, 0, 66, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Reached Point 66 - Evade '),
  (@ENTRY, 0, 14, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - On Reached Point 66 - Set NPC Flag Gossip ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100 AND source_type = 9;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Store Targetlist 1 '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Close Gossip '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Set NPC Flag Gossip '),
  (@ENTRY*100+1, 9, 103, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 104, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 53, 0, 23093, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Start Waypoint 23093 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+2 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+2, 9, 200, 0, 0, 0, 100, 0, 0, 0, 0, 0, 54, 9000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Pause Waypoint 9000ms '),
  (@ENTRY*100+2, 9, 201, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 1 '),
  (@ENTRY*100+2, 9, 202, 0, 0, 0, 100, 0, 1500, 1500, 0, 0, 50, 185856, 290000, 0, 0, 0, 0, 14, 0, 81394, 185863, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Summon GO "<a href="http://wowhead.com/object=185856">Fetish of Sar"this</a>" '),
  (@ENTRY*100+2, 9, 203, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 10, 0, 94883, 23094, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Set Event Phase 1 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+3 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+3, 9, 300, 0, 0, 0, 100, 0, 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Stop Waypoint '),
  (@ENTRY*100+3, 9, 301, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 2 '),
  (@ENTRY*100+3, 9, 302, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 40129, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Cast "<a href="http://wowhead.com/spell=40129">Summon Air Elemental</a>" ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+4 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+4, 9, 400, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 3 '),
  (@ENTRY*100+4, 9, 401, 0, 0, 0, 100, 0, 0, 0, 0, 0, 28, 40129, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Remove Aura "<a href="http://wowhead.com/spell=40129">Summon Air Elemental</a>" '),
  (@ENTRY*100+4, 9, 402, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 10, 0, 94884, 23094, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Set Event Phase 2 '),
  (@ENTRY*100+4, 9, 403, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 53, 0, 2309301, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Start Waypoint 2309301 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+5 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+5, 9, 500, 0, 0, 0, 100, 0, 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Stop Waypoint '),
  (@ENTRY*100+5, 9, 501, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 4 '),
  (@ENTRY*100+5, 9, 502, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 40130, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Cast "<a href="http://wowhead.com/spell=40130">Summon Water Elemental</a>" ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+6 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+6, 9, 600, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 3 '),
  (@ENTRY*100+6, 9, 601, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 3, 0, 0, 0, 0, 0, 10, 0, 94885, 23094, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Set Event Phase 3 '),
  (@ENTRY*100+6, 9, 602, 0, 0, 0, 100, 0, 0, 0, 0, 0, 53, 0, 2309302, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Start Waypoint 2309302 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+7 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+7, 9, 700, 0, 0, 0, 100, 0, 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Stop Waypoint '),
  (@ENTRY*100+7, 9, 701, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 5 '),
  (@ENTRY*100+7, 9, 702, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 40132, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Cast "<a href="http://wowhead.com/spell=40132">Summon Earth Elemental</a>" ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+8 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+8, 9, 800, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 3 '),
  (@ENTRY*100+8, 9, 801, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 4, 0, 0, 0, 0, 0, 10, 0, 94886, 23094, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Set Event Phase 4 '),
  (@ENTRY*100+8, 9, 802, 0, 0, 0, 100, 0, 0, 0, 0, 0, 53, 0, 2309303, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Start Waypoint 2309303 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+9 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+9, 9, 900, 0, 0, 0, 100, 0, 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Stop Waypoint '),
  (@ENTRY*100+9, 9, 901, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 6 '),
  (@ENTRY*100+9, 9, 902, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 40133, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Cast "<a href="http://wowhead.com/spell=40133">Summon Fire Elemental</a>" ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+10 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+10, 9, 1000, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 3 '),
  (@ENTRY*100+10, 9, 1001, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 53, 0, 2309304, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Start Waypoint 2309304 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+11 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+11, 9, 1100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Stop Waypoint '),
  (@ENTRY*100+11, 9, 1101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 7 '),
  (@ENTRY*100+11, 9, 1102, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 40134, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Cast "<a href="http://wowhead.com/spell=40134">Summon Arcane Elemental</a>" '),
  (@ENTRY*100+11, 9, 1103, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 0, 23100, 20, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 0 '),
  (@ENTRY*100+11, 9, 1104, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Say Line 8 '),
  (@ENTRY*100+11, 9, 1105, 0, 0, 0, 100, 0, 0, 0, 0, 0, 60, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Disable Gravity '),
  (@ENTRY*100+11, 9, 1106, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2465.16, 4700.42, 159.762, 0.009885, 'Sar&#039;this - In Combat - Move To Pos '),
  (@ENTRY*100+11, 9, 1107, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 19, 33554688, 0, 0, 0, 0, 0, 19, 0, 23100, 5, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Set Unit Flag Immune to PC and  Not Selectable '),
  (@ENTRY*100+11, 9, 1108, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sar&#039;this - In Combat - Despawn Instant ');
# Path 1 -- Start, summon fetish + summon air elemental
DELETE FROM waypoints WHERE entry = @ENTRY;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (@ENTRY,	1,	-2528.15,	4661.22,	170.497,	'Sar\'this'),
  (@ENTRY,	2,	-2495.94,	4677.74,	159.028,	'Sar\'this'),
  (@ENTRY,	3,	-2472.57, 4699.87,  155.633,	'Sar\'this'),
  (@ENTRY,	4,	-2478.02,	4669.91,	159.283,	'Sar\'this'),
  (@ENTRY,	5,	-2481.19,	4665.16,	160.551,	'Sar\'this');
# Path 2 -- Summon water elemental
DELETE FROM waypoints WHERE entry = @ENTRY*100+1;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (@ENTRY*100+1,	1,	-2481.19,	4665.16,	160.551,	'Sar\'this'),
  (@ENTRY*100+1,	2,	-2451.59,	4661.5,	  160.278,	'Sar\'this'),
  (@ENTRY*100+1,	3,	-2434.28,	4654.77,	160.582,	'Sar\'this'),
  (@ENTRY*100+1,	4,	-2433.41,	4650.76,	160.633,	'Sar\'this'),
  (@ENTRY*100+1,	5,	-2440.39,	4639.58,	158.108,	'Sar\'this');
# Path 3 -- Summon earth elemental
DELETE FROM waypoints WHERE entry = @ENTRY*100+2;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (@ENTRY*100+2,	1,	-2440.39,	4639.58,	158.108,	'Sar\'this'),
  (@ENTRY*100+2,	2,	-2430.42,	4652.01,	160.568,	'Sar\'this'),
  (@ENTRY*100+2,	3,	-2407.94,	4630.11,	160.36,	  'Sar\'this'),
  (@ENTRY*100+2,	4,	-2416.41,	4589.29,	160.543,	'Sar\'this'),
  (@ENTRY*100+2,	5,	-2396.04,	4578.73,	165.653,	'Sar\'this'),
  (@ENTRY*100+2,	6,	-2389.72,	4561.02,	165.151,	'Sar\'this');
# Path 4 -- Summon fire elemental
DELETE FROM waypoints WHERE entry = @ENTRY*100+3;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (@ENTRY*100+3,	1,	-2389.72,	4561.02,	165.151,	'Sar\'this'),
  (@ENTRY*100+3,	2,	-2390.17,	4548.29,	165.612,	'Sar\'this'),
  (@ENTRY*100+3,	3,	-2409.39,	4532.05,	166.064,	'Sar\'this'),
  (@ENTRY*100+3,	4,	-2421.99,	4505.39,	166.6,	  'Sar\'this'),
  (@ENTRY*100+3,	5,	-2428.29,	4482.35,	167.131,	'Sar\'this'),
  (@ENTRY*100+3,	6,	-2430.1,	4460.05,	166.106,	'Sar\'this');
# Path 5 -- Summon arcane elemental
DELETE FROM waypoints WHERE entry = @ENTRY*100+4;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (@ENTRY*100+4,	1,	-2430.1,	4460.05,	166.106,	'Sar\'this'),
  (@ENTRY*100+4,	2,	-2428.27,	4482.37,	167.133,	'Sar\'this'),
  (@ENTRY*100+4,	3,	-2421.38,	4507.43,	166.573,	'Sar\'this'),
  (@ENTRY*100+4,	4,	-2409.56,	4530.33,	166.118,	'Sar\'this'),
  (@ENTRY*100+4,	5,	-2392.02,	4547.83,	165.582,	'Sar\'this'),
  (@ENTRY*100+4,	6,	-2393.26,	4573.9,	  165.988,	'Sar\'this'),
  (@ENTRY*100+4,	7,	-2417.37,	4591.83,	160.521,	'Sar\'this'),
  (@ENTRY*100+4,	8,	-2408.31,	4622.44,	160.609,	'Sar\'this'),
  (@ENTRY*100+4,	9,	-2413.18,	4635.83,	160.454,	'Sar\'this'),
  (@ENTRY*100+4,	10,	-2435.94,	4657.05,	160.58,	  'Sar\'this'),
  (@ENTRY*100+4,	11,	-2478.02,	4666.97,	159.727,	'Sar\'this'),
  (@ENTRY*100+4,	12,	-2478.86,	4689.45,	155.416,	'Sar\'this'),
  (@ENTRY*100+4,	13,	-2469.89,	4700.31,	155.87,	  'Sar\'this');
DELETE FROM event_scripts WHERE id IN (14856,14857,14858,14859,14860);
INSERT INTO event_scripts (id, delay, command, datalong, datalong2, dataint, x, y, z, o) VALUES
  (14856,	0,	10,	23096,	120000,	0,	-2482.84,	4661.56,	161.6,	0.983774), -- Summon Acolyte of Air
  (14857,	0,	10,	23097,	120000,	0,	-2443.37,	4634.18,	158.2,	0.979847), -- Summon Acolyte of Water
  (14858,	0,	10,	23098,	120000,	0,	-2384.31,	4554.57,	165.9,	2.091180), -- Summon Acolyte of Earth
  (14859,	0,	10,	23099,	120000,	0,	-2428.50,	4452.31,	166.2,	1.831991), -- Summon Acolyte of Fire
  (14860,	0,	10,	23100,	120000,	0,	-2467.10,	4700.37,	155.7,	3.265357); -- Summon Arcane Elemental

-- NPC 23096
SET @ENTRY = 23096;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 6, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, 0, 94882, 23093, 0, 0, 0, 0, 0, 'Acolyte of Air - On Death - Set Data 1 1 '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 40156, 2, 0, 0, 0, 0, 10, 0, 94883, 23094, 0, 0, 0, 0, 0, 'Acolyte of Air - On Death - Cast "<a href="http://wowhead.com/spell=40156">Essence of Wind</a>" '),
  (@ENTRY, 0, 10, 0, 60, 0, 100, 1, 119000, 119000, 0, 0, 45, 6, 6, 0, 0, 0, 0, 10, 0, 94882, 23093, 0, 0, 0, 0, 0, 'Acolyte of Air - On Update - Set Data 6 6 (No Repeat)');
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 40156 AND ConditionTypeOrReference = 31 AND ConditionValue1 = 3 AND ConditionValue2 = 23094;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
  (13,	1,	40156,	0,	0,	31,	0,	3,	23094,	94883,	0,	0,	0,	'',	NULL);

-- NPC 23097
SET @ENTRY = 23097;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 6, 0, 100, 0, 0, 0, 0, 0, 45, 2, 1, 0, 0, 0, 0, 10, 0, 94882, 23093, 0, 0, 0, 0, 0, 'Acolyte of Water - On Death - Set Data 1 1 '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 75, 40187, 0, 0, 0, 0, 0, 10, 0, 94884, 23094, 0, 0, 0, 0, 0, 'Acolyte of Water - On Death - Add Aura "<a href="http://wowhead.com/spell=40187">Essence of Water</a>" '),
  (@ENTRY, 0, 10, 0, 60, 0, 100, 1, 119000, 119000, 0, 0, 45, 6, 6, 0, 0, 0, 0, 10, 0, 94882, 23093, 0, 0, 0, 0, 0, 'Acolyte of Water - On Update - Set Data 6 6 (No Repeat)');
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 40187 AND ConditionTypeOrReference = 31 AND ConditionValue1 = 3 AND ConditionValue2 = 23094;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
  (13,	1,	40187,	0,	0,	31,	0,	3,	23094,	94884,	0,	0,	0,	'',	NULL);

-- NPC 23098
SET @ENTRY = 23098;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 6, 0, 100, 0, 0, 0, 0, 0, 45, 3, 1, 0, 0, 0, 0, 10, 0, 94882, 23093, 0, 0, 0, 0, 0, 'Acolyte of Earth - On Death - Set Data 1 1 '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 75, 40189, 0, 0, 0, 0, 0, 10, 0, 94885, 23094, 0, 0, 0, 0, 0, 'Acolyte of Earth - On Death - Add Aura "<a href="http://wowhead.com/spell=40189">Essence of Earth</a>" '),
  (@ENTRY, 0, 10, 0, 60, 0, 100, 1, 119000, 119000, 0, 0, 45, 6, 6, 0, 0, 0, 0, 10, 0, 94882, 23093, 0, 0, 0, 0, 0, 'Acolyte of Earth - On Update - Set Data 6 6 (No Repeat)');
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 40189 AND ConditionTypeOrReference = 31 AND ConditionValue1 = 3 AND ConditionValue2 = 23094;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
  (13,	1,	40189,	0,	0,	31,	0,	3,	23094,	94885,	0,	0,	0,	'',	NULL);

-- NPC 23099
SET @ENTRY = 23099;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 6, 0, 100, 0, 0, 0, 0, 0, 45, 4, 1, 0, 0, 0, 0, 10, 0, 94882, 23093, 0, 0, 0, 0, 0, 'Acolyte of Fire - On Death - Set Data 1 1 '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 75, 40190, 0, 0, 0, 0, 0, 10, 0, 94886, 23094, 0, 0, 0, 0, 0, 'Acolyte of Fire - On Death - Add Aura "<a href="http://wowhead.com/spell=40190">Essence of Fire</a>" '),
  (@ENTRY, 0, 10, 0, 60, 0, 100, 1, 119000, 119000, 0, 0, 45, 6, 6, 0, 0, 0, 0, 10, 0, 94882, 23093, 0, 0, 0, 0, 0, 'Acolyte of Fire - On Update - Set Data 6 6 (No Repeat)');
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 40190 AND ConditionTypeOrReference = 31 AND ConditionValue1 = 3 AND ConditionValue2 = 23094;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
  (13,	1,	40190,	0,	0,	31,	0,	3,	23094,	94886,	0,	0,	0,	'',	NULL);

SET @ENTRY = 23100;
UPDATE creature_template SET unit_flags = 33554688 WHERE entry = @ENTRY; -- Immune to PC & Not Selectable
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "I require your life essence to maintain my existence in this realm.", 12, 0, 100, 0, 0, "Flawless Arcane Elemental - ");

-- NPC 23094
SET @ENTRY = 23094;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', flags_extra = 262144 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 8, 0, 100, 0, 40156, 0, 0, 0, 80, 2309401, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Minion of Sar&#039;this - On Spellhit "<a href="http://wowhead.com/spell=40156">Essence of Wind</a>" - Run Script <a href="/smartai/script/2309401">2309401</a> '),
  (@ENTRY, 0, 1, 0, 34, 0, 100, 0, 0, 1, 0, 0, 11, 40193, 0, 0, 0, 0, 0, 10, 0, 311402, 50127, 0, 0, 0, 0, 0, 'Minion of Sar&#039;this - On Reached Point 1 - Cast "<a href="http://wowhead.com/spell=40193">White Beam</a>" '),
  (@ENTRY, 0, 2, 0, 23, 0, 100, 1, 40187, 1, 0, 0, 69, 2, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2474.23, 4701.54, 155.318, 6.12812, 'Minion of Sar&#039;this - On Has Aura "<a href="http://wowhead.com/spell=40187">Essence of Water</a>" - Move To Pos (No Repeat)'),
  (@ENTRY, 0, 3, 0, 34, 0, 100, 0, 0, 2, 0, 0, 11, 40225, 0, 0, 0, 0, 0, 10, 0, 311402, 50127, 0, 0, 0, 0, 0, 'Minion of Sar&#039;this - On Reached Point 2 - Cast "<a href="http://wowhead.com/spell=40225">Blue Beam</a>" '),
  (@ENTRY, 0, 4, 0, 23, 0, 100, 1, 40189, 1, 0, 0, 69, 3, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2473.86, 4698.34, 155.525, 0.239204, 'Minion of Sar&#039;this - On Has Aura "<a href="http://wowhead.com/spell=40189">Essence of Earth</a>" - Move To Pos (No Repeat)'),
  (@ENTRY, 0, 5, 0, 34, 0, 100, 0, 0, 3, 0, 0, 11, 40227, 0, 0, 0, 0, 0, 10, 0, 311402, 50127, 0, 0, 0, 0, 0, 'Minion of Sar&#039;this - On Reached Point 3 - Cast "<a href="http://wowhead.com/spell=40227">Green Beam</a>" '),
  (@ENTRY, 0, 6, 0, 23, 0, 100, 1, 40190, 1, 0, 0, 69, 4, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2471.4, 4696.51, 155.874, 0.691091, 'Minion of Sar&#039;this - On Has Aura "<a href="http://wowhead.com/spell=40190">Essence of Fire</a>" - Move To Pos (No Repeat)'),
  (@ENTRY, 0, 7, 0, 34, 0, 100, 0, 0, 4, 0, 0, 11, 40228, 0, 0, 0, 0, 0, 10, 0, 311402, 50127, 0, 0, 0, 0, 0, 'Minion of Sar&#039;this - On Reached Point 4 - Cast "<a href="http://wowhead.com/spell=40228">Red Beam</a>" '),
  (@ENTRY, 0, 8, 0, 11, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Minion of Sar&#039;this - On Respawn - Set Run Off '),
  (@ENTRY, 0, 10, 0, 103, 1, 100, 0, 1, 0, 0, 0, 69, 11, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2487.97, 4713.62, 154.583, 4.6267, 'Minion of Sar&#039;this - On Enter Phase 1 - Move To Pos (Phase 1)'),
  (@ENTRY, 0, 11, 0, 103, 2, 100, 0, 2, 0, 0, 0, 69, 12, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2439.29, 4665.75, 162.169, 4.85211, 'Minion of Sar&#039;this - On Enter Phase 2 - Move To Pos (Phase 2)'),
  (@ENTRY, 0, 12, 0, 103, 4, 100, 0, 3, 0, 0, 0, 69, 13, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2404.93, 4583.43, 163.176, 5.09557, 'Minion of Sar&#039;this - On Enter Phase 3 - Move To Pos (Phase 3)'),
  (@ENTRY, 0, 13, 0, 103, 8, 100, 0, 4, 0, 0, 0, 69, 14, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2426.86, 4489.22, 166.207, 4.54187, 'Minion of Sar&#039;this - On Enter Phase 4 - Move To Pos (Phase 4)'),
  (@ENTRY, 0, 14, 0, 38, 0, 100, 1, 6, 6, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Minion of Sar&#039;this - On Data Set 6 6 - Evade (No Repeat)');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 75, 32332, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Minion of Sar&#039;this - In Combat - Add Aura "<a href="http://wowhead.com/spell=32332">Cyclone Visual</a>" '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -2471.79, 4704.23, 155.476, 5.55309, 'Minion of Sar&#039;this - In Combat - Move To Pos ');
DELETE FROM creature_template WHERE entry = 50127;
INSERT INTO creature_template (entry, difficulty_entry_1, modelid1, modelid2, modelid3, modelid4, name, subname, IconName, gossip_menu_id, minlevel, maxlevel, exp, faction, npcflag, speed, scale, rank, dmgschool, BaseAttackTime, RangeAttackTime, BaseVariance, RangeVariance, unit_class, unit_flags, dynamicflags, family, trainer_type, trainer_spell, trainer_class, trainer_race, type, type_flags, lootid, pickpocketloot, skinloot, resistance1, resistance2, resistance3, resistance4, resistance5, resistance6, spell1, spell2, spell3, spell4, spell5, spell6, spell7, spell8, PetSpellDataId, mingold, maxgold, AIName, MovementType, InhabitType, HealthModifier, ManaModifier, ArmorModifier, DamageModifier, ExperienceModifier, RacialLeader, RegenHealth, equipment_id, mechanic_immune_mask, flags_extra, ScriptName, pool_id) VALUES
  (50127,	0,	18783,	11686,	0,	0,	'Terokkar Quest Bunny',	'',	NULL,	0,	70,	70,	0,	114,	0,	1.15,	1,	0,	0,	2000,	2400,	0,	1,	1,	34079494,	0,	0,	0,	0,	0,	0,	10,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	'SmartAI',	0,	7,	1.63827,	0,	0,	0,	1,	0,	1,	0,	0,	130,	'',	0);
DELETE FROM creature WHERE id = 50127 AND guid = 311402;
INSERT INTO creature (guid, id, map, spawnMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, MovementType, pool_id, ScriptName) VALUES
  (311402,	50127,	530,	1,	0,	0,	-2466.34,	4700.5,	155.796,	3.20174,	25,	0,	0,	6635,	0,	0,	0,	'');

UPDATE spell_template SET speed = 0 WHERE entry = 40227;

-- NPC 23100
SET @ENTRY = 23100;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 13, 0, 185863, 0, 10, 0, 0, 0, 0, 'Flawless Arcane Elemental - On Just Summoned - Despawn Instant '),
  (@ENTRY, 0, 1, 0, 6, 0, 100, 0, 0, 0, 0, 0, 45, 6, 6, 0, 0, 0, 0, 9, 0, 23094, 0, 20, 0, 0, 0, 0, 'Flawless Arcane Elemental - On Death - Set Data 6 6 ');

# SmartAIMgr: EntryOrGuid 5012400 using event(0) has invalid action type (0), skipped.
DELETE FROM smart_scripts WHERE entryorguid = 5012400 AND source_type = 9 AND id = 0;

# SmartAIMgr: Entry 18471500 SourceType 9 Event 0 Action 12 creature summon: There is a summon spell for creature entry 21308 (SpellId: 36552, effect: 0)
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 36552, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, ' - In Combat - Cast "<a href="http://wowhead.com/spell=36552">Summon Cauldron Bugs</a>" '),
  (@ENTRY, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 32, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, ' - In Combat - Reset GO ');

# SmartAIMgr: EntryOrGuid 31124800 using event(0) has invalid action type (0), skipped.
DELETE FROM smart_scripts WHERE entryorguid = 31124800 AND source_type = 9 AND id IN (0,1);

# CreatureTextMgr: Entry 314, Group 0 in table `creature_texts` has Type 0 but this chat type is not a valid chat type for creatures. Defaulting to 12 (CHAT_MSG_MONSTER_SAY)
UPDATE creature_text SET type = 12 WHERE CreatureID = 314;

# CreatureTextMgr: Entry 11980, Group 0 in table `creature_texts` has Type 1 but this chat type is not a valid chat type for creatures. Defaulting to 12 (CHAT_MSG_MONSTER_SAY)
UPDATE creature_text SET type = 14 WHERE CreatureID = 11980;

# CreatureTextMgr: Entry 16700, Group 6 in table `creature_texts` has Type 0 but this chat type is not a valid chat type for creatures. Defaulting to 12 (CHAT_MSG_MONSTER_SAY)
# CreatureTextMgr: Entry 16700, Group 7 in table `creature_texts` has Type 0 but this chat type is not a valid chat type for creatures. Defaulting to 12 (CHAT_MSG_MONSTER_SAY)
# CreatureTextMgr: Entry 16700, Group 8 in table `creature_texts` has Type 0 but this chat type is not a valid chat type for creatures. Defaulting to 12 (CHAT_MSG_MONSTER_SAY)
UPDATE creature_text SET type = 14 WHERE CreatureID = 11980 AND groupid IN (6,7,8);

# From TC
# CreatureTextMgr: Entry 7779, Group 4, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId X.
DELETE FROM broadcast_text WHERE ID IN (314,316,317,2229,2230,2231,2625,2626,2627,2628,3762,3781,3782,3791,10275,22097,29551,10274,10276,10277,10278,10279,10280,10281,29545,13698,13699,13700,13701,13702,13704,13705,13711,13712,13713,13714,13715,13716,13717,13718,13719,17884,17885,17886,17900,18155,18156,18190,18191,18289,18291,18293,18432,18433,18435,18436,18437,18438,18439,18441,18442,18443,18566,18567,18568,19336,18694,18695,18696,18697,18698,18699,18700,19298,19299,19301,19302,19303,19308,19338,19339,19340,19503,19504,19506,19508,19509);
INSERT INTO broadcast_text (ID, Language, MaleText, FemaleText, EmoteID0, EmoteID1, EmoteID2, EmoteDelay0, EmoteDelay1, EmoteDelay2, SoundId, Unk1, Unk2, VerifiedBuild) VALUES
  (314,	  0,	'These lands shall be cleansed!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (316,	  0,	'These undead atrocities will be destroyed!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (317,	  0,	'The Scarlet Crusade shall not fail in its mission!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (2229,	0,	'',	'A fine trophy your head will make, $R.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (2230,	0,	'',	'My talons will shred your puny body, $R.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (2231,	0,	'',	'You will be easy prey, $C.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (2625,	0,	'You carry the taint of the Scourge.  Prepare to enter the Twisting Nether.',	'You carry the taint of the Scourge.  Prepare to enter the Twisting Nether.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (2626,	0,	'There is no escape for you.  The Crusade shall destroy all who carry the Scourge\'s taint.',	'There is no escape for you.  The Crusade shall destroy all who carry the Scourge\'s taint.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (2627,	0,	'The Light condemns all who harbor evil.  Now you will die!',	'The Light condemns all who harbor evil.  Now you will die!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (2628,	0,	'The Scarlet Crusade shall smite the wicked and drive evil from these lands!',	'The Scarlet Crusade shall smite the wicked and drive evil from these lands!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (3762,	0,	'Milord, your guest has arrived. He awaits your presence.',	'Milord, your guest has arrived. He awaits your presence.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (3781,	0,	'Good day to you both. I would speak to Lord Lescovar.',	'Good day to you both. I would speak to Lord Lescovar.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (3782,	0,	'Thank you. The Light be with you both.',	'Thank you. The Light be with you both.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (3791,	0,	'I shall use the time wisely, milord. Thank you.',	'I shall use the time wisely, milord. Thank you.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (10275,	1,	'Yes you may, Okla. But do not stray too far from home. ',	'',	1,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (22097,	0,	'The zeppelin to Grom\'gol has just arrived! All aboard for Stranglethorn!',	'The zeppelin to Grom\'gol has just arrived! All aboard for Stranglethorn!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (29551,	0,	'The zeppelin to Orgrimmar has just arrived! All aboard for Durotar!',	'The zeppelin to Orgrimmar has just arrived! All aboard for Durotar!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (10274,	1,	'',	'Can I go collect more rocks for my necklace, Papa?',	1,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (10276,	1,	'',	'Dabu! I will be careful Papa!',	1,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (10277,	1,	'',	'Ooohh... This rock is nice and colorful. Let\'s see if I can find more like it...',	1,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (10278,	1,	'',	'Hmm... That rock is nice, but too small.',	1,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (10279,	1,	'',	'This is a shiney rock, I\'ll put it in my bucket. Ok, I just need a few more...',	1,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (10280,	1,	'',	'I bet my friend Gruk would like this rock for the spear he is making! It\'s very sharp... I hope he likes it.',	1,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (10281,	1,	'',	'There... That should be enough rocks to make a necklace. I should probably get home now anyway.',	1,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (29545,	0,	'The zeppelin to Undercity has just arrived! All aboard for Tirisfal Glades!',	'The zeppelin to Undercity has just arrived! All aboard for Tirisfal Glades!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13698,	7,	'Hey, Cookie! What\'s for dinner tonight? And don\'t say chicken!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13699,	7,	'Yarr, Admiral. Let me think about it... Arrr... It be comin\' into focus.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13700,	7,	'It looks like it be succulent pork ribs basted with its own delectable juices and a side o\' Captain Sander\'s Secret Sauce - fer dippin\'.\n',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13701,	7,	'And fer dessert we be havin\' cheesecake, flown in fresh from Stormwind on the wings o\' angels...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13702,	7,	'Wow! Really?',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13704,	7,	'It be chicken...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13705,	7,	'I hate you so much, Cookie.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13711,	7,	'',	'Adamant, could you please take a look at this tablet and try to decipher the runes?',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13712,	7,	'Of course! Anything for you, darling!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13713,	7,	'Alright, let me take a look at that tablet.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13714,	7,	'%s slowly reads the tablet, mouthing the words in their native tongue.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13715,	7,	'Naga warlord! Oh dear...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13716,	7,	'Well, you aren\'t going to like what I have to tell you, young missy. This tablet is a naga communication. Their leader, Warlord Sriss\'tiz, has ordered his naga to take the rest of the island by force.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13717,	7,	'And it looks like he\'s got reinforcements comin\' from Nazjatar!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13718,	0,	'We\'ve got to do something about this!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13719,	7,	'',	'Thank you, Adamant. I think I know just the person for the job.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (17884,	0,	'Emergency shutdown will complete in thirty seconds.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (17885,	0,	'Emergency shutdown will complete in ten seconds.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (17886,	0,	'Manaforge shutdown aborted.  Resuming manaforge activity.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (17900,	0,	'Emergency shutdown complete.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18155,	0,	'Warning!  %s emergency shutdown process initiated by $n.  Shutdown will complete in two minutes.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18156,	0,	'Emergency shutdown will complete in one minute.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18190,	0,	'Hostiles detected. Ending transmission.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18191,	0,	'Protectorate transmission complete.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18289,	0,	'',	'I have an idea.  Let\'s plant this shard in the ground and see what happens.',	1,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18291,	0,	'',	'The evil emanating from the crystal shard has lured one of the colossi. Put it down quick!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18293,	0,	'',	'Up here on the hill, $n.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18432,	0,	'Let\'s do this... Just keep me covered and I\'ll deliver the package.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18433,	0,	'By the second sun of K\'aresh, look at this place! I can only imagine what Salhadaar is planning. Come on, let\'s keep going.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18435,	0,	'Look there, fleshling! Salhadaar\'s conduits! He\'s keeping well fed....',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18436,	0,	'Alright, keep me protected while I plant this disruptor. This shouldn\'t take very long.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18437,	0,	'Done! Back up! Back up!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18438,	0,	'Keep these things off me!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18439,	0,	'I\'m under attack! I repeat, I am under attack!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18441,	0,	'Protect the conduit! Stop the intruders!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18442,	0,	'Looks like my work here is done. Report back to the holo-image of Ameer over at the transponder.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18443,	0,	'Prepare to enter oblivion, meddlers. You have unleashed a god!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18566,	0,	'We\'re not too far from the Protectorate Watch Post, $n. This way!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18567,	0,	'Commander! This fleshling rescued me!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18568,	0,	'%s salutes Commander Ameer.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19336,	0,	'I hear what you hear, brother. Look behind you...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18694,	0,	'Tear the land asunder, Gul\'dan! Sever the tie!',	'Tear the land asunder, Gul\'dan! Sever the tie!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18695,	0,	'They have abandoned us! Do not forget!',	'They have abandoned us! Do not forget!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18696,	0,	'We will take from the land if it refuses to give!',	'We will take from the land if it refuses to give!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18697,	0,	'Do not do this, Gul\'dan! The elements will never forgive us!',	'Do not do this, Gul\'dan! The elements will never forgive us!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18698,	0,	'Stop! You must stop!',	'Stop! You must stop!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18699,	0,	'Think of our younglings, Gul\'dan! You will destroy us all!',	'Think of our younglings, Gul\'dan! You will destroy us all!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18700,	0,	'You have damned us all... We are lost.',	'You have damned us all... We are lost.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19298,	0,	'Cyrukh has awoken!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19299,	0,	'You will suffer eternally!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19301,	0,	'Cyrukh comes for you!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19302,	0,	'Those that dare play with fire will be incinerated!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19303,	0,	'A flaming vortex takes shape.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19308,	0,	'Little creature made of flesh, your wish is granted! Death comes for you!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19338,	0,	'It is now as it should be, shaman. You have done well.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19339,	0,	'Yes... Well enough for the elements that are here, but the cipher is known to another... The spirits of fire are in turmoil... If this force is not stopped, the world where these mortals came from will cease.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19340,	0,	'Farewell, mortals... The earthmender knows what fire feels...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19503,	0,	'Waste no time, fool! Use our power to kill those that stand in our way! Destroy Karsius before you are subdued!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19504,	0,	'Your pathetic attempt to escape will be short lived, Gorefiend. Let the $g boy:girl; go and submit! Even with your armor and weapons, you cannot defeat the ancients!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19506,	0,	'What ... have you done...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19508,	0,	'We will meet again... Someday.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (19509,	0,	'Death incarnate has been released upon the world once more! Teron Gorefiend has returned...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019);

# SmartAIMgr: Entry 424 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 424 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 424;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (424,	0,	0,	'More bones to gnaw on...',	12,	0,	100,	0,	0,	0,	1871,	0,	'Redridge Poacher - Random Say on Aggro'),
  (424,	0,	1,	'Grrrr... fresh meat!',	12,	0,	100,	0,	0,	0,	1870,	0,	'Redridge Poacher - Random Say on Aggro');

# SmartAIMgr: Entry 429 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 429 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 429;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (429,	0,	0,	'More bones to gnaw on...',	12,	0,	100,	0,	0,	0,	1871,	0,	'Shadowhide Darkweaver - Random Say on Aggro'),
  (429,	0,	1,	'Grrrr... fresh meat!',	12,	0,	100,	0,	0,	0,	1870,	0,	'Shadowhide Darkweaver - Random Say on Aggro');

# SmartAIMgr: Entry 430 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 430 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 430;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (430,	0,	0,	'More bones to gnaw on...',	12,	0,	100,	0,	0,	0,	1871,	0,	'Redridge Mystic - Random Say on Aggro'),
  (430,	0,	1,	'Grrrr... fresh meat!',	12,	0,	100,	0,	0,	0,	1870,	0,	'Redridge Mystic - Random Say on Aggro');

# SmartAIMgr: Entry 436 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
# SmartAIMgr: Entry 436 SourceType 0 Event 4 Action 1 using non-existent Text id 1, skipped.
# SmartAIMgr: Entry 436 SourceType 0 Event 4 Action 1 uses non-existent text 1, skipped.
DELETE FROM creature_text WHERE CreatureID = 436;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (436,	0,	0,	'Feel the power of the Blackrock Orcs!',	12,	1,	100,	0,	0,	0,	1874,	0,	'Blackrock Shadowcaster'),
  (436,	0,	1,	'You are no match for the Blackrock Orcs!',	12,	1,	100,	0,	0,	0,	1875,	0,	'Blackrock Shadowcaster'),
  (436,	1,	0,	'%s becomes enraged!',	16,	0,	100,	0,	0,	0,	24144,	0,	'Blackrock Shadowcaster');

# SmartAIMgr: Entry 453 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 453 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 453;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (453,	0,	0,	'More bones to gnaw on...',	12,	0,	100,	0,	0,	0,	1871,	0,	'Riverpaw Mystic - Random Say on Aggro'),
  (453,	0,	1,	'Grrrr... fresh meat!',	12,	0,	100,	0,	0,	0,	1870,	0,	'Riverpaw Mystic - Random Say on Aggro');

# SmartAIMgr: Entry 500 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 500 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 500;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (500,	0,	0,	'More bones to gnaw on...',	12,	0,	100,	0,	0,	0,	1871,	0,	'Riverpaw Scout - Random Say on Aggro'),
  (500,	0,	1,	'Grrrr... fresh meat!',	12,	0,	100,	0,	0,	0,	1870,	0,	'Riverpaw Scout - Random Say on Aggro');

# SmartAIMgr: Entry 694 SourceType 0 Event 2 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 694 SourceType 0 Event 2 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 694;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (694,	0,	0,	'%s becomes enraged!',	16,	0,	100,	0,	0,	0,	10677,	0,	'Bloodscalp Axe Thrower');

# SmartAIMgr: Entry 891 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 891 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.DELETE FROM creature_text WHERE CreatureID = 694;
DELETE FROM creature_text WHERE CreatureID = 891;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (891,	0,	0,	'Raaar!!! Me smash $r!',	12,	0,	100,	0,	0,	0,	1927,	0,	'Splinter Fist Fire Weaver'),
  (891,	0,	1,	'Me smash! You die!',	12,	0,	100,	0,	0,	0,	1926,	0,	'Splinter Fist Fire Weaver'),
  (891,	0,	2,	'I\'ll crush you!',	12,	0,	100,	0,	0,	0,	1925,	0,	'Splinter Fist Fire Weaver');

# SmartAIMgr: Entry 1009 SourceType 0 Event 1 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 1009 SourceType 0 Event 1 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 1009;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (1009,	0,	0,	'More bones to gnaw on...',	12,	0,	100,	0,	0,	0,	1871,	0,	'Mosshide Mistweaver - Random Say on Aggro'),
  (1009,	0,	1,	'Grrrr... fresh meat!',	12,	0,	100,	0,	0,	0,	1870,	0,	'Mosshide Mistweaver - Random Say on Aggro');

# SmartAIMgr: Entry 1013 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 1013 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 1013;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (1013,	0,	0,	'More bones to gnaw on...',	12,	0,	100,	0,	0,	0,	1871,	0,	'Mosshide Mystic - Random Say on Aggro'),
  (1013,	0,	1,	'Grrrr... fresh meat!',	12,	0,	100,	0,	0,	0,	1870,	0,	'Mosshide Mystic - Random Say on Aggro');

# SmartAIMgr: Entry 1054 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 1054 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 1054;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (1054,	0,	0,	'Never cross a Dark Iron, $C.',	12,	0,	100,	0,	0,	0,	1934,	0,	'Dark Iron Demolitionist'),
  (1054,	0,	1,	'Time to die, $C.',	12,	0,	100,	0,	0,	0,	1935,	0,	'Dark Iron Demolitionist'),
  (1054,	0,	2,	'Feel the power of the Dark Iron Dwarves!',	12,	0,	100,	0,	0,	0,	1936,	0,	'Dark Iron Demolitionist');

# SmartAIMgr: Entry 1065 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 1065 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 1065;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (1065,	0,	0,	'More bones to gnaw on...',	12,	0,	100,	0,	0,	0,	1871,	0,	'Riverpaw Shaman - Random Say on Aggro'),
  (1065,	0,	1,	'Grrrr... fresh meat!',	12,	0,	100,	0,	0,	0,	1870,	0,	'Riverpaw Shaman - Random Say on Aggro');

# SmartAIMgr: Entry 1123 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 1123 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 1123;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (1123,	0,	0,	'You be dead soon!',	12,	0,	100,	0,	0,	0,	10434,	0,	'Frostmane Headhunter'),
  (1123,	0,	1,	'Killing you be easy.',	12,	0,	100,	0,	0,	0,	1909,	0,	'Frostmane Headhunter'),
  (1123,	0,	2,	'I gonna make you into mojo!',	12,	0,	100,	0,	0,	0,	10435,	0,	'Frostmane Headhunter');

# SmartAIMgr: Entry 1124 SourceType 0 Event 1 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 1124 SourceType 0 Event 1 Action 1 uses non-existent text 0, skipped.
DELETE FROM creature_text WHERE CreatureID = 1124;
INSERT INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextId, TextRange, comment) VALUES
  (1124,	0,	0,	'Iman m t\'ief fu Fus\'obeah italaf',	12,	0,	100,	0,	0,	0,	0,	0,	'Frostmane Shadowcaster'),
  (1124,	0,	1,	'Killing you be easy.',	12,	0,	100,	0,	0,	0,	1909,	0,	'Frostmane Shadowcaster');

# SmartAIMgr: Entry 1535 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 1535 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
-- NPC 1535
SET @ENTRY = 1535;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Warrior - On Aggro - Say Line 0 '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 3000, 5000, 45000, 50000, 11, 3238, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Warrior - In Combat - Cast "<a href="http://wowhead.com/spell=3238">Nimble Reflexes</a>" '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Warrior - Between 0-15% HP - Flee For Assist (No Repeat)');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "The Light condemns all who harbor evil. Now you will die!", 12, 7, 100, 0, 0, "Scarlet Warrior - "),
  (@ENTRY, 0, 1, "The Scarlet Crusade shall smite the wicked and drive evil from these lands!", 12, 7, 100, 0, 0, "Scarlet Warrior - "),
  (@ENTRY, 0, 2, "You carry the taint of the Scourge. Prepare to enter the Twisting Nether.", 12, 7, 100, 0, 0, "Scarlet Warrior - ");

# SmartAIMgr: Entry 18152 SourceType 0 Event 2 Action 26 SpecialFlags for Quest entry 9816 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
-- NPC 18152
SET @ENTRY = 18152;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 3, 34, 0, 100, 1, 8, 0, 0, 0, 11, 24983, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Reached Point 0 - Cast "<a href="http://wowhead.com/spell=24983">Baby Murloc Passive</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 60, 0, 100, 1, 2500, 2500, 1, 1, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1170.34, 8144.97, 19.1958, 6.05553, 'Baby Murloc - On Update - Move To Pos (No Repeat)'),
  (@ENTRY, 0, 2, 0, 54, 0, 100, 0, 0, 0, 0, 0, 33, 18152, 0, 0, 0, 0, 0, 17, 0, 0, 30, 0, 0, 0, 0, 0, 'Baby Murloc - On Just Summoned - Quest Credit "<a href="http://wowhead.com/quest=18152">Baby Murloc</a>" '),
  (@ENTRY, 0, 3, 0, 34, 0, 100, 0, 8, 0, 0, 0, 17, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Reached Point 0 - Set Emote State 10 '),
  (@ENTRY, 0, 4, 0, 60, 0, 100, 1, 19000, 19000, 1, 1, 41, 0, 0, 0, 0, 0, 0, 13, 0, 182164, 0, 60, 0, 0, 0, 0, 'Baby Murloc - On Update - Despawn Instant (No Repeat)');
INSERT INTO event_scripts (id, delay, command, datalong, datalong2, dataint, x, y, z, o) VALUES
  (11424,	0,	8,	@ENTRY,	0,	0,	0,	0,	0,	0);

# SmartAIMgr: Entry 18398 SourceType 0 Event 1 Action 15 SpecialFlags for Quest entry 9962 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
-- NPC 18398
SET @ENTRY = 18398;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 1000, 1000, 9000, 11000, 11, 32023, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Brokentoe - In Combat - Cast "<a href="http://wowhead.com/spell=32023">Hoof Stomp</a>" '),
  (@ENTRY, 0, 2, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 10, 10, 0, 0, 0, 0, 19, 0, 18471, 0, 0, 0, 0, 0, 0, 'Brokentoe - On Death - Set Data 10 10 (No Repeat)');

# SmartAIMgr: Entry 18399 SourceType 0 Event 4 Action 15 SpecialFlags for Quest entry 9967 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
-- NPC 18399
SET @ENTRY = 18399;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Twin - On Aggro - Say Line 0 '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 2000, 2000, 11, 14873, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Twin - In Combat - Cast "<a href="http://wowhead.com/spell=14873">Sinister Strike</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 5000, 6000, 11000, 12000, 11, 15691, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Twin - In Combat - Cast "<a href="http://wowhead.com/spell=15691">Eviscerate</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 8000, 9000, 15000, 16000, 11, 32319, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Twin - In Combat - Cast "<a href="http://wowhead.com/spell=32319">Mutilate</a>" '),
  (@ENTRY, 0, 5, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 11, 11, 0, 0, 0, 0, 19, 0, 18471, 0, 0, 0, 0, 0, 0, 'Murkblood Twin - On Death - Set Data 11 11 (No Repeat)');

# SmartAIMgr: Entry 17413 SourceType 0 Event 0 Action 15 SpecialFlags for Quest entry 9545 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
SET @ENTRY = 17413;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
UPDATE quest_template SET ReqCreatureOrGOId1 = @ENTRY, ReqCreatureOrGOCount1 = 1 WHERE entry = 9545;
DELETE FROM event_scripts WHERE id = 10745 AND delay = 20 AND command = 8 AND datalong = @ENTRY;
INSERT INTO event_scripts (id, delay, command, datalong, datalong2, dataint, x, y, z, o) VALUES
  (10745,	20,	8,	@ENTRY,	0,	0,	0,	0,	0,	0);
-- NPC 17418
SET @ENTRY = 17418;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', unit_flags = 256, flags_extra = 0, faction = 1095 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Laughing Skull Ambusher - On Just Summoned - Set Home Position '),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Laughing Skull Ambusher - On Just Summoned - Set React State Passive '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 69, 1, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 214.556, 4125.19, 79.7483, 2.47792, 'Laughing Skull Ambusher - On Just Summoned - Move To Pos '),
  (@ENTRY, 0, 4, 0, 38, 0, 100, 0, 1, 1, 500, 2000, 49, 1, 0, 0, 0, 0, 0, 9, 0, 17404, 0, 50, 0, 0, 0, 0, 'Laughing Skull Ambusher - On Data Set 1 1 - Start Attacking '),
  (@ENTRY, 0, 5, 0, 1, 0, 100, 1, 30000, 30000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Laughing Skull Ambusher - Out of Combat - Despawn Instant (No Repeat)'),
  (@ENTRY, 0, 6, 7, 34, 0, 100, 0, 0, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 0, 50116, 0, 50, 0, 0, 0, 0, 'Laughing Skull Ambusher - On Reached Point 1 - Start Attacking '),
  (@ENTRY, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 45, 2, 1, 0, 0, 0, 0, 9, 0, 50116, 0, 20, 0, 0, 0, 0, 'Laughing Skull Ambusher - On Reached Point 1 - Set Data 2 1 '),
  (@ENTRY, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 2, 1, 0, 0, 0, 0, 9, 0, 17417, 0, 20, 0, 0, 0, 0, 'Laughing Skull Ambusher - On Reached Point 1 - Set Data 2 1 '),
  (@ENTRY, 0, 10, 0, 38, 0, 100, 0, 2, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, 0, 17417, 20, 0, 0, 0, 0, 0, 'Laughing Skull Ambusher - On Data Set 2 1 - Start Attacking ');
-- NPC 17417
SET @ENTRY = 17417;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', unit_flags = 256 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 53, 0, 17417, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Respawn - Start Waypoint 17417 '),
  (@ENTRY, 0, 1, 2, 40, 0, 100, 0, 2, 17417, 0, 0, 54, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Waypoint 2 Reached - Pause Waypoint 10000ms '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 2, 17417, 0, 0, 80, 1741702, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Waypoint 2 Reached - Run Script <a href="/smartai/script/1741702">1741702</a> '),
  (@ENTRY, 0, 3, 0, 40, 0, 100, 0, 3, 17417, 0, 0, 55, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Waypoint 3 Reached - Stop Waypoint '),
  (@ENTRY, 0, 5, 0, 38, 0, 100, 1, 2, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 0, 17418, 0, 15, 0, 0, 0, 0, 'Mag&#039;har Escort - On Data Set 2 1 - Start Attacking (No Repeat)'),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 1, 0, 0, 0, 0, 39, 10, 0, 0, 0, 0, 0, 19, 0, 50116, 10, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Aggro - Call For Help (No Repeat)');
-- NPC 50116
SET @ENTRY = 50116;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', unit_flags = 256 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 53, 0, 1741701, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Respawn - Start Waypoint 1741701 '),
  (@ENTRY, 0, 1, 2, 40, 0, 100, 0, 2, 1741701, 0, 0, 54, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Waypoint 2 Reached - Pause Waypoint 10000ms '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 2, 1741701, 0, 0, 80, 5011601, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Waypoint 2 Reached - Run Script <a href="/smartai/script/5011601">5011601</a> '),
  (@ENTRY, 0, 3, 0, 40, 0, 100, 0, 3, 1741701, 0, 0, 55, 0, 0, 0, 0, 0, 0, 1, 0, 17418, 0, 15, 0, 0, 0, 0, 'Mag&#039;har Escort - On Waypoint 3 Reached - Stop Waypoint '),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 1, 0, 0, 0, 0, 39, 10, 0, 0, 0, 0, 0, 9, 0, 17417, 0, 10, 0, 0, 0, 0, 'Mag&#039;har Escort - On Aggro - Call For Help (No Repeat)'),
  (@ENTRY, 0, 8, 0, 54, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Just Summoned - Set React State Passive '),
  (@ENTRY, 0, 9, 0, 38, 0, 100, 1, 2, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, 0, 17418, 20, 0, 0, 0, 0, 0, 'Mag&#039;har Escort - On Data Set 2 1 - Start Attacking (No Repeat)');
-- NPC 17404
SET @ENTRY = 17404;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', faction = 1683 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 53, 0, 17404, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - On Respawn - Start Waypoint 17404 '),
  (@ENTRY, 0, 1, 0, 40, 0, 100, 0, 2, 17404, 0, 0, 80, 1740401, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - On Waypoint 2 Reached - Run Script <a href="/smartai/script/1740401">1740401</a> '),
  (@ENTRY, 0, 4, 0, 40, 0, 100, 0, 3, 17404, 0, 0, 80, 1740402, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - On Waypoint 3 Reached - Run Script <a href="/smartai/script/1740402">1740402</a> '),
  (@ENTRY, 0, 7, 0, 40, 0, 100, 0, 4, 17404, 0, 0, 80, 1740404, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - On Waypoint 4 Reached - Run Script <a href="/smartai/script/1740404">1740404</a> '),
  (@ENTRY, 0, 9, 0, 40, 0, 100, 0, 5, 17404, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - On Waypoint 5 Reached - Set Run Off '),
  (@ENTRY, 0, 10, 0, 40, 0, 100, 0, 6, 17404, 0, 0, 80, 1740403, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - On Waypoint 6 Reached - Run Script <a href="/smartai/script/1740403">1740403</a> '),
  (@ENTRY, 0, 12, 0, 11, 0, 100, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - On Respawn - Store Targetlist 0 '),
  (@ENTRY, 0, 13, 0, 0, 0, 100, 0, 0, 5000, 10000, 15000, 11, 17142, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Cast "<a href="http://wowhead.com/spell=17142">Holy Fire</a>" '),
  (@ENTRY, 0, 14, 0, 0, 0, 100, 0, 0, 5000, 30000, 35000, 11, 13005, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Cast "<a href="http://wowhead.com/spell=13005">Hammer of Justice</a>" '),
  (@ENTRY, 0, 15, 0, 2, 0, 100, 0, 0, 25, 10000, 15000, 11, 29427, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - Between 0-25% HP - Cast "<a href="http://wowhead.com/spell=29427">Holy Light</a>" '),
  (@ENTRY, 0, 17, 0, 102, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, 0, 17418, 30, 0, 0, 0, 0, 0, 'Vindicator Sedai - On Victim Died - Start Attacking ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 54, 28000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Pause Waypoint 28000ms '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 5.33678, 'Vindicator Sedai - In Combat - Set Orientation 5.33678 '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 2.36404, 'Vindicator Sedai - In Combat - Set Orientation 2.36404 '),
  (@ENTRY*100+1, 9, 103, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 90, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Set Flag Kneel '),
  (@ENTRY*100+1, 9, 105, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 106, 0, 0, 0, 100, 0, 1500, 1500, 0, 0, 12, 17418, 6, 20000, 0, 0, 0, 8, 0, 0, 0, 0, 264.041, 4104.36, 94.866, 2.77574, 'Vindicator Sedai - In Combat - Summon "<a href="http://wowhead.com/npc=17418">Laughing Skull Ambusher</a>" '),
  (@ENTRY*100+1, 9, 107, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 17418, 6, 20000, 0, 0, 0, 8, 0, 0, 0, 0, 262.114, 4101.12, 94.6748, 2.62964, 'Vindicator Sedai - In Combat - Summon "<a href="http://wowhead.com/npc=17418">Laughing Skull Ambusher</a>" '),
  (@ENTRY*100+1, 9, 108, 0, 0, 0, 100, 0, 13500, 13500, 0, 0, 91, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Set Flag Kneel '),
  (@ENTRY*100+1, 9, 109, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Say Line 1 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+2 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+2, 9, 200, 0, 0, 0, 100, 0, 0, 0, 0, 0, 54, 2000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Pause Waypoint 2000ms '),
  (@ENTRY*100+2, 9, 201, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Say Line 2 '),
  (@ENTRY*100+2, 9, 202, 0, 0, 0, 100, 0, 0, 0, 0, 0, 59, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Set Run On ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+3 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+3, 9, 300, 0, 0, 0, 100, 0, 0, 0, 0, 0, 55, 30000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Stop Waypoint '),
  (@ENTRY*100+3, 9, 301, 0, 0, 0, 100, 0, 0, 0, 0, 0, 90, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Set Flag Kneel '),
  (@ENTRY*100+3, 9, 302, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Say Line 3 '),
  (@ENTRY*100+3, 9, 303, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 17405, 3, 90000, 0, 0, 0, 8, 0, 0, 0, 0, 210.73, 4129.29, 78.6677, 0, 'Vindicator Sedai - In Combat - Summon "<a href="http://wowhead.com/npc=17405">Krun Spinebreaker</a>" '),
  (@ENTRY*100+3, 9, 304, 0, 0, 0, 100, 0, 9950, 9950, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 5.34071, 'Vindicator Sedai - In Combat - Set Orientation 5.34071 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+4 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+4, 9, 400, 0, 0, 0, 100, 0, 0, 0, 0, 0, 54, 25000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Pause Waypoint 25000ms '),
  (@ENTRY*100+4, 9, 402, 0, 0, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Set React State Passive '),
  (@ENTRY*100+4, 9, 403, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 0, 17418, 0, 20, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Set Data 1 1 '),
  (@ENTRY*100+4, 9, 404, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 0, 17418, 0, 20, 0, 0, 0, 0, 'Vindicator Sedai - In Combat - Start Attacking ');

# SmartAIMgr: Entry 50102 SourceType 0 Event 2 Action 26 SpecialFlags for Quest entry 9816 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
# SmartAIMgr: Entry 50103 SourceType 0 Event 2 Action 26 SpecialFlags for Quest entry 9816 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
# SmartAIMgr: Entry 50104 SourceType 0 Event 2 Action 26 SpecialFlags for Quest entry 9816 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
DELETE FROM smart_scripts WHERE entryorguid IN (50102,50103,50104) AND source_type = 0 AND id = 2;

# SmartAIMgr: Entry 1921000 SourceType 9 Event 2 Action 26 SpecialFlags for Quest entry 10011 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
SET @ENTRY = 1921000;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 2.66796, 'Fel Cannon: Fear - In Combat - Set Orientation 2.66796 '),
  (@ENTRY, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 11, 40227, 0, 0, 0, 0, 0, 10, 0, 67982, 19211, 0, 0, 0, 0, 0, 'Fel Cannon: Fear - In Combat - Cast "<a href="http://wowhead.com/spell=40227">Green Beam</a>" '),
  (@ENTRY, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 33, 19210, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 'Fel Cannon: Fear - In Combat - Quest Credit "<a href="http://wowhead.com/quest=19210">Fel Cannon: Fear</a>" '),
  (@ENTRY, 9, 3, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fel Cannon: Fear - In Combat - Evade ');

# SmartAIMgr: Entry 2163301 SourceType 9 Event 12 Action 26 SpecialFlags for Quest entry 10596 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
# SmartAIMgr: Entry 2163301 SourceType 9 Event 13 Action 26 SpecialFlags for Quest entry 10563 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
DELETE FROM spell_template WHERE entry = 37492;
INSERT INTO spell_template (entry, category, dispel, mechanic, attributes, attributesEx, attributesEx2, attributesEx3, attributesEx4, attributesEx5, attributesEx6, stances, stancesNot, targets, targetCreatureType, requiresSpellFocus, facingCasterFlags, casterAuraState, targetAuraState, casterAuraStateNot, targetAuraStateNot, castingTimeIndex, recoveryTime, categoryRecoveryTime, interruptFlags, auraInterruptFlags, channelInterruptFlags, procFlags, procChance, procCharges, maxLevel, baseLevel, spellLevel, durationIndex, powerType, manaCost, manaCostPerlevel, manaPerSecond, manaPerSecondPerLevel, rangeIndex, speed, stackAmount, totem1, totem2, reagent1, reagent2, reagent3, reagent4, reagent5, reagent6, reagent7, reagent8, reagentCount1, reagentCount2, reagentCount3, reagentCount4, reagentCount5, reagentCount6, reagentCount7, reagentCount8, equippedItemClass, equippedItemSubClassMask, equippedItemInventoryTypeMask, effect1, effect2, effect3, effectDieSides1, effectDieSides2, effectDieSides3, effectBaseDice1, effectBaseDice2, effectBaseDice3, effectDicePerLevel1, effectDicePerLevel2, effectDicePerLevel3, effectRealPointsPerLevel1, effectRealPointsPerLevel2, effectRealPointsPerLevel3, effectBasePoints1, effectBasePoints2, effectBasePoints3, effectMechanic1, effectMechanic2, effectMechanic3, effectImplicitTargetA1, effectImplicitTargetA2, effectImplicitTargetA3, effectImplicitTargetB1, effectImplicitTargetB2, effectImplicitTargetB3, effectRadiusIndex1, effectRadiusIndex2, effectRadiusIndex3, effectApplyAuraName1, effectApplyAuraName2, effectApplyAuraName3, effectAmplitude1, effectAmplitude2, effectAmplitude3, effectMultipleValue1, effectMultipleValue2, effectMultipleValue3, effectChainTarget1, effectChainTarget2, effectChainTarget3, effectItemType1, effectItemType2, effectItemType3, effectMiscValue1, effectMiscValue2, effectMiscValue3, effectMiscValueB1, effectMiscValueB2, effectMiscValueB3, effectTriggerSpell1, effectTriggerSpell2, effectTriggerSpell3, effectPointsPerComboPoint1, effectPointsPerComboPoint2, effectPointsPerComboPoint3, spellVisual, spellIconID, activeIconID, spellName1, spellName2, spellName3, spellName4, spellName5, spellName6, spellName7, spellName8, spellName9, spellName10, spellName11, spellName12, spellName13, spellName14, spellName15, spellName16, rank1, rank2, rank3, rank4, rank5, rank6, rank7, rank8, rank9, rank10, rank11, rank12, rank13, rank14, rank15, rank16, manaCostPercentage, startRecoveryCategory, startRecoveryTime, maxTargetLevel, spellFamilyName, spellFamilyFlags, maxAffectedTargets, dmgClass, preventionType, dmgMultiplier1, dmgMultiplier2, dmgMultiplier3, totemCategory1, totemCategory2, areaId, schoolMask, customAttributesFlags) VALUES
  (37492,	0,	0,	0,	384,	268435456,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	101,	0,	0,	0,	0,	3,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	0,	6,	61,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	12,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	13852,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	'BOX O TRICKS EVENT TRIGGER',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	1,	0);
UPDATE spell_template SET effect3 = 64, effectBasePoints3 = 0, effectImplicitTargetA3 = 1, effectApplyAuraName3 = 0, effectMiscValue3 = 0, effectTriggerSpell3 = 37492 WHERE entry = 37097;
UPDATE quest_template SET ReqCreatureOrGOId1 = 0, ReqCreatureOrGOCount1 = 0, ReqCreatureOrGOId3 = 21502, ReqCreatureOrGOCount3 = 1, ObjectiveText1 = '', ObjectiveText3 = "Discover Legion's Plans" WHERE entry IN (10596,10563);
UPDATE gameobject SET spawntimesecs = 61 WHERE guid IN (25542,25543);
UPDATE creature_template SET equipment_id = 416 WHERE entry = 21502;

# Table `command` have not existing subcommand 'irc' in command 'gm irc', skip.
# Table `command` have not existing subcommand 'online' in command 'gm online', skip.
# Table `command` have not existing command 'gmnameannounce', skip.
# Table `command` have not existing command 'shop', skip.
DELETE FROM command WHERE name IN ('gm irc','gm online','gmnameannounce','shop');

# SmartAIMgr: Entry 21512 SourceType 0 Event 1 Action 26 SpecialFlags for Quest entry 10564 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
# SmartAIMgr: Entry 21512 SourceType 0 Event 2 Action 26 SpecialFlags for Quest entry 10598 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
-- NPC 21512
SET @ENTRY = 21512;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 0, 37055, 0, 0, 0, 11, 41441, 0, 0, 0, 0, 0, 9, 0, 21316, 0, 100, 0, 0, 0, 0, 'Invis Legion Hold Glyph - On Spellhit "<a href="http://wowhead.com/spell=37055">Destroy Legion Hold Infernals</a>" - Cast "<a href="http://wowhead.com/spell=41441">Acid Geyser</a>" '),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 33, 21512, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 'Invis Legion Hold Glyph - On Spellhit "<a href="http://wowhead.com/spell=37055">Destroy Legion Hold Infernals</a>" - Quest Credit "<a href="http://wowhead.com/quest=21512">Invis Legion Hold Glyph</a>" ');

# SmartAIMgr: Entry 22375 SourceType 0 Event 3 Action 26 SpecialFlags for Quest entry 10879 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
-- NPC 22373
SET @ENTRY = 22373;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 19, 0, 100, 0, 10879, 1, 0, 0, 80, 2237301, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defender Grashna - On Quest "<a href="http://wowhead.com/quest=10879">The Skettis Offensive</a>" Accepted - Run Script <a href="/smartai/script/2237301">2237301</a> '),
  (@ENTRY, 0, 2, 3, 38, 0, 100, 0, 1, 1, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Defender Grashna - On Data Set 1 1 - Say Line 3 '),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defender Grashna - On Data Set 1 1 - Set NPC Flag Quest Giver '),
  (@ENTRY, 0, 4, 0, 35, 0, 100, 0, 22375, 0, 0, 0, 82, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defender Grashna - On Summoned "<a href="http://wowhead.com/npc=22375">Avatar of Terokk</a>" Despawned - Set NPC Flag Quest Giver ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defender Grashna - In Combat - Set NPC Flag Quest Giver '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Defender Grashna - In Combat - Say Line 4 '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 22376, 4, 30000, 0, 0, 0, 8, 0, 0, 0, 0, -1635.09, 5431.15, -42.9365, 2.11351, 'Defender Grashna - In Combat - Summon "<a href="http://wowhead.com/npc=22376">Minion of Terokk</a>" '),
  (@ENTRY*100+1, 9, 103, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 22376, 4, 30000, 0, 0, 0, 8, 0, 0, 0, 0, -1641.94, 5426.66, -44.0092, 1.96429, 'Defender Grashna - In Combat - Summon "<a href="http://wowhead.com/npc=22376">Minion of Terokk</a>" '),
  (@ENTRY*100+1, 9, 104, 0, 0, 0, 100, 0, 20000, 20000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Defender Grashna - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 105, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 22376, 4, 30000, 0, 0, 0, 8, 0, 0, 0, 0, -1635.09, 5431.15, -42.9365, 2.11351, 'Defender Grashna - In Combat - Summon "<a href="http://wowhead.com/npc=22376">Minion of Terokk</a>" '),
  (@ENTRY*100+1, 9, 106, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 22376, 4, 30000, 0, 0, 0, 8, 0, 0, 0, 0, -1641.94, 5426.66, -44.0092, 1.96429, 'Defender Grashna - In Combat - Summon "<a href="http://wowhead.com/npc=22376">Minion of Terokk</a>" '),
  (@ENTRY*100+1, 9, 107, 0, 0, 0, 100, 0, 20000, 20000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Defender Grashna - In Combat - Say Line 1 '),
  (@ENTRY*100+1, 9, 108, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 22376, 4, 30000, 0, 0, 0, 8, 0, 0, 0, 0, -1635.09, 5431.15, -42.9365, 2.11351, 'Defender Grashna - In Combat - Summon "<a href="http://wowhead.com/npc=22376">Minion of Terokk</a>" '),
  (@ENTRY*100+1, 9, 109, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 22376, 4, 30000, 0, 0, 0, 8, 0, 0, 0, 0, -1641.94, 5426.66, -44.0092, 1.96429, 'Defender Grashna - In Combat - Summon "<a href="http://wowhead.com/npc=22376">Minion of Terokk</a>" '),
  (@ENTRY*100+1, 9, 110, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 22376, 4, 30000, 0, 0, 0, 8, 0, 0, 0, 0, -1647.75, 5423.67, -44.4454, 1.76008, 'Defender Grashna - In Combat - Summon "<a href="http://wowhead.com/npc=22376">Minion of Terokk</a>" '),
  (@ENTRY*100+1, 9, 111, 0, 0, 0, 100, 0, 20000, 20000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Defender Grashna - In Combat - Say Line 2 '),
  (@ENTRY*100+1, 9, 112, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 22375, 4, 30000, 0, 0, 0, 8, 0, 0, 0, 0, -1631.35, 5409.77, -43.5877, 2.0232, 'Defender Grashna - In Combat - Summon "<a href="http://wowhead.com/npc=22375">Avatar of Terokk</a>" ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "More Minions of Terokk are coming!", 12, 0, 100, 0, 0, "Defender Grashna"),
  (@ENTRY, 1, 0, "The invaders persist! Hold them off!", 12, 0, 100, 0, 0, "Defender Grashna"),
  (@ENTRY, 2, 0, "An Avatar of Terokk!! To arms!", 12, 0, 100, 0, 0, "Defender Grashna"),
  (@ENTRY, 3, 0, "The Avatar of Terokk has been defeated! Death to Terokk! Death to Skettis!", 12, 0, 100, 0, 0, "Defender Grashna"),
  (@ENTRY, 4, 0, "%s points to the sky above.", 16, 0, 100, 0, 0, "Defender Grashna - ");
-- NPC 22375
SET @ENTRY = 22375;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -1641.12, 5436.65, -43.3445, 0.803601, 'Avatar of Terokk - On Just Summoned - Move To Pos '),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -1641.12, 5436.65, -43.3445, 0.803601, 'Avatar of Terokk - On Aggro - Move To Pos '),
  (@ENTRY, 0, 2, 0, 6, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 22373, 50, 0, 0, 0, 0, 0, 'Avatar of Terokk - On Death - Set Data 1 1 '),
  (@ENTRY, 0, 4, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 24193, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Avatar of Terokk - On Aggro - Cast "<a href="http://wowhead.com/spell=24193">Charge</a>" (No Repeat)'),
  (@ENTRY, 0, 5, 0, 0, 0, 100, 0, 6000, 9000, 11000, 14000, 11, 39068, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Avatar of Terokk - In Combat - Cast "<a href="http://wowhead.com/spell=39068">Feather Burst</a>" ');
UPDATE quest_template SET ObjectiveText1 = "Attack thwarted", EndText = "", ReqCreatureOrGOId1 = 22375, ReqCreatureOrGOId2 = 0, ReqCreatureOrGOCount1 = 1, ReqCreatureOrGOCount2 = 0, StartScript = 0 WHERE entry = 10879;
DELETE FROM quest_start_scripts WHERE id = 10879;

# SmartAIMgr::LoadSmartAIFromDB: Entry -310388 SourceType 0, Event 0, Missing Repeat flag.
-- GUID -310388 - ENTRY 22515
SET @ENTRY = -310388;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = 22515;DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 23, 0, 100, 0, 38034, 1, 500, 500, 75, 33344, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'World Trigger - On Has Aura "<a href="http://wowhead.com/spell=38034">Blue Beam</a>" - Add Aura "<a href="http://wowhead.com/spell=33344">Blue Banish State</a>" ');

# SmartAIMgr::LoadSmartAIFromDB: Entry -310699 SourceType 0, Event 2, Missing Repeat flag.
-- GUID -310699 - ENTRY 19680
SET @ENTRY = -310699;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = 19680;DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 38, 0, 100, 0, 0, 1, 0, 0, 12, 19153, 8, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Aldor Spawn Controller - On Data Set 0 1 - Summon "<a href="http://wowhead.com/npc=19153">Aldor Neophyte</a>" '),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 80, 31069900, 2, 0, 0, 0, 0, 9, 0, 19153, 0, 2, 0, 0, 0, 0, 'Aldor Spawn Controller - On Data Set 0 1 - Run Script <a href="/smartai/script/31069900">31069900</a> ');

# SmartAIMgr::LoadSmartAIFromDB: GameObject entry (101848) guid (17877) is not using SmartGameObjectAI, skipped loading.
DELETE FROM smart_scripts WHERE entryorguid = -17877 AND source_type = 1;

# Table `event_scripts` has out of range text id (dataint = 14 expected 2000000000-2000010000) in SCRIPT_COMMAND_TALK for script id 13470
# Table `event_scripts` has out of range text id (dataint = 15 expected 2000000000-2000010000) in SCRIPT_COMMAND_TALK for script id 13470
# Table `event_scripts` has out of range text id (dataint = 16 expected 2000000000-2000010000) in SCRIPT_COMMAND_TALK for script id 13470
# Table `event_scripts` has out of range text id (dataint = 17 expected 2000000000-2000010000) in SCRIPT_COMMAND_TALK for script id 13470
# Table `event_scripts` has out of range text id (dataint = 18 expected 2000000000-2000010000) in SCRIPT_COMMAND_TALK for script id 13470
UPDATE gameobject_template SET flags = 32 WHERE entry = 184725;
UPDATE creature_loot_template SET ChanceOrQuestChance = -100 WHERE entry = 18554 AND item = 29912;
DELETE FROM broadcast_text WHERE ID IN (14,15,16,17,18,18676,18677,18678,18680,18681);
INSERT INTO broadcast_text (ID, Language, MaleText, FemaleText, EmoteID0, EmoteID1, EmoteID2, EmoteDelay0, EmoteDelay1, EmoteDelay2, SoundId, Unk1, Unk2, VerifiedBuild) VALUES
  (18676,	0,	'5...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18677,	0,	'4...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18678,	0,	'3...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18680,	0,	'2...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (18681,	0,	'1...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019);
DELETE FROM event_scripts WHERE id = 13470;
INSERT INTO event_scripts (id, delay, command, datalong, datalong2, dataint, x, y, z, o) VALUES
  (13470,	0,	10,	21039,	2000,	0,	-2345.05,	3235.15,	2.98429,	0),
  (13470,	7,	0,	3,	0,	18676,	0,	0,	0,	0),
  (13470,	8,	0,	3,	0,	18677,	0,	0,	0,	0),
  (13470,	9,	0,	3,	0,	18678,	0,	0,	0,	0),
  (13470,	10,	0,	3,	0,	18680,	0,	0,	0,	0),
  (13470,	11,	0,	3,	0,	18681,	0,	0,	0,	0);

# `game_event_npc_vendor` game event id (67) has an item with non existing template (38518)
DELETE FROM item_template WHERE entry = 38518;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `dmg_min3`, `dmg_max3`, `dmg_type3`, `dmg_min4`, `dmg_max4`, `dmg_type4`, `dmg_min5`, `dmg_max5`, `dmg_type5`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `zone`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `Duration`) VALUES
  (38518,	0,	0,	-1,	'Cro\'s Apple',	50737,	1,	64,	1,	150,	37,	0,	-1,	-1,	5,	1,	0,	0,	0,	0,	0,	0,	0,	24,	24,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	50749,	0,	-1,	0,	0,	0,	1000,	0,	0,	0,	0,	-1,	0,	-1,	0,	0,	0,	0,	-1,	0,	-1,	0,	0,	0,	0,	-1,	0,	-1,	0,	0,	0,	0,	-1,	0,	-1,	0,	'For Cro Threadstrong!',	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	'',	0,	0,	0,	0,	0);

# `game_event_npc_vendor` game event id (66) has an item with non existing template (20240)
# `game_event_npc_vendor` game event id (66) has an item with non existing template (20241)
DELETE FROM game_event_npc_vendor WHERE item IN (20240,20241);


# CreatureTextMgr: Entry 16700, Group 6 in table `creature_texts` has Type 0 but this chat type is not a valid chat type for creatures. Defaulting to 12 (CHAT_MSG_MONSTER_SAY)
# CreatureTextMgr: Entry 16700, Group 7 in table `creature_texts` has Type 0 but this chat type is not a valid chat type for creatures. Defaulting to 12 (CHAT_MSG_MONSTER_SAY)
# CreatureTextMgr: Entry 16700, Group 8 in table `creature_texts` has Type 0 but this chat type is not a valid chat type for creatures. Defaulting to 12 (CHAT_MSG_MONSTER_SAY)
UPDATE creature_text SET type = 14 WHERE CreatureID = 16700 AND groupid IN (6,7,8);

