/*
  Startup errors fixes
 */

# SmartAIMgr::LoadSmartAIFromDB: Creature entry (16488) is not using SmartAI, skipped loading.
DELETE FROM smart_scripts WHERE entryorguid = 16488 AND source_type = 0;

# SmartAIMgr::LoadSmartAIFromDB: Entry 16525 SourceType 0, Event 1, Missing Repeat flag.
-- NPC 16525
SET @ENTRY = 16525;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 25, 0, 100, 0, 0, 5000, 15000, 20000, 11, 29920, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - On Reset - Cast "<a href="http://wowhead.com/spell=29920">Phasing Invisibility</a>" '),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 31, 1, 3, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - On Aggro - Set Phase Random Between 1-3 (No Repeat)'),
  (@ENTRY, 0, 2, 0, 60, 1, 100, 1, 0, 1, 0, 0, 58, 6, 29925, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - On Update - Install Caster SUN Template (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 4, 0, 60, 2, 100, 1, 0, 1, 0, 0, 58, 6, 29926, 2000, 2500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - On Update - Install Caster SUN Template (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 6, 0, 60, 4, 100, 1, 0, 1, 0, 0, 58, 6, 29927, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - On Update - Install Caster SUN Template (No Repeat)(Phase 3)');

#SmartAIMgr: Entry 17817 SourceType 0 Event 0 Action 11 uses non-existent Spell entry 0, skipped.
-- NPC 17817
SET @ENTRY = 17817;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 23, 0, 100, 0, 35760, 0, 15000, 20000, 11, 35760, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Greater Bogstrok - On Missing Aura "<a href="http://wowhead.com/spell=35760">Decayed Strength</a>" - Cast "<a href="http://wowhead.com/spell=35760">Decayed Strength</a>" ');

# SmartAIMgr: Entry 17835 SourceType 0 Event 3 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 17835 SourceType 0 Event 3 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 17835;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Our time has come!", 12, 0, 100, 0, 0, "Infinite Assassin - ");

# SmartAIMgr: Entry 17839 SourceType 0 Event 1 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 17839 SourceType 0 Event 1 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 17839;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "History is about to be rewritten!", 14, 0, 100, 0, 0, "Rift Lord - "),
  (@ENTRY, 0, 1, "Let the siege begin!", 14, 0, 100, 0, 0, "Rift Lord - "),
  (@ENTRY, 0, 2, "The sands of time shall be scattered to the winds!", 14, 0, 100, 0, 0, "Rift Lord - "),
  (@ENTRY, 0, 3, "You will accomplish nothing!", 14, 0, 100, 0, 0, "Rift Lord - "),
  (@ENTRY, 0, 4, "You will never defeat us all!", 14, 0, 100, 0, 0, "Rift Lord - ");

# SmartAIMgr: Entry 17892 SourceType 0 Event 2 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 17892 SourceType 0 Event 2 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 17892;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Our time has come!", 12, 0, 100, 0, 0, "Infinite Assassin - ");

# SmartAIMgr: Entry 17905 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 17905 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.-- NPC 17905
SET @ENTRY = 17905;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 6, 0, 20, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Banshee - On Death - Say Line 0 (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 10000, 20000, 30000, 60000, 11, 31662, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Banshee - In Combat - Cast "<a href="http://wowhead.com/spell=31662">Anti-Magic Shell</a>" '),
  (@ENTRY, 0, 2, 0, 23, 0, 100, 0, 31651, 0, 10000, 15000, 11, 31651, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Banshee - On Missing Aura "<a href="http://wowhead.com/spell=31651">Banshee Curse</a>" - Cast "<a href="http://wowhead.com/spell=31651">Banshee Curse</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 0, 5000, 3000, 5000, 11, 38183, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Banshee - In Combat - Cast "<a href="http://wowhead.com/spell=38183">Banshee Wail</a>" ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "I am... released?", 12, 0, 100, 0, 0, "Banshee - "),
  (@ENTRY, 0, 1, "Is it really... over?", 12, 0, 100, 0, 0, "Banshee - "),
  (@ENTRY, 0, 2, "Let this torment end!!", 12, 0, 100, 0, 0, "Banshee - ");

# SmartAIMgr::LoadSmartAIFromDB: Entry 18077 SourceType 0, Event 1, Missing Repeat flag.
-- NPC 18077
SET @ENTRY = 18077;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 12550, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Umbrafen Oracle - On Reset - Cast "<a href="http://wowhead.com/spell=12550">Lightning Shield</a>" '),
  (@ENTRY, 0, 1, 0, 23, 0, 100, 0, 12550, 0, 10000, 15000, 11, 12550, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Umbrafen Oracle - On Missing Aura "<a href="http://wowhead.com/spell=12550">Lightning Shield</a>" - Cast "<a href="http://wowhead.com/spell=12550">Lightning Shield</a>" '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 0, 0, 50, 20000, 30000, 11, 11986, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Umbrafen Oracle - Between 0-50% HP - Cast "<a href="http://wowhead.com/spell=11986">Healing Wave</a>" ');

# SmartAIMgr: Entry 18080 SourceType 0 Event 3 Action 11 uses non-existent Spell entry 0, skipped.
SET @ENTRY = 18080;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 5000, 15000, 5000, 15000, 11, 12058, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Kataru - In Combat - Cast "<a href="http://wowhead.com/spell=12058">Chain Lightning</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 5000, 10000, 60000, 75000, 11, 15869, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kataru - In Combat - Cast "<a href="http://wowhead.com/spell=15869">Superior Healing Ward</a>" '),
  (@ENTRY, 0, 3, 0, 23, 0, 100, 0, 32734, 0, 10000, 15000, 11, 32734, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kataru - On Missing Aura "<a href="http://wowhead.com/spell=32734">Earth Shield</a>" - Cast "<a href="http://wowhead.com/spell=32734">Earth Shield</a>" ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 18122 SourceType 0, Event 0, Missing Repeat flag.
# SmartAIMgr: Entry 18122 SourceType 0 Event 1 Action 11 uses non-existent Spell entry 0, skipped.
UPDATE spell_template SET attributesEx = attributesEx & ~0x4 WHERE entry = 34788;
-- NPC 18122
SET @ENTRY = 18122;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 34788, 32, 0, 0, 0, 0, 19, 0, 18122, 40, 0, 0, 0, 0, 0, 'Dreghood Drudge - On Aggro - Cast "<a href="http://wowhead.com/spell=34788">Shared Bonds</a>" ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 18179 SourceType 0, Event 3, Missing Repeat flag.
-- NPC 18179
SET @ENTRY = 18179;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 11, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Corrupted Nova Totem - On Respawn - Disable Combat Movement '),
  (@ENTRY, 0, 2, 0, 60, 0, 100, 1, 5000, 5000, 0, 0, 11, 33132, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Corrupted Nova Totem - On Update - Cast "<a href="http://wowhead.com/spell=33132">Fire Nova</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 60, 0, 100, 1, 6000, 6000, 0, 0, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Corrupted Nova Totem - On Update - Die (No Repeat)');

# SmartAIMgr: Entry 18240 SourceType 0 Event 0 Action 80 uses min/max params wrong (66000/0), skipped.
-- NPC 18240
SET @ENTRY = 18240;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 8, 0, 100, 0, 32146, 0, 66000, 66000, 80, 1824000, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunspring Villager - On Spellhit "<a href="http://wowhead.com/spell=32146">Liquid Fire</a>" - Run Script <a href="/smartai/script/1824000">1824000</a> ');

# SmartAIMgr: Entry 18282 SourceType 0 Event 1 Action 11 uses non-existent Spell entry 0, skipped.
-- NPC 18282
SET @ENTRY = 18282;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 10000, 15000, 15000, 20000, 11, 8078, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Lord Klaq - In Combat - Cast "<a href="http://wowhead.com/spell=8078">Thunderclap</a>" '),
  (@ENTRY, 0, 1, 0, 23, 0, 100, 0, 35361, 0, 20000, 30000, 11, 35361, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lord Klaq - On Missing Aura "<a href="http://wowhead.com/spell=35361">Thorns</a>" - Cast "<a href="http://wowhead.com/spell=35361">Thorns</a>" ');

# SmartAIMgr: Entry 18311 SourceType 0 Event 6 Action 1 using non-existent Text id 1, skipped.
# SmartAIMgr: Entry 18311 SourceType 0 Event 6 Action 1 uses non-existent text 1, skipped.
SET @ENTRY = 18311;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s becomes enraged!", 16, 0, 100, 0, 0, "Ethereal Crypt Raider"),
  (@ENTRY, 1, 0, "If you hear the whisper, you're dying...", 12, 0, 100, 0, 0, "Ethereal Crypt Raider - "),
  (@ENTRY, 1, 1, "Welcome to the Void...", 12, 0, 100, 0, 0, "Ethereal Crypt Raider - "),
  (@ENTRY, 1, 2, "What have the netherwinds brought us?", 12, 0, 100, 0, 0, "Ethereal Crypt Raider - "),
  (@ENTRY, 1, 3, "You're far from home, stranger.", 12, 0, 100, 0, 0, "Ethereal Crypt Raider - ");

# SmartAIMgr: Entry 18319 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 18319 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 18319;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Arak-ha!", 12, 0, 100, 0, 0, "Time-Lost Scryer - "),
  (@ENTRY, 0, 1, "Darkfire -- avenge us!", 12, 0, 100, 0, 0, "Time-Lost Scryer - "),
  (@ENTRY, 0, 2, "In Terokk's name!", 12, 0, 100, 0, 0, "Time-Lost Scryer - "),
  (@ENTRY, 0, 3, "Protect the Veil!", 12, 0, 100, 0, 0, "Time-Lost Scryer - "),
  (@ENTRY, 0, 4, "Ssssekk-sara Rith-nealaak!", 12, 0, 100, 0, 0, "Time-Lost Scryer - ");

# SmartAIMgr: Entry 18321 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 18321 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 18321;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Arak-ha!", 12, 0, 100, 0, 0, "Sethekk Talon Lord - "),
  (@ENTRY, 0, 1, "Darkfire -- avenge us!", 12, 0, 100, 0, 0, "Sethekk Talon Lord - "),
  (@ENTRY, 0, 2, "In Terokk's name!", 12, 0, 100, 0, 0, "Sethekk Talon Lord - "),
  (@ENTRY, 0, 3, "Protect the Veil!", 12, 0, 100, 0, 0, "Sethekk Talon Lord - "),
  (@ENTRY, 0, 4, "Ssssekk-sara Rith-nealaak!", 12, 0, 100, 0, 0, "Sethekk Talon Lord - ");

# SmartAIMgr: Entry 18325 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 18325 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
# SmartAIMgr: Entry 18325 SourceType 0 Event 2 Action 12 creature summon: There is a summon spell for creature entry 18703 (SpellId: 32692, effect: 0)
-- NPC 18325
SET @ENTRY = 18325;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 20, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sethekk Prophet - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 10000, 15000, 10000, 20000, 11, 27641, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Sethekk Prophet - In Combat - Cast "<a href="http://wowhead.com/spell=27641">Fear</a>" '),
  (@ENTRY, 0, 2, 0, 6, 0, 100, 1, 0, 0, 0, 0, 11, 32692, 2, 11000, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sethekk Prophet - On Death - Cast "<a href="http://wowhead.com/spell=32692">Summon Arakkoa Spirit</a>" (No Repeat)');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Arak-ha!", 12, 0, 100, 0, 0, "Sethekk Prophet - "),
  (@ENTRY, 0, 1, "Darkfire -- avenge us!", 12, 0, 100, 0, 0, "Sethekk Prophet - "),
  (@ENTRY, 0, 2, "In Terokk's name!", 12, 0, 100, 0, 0, "Sethekk Prophet - "),
  (@ENTRY, 0, 3, "Protect the Veil!", 12, 0, 100, 0, 0, "Sethekk Prophet - "),
  (@ENTRY, 0, 4, "Ssssekk-sara Rith-nealaak!", 12, 0, 100, 0, 0, "Sethekk Prophet - ");

# SmartAIMgr: Entry 18326 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 18326 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 18326;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Arak-ha!", 12, 0, 100, 0, 0, "Sethekk Shaman - "),
  (@ENTRY, 0, 1, "Darkfire -- avenge us!", 12, 0, 100, 0, 0, "Sethekk Shaman - "),
  (@ENTRY, 0, 2, "In Terokk's name!", 12, 0, 100, 0, 0, "Sethekk Shaman - "),
  (@ENTRY, 0, 3, "Protect the Veil!", 12, 0, 100, 0, 0, "Sethekk Shaman - "),
  (@ENTRY, 0, 4, "Ssssekk-sara Rith-nealaak!", 12, 0, 100, 0, 0, "Sethekk Shaman - ");

# SmartAIMgr: Entry 18327 SourceType 0 Event 2 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 18327 SourceType 0 Event 2 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 18327;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Arak-ha!", 12, 0, 100, 0, 0, "Time-Lost Controller - "),
  (@ENTRY, 0, 1, "Darkfire -- avenge us!", 12, 0, 100, 0, 0, "Time-Lost Controller - "),
  (@ENTRY, 0, 2, "In Terokk's name!", 12, 0, 100, 0, 0, "Time-Lost Controller - "),
  (@ENTRY, 0, 3, "Protect the Veil!", 12, 0, 100, 0, 0, "Time-Lost Controller - "),
  (@ENTRY, 0, 4, "Ssssekk-sara Rith-nealaak!", 12, 0, 100, 0, 0, "Time-Lost Controller - ");

# SmartAIMgr: Entry 18328 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 18328 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 18328;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Arak-ha!", 12, 0, 100, 0, 0, "Sethekk Oracle - "),
  (@ENTRY, 0, 1, "Darkfire -- avenge us!", 12, 0, 100, 0, 0, "Sethekk Oracle - "),
  (@ENTRY, 0, 2, "In Terokk's name!", 12, 0, 100, 0, 0, "Sethekk Oracle - "),
  (@ENTRY, 0, 3, "Protect the Veil!", 12, 0, 100, 0, 0, "Sethekk Oracle - "),
  (@ENTRY, 0, 4, "Ssssekk-sara Rith-nealaak!", 12, 0, 100, 0, 0, "Sethekk Oracle - ");

# SmartAIMgr::LoadSmartAIFromDB: Entry 18340 SourceType 0, Event 2, Missing Repeat flag.
UPDATE smart_scripts SET event_flags = event_flags | 0x1 WHERE entryorguid = 18340 AND source_type = 0 AND id = 2;

# SmartAIMgr: Entry 18440 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 18440 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 18440;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "GET IN DA STEW!", 12, 0, 100, 0, 0, "Warmaul Chef Bufferlo - "),
  (@ENTRY, 0, 1, "IT DUZ WUT IT'S TOLD!", 12, 0, 100, 0, 0, "Warmaul Chef Bufferlo - "),
  (@ENTRY, 0, 2, "YOU GUD IN DA BELLY!", 12, 0, 100, 0, 0, "Warmaul Chef Bufferlo - ");

# SmartAIMgr: Entry 18473 SourceType 0 Event 3 Action 1 using non-existent Text id 3, skipped.
# SmartAIMgr: Entry 18473 SourceType 0 Event 3 Action 1 uses non-existent text 3, skipped.
SET @ENTRY = 18473;
DELETE FROM creature_text WHERE CreatureID = @ENTRY AND groupid = 3;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 3, 0, "Ikiss will not -- rak, rak -- die...", 14, 0, 100, 0, 0, "Talon King Ikiss - Death");

# SmartAIMgr: Entry 18495 SourceType 0 Event 0 Action 11 uses non-existent Spell entry 0, skipped.
# SmartAIMgr: Entry 18495 SourceType 0 Event 2 Action 31 attempts to set invalid phase, skipped.
# SmartAIMgr: Entry 18495 SourceType 0 Event 8 Action 11 uses non-existent Spell entry 0, skipped.
-- NPC 18495
SET @ENTRY = 18495;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 37, 0, 100, 1, 0, 0, 0, 0, 31, 1, 5, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - On AI Initialize - Set Phase Random Between 1-5 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - On AI Initialize - Store Current Phase '),
  (@ENTRY, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 164, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - On Reset - Restore Phase '),
  (@ENTRY, 0, 6, 0, 23, 0, 100, 2, 32861, 0, 10000, 20000, 11, 32861, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - On Missing Aura "<a href="http://wowhead.com/spell=32861">Shadowguard</a>" - Cast "<a href="http://wowhead.com/spell=32861">Shadowguard</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 7, 0, 23, 0, 100, 4, 38379, 0, 10000, 20000, 11, 38379, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - On Missing Aura "<a href="http://wowhead.com/spell=38379">Shadowguard</a>" - Cast "<a href="http://wowhead.com/spell=38379">Shadowguard</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 8, 0, 0, 0, 100, 2, 2500, 7500, 15000, 25000, 11, 17439, 32860, 2500, 2750, 40, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - In Combat - Cast "<a href="http://wowhead.com/spell=17439">Shadow Shock</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 9, 0, 0, 0, 100, 4, 2500, 7500, 15000, 25000, 11, 17289, 32860, 2500, 2750, 40, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - In Combat - Cast "<a href="http://wowhead.com/spell=17289">Shadow Shock</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 10, 0, 0, 1, 100, 1, 4000, 5000, 0, 0, 11, 32857, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - In Combat - Cast "<a href="http://wowhead.com/spell=32857">Summon Phantasmal Possessor</a>" (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 20, 0, 0, 2, 100, 1, 4000, 5000, 0, 0, 11, 32855, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - In Combat - Cast "<a href="http://wowhead.com/spell=32855">Summon Unliving Cleric</a>" (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 30, 0, 0, 4, 100, 1, 4000, 5000, 0, 0, 11, 32853, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - In Combat - Cast "<a href="http://wowhead.com/spell=32853">Summon Unliving Soldier</a>" (No Repeat)(Phase 3)'),
  (@ENTRY, 0, 40, 0, 0, 8, 100, 1, 4000, 5000, 0, 0, 11, 32854, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - In Combat - Cast "<a href="http://wowhead.com/spell=32854">Summon Unliving Sorcerer</a>" (No Repeat)(Phase 4)'),
  (@ENTRY, 0, 50, 0, 0, 16, 100, 1, 4000, 5000, 0, 0, 11, 32856, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Vindicator - In Combat - Cast "<a href="http://wowhead.com/spell=32856">Summon Unliving Stalker</a>" (No Repeat)(Phase 5)');

# SmartAIMgr: Entry 18497 SourceType 0 Event 0 Action 11 uses non-existent Spell entry 0, skipped.
# SmartAIMgr: Entry 18497 SourceType 0 Event 2 Action 31 attempts to set invalid phase, skipped.
# SmartAIMgr: Entry 18537 SourceType 0 Event 9 Action 11 has invalid target type for event, skipped.
-- NPC 18497
SET @ENTRY = 18497;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 37, 0, 100, 1, 0, 0, 0, 0, 31, 1, 5, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - On AI Initialize - Set Phase Random Between 1-5 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - On AI Initialize - Store Current Phase '),
  (@ENTRY, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 164, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - On Reset - Restore Phase '),
  (@ENTRY, 0, 6, 0, 23, 0, 100, 6, 38168, 0, 0, 15000, 11, 38168, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - On Missing Aura "<a href="http://wowhead.com/spell=38168">Spiritual Sight</a>" - Cast "<a href="http://wowhead.com/spell=38168">Spiritual Sight</a>" (Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 7, 0, 9, 0, 100, 6, 0, 5, 15000, 25000, 11, 32846, 0, 0, 0, 0, 0, 101, 0, 5, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - Within 0-5 Range - Cast "<a href="http://wowhead.com/spell=32846">Counter Kick</a>" (Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 8, 0, 0, 0, 100, 6, 0, 10000, 5000, 15000, 11, 37321, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - In Combat - Cast "<a href="http://wowhead.com/spell=37321">Overpower</a>" (Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 9, 0, 0, 0, 100, 6, 10000, 20000, 15000, 25000, 11, 32849, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - In Combat - Cast "<a href="http://wowhead.com/spell=32849">Cyclone Strike</a>" (Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 10, 0, 0, 1, 100, 1, 4000, 5000, 0, 0, 11, 32857, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - In Combat - Cast "<a href="http://wowhead.com/spell=32857">Summon Phantasmal Possessor</a>" (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 20, 0, 0, 2, 100, 1, 4000, 5000, 0, 0, 11, 32855, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - In Combat - Cast "<a href="http://wowhead.com/spell=32855">Summon Unliving Cleric</a>" (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 30, 0, 0, 4, 100, 1, 4000, 5000, 0, 0, 11, 32853, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - In Combat - Cast "<a href="http://wowhead.com/spell=32853">Summon Unliving Soldier</a>" (No Repeat)(Phase 3)'),
  (@ENTRY, 0, 40, 0, 0, 8, 100, 1, 4000, 5000, 0, 0, 11, 32854, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - In Combat - Cast "<a href="http://wowhead.com/spell=32854">Summon Unliving Sorcerer</a>" (No Repeat)(Phase 4)'),
  (@ENTRY, 0, 50, 0, 0, 16, 100, 1, 4000, 5000, 0, 0, 11, 32856, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Monk - In Combat - Cast "<a href="http://wowhead.com/spell=32856">Summon Unliving Stalker</a>" (No Repeat)(Phase 5)');

# SmartAIMgr::LoadSmartAIFromDB: Entry 18559 SourceType 0, Event 0, Missing Repeat flag.
# SmartAIMgr::LoadSmartAIFromDB: Entry 18559 SourceType 0, Event 4, Missing Repeat flag.
# SmartAIMgr: Entry 18559 SourceType 0 Event 7 Action 11 uses non-existent Spell entry 0, skipped.
-- NPC 18559
SET @ENTRY = 18559;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 2, 0, 0, 0, 0, 58, 2, 15547, 3000, 3500, 30, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - On AI Initialize - Install Turret Template (Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 2, 5000, 10000, 10000, 15000, 11, 31975, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - In Combat - Cast "<a href="http://wowhead.com/spell=31975">Serpent Sting</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 2, 7, 9, 0, 100, 0, 0, 5, 0, 500, 23, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - Within 0-5 Range - Increase Phase By 1 '),
  (@ENTRY, 0, 3, 7, 0, 0, 100, 4, 5000, 10000, 10000, 15000, 11, 35511, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - In Combat - Cast "<a href="http://wowhead.com/spell=35511">Serpent Sting</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 4, 0, 37, 0, 100, 4, 0, 0, 0, 0, 58, 2, 16100, 3000, 3500, 30, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - On AI Initialize - Install Turret Template (Heroic Dungeon)'),
  (@ENTRY, 0, 5, 0, 18, 0, 100, 4, 0, 100, 15000, 25000, 11, 37551, 32, 0, 0, 0, 0, 17, 0, 5, 35, 0, 0, 0, 0, 0, 'Phasing Stalker - Target Between 0-100% MP - Cast "<a href="http://wowhead.com/spell=37551">Viper Sting</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 7, 0, 23, 1, 100, 0, 32829, 0, 5000, 15000, 11, 32829, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - On Missing Aura "<a href="http://wowhead.com/spell=32829">Spirit Vengeance</a>" - Cast "<a href="http://wowhead.com/spell=32829">Spirit Vengeance</a>" (Phase 1)'),
  (@ENTRY, 0, 8, 0, 9, 1, 100, 1, 5, 40, 0, 500, 23, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - Within 5-40 Range - Decrease Phase By 0 (No Repeat)(Phase 1)');

# SmartAIMgr::LoadSmartAIFromDB: Entry 18635 SourceType 0, Event 1, Missing Repeat flag.
UPDATE smart_scripts SET event_param3 = 15000, event_param4 = 20000 WHERE entryorguid = 18365 AND source_type = 0 AND id = 1;

# SmartAIMgr::LoadSmartAIFromDB: Entry 18638 SourceType 0, Event 0, Missing Repeat flag.
# SmartAIMgr::LoadSmartAIFromDB: Entry 18638 SourceType 0, Event 1, Missing Repeat flag.
-- NPC 18638
SET @ENTRY = 18638;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 2, 0, 0, 0, 0, 58, 1, 12471, 3000, 3250, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Zealot - On AI Initialize - Install Caster Template (Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 37, 0, 100, 4, 0, 0, 0, 0, 58, 1, 15472, 3000, 3250, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Zealot - On AI Initialize - Install Caster Template (Heroic Dungeon)'),
  (@ENTRY, 0, 2, 3, 2, 0, 100, 1, 0, 40, 0, 0, 11, 33499, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Zealot - Between 0-40% HP - Cast "<a href="http://wowhead.com/spell=33499">Shape of the Beast</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 23, 0, 100, 0, 33499, 1, 4500, 15000, 75, 33958, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Zealot - On Has Aura "<a href="http://wowhead.com/spell=33499">Shape of the Beast</a>" - Add Aura "<a href="http://wowhead.com/spell=33958">Frenzy</a>" '),
  (@ENTRY, 0, 4, 0, 25, 0, 100, 0, 0, 0, 0, 0, 28, 33499, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Zealot - On Reset - Remove Aura "<a href="http://wowhead.com/spell=33499">Shape of the Beast</a>" ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 18640 SourceType 0, Event 1, Missing Repeat flag.
# SmartAIMgr::LoadSmartAIFromDB: Entry 18640 SourceType 0, Event 2, Missing Repeat flag.
-- NPC 18640
SET @ENTRY = 18640;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 23, 0, 100, 0, 13787, 0, 10000, 15000, 11, 13787, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Warlock - On Missing Aura "<a href="http://wowhead.com/spell=13787">Demon Armor</a>" - Cast "<a href="http://wowhead.com/spell=13787">Demon Armor</a>" '),
  (@ENTRY, 0, 1, 0, 37, 0, 100, 2, 0, 0, 0, 0, 58, 1, 12471, 3000, 3250, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Warlock - On AI Initialize - Install Caster Template (Normal Dungeon)'),
  (@ENTRY, 0, 2, 0, 37, 0, 100, 4, 0, 0, 0, 0, 58, 1, 15232, 3000, 3250, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Warlock - On AI Initialize - Install Caster Template (Heroic Dungeon)'),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 4, 7500, 15000, 10000, 20000, 11, 38252, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Warlock - In Combat - Cast "<a href="http://wowhead.com/spell=38252">Seed of Corruption</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 2, 7500, 15000, 10000, 20000, 11, 32863, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Warlock - In Combat - Cast "<a href="http://wowhead.com/spell=32863">Seed of Corruption</a>" (Normal Dungeon)');

# SmartAIMgr::LoadSmartAIFromDB: Entry 18641 SourceType 0, Event 0, Missing Repeat flag.
# SmartAIMgr::LoadSmartAIFromDB: Entry 18641 SourceType 0, Event 1, Missing Repeat flag.
-- NPC 18641
SET @ENTRY = 18641;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 2, 0, 0, 0, 0, 58, 1, 20801, 2000, 2250, 30, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Familiar - On AI Initialize - Install Caster Template (Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 37, 0, 100, 4, 0, 0, 0, 0, 58, 1, 38239, 2000, 2250, 30, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Familiar - On AI Initialize - Install Caster Template (Heroic Dungeon)');

# SmartAIMgr: Entry 18678 SourceType 0 Event 0 Action 11 uses non-existent Spell entry 34038, skipped.
# SmartAIMgr: Entry 18678 SourceType 0 Event 2 Action 28 uses non-existent Spell entry 34038, skipped.
# SmartAIMgr: Entry 18678 SourceType 0 Event 9 Action 11 uses non-existent Spell entry 34038, skipped.
# SmartAIMgr: Entry 18678 SourceType 0 Event 11 Action 28 uses non-existent Spell entry 34038, skipped.
DELETE FROM spell_template WHERE entry = 34038;
INSERT INTO spell_template (entry, category, dispel, mechanic, attributes, attributesEx, attributesEx2, attributesEx3, attributesEx4, attributesEx5, attributesEx6, stances, stancesNot, targets, targetCreatureType, requiresSpellFocus, facingCasterFlags, casterAuraState, targetAuraState, casterAuraStateNot, targetAuraStateNot, castingTimeIndex, recoveryTime, categoryRecoveryTime, interruptFlags, auraInterruptFlags, channelInterruptFlags, procFlags, procChance, procCharges, maxLevel, baseLevel, spellLevel, durationIndex, powerType, manaCost, manaCostPerlevel, manaPerSecond, manaPerSecondPerLevel, rangeIndex, speed, stackAmount, totem1, totem2, reagent1, reagent2, reagent3, reagent4, reagent5, reagent6, reagent7, reagent8, reagentCount1, reagentCount2, reagentCount3, reagentCount4, reagentCount5, reagentCount6, reagentCount7, reagentCount8, equippedItemClass, equippedItemSubClassMask, equippedItemInventoryTypeMask, effect1, effect2, effect3, effectDieSides1, effectDieSides2, effectDieSides3, effectBaseDice1, effectBaseDice2, effectBaseDice3, effectDicePerLevel1, effectDicePerLevel2, effectDicePerLevel3, effectRealPointsPerLevel1, effectRealPointsPerLevel2, effectRealPointsPerLevel3, effectBasePoints1, effectBasePoints2, effectBasePoints3, effectMechanic1, effectMechanic2, effectMechanic3, effectImplicitTargetA1, effectImplicitTargetA2, effectImplicitTargetA3, effectImplicitTargetB1, effectImplicitTargetB2, effectImplicitTargetB3, effectRadiusIndex1, effectRadiusIndex2, effectRadiusIndex3, effectApplyAuraName1, effectApplyAuraName2, effectApplyAuraName3, effectAmplitude1, effectAmplitude2, effectAmplitude3, effectMultipleValue1, effectMultipleValue2, effectMultipleValue3, effectChainTarget1, effectChainTarget2, effectChainTarget3, effectItemType1, effectItemType2, effectItemType3, effectMiscValue1, effectMiscValue2, effectMiscValue3, effectMiscValueB1, effectMiscValueB2, effectMiscValueB3, effectTriggerSpell1, effectTriggerSpell2, effectTriggerSpell3, effectPointsPerComboPoint1, effectPointsPerComboPoint2, effectPointsPerComboPoint3, spellVisual, spellIconID, activeIconID, spellName1, spellName2, spellName3, spellName4, spellName5, spellName6, spellName7, spellName8, spellName9, spellName10, spellName11, spellName12, spellName13, spellName14, spellName15, spellName16, rank1, rank2, rank3, rank4, rank5, rank6, rank7, rank8, rank9, rank10, rank11, rank12, rank13, rank14, rank15, rank16, manaCostPercentage, startRecoveryCategory, startRecoveryTime, maxTargetLevel, spellFamilyName, spellFamilyFlags, maxAffectedTargets, dmgClass, preventionType, dmgMultiplier1, dmgMultiplier2, dmgMultiplier3, totemCategory1, totemCategory2, areaId, schoolMask, customAttributesFlags) VALUES
  (34038,	0,	0,	0,	134217984,	268435456,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	101,	0,	0,	0,	0,	21,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	23,	0,	0,	1000,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	34039,	0,	0,	0,	0,	0,	8719,	1,	0,	'Tunnel Bore Red Passive',	'',	'Forage de tunnel Passif rouge',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	'',	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0);
-- NPC 18678
SET @ENTRY = 18678;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 25, 0, 100, 1, 0, 0, 0, 0, 11, 34038, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - On Reset - Cast "<a href="http://wowhead.com/spell=34038">Tunnel Bore Red Passive</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 1, 0, 0, 0, 0, 18, 33554434, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - On Reset - Set Unit Flag Non Attackable and  Not Selectable (No Repeat)'),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 33928, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - On Reset - Cast "<a href="http://wowhead.com/spell=33928">Sandworm Submerge Visual</a>" '),
  (@ENTRY, 0, 5, 0, 4, 0, 100, 1, 0, 0, 0, 0, 80, @ENTRY*100+1, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - On Aggro - Run Script <a href="/smartai/script/1867801">1867801</a> (No Repeat)'),
  (@ENTRY, 0, 10, 0, 0, 0, 100, 0, 1000, 1000, 2100, 4500, 11, 31747, 0, 2000, 3000, 50, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - In Combat - Cast "<a href="http://wowhead.com/spell=31747">Poison</a>" '),
  (@ENTRY, 0, 12, 0, 9, 0, 100, 0, 0, 5, 45000, 50000, 11, 32738, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - Within 0-5 Range - Cast "<a href="http://wowhead.com/spell=32738">Bore</a>" '),
  (@ENTRY, 0, 30, 31, 34, 0, 100, 0, 0, 1, 0, 0, 28, 33928, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - On Reached Point 1 - Remove Aura "<a href="http://wowhead.com/spell=33928">Sandworm Submerge Visual</a>" '),
  (@ENTRY, 0, 31, 0, 61, 0, 100, 0, 0, 0, 0, 0, 19, 33554432, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - On Reached Point 1 - Set Unit Flag Not Selectable ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 300, 0, 0, 0, 100, 0, 0, 0, 0, 0, 28, 34038, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - In Combat - Remove Aura "<a href="http://wowhead.com/spell=34038">Tunnel Bore Red Passive</a>" '),
  (@ENTRY*100+1, 9, 301, 0, 0, 0, 100, 0, 0, 0, 0, 0, 28, 33928, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - In Combat - Remove Aura "<a href="http://wowhead.com/spell=33928">Sandworm Submerge Visual</a>" '),
  (@ENTRY*100+1, 9, 302, 0, 0, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - In Combat - Disable Combat Movement '),
  (@ENTRY*100+1, 9, 303, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 26262, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - In Combat - Cast "<a href="http://wowhead.com/spell=26262">Birth</a>" '),
  (@ENTRY*100+1, 9, 304, 0, 0, 0, 100, 0, 250, 250, 0, 0, 19, 33554434, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fulgorge - In Combat - Set Unit Flag Non Attackable and  Not Selectable ');

# SmartAIMgr: Entry 18701 SourceType 0 Event 0 Action 11 uses min/max params wrong (5000/1500), skipped.
UPDATE smart_scripts SET event_param1 = 1500, event_param2 = 5000 WHERE entryorguid = 18701 AND source_type = 0 AND id = 0;

# SmartAIMgr: Entry 18703 SourceType 0 Event 2 Action 49 has maxDist 0 as target_param1, skipped.
-- NPC 18703
SET @ENTRY = 18703;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 54, 0, 100, 1, 10000, 10000, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sethekk Spirit - On Just Summoned - Despawn In 10000ms (No Repeat)'),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 1, 0, 10000, 0, 0, 11, 24051, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sethekk Spirit - On Just Summoned - Cast "<a href="http://wowhead.com/spell=24051">Spirit Burst</a>" (No Repeat)'),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 0, 30, 30, 0, 0, 0, 0, 0, 'Sethekk Spirit - On Just Summoned - Start Attacking ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 18848 SourceType 0, Event 2, Missing Repeat flag.
-- NPC 18848
SET @ENTRY = 18848;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 5000, 10000, 15000, 25000, 11, 33493, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Malicious Instructor - In Combat - Cast "<a href="http://wowhead.com/spell=33493">Mark of Malice</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 10000, 20000, 10000, 20000, 11, 33501, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Malicious Instructor - In Combat - Cast "<a href="http://wowhead.com/spell=33501">Shadow Nova</a>" '),
  (@ENTRY, 0, 2, 0, 9, 0, 100, 4, 0, 5, 10000, 20000, 11, 6713, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Malicious Instructor - Within 0-5 Range - Cast "<a href="http://wowhead.com/spell=6713">Disarm</a>" (Heroic Dungeon)');

# SmartAIMgr: Entry 18869 SourceType 0 Event 0 Action 12 creature summon: There is a summon spell for creature entry 17471 (SpellId: 30496, effect: 0)
-- NPC 18869
SET @ENTRY = 18869;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 6, 0, 50, 0, 0, 0, 0, 0, 11, 30496, 2, 100000, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Unstable Voidwraith - On Death - Cast "<a href="http://wowhead.com/spell=30496">Lesser Shadow Fissure</a>" '),
  (@ENTRY, 0, 1, 0, 11, 0, 100, 0, 0, 0, 0, 0, 11, 34302, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Unstable Voidwraith - On Respawn - Cast "<a href="http://wowhead.com/spell=34302">Coalesce</a>" ');

# SmartAIMgr: Entry 18938 SourceType 0 Event 2 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 18938 SourceType 0 Event 2 Action 1 uses non-existent text 0, skipped.
DELETE FROM smart_scripts WHERE entryorguid = 18938 AND source_type = 0 AND id = 2;

# SmartAIMgr::LoadSmartAIFromDB: Creature entry (18944) is not using SmartAI, skipped loading.
# SmartAIMgr::LoadSmartAIFromDB: Creature entry (18944) is not using SmartAI, skipped loading.
# SmartAIMgr::LoadSmartAIFromDB: Creature entry (18945) is not using SmartAI, skipped loading.
# SmartAIMgr::LoadSmartAIFromDB: Creature entry (18945) is not using SmartAI, skipped loading.
# SmartAIMgr::LoadSmartAIFromDB: Creature entry (18945) is not using SmartAI, skipped loading.
# SmartAIMgr::LoadSmartAIFromDB: Creature entry (18945) is not using SmartAI, skipped loading.
DELETE FROM smart_scripts WHERE entryorguid IN (18944,18945) AND source_type = 0;

# SmartAIMgr::LoadSmartAIFromDB: Entry 19016 SourceType 0, Event 0, Missing Repeat flag.
# SmartAIMgr::LoadSmartAIFromDB: Entry 19016 SourceType 0, Event 1, Missing Repeat flag.
-- NPC 19016
SET @ENTRY = 19016;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 2, 0, 0, 0, 0, 58, 2, 11921, 3000, 3500, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hellfire Familiar - On AI Initialize - Install Turret Template (Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 37, 0, 100, 4, 0, 0, 0, 0, 58, 2, 14034, 3000, 3500, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hellfire Familiar - On AI Initialize - Install Turret Template (Heroic Dungeon)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 4, 0, 15000, 15000, 30000, 11, 13341, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Hellfire Familiar - In Combat - Cast "<a href="http://wowhead.com/spell=13341">Fire Blast</a>" (Heroic Dungeon)');

# SmartAIMgr::LoadSmartAIFromDB: Entry 19440 SourceType 0, Event 0, Missing Repeat flag.
-- NPC 19440
SET @ENTRY = 19440;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 80, @ENTRY*100+1, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Eye of Grillok - On Aggro - Run Script <a href="/smartai/script/1944001">1944001</a> (No Repeat)');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Eye of Grillok - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 39, 30, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Eye of Grillok - In Combat - Call For Help '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Eye of Grillok - In Combat - Despawn Instant ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 19720 SourceType 0, Event 1, Missing Repeat flag.
UPDATE creature_template SET faction = 1194 WHERE entry IN (19720,19726,19725);
-- NPC 19720
SET @ENTRY = 19720;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 62, 0, 100, 0, 9920, 0, 0, 0, 80, 1972000, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - On Gossip 9920 Option 0 Selected - Run Script <a href="/smartai/script/1972000">1972000</a> '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 1, 0, 0, 80, 1972001, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - Between 0-1% HP - Run Script <a href="/smartai/script/1972001">1972001</a> (No Repeat)'),
  (@ENTRY, 0, 2, 3, 25, 0, 100, 0, 0, 0, 0, 0, 2, 1194, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - On Reset - Set Faction 1194 '),
  (@ENTRY, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 18, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - On Reset - Set Unit Flag Immune to PC '),
  (@ENTRY, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 81, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - On Reset - Set NPC Flag Gossip and  Quest Giver ');
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Time to teach you a lesson in manners, little $gboy:girl;!", 12, 0, 100, 5, 0, "&quot;Dirty&quot; Larry - ");
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Close Gossip '),
  (@ENTRY*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY*100, 9, 2, 0, 0, 0, 100, 0, 500, 500, 0, 0, 66, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Set Orientation 0 '),
  (@ENTRY*100, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Say Line 0 '),
  (@ENTRY*100, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 0, 0, 0, 0, 0, 9, 0, 0, 0, 20, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Set Data 1 0 '),
  (@ENTRY*100, 9, 5, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Say Line 1 '),
  (@ENTRY*100, 9, 6, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Say Line 2 '),
  (@ENTRY*100, 9, 7, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Say Line 3 '),
  (@ENTRY*100, 9, 8, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Say Line 4 '),
  (@ENTRY*100, 9, 9, 0, 0, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Store Targetlist 1 '),
  (@ENTRY*100, 9, 10, 0, 0, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 9, 0, 0, 0, 20, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Send Target 1 '),
  (@ENTRY*100, 9, 11, 0, 0, 0, 100, 0, 0, 0, 0, 0, 42, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Set Invincibility At 0% HP '),
  (@ENTRY*100, 9, 12, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 2, 14, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Set Faction 14 '),
  (@ENTRY*100, 9, 13, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 0, 0, 0, 20, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Set Data 1 1 '),
  (@ENTRY*100, 9, 14, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Start Attacking ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 2, 1194, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Set Faction 1194 '),
  (@ENTRY*100+1, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 2, 0, 0, 0, 0, 9, 0, 0, 0, 20, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Set Data 1 2 '),
  (@ENTRY*100+1, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 26, 10231, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Quest Credit "<a href="http://wowhead.com/quest=10231">What Book? I Don"t See Any Book.</a>" '),
  (@ENTRY*100+1, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Say Line 5 '),
  (@ENTRY*100+1, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Evade '),
  (@ENTRY*100+1, 9, 5, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 81, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Dirty&quot; Larry - In Combat - Set NPC Flag Gossip and  Quest Giver ');

# SmartAIMgr: Entry 19725 SourceType 0 Event 7 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 19725 SourceType 0 Event 7 Action 1 uses non-existent text 0, skipped.
-- NPC 19725
SET @ENTRY = 19725;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 25, 0, 100, 0, 0, 0, 0, 0, 2, 1194, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Epic&quot; Malone - On Reset - Set Faction 1194 '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 18, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Epic&quot; Malone - On Reset - Set Unit Flag Immune to PC '),
  (@ENTRY, 0, 2, 3, 38, 0, 100, 0, 1, 1, 0, 0, 2, 14, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Epic&quot; Malone - On Data Set 1 1 - Set Faction 14 '),
  (@ENTRY, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 19, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Epic&quot; Malone - On Data Set 1 1 - Set Unit Flag Immune to PC '),
  (@ENTRY, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, '&quot;Epic&quot; Malone - On Data Set 1 1 - Start Attacking '),
  (@ENTRY, 0, 5, 0, 38, 0, 100, 0, 1, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Epic&quot; Malone - On Data Set 1 2 - Evade '),
  (@ENTRY, 0, 6, 0, 38, 0, 100, 0, 1, 0, 0, 0, 80, 1972501, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Epic&quot; Malone - On Data Set 1 0 - Run Script <a href="/smartai/script/1972501">1972501</a> ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 91, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Epic&quot; Malone - In Combat - Set Flag Sleep '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 66, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, '&quot;Epic&quot; Malone - In Combat - Set Orientation 0 '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Epic&quot; Malone - In Combat - Say Line 0 ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s cracks his knucles.", 16, 0, 100, 23, 0, "&quot;Epic&quot; Malone - ");

# SmartAIMgr: Entry 19726 SourceType 0 Event 7 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 19726 SourceType 0 Event 7 Action 1 uses non-existent text 0, skipped.
-- NPC 19726
SET @ENTRY = 19726;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 25, 0, 100, 0, 0, 0, 0, 0, 2, 1194, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Creepjack&quot; - On Reset - Set Faction 1194 '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 18, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Creepjack&quot; - On Reset - Set Unit Flag Immune to PC '),
  (@ENTRY, 0, 2, 3, 38, 0, 100, 0, 1, 1, 0, 0, 2, 14, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Creepjack&quot; - On Data Set 1 1 - Set Faction 14 '),
  (@ENTRY, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 19, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Creepjack&quot; - On Data Set 1 1 - Set Unit Flag Immune to PC '),
  (@ENTRY, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, '&quot;Creepjack&quot; - On Data Set 1 1 - Start Attacking '),
  (@ENTRY, 0, 5, 0, 38, 0, 100, 0, 1, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Creepjack&quot; - On Data Set 1 2 - Evade '),
  (@ENTRY, 0, 6, 0, 38, 0, 100, 0, 1, 0, 0, 0, 80, 1972501, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '&quot;Creepjack&quot; - On Data Set 1 0 - Run Script <a href="/smartai/script/1972501">1972501</a> ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s cracks his knucles.", 16, 0, 100, 23, 0, "&quot;Creepjack&quot; - ");

# SmartAIMgr: Entry 19946 SourceType 0 Event 1 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 19946 SourceType 0 Event 1 Action 1 uses non-existent text 0, skipped.
SET @ENTRY = 19946;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 5000, 10000, 15000, 20000, 11, 13730, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Slaver - In Combat - Cast "<a href="http://wowhead.com/spell=13730">Demoralizing Shout</a>" '),
  (@ENTRY, 0, 1, 2, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Slaver - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 39, 20, 0, 0, 0, 0, 0, 9, 6, 18112, 0, 20, 0, 0, 0, 0, 'Darkcrest Slaver - On Aggro - Call For Help ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s calls for a nearby slave to assist him!", 16, 0, 100, 0, 0, "Darkcrest Slaver - ");

# SmartAIMgr: Entry 19947 SourceType 0 Event 0 Action 11 uses non-existent Spell entry 0, skipped.
-- NPC 19947
SET @ENTRY = 19947;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 23, 0, 100, 0, 12544, 0, 10000, 20000, 11, 12544, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Sorceress - On Missing Aura "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" - Cast "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 500, 1500, 3000, 4000, 11, 13901, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Sorceress - In Combat - Cast "<a href="http://wowhead.com/spell=13901">Arcane Bolt</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 15000, 20000, 20000, 30000, 11, 34787, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Sorceress - In Combat - Cast "<a href="http://wowhead.com/spell=34787">Freezing Circle</a>" ');

# SmartAIMgr: Entry 20049 SourceType 0 Event 4 Action 11 Parameter can not be NULL, skipped.
# SmartAIMgr: Entry 20049 SourceType 0 Event 5 Action 11 Parameter can not be NULL, skipped.
-- NPC 20049
SET @ENTRY = 20049;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 5000, 5000, 25000, 50000, 11, 39077, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Crimson Hand Blood Knight - In Combat - Cast "<a href="http://wowhead.com/spell=39077">Hammer of Justice</a>" '),
  (@ENTRY, 0, 1, 0, 12, 0, 100, 0, 0, 20, 15000, 15000, 11, 37259, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Crimson Hand Blood Knight - Target Between 0-20% HP - Cast "<a href="http://wowhead.com/spell=37259">Hammer of Wrath</a>" '),
  (@ENTRY, 0, 2, 0, 9, 0, 100, 0, 0, 50, 15000, 25000, 11, 37257, 0, 0, 0, 0, 0, 102, 21, 50, 75, 0, 0, 0, 0, 0, 'Crimson Hand Blood Knight - Within 0-50 Range - Cast "<a href="http://wowhead.com/spell=37257">Flash of Light</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 60000, 60000, 120000, 160000, 11, 37257, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Crimson Hand Blood Knight - In Combat - Cast "<a href="http://wowhead.com/spell=37257">Flash of Light</a>" '),
  (@ENTRY, 0, 4, 0, 9, 0, 100, 0, 0, 40, 40000, 40000, 11, 37260, 0, 0, 0, 0, 0, 102, 0, 40, 60, 0, 0, 0, 0, 0, 'Crimson Hand Blood Knight - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=37260">Renew</a>" '),
  (@ENTRY, 0, 5, 0, 15, 0, 100, 0, 30, 10000, 20000, 60000, 11, 39078, 0, 0, 0, 0, 0, 9, 21, 0, 0, 30, 0, 0, 0, 0, 'Crimson Hand Blood Knight - On Friendly CCed - Cast "<a href="http://wowhead.com/spell=39078">Cleanse</a>" ');

# SmartAIMgr: Entry 20079 SourceType 0 Event 0 Action 1 using non-existent Text id 0, skipped.
# SmartAIMgr: Entry 20079 SourceType 0 Event 0 Action 1 uses non-existent text 0, skipped.
-- NPC 20079
SET @ENTRY = 20079;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 80, 2007901, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Sentry - On Aggro - Run Script <a href="/smartai/script/2007901">2007901</a> ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 0, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Sentry - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 39, 30, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Sentry - In Combat - Call For Help '),
  (@ENTRY*100+1, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darkcrest Sentry - In Combat - Die ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s calls for help!", 16, 0, 100, 0, 0, "Darkcrest Sentry - ");

# SmartAIMgr: Entry 20143 SourceType 0 Event 1 Action 12 creature summon: There is a summon spell for creature entry 20145 (SpellId: 34943, effect: 0)
-- NPC 20143
SET @ENTRY = 20143;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 60, 0, 100, 0, 2000, 5000, 15000, 23000, 12, 20145, 6, 30000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Void Spawner - Quest - Warp Rifts - On Update - Summon "<a href="http://wowhead.com/npc=20145">Unstable Voidwalker</a>" '),
  (@ENTRY, 0, 2, 0, 37, 0, 100, 0, 0, 0, 0, 0, 41, 120000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Void Spawner - Quest - Warp Rifts - On AI Initialize - Despawn In 120000ms ');

# SmartAIMgr::LoadSmartAIFromDB: Entry 20159 SourceType 0, Event 1, Missing Repeat flag.
# SmartAIMgr::LoadSmartAIFromDB: Entry 20159 SourceType 0, Event 4, Missing Repeat flag.
-- NPC 20159
SET @ENTRY = 20159;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 62, 0, 100, 0, 7, 1, 0, 0, 80, 2015901, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - On Gossip 7 Option 1 Selected - Run Script <a href="/smartai/script/2015901">2015901</a> '),
  (@ENTRY, 0, 4, 0, 2, 0, 100, 1, 0, 1, 0, 0, 80, 2015902, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - Between 0-1% HP - Run Script <a href="/smartai/script/2015902">2015902</a> (No Repeat)'),
  (@ENTRY, 0, 6, 7, 11, 0, 100, 0, 0, 0, 0, 0, 82, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - On Respawn - Set NPC Flag Gossip '),
  (@ENTRY, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 152, 1831, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - On Respawn - Load Path 1831 '),
  (@ENTRY, 0, 8, 0, 25, 0, 100, 0, 0, 0, 0, 0, 42, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - On Reset - Set Invincibility At 0% HP '),
  (@ENTRY, 0, 9, 0, 0, 0, 100, 0, 0, 3000, 3000, 7000, 11, 20823, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Cast "<a href="http://wowhead.com/spell=20823">Fireball</a>" '),
  (@ENTRY, 0, 10, 0, 9, 0, 100, 0, 0, 10, 10000, 15000, 11, 11831, 0, 0, 0, 0, 0, 17, 0, 0, 10, 0, 0, 0, 0, 0, 'Magister Aledis - Within 0-10 Range - Cast "<a href="http://wowhead.com/spell=11831">Frost Nova</a>" ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Set NPC Flag Gossip '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 152, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Load Path 0 '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Close Gossip '),
  (@ENTRY*100+1, 9, 104, 0, 0, 0, 100, 0, 0, 0, 0, 0, 43, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Dismount '),
  (@ENTRY*100+1, 9, 105, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 66, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Set Orientation 0 '),
  (@ENTRY*100+1, 9, 106, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 108, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 2, 14, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Set Faction 14 '),
  (@ENTRY*100+1, 9, 109, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Start Attacking '),
  (@ENTRY*100+1, 9, 110, 0, 0, 0, 100, 0, 0, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Set Home Position ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+2 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+2, 9, 200, 0, 0, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Set React State Passive '),
  (@ENTRY*100+2, 9, 201, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Say Line 1 '),
  (@ENTRY*100+2, 9, 202, 0, 0, 0, 100, 0, 0, 0, 0, 0, 2, 1604, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Set Faction 1604 '),
  (@ENTRY*100+2, 9, 203, 0, 0, 0, 100, 0, 0, 0, 0, 0, 81, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Set NPC Flag Quest Giver '),
  (@ENTRY*100+2, 9, 204, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Set Event Phase 1 '),
  (@ENTRY*100+2, 9, 205, 0, 0, 0, 100, 0, 0, 0, 0, 0, 103, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Set Root On '),
  (@ENTRY*100+2, 9, 207, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 60000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Despawn In 60000ms ');

# SmartAIMgr::LoadSmartAIFromDB: Creature entry (20208) is not using SmartAI, skipped loading.
DELETE FROM smart_scripts WHERE entryorguid = 20208 AND source_type = 0;

# SmartAIMgr: Warning: Entry 20216 SourceType 0 Event 3 Action 50 gameobject summon: There is a summon spell for gameobject entry 185567 (SpellId: 39890, effect: 0)
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
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 22 AND SourceGroup = 4 AND SourceEntry = 20216 AND ConditionTypeOrReference = 9 AND ConditionValue1 = 10995;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment)
VALUES (22, 4, 20216, 0, 0, 9, 0, 10995, 0, 0, 0, 0, 0, '', NULL);

# SmartAIMgr: Entry 20243 SourceType 0 Event 9 Action 75 uses non-existent Spell entry 39311, skipped.
# Aura Scrapped Fel Reaver Transform'
DELETE FROM spell_template WHERE entry = 39311;
INSERT INTO spell_template (entry, category, dispel, mechanic, attributes, attributesEx, attributesEx2, attributesEx3, attributesEx4, attributesEx5, attributesEx6, stances, stancesNot, targets, targetCreatureType, requiresSpellFocus, facingCasterFlags, casterAuraState, targetAuraState, casterAuraStateNot, targetAuraStateNot, castingTimeIndex, recoveryTime, categoryRecoveryTime, interruptFlags, auraInterruptFlags, channelInterruptFlags, procFlags, procChance, procCharges, maxLevel, baseLevel, spellLevel, durationIndex, powerType, manaCost, manaCostPerlevel, manaPerSecond, manaPerSecondPerLevel, rangeIndex, speed, stackAmount, totem1, totem2, reagent1, reagent2, reagent3, reagent4, reagent5, reagent6, reagent7, reagent8, reagentCount1, reagentCount2, reagentCount3, reagentCount4, reagentCount5, reagentCount6, reagentCount7, reagentCount8, equippedItemClass, equippedItemSubClassMask, equippedItemInventoryTypeMask, effect1, effect2, effect3, effectDieSides1, effectDieSides2, effectDieSides3, effectBaseDice1, effectBaseDice2, effectBaseDice3, effectDicePerLevel1, effectDicePerLevel2, effectDicePerLevel3, effectRealPointsPerLevel1, effectRealPointsPerLevel2, effectRealPointsPerLevel3, effectBasePoints1, effectBasePoints2, effectBasePoints3, effectMechanic1, effectMechanic2, effectMechanic3, effectImplicitTargetA1, effectImplicitTargetA2, effectImplicitTargetA3, effectImplicitTargetB1, effectImplicitTargetB2, effectImplicitTargetB3, effectRadiusIndex1, effectRadiusIndex2, effectRadiusIndex3, effectApplyAuraName1, effectApplyAuraName2, effectApplyAuraName3, effectAmplitude1, effectAmplitude2, effectAmplitude3, effectMultipleValue1, effectMultipleValue2, effectMultipleValue3, effectChainTarget1, effectChainTarget2, effectChainTarget3, effectItemType1, effectItemType2, effectItemType3, effectMiscValue1, effectMiscValue2, effectMiscValue3, effectMiscValueB1, effectMiscValueB2, effectMiscValueB3, effectTriggerSpell1, effectTriggerSpell2, effectTriggerSpell3, effectPointsPerComboPoint1, effectPointsPerComboPoint2, effectPointsPerComboPoint3, spellVisual, spellIconID, activeIconID, spellName1, spellName2, spellName3, spellName4, spellName5, spellName6, spellName7, spellName8, spellName9, spellName10, spellName11, spellName12, spellName13, spellName14, spellName15, spellName16, rank1, rank2, rank3, rank4, rank5, rank6, rank7, rank8, rank9, rank10, rank11, rank12, rank13, rank14, rank15, rank16, manaCostPercentage, startRecoveryCategory, startRecoveryTime, maxTargetLevel, spellFamilyName, spellFamilyFlags, maxAffectedTargets, dmgClass, preventionType, dmgMultiplier1, dmgMultiplier2, dmgMultiplier3, totemCategory1, totemCategory2, areaId, schoolMask, customAttributesFlags)
VALUES (39311, 0, 0, 0, 2155872640, 268435456, 1, 269484032, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 101, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22509, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Scrapped Fel Reaver Transform', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0);
-- NPC 20243
SET @ENTRY = 20243;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', modelid1 = 21072, unit_flags = 131846 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 3, 0, 60, 1, 100, 0, 2000, 2000, 30000, 30000, 12, 20287, 2, 180000, 0, 1, 0, 8, 0, 0, 0, 0, 2547.08, 3982.24, 131.39, 2.01, 'Scrapped Fel Reaver - On Update - Summon "<a href="http://wowhead.com/npc=20287">Zaxxis Ambusher</a>" (Phase 1)'),
  (@ENTRY, 0, 4, 0, 60, 1, 100, 0, 17000, 17000, 45000, 45000, 12, 20287, 2, 180000, 0, 1, 0, 8, 0, 0, 0, 0, 2537.7, 3975.96, 130.4, 1.58, 'Scrapped Fel Reaver - On Update - Summon "<a href="http://wowhead.com/npc=20287">Zaxxis Ambusher</a>" (Phase 1)'),
  (@ENTRY, 0, 5, 0, 60, 1, 100, 0, 32000, 32000, 45000, 45000, 12, 20287, 2, 180000, 0, 1, 0, 8, 0, 0, 0, 0, 2506.46, 4008.93, 133.8, 6.19, 'Scrapped Fel Reaver - On Update - Summon "<a href="http://wowhead.com/npc=20287">Zaxxis Ambusher</a>" (Phase 1)'),
  (@ENTRY, 0, 6, 0, 60, 1, 100, 0, 60000, 60000, 45000, 45000, 12, 20287, 2, 180000, 0, 1, 0, 8, 0, 0, 0, 0, 2537.3, 4027.11, 135.5, 4.3, 'Scrapped Fel Reaver - On Update - Summon "<a href="http://wowhead.com/npc=20287">Zaxxis Ambusher</a>" (Phase 1)'),
  (@ENTRY, 0, 7, 0, 6, 0, 100, 0, 0, 0, 0, 0, 51, 0, 0, 0, 0, 0, 0, 9, 0, 20287, 0, 150, 0, 0, 0, 0, 'Scrapped Fel Reaver - On Death - Kill Target '),
  (@ENTRY, 0, 8, 0, 7, 0, 100, 0, 0, 0, 0, 0, 51, 0, 0, 0, 0, 0, 0, 9, 0, 20287, 0, 150, 0, 0, 0, 0, 'Scrapped Fel Reaver - On Evade - Kill Target '),
  (@ENTRY, 0, 10, 0, 8, 0, 100, 1, 35282, 0, 0, 0, 80, @ENTRY*100+1, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Scrapped Fel Reaver - On Spellhit "<a href="http://wowhead.com/spell=35282">Fel Zapper</a>" - Run Script <a href="/smartai/script/2024301">2024301</a> (No Repeat)'),
  (@ENTRY, 0, 13, 0, 25, 0, 100, 0, 0, 0, 0, 0, 18, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Scrapped Fel Reaver - On Reset - Set Unit Flag Server Controlled '),
  (@ENTRY, 0, 15, 0, 37, 0, 100, 0, 1000, 2000, 1000, 1000, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Scrapped Fel Reaver - On AI Initialize - Set React State Passive ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Scrapped Fel Reaver - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 19, 258, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Scrapped Fel Reaver - In Combat - Set Unit Flag Non Attackable and  Immune to PC '),
  (@ENTRY*100+1, 9, 103, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Scrapped Fel Reaver - In Combat - Set Event Phase 1 ');
REPLACE INTO creature_template_addon (entry, path_id, mount, bytes0, bytes1, bytes2, emote, moveflags, auras) VALUES
  (@ENTRY,	0,	0,	0,	0,	0,	0,	0,	'39311');

-- NPC 20287
SET @ENTRY = 20287;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 2537.139404, 3995.689697, 132.510269, 0, 'Zaxxis Ambusher - On Just Summoned - Move To Pos '),
  (@ENTRY, 0, 1, 0, 34, 0, 100, 0, 0, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 0, 30, 0, 0, 0, 0, 0, 0, 'Zaxxis Ambusher - On Reached Point 1 - Start Attacking ');










