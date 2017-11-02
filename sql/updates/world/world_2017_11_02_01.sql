# Daily Quest 11926 not marked as repeatable in `SpecialFlags`, added.
UPDATE quest_template SET SpecialFlags = 1 WHERE entry = 11926;

# Table `quest_template` has non-existing Emote (5000) set for quest 862. Skipped.
# Table `quest_template` has non-existing Emote (1000) set for quest 997. Skipped.
UPDATE quest_template SET DetailsEmote3 = 0 WHERE entry IN (862,997);

# Table `quest_template` has non-existing Emote (2000) set for quest 1106. Skipped.
UPDATE quest_template SET DetailsEmote2 = 0 WHERE entry = 1106;

# Daily Quest 5727 not marked as repeatable in `SpecialFlags`, added.
UPDATE quest_template SET SpecialFlags = 1 WHERE entry = 5727;

# Quest 10637 has `RequiredSourceItemId1` = 0 but `ReqSourceRef1` = 1.
# Quest 10637 has `ReqSourceRef1` = 1 but `RequiredItemId1` = 0 and `ReqSpellCast1` = 0, quest can't be done.
UPDATE quest_template SET ReqSourceId1 = 30811, ReqSourceCount1 = 1, ReqSpellCast1 = 37834, ReqSourceRef1 = 1 WHERE entry = 10637;
-- NPC 21503 - Sunfury Warlock
SET @ENTRY = 21503;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 25, 0, 100, 0, 0, 1, 60000, 60000, 11, 38722, 0, 0, 0, 0, 0, 10, 0, 74581, 21506, 0, 0, 0, 0, 0, 'Sunfury Warlock - On Reset - Cast "<a href="http://wowhead.com/spell=38722">Spellbind Azaloth</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 0, 0, 6000, 8000, 11, 32707, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunfury Warlock - In Combat - Cast "<a href="http://wowhead.com/spell=32707">Incinerate</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 2500, 2750, 6000, 8000, 11, 9613, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunfury Warlock - In Combat - Cast "<a href="http://wowhead.com/spell=9613">Shadow Bolt</a>" '),
  (@ENTRY, 0, 4, 0, 25, 0, 100, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunfury Warlock - On Reset - Set React State Passive '),
  (@ENTRY, 0, 5, 6, 38, 0, 100, 0, 1, 1, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunfury Warlock - On Data Set 1 1 - Set React State Passive '),
  (@ENTRY, 0, 6, 0, 61, 0, 100, 0, 1, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 10, 0, 74581, 21506, 0, 0, 0, 0, 0, 'Sunfury Warlock - On Data Set 1 1 - Start Attacking ');
-- NPC 21506 - Azaloth
SET @ENTRY = 21506;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', unit_flags = 2147655748 WHERE entry = @ENTRY;
DELETE FROM creature_template_addon WHERE entry = @ENTRY;
INSERT INTO creature_template_addon (entry, path_id, mount, bytes0, bytes1, bytes2, emote, moveflags, auras) VALUES
  (@ENTRY,	0,	0,	512,	0,	4097,	0,	0,	'37833');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, 5000, 10000, 15000, 11, 11443, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Cast "<a href="http://wowhead.com/spell=11443">Cripple</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 10000, 15000, 11, 38741, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Cast "<a href="http://wowhead.com/spell=38741">Rain of Fire</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 0, 5000, 5000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Cast "<a href="http://wowhead.com/spell=40504">Cleave</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 0, 5000, 5000, 10000, 11, 38750, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Cast "<a href="http://wowhead.com/spell=38750">War Stomp</a>" '),
  (@ENTRY, 0, 6, 7, 11, 0, 100, 0, 0, 0, 0, 0, 75, 37833, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - On Respawn - Add Aura "<a href="http://wowhead.com/spell=37833">Banish</a>" '),
  (@ENTRY, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - On Respawn - Set React State Passive '),
  (@ENTRY, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 18, 139268, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - On Respawn - Set Unit Flag Disable Move, Silenced and  Pacified '),
  (@ENTRY, 0, 10, 0, 38, 0, 100, 1, 1, 1, 0, 0, 80, 2150601, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - On Data Set 1 1 - Run Script <a href="/smartai/script/2150601">2150601</a> (No Repeat)'),
  (@ENTRY, 0, 11, 0, 7, 1, 100, 1, 0, 0, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - On Evade - Despawn In 10000ms (No Repeat)(Phase 1)');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Illidan's lapdogs! You will pay for my imprisonment with your lives!", 14, 0, 100, 0, 0, "Azaloth - Aggro");
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY*100+1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY*100+1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 28, 37833, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Remove Aura "<a href="http://wowhead.com/spell=37833">Banish</a>" '),
  (@ENTRY*100+1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Say Line 0 '),
  (@ENTRY*100+1, 9, 102, 0, 0, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Set React State Passive '),
  (@ENTRY*100+1, 9, 103, 0, 0, 0, 100, 0, 0, 0, 0, 0, 19, 139268, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Set Unit Flag Disable Move, Silenced and  Pacified '),
  (@ENTRY*100+1, 9, 104, 0, 0, 0, 100, 0, 0, 0, 0, 0, 2, 14, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth - In Combat - Set Faction 14 '),
  (@ENTRY*100+1, 9, 105, 0, 0, 0, 100, 0, 100, 100, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 50, 0, 0, 0, 0, 'Azaloth - In Combat - Start Attacking '),
  (@ENTRY*100+1, 9, 106, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 0, 21503, 0, 30, 0, 0, 0, 0, 'Azaloth - In Combat - Set Data 1 1 ');
-- NPC 21892 - Azaloth Credit Marker
SET @ENTRY = 21892;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', unit_flags = 33554946 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 0, 37834, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, 0, 74581, 21506, 0, 0, 0, 0, 0, 'Azaloth Credit Marker - On Spellhit "<a href="http://wowhead.com/spell=37834">Unbanish Azaloth</a>" - Set Data 1 1 '),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 33, 21892, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Azaloth Credit Marker - On Spellhit "<a href="http://wowhead.com/spell=37834">Unbanish Azaloth</a>" - Quest Credit "<a href="http://wowhead.com/quest=21892">Azaloth Credit Marker</a>" '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 10, 0, 74581, 21506, 0, 0, 0, 0, 0, 'Azaloth Credit Marker - On Spellhit "<a href="http://wowhead.com/spell=37834">Unbanish Azaloth</a>" - Set Event Phase 1 ');


# Quest 9948 has `ReqSourceRef1` = 1 but `RequiredItemId1` = 0 and `ReqSpellCast1` = 0, quest can't be done.
UPDATE quest_template SET ReqSpellCast1 = 32347 WHERE entry = 9948;
-- NPC 18428
SET @ENTRY = 18428;
UPDATE creature_template SET AIName='SmartAI', ScriptName='', faction = 1652 WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Prisoner - On Data Set 1 1 - Say Line 0 '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Prisoner - On Data Set 1 1 - Despawn In 10000ms '),
  (@ENTRY, 0, 2, 0, 60, 0, 100, 0, 0, 90000, 15000, 90000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Mag&#039;har Prisoner - On Update - Say Line 1 ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Many thanks, hero!", 12, 1, 100, 0, 0, "Mag&#039;har Prisoner - "),
  (@ENTRY, 0, 1, "Spirits watch over you, $r!", 12, 1, 100, 0, 0, "Mag&#039;har Prisoner - "),
  (@ENTRY, 0, 2, "Thank you, $r! Your service to the Mag'har will not be forgotten.", 12, 1, 100, 0, 0, "Mag&#039;har Prisoner - "),
  (@ENTRY, 1, 0, "Help! Help! They're going to eat me!", 12, 1, 100, 0, 0, "Mag&#039;har Prisoner - "),
  (@ENTRY, 1, 1, "My children will be made orphans!", 12, 1, 100, 0, 0, "Mag&#039;har Prisoner - "),
  (@ENTRY, 1, 2, "The ogres have the keys! Kill the ogres and get me out of here!", 12, 1, 100, 0, 0, "Mag&#039;har Prisoner - "),
  (@ENTRY, 1, 3, "Death to the ogres!", 12, 1, 100, 0, 0, "Mag&#039;har Prisoner - "),
  (@ENTRY, 1, 4, "I'm done for!", 12, 1, 100, 0, 0, "Mag&#039;har Prisoner - ");
-- GO Warmaul Prison
UPDATE gameobject_template SET AIName='SmartGameObjectAI', ScriptName='', data2 = 1048576 WHERE entry IN (182484,182486,182487,182488,182489,182490,182491,182492,182493,182494,182495,182496,182497,182498,182499,182500,182501,182502,182503,182504);
UPDATE gameobject SET spawntimesecs = 300 WHERE id IN (182484,182486,182487,182488,182489,182490,182491,182492,182493,182494,182495,182496,182497,182498,182499,182500,182501,182502,182503,182504);
DELETE FROM smart_scripts WHERE entryorguid IN (182484,182486,182487,182488,182489,182490,182491,182492,182493,182494,182495,182496,182497,182498,182499,182500,182501,182502,182503,182504) AND source_type = 1;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (182484, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182486, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182487, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182488, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182489, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182490, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182491, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182492, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182493, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182494, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182495, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182496, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182497, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182498, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182499, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182500, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182501, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182502, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182503, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),
  (182504, 1, 0, 1, 70, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Store Targetlist 1 '),

  (182484, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182486, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182487, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182488, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182489, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182490, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182491, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182492, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182493, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182494, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182495, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182496, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182497, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182498, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182499, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182500, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182501, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182502, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182503, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),
  (182504, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Send Target 1 '),

  (182484, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182486, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182487, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182488, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182489, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182490, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182491, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182492, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182493, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182494, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182495, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182496, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182497, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182498, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182499, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182500, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182501, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182502, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182503, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 '),
  (182504, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 0, 18428, 5, 0, 0, 0, 0, 0, 'Warmaul Prison - On GO State Changed - Set Data 1 1 ');

# Table `quest_template` has non-existing Emote (1000) set for quest 9702. Skipped.
# Table `quest_template` has non-existing Emote (1000) set for quest 9702. Skipped.
UPDATE quest_template SET DetailsEmote3 = 0, DetailsEmote4 = 0 WHERE entry = 9702;

# Spell (id: 34142) have SPELL_EFFECT_QUEST_COMPLETE or SPELL_EFFECT_SEND_EVENT for quest 10306 and RequiredNpcOrGo1 = 0, but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags or RequiredNpcOrGo1 must be fixed, quest modified to enable objective.
UPDATE quest_template SET ReqCreatureOrGOId1 = 19548, ReqCreatureOrGOId2 = 0, ReqCreatureOrGOCount1 = 1 , ReqCreatureOrGOCount2 = 0, ReqSpellCast1 = 0, SpecialFlags = 0 WHERE entry = 10306;
SET @ENTRY = 1954400;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 9, 8, 0, 0, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Conjurer Luminrath - In Combat - Set Run Off '),
  (@ENTRY, 9, 9, 0, 0, 0, 100, 0, 0, 0, 0, 0, 33, 19548, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Conjurer Luminrath - In Combat - Quest Credit "<a href="http://wowhead.com/quest=19548">Invis Dresser</a>" '),
  (@ENTRY, 9, 10, 0, 0, 0, 100, 0, 0, 0, 0, 0, 2, 35, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Conjurer Luminrath - In Combat - Set Faction 35 '),
  (@ENTRY, 9, 11, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 2193.52, 2339.14, 90.026, 4.02078, 'Conjurer Luminrath - In Combat - Move To Pos '),
  (@ENTRY, 9, 13, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Conjurer Luminrath - In Combat - Say Line 0 '),
  (@ENTRY, 9, 14, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 3, 19580, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Conjurer Luminrath - In Combat - Morph To "19580" '),
  (@ENTRY, 9, 15, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Conjurer Luminrath - In Combat - Say Line 1 ');

# Table `quest_template` has non-existing Emote (1000) set for quest 9855. Skipped.
UPDATE quest_template SET DetailsEmote3 = 0 WHERE entry = 9855;

# Spell (id: 34141) have SPELL_EFFECT_QUEST_COMPLETE or SPELL_EFFECT_SEND_EVENT for quest 10182 and RequiredNpcOrGo1 = 0, but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags or RequiredNpcOrGo1 must be fixed, quest modified to enable objective.
UPDATE quest_template SET ReqCreatureOrGOId1 = 19549, ReqCreatureOrGOId2 = 0, ReqCreatureOrGOCount1 = 1 , ReqCreatureOrGOCount2 = 0 WHERE entry = 10182;

# Spell (id: 44969) have SPELL_EFFECT_QUEST_COMPLETE or SPELL_EFFECT_SEND_EVENT for quest 11523 and RequiredNpcOrGo1 = 0, but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags or RequiredNpcOrGo1 must be fixed, quest modified to enable objective.
UPDATE quest_template SET ReqSpellCast1 = 44981, ReqSourceRef1 = 1, SpecialFlags = 3 WHERE entry = 11523; #44969 previously
UPDATE item_template SET spellid_1 = 44981 WHERE entry = 34338; #44969 previously
-- NPC 24980
SET @ENTRY = 24980;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 0, 44981, 0, 0, 500, 11, 35426, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Crystal Ward - On Spellhit "<a href="http://wowhead.com/spell=44981">Activate Crystal Ward</a>" - Cast "<a href="http://wowhead.com/spell=35426">Arcane Explosion Visual</a>" '),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Crystal Ward - On Spellhit "<a href="http://wowhead.com/spell=44981">Activate Crystal Ward</a>" - Say Line 0 '),
  (@ENTRY, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 15, 11523, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Crystal Ward - On Spellhit "<a href="http://wowhead.com/spell=44981">Activate Crystal Ward</a>" - Quest Credit ""<a href="http://wowhead.com/quest=11523">Arm the Wards!</a>" '),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 15, 11496, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Crystal Ward - On Spellhit "<a href="http://wowhead.com/spell=44981">Activate Crystal Ward</a>" - Quest Credit ""<a href="http://wowhead.com/quest=11496">The Sanctum Wards</a>" ');
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "The Crystal Ward becomes energized with arcane power.", 16, 0, 100, 0, 0, "Crystal Ward - ");

# Daily Quest 11921 not marked as repeatable in `SpecialFlags`, added.
UPDATE quest_template SET SpecialFlags = 1 WHERE entry = 11921;

# Spell (id: 44969) have SPELL_EFFECT_QUEST_COMPLETE or SPELL_EFFECT_SEND_EVENT for quest 11496 and RequiredNpcOrGo1 = 0, but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags or RequiredNpcOrGo1 must be fixed, quest modified to enable objective.
UPDATE quest_template SET ReqSpellCast1 = 44981, ReqSourceRef1 = 1, SpecialFlags = 3 WHERE entry = 11496; #44969 previously

# Spell (id: 25201) have SPELL_EFFECT_QUEST_COMPLETE for quest 8305 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 40311) have SPELL_EFFECT_QUEST_COMPLETE for quest 11080 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 41454) have SPELL_EFFECT_QUEST_COMPLETE for quest 11097 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 42242) have SPELL_EFFECT_QUEST_COMPLETE for quest 11131 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 42242) have SPELL_EFFECT_QUEST_COMPLETE for quest 11219 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 43475) have SPELL_EFFECT_QUEST_COMPLETE for quest 11336 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 43475) have SPELL_EFFECT_QUEST_COMPLETE for quest 11340 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 43477) have SPELL_EFFECT_QUEST_COMPLETE for quest 11337 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 43477) have SPELL_EFFECT_QUEST_COMPLETE for quest 11341 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 43483) have SPELL_EFFECT_QUEST_COMPLETE for quest 11338 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 43483) have SPELL_EFFECT_QUEST_COMPLETE for quest 11342 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 43484) have SPELL_EFFECT_QUEST_COMPLETE for quest 11335 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 43484) have SPELL_EFFECT_QUEST_COMPLETE for quest 11339 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 44947) have SPELL_EFFECT_QUEST_COMPLETE for quest 11516 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 45719) have SPELL_EFFECT_QUEST_COMPLETE for quest 11731 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 45719) have SPELL_EFFECT_QUEST_COMPLETE for quest 11921 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 46081) have SPELL_EFFECT_QUEST_COMPLETE for quest 11924 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 46654) have SPELL_EFFECT_QUEST_COMPLETE for quest 11925 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
# Spell (id: 47134) have SPELL_EFFECT_QUEST_COMPLETE for quest 11293 , but quest not have flag QUEST_TRINITY_FLAGS_EXPLORATION_OR_EVENT. Quest flags must be fixed, quest modified to enable objective.
UPDATE quest_template SET SpecialFlags = SpecialFlags | 0x2 WHERE entry IN(8305,11921,11080,11097,11131,11219,11336,11340,11337,11341,11338,11342,11335,11339,11516,11731,11921,11924,11925,11293);
UPDATE quest_template SET SpecialFlags = SpecialFlags | 0x1 WHERE entry IN(11336,11335,11080,11097,11342,11340,11131,11219,11293,11337,11338,11339,11341,11516,11924,11925);

# Table `creature_queststarter` has creature entry (18482) for quest 9979, but npcflag does not include UNIT_NPC_FLAG_QUESTGIVER
# Table `creature_queststarter` has creature entry (20159) for quest 10287, but npcflag does not include UNIT_NPC_FLAG_QUESTGIVER
# Table `creature_queststarter` has creature entry (21027) for quest 10451, but npcflag does not include UNIT_NPC_FLAG_QUESTGIVER
# Table `creature_questender` has creature entry (18482) for quest 9978, but npcflag does not include UNIT_NPC_FLAG_QUESTGIVER
# Table `creature_questender` has creature entry (19227) for quest 11195, but npcflag does not include UNIT_NPC_FLAG_QUESTGIVER
# Table `creature_questender` has creature entry (20159) for quest 10286, but npcflag does not include UNIT_NPC_FLAG_QUESTGIVER
UPDATE creature_template SET npcflag = npcflag | 0x2 WHERE entry IN (18482,20159,21027,18482,19227,20159);

# `game_event` game event id (61) isn't a world event and has length = 0, thus it can't be used.
UPDATE game_event SET world_event = 1 WHERE entry = 61;

# Table `gossip_menu_option` for menu 22829, id 0 has non-existing or incompatible OptionBroadcastTextId 22086, ignoring.
DELETE FROM broadcast_text WHERE ID = 22086;
INSERT INTO broadcast_text (ID, Language, MaleText, FemaleText, EmoteID0, EmoteID1, EmoteID2, EmoteDelay0, EmoteDelay1, EmoteDelay2, SoundId, Unk1, Unk2, VerifiedBuild) VALUES
  (22086,	0,	'Where is the zeppelin now?',	'Where is the zeppelin now?',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019);

# Table `(game_event_)npc_vendor` have data for not creature template (Entry: 303) without vendor flag, ignore
DELETE FROM npc_vendor WHERE entry = 303;

# SourceEntry 35997 SourceGroup 1 in `condition` table - spell 35997 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 35997 SourceGroup 1 in `condition` table - spell 35997 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
DELETE FROM conditions WHERE SourceEntry = 35997;

# [Condition SourceType: 10 (Reference Loot), SourceGroup: 30281, SourceEntry: 20000] Not handled grouped condition.
DELETE FROM conditions WHERE SourceEntry = 20000;
DELETE FROM conditions WHERE SourceGroup = 34052;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
  (10,	34052,	30280,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30281,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30282,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30283,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30301,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30302,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30303,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30304,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30305,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30306,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30307,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30308,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30321,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30322,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30323,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1'),
  (10,	34052,	30324,	0,	0,	12,	0,	65,	0,	0,	0,	0,	0,	'',	'Patterns drop in TK/SSC after 2.1');

# [Condition SourceType: 13 (Spell Impl. Target), SourceGroup: 1, SourceEntry: 22454] in `condition` table, SourceEntry does not exist in `spell.dbc`, ignoring.
DELETE FROM conditions WHERE SourceEntry = 22454;

# [Condition SourceType: 17 (Spell Expl. Target), SourceEntry: 37390, ConditionType: 35 (Distance)] has invalid ConditionValue1(ConditionTarget selection) (21760), skipped.
# [Condition SourceType: 17 (Spell Expl. Target), SourceEntry: 37390, ConditionType: 35 (Distance)] has invalid ConditionValue1(ConditionTarget selection) (21760), skipped.
DELETE FROM conditions WHERE SourceEntry = 37390;

# [Condition SourceType: 13 (Spell Impl. Target), SourceGroup: 0, SourceEntry: 35372, ConditionType: 18 (Title)] has useless data in ConditionValue2 (20561)!
# [Condition SourceType: 13 (Spell Impl. Target), SourceGroup: 0, SourceEntry: 35372] in `condition` table, has incorrect SourceGroup (spell effectMask) set, ignoring.
DELETE FROM conditions WHERE SourceEntry = 35372 AND ConditionTypeOrReference = 18;
UPDATE conditions SET SourceGroup = 0 WHERE SourceEntry = 35372;

# SourceEntry 13489 SourceGroup 1 in `condition` table - spell 13489 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27184 SourceGroup 1 in `condition` table - spell 27184 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27190 SourceGroup 1 in `condition` table - spell 27190 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27191 SourceGroup 1 in `condition` table - spell 27191 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27201 SourceGroup 1 in `condition` table - spell 27201 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27202 SourceGroup 1 in `condition` table - spell 27202 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27203 SourceGroup 1 in `condition` table - spell 27203 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27203 SourceGroup 1 in `condition` table - spell 27203 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27203 SourceGroup 1 in `condition` table - spell 27203 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27203 SourceGroup 1 in `condition` table - spell 27203 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27203 SourceGroup 1 in `condition` table - spell 27203 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 27517 SourceGroup 1 in `condition` table - spell 27517 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 29364 SourceGroup 1 in `condition` table - spell 29364 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 30009 SourceGroup 1 in `condition` table - spell 30009 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 31538 SourceGroup 1 in `condition` table - spell 31538 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 32205 SourceGroup 1 in `condition` table - spell 32205 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 32205 SourceGroup 1 in `condition` table - spell 32205 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 32205 SourceGroup 1 in `condition` table - spell 32205 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 34395 SourceGroup 1 in `condition` table - spell 34395 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 35246 SourceGroup 1 in `condition` table - spell 35246 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 35246 SourceGroup 1 in `condition` table - spell 35246 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 35246 SourceGroup 1 in `condition` table - spell 35246 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 35683 SourceGroup 1 in `condition` table - spell 35683 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 38782 SourceGroup 1 in `condition` table - spell 38782 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 40447 SourceGroup 1 in `condition` table - spell 40447 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 40468 SourceGroup 1 in `condition` table - spell 40468 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 42323 SourceGroup 1 in `condition` table - spell 42323 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 40055 SourceGroup 1 in `condition` table - spell 40055 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 40165 SourceGroup 1 in `condition` table - spell 40165 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 40166 SourceGroup 1 in `condition` table - spell 40166 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 40167 SourceGroup 1 in `condition` table - spell 40167 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
UPDATE conditions SET SourceGroup = 2 WHERE SourceEntry IN (13489,27184,27190,27191,27201,27202,27203,27517,29364,30009,31538,32205,34395,35246,35683,38782,40447,40468,42323,40055,40165,40166,40167);

# [Condition SourceType: 13 (Spell Impl. Target), SourceGroup: 0, SourceEntry: 35372] in `condition` table, has incorrect SourceGroup (spell effectMask) set, ignoring.
# SourceEntry 35372 SourceGroup 4 in `condition` table - spell 35372 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 2, SourceGroup needs correction, ignoring.
# SourceEntry 43734 SourceGroup 1 in `condition` table - spell 43734 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
UPDATE conditions SET SourceGroup = 1 WHERE SourceEntry IN (35372,43734);

# SourceEntry 36460 SourceGroup 1 in `condition` table - spell 36460 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 44969 SourceGroup 1 in `condition` table - spell 44969 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 39246 SourceGroup 1 in `condition` table - spell 39246 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 36374 SourceGroup 1 in `condition` table - spell 36374 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 36374 SourceGroup 1 in `condition` table - spell 36374 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 36374 SourceGroup 1 in `condition` table - spell 36374 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 36374 SourceGroup 1 in `condition` table - spell 36374 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
UPDATE conditions SET SourceGroup = 4 WHERE SourceEntry IN (36460,44969,39246,36374);

# SourceEntry 30659 SourceGroup 1 in `condition` table - spell 30659 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 34141 SourceGroup 1 in `condition` table - spell 34141 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 37769 SourceGroup 1 in `condition` table - spell 37769 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 38002 SourceGroup 1 in `condition` table - spell 38002 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 38510 SourceGroup 1 in `condition` table - spell 38510 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 40851 SourceGroup 1 in `condition` table - spell 40851 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 40902 SourceGroup 1 in `condition` table - spell 40902 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 41145 SourceGroup 1 in `condition` table - spell 41145 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 41146 SourceGroup 1 in `condition` table - spell 41146 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 44885 SourceGroup 1 in `condition` table - spell 44885 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 46350 SourceGroup 1 in `condition` table - spell 46350 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
# SourceEntry 46589 SourceGroup 1 in `condition` table - spell 46589 does not have implicit targets of types: _AREA_, _CONE_, _NEARBY_ for effect 0, SourceGroup needs correction, ignoring.
DELETE FROM conditions WHERE SourceEntry IN (30659,34141,37769,38002,38510,40851,40902,41145,41146,44885,46350,46589);

# [Condition SourceType: 13 (Spell Impl. Target), SourceGroup: 1, SourceEntry: 37204] in `condition` table, has incorrect SourceGroup 1 (spell effectMask) set - effect masks are overlapping (all SourceGroup values having given bit set must be equal) - ignoring.
# [Condition SourceType: 13 (Spell Impl. Target), SourceGroup: 1, SourceEntry: 37204] Not handled grouped condition.
DELETE FROM conditions WHERE SourceEntry = 37204 AND SourceGroup = 5;
UPDATE conditions SET SourceGroup = 5 WHERE SourceEntry = 37204;

# [Condition SourceType: 10 (Reference Loot), SourceGroup: 187909, SourceEntry: 187909] Item 187909 not found in LootTemplate 187909.
# [Condition SourceType: 10 (Reference Loot), SourceGroup: 187909, SourceEntry: 187909] Not handled grouped condition.
# [Condition SourceType: 10 (Reference Loot), SourceGroup: 187909, SourceEntry: 187909] Item 187909 not found in LootTemplate 187909.
# [Condition SourceType: 10 (Reference Loot), SourceGroup: 187909, SourceEntry: 187909] Not handled grouped condition.
UPDATE conditions SET SourceEntry = 33174 WHERE SourceGroup = 187909;

#[Condition SourceType: 10 (Reference Loot), SourceGroup: 187910, SourceEntry: 187910] Item 187910 not found in LootTemplate 187910.
#[Condition SourceType: 10 (Reference Loot), SourceGroup: 187910, SourceEntry: 187910] Not handled grouped condition.
DELETE FROM conditions WHERE SourceGroup = 187910;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
  (10,	187910,	31870,	0,	0,	12,	0,	76,	0,	0,	0,	0,	0,	'',	'Reference loot Jewelcrafting only if 2.2 event active'),
  (10,	187910,	31873,	0,	0,	12,	0,	76,	0,	0,	0,	0,	0,	'',	'Reference loot Jewelcrafting only if 2.2 event active'),
  (10,	187910,	31874,	0,	0,	12,	0,	76,	0,	0,	0,	0,	0,	'',	'Reference loot Jewelcrafting only if 2.2 event active');

# [Condition SourceType: 10 (Reference Loot), SourceGroup: 187911, SourceEntry: 187911] Item 187911 not found in LootTemplate 187911.
# [Condition SourceType: 10 (Reference Loot), SourceGroup: 187911, SourceEntry: 187911] Not handled grouped condition.
# [Condition SourceType: 10 (Reference Loot), SourceGroup: 187911, SourceEntry: 187911] Item 187911 not found in LootTemplate 187911.
# [Condition SourceType: 10 (Reference Loot), SourceGroup: 187911, SourceEntry: 187911] Not handled grouped condition.
UPDATE conditions SET SourceEntry = 34491 WHERE SourceGroup = 187911;

# The spell 35480 listed in `spell_area` has a wrong area (4100) requirement.
# The spell 35481 listed in `spell_area` has a wrong area (4100) requirement.
# The spell 35482 listed in `spell_area` has a wrong area (4100) requirement.
# The spell 35483 listed in `spell_area` has a wrong area (4100) requirement.
DELETE FROM spell_area WHERE area = 4100;

# The spell 53107 listed in `spell_area` has a wrong area (4298) requirement.
DELETE FROM spell_area WHERE spell = 53107;









