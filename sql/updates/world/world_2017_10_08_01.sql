/*
  Startup errors fixes
 */

# SmartAIMgr: Entry 18537 SourceType 0 Event 9 Action 11 has invalid target type for event, skipped.
-- NPC 18537
SET @ENTRY = 18537;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - On Data Set 0 1 - Say Line 0 '),
  (@ENTRY, 0, 1, 0, 38, 0, 100, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - On Data Set 0 2 - Say Line 1 '),
  (@ENTRY, 0, 2, 0, 38, 0, 100, 0, 0, 3, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - On Data Set 0 3 - Say Line 2 '),
  (@ENTRY, 0, 3, 0, 38, 0, 100, 0, 0, 4, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - On Data Set 0 4 - Say Line 3 '),
  (@ENTRY, 0, 4, 0, 38, 0, 100, 0, 0, 5, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - On Data Set 0 5 - Say Line 4 '),
  (@ENTRY, 0, 5, 0, 38, 0, 100, 0, 0, 6, 0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - On Data Set 0 6 - Say Line 6 '),
  (@ENTRY, 0, 6, 0, 38, 0, 100, 0, 0, 7, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - On Data Set 0 7 - Say Line 5 '),
  (@ENTRY, 0, 7, 0, 0, 0, 100, 0, 5000, 6000, 10000, 11000, 11, 14518, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - In Combat - Cast "<a href="http://wowhead.com/spell=14518">Crusader Strike</a>" '),
  (@ENTRY, 0, 8, 0, 0, 0, 100, 0, 10000, 15000, 30000, 35000, 11, 13005, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - In Combat - Cast "<a href="http://wowhead.com/spell=13005">Hammer of Justice</a>" '),
  (@ENTRY, 0, 9, 0, 9, 0, 100, 0, 0, 40, 4000, 6000, 11, 13952, 0, 0, 0, 0, 0, 102, 5, 40, 30, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=13952">Holy Light</a>" '),
  (@ENTRY, 0, 10, 0, 2, 0, 100, 512, 0, 30, 20000, 30000, 80, 1853706, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Adyen the Lightwarden - Between 0-30% HP - Run Script <a href="/smartai/script/1853706">1853706</a> (While Charmed)');

# SmartAIMgr::LoadSmartAIFromDB: Entry 18584 SourceType 0, Event 3, Missing Repeat flag.
-- NPC 18584
SET @ENTRY = 18584;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sal&#039;salabim - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 62, 0, 100, 0, 9435, 0, 0, 0, 80, 1858400, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sal&#039;salabim - On Gossip 9435 Option 0 Selected - Run Script <a href="/smartai/script/1858400">1858400</a> '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 0, 10000, 10000, 20000, 11, 31705, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Sal&#039;salabim - In Combat - Cast "<a href="http://wowhead.com/spell=31705">Magnetic Pull</a>" '),
  (@ENTRY, 0, 3, 0, 2, 0, 100, 1, 0, 1, 0, 0, 80, 1858401, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sal&#039;salabim - Between 0-1% HP - Run Script <a href="/smartai/script/1858401">1858401</a> (No Repeat)'),
  (@ENTRY, 0, 4, 5, 7, 0, 100, 0, 0, 0, 0, 0, 81, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sal&#039;salabim - On Evade - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 2, 35, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sal&#039;salabim - On Evade - Set Faction 35 ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 18635 SourceType 0, Event 1, Missing Repeat flag.
-- NPC 18635
SET @ENTRY = 18635;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 2, 10000, 20000, 10000, 20000, 11, 33480, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Deathsworn - In Combat - Cast "<a href="http://wowhead.com/spell=33480">Black Cleave</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 7500, 15000, 11, 11428, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Deathsworn - In Combat - Cast "<a href="http://wowhead.com/spell=11428">Knockdown</a>" '),
  (@ENTRY, 0, 2, 3, 2, 0, 100, 1, 0, 15, 0, 0, 11, 8599, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Deathsworn - Between 0-15% HP - Cast "<a href="http://wowhead.com/spell=8599">Enrage</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 0, 0, 15, 120000, 120000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Deathsworn - Between 0-15% HP - Say Line 0 '),
  (@ENTRY, 0, 4, 0, 25, 0, 100, 0, 0, 0, 0, 0, 28, 8599, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Deathsworn - On Reset - Remove Aura "<a href="http://wowhead.com/spell=8599">Enrage</a>" '),
  (@ENTRY, 0, 5, 0, 0, 0, 100, 4, 10000, 20000, 10000, 20000, 11, 38226, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Deathsworn - In Combat - Cast "<a href="http://wowhead.com/spell=38226">Black Cleave</a>" (Heroic Dungeon)');

# SmartAIMgr: Entry 18701 SourceType 0 Event 0 Action 11 uses min/max params wrong (75000/10000), skipped.
-- NPC 18701
SET @ENTRY = 18701;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 1500, 5000, 7500, 10000, 11, 12471, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Dark Vortex - In Combat - Cast "<a href="http://wowhead.com/spell=12471">Shadow Bolt</a>" ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 18794 SourceType 0, Event 6, Missing Repeat flag.
# SmartAIMgr::LoadSmartAIFromDB: Entry 18794 SourceType 0, Event 7, Missing Repeat flag.
# SmartAIMgr: Entry 18794 SourceType 0 Event 13 Action 11 uses non-existent Spell entry 0, skipped.
-- NPC 18794
SET @ENTRY = 18794;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 21, 0, 100, 0, 0, 0, 0, 0, 11, 32958, 0, 0, 0, 0, 0, 9, 0, 18793, 0, 15, 0, 0, 0, 0, 'Cabal Ritualist - On Reached Home - Cast "<a href="http://wowhead.com/spell=32958">Crystal Channel</a>" '),
  (@ENTRY, 0, 1, 2, 37, 0, 100, 0, 0, 0, 0, 0, 31, 1, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - On AI Initialize - Set Phase Random Between 1-4 '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - On AI Initialize - Store Current Phase '),
  (@ENTRY, 0, 3, 0, 25, 0, 100, 0, 0, 0, 0, 0, 164, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - On Reset - Restore Phase '),
  (@ENTRY, 0, 10, 0, 0, 1, 100, 0, 10000, 15000, 10000, 15000, 11, 12540, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - In Combat - Cast "<a href="http://wowhead.com/spell=12540">Gouge</a>" (Phase 1)'),
  (@ENTRY, 0, 20, 0, 0, 2, 100, 2, 0, 2500, 10000, 15000, 11, 33832, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - In Combat - Cast "<a href="http://wowhead.com/spell=33832">Arcane Missiles</a>" (Normal Dungeon)(Phase 2)'),
  (@ENTRY, 0, 21, 0, 0, 2, 100, 0, 10000, 20000, 10000, 20000, 11, 33487, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - In Combat - Cast "<a href="http://wowhead.com/spell=33487">Addle Humanoid</a>" (Phase 2)'),
  (@ENTRY, 0, 22, 0, 0, 2, 100, 4, 0, 2500, 10000, 15000, 11, 38263, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - In Combat - Cast "<a href="http://wowhead.com/spell=38263">Arcane Missiles</a>" (Heroic Dungeon)(Phase 2)'),
  (@ENTRY, 0, 30, 0, 37, 4, 100, 2, 0, 0, 0, 0, 58, 1, 15497, 3000, 3250, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - On AI Initialize - Install Caster Template (Normal Dungeon)(Phase 3)'),
  (@ENTRY, 0, 31, 0, 37, 4, 100, 4, 0, 0, 0, 0, 58, 1, 12675, 3000, 3250, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - On AI Initialize - Install Caster Template (Heroic Dungeon)(Phase 3)'),
  (@ENTRY, 0, 32, 0, 9, 4, 100, 2, 0, 10, 25000, 30000, 11, 15532, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - Within 0-10 Range - Cast "<a href="http://wowhead.com/spell=15532">Frost Nova</a>" (Normal Dungeon)(Phase 3)'),
  (@ENTRY, 0, 33, 0, 9, 4, 100, 4, 0, 10, 25000, 30000, 11, 12675, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - Within 0-10 Range - Cast "<a href="http://wowhead.com/spell=12675">Frostbolt</a>" (Heroic Dungeon)(Phase 3)'),
  (@ENTRY, 0, 40, 0, 0, 8, 100, 2, 2500, 5000, 10000, 15000, 11, 9574, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - In Combat - Cast "<a href="http://wowhead.com/spell=9574">Flame Buffet</a>" (Normal Dungeon)(Phase 4)'),
  (@ENTRY, 0, 41, 0, 0, 8, 100, 2, 5000, 10000, 10000, 15000, 11, 20795, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - In Combat - Cast "<a href="http://wowhead.com/spell=20795">Fire Blast</a>" (Normal Dungeon)(Phase 4)'),
  (@ENTRY, 0, 42, 0, 0, 8, 100, 4, 5000, 10000, 10000, 15000, 11, 14145, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Ritualist - In Combat - Cast "<a href="http://wowhead.com/spell=14145">Fire Blast</a>" (Heroic Dungeon)(Phase 4)'),
  (@ENTRY, 0, 50, 0, 15, 15, 100, 4, 30, 5000, 10000, 10000, 11, 17201, 0, 0, 0, 0, 0, 9, 21, 0, 0, 30, 0, 0, 0, 0, 'Cabal Ritualist - On Friendly CCed - Cast "<a href="http://wowhead.com/spell=17201">Dispel Magic</a>" (Heroic Dungeon)(Phase 1, Phase 2, Phase 3 and  Phase 4)');

# SmartAIMgr: Entry 18796 SourceType 0 Event 3 Action 11 uses min/max params wrong (5000/1500), skipped.
UPDATE smart_scripts SET event_param4 = 15000 WHERE entryorguid = 18796 AND source_type = 0 AND id = 3;

# SmartAIMgr::LoadSmartAIFromDB: Creature entry (18841) is not using SmartAI, skipped loading.
# SmartAIMgr::LoadSmartAIFromDB: Creature entry (18841) is not using SmartAI, skipped loading.
DELETE FROM smart_scripts WHERE entryorguid = 18841 AND source_type = 0;

# SmartAIMgr: EntryOrGuid 19556 using event(6) has invalid action type (0), skipped.
# SmartAIMgr: EntryOrGuid 19556 using event(7) has invalid action type (0), skipped.
# SmartAIMgr::LoadSmartAIFromDB: Entry 19556 SourceType 0, Event 12, Missing Repeat flag.

# SmartAIMgr: Entry 19946 SourceType 0 Event 2 Action 39 uses non-existent Creature entry 18112 as target_param1, skipped.
-- NPC 19946
SET @ENTRY = 19946;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 5000, 10000, 15000, 20000, 11, 13730, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Slaver - In Combat - Cast "<a href="http://wowhead.com/spell=13730">Demoralizing Shout</a>" '),
  (@ENTRY, 0, 1, 2, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Slaver - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 39, 20, 0, 0, 0, 0, 0, 9, 6, 18122, 0, 20, 0, 0, 0, 0, 'Darkcrest Slaver - On Aggro - Call For Help ');

# SmartAIMgr: Entry 20143 SourceType 0 Event 1 Action 12 creature summon: There is a summon spell for creature entry 20145 (SpellId: 34943, effect: 0)
-- NPC 20143
SET @ENTRY = 20143;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 60, 0, 100, 0, 2000, 5000, 15000, 23000, 11, 34943, 0, 30000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Void Spawner - Quest - Warp Rifts - On Update - Cast "<a href="http://wowhead.com/spell=34943">Summon Unstable Voidwalker</a>" '),
  (@ENTRY, 0, 2, 0, 37, 0, 100, 0, 0, 0, 0, 0, 41, 120000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Void Spawner - Quest - Warp Rifts - On AI Initialize - Despawn In 120000ms ');
-- NPC 20145
SET @ENTRY = 20145;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 3000, 6000, 10000, 12000, 11, 33914, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Unstable Voidwalker - In Combat - Cast "<a href="http://wowhead.com/spell=33914">Shadowstrike</a>" '),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 1, 30000, 30000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Unstable Voidwalker - Out of Combat - Despawn Instant (No Repeat)');

# SmartAIMgr::LoadSmartAIFromDB: Creature entry (20343) is not using SmartAI, skipped loading.
DELETE FROM smart_scripts WHERE entryorguid = 20343 AND source_type = 0;

# SmartAIMgr: Entry 20445 SourceType 0 Event 2 Action 12 creature summon: There is a summon spell for creature entry 20669 (SpellId: 35425, effect: 0)
# SmartAIMgr: Entry 20445 SourceType 0 Event 3 Action 12 creature summon: There is a summon spell for creature entry 20669 (SpellId: 35425, effect: 0)
-- NPC 20445
SET @ENTRY = 20445;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 4000, 4000, 6000, 6000, 11, 16568, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Mal&#039;druk the Soulrender - In Combat - Cast "<a href="http://wowhead.com/spell=16568">Mind Flay</a>" '),
  (@ENTRY, 0, 1, 2, 2, 0, 100, 1, 0, 75, 0, 0, 11, 35425, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Mal&#039;druk the Soulrender - Between 0-75% HP - Cast "<a href="http://wowhead.com/spell=35425">Summon Shadow Image</a>" (No Repeat)'),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 1, 0, 75, 0, 0, 11, 35425, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Mal&#039;druk the Soulrender - Between 0-75% HP - Cast "<a href="http://wowhead.com/spell=35425">Summon Shadow Image</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 7, 0, 100, 0, 0, 0, 0, 0, 51, 0, 0, 0, 0, 0, 0, 9, 0, 20669, 0, 30, 0, 0, 0, 0, 'Mal&#039;druk the Soulrender - On Evade - Kill Target ');
-- NPC 20669
SET @ENTRY = 20669;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', faction = 45 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 2, 54, 0, 100, 0, 0, 0, 0, 0, 11, 35424, 2, 0, 0, 0, 0, 19, 0, 20445, 20, 0, 0, 0, 0, 0, 'Shade of Mal&#039;druk - On Just Summoned - Cast "<a href="http://wowhead.com/spell=35424">Soul Shadows</a>" '),
  (@ENTRY, 0, 2, 0, 54, 0, 100, 0, 0, 0, 0, 0, 155, 35424, 67, 0, 0, 0, 0, 19, 0, 20445, 20, 0, 0, 0, 0, 0, 'Shade of Mal&#039;druk - On Just Summoned - Assist Target ');

# SmartAIMgr: Warning: Entry 20600 SourceType 0 Event 2 Action 50 gameobject summon: There is a summon spell for gameobject entry 185569 (SpellId: 39891, effect: 0)
-- NPC 20216
SET @ENTRY = 20216;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 20000, 20000, 20000, 25000, 11, 38771, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grulloc - In Combat - Cast "<a href="http://wowhead.com/spell=38771">Burning Rage</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 7000, 7000, 12000, 16000, 11, 21055, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Grulloc - In Combat - Cast "<a href="http://wowhead.com/spell=21055">Crush Armor</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 10000, 10000, 45000, 45000, 11, 38772, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Grulloc - In Combat - Cast "<a href="http://wowhead.com/spell=38772">Grievous Wound</a>" '),
  (@ENTRY, 0, 3, 0, 6, 0, 100, 0, 0, 0, 0, 0, 85, 39890, 2, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Grulloc - On Death - Invoker Cast "<a href="http://wowhead.com/spell=39890">Grulloc: Summon Grulloc"s Dragon Skull Chest</a>" '),
  (@ENTRY, 0, 4, 0, 4, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 'Grulloc - On Aggro - Store Targetlist 1 ');
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 22 AND SourceGroup = 4 AND SourceEntry = @ENTRY AND ConditionTypeOrReference = 9 AND ConditionValue1 = 10996;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment)
VALUES (22, 4, @ENTRY, 0, 0, 9, 0, 10996, 0, 0, 0, 0, 0, '', NULL);

# SmartAIMgr: Entry 20610 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 20610 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
# SmartAIMgr: Entry 20610 SourceType 0 Event 2 Action 1 using non-existent Text id 1, skipped.
# SmartAIMgr: Entry 20610 SourceType 0 Event 2 Action 1 uses non-existent text 1, skipped.
-- NPC 20610
SET @ENTRY = 20610;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 5, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - On Aggro - Say Line 0 '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 8000, 11000, 11, 32019, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - In Combat - Cast "<a href="http://wowhead.com/spell=32019">Gore</a>" '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 20, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - Between 0-20% HP - Say Line 1 (No Repeat)'),
  (@ENTRY, 0, 3, 0, 8, 0, 100, 0, 35771, 0, 0, 0, 80, @ENTRY*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - On Spellhit "<a href="http://wowhead.com/spell=35771">Tag Subbued Talbuk</a>" - Run Script <a href="/smartai/script/2061000">2061000</a> '),
  (@ENTRY, 0, 4, 0, 11, 0, 100, 0, 0, 0, 0, 0, 19, 386, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - On Respawn - Set Unit Flag Non Attackable, Not Atackable 1 and  Immune to PC '),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 19, 2, 20777, 30, 0, 0, 0, 0, 0, 'Talbuk Doe - On Aggro - Set Data 0 1 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100, 9, 98, 0, 0, 0, 100, 0, 0, 0, 0, 0, 103, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - In Combat - Set Root On '),
  (@ENTRY*100, 9, 99, 0, 0, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - In Combat - Set React State Passive '),
  (@ENTRY*100, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 85, 40347, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - In Combat - Invoker Cast "<a href="http://wowhead.com/spell=40347">Talbuk Tagging Credit</a>" '),
  (@ENTRY*100, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 75, 14915, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - In Combat - Add Aura "<a href="http://wowhead.com/spell=14915">Self Visual - Sleep Until Cancelled (DND)</a>" '),
  (@ENTRY*100, 9, 102, 0, 0, 0, 100, 0, 0, 0, 0, 0, 18, 33685894, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - In Combat - Set Unit Flag Non Attackable, Disable Move, Not Atackable 1, Immune to PC, Pacified and  Not Selectable '),
  (@ENTRY*100, 9, 103, 0, 0, 0, 100, 0, 0, 0, 0, 0, 18, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - In Combat - Set Unit Flag Server Controlled '),
  (@ENTRY*100, 9, 105, 0, 0, 0, 100, 0, 15000, 15000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Doe - In Combat - Despawn Instant ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s calls for the aid of a nearby male!", 16, 0, 100, 0, 0, "Talbuk Doe - "),
  (@ENTRY, 1, 0, "%s seems to have weakened.", 16, 0, 100, 0, 0, "Talbuk Doe - ");

# SmartAIMgr: Entry 20777 SourceType 0 Event 1 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 20777 SourceType 0 Event 1 Action 1 uses non-existent text 0, skipped.
-- NPC 20777
SET @ENTRY = 20777;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 4000, 6000, 8000, 11000, 11, 32023, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Sire - In Combat - Cast "<a href="http://wowhead.com/spell=32023">Hoof Stomp</a>" '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 20, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Sire - Between 0-20% HP - Say Line 1 (No Repeat)'),
  (@ENTRY, 0, 2, 0, 8, 0, 100, 0, 35771, 0, 0, 0, 80, 2061000, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Sire - On Spellhit "<a href="http://wowhead.com/spell=35771">Tag Subbued Talbuk</a>" - Run Script <a href="/smartai/script/2061000">2061000</a> '),
  (@ENTRY, 0, 3, 0, 11, 0, 100, 0, 0, 0, 0, 0, 19, 33685894, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Sire - On Respawn - Set Unit Flag Non Attackable, Disable Move, Not Atackable 1, Immune to PC, Pacified and  Not Selectable '),
  (@ENTRY, 0, 4, 5, 38, 0, 100, 0, 0, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 0, 40, 0, 0, 0, 0, 0, 0, 'Talbuk Sire - On Data Set 0 1 - Start Attacking '),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Talbuk Sire - On Data Set 0 1 - Say Line 0 ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s rushes to the aid of a nerby doe!", 16, 0, 100, 0, 0, "Talbuk Sire - "),
  (@ENTRY, 1, 0, "%s seems to have weakened.", 16, 0, 100, 0, 0, "Talbuk Sire - ");

# SmartAIMgr::LoadSmartAIFromDB: Entry 20813 SourceType 0, Event 3, Missing Repeat flag.
-- NPC 20813
SET @ENTRY = 20813;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 0, 35724, 0, 0, 0, 11, 34386, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, Barracks - On Spellhit "<a href="http://wowhead.com/spell=35724">Throw Torch</a>" - Cast "<a href="http://wowhead.com/spell=34386">Create Hellfire Fire</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 35724, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 9, 0, 20813, 0, 70, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, Barracks - On Spellhit "<a href="http://wowhead.com/spell=35724">Throw Torch</a>" - Set Data 0 1 '),
  (@ENTRY, 0, 2, 0, 38, 0, 100, 0, 0, 1, 0, 0, 22, 1, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, Barracks - On Data Set 0 1 - Set Event Phase 1 '),
  (@ENTRY, 0, 3, 4, 103, 1, 100, 0, 1, 0, 0, 0, 11, 34386, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, Barracks - On Enter Phase 1 - Cast "<a href="http://wowhead.com/spell=34386">Create Hellfire Fire</a>" (Phase 1)'),
  (@ENTRY, 0, 4, 0, 61, 1, 100, 0, 2000, 15000, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, Barracks - On Enter Phase 1 - Set Event Phase 0 (Phase 1)');

# SmartAIMgr::LoadSmartAIFromDB: Entry 20814 SourceType 0, Event 3, Missing Repeat flag.
-- NPC 20814
SET @ENTRY = 20814;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 0, 35724, 0, 0, 0, 11, 34386, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, Stable - On Spellhit "<a href="http://wowhead.com/spell=35724">Throw Torch</a>" - Cast "<a href="http://wowhead.com/spell=34386">Create Hellfire Fire</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 35724, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 9, 0, 20814, 0, 30, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, Stable - On Spellhit "<a href="http://wowhead.com/spell=35724">Throw Torch</a>" - Set Data 0 1 '),
  (@ENTRY, 0, 2, 0, 38, 0, 100, 0, 0, 1, 0, 0, 22, 1, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, Stable - On Data Set 0 1 - Set Event Phase 1 '),
  (@ENTRY, 0, 3, 4, 103, 1, 100, 0, 1, 0, 0, 0, 11, 34386, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, Stable - On Enter Phase 1 - Cast "<a href="http://wowhead.com/spell=34386">Create Hellfire Fire</a>" (Phase 1)'),
  (@ENTRY, 0, 4, 0, 61, 1, 100, 0, 2000, 15000, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, Stable - On Enter Phase 1 - Set Event Phase 0 (Phase 1)');

# SmartAIMgr::LoadSmartAIFromDB: Entry 20815 SourceType 0, Event 3, Missing Repeat flag.
-- NPC 20815
SET @ENTRY = 20815;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 0, 35724, 0, 0, 0, 11, 34386, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, East Hovel - On Spellhit "<a href="http://wowhead.com/spell=35724">Throw Torch</a>" - Cast "<a href="http://wowhead.com/spell=34386">Create Hellfire Fire</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 35724, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 9, 0, 20815, 0, 30, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, East Hovel - On Spellhit "<a href="http://wowhead.com/spell=35724">Throw Torch</a>" - Set Data 0 1 '),
  (@ENTRY, 0, 2, 0, 38, 0, 100, 0, 0, 1, 0, 0, 22, 1, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, East Hovel - On Data Set 0 1 - Set Event Phase 1 '),
  (@ENTRY, 0, 3, 4, 103, 1, 100, 0, 1, 0, 0, 0, 11, 34386, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, East Hovel - On Enter Phase 1 - Cast "<a href="http://wowhead.com/spell=34386">Create Hellfire Fire</a>" (Phase 1)'),
  (@ENTRY, 0, 4, 0, 61, 1, 100, 0, 2000, 15000, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, East Hovel - On Enter Phase 1 - Set Event Phase 0 (Phase 1)');

# SmartAIMgr::LoadSmartAIFromDB: Entry 20816 SourceType 0, Event 3, Missing Repeat flag.
-- NPC 20816
SET @ENTRY = 20816;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 0, 35724, 0, 0, 0, 11, 34386, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, West Hovel - On Spellhit "<a href="http://wowhead.com/spell=35724">Throw Torch</a>" - Cast "<a href="http://wowhead.com/spell=34386">Create Hellfire Fire</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 35724, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 9, 0, 20816, 0, 30, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, West Hovel - On Spellhit "<a href="http://wowhead.com/spell=35724">Throw Torch</a>" - Set Data 0 1 '),
  (@ENTRY, 0, 2, 0, 38, 0, 100, 0, 0, 1, 0, 0, 22, 1, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, West Hovel - On Data Set 0 1 - Set Event Phase 1 '),
  (@ENTRY, 0, 3, 4, 103, 1, 100, 0, 1, 0, 0, 0, 11, 34386, 36, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, West Hovel - On Enter Phase 1 - Cast "<a href="http://wowhead.com/spell=34386">Create Hellfire Fire</a>" (Phase 1)'),
  (@ENTRY, 0, 4, 0, 61, 1, 100, 0, 2000, 15000, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zeth&#039;Gor Quest Credit Marker, West Hovel - On Enter Phase 1 - Set Event Phase 0 (Phase 1)');

# SmartAIMgr: Entry 20851 SourceType 0 Event 1 Action 12 creature summon: There is a summon spell for creature entry 20845 (SpellId: 55003, effect: 0)
-- NPC 20666
SET @ENTRY = 20666;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 80, 2066600, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blade&#039;s Edge - Orb Trigger 01 - On Data Set 0 1 - Run Script <a href="/smartai/script/2066600">2066600</a> '),
  (@ENTRY, 0, 1, 0, 38, 0, 100, 0, 6, 6, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blade&#039;s Edge - Orb Trigger 01 - On Data Set 6 6 - Evade '),
  (@ENTRY, 0, 10, 0, 103, 1, 100, 0, 1, 0, 0, 0, 12, 21025, 8, 0, 0, 0, 0, 8, 0, 0, 0, 0, 2809.74, 5250.4, 268, 0.364556, 'Blade&#039;s Edge - Orb Trigger 01 - On Enter Phase 1 - Summon "<a href="http://wowhead.com/npc=21025">Blade"s Edge - Nexus Prince Event - Orb01</a>" (Phase 1)'),
  (@ENTRY, 0, 20, 0, 103, 2, 100, 0, 2, 0, 0, 0, 12, 21025, 8, 0, 0, 0, 0, 8, 0, 0, 0, 0, 2809.74, 5250.4, 269.034, 0.364556, 'Blade&#039;s Edge - Orb Trigger 01 - On Enter Phase 2 - Summon "<a href="http://wowhead.com/npc=21025">Blade"s Edge - Nexus Prince Event - Orb01</a>" (Phase 2)'),
  (@ENTRY, 0, 30, 0, 103, 4, 100, 0, 3, 0, 0, 0, 12, 21025, 8, 0, 0, 0, 0, 8, 0, 0, 0, 0, 2809.74, 5250.4, 269.734, 0.364556, 'Blade&#039;s Edge - Orb Trigger 01 - On Enter Phase 3 - Summon "<a href="http://wowhead.com/npc=21025">Blade"s Edge - Nexus Prince Event - Orb01</a>" (Phase 3)'),
  (@ENTRY, 0, 40, 0, 103, 8, 100, 0, 4, 0, 0, 0, 12, 21025, 8, 0, 0, 0, 0, 8, 0, 0, 0, 0, 2809.74, 5250.4, 270.427, 0.364556, 'Blade&#039;s Edge - Orb Trigger 01 - On Enter Phase 4 - Summon "<a href="http://wowhead.com/npc=21025">Blade"s Edge - Nexus Prince Event - Orb01</a>" (Phase 4)'),
  (@ENTRY, 0, 50, 51, 103, 16, 100, 0, 5, 0, 0, 0, 12, 50124, 8, 0, 0, 0, 0, 8, 0, 0, 0, 0, 2809.58, 5250.83, 276.547, 5.52908, 'Blade&#039;s Edge - Orb Trigger 01 - On Enter Phase 5 - Summon "<a href="http://wowhead.com/npc=50124">Blade"s Edge - Nexus Prince Event - Orb02</a>" (Phase 5)'),
  (@ENTRY, 0, 51, 0, 61, 16, 100, 0, 0, 0, 0, 0, 51, 0, 0, 0, 0, 0, 0, 9, 0, 21025, 0, 20, 0, 0, 0, 0, 'Blade&#039;s Edge - Orb Trigger 01 - On Enter Phase 5 - Kill Target (Phase 5)');
-- NPC 21057
SET @ENTRY = 21057;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 2, 54, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nexus-Prince Razaan - On Just Summoned - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 4, 6, 0, 100, 0, 0, 0, 0, 0, 50, 185033, 60000, 1, 0, 0, 0, 1, 8, 0, 0, 0, 0, 0, 0, 0, 'Nexus-Prince Razaan - On Death - Summon GO "<a href="http://wowhead.com/object=185033">Collection of Souls</a>" '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 10, 0, 72092, 20666, 0, 0, 0, 0, 0, 'Nexus-Prince Razaan - On Just Summoned - Set Event Phase 0 '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 10000, 15000, 20000, 30000, 11, 35924, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nexus-Prince Razaan - In Combat - Cast "<a href="http://wowhead.com/spell=35924">Energy Flux</a>" '),
  (@ENTRY, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 6, 6, 0, 0, 0, 0, 10, 0, 72092, 20666, 0, 0, 0, 0, 0, 'Nexus-Prince Razaan - On Death - Set Data 6 6 ');
-- NPC 20851
SET @ENTRY = 20851;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 2, 0, 60, 0, 100, 0, 1000, 1000, 1000, 1000, 45, 0, 2, 0, 0, 0, 0, 19, 0, 20845, 1, 0, 0, 0, 0, 0, 'Blade&#039;s Edge - Deadsoul Orb Flight 01 - On Update - Set Data 0 2 ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 21052 SourceType 0, Event 2, Missing Repeat flag.
-- NPC 21052
SET @ENTRY = 21052;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 80, @ENTRY*100+1, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Camera Shaker - Altar of Damnation - On Data Set 1 1 - Run Script <a href="/smartai/script/2105201">2105201</a> '),
  (@ENTRY, 0, 1, 0, 60, 1, 100, 0, 0, 2000, 2000, 5000, 11, 35997, 0, 0, 0, 0, 0, 9, 4, 21052, 20, 80, 0, 0, 0, 0, 'Camera Shaker - Altar of Damnation - On Update - Cast "<a href="http://wowhead.com/spell=35997">Fel Flames</a>" (Phase 1)');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Camera Shaker - Altar of Damnation - In Combat - Set Event Phase 1 '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 10000, 15000, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Camera Shaker - Altar of Damnation - In Combat - Set Event Phase 0 ');

# SmartAIMgr: Entry 21104 SourceType 0 Event 1 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 21104 SourceType 0 Event 1 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 21104;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "History is about to be rewritten!", 14, 0, 100, 0, 0, "Rift Keeper - "),
  (@ENTRY, 0, 1, "Let the siege begin!", 14, 0, 100, 0, 0, "Rift Keeper - "),
  (@ENTRY, 0, 2, "No! The rift...", 14, 0, 100, 0, 0, "Rift Keeper - "),
  (@ENTRY, 0, 3, "The sands of time shall be scattered to the winds!", 14, 0, 100, 0, 0, "Rift Keeper - "),
  (@ENTRY, 0, 4, "You will accomplish nothing!", 14, 0, 100, 0, 0, "Rift Keeper - "),
  (@ENTRY, 0, 5, "You will never defeat us all!", 12, 0, 100, 0, 0, "Rift Keeper - ");

# SmartAIMgr: Entry 21279 SourceType 0 Event 3 Action 12 creature summon: There is a summon spell for creature entry 21306 (SpellId: 36555, effect: 0)
-- NPC 21279
SET @ENTRY = 21279;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 4, 20, 0, 100, 0, 10242, 0, 0, 0, 80, 2127901, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Apothecary Albreck - On Quest "<a href="http://wowhead.com/quest=10242">Spinebreaker Post</a>" Rewarded - Run Script <a href="/smartai/script/2127901">2127901</a> '),
  (@ENTRY, 0, 1, 2, 40, 2, 100, 1, 10, 21279, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Apothecary Albreck - On Waypoint 10 Reached - Say Line 4 (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 2, 6, 61, 2, 100, 1, 10, 21279, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Apothecary Albreck - On Waypoint 10 Reached - Set Event Phase 0 (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 3, 0, 60, 1, 100, 0, 0, 0, 66, 66, 11, 36555, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Apothecary Albreck - On Update - Cast "<a href="http://wowhead.com/spell=36555">Summon Cursed Scarabs</a>" (Phase 1)'),
  (@ENTRY, 0, 4, 5, 61, 0, 100, 1, 10242, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Apothecary Albreck - On Quest "<a href="http://wowhead.com/quest=10242">Spinebreaker Post</a>" Rewarded - Store Targetlist 0 (No Repeat)'),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 10242, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 'Apothecary Albreck - On Quest "<a href="http://wowhead.com/quest=10242">Spinebreaker Post</a>" Rewarded - Set Orientation 0 '),
  (@ENTRY, 0, 6, 0, 61, 2, 100, 0, 10, 21279, 0, 0, 66, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 'Apothecary Albreck - On Waypoint 10 Reached - Set Orientation 0 (Phase 2)');
-- NPC 21306
SET @ENTRY = 21306;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 54, 0, 25, 1, 0, 0, 0, 0, 2, 14, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cursed Scarab - On Just Summoned - Set Faction 14 (No Repeat)'),
  (@ENTRY, 0, 1, 2, 54, 0, 100, 1, 0, 0, 0, 0, 59, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cursed Scarab - On Just Summoned - Set Run On (No Repeat)'),
  (@ENTRY, 0, 2, 3, 61, 0, 100, 1, 0, 0, 0, 0, 89, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cursed Scarab - On Just Summoned - Start Random Movement (No Repeat)'),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 20000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cursed Scarab - On Just Summoned - Despawn In 20000ms ');

# SmartAIMgr: EntryOrGuid 21315 using event(2) has invalid action type (0), skipped.
-- NPC 21315
SET @ENTRY = 21315;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 60, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ruul the Darkener - On AI Initialize - Disable Gravity '),
  (@ENTRY, 0, 1, 0, 11, 0, 100, 0, 0, 0, 0, 0, 53, 0, 21315, 0, 0, 2000, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ruul the Darkener - On Respawn - Start Waypoint 21315 '),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 'Ruul the Darkener - On Aggro - Store Targetlist 1 '),
  (@ENTRY, 0, 3, 4, 6, 0, 100, 0, 0, 0, 0, 0, 11, 38343, 2, 20000, 0, 1, 0, 1, 8, 0, 0, 0, 0, 0, 0, 0, 'Ruul the Darkener - On Death - Cast "<a href="http://wowhead.com/spell=38343">Summon Ruul"s Netherdrake</a>" '),
  (@ENTRY, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 4, 22106, 5, 0, 0, 0, 0, 0, 'Ruul the Darkener - On Death - Send Target 1 '),
  (@ENTRY, 0, 5, 0, 0, 0, 100, 0, 15000, 20000, 15000, 20000, 11, 35871, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Ruul the Darkener - In Combat - Cast "<a href="http://wowhead.com/spell=35871">Spellbreaker</a>" '),
  (@ENTRY, 0, 6, 0, 0, 0, 100, 0, 5000, 10000, 7500, 12500, 11, 15284, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Ruul the Darkener - In Combat - Cast "<a href="http://wowhead.com/spell=15284">Cleave</a>" '),
  (@ENTRY, 0, 7, 0, 0, 0, 100, 0, 15000, 20000, 20000, 30000, 11, 39153, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Ruul the Darkener - In Combat - Cast "<a href="http://wowhead.com/spell=39153">Darkfury</a>" '),
  (@ENTRY, 0, 8, 0, 40, 0, 100, 0, 4, 21315, 0, 0, 60, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ruul the Darkener - On Waypoint 4 Reached - Enable Gravity ');
-- NPC 22106
SET @ENTRY = 22106;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 60, 0, 100, 1, 250, 250, 0, 0, 49, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Ruul&#039;s Netherdrake - On Update - Start Attacking (No Repeat)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 5000, 10000, 15000, 20000, 11, 38344, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Ruul&#039;s Netherdrake - In Combat - Cast "<a href="http://wowhead.com/spell=38344">Arcane Blast</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 10000, 15000, 15000, 20000, 11, 36513, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Ruul&#039;s Netherdrake - In Combat - Cast "<a href="http://wowhead.com/spell=36513">Intangible Presence</a>" ');

# SmartAIMgr: Entry 21316 SourceType 0 Event 2 Action 11 uses non-existent Spell entry 12743, skipped.
DELETE FROM spell_template WHERE entry = 12743;
INSERT INTO spell_template (entry, category, dispel, mechanic, attributes, attributesEx, attributesEx2, attributesEx3, attributesEx4, attributesEx5, attributesEx6, stances, stancesNot, targets, targetCreatureType, requiresSpellFocus, facingCasterFlags, casterAuraState, targetAuraState, casterAuraStateNot, targetAuraStateNot, castingTimeIndex, recoveryTime, categoryRecoveryTime, interruptFlags, auraInterruptFlags, channelInterruptFlags, procFlags, procChance, procCharges, maxLevel, baseLevel, spellLevel, durationIndex, powerType, manaCost, manaCostPerlevel, manaPerSecond, manaPerSecondPerLevel, rangeIndex, speed, stackAmount, totem1, totem2, reagent1, reagent2, reagent3, reagent4, reagent5, reagent6, reagent7, reagent8, reagentCount1, reagentCount2, reagentCount3, reagentCount4, reagentCount5, reagentCount6, reagentCount7, reagentCount8, equippedItemClass, equippedItemSubClassMask, equippedItemInventoryTypeMask, effect1, effect2, effect3, effectDieSides1, effectDieSides2, effectDieSides3, effectBaseDice1, effectBaseDice2, effectBaseDice3, effectDicePerLevel1, effectDicePerLevel2, effectDicePerLevel3, effectRealPointsPerLevel1, effectRealPointsPerLevel2, effectRealPointsPerLevel3, effectBasePoints1, effectBasePoints2, effectBasePoints3, effectMechanic1, effectMechanic2, effectMechanic3, effectImplicitTargetA1, effectImplicitTargetA2, effectImplicitTargetA3, effectImplicitTargetB1, effectImplicitTargetB2, effectImplicitTargetB3, effectRadiusIndex1, effectRadiusIndex2, effectRadiusIndex3, effectApplyAuraName1, effectApplyAuraName2, effectApplyAuraName3, effectAmplitude1, effectAmplitude2, effectAmplitude3, effectMultipleValue1, effectMultipleValue2, effectMultipleValue3, effectChainTarget1, effectChainTarget2, effectChainTarget3, effectItemType1, effectItemType2, effectItemType3, effectMiscValue1, effectMiscValue2, effectMiscValue3, effectMiscValueB1, effectMiscValueB2, effectMiscValueB3, effectTriggerSpell1, effectTriggerSpell2, effectTriggerSpell3, effectPointsPerComboPoint1, effectPointsPerComboPoint2, effectPointsPerComboPoint3, spellVisual, spellIconID, activeIconID, spellName1, spellName2, spellName3, spellName4, spellName5, spellName6, spellName7, spellName8, spellName9, spellName10, spellName11, spellName12, spellName13, spellName14, spellName15, spellName16, rank1, rank2, rank3, rank4, rank5, rank6, rank7, rank8, rank9, rank10, rank11, rank12, rank13, rank14, rank15, rank16, manaCostPercentage, startRecoveryCategory, startRecoveryTime, maxTargetLevel, spellFamilyName, spellFamilyFlags, maxAffectedTargets, dmgClass, preventionType, dmgMultiplier1, dmgMultiplier2, dmgMultiplier3, totemCategory1, totemCategory2, areaId, schoolMask, customAttributesFlags) VALUES
  (12743,	0,	0,	0,	134217984,	268435456,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	101,	0,	0,	0,	0,	21,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	23,	0,	0,	3000,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	12744,	0,	0,	0,	0,	0,	8719,	1,	0,	'Immolation',	'',	'Immoler',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0);
-- NPC 21316
SET @ENTRY = 21316;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 1, 0, 0, 0, 0, 11, 16245, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Deathforged Infernal - On Respawn - Cast "<a href="http://wowhead.com/spell=16245">Freeze Anim</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 8, 0, 100, 512, 41441, 0, 0, 0, 37, 16245, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Deathforged Infernal - On Spellhit "<a href="http://wowhead.com/spell=41441">Acid Geyser</a>" - Die (While Charmed)'),
  (@ENTRY, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 12743, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Deathforged Infernal - On Reset - Cast "<a href="http://wowhead.com/spell=12743">Immolation</a>" ');

# SmartAIMgr: Entry 21332 SourceType 0 Event 1 Action 29 has maxDist 0 as target_param1, skipped.
-- NPC 21332
SET @ENTRY = 21332;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 80, 2133200, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Spirit Hunter - On Data Set 1 1 - Run Script <a href="/smartai/script/2133200">2133200</a> '),
  (@ENTRY, 0, 1, 0, 54, 0, 100, 0, 0, 0, 0, 0, 29, 5, 120, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 'Spirit Hunter - On Just Summoned - Follow Target '),
  (@ENTRY, 0, 2, 0, 1, 0, 100, 0, 0, 1000, 1000, 1000, 45, 1, 1, 0, 0, 0, 0, 9, 4, 21334, 0, 20, 0, 0, 0, 0, 'Spirit Hunter - Out of Combat - Set Data 1 1 '),
  (@ENTRY, 0, 3, 0, 38, 0, 100, 0, 2, 1, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Spirit Hunter - On Data Set 2 1 - Say Line 2 ');

# SmartAIMgr: Entry 21338 SourceType 0 Event 0 Action 30 attempts to set invalid phase, skipped.
-- NPC 21338
SET @ENTRY = 21338;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 37, 0, 100, 0, 0, 0, 0, 0, 31, 1, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - On AI Initialize - Set Phase Random Between 1-4 '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - On AI Initialize - Store Current Phase '),
  (@ENTRY, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 164, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - On Reset - Restore Phase '),
  (@ENTRY, 0, 10, 0, 0, 1, 100, 2, 0, 3000, 3000, 3500, 11, 15547, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=15547">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 11, 0, 0, 1, 100, 4, 0, 3000, 3000, 3500, 11, 16100, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 20, 0, 0, 2, 100, 0, 0, 7500, 7500, 15000, 11, 40505, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=40505">Cleave</a>" (Phase 2)'),
  (@ENTRY, 0, 21, 0, 0, 2, 100, 0, 0, 7500, 7500, 15000, 11, 13446, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=13446">Strike</a>" (Phase 2)'),
  (@ENTRY, 0, 22, 0, 0, 2, 100, 0, 0, 5000, 5000, 10000, 11, 13444, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=13444">Sunder Armor</a>" (Phase 2)'),
  (@ENTRY, 0, 30, 0, 0, 4, 100, 2, 0, 7500, 3000, 10000, 11, 13339, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=13339">Fire Blast</a>" (Normal Dungeon)(Phase 3)'),
  (@ENTRY, 0, 31, 0, 0, 4, 100, 4, 0, 7500, 3000, 10000, 11, 14145, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=14145">Fire Blast</a>" (Heroic Dungeon)(Phase 3)'),
  (@ENTRY, 0, 32, 0, 0, 4, 100, 2, 7500, 15000, 5000, 10000, 11, 9613, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=9613">Shadow Bolt</a>" (Normal Dungeon)(Phase 3)'),
  (@ENTRY, 0, 33, 0, 0, 4, 100, 4, 7500, 15000, 5000, 10000, 11, 12739, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=12739">Shadow Bolt</a>" (Heroic Dungeon)(Phase 3)'),
  (@ENTRY, 0, 34, 0, 0, 4, 100, 2, 15000, 25000, 15000, 25000, 11, 11831, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=11831">Frost Nova</a>" (Normal Dungeon)(Phase 3)'),
  (@ENTRY, 0, 35, 0, 0, 4, 100, 4, 15000, 25000, 15000, 25000, 11, 15063, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Leper - In Combat - Cast "<a href="http://wowhead.com/spell=15063">Frost Nova</a>" (Heroic Dungeon)(Phase 3)'),
  (@ENTRY, 0, 40, 0, 9, 8, 100, 2, 0, 40, 10000, 15000, 11, 11642, 0, 0, 0, 0, 0, 102, 1, 40, 75, 0, 0, 0, 0, 0, 'Coilfang Leper - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=11642">Heal</a>" (Normal Dungeon)(Phase 4)'),
  (@ENTRY, 0, 41, 0, 9, 8, 100, 4, 0, 40, 10000, 15000, 11, 15586, 0, 0, 0, 0, 0, 102, 1, 40, 75, 0, 0, 0, 0, 0, 'Coilfang Leper - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=15586">Heal</a>" (Heroic Dungeon)(Phase 4)');

# SmartAIMgr::LoadSmartAIFromDB: Entry 21506 SourceType 0, Event 9, Missing Repeat flag.
-- NPC 21506
SET @ENTRY = 21506;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, 5000, 10000, 15000, 11, 11443, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Cast "<a href="http://wowhead.com/spell=11443">Cripple</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 10000, 15000, 11, 38741, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Cast "<a href="http://wowhead.com/spell=38741">Rain of Fire</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 0, 5000, 5000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Cast "<a href="http://wowhead.com/spell=40504">Cleave</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 0, 5000, 5000, 10000, 11, 38750, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Cast "<a href="http://wowhead.com/spell=38750">War Stomp</a>" '),
  (@ENTRY, 0, 4, 5, 23, 0, 100, 1, 37833, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, 0, 21503, 30, 0, 0, 0, 0, 0, 'Azaloth - On Missing Aura "<a href="http://wowhead.com/spell=37833">Banish</a>" - Start Attacking (No Repeat)'),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 0, 21503, 0, 30, 0, 0, 0, 0, 'Azaloth - On Missing Aura "<a href="http://wowhead.com/spell=37833">Banish</a>" - Set Data 1 1 '),
  (@ENTRY, 0, 6, 0, 11, 0, 100, 0, 0, 0, 0, 0, 11, 37833, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - On Respawn - Cast "<a href="http://wowhead.com/spell=37833">Banish</a>" '),
  (@ENTRY, 0, 7, 0, 61, 0, 100, 0, 1, 1, 0, 0, 28, 37833, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - On Data Set 1 1 - Remove Aura "<a href="http://wowhead.com/spell=37833">Banish</a>" '),
  (@ENTRY, 0, 8, 7, 38, 0, 100, 0, 1, 1, 0, 0, 41, 60000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - On Data Set 1 1 - Despawn In 60000ms ');

# SmartAIMgr: Entry 21685 SourceType 0 Event 24 Action 11 has invalid target type for event, skipped.
-- NPC 21685
SET @ENTRY = 21685;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 80, 2168500, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Respawn - Run Script <a href="/smartai/script/2168500">2168500</a> '),
  (@ENTRY, 0, 1, 0, 40, 0, 100, 0, 9, 2168501, 0, 0, 80, 2168501, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Waypoint 9 Reached - Run Script <a href="/smartai/script/2168501">2168501</a> '),
  (@ENTRY, 0, 2, 3, 40, 0, 100, 0, 11, 2168501, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Waypoint 11 Reached - Say Line 5 '),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Waypoint 11 Reached - Set NPC Flag Gossip '),
  (@ENTRY, 0, 4, 0, 62, 0, 100, 0, 20095, 0, 0, 0, 80, 2168502, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Gossip 20095 Option 0 Selected - Run Script <a href="/smartai/script/2168502">2168502</a> '),
  (@ENTRY, 0, 5, 0, 40, 0, 100, 0, 2, 21685, 0, 0, 80, 2168503, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Waypoint 2 Reached - Run Script <a href="/smartai/script/2168503">2168503</a> '),
  (@ENTRY, 0, 11, 0, 0, 0, 100, 0, 0, 1500, 8000, 11000, 11, 16006, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - In Combat - Cast "<a href="http://wowhead.com/spell=16006">Chain Lightning</a>" '),
  (@ENTRY, 0, 12, 0, 0, 0, 100, 0, 0, 0, 15000, 20000, 11, 12548, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - In Combat - Cast "<a href="http://wowhead.com/spell=12548">Frost Shock</a>" '),
  (@ENTRY, 0, 13, 0, 2, 0, 100, 0, 0, 40, 5000, 8000, 11, 12491, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - Between 0-40% HP - Cast "<a href="http://wowhead.com/spell=12491">Healing Wave</a>" '),
  (@ENTRY, 0, 14, 0, 38, 0, 100, 0, 4, 4, 4000, 6000, 11, 12491, 0, 0, 0, 0, 0, 19, 0, 21687, 20, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Data Set 4 4 - Cast "<a href="http://wowhead.com/spell=12491">Healing Wave</a>" '),
  (@ENTRY, 0, 15, 0, 38, 0, 100, 0, 6, 6, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Data Set 6 6 - Change Equipment '),
  (@ENTRY, 0, 16, 0, 38, 0, 100, 0, 5, 5, 4000, 6000, 11, 12491, 0, 0, 0, 0, 0, 19, 0, 21686, 20, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Data Set 5 5 - Cast "<a href="http://wowhead.com/spell=12491">Healing Wave</a>" '),
  (@ENTRY, 0, 24, 0, 9, 0, 100, 0, 0, 40, 4000, 6000, 11, 12491, 0, 0, 0, 0, 0, 102, 17, 40, 40, 0, 0, 0, 0, 0, 'Oronok Torn-heart - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=12491">Healing Wave</a>" '),
  (@ENTRY, 0, 26, 0, 38, 0, 100, 0, 7, 7, 0, 0, 80, 2168504, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Data Set 7 7 - Run Script <a href="/smartai/script/2168504">2168504</a> '),
  (@ENTRY, 0, 27, 0, 40, 0, 100, 0, 2, 2168502, 0, 0, 80, 2168505, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Oronok Torn-heart - On Waypoint 2 Reached - Run Script <a href="/smartai/script/2168505">2168505</a> ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 21722 SourceType 0, Event 9, Missing Repeat flag.
-- NPC 21722
SET @ENTRY = 21722;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 0, 38762, 0, 60000, 60000, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Netherwing Drake - On Spellhit "<a href="http://wowhead.com/spell=38762">Force of Neltharaku</a>" - Set Event Phase 1 '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 4, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Netherwing Drake - On Spellhit "<a href="http://wowhead.com/spell=38762">Force of Neltharaku</a>" - Store Targetlist 1 '),
  (@ENTRY, 0, 2, 3, 60, 1, 100, 1, 0, 0, 0, 0, 2, 1840, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Netherwing Drake - On Update - Set Faction 1840 (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 3, 4, 61, 1, 100, 1, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 4, 21718, 0, 5, 0, 0, 0, 0, 'Enslaved Netherwing Drake - On Update - Start Attacking (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 4, 0, 61, 1, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Netherwing Drake - On Update - Say Line 0 (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 5, 6, 38, 0, 100, 0, 0, 1, 0, 0, 11, 38775, 0, 0, 0, 0, 0, 12, 4, 1, 0, 0, 0, 0, 0, 0, 'Enslaved Netherwing Drake - On Data Set 0 1 - Cast "<a href="http://wowhead.com/spell=38775">Force of Neltharaku</a>" '),
  (@ENTRY, 0, 6, 7, 61, 0, 100, 0, 0, 1, 0, 0, 60, 1, 21722, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Netherwing Drake - On Data Set 0 1 - Disable Gravity '),
  (@ENTRY, 0, 7, 0, 61, 0, 100, 0, 0, 1, 0, 0, 152, 12949495, 21722, 1, 0, 1, 0, 1, 0, 0, 0, 0, 254, 69, 8, 0, 'Enslaved Netherwing Drake - On Data Set 0 1 - Load Path 12949495 '),
  (@ENTRY, 0, 8, 0, 0, 0, 100, 0, 2500, 5000, 10000, 15000, 11, 36513, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Netherwing Drake - In Combat - Cast "<a href="http://wowhead.com/spell=36513">Intangible Presence</a>" '),
  (@ENTRY, 0, 9, 0, 60, 1, 100, 1, 12000, 12000, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Netherwing Drake - On Update - Set Visibility Off (No Repeat)(Phase 1)');

# SmartAIMgr: Entry 21814 SourceType 0 Event 0 Action 12 creature summon: There is a summon spell for creature entry 20021 (SpellId: 36326, effect: 0)
-- NPC 21814
SET @ENTRY = 21814;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 54, 0, 100, 1, 0, 0, 0, 0, 11, 36326, 0, 30000, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nether Drake Egg Bunny - On Just Summoned - Cast "<a href="http://wowhead.com/spell=36326">Nether Whelp</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 1, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nether Drake Egg Bunny - On Just Summoned - Despawn Instant (No Repeat)');
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceEntry = 37573 AND ConditionValue2 IN (20021,21817,21820,21821);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
  (13,	1,	37573,	0,	0,	31,	0,	3,	20021,	0,	0,	0,	0,	'',	NULL), -- # Whelp
  (13,	1,	37573,	0,	1,	31,	0,	3,	21821,	0,	0,	0,	0,	'',	NULL), -- # Proto
  (13,	1,	37573,	0,	2,	31,	0,	3,	21817,	0,	0,	0,	0,	'',	NULL), -- # Adullt
  (13,	1,	37573,	0,	3,	31,	0,	3,	21820,	0,	0,	0,	0,	'',	NULL); -- # Mature

# SmartAIMgr::LoadSmartAIFromDB: Entry 21898 SourceType 0, Event 2, Missing Repeat flag.
-- NPC 21898
SET @ENTRY = 21898;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mana Bomb Lightning Trigger - On Data Set 0 1 - Set Event Phase 1 '),
  (@ENTRY, 0, 1, 0, 1, 1, 100, 0, 0, 0, 1500, 3500, 11, 37843, 3, 0, 0, 0, 0, 1, 0, 21889, 50, 0, 0, 0, 0, 0, 'Mana Bomb Lightning Trigger - Out of Combat - Cast "<a href="http://wowhead.com/spell=37843">Mana Bomb: Lightning</a>" (Phase 1)'),
  (@ENTRY, 0, 2, 0, 1, 1, 100, 1, 10000, 10000, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mana Bomb Lightning Trigger - Out of Combat - Set Event Phase 0 (No Repeat)(Phase 1)');

# SmartAIMgr: Warning: Entry 22199 SourceType 0 Event 2 Action 50 gameobject summon: There is a summon spell for gameobject entry 185574 (SpellId: 39898, effect: 0)
-- NPC 22199
SET @ENTRY = 22199;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 2, 0, 100, 1, 0, 30, 0, 0, 11, 33958, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Slaag - Between 0-30% HP - Cast "<a href="http://wowhead.com/spell=33958">Frenzy</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Slaag - Between 0-30% HP - Say Line 0 '),
  (@ENTRY, 0, 2, 0, 6, 0, 100, 1, 0, 0, 0, 0, 85, 39898, 2, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Slaag - On Death - Invoker Cast "<a href="http://wowhead.com/spell=39898">Slaag: Summon Slaag"s Standard Chest</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 'Slaag - On Aggro - Store Targetlist 1 '),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 0, 15000, 20000, 25000, 35000, 11, 41981, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Slaag - In Combat - Cast "<a href="http://wowhead.com/spell=41981">Dust Field</a>" ');
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 22 AND SourceGroup = 4 AND SourceEntry = @ENTRY AND ConditionTypeOrReference = 9 AND ConditionValue1 = 10997;
REPLACE INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment)
  VALUES (22, 3, @ENTRY, 0, 0, 9, 0, 10997, 0, 0, 0, 0, 0, '', NULL);

# SmartAIMgr: Entry 22444 SourceType 0 Event 3 Action 12 creature summon: There is a summon spell for creature entry 22454 (SpellId: 39206, effect: 0)
-- NPC 22444
SET @ENTRY = 22444;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 2, 54, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anchorite Relic Bunny - On Just Summoned - Disable Combat Movement '),
  (@ENTRY, 0, 1, 0, 60, 0, 100, 0, 0, 1, 1000, 1000, 11, 39184, 1, 0, 0, 0, 0, 1, 0, 16878, 0, 0, 0, 0, 0, 0, 'Anchorite Relic Bunny - On Update - Cast "<a href="http://wowhead.com/spell=39184">Anchorite Contrition</a>" '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 2, 1662, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anchorite Relic Bunny - On Just Summoned - Set Faction 1662 '),
  (@ENTRY, 0, 3, 0, 8, 0, 100, 0, 39190, 0, 0, 0, 11, 39206, 0, 30000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anchorite Relic Bunny - On Spellhit "<a href="http://wowhead.com/spell=39190">Send Vengeance</a>" - Cast "<a href="http://wowhead.com/spell=39206">Summon Fel Spirit</a>" '),
  (@ENTRY, 0, 4, 0, 37, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Anchorite Relic Bunny - On AI Initialize - Set React State Passive ');
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceEntry = 39190 AND ConditionValue2 = 22444;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
  (13,	1,	39190,	0,	0,	31,	0,	3,	22444,	0,	0,	0,	0,	'',	NULL);
-- NPC 22454
SET @ENTRY = 22454;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 21, 0, 30, 0, 0, 0, 0, 0, 0, 'Fel Spirit - On Just Summoned - Say Line 0 '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 0, 30, 0, 0, 0, 0, 0, 0, 'Fel Spirit - On Just Summoned - Start Attacking '),
  (@ENTRY, 0, 2, 0, 1, 0, 100, 0, 0, 0, 0, 0, 41, 30000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fel Spirit - Out of Combat - Despawn In 30000ms ');

# SmartAIMgr: EntryOrGuid 23162 using event(3) has invalid action type (0), skipped.
-- NPC 23162
SET @ENTRY = 23162;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 11, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vakkiz the Windrager - On Respawn - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 1, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vakkiz the Windrager - On Respawn - Set Event Phase 1 (No Repeat)'),
  (@ENTRY, 0, 3, 4, 2, 0, 100, 1, 0, 40, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vakkiz the Windrager - Between 0-40% HP - Set Event Phase 2 (No Repeat)'),
  (@ENTRY, 0, 4, 7, 61, 0, 100, 1, 0, 40, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vakkiz the Windrager - Between 0-40% HP - Say Line 1 (No Repeat)'),
  (@ENTRY, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 3, 0, 8053, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vakkiz the Windrager - Between 0-40% HP - Morph To "0" '),
  (@ENTRY, 0, 10, 0, 0, 1, 100, 0, 6500, 9500, 8500, 11500, 11, 40420, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Vakkiz the Windrager - In Combat - Cast "<a href="http://wowhead.com/spell=40420">Lightning Breath</a>" (Phase 1)'),
  (@ENTRY, 0, 20, 0, 0, 2, 100, 0, 3000, 7000, 5000, 9000, 11, 40419, 33, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Vakkiz the Windrager - In Combat - Cast "<a href="http://wowhead.com/spell=40419">Bone Spray</a>" (Phase 2)'),
  (@ENTRY, 0, 21, 0, 25, 0, 100, 0, 0, 0, 0, 0, 3, 23162, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vakkiz the Windrager - On Reset - Morph To "23162" ');

# SmartAIMgr: Entry 23219 SourceType 0 Event 6 Action 12 creature summon: There is a summon spell for creature entry 23438 (SpellId: 41428, effect: 0)
-- NPC 23219
SET @ENTRY = 23219;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 1, 0, 0, 0, 0, 11, 32942, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blackwind Warp Chaser - On Respawn - Cast "<a href="http://wowhead.com/spell=32942">Phasing Invisibility</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 513, 0, 0, 0, 0, 28, 32942, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blackwind Warp Chaser - On Aggro - Remove Aura "<a href="http://wowhead.com/spell=32942">Phasing Invisibility</a>" (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 3000, 6000, 4000, 7000, 11, 32739, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Blackwind Warp Chaser - In Combat - Cast "<a href="http://wowhead.com/spell=32739">Venomous Bite</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 12000, 15000, 20000, 40000, 11, 32920, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Blackwind Warp Chaser - In Combat - Cast "<a href="http://wowhead.com/spell=32920">Warp</a>" '),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 0, 2000, 5000, 7000, 15000, 11, 37417, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Blackwind Warp Chaser - In Combat - Cast "<a href="http://wowhead.com/spell=37417">Warp Charge</a>" '),
  (@ENTRY, 0, 5, 0, 7, 0, 100, 1, 0, 0, 0, 0, 11, 32942, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blackwind Warp Chaser - On Evade - Cast "<a href="http://wowhead.com/spell=32942">Phasing Invisibility</a>" (No Repeat)'),
  (@ENTRY, 0, 6, 0, 6, 0, 100, 1, 0, 0, 0, 0, 85, 41428, 0, 15000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blackwind Warp Chaser - On Death - Invoker Cast "<a href="http://wowhead.com/spell=41428">Summon Lucille Credit</a>" (No Repeat)');
-- NPC 23439
SET @ENTRY = 23439;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 29, 2, 120, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Nether Ray - On Just Summoned - Follow Target '),
  (@ENTRY, 0, 1, 0, 38, 0, 100, 0, 0, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 19, 8, 23219, 40, 1, 0, 0, 0, 0, 'Hungry Nether Ray - On Data Set 0 1 - Move To Pos '),
  (@ENTRY, 0, 2, 0, 34, 0, 100, 0, 0, 1, 0, 0, 80, 2343901, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Nether Ray - On Reached Point 1 - Run Script <a href="/smartai/script/2343901">2343901</a> ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 103, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Nether Ray - In Combat - Set Root On '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 5, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Nether Ray - In Combat - Play Emote 7 '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 103, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Nether Ray - In Combat - Set Root Off '),
  (@ENTRY*100+1, 9, 103, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Nether Ray - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 104, 0, 0, 0, 100, 0, 0, 0, 0, 0, 29, 2, 120, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Nether Ray - In Combat - Follow Target ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s feeds on the freshly-killed warp chaser.", 16, 0, 100, 0, 0, "Hungry Nether Ray - ");
-- NPC 23438
SET @ENTRY = 23438;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 33, 23438, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 'Nether Ray Feed Credit - On Just Summoned - Quest Credit "<a href="http://wowhead.com/quest=23438">Nether Ray Feed Credit</a>" '),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 19, 4, 23439, 10, 0, 0, 0, 0, 0, 'Nether Ray Feed Credit - On Just Summoned - Set Data 0 1 '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nether Ray Feed Credit - On Just Summoned - Despawn In 1000ms ');

# SmartAIMgr: EntryOrGuid 23580 using event(1) has invalid action type (0), skipped.
-- NPC 23580
SET @ENTRY = 23580;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 2, 2, 0, 100, 3, 0, 19, 0, 0, 11, 43274, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amani&#039;shi Warbringer - Between 0-19% HP - Cast "<a href="http://wowhead.com/spell=43274">Dismount Bear</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 3, 0, 19, 0, 0, 43, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amani&#039;shi Warbringer - Between 0-19% HP - Dismount (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 2, 0, 0, 12000, 12000, 11, 43273, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Amani&#039;shi Warbringer - In Combat - Cast "<a href="http://wowhead.com/spell=43273">Cleave</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 2, 5000, 5000, 20000, 20000, 11, 42496, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Amani&#039;shi Warbringer - In Combat - Cast "<a href="http://wowhead.com/spell=42496">Furious Roar</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 5, 0, 2, 0, 100, 3, 0, 30, 0, 0, 11, 40743, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amani&#039;shi Warbringer - Between 0-30% HP - Cast "<a href="http://wowhead.com/spell=40743">Enrage</a>" (No Repeat and  Normal Dungeon)');

# SmartAIMgr::LoadSmartAIFromDB: Creature entry (25824) is not using SmartAI, skipped loading.
DELETE FROM smart_scripts WHERE entryorguid = 25824 AND source_type = 0;