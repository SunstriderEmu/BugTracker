# SmartAIMgr: Entry 18400 SourceType 0 Event 5 Action 15 SpecialFlags for Quest entry 9970 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
# SmartAIMgr: Entry 18401 SourceType 0 Event 3 Action 15 SpecialFlags for Quest entry 9972 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
# SmartAIMgr: Entry 18402 SourceType 0 Event 5 Action 15 SpecialFlags for Quest entry 9973 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
# Ring of Blood
-- NPC 18471
SET @ENTRY = 18471;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 19, 0, 100, 0, 9962, 0, 0, 0, 80, 1847101, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Quest "<a href="http://wowhead.com/quest=9962">The Ring of Blood: Brokentoe</a>" Accepted - Run Script <a href="/smartai/script/1847101">1847101</a> '),
  (@ENTRY, 0, 1, 2, 38, 0, 100, 0, 10, 10, 0, 0, 1, 2, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 10 10 - Say Line 2 '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 10 10 - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY, 0, 10, 0, 19, 0, 100, 0, 9967, 0, 0, 0, 80, 1847102, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Quest "<a href="http://wowhead.com/quest=9967">The Ring of Blood: The Blue Brothers</a>" Accepted - Run Script <a href="/smartai/script/1847102">1847102</a> '),
  (@ENTRY, 0, 11, 12, 60, 2, 100, 0, 500, 1000, 10000, 10000, 1, 4, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Update - Say Line 4 (Phase 2)'),
  (@ENTRY, 0, 12, 13, 61, 2, 100, 0, 0, 0, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Update - Set NPC Flag Gossip and  Quest Giver (Phase 2)'),
  (@ENTRY, 0, 13, 0, 61, 2, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Update - Set Event Phase 0 (Phase 2)'),
  (@ENTRY, 0, 20, 0, 19, 0, 100, 0, 9970, 0, 0, 0, 80, 1847103, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Quest "<a href="http://wowhead.com/quest=9970">The Ring of Blood: Rokdar the Sundered Lord</a>" Accepted - Run Script <a href="/smartai/script/1847103">1847103</a> '),
  (@ENTRY, 0, 21, 22, 38, 0, 100, 0, 12, 12, 0, 0, 1, 6, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 12 12 - Say Line 6 '),
  (@ENTRY, 0, 22, 23, 61, 0, 100, 0, 0, 0, 0, 0, 45, 12, 12, 0, 0, 0, 0, 10, 0, 311406, 18069, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 12 12 - Set Data 12 12 '),
  (@ENTRY, 0, 23, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 12 12 - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY, 0, 30, 0, 19, 0, 100, 0, 9972, 0, 0, 0, 80, 1847104, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Quest "<a href="http://wowhead.com/quest=9972">The Ring of Blood: Skra"gath</a>" Accepted - Run Script <a href="/smartai/script/1847104">1847104</a> '),
  (@ENTRY, 0, 31, 32, 38, 0, 100, 0, 13, 13, 0, 0, 1, 8, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 13 13 - Say Line 8 '),
  (@ENTRY, 0, 32, 33, 61, 0, 100, 0, 0, 0, 0, 0, 45, 13, 13, 0, 0, 0, 0, 10, 0, 311406, 18069, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 13 13 - Set Data 13 13 '),
  (@ENTRY, 0, 33, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 13 13 - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY, 0, 40, 0, 19, 0, 100, 0, 9973, 0, 0, 0, 80, 1847105, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Quest "<a href="http://wowhead.com/quest=9973">The Ring of Blood: The Warmaul Champion</a>" Accepted - Run Script <a href="/smartai/script/1847105">1847105</a> '),
  (@ENTRY, 0, 41, 42, 38, 0, 100, 0, 14, 14, 0, 0, 1, 10, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 14 14 - Say Line 10 '),
  (@ENTRY, 0, 42, 43, 61, 0, 100, 0, 0, 0, 0, 0, 45, 14, 14, 0, 0, 0, 0, 10, 0, 311406, 18069, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 14 14 - Set Data 14 14 '),
  (@ENTRY, 0, 43, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 3, 14, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 14 14 - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY, 0, 50, 0, 19, 0, 100, 0, 9977, 0, 0, 0, 80, 1847106, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Quest "<a href="http://wowhead.com/quest=9977">The Ring of Blood: The Final Challenge</a>" Accepted - Run Script <a href="/smartai/script/1847106">1847106</a> '),
  (@ENTRY, 0, 51, 52, 38, 0, 100, 0, 15, 15, 0, 0, 1, 14, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 15 15 - Say Line 14 '),
  (@ENTRY, 0, 52, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 15 15 - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY, 0, 60, 0, 38, 0, 100, 0, 30, 30, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 30 30 - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY, 0, 61, 62, 38, 0, 100, 0, 20, 20, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 20 20 - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY, 0, 62, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 12, 0, 0, 0, 0, 0, 12, 8, 1, 0, 0, 0, 0, 0, 0, 'Gurgthock - On Data Set 20 20 - Say Line 12 ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Get in the Ring of Blood, $N. The fight is about to start!", 12, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 1, 0, "The battle is about to begin! $N versus the ferocious clefthoof, Brokentoe!", 14, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 2, 0, "$N has defeated Brokentoe!", 14, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 3, 0, "The battle is about to begin! The unmerciful Murkblood twins versus $N!", 14, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 4, 0, "Unbelievable! $N has defeated the Murkblood Twins!", 14, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 5, 0, "Hailing from the mountains of Blade's Edge comes Rokdar the Sundered Lord! $N is in for the fight of $g his:her; life.", 14, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 6, 0, "$N is victorious once more!", 14, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 7, 0, "From parts unkown: Skra'gath! Can $N possibly survive the onslaught of void energies?", 14, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 8, 0, "$N is victorious once more!", 14, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 9, 0, "This is the moment we've all been waiting for! The Warmaul champion is about to make $g his:her; first showing at the Ring of Blood in weeks! Will $N go down in defeat as easily as the champion's other opponents? We shall see...", 14, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 10, 0, "$N is victorious once more!", 14, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 11, 0, "Mogor has challenged you. You have to accept! Get in the ring if you are ready to fight.", 12, 0, 100, 0, 0, "Gurgthock"),
  (@ENTRY, 12, 0, "$N has been defeated!", 14, 0, 100, 0, 0, "Gurgthock - "),
  (@ENTRY, 13, 0, "For the first time in the Ring of Blood's history, Mogor has chosen to exercise his right of battle! On this wartorn ground, $N will face Mogor, hero of the Warmaul!", 14, 0, 100, 0, 0, "Gurgthock - "),
  (@ENTRY, 14, 0, "$N has defeated the hero of the Warmaul, Mogor! All hail $N!", 14, 0, 100, 0, 0, "Gurgthock - ");
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Store Targetlist 1 '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 103, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 1 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+2 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+2, 9, 200, 0, 0, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Store Targetlist 1 '),
  (@ENTRY*100+2, 9, 201, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY*100+2, 9, 202, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 0 '),
  (@ENTRY*100+2, 9, 203, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 3 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+3 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+3, 9, 300, 0, 0, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Store Targetlist 1 '),
  (@ENTRY*100+3, 9, 301, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY*100+3, 9, 302, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 0 '),
  (@ENTRY*100+3, 9, 303, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 5 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+4 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+4, 9, 400, 0, 0, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Store Targetlist 1 '),
  (@ENTRY*100+4, 9, 401, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY*100+4, 9, 402, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 0 '),
  (@ENTRY*100+4, 9, 403, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 7, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 7 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+5 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+5, 9, 500, 0, 0, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Store Targetlist 1 '),
  (@ENTRY*100+5, 9, 501, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY*100+5, 9, 502, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 0 '),
  (@ENTRY*100+5, 9, 503, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 9, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 9 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+6 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+6, 9, 600, 0, 0, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Store Targetlist 1 '),
  (@ENTRY*100+6, 9, 601, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY*100+6, 9, 602, 0, 0, 0, 100, 0, 1500, 1500, 0, 0, 1, 11, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 11 '),
  (@ENTRY*100+6, 9, 603, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 13, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 13 '),
  (@ENTRY*100+6, 9, 604, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 10, 0, 311406, 18069, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Say Line 3 '),
  (@ENTRY*100+6, 9, 605, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, 0, 311406, 18069, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Set Data 1 1 '),
  (@ENTRY*100+6, 9, 606, 0, 0, 0, 100, 0, 0, 0, 0, 0, 100, 1, 1, 0, 0, 0, 0, 10, 0, 311406, 18069, 0, 0, 0, 0, 0, 'Gurgthock - In Combat - Send Target 1 ');

# Brokentoe
UPDATE quest_start_scripts SET delay = 20 WHERE id = 9962;
-- NPC 18398
SET @ENTRY = 18398;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 1000, 1000, 9000, 11000, 11, 32023, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Brokentoe - In Combat - Cast "<a href="http://wowhead.com/spell=32023">Hoof Stomp</a>" '),
  (@ENTRY, 0, 2, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 10, 10, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Brokentoe - On Death - Set Data 10 10 (No Repeat)'),
  (@ENTRY, 0, 4, 5, 7, 0, 100, 1, 0, 0, 0, 0, 45, 20, 20, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Brokentoe - On Evade - Set Data 20 20 (No Repeat)'),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Brokentoe - On Evade - Despawn In 5000ms '),
  (@ENTRY, 0, 6, 0, 1, 0, 100, 0, 179000, 179000, 0, 0, 45, 30, 30, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Brokentoe - Out of Combat - Set Data 30 30 ');

-- NPC 18399 - Murkblood Twin
SET @ENTRY = 18399;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Twin - On Aggro - Say Line 0 '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 2000, 2000, 11, 14873, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Twin - In Combat - Cast "<a href="http://wowhead.com/spell=14873">Sinister Strike</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 5000, 6000, 11000, 12000, 11, 15691, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Twin - In Combat - Cast "<a href="http://wowhead.com/spell=15691">Eviscerate</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 8000, 9000, 15000, 16000, 11, 32319, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Twin - In Combat - Cast "<a href="http://wowhead.com/spell=32319">Mutilate</a>" '),
  (@ENTRY, 0, 5, 0, 6, 0, 100, 1, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Murkblood Twin - On Death - Increase Phase By 1 (No Repeat)'),
  (@ENTRY, 0, 6, 8, 7, 0, 100, 0, 0, 0, 0, 0, 45, 20, 20, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Murkblood Twin - On Evade - Set Data 20 20 '),
  (@ENTRY, 0, 7, 0, 1, 0, 100, 1, 179000, 179000, 0, 0, 45, 30, 30, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Murkblood Twin - Out of Combat - Set Data 30 30 (No Repeat)'),
  (@ENTRY, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Twin - On Evade - Despawn In 5000ms ');

-- NPC 18400 - Rokdar the Sundered Lord
SET @ENTRY = 18400;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - Out of Combat - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 9000, 11000, 11, 16727, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - In Combat - Cast "<a href="http://wowhead.com/spell=16727">War Stomp</a>" '),
  (@ENTRY, 0, 2, 0, 31, 0, 100, 0, 31389, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - On Target Spellhit "<a href="http://wowhead.com/spell=31389">Knock Away</a>" - Say Line 0 '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 6000, 6000, 12000, 12000, 11, 31389, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - In Combat - Cast "<a href="http://wowhead.com/spell=31389">Knock Away</a>" '),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 0, 20000, 20000, 25000, 25000, 11, 15976, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - In Combat - Cast "<a href="http://wowhead.com/spell=15976">Puncture</a>" '),
  (@ENTRY, 0, 6, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 12, 12, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - On Death - Set Data 12 12 (No Repeat)'),
  (@ENTRY, 0, 7, 8, 7, 0, 100, 0, 0, 0, 0, 0, 45, 20, 20, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - On Evade - Set Data 20 20 '),
  (@ENTRY, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - On Evade - Despawn In 5000ms '),
  (@ENTRY, 0, 9, 0, 1, 0, 100, 0, 179000, 179000, 0, 0, 45, 30, 30, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - Out of Combat - Set Data 30 30 ');

-- NPC 18401 - Skra'gath
SET @ENTRY = 18401;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 1, 0, 0, 0, 0, 11, 29299, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Skra&#039;gath - Out of Combat - Cast "<a href="http://wowhead.com/spell=29299">Draining Touch</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Skra&#039;gath - On Aggro - Say Line 0 '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 6000, 6000, 12000, 12000, 11, 32324, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Skra&#039;gath - In Combat - Cast "<a href="http://wowhead.com/spell=32324">Shadow Burst</a>" '),
  (@ENTRY, 0, 4, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 13, 13, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Skra&#039;gath - On Death - Set Data 13 13 (No Repeat)'),
  (@ENTRY, 0, 5, 6, 7, 0, 100, 1, 0, 0, 0, 0, 45, 20, 20, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Skra&#039;gath - On Evade - Set Data 20 20 (No Repeat)'),
  (@ENTRY, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Skra&#039;gath - On Evade - Despawn In 5000ms '),
  (@ENTRY, 0, 7, 0, 1, 0, 100, 1, 179000, 179000, 0, 0, 45, 30, 30, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Skra&#039;gath - Out of Combat - Set Data 30 30 (No Repeat)');

-- NPC 18402 - Warmaul Champion
SET @ENTRY = 18402;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Champion - On Aggro - Say Line 0 '),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 31403, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Champion - On Aggro - Cast "<a href="http://wowhead.com/spell=31403">Battle Shout</a>" '),
  (@ENTRY, 0, 2, 0, 9, 0, 100, 1, 5, 30, 1500, 2000, 11, 32323, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Champion - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=32323">Charge</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 3000, 4000, 6000, 7000, 11, 15708, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Champion - In Combat - Cast "<a href="http://wowhead.com/spell=15708">Mortal Strike</a>" '),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 0, 1000, 1000, 9000, 11000, 11, 17963, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Champion - In Combat - Cast "<a href="http://wowhead.com/spell=17963">Sundering Cleave</a>" '),
  (@ENTRY, 0, 6, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 14, 14, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Warmaul Champion - On Death - Set Data 14 14 (No Repeat)'),
  (@ENTRY, 0, 7, 8, 7, 0, 100, 1, 0, 0, 0, 0, 45, 20, 20, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Warmaul Champion - On Evade - Set Data 20 20 (No Repeat)'),
  (@ENTRY, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Champion - On Evade - Despawn In 5000ms '),
  (@ENTRY, 0, 9, 0, 1, 0, 100, 1, 179000, 179000, 0, 0, 45, 30, 30, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Warmaul Champion - Out of Combat - Set Data 30 30 (No Repeat)');

# Mogor
DELETE FROM creature WHERE guid = 311406;
INSERT INTO creature (guid, id, map, spawnMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, MovementType, pool_id, ScriptName) VALUES
  (311406,	18069,	530,	1,	0,	0,	-714.62,	7931.35,	58.8617,	4.50788,	5,	0,	0,	60720,	29330,	0,	0,	'');
-- NPC 18069
SET @ENTRY = 18069;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', faction = 35, flags_extra = 262144 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 1000, 1000, 3500, 3500, 11, 16033, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Cast "<a href="http://wowhead.com/spell=16033">Chain Lightning</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 4000, 4000, 11000, 13000, 11, 39529, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Cast "<a href="http://wowhead.com/spell=39529">Flame Shock</a>" '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 60, 0, 0, 11, 15982, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - Between 0-60% HP - Cast "<a href="http://wowhead.com/spell=15982">Healing Wave</a>" (No Repeat)'),
  (@ENTRY, 0, 5, 0, 2, 0, 100, 1, 0, 1, 0, 0, 80, 1806902, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - Between 0-1% HP - Run Script <a href="/smartai/script/1806902">1806902</a> (No Repeat)'),
  (@ENTRY, 0, 6, 0, 38, 0, 100, 0, 12, 12, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - On Data Set 12 12 - Say Line 1 '),
  (@ENTRY, 0, 7, 0, 38, 0, 100, 0, 13, 13, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - On Data Set 13 13 - Say Line 2 '),
  (@ENTRY, 0, 8, 0, 38, 0, 100, 0, 14, 14, 0, 0, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - On Data Set 14 14 - Say Line 6 '),
  (@ENTRY, 0, 9, 0, 38, 0, 100, 0, 1, 1, 0, 0, 53, 0, 18069, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - On Data Set 1 1 - Start Waypoint 18069 '),
  (@ENTRY, 0, 11, 12, 40, 0, 100, 0, 5, 18069, 0, 0, 54, 100000, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - On Waypoint 5 Reached - Pause Waypoint 100000ms '),
  (@ENTRY, 0, 12, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 1806901, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - On Waypoint 5 Reached - Run Script <a href="/smartai/script/1806901">1806901</a> '),
  (@ENTRY, 0, 13, 0, 6, 0, 100, 0, 0, 0, 0, 0, 45, 15, 15, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Mogor - On Death - Set Data 15 15 '),
  (@ENTRY, 0, 14, 15, 21, 0, 100, 0, 179000, 179000, 0, 0, 45, 20, 20, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Mogor - On Reached Home - Set Data 20 20 '),
  (@ENTRY, 0, 15, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - On Reached Home - Despawn In 5000ms '),
  (@ENTRY, 0, 16, 17, 1, 0, 100, 1, 179000, 179000, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - Out of Combat - Despawn In 1000ms (No Repeat)'),
  (@ENTRY, 0, 17, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 30, 30, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Mogor - Out of Combat - Set Data 30 30 ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s goes into a frenzy!", 16, 0, 100, 0, 0, "Mogor"),
  (@ENTRY, 1, 0, "Dat was poop! Mogor could put up much better fight den dat!", 14, 0, 100, 0, 0, "Mogor"),
  (@ENTRY, 2, 0, "Mogor not impressed! Skra'gath wuz made of da air and shadow! Soft like da squishy orcies!", 14, 0, 100, 0, 0, "Mogor"),
  (@ENTRY, 3, 0, "Now you face da true champion! I give you chance to run away little one. Run away now before Mogor decim... destyor... Run away before Mogor KILL!", 14, 0, 100, 0, 0, "Mogor"),
  (@ENTRY, 4, 0, "No more chances! Now you pay da ogre!", 14, 0, 100, 15, 0, "Mogor"),
  (@ENTRY, 5, 0, "No more nice ogre! You hurt Mogor!", 14, 0, 100, 0, 0, "Mogor"),
  (@ENTRY, 6, 0, "WUT!? UNPOSSIBLE!! You fight Mogor now! Mogor destroy!", 14, 0, 100, 0, 0, "Mogor");
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Set Orientation 0 '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Say Line 4 '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 2, 14, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Set Faction 14 '),
  (@ENTRY*100+1, 9, 103, 0, 0, 0, 100, 0, 500, 500, 0, 0, 49, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Start Attacking '),
  (@ENTRY*100+1, 9, 104, 0, 0, 0, 100, 0, 0, 0, 0, 0, 42, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Set Invincibility At 1 HP ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+2 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+2, 9, 200, 0, 0, 0, 100, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Set React State Passive '),
  (@ENTRY*100+2, 9, 201, 0, 0, 0, 100, 0, 0, 0, 0, 0, 90, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Set Flag Dead '),
  (@ENTRY*100+2, 9, 202, 0, 0, 0, 100, 0, 0, 0, 0, 0, 18, 33685766, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Set Unit Flag Non Attackable, Disable Move, Immune to PC, Pacified and  Not Selectable '),
  (@ENTRY*100+2, 9, 203, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 17683, 66, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Cast "<a href="http://wowhead.com/spell=17683">Full Heal</a>" '),
  (@ENTRY*100+2, 9, 204, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 11, 24171, 66, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Cast "<a href="http://wowhead.com/spell=24171">Resurrection Impact Visual</a>" '),
  (@ENTRY*100+2, 9, 205, 0, 0, 0, 100, 0, 0, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Error '),
  (@ENTRY*100+2, 9, 206, 0, 0, 0, 100, 0, 0, 0, 0, 0, 91, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Set Flag Dead '),
  (@ENTRY*100+2, 9, 207, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 19, 33685766, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Set Unit Flag Non Attackable, Disable Move, Immune to PC, Pacified and  Not Selectable '),
  (@ENTRY*100+2, 9, 208, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 28747, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Cast "<a href="http://wowhead.com/spell=28747">Enrage</a>" '),
  (@ENTRY*100+2, 9, 209, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Start Attacking '),
  (@ENTRY*100+2, 9, 210, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Mogor - In Combat - Say Line 5 ');

# SmartAIMgr: Creature 19055 Event 0 Action 53 uses non-existent or empty WaypointPath id 19055, skipped. -- Thanks to TrinityCore
DELETE FROM waypoints WHERE entry = 19055;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (19055,	1,	-2422.51,	6910.64,	20.1247,	'Windroc Matriarch WP 1'),
  (19055,	2,	-2420.72,	6901.21,	15.2252,	'Windroc Matriarch WP 2'),
  (19055,	3,	-2400.64,	6887.52,	-1.38425,	'Windroc Matriarch WP 3');

# SmartAIMgr: Entry 19273 SourceType 0 Event 0 Action 15 SpecialFlags for Quest entry 10162 does not include FLAGS_EXPLORATION_OR_EVENT(2), skipped.
-- NPC 19273
SET @ENTRY = 19273;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 19, 0, 100, 0, 10129, 0, 0, 0, 80, 1927301, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Forward Commander To&#039;arch - On Quest "<a href="http://wowhead.com/quest=10129">Mission: Gateways Murketh and Shaadraz</a>" Accepted - Run Script <a href="/smartai/script/1927301">1927301</a> ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 4.3897, 'Forward Commander To&#039;arch - In Combat - Set Orientation 4.3897 '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 500, 500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Forward Commander To&#039;arch - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'Forward Commander To&#039;arch - In Combat - Set Orientation 0 ');

DELETE FROM gossip_text WHERE ID = 19401;
INSERT INTO gossip_text (ID, comment, text0_0, text0_1, BroadcastTextID0, lang0, prob0, em0_0, em0_1, em0_2, em0_3, em0_4, em0_5, text1_0, text1_1, BroadcastTextID1, lang1, prob1, em1_0, em1_1, em1_2, em1_3, em1_4, em1_5, text2_0, text2_1, BroadcastTextID2, lang2, prob2, em2_0, em2_1, em2_2, em2_3, em2_4, em2_5, text3_0, text3_1, BroadcastTextID3, lang3, prob3, em3_0, em3_1, em3_2, em3_3, em3_4, em3_5, text4_0, text4_1, BroadcastTextID4, lang4, prob4, em4_0, em4_1, em4_2, em4_3, em4_4, em4_5, text5_0, text5_1, BroadcastTextID5, lang5, prob5, em5_0, em5_1, em5_2, em5_3, em5_4, em5_5, text6_0, text6_1, BroadcastTextID6, lang6, prob6, em6_0, em6_1, em6_2, em6_3, em6_4, em6_5, text7_0, text7_1, BroadcastTextID7, lang7, prob7, em7_0, em7_1, em7_2, em7_3, em7_4, em7_5) VALUES
  (19401,	'Wing Commander Brack',	'Hello, $r! Are you reporting for a flight mission?',	NULL,	0,	0,	0,	0,	0,	0,	0,	0,	0,	NULL,	NULL,	0,	0,	0,	0,	0,	0,	0,	0,	0,	NULL,	NULL,	0,	0,	0,	0,	0,	0,	0,	0,	0,	NULL,	NULL,	0,	0,	0,	0,	0,	0,	0,	0,	0,	NULL,	NULL,	0,	0,	0,	0,	0,	0,	0,	0,	0,	NULL,	NULL,	0,	0,	0,	0,	0,	0,	0,	0,	0,	NULL,	NULL,	0,	0,	0,	0,	0,	0,	0,	0,	0,	NULL,	NULL,	0,	0,	0,	0,	0,	0,	0,	0,	0);
DELETE FROM gossip_menu WHERE entry = 19401;
INSERT INTO gossip_menu (entry, text_id) VALUES
  (19401,	19401);
DELETE FROM gossip_menu_option WHERE menu_id = 19401;
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, OptionBroadcastTextID, option_id, npc_option_npcflag, action_menu_id, action_poi_id, box_coded, box_money, box_text, BoxBroadcastTextID) VALUES
  (19401,	0,	0,	'I\'m on a bombing mission for Forward Commander To\'arch. I need a wyvern destroyer!',	0,	1,	1,	NULL,	0,	0,	0,	NULL,	0),
  (19401,	1,	0,	'Send me to the Abyssal Shelf!',	0,	1,	1,	NULL,	0,	0,	0,	NULL,	0),
  (19401,	2,	0,	'Lend me a Windrider. I\'m going to Spinebreaker Post!',	0,	1,	1,	NULL,	0,	0,	0,	NULL,	0);
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 15 AND SourceGroup = 19401;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
  (15,	19401,	0,	0,	0,	9,	0,	10129,	0,	0,  0,	0,	0,	'',	'Gossip Option on Mission: Gateways Murketh and Shaadraz taken'),
  (15,	19401,	0,	0,	0,	28,	0,	10129,	0,	0,	1,	0,	0,	'',	'Gossip Option on Mission: Gateways Murketh and Shaadraz incomplete'),
  (15,	19401,	1,	0,	0,	9,	0,	10162,	0,	0,	0,	0,	0,	'',	'Gossip Option on Mission: The Abyssal Shelf taken'),
  (15,	19401,	1,	0,	0,	28,	0,	10162,	0,	0,	1,	0,	0,	'',	'Gossip Option on Mission: The Abyssal Shelf incomplete'),
  (15,	19401,	1,	0,	1,	9,	0,	10347,	0,	0,	0,	0,	0,	'',	'Gossip Option on Return to The Abyssal Shelf incomplete'),
  (15,	19401,	1,	0,	1,	28,	0,	10347,	0,	0,	1,	0,	0,	'',	'Gossip Option on Return to The Abyssal Shelf incomplete'),
  (15,	19401,	2,	0,	0,	9,	0,	10242,	0,	0,	0,	0,	0,	'',	'Gossip Option on Spinebreaker Post complete'),
  (15,	19401,	2,	0,	0,	28,	0,	10242,	0,	0,	0,	0,	0,	'',	'Gossip Option on Spinebreaker Post complete');
-- NPC 19401
SET @ENTRY = 19401;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', gossip_menu_id = 19401 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 62, 0, 100, 0, 19401, 0, 0, 0, 11, 33659, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Wing Commander Brack - On Gossip 19401 Option 0 Selected - Cast "<a href="http://wowhead.com/spell=33659">Gateways Murket and Shaadraz</a>" '),
  (@ENTRY, 0, 2, 0, 62, 0, 100, 0, 19401, 1, 0, 0, 11, 33825, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Wing Commander Brack - On Gossip 19401 Option 1 Selected - Cast "<a href="http://wowhead.com/spell=33825">Aerial Assault Flight (Horde)</a>" '),
  (@ENTRY, 0, 3, 0, 62, 0, 100, 0, 19401, 2, 0, 0, 11, 34578, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Wing Commander Brack - On Gossip 19401 Option 2 Selected - Cast "<a href="http://wowhead.com/spell=34578">Taxi - Reaver"s Fall to Spinebreaker Ridge</a>" ');

# SmartAIMgr: Creature 3584 Event 1 Action 53 uses non-existent or empty WaypointPath id 3584, skipped.
DELETE FROM waypoints WHERE entry = 3584;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (3584,	1,	4520.4,	420.235,	33.5284,	'Therylune'),
  (3584,	2,	4512.26,	408.881,	32.9308,	'Therylune'),
  (3584,	3,	4507.94,	396.47,	32.9476,	'Therylune'),
  (3584,	4,	4507.53,	383.781,	32.995,	'Therylune'),
  (3584,	5,	4512.1,	374.02,	33.166,	'Therylune'),
  (3584,	6,	4519.75,	373.241,	33.1574,	'Therylune'),
  (3584,	7,	4592.41,	369.127,	31.4893,	'Therylune'),
  (3584,	8,	4598.55,	364.801,	31.4947,	'Therylune'),
  (3584,	9,	4602.76,	357.649,	32.9265,	'Therylune'),
  (3584,	10,	4597.88,	352.629,	34.0317,	'Therylune'),
  (3584,	11,	4590.23,	350.9,	36.2977,	'Therylune'),
  (3584,	12,	4581.5,	348.254,	38.3878,	'Therylune'),
  (3584,	13,	4572.05,	348.059,	42.3539,	'Therylune'),
  (3584,	14,	4564.75,	344.041,	44.2463,	'Therylune'),
  (3584,	15,	4556.63,	341.003,	47.6755,	'Therylune'),
  (3584,	16,	4554.38,	334.968,	48.8003,	'Therylune'),
  (3584,	17,	4557.63,	329.783,	49.9532,	'Therylune'),
  (3584,	18,	4563.32,	316.829,	53.2409,	'Therylune'),
  (3584,	19,	4566.09,	303.127,	55.0396,	'Therylune'),
  (3584,	20,	4561.65,	295.456,	57.0984,	'Therylune'),
  (3584,	21,	4551.03,	293.333,	57.1534,	'Therylune');

# SmartAIMgr: Creature 18146 Event 0 Action 53 uses non-existent or empty WaypointPath id 18146, skipped.
DELETE FROM waypoints WHERE entry = 18146;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (18146,	1,	9834.04,	-7480.85,	14.9347,	'Champion Vranesh'),
  (18146,	2,	9829.11,	-7493.61,	14.9365,	'Champion Vranesh'),
  (18146,	3,	9826.17,	-7516.15,	19.7371,	'Champion Vranesh'),
  (18146,	4,	9841.33,	-7518.85,	19.7055,	'Champion Vranesh'),
  (18146,	5,	9845.06,	-7512.88,	19.681,	'Champion Vranesh'),
  (18146,	6,	9850.94,	-7512.47,	19.7155,	'Champion Vranesh'),
  (18146,	7,	9850.93,	-7513.6,	19.7181,	'Champion Vranesh'),
  (18146,	8,	9872.73,	-7517.26,	19.7528,	'Champion Vranesh'),
  (18146,	9,	9872.42,	-7489.98,	14.9127,	'Champion Vranesh'),
  (18146,	10,	9851.4,	-7490.21,	14.9346,	'Champion Vranesh'),
  (18146,	11,	9850.95,	-7470.1,	14.914,	'Champion Vranesh'),
  (18146,	12,	9851.16,	-7469.15,	14.9132,	'Champion Vranesh'),
  (18146,	13,	9849.69,	-7442.58,	13.5093,	'Champion Vranesh'),
  (18146,	14,	9848.73,	-7423.56,	13.3195,	'Champion Vranesh'),
  (18146,	15,	9816.58,	-7423.82,	13.3033,	'Champion Vranesh'),
  (18146,	16,	9794.67,	-7424.88,	13.5099,	'Champion Vranesh'),
  (18146,	17,	9794.48,	-7442.29,	14.4023,	'Champion Vranesh'),
  (18146,	18,	9767.99,	-7442.61,	14.3926,	'Champion Vranesh'),
  (18146,	19,	9767.41,	-7422.98,	13.3585,	'Champion Vranesh'),
  (18146,	20,	9739.56,	-7422.83,	13.2888,	'Champion Vranesh'),
  (18146,	21,	9736.46,	-7440.87,	13.5396,	'Champion Vranesh'),
  (18146,	22,	9740.34,	-7464.68,	13.5748,	'Champion Vranesh'),
  (18146,	23,	9746.74,	-7482.59,	13.5574,	'Champion Vranesh'),
  (18146,	24,	9748.77,	-7486.58,	13.5498,	'Champion Vranesh'),
  (18146,	25,	9753.25,	-7486.52,	13.5461,	'Champion Vranesh'),
  (18146,	26,	9720.04,	-7486.48,	13.5287,	'Champion Vranesh'),
  (18146,	27,	9681.5,	-7475.87,	13.5278,	'Champion Vranesh'),
  (18146,	28,	9666.59,	-7479.55,	13.5378,	'Champion Vranesh'),
  (18146,	29,	9638.03,	-7492.63,	13.5089,	'Champion Vranesh'),
  (18146,	30,	9620.12,	-7488.49,	13.5385,	'Champion Vranesh'),
  (18146,	31,	9605.79,	-7475.28,	13.5577,	'Champion Vranesh'),
  (18146,	32,	9597.92,	-7460.31,	13.5434,	'Champion Vranesh'),
  (18146,	33,	9594.61,	-7450.37,	13.5353,	'Champion Vranesh'),
  (18146,	34,	9592.94,	-7450.38,	13.5312,	'Champion Vranesh'),
  (18146,	35,	9594.61,	-7450.37,	13.5353,	'Champion Vranesh'),
  (18146,	36,	9615.79,	-7419.52,	13.3055,	'Champion Vranesh'),
  (18146,	37,	9654.94,	-7420.38,	13.2934,	'Champion Vranesh'),
  (18146,	38,	9673.07,	-7429.82,	13.2933,	'Champion Vranesh'),
  (18146,	39,	9689.37,	-7431.43,	13.2933,	'Champion Vranesh'),
  (18146,	40,	9709.58,	-7422.25,	13.2933,	'Champion Vranesh'),
  (18146,	41,	9722.3,	-7415.22,	13.3999,	'Champion Vranesh'),
  (18146,	42,	9748.05,	-7414.6,	13.3214,	'Champion Vranesh'),
  (18146,	43,	9766.79,	-7413.54,	13.3862,	'Champion Vranesh'),
  (18146,	44,	9767.26,	-7396.83,	14.431,	'Champion Vranesh'),
  (18146,	45,	9793.14,	-7395.39,	14.3936,	'Champion Vranesh'),
  (18146,	46,	9794.22,	-7415.12,	13.4868,	'Champion Vranesh'),
  (18146,	47,	9817.58,	-7415.3,	13.306,	'Champion Vranesh'),
  (18146,	48,	9837.02,	-7414.86,	13.3086,	'Champion Vranesh'),
  (18146,	49,	9848.05,	-7414.79,	13.3114,	'Champion Vranesh'),
  (18146,	50,	9848.2,	-7414.07,	13.3107,	'Champion Vranesh'),
  (18146,	51,	9847.7,	-7415.9,	13.3124,	'Champion Vranesh'),
  (18146,	52,	9848.26,	-7428.58,	13.3322,	'Champion Vranesh'),
  (18146,	53,	9846.75,	-7446.96,	13.565,	'Champion Vranesh'),
  (18146,	54,	9850.37,	-7465.03,	14.9097,	'Champion Vranesh'),
  (18146,	55,	9850.84,	-7480.41,	14.9377,	'Champion Vranesh'),
  (18146,	56,	9840.17,	-7480.27,	14.9292,	'Champion Vranesh'),
  (18146,	57,	9843.28,	-7480.13,	14.9265,	'Champion Vranesh');

# SmartAIMgr: Creature 21117 Event 1 Action 53 uses non-existent or empty WaypointPath id 21117, skipped.
DELETE FROM waypoints WHERE entry = 21117;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (21117,	1,	2319.76,	6007.02,	142.701,	'Gor\'drek WP 1'),
  (21117,	2,	2325.91,	6010.9,	142.576,	'Gor\'drek WP 2'),
  (21117,	3,	2319.76,	6007.02,	142.701,	'Gor\'drek WP 3'),
  (21117,	4,	2313.01,	6004.88,	142.826,	'Gor\'drek WP 4');

# SmartAIMgr: Creature 21291 Event 0 Action 53 uses non-existent or empty WaypointPath id 21291, skipped.
DELETE FROM waypoints WHERE entry = 21291;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (21291,	1,	-2817.19,	1777.81,	60.3517,	'Grom\'tor, Son of Oronok'),
  (21291,	2,	-2815.42,	1771.03,	59.1017,	'Grom\'tor, Son of Oronok');

# SmartAIMgr: Creature 23995 Event 0 Action 53 uses non-existent or empty WaypointPath id 23995, skipped.
DELETE FROM waypoints WHERE entry = 23995;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (23995,	1,	-4627.79,	-3176.21,	41.4062,	'Axle'),
  (23995,	2,	-4617.29,	-3178.56,	34.9508,	'Axle'),
  (23995,	3,	-4615.73,	-3176.38,	34.8111,	'Axle'),
  (23995,	4,	-4618,	-3175.21,	34.8124,	'Axle'),
  (23995,	5,	-4615.73,	-3176.38,	34.8111,	'Axle'),
  (23995,	6,	-4617.29,	-3178.56,	34.9508,	'Axle'),
  (23995,	7,	-4627.79,	-3176.21,	41.4062,	'Axle'),
  (23995,	8,	-4629.94,	-3176.12,	41.2235,	'Axle');

# SmartAIMgr: Creature 225 Event 0 Action 53 uses non-existent or empty WaypointPath id 225, skipped.
DELETE FROM waypoints WHERE entry = 225;
INSERT INTO waypoints (entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (225,	1,	-10616.7,	-1150.73,	28.0361,	'Gavin Gnarltree'),
  (225,	2,	-10609.4,	-1154.94,	28.2175,	'Gavin Gnarltree'),
  (225,	3,	-10605.3,	-1157.31,	30.007,	  'Gavin Gnarltree'),
  (225,	4,	-10600.3,	-1159.58,	30.0602,	'Gavin Gnarltree'),
  (225,	5,	-10596.1,	-1156.43,	30.0602,	'Gavin Gnarltree'),
  (225,	6,	-10596.9,	-1154.15,	30.0597,	'Gavin Gnarltree'),
  (225,	7,	-10601.7,	-1159.03,	30.0602,	'Gavin Gnarltree'),
  (225,	8,	-10606,	  -1156.86,	29.9963,	'Gavin Gnarltree'),
  (225,	9,	-10609.6,	-1155.18,	28.2269,	'Gavin Gnarltree'),
  (225,	10,	-10617.3,	-1153.9,	27.1127,	'Gavin Gnarltree');

# Conditions
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 34387;
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 35936;
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 36460 AND ConditionValue1 = 5;

# SourceEntry 36904 SourceGroup 1 in `condition` table - spell 36904 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 36904;
DELETE FROM event_scripts WHERE id = 12890;
-- NPC 21468
SET @ENTRY = 21468;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 29, 3, 120, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 'Kaliri Totem - On Just Summoned - Follow Target ');
-- NPC 21469
SET @ENTRY = 21469;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 5, 6, 38, 0, 100, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Daranelle - On Data Set 0 1 - Say Line 0 '),
  (@ENTRY, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 11, 37028, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Daranelle - On Data Set 0 1 - Cast "<a href="http://wowhead.com/spell=37028">Dispelling Analysis</a>" '),
  (@ENTRY, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 28, 36904, 1, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Daranelle - On Data Set 0 1 - Remove Aura "<a href="http://wowhead.com/spell=36904">Lashh"an Channeling</a>" '),
  (@ENTRY, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 500, 0, 0, 0, 0, 0, 19, 0, 21468, 30, 0, 0, 0, 0, 0, 'Daranelle - On Data Set 0 1 - Despawn In 500ms ');

# SourceEntry 38055 SourceGroup 1 in `condition` table - spell 38055 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 38055;

# SourceEntry 42287 SourceGroup 1 in `condition` table - spell 42287 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 42287;

# SourceEntry 45149 SourceGroup 1 in `condition` table - spell 45149 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 45149;
UPDATE conditions SET SourceGroup = 2, ConditionValue1 = 3 AND ConditionValue2 = 25114 WHERE SourceTypeOrReferenceId = 13 AND SourceGroup = 1 AND SourceEntry = 45149;
DELETE FROM creature WHERE guid = 311410;
INSERT INTO creature (guid, id, map, spawnMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, MovementType, pool_id, ScriptName) VALUES
  (311410,	25114,	530,	1,	0,	0,	12664.5,	-6986.2,	15.6019,	1.51368,	25,	0,	0,	1,	0,	0,	0,	'');
DELETE FROM game_event_creature WHERE guid = 311410 AND event = 44;
INSERT INTO game_event_creature (guid, event) VALUES
  (311410,	44);
-- NPC 25114
SET @ENTRY = 25114;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 0, 45149, 0, 0, 500, 11, 20694, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hauthaa&#039;s Anvil Bunny - On Spellhit "<a href="http://wowhead.com/spell=45149">Cleanse Ata"mal Armament</a>" - Cast "<a href="http://wowhead.com/spell=20694">Holy Nova</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hauthaa&#039;s Anvil Bunny - On Spellhit "<a href="http://wowhead.com/spell=45149">Cleanse Ata"mal Armament</a>" - Increase Phase By 1 '),
  (@ENTRY, 0, 2, 3, 103, 16, 100, 0, 5, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, 0, 92571, 25046, 0, 0, 0, 0, 0, 'Hauthaa&#039;s Anvil Bunny - On Enter Phase 5 - Set Data 1 1 (Phase 5)'),
  (@ENTRY, 0, 3, 0, 61, 16, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hauthaa&#039;s Anvil Bunny - On Enter Phase 5 - Set Event Phase 0 (Phase 5)');
-- NPC 25046
SET @ENTRY = 25046;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 500, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Smith Hauthaa - On Data Set 1 1 - Say Line 0 ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Along with the naga's ore, the cleansed metal that you provide will form a nigh-invulnerable alloy.", 12, 0, 100, 0, 0, "Smith Hauthaa - ");








