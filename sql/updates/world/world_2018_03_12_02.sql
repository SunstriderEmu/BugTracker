/*
  End event of quest "Stealing Back the Mushrooms" (9709)
  Starring Watcher Leesa'oh, Buddy, Grown Mushroom and Hungry Bog Lord.
 */

-- NPC 17831
SET @ENTRY = 17831;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 20, 0, 100, 0, 9709, 0, 0, 0, 80, 1783101, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - On Quest "<a href="http://wowhead.com/quest=9709">Stealing Back the Mushrooms</a>" Rewarded - Run Script <a href="/smartai/script/1783101">1783101</a> '),
  (@ENTRY, 0, 1, 0, 40, 0, 100, 0, 8, 17831, 0, 0, 80, 1783102, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - On Waypoint 8 Reached - Run Script <a href="/smartai/script/1783102">1783102</a> '),
  (@ENTRY, 0, 2, 3, 40, 0, 100, 0, 13, 17831, 0, 0, 55, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - On Waypoint 13 Reached - Stop Waypoint '),
  (@ENTRY, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - On Waypoint 13 Reached - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0.925025, 'Watcher Leesa&#039;oh - On Waypoint 13 Reached - Set Orientation 0.925025 '),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - On Waypoint 13 Reached - Set Home Position ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY * 100 + 1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY * 100 + 1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Set NPC Flag Gossip and  Quest Giver '),
  (@ENTRY * 100 + 1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Close Gossip '),
  (@ENTRY * 100 + 1, 9, 102, 0, 0, 0, 100, 0, 1500, 1500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Say Line 0 '),
  (@ENTRY * 100 + 1, 9, 103, 0, 0, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Store Targetlist 1 '),
  (@ENTRY * 100 + 1, 9, 104, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 1, 10, 0, 62970, 17953, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Set Data 1 1 '),
  (@ENTRY * 100 + 1, 9, 106, 0, 0, 0, 100, 0, 0, 0, 0, 0, 156, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Prevent Moving Home '),
  (@ENTRY * 100 + 1, 9, 110, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 53, 0, 17831, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Start Waypoint 17831 ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY * 100 + 2 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY * 100 + 2, 9, 199, 0, 0, 0, 100, 0, 199, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Set Home Position '),
  (@ENTRY * 100 + 2, 9, 200, 0, 0, 0, 100, 0, 0, 0, 0, 0, 54, 75000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Pause Waypoint 75000ms '),
  (@ENTRY * 100 + 2, 9, 201, 0, 0, 0, 100, 0, 1500, 1500, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Say Line 1 '),
  (@ENTRY * 100 + 2, 9, 202, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 11, 32618, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Cast "<a href="http://wowhead.com/spell=32618">Cosmetic Nature Cast</a>" '),
  (@ENTRY * 100 + 2, 9, 203, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Say Line 2 '),
  (@ENTRY * 100 + 2, 9, 204, 0, 0, 0, 100, 0, 2500, 2500, 0, 0, 50, 182073, 30000, 0, 0, 0, 0, 8, 0, 0, 0, 0, -298.833, 8212.2, 21.0342, 4.32973, 'Watcher Leesa&#039;oh - In Combat - Summon GO "<a href="http://wowhead.com/object=182073">Grown Mushroom</a>" '),
  (@ENTRY * 100 + 2, 9, 205, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 17955, 8, 30000, 0, 0, 0, 8, 0, 0, 0, 0, -360.843, 8221.75, 25.0206, 6.19033, 'Watcher Leesa&#039;oh - In Combat - Summon "<a href="http://wowhead.com/npc=17955">Hungry Bog Lord</a>" '),
  (@ENTRY * 100 + 2, 9, 206, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 45, 1, 2, 0, 0, 0, 0, 10, 0, 62970, 17953, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Set Data 1 2 '),
  (@ENTRY * 100 + 2, 9, 207, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Say Line 3 '),
  (@ENTRY * 100 + 2, 9, 208, 0, 0, 0, 100, 0, 15000, 15000, 0, 0, 66, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Set Orientation 0 '),
  (@ENTRY * 100 + 2, 9, 209, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Watcher Leesa&#039;oh - In Combat - Say Line 4 ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "$N, let's go see if this plan will work. Come along, Buddy!", 12, 0, 100, 0, 0, "Watcher Leesa&#039;oh - "),
  (@ENTRY, 1, 0, "Ok, let's see about using those mushrooms you brought back to grow the bog lords a new food supply.", 12, 0, 100, 0, 0, "Watcher Leesa&#039;oh - "),
  (@ENTRY, 2, 0, "Wait and see what happens!", 12, 0, 100, 0, 0, "Watcher Leesa&#039;oh - "),
  (@ENTRY, 3, 0, "Oh Buddy, you big baby! Look, it's working. It's really working! Now all I need to do is grow more of these mushrooms here and the bog lords will likely leave the sporelings alone!", 12, 0, 100, 0, 0, "Watcher Leesa&#039;oh - "),
  (@ENTRY, 4, 0, "Oh, thank you, $N! You've made it possible to save both the sporelings from the bog lords, and the bog lords from our wrath.", 12, 0, 100, 0, 0, "Watcher Leesa&#039;oh - ");
DELETE FROM waypoints WHERE entry = @ENTRY;
INSERT INTO waypoints (id, entry, pointid, position_x, position_y, position_z, point_comment) VALUES
  (23026,	@ENTRY,	1,	-283.861,	8302.74,	19.6126,	'Watcher Leesa\'oh'),
  (23027,	@ENTRY,	2,	-278.428,	8306.06,	20.03,	'Watcher Leesa\'oh'),
  (23028,	@ENTRY,	3,	-274.598,	8304.2,	20.3432,	'Watcher Leesa\'oh'),
  (23029,	@ENTRY,	4,	-275.413,	8299.04,	19.8574,	'Watcher Leesa\'oh'),
  (23030,	@ENTRY,	5,	-279.391,	8288.47,	19.4835,	'Watcher Leesa\'oh'),
  (23031,	@ENTRY,	6,	-286.761,	8262.58,	17.6688,	'Watcher Leesa\'oh'),
  (23032,	@ENTRY,	7,	-291.895,	8249.65,	17.9023,	'Watcher Leesa\'oh'),
  (23033,	@ENTRY,	8,	-293.89,	8231.25,	21.086,	'Watcher Leesa\'oh'),
  (23034,	@ENTRY,	9,	-292.491,	8254.58,	17.743,	'Watcher Leesa\'oh'),
  (23035,	@ENTRY,	10,	-279.31,	8289.42,	19.5377,	'Watcher Leesa\'oh'),
  (23036,	@ENTRY,	11,	-275.935,	8297.89,	19.8591,	'Watcher Leesa\'oh'),
  (23037,	@ENTRY,	12,	-279.9,	8302.28,	19.8396,	'Watcher Leesa\'oh'),
  (23038,	@ENTRY,	13,	-283.861,	8302.74,	19.6126,	'Watcher Leesa\'oh');

UPDATE gameobject_template SET size = 5 WHERE entry = 182073;

-- NPC 17953
SET @ENTRY = 17953;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 29, 5, 120, 0, 0, 0, 0, 10, 0, 62859, 17831, 0, 0, 0, 0, 0, 'Buddy - On Data Set 1 1 - Follow Target '),
  (@ENTRY, 0, 1, 0, 38, 0, 100, 0, 1, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Buddy - On Data Set 1 2 - Evade ');

-- NPC 17955
SET @ENTRY = 17955;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -305.926, 8213.72, 22.2092, 6.09135, 'Hungry Bog Lord - On Just Summoned - Move To Pos '),
  (@ENTRY, 0, 1, 0, 34, 0, 100, 0, 0, 1, 0, 0, 80, 1795501, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Bog Lord - On Reached Point 1 - Run Script <a href="/smartai/script/1795501">1795501</a> ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY * 100 + 1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY * 100 + 1, 9, 100, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 5, 35, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Bog Lord - In Combat - Play Emote 35 '),
  (@ENTRY * 100 + 1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Bog Lord - In Combat - Say Line 0 '),
  (@ENTRY * 100 + 1, 9, 102, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Bog Lord - In Combat - Say Line 1 '),
  (@ENTRY * 100 + 1, 9, 103, 0, 0, 0, 100, 0, 0, 0, 0, 0, 5, 35, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Bog Lord - In Combat - Play Emote 35 '),
  (@ENTRY * 100 + 1, 9, 104, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 41, 1500, 0, 0, 0, 0, 0, 20, 0, 182073, 10, 0, 0, 0, 0, 0, 'Hungry Bog Lord - In Combat - Despawn In 1500ms '),
  (@ENTRY * 100 + 1, 9, 105, 0, 0, 0, 100, 0, 1500, 1500, 0, 0, 41, 8000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hungry Bog Lord - In Combat - Despawn In 8000ms '),
  (@ENTRY * 100 + 1, 9, 106, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 2, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, -212.703, 8203.03, 17.755, 5.83217, 'Hungry Bog Lord - In Combat - Move To Pos ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "%s takes a piece of the mushroom tree and holds it to its 'nose'. Seemingly satisfied, it eats it!", 16, 0, 100, 0, 0, "Hungry Bog Lord - "),
  (@ENTRY, 1, 0, "%s uproots the rest of the mushroom tree and makes off with it.", 16, 0, 100, 0, 0, "Hungry Bog Lord - ");
