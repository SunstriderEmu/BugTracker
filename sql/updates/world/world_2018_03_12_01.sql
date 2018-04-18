# The spell 26798 (rank 5) listed in `spell_ranks` for chain 3908 does not have a proper rank value (should be 6)!
# The spell 20219 (rank 5) listed in `spell_ranks` for chain 4036 does not have a proper rank value (should be 6)!
# The spell 27681 (rank 2) listed in `spell_ranks` for chain 14752 does not have a proper rank value (should be 3)!
DELETE from spell_ranks WHERE first_spell_id = 3908 AND spell_id IN (26797, 26798, 26801);
DELETE from spell_ranks WHERE first_spell_id = 4036 AND spell_id IN (20219, 20222);
DELETE from spell_ranks WHERE first_spell_id = 14752 AND spell_id IN (27681, 32999);

# CreatureTextMgr: Entry 6516, Group 0, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 5045.
# CreatureTextMgr: Entry 6516, Group 0, Id 1 in table `creature_text` has non-existing or incompatible BroadcastTextId 5046.
# CreatureTextMgr: Entry 6557, Group 0, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 2082.
# CreatureTextMgr: Entry 6559, Group 0, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 4838.
# CreatureTextMgr: Entry 8578, Group 0, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 4495.
# CreatureTextMgr: Entry 8581, Group 0, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 4502.
# CreatureTextMgr: Entry 8581, Group 1, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 4491.
# CreatureTextMgr: Entry 8581, Group 2, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 4492.
# CreatureTextMgr: Entry 11677, Group 0, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 10025.
# CreatureTextMgr: Entry 17225, Group 0, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 13647.
# CreatureTextMgr: Entry 17225, Group 1, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 13649.
# CreatureTextMgr: Entry 17225, Group 2, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 20023.
# CreatureTextMgr: Entry 17225, Group 3, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 13676.
# CreatureTextMgr: Entry 17225, Group 3, Id 1 in table `creature_text` has non-existing or incompatible BroadcastTextId 13677.
# CreatureTextMgr: Entry 17225, Group 4, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 24548.
# CreatureTextMgr: Entry 19392, Group 0, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 16575.
# CreatureTextMgr: Entry 19392, Group 0, Id 1 in table `creature_text` has non-existing or incompatible BroadcastTextId 16574.
# CreatureTextMgr: Entry 19392, Group 0, Id 2 in table `creature_text` has non-existing or incompatible BroadcastTextId 16573.
# CreatureTextMgr: Entry 20875, Group 0, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 17105.
# CreatureTextMgr: Entry 20875, Group 1, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 17109.
# CreatureTextMgr: Entry 20875, Group 2, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 17106.
# CreatureTextMgr: Entry 20875, Group 3, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 17110.
# CreatureTextMgr: Entry 20875, Group 4, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 17107.
# CreatureTextMgr: Entry 20875, Group 5, Id 0 in table `creature_text` has non-existing or incompatible BroadcastTextId 17108.
DELETE FROM broadcast_text WHERE ID IN (2082,4491,4492,4495,4502,4838,5045,5046,10025,13647,13649,13676,13677,16573,16574,16575,17105,17106,17107,17108,17109,17110,20023,24548);
INSERT INTO broadcast_text (ID, Language, MaleText, FemaleText, EmoteID0, EmoteID1, EmoteID2, EmoteDelay0, EmoteDelay1, EmoteDelay2, SoundId, Unk1, Unk2, VerifiedBuild) VALUES
  (2082,	0,	'%s begins to make a copy of itself!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (4491,	0,	'Mistress!! They seek to destroy your work!!',	'Mistress!! They seek to destroy your work!!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (4492,	0,	'Ha! Now your death is ensured!',	'Ha! Now your death is ensured!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (4495,	0,	'',	'You dare! Now feel my wrath!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (4502,	0,	'Who dares?! I will destroy you!',	'Who dares?! I will destroy you!',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (4838,	0,	'%s explodes into chunks of acidic slime!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (5045,	0,	'%s looks tired. He then yawns and lies down next to A-Me 01',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (5046,	0,	'%s snores loudly and cuddles up next to A-Me 01.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (10025,	0,	'Snivvle is here!  Snivvle claims the Coldtooth mine!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13647,	0,	'An ancient being awakens in the distance...',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13649,	0,	'What fools! I shall bring a quick end to your suffering!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13676,	0,	'Enough! I shall land and crush you myself!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (13677,	0,	'Insects! Let me show you my strength up close!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (16573,	7,	'INFERNAL RAIN ON THE RISE! TAKE COVER!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (16574,	7,	'INFERNALS! CLEAR THE COURTYARD!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (16575,	7,	'WE\'RE UNDER ATTACK! RUN FOR COVER!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (17105,	0,	'%s absorbs the fire energy of the attack.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (17106,	0,	'%s absorbs the frost energy of the attack.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (17107,	0,	'%s absorbs the nature energy of the attack.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (17108,	0,	'%s absorbs the shadow energy of the attack.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (17109,	0,	'%s absorbs the arcane energy of the attack.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (17110,	0,	'%s absorbs the holy energy of the attack.',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (20023,	0,	'Miserable vermin. I shall exterminate you from the air!',	'',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019),
  (24548,	7,	'%s takes a deep breath.',	'%s takes a deep breath.',	0,	0,	0,	0,	0,	0,	0,	0,	1,	18019);

-- NPC 352
SET @ENTRY = 352;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Dungar Longdrink - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dungar Longdrink - On Aggro - Say Line 0 (No Repeat)');

-- NPC 523
SET @ENTRY = 523;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Thor - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thor - On Aggro - Say Line 0 (No Repeat)');

-- NPC 931
SET @ENTRY = 931;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Ariena Stormfeather - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ariena Stormfeather - On Aggro - Say Line 0 (No Repeat)');

-- NPC 1179
SET @ENTRY = 1179;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 10, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Mo&#039;grosh Enforcer - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 7400, 14500, 46600, 53700, 11, 13730, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mo&#039;grosh Enforcer - In Combat - Cast "<a href="http://wowhead.com/spell=13730">Demoralizing Shout</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 7400, 14500, 46600, 53700, 5, 15, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mo&#039;grosh Enforcer - In Combat - Play Emote 15 ');

-- NPC 1180
SET @ENTRY = 1180;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 10, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Mo&#039;grosh Brute - On Aggro - Say Line 0 (No Repeat)');

-- NPC 1387
SET @ENTRY = 1387;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Thysta - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thysta - On Aggro - Say Line 0 (No Repeat)');

-- NPC 1571
SET @ENTRY = 1571;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Shellei Brondir - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shellei Brondir - On Aggro - Say Line 0 (No Repeat)');

-- NPC 1572
SET @ENTRY = 1572;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Thorgrum Borrelson - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thorgrum Borrelson - On Aggro - Say Line 0 (No Repeat)');

-- NPC 1573
SET @ENTRY = 1573;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gryth Thurden - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gryth Thurden - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2044
SET @ENTRY = 2044;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Forlorn Spirit - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 23, 0, 100, 0, 3105, 0, 10000, 20000, 11, 3105, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Forlorn Spirit - On Missing Aura "<a href="http://wowhead.com/spell=3105">Curse of Stalvan</a>" - Cast "<a href="http://wowhead.com/spell=3105">Curse of Stalvan</a>" '),
  (@ENTRY, 0, 2, 0, 9, 0, 100, 0, 5, 10, 10000, 20000, 11, 118, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Forlorn Spirit - Within 5-10 Range - Cast "<a href="http://wowhead.com/spell=118">Polymorph</a>" ');

-- NPC 2226
SET @ENTRY = 2226;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14252, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Karos Razok - On Aggro - Cast "<a href="http://wowhead.com/spell=14252">Summon Enraged Felbat</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Karos Razok - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2299
SET @ENTRY = 2299;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Borgus Stoutarm - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Borgus Stoutarm - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2389
SET @ENTRY = 2389;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14252, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Zarise - On Aggro - Cast "<a href="http://wowhead.com/spell=14252">Summon Enraged Felbat</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zarise - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2409
SET @ENTRY = 2409;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Felicia Maline - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Felicia Maline - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2432
SET @ENTRY = 2432;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Darla Harris - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darla Harris - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2567
SET @ENTRY = 2567;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 513, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Out of Combat - Disable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 1, 1000, 1000, 1800000, 1800000, 11, 12544, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Out of Combat - Cast "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" (No Repeat)'),
  (@ENTRY, 0, 2, 0, 4, 0, 5, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 20822, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - On Aggro - Cast "<a href="http://wowhead.com/spell=20822">Frostbolt</a>" (No Repeat)'),
  (@ENTRY, 0, 4, 0, 4, 0, 100, 513, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - On Aggro - Increase Phase By 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 5, 0, 9, 1, 100, 0, 0, 40, 3500, 6400, 11, 20822, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=20822">Frostbolt</a>" (Phase 1)'),
  (@ENTRY, 0, 6, 7, 3, 1, 100, 513, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Between 0-15% MP - Enable Combat Movement (No Repeat and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 61, 1, 100, 513, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Between 0-15% MP - Increase Phase By 1 (No Repeat and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 0, 9, 1, 100, 513, 35, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Within 35-80 Range - Enable Combat Movement (No Repeat and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 9, 1, 100, 513, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Within 0-5 Range - Enable Combat Movement (No Repeat and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 10, 0, 9, 1, 100, 512, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Within 5-15 Range - Disable Combat Movement (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 0, 3, 4, 100, 512, 30, 100, 100, 100, 23, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Between 30-100% MP - Decrease Phase By 0 (While Charmed)(Phase 3)'),
  (@ENTRY, 0, 12, 0, 0, 0, 100, 0, 6000, 9800, 15400, 23500, 11, 11831, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - In Combat - Cast "<a href="http://wowhead.com/spell=11831">Frost Nova</a>" '),
  (@ENTRY, 0, 13, 0, 2, 0, 100, 513, 0, 15, 0, 0, 22, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Between 0-15% HP - Set Event Phase 3 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 14, 0, 2, 0, 100, 513, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Between 0-15% HP - Enable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 15, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Between 0-15% HP - Flee For Assist (No Repeat)'),
  (@ENTRY, 0, 16, 0, 7, 0, 100, 513, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - On Evade - Set Event Phase 0 (No Repeat and  While Charmed)');

-- NPC 2567
SET @ENTRY = 2567;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 23, 0, 100, 0, 12544, 0, 10000, 30000, 11, 12544, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - On Missing Aura "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" - Cast "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" '),
  (@ENTRY, 0, 2, 0, 37, 0, 5, 0, 0, 0, 0, 0, 58, 6, 20822, 3000, 3300, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 6000, 9800, 15400, 23500, 11, 11831, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - In Combat - Cast "<a href="http://wowhead.com/spell=11831">Frost Nova</a>" '),
  (@ENTRY, 0, 4, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Magus - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 2720
SET @ENTRY = 2720;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 4, 0, 10, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Dustbelcher Ogre Mage - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 2, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20822, 3000, 3300, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dustbelcher Ogre Mage - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 11, 0, 0, 0, 100, 0, 3700, 7700, 31500, 43600, 11, 6742, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dustbelcher Ogre Mage - In Combat - Cast "<a href="http://wowhead.com/spell=6742">Bloodlust</a>" ');

-- NPC 2793
SET @ENTRY = 2793;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 30, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Kor&#039;gresh Coldrage - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 8500, 12400, 48700, 53600, 11, 865, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Kor&#039;gresh Coldrage - In Combat - Cast "<a href="http://wowhead.com/spell=865">Frost Nova</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 1200, 7800, 48600, 55100, 11, 4320, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Kor&#039;gresh Coldrage - In Combat - Cast "<a href="http://wowhead.com/spell=4320">Trelane"s Freezing Touch</a>" ');

-- NPC 2835
SET @ENTRY = 2835;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 0, 30000, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Cedrik Prose - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cedrik Prose - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2851
SET @ENTRY = 2851;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Urda - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Urda - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2858
SET @ENTRY = 2858;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gringer - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gringer - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2859
SET @ENTRY = 2859;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gyll - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gyll - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2861
SET @ENTRY = 2861;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gorrik - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gorrik - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2941
SET @ENTRY = 2941;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Lanie Reed - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lanie Reed - On Aggro - Say Line 0 (No Repeat)');

-- NPC 2995
SET @ENTRY = 2995;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Tal - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tal - On Aggro - Say Line 0 (No Repeat)');

-- NPC 3305
SET @ENTRY = 3305;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Grisha - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grisha - On Aggro - Say Line 0 (No Repeat)');

-- NPC 3310
SET @ENTRY = 3310;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Doras - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Doras - On Aggro - Say Line 0 (No Repeat)');

-- NPC 3584
SET @ENTRY = 3584;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 19, 0, 100, 0, 945, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Therylune - On Quest "<a href="http://wowhead.com/quest=945">Therylune"s Escape</a>" Accepted - Say Line 0 '),
  (@ENTRY, 0, 1, 5, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 3584, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Therylune - On Quest "<a href="http://wowhead.com/quest=945">Therylune"s Escape</a>" Accepted - Start Waypoint 3584 '),
  (@ENTRY, 0, 2, 3, 40, 0, 100, 0, 20, 3584, 0, 0, 1, 1, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Therylune - On Waypoint 20 Reached - Say Line 1 '),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 15, 945, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Therylune - On Waypoint 20 Reached - Quest Credit ""<a href="http://wowhead.com/quest=945">Therylune"s Escape</a>" '),
  (@ENTRY, 0, 4, 0, 40, 0, 100, 0, 21, 3584, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Therylune - On Waypoint 21 Reached - Despawn In 5000ms '),
  (@ENTRY, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 2, 1709, 3584, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Therylune - On Quest "<a href="http://wowhead.com/quest=945">Therylune"s Escape</a>" Accepted - Set Faction 1709 '),
  (@ENTRY, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Therylune - On Quest "<a href="http://wowhead.com/quest=945">Therylune"s Escape</a>" Accepted - Store Targetlist 1 ');

-- NPC 3615
SET @ENTRY = 3615;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Devrak - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Devrak - On Aggro - Say Line 0 (No Repeat)');

-- NPC 4312
SET @ENTRY = 4312;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Tharm - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tharm - On Aggro - Say Line 0 (No Repeat)');

-- NPC 4314
SET @ENTRY = 4314;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 12, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gorkas - On Aggro - Summon "<a href="http://wowhead.com/npc=14307">Black Drakonid Spawner</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gorkas - On Aggro - Say Line 0 (No Repeat)');

-- NPC 4317
SET @ENTRY = 4317;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Nyse - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nyse - On Aggro - Say Line 0 (No Repeat)');

-- NPC 4321
SET @ENTRY = 4321;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Baldruc - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baldruc - On Aggro - Say Line 0 (No Repeat)');

-- NPC 4551
SET @ENTRY = 4551;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14252, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Michael Garrett - On Aggro - Cast "<a href="http://wowhead.com/spell=14252">Summon Enraged Felbat</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Michael Garrett - On Aggro - Say Line 0 (No Repeat)');

-- NPC 5975
SET @ENTRY = 5975;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 15, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Dreadmaul Ogre Mage - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20823, 3000, 3300, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dreadmaul Ogre Mage - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 30, 0, 0, 11, 6742, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dreadmaul Ogre Mage - Between 0-30% HP - Cast "<a href="http://wowhead.com/spell=6742">Bloodlust</a>" (No Repeat)');

-- NPC 6026
SET @ENTRY = 6026;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Breyk - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Breyk - On Aggro - Say Line 0 (No Repeat)');

-- NPC 6556
SET @ENTRY = 6556;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 23, 0, 100, 0, 14133, 0, 20000, 30000, 11, 14133, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Muculent Ooze - On Missing Aura "<a href="http://wowhead.com/spell=14133">Muculent Fever Proc</a>" - Cast "<a href="http://wowhead.com/spell=14133">Muculent Fever Proc</a>" '),
  (@ENTRY, 0, 1, 0, 8, 0, 100, 0, 15702, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Muculent Ooze - On Spellhit "<a href="http://wowhead.com/spell=15702">Filling Empty Jar</a>" - Despawn Instant ');

-- NPC 6726
SET @ENTRY = 6726;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Thalon - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thalon - On Aggro - Say Line 0 (No Repeat)');

-- NPC 7823
SET @ENTRY = 7823;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Bera Stonehammer - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bera Stonehammer - On Aggro - Say Line 0 (No Repeat)');

-- NPC 7824
SET @ENTRY = 7824;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Bulkrek Ragefist - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bulkrek Ragefist - On Aggro - Say Line 0 (No Repeat)');

-- NPC 8018
SET @ENTRY = 8018;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Guthrum Thunderfist - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Guthrum Thunderfist - On Aggro - Say Line 0 (No Repeat)');

-- NPC 8020
SET @ENTRY = 8020;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Shyn - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shyn - On Aggro - Say Line 0 (No Repeat)');

-- NPC 8578
SET @ENTRY = 8578;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, 0, 3000, 5000, 11, 20823, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Magus Rimtori - In Combat - Cast "<a href="http://wowhead.com/spell=20823">Fireball</a>" '),
  (@ENTRY, 0, 1, 0, 9, 0, 100, 0, 0, 8, 13000, 16000, 11, 11831, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magus Rimtori - Within 0-8 Range - Cast "<a href="http://wowhead.com/spell=11831">Frost Nova</a>" '),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magus Rimtori - On Aggro - Say Line 0 ');

-- NPC 8609
SET @ENTRY = 8609;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Alexandra Constantine - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Alexandra Constantine - On Aggro - Say Line 0 (No Repeat)');

-- NPC 8610
SET @ENTRY = 8610;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Kroum - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kroum - On Aggro - Say Line 0 (No Repeat)');

-- NPC 10378
SET @ENTRY = 10378;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Omusa Thunderhorn - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Omusa Thunderhorn - On Aggro - Say Line 0 (No Repeat)');

-- NPC 10583
SET @ENTRY = 10583;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gryfe - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gryfe - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 11139
SET @ENTRY = 11139;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Yugrek - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Yugrek - On Aggro - Say Line 0 (No Repeat)');

-- NPC 11899
SET @ENTRY = 11899;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Shardi - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shardi - On Aggro - Say Line 0 (No Repeat)');

-- NPC 11900
SET @ENTRY = 11900;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Brakkar - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Brakkar - On Aggro - Say Line 0 (No Repeat)');

-- NPC 11901
SET @ENTRY = 11901;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Andruk - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Andruk - On Aggro - Say Line 0 (No Repeat)');

-- NPC 12596
SET @ENTRY = 12596;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Bibilfaz Featherwhistle - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bibilfaz Featherwhistle - On Aggro - Say Line 0 (No Repeat)');

-- NPC 12616
SET @ENTRY = 12616;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Vhulgra - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vhulgra - On Aggro - Say Line 0 (No Repeat)');

-- NPC 12617
SET @ENTRY = 12617;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Khaelyn Steelwing - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Khaelyn Steelwing - On Aggro - Say Line 0 (No Repeat)');

-- NPC 12636
SET @ENTRY = 12636;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14252, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Georgia - On Aggro - Cast "<a href="http://wowhead.com/spell=14252">Summon Enraged Felbat</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Georgia - On Aggro - Say Line 0 (No Repeat)');

-- NPC 12740
SET @ENTRY = 12740;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Faustron - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Faustron - On Aggro - Say Line 0 (No Repeat)');

-- NPC 13177
SET @ENTRY = 13177;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Vahgruk - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vahgruk - On Aggro - Say Line 0 (No Repeat)');

-- NPC 15178
SET @ENTRY = 15178;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Runk Windtamer - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Runk Windtamer - On Aggro - Say Line 0 (No Repeat)');

-- NPC 16189
SET @ENTRY = 16189;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14252, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Skymaster Sunwing - On Aggro - Cast "<a href="http://wowhead.com/spell=14252">Summon Enraged Felbat</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Skymaster Sunwing - On Aggro - Say Line 0 (No Repeat)');

-- NPC 16192
SET @ENTRY = 16192;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14252, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Skymistress Gloaming - On Aggro - Cast "<a href="http://wowhead.com/spell=14252">Summon Enraged Felbat</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Skymistress Gloaming - On Aggro - Say Line 0 (No Repeat)');

-- NPC 16227
SET @ENTRY = 16227;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bragok - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bragok - On Aggro - Say Line 0 ');

-- NPC 16504
SET @ENTRY = 16504;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 10000, 15000, 25000, 30000, 11, 29840, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Cast "<a href="http://wowhead.com/spell=29840">Fist of Stone</a>" '),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 30, 1, 2, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - On Aggro - Set Random Phase (1, 2 and 3) '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 15000, 20000, 15000, 20000, 11, 29857, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Cast "<a href="http://wowhead.com/spell=29857">Summon Astral Spark</a>" '),
  (@ENTRY, 0, 3, 0, 0, 1, 100, 0, 0, 1000, 21000, 21000, 11, 29788, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Cast "<a href="http://wowhead.com/spell=29788">Return Fire</a>" (Phase 1)'),
  (@ENTRY, 0, 4, 0, 0, 1, 100, 0, 0, 0, 21000, 21000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Say Line 0 (Phase 1)'),
  (@ENTRY, 0, 5, 0, 0, 1, 100, 1, 20000, 20000, 0, 0, 30, 1, 2, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Set Random Phase (1, 2 and 3) (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 0, 2, 100, 0, 0, 1000, 21000, 21000, 11, 29793, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Cast "<a href="http://wowhead.com/spell=29793">Return Fire</a>" (Phase 2)'),
  (@ENTRY, 0, 7, 0, 0, 2, 100, 0, 0, 0, 21000, 21000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Say Line 1 (Phase 2)'),
  (@ENTRY, 0, 8, 0, 0, 2, 100, 1, 20000, 20000, 0, 0, 30, 1, 2, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Set Random Phase (1, 2 and 3) (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 9, 0, 0, 4, 100, 0, 0, 1000, 21000, 21000, 11, 29794, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Cast "<a href="http://wowhead.com/spell=29794">Return Fire</a>" (Phase 3)'),
  (@ENTRY, 0, 10, 0, 0, 4, 100, 0, 0, 0, 21000, 21000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Say Line 2 (Phase 3)'),
  (@ENTRY, 0, 11, 0, 0, 4, 100, 1, 20000, 20000, 0, 0, 30, 1, 2, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - In Combat - Set Random Phase (1, 2 and 3) (No Repeat)(Phase 3)'),
  (@ENTRY, 0, 12, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - On Aggro - Say Line 3 (No Repeat)'),
  (@ENTRY, 0, 13, 0, 6, 0, 100, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcane Protector - On Death - Say Line 4 ');

-- NPC 16587
SET @ENTRY = 16587;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Barley - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Barley - On Aggro - Say Line 0 (No Repeat)');

-- NPC 16802
SET @ENTRY = 16802;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 5000, 7000, 5000, 9000, 11, 15284, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Lor&#039;themar Theron - In Combat - Cast "<a href="http://wowhead.com/spell=15284">Cleave</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 8000, 11000, 10000, 13000, 11, 33385, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Lor&#039;themar Theron - In Combat - Cast "<a href="http://wowhead.com/spell=33385">Mana Burn</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 22000, 24000, 44000, 48000, 11, 33384, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Lor&#039;themar Theron - In Combat - Cast "<a href="http://wowhead.com/spell=33384">Mass Charm</a>" ');

-- NPC 16822
SET @ENTRY = 16822;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Flightmaster Krill Bitterhue - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Flightmaster Krill Bitterhue - On Aggro - Say Line 0 (No Repeat)');

-- NPC 17209
SET @ENTRY = 17209;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'William Kielar - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'William Kielar - On Aggro - Say Line 0 (No Repeat)');

DELETE FROM smart_scripts WHERE entryorguid = 17301 AND source_type = 0;

-- NPC 17468
SET @ENTRY = 17468;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 4, 10154, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Prophet Velen - On Aggro - Play Sound 10154 '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 5000, 7000, 6000, 8000, 11, 33542, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Prophet Velen - In Combat - Cast "<a href="http://wowhead.com/spell=33542">Staff Strike</a>" ');

-- NPC 18398
SET @ENTRY = 18398;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 1000, 1000, 9000, 11000, 11, 32023, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Brokentoe - In Combat - Cast "<a href="http://wowhead.com/spell=32023">Hoof Stomp</a>" '),
  (@ENTRY, 0, 2, 0, 6, 0, 100, 0, 0, 0, 0, 0, 45, 10, 10, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Brokentoe - On Death - Set Data 10 10 '),
  (@ENTRY, 0, 4, 5, 7, 0, 100, 0, 0, 0, 0, 0, 45, 20, 20, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Brokentoe - On Evade - Set Data 20 20 '),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Brokentoe - On Evade - Despawn In 5000ms '),
  (@ENTRY, 0, 6, 0, 1, 0, 100, 1, 179000, 179000, 0, 0, 45, 30, 30, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Brokentoe - Out of Combat - Set Data 30 30 (No Repeat)');

-- NPC 18400
SET @ENTRY = 18400;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - Out of Combat - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 9000, 11000, 11, 16727, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - In Combat - Cast "<a href="http://wowhead.com/spell=16727">War Stomp</a>" '),
  (@ENTRY, 0, 2, 0, 31, 0, 100, 0, 31389, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - On Target Spellhit "<a href="http://wowhead.com/spell=31389">Knock Away</a>" - Say Line 0 '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 6000, 6000, 12000, 12000, 11, 31389, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - In Combat - Cast "<a href="http://wowhead.com/spell=31389">Knock Away</a>" '),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 0, 20000, 20000, 25000, 25000, 11, 15976, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - In Combat - Cast "<a href="http://wowhead.com/spell=15976">Puncture</a>" '),
  (@ENTRY, 0, 6, 0, 6, 0, 100, 0, 0, 0, 0, 0, 45, 12, 12, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - On Death - Set Data 12 12 '),
  (@ENTRY, 0, 7, 8, 7, 0, 100, 0, 0, 0, 0, 0, 45, 20, 20, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - On Evade - Set Data 20 20 '),
  (@ENTRY, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - On Evade - Despawn In 5000ms '),
  (@ENTRY, 0, 9, 0, 1, 0, 100, 1, 179000, 179000, 0, 0, 45, 30, 30, 0, 0, 0, 0, 10, 0, 65810, 18471, 0, 0, 0, 0, 0, 'Rokdar the Sundered Lord - Out of Combat - Set Data 30 30 (No Repeat)');

-- NPC 18791
SET @ENTRY = 18791;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Du&#039;ga - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Du&#039;ga - On Aggro - Say Line 0 (No Repeat)');

-- NPC 18807
SET @ENTRY = 18807;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Kerna - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kerna - On Aggro - Say Line 0 (No Repeat)');

-- NPC 18808
SET @ENTRY = 18808;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gursha - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gursha - On Aggro - Say Line 0 (No Repeat)');

-- NPC 18809
SET @ENTRY = 18809;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Furnan Skysoar - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Furnan Skysoar - On Aggro - Say Line 0 (No Repeat)');

-- NPC 18930
SET @ENTRY = 18930;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Vlagga Freyfeather - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vlagga Freyfeather - On Aggro - Say Line 0 (No Repeat)');

-- NPC 18931
SET @ENTRY = 18931;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Amish Wildhammer - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amish Wildhammer - On Aggro - Say Line 0 (No Repeat)');

-- NPC 18938
SET @ENTRY = 18938;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Krexcil - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Krexcil - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 18939
SET @ENTRY = 18939;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Brubeck Stormfoot - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Brubeck Stormfoot - On Aggro - Say Line 0 (No Repeat)');

-- NPC 18940
SET @ENTRY = 18940;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nutral - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nutral - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 18942
SET @ENTRY = 18942;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 513, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Out of Combat - Disable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 513, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Out of Combat - Stop Attacking (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - In Combat - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - In Combat - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 5, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 22121, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - On Aggro - Cast "<a href="http://wowhead.com/spell=22121">Shoot</a>" (No Repeat)'),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 513, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - On Aggro - Increase Phase By 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 7, 0, 9, 1, 100, 0, 5, 30, 2300, 3900, 11, 22121, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=22121">Shoot</a>" (Phase 1)'),
  (@ENTRY, 0, 8, 0, 9, 1, 100, 0, 5, 30, 2300, 3900, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Within 5-30 Range - Set Sheath Ranged (Phase 1)'),
  (@ENTRY, 0, 9, 0, 9, 1, 100, 512, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Within 25-80 Range - Enable Combat Movement (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 10, 0, 9, 1, 100, 512, 25, 80, 0, 500, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Within 25-80 Range - Start Attacking (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 0, 9, 1, 100, 512, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Within 0-5 Range - Enable Combat Movement (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 9, 1, 100, 0, 0, 5, 0, 500, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Within 0-5 Range - Set Sheath Melee (Phase 1)'),
  (@ENTRY, 0, 13, 0, 9, 1, 100, 512, 0, 5, 0, 500, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Within 0-5 Range - Start Attacking (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 14, 0, 9, 1, 100, 512, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Within 5-15 Range - Disable Combat Movement (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 15, 0, 9, 1, 100, 512, 5, 15, 0, 500, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Within 5-15 Range - Stop Attacking (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 16, 0, 2, 0, 100, 513, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Between 0-15% HP - Increase Phase By 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 513, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Between 0-15% HP - Enable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 18, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - Between 0-15% HP - Flee For Assist (No Repeat)'),
  (@ENTRY, 0, 19, 0, 7, 0, 100, 513, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - On Evade - Set Event Phase 0 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 20, 0, 7, 0, 100, 1, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Innalia - On Evade - Set Sheath Melee (No Repeat)');

-- NPC 18953
SET @ENTRY = 18953;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Unoke Tenderhoof - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Unoke Tenderhoof - On Aggro - Say Line 0 (No Repeat)');

-- NPC 19027
SET @ENTRY = 19027;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 1, 0, 0, 0, 0, 11, 16093, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Stabled Kurenai Lion - On Respawn - Cast "<a href="http://wowhead.com/spell=16093">Self Visual - Sleep Until Cancelled (DND)</a>" (No Repeat)');

-- NPC 19030
SET @ENTRY = 19030;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 1, 0, 0, 0, 0, 11, 16093, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Stabled Kurenai Panther - On Respawn - Cast "<a href="http://wowhead.com/spell=16093">Self Visual - Sleep Until Cancelled (DND)</a>" (No Repeat)');

-- NPC 19181
SET @ENTRY = 19181;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Lemla Hopewing - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lemla Hopewing - On Aggro - Say Line 0 (No Repeat)');

-- NPC 19317
SET @ENTRY = 19317;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Drek&#039;Gol - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Drek&#039;Gol - On Aggro - Say Line 0 (No Repeat)');

-- NPC 19558
SET @ENTRY = 19558;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 513, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Out of Combat - Disable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 513, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Out of Combat - Stop Attacking (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - In Combat - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - In Combat - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 5, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 22121, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - On Aggro - Cast "<a href="http://wowhead.com/spell=22121">Shoot</a>" (No Repeat)'),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 513, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - On Aggro - Increase Phase By 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 7, 0, 9, 1, 100, 0, 5, 30, 2300, 3900, 11, 22121, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=22121">Shoot</a>" (Phase 1)'),
  (@ENTRY, 0, 8, 0, 9, 1, 100, 0, 5, 30, 2300, 3900, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Within 5-30 Range - Set Sheath Ranged (Phase 1)'),
  (@ENTRY, 0, 9, 0, 9, 1, 100, 512, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Within 25-80 Range - Enable Combat Movement (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 10, 0, 9, 1, 100, 512, 25, 80, 0, 500, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Within 25-80 Range - Start Attacking (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 0, 9, 1, 100, 512, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Within 0-5 Range - Enable Combat Movement (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 9, 1, 100, 0, 0, 5, 0, 500, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Within 0-5 Range - Set Sheath Melee (Phase 1)'),
  (@ENTRY, 0, 13, 0, 9, 1, 100, 512, 0, 5, 0, 500, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Within 0-5 Range - Start Attacking (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 14, 0, 9, 1, 100, 512, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Within 5-15 Range - Disable Combat Movement (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 15, 0, 9, 1, 100, 512, 5, 15, 0, 500, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Within 5-15 Range - Stop Attacking (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 16, 0, 2, 0, 100, 513, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Between 0-15% HP - Increase Phase By 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 513, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Between 0-15% HP - Enable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 18, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - Between 0-15% HP - Flee For Assist (No Repeat)'),
  (@ENTRY, 0, 19, 0, 7, 0, 100, 513, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - On Evade - Set Event Phase 0 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 20, 0, 7, 0, 100, 1, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Amilya Airheart - On Evade - Set Sheath Melee (No Repeat)');

-- NPC 19581
SET @ENTRY = 19581;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Maddix - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Maddix - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 19583
SET @ENTRY = 19583;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grennik - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grennik - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 20234
SET @ENTRY = 20234;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Runetog Wildhammer - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Runetog Wildhammer - On Aggro - Say Line 0 (No Repeat)');

-- NPC 20515
SET @ENTRY = 20515;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Harpax - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Harpax - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 20601
SET @ENTRY = 20601;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 3000, 5000, 10000, 15000, 11, 35922, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Razaani Raider - In Combat - Cast "<a href="http://wowhead.com/spell=35922">Energy Flare</a>" ');

-- NPC 20609
SET @ENTRY = 20609;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 3000, 5000, 5000, 10000, 11, 11975, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Razaani Nexus Stalker - In Combat - Cast "<a href="http://wowhead.com/spell=11975">Arcane Explosion</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 10000, 15000, 15000, 20000, 11, 36513, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Razaani Nexus Stalker - In Combat - Cast "<a href="http://wowhead.com/spell=36513">Intangible Presence</a>" ');

-- NPC 20614
SET @ENTRY = 20614;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 10000, 10000, 10000, 15000, 11, 36508, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Razaani Spell-Thief - In Combat - Cast "<a href="http://wowhead.com/spell=36508">Energy Surge</a>" ');

-- NPC 20762
SET @ENTRY = 20762;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14307, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Gur&#039;zil - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gur&#039;zil - On Aggro - Say Line 0 (No Repeat)');

-- NPC 21107
SET @ENTRY = 21107;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Rip Pedalslam - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Rip Pedalslam - On Aggro - Say Line 0 (No Repeat)');

-- NPC 21735
SET @ENTRY = 21735;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 0, 11, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 23, 0, 100, 0, 0, 0, 0, 0, 0, 'Infernal Oversoul - On Respawn - Start Attacking ');

-- NPC 21766
SET @ENTRY = 21766;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Alieshor - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Alieshor - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 22216
SET @ENTRY = 22216;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fhyn Leafshadow - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fhyn Leafshadow - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 22423
SET @ENTRY = 22423;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 1, 38782, 0, 0, 0, 11, 38776, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Evergrove Druid - On Spellhit "<a href="http://wowhead.com/spell=38782">Druid Signal</a>" - Cast "<a href="http://wowhead.com/spell=38776">Evergrove Druid Transform Crow</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 512, 0, 0, 0, 0, 19, 33554432, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Evergrove Druid - On Spellhit "<a href="http://wowhead.com/spell=38782">Druid Signal</a>" - Set Unit Flag Not Selectable (While Charmed)'),
  (@ENTRY, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Evergrove Druid - On Spellhit "<a href="http://wowhead.com/spell=38782">Druid Signal</a>" - Move To Pos '),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 512, 0, 0, 0, 0, 81, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Evergrove Druid - On Spellhit "<a href="http://wowhead.com/spell=38782">Druid Signal</a>" - Set NPC Flag Quest Giver (While Charmed)'),
  (@ENTRY, 0, 4, 5, 64, 0, 100, 1, 0, 0, 0, 0, 11, 39158, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Evergrove Druid - On Gossip Hello - Cast "<a href="http://wowhead.com/spell=39158">Evergrove Druid Transform Druid</a>" (No Repeat)'),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 512, 0, 0, 0, 0, 41, 60000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Evergrove Druid - On Gossip Hello - Despawn In 60000ms (While Charmed)'),
  (@ENTRY, 0, 6, 0, 19, 0, 100, 512, 10904, 0, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Evergrove Druid - On Quest "<a href="http://wowhead.com/quest=10904">Harvesting the Fel Ammunition</a>" Accepted - Despawn In 10000ms (While Charmed)'),
  (@ENTRY, 0, 7, 0, 19, 0, 100, 512, 10911, 0, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Evergrove Druid - On Quest "<a href="http://wowhead.com/quest=10911">Fire At Will!</a>" Accepted - Despawn In 10000ms (While Charmed)'),
  (@ENTRY, 0, 8, 0, 19, 0, 100, 512, 10912, 0, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Evergrove Druid - On Quest "<a href="http://wowhead.com/quest=10912">The Hound-Master</a>" Accepted - Despawn In 10000ms (While Charmed)'),
  (@ENTRY, 0, 9, 0, 11, 0, 100, 512, 0, 0, 0, 0, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Evergrove Druid - On Respawn - Set NPC Flag Quest Giver (While Charmed)');

-- NPC 22455
SET @ENTRY = 22455;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sky-Master Maxxor - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sky-Master Maxxor - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 23049
SET @ENTRY = 23049;
DELETE FROM creature_text WHERE CreatureID = @ENTRY;
INSERT IGNORE INTO creature_text (CreatureID, groupid, id, text, type, language, probability, emote, sound, comment) VALUES
  (@ENTRY, 0, 0, "Battle Stance! Prepare for an offensive rush!", 14, 0, 100, 0, 0, "Shadowmoon Weapon Master - "),
  (@ENTRY, 1, 0, "Berserker Stance! Attack them recklessly!", 14, 0, 100, 0, 0, "Shadowmoon Weapon Master - "),
  (@ENTRY, 2, 0, "Defensive Stance! Shield yourself against their blows and strike back!", 14, 0, 100, 0, 0, "Shadowmoon Weapon Master - ");
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 41099, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - On Aggro - Cast "<a href="http://wowhead.com/spell=41099">Battle Stance</a>" '),
  (@ENTRY, 0, 1, 10, 61, 0, 100, 0, 0, 0, 0, 0, 11, 41106, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - On Aggro - Cast "<a href="http://wowhead.com/spell=41106">Battle Aura</a>" '),
  (@ENTRY, 0, 2, 3, 2, 0, 100, 1, 0, 70, 0, 0, 11, 41101, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - Between 0-70% HP - Cast "<a href="http://wowhead.com/spell=41101">Defensive Stance</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 4, 61, 0, 100, 1, 0, 0, 0, 0, 11, 41105, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - Between 0-70% HP - Cast "<a href="http://wowhead.com/spell=41105">Defensive Aura</a>" (No Repeat)'),
  (@ENTRY, 0, 4, 0, 61, 0, 100, 1, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - Between 0-70% HP - Say Line 2 (No Repeat)'),
  (@ENTRY, 0, 5, 6, 2, 0, 100, 1, 0, 40, 0, 0, 11, 41100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - Between 0-40% HP - Cast "<a href="http://wowhead.com/spell=41100">Berserker Stance</a>" (No Repeat)'),
  (@ENTRY, 0, 6, 11, 61, 0, 100, 3, 0, 0, 0, 0, 11, 41107, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - Between 0-40% HP - Cast "<a href="http://wowhead.com/spell=41107">Berseker Aura</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 7, 0, 2, 0, 100, 2, 0, 30, 25000, 30000, 11, 41097, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - Between 0-30% HP - Cast "<a href="http://wowhead.com/spell=41097">Whirlwind</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 8, 0, 0, 0, 100, 2, 3000, 6000, 8000, 11000, 11, 41103, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - In Combat - Cast "<a href="http://wowhead.com/spell=41103">Mutilate</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 9, 0, 0, 0, 100, 2, 6000, 8000, 12000, 16000, 11, 18813, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - In Combat - Cast "<a href="http://wowhead.com/spell=18813">Knock Away</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - On Aggro - Say Line 0 '),
  (@ENTRY, 0, 11, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowmoon Weapon Master - Between 0-40% HP - Say Line 1 ');

-- NPC 23163
SET @ENTRY = 23163;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gezzarak the Huntress - On Respawn - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 15000, 21000, 11, 40542, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gezzarak the Huntress - In Combat - Cast "<a href="http://wowhead.com/spell=40542">Warped Armor</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 4000, 7000, 17500, 20000, 11, 40434, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Gezzarak the Huntress - In Combat - Cast "<a href="http://wowhead.com/spell=40434">Knock Away</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 512, 16000, 19000, 22000, 25000, 14, 0, 99, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gezzarak the Huntress - In Combat - Decrease All Threat By 0% (While Charmed)'),
  (@ENTRY, 0, 4, 5, 0, 0, 100, 0, 16000, 19000, 22000, 25000, 11, 40432, 1, 0, 0, 0, 0, 5, 0, 0, 1, 0, 0, 0, 0, 0, 'Gezzarak the Huntress - In Combat - Cast "<a href="http://wowhead.com/spell=40432">Warp</a>" '),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 'Gezzarak the Huntress - In Combat - Say Line 1 '),
  (@ENTRY, 0, 6, 0, 0, 0, 100, 0, 13000, 17800, 21000, 26000, 11, 40542, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 'Gezzarak the Huntress - In Combat - Cast "<a href="http://wowhead.com/spell=40542">Warped Armor</a>" '),
  (@ENTRY, 0, 7, 0, 0, 0, 100, 0, 13000, 17800, 21000, 26000, 11, 40433, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 'Gezzarak the Huntress - In Combat - Cast "<a href="http://wowhead.com/spell=40433">Warp Rift</a>" ');

-- NPC 23612
SET @ENTRY = 23612;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dyslix Silvergrub - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dyslix Silvergrub - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 23704
SET @ENTRY = 23704;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Cassa Crimsonwing - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cassa Crimsonwing - On Aggro - Say Line 0 (No Repeat)');

-- NPC 24366
SET @ENTRY = 24366;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 14313, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Nizzle - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nizzle - On Aggro - Say Line 0 (No Repeat)');

-- NPC 24851
SET @ENTRY = 24851;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kiz Coilspanner - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kiz Coilspanner - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 26560
SET @ENTRY = 26560;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14252, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ohura - On Aggro - Cast "<a href="http://wowhead.com/spell=14252">Summon Enraged Felbat</a>" ');

DELETE FROM smart_scripts WHERE entryorguid = 29611 AND source_type = 0;

-- NPC 8581
SET @ENTRY = 8581;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY * 100 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY * 100, 9, 101, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 0, 50, 0, 0, 0, 0, 0, 0, 'Blood Elf Defender - In Combat - Start Attacking '),
  (@ENTRY * 100, 9, 102, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blood Elf Defender - In Combat - Say Line 0 '),
  (@ENTRY * 100, 9, 103, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blood Elf Defender - In Combat - Say Line 1 '),
  (@ENTRY * 100, 9, 104, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blood Elf Defender - In Combat - Say Line 2 ');

-- NPC 17410
SET @ENTRY = 17410;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY * 100 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY * 100, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 25035, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Stillpine Ancestor Vark - In Combat - Cast "<a href="http://wowhead.com/spell=25035">Elemental Spawn-in</a>" '),
  (@ENTRY * 100, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Stillpine Ancestor Vark - In Combat - Say Line 0 '),
  (@ENTRY * 100, 9, 102, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 11, 25035, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Stillpine Ancestor Vark - In Combat - Cast "<a href="http://wowhead.com/spell=25035">Elemental Spawn-in</a>" ');

-- NPC 6546
SET @ENTRY = 6546;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 19, 0, 100, 0, 4961, 0, 0, 0, 80, 654600, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tabetha - On Quest "<a href="http://wowhead.com/quest=4961">Cleansing of the Orb of Orahil</a>" Accepted - Run Script <a href="/smartai/script/654600">654600</a> '),
  (@ENTRY, 0, 1, 0, 20, 0, 100, 0, 1957, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 14, 0, 28294, 103680, 0, 0, 0, 0, 0, 'Tabetha - On Quest "<a href="http://wowhead.com/quest=1957">Mana Surges</a>" Rewarded - Activate GO '),
  (@ENTRY, 0, 2, 3, 19, 0, 100, 0, 1957, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 14, 0, 28294, 103680, 0, 0, 0, 0, 0, 'Tabetha - On Quest "<a href="http://wowhead.com/quest=1957">Mana Surges</a>" Accepted - Activate GO '),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 87, 654601, 654602, 654603, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tabetha - On Quest "<a href="http://wowhead.com/quest=1957">Mana Surges</a>" Accepted - Run Random Script '),
  (@ENTRY, 0, 4, 0, 38, 0, 100, 0, 1, 1, 0, 0, 87, 654601, 654602, 654603, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tabetha - On Data Set 1 1 - Run Random Script '),
  (@ENTRY, 0, 5, 0, 19, 0, 100, 0, 1955, 0, 0, 0, 80, 654600, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tabetha - On Quest "<a href="http://wowhead.com/quest=1955">The Exorcism</a>" Accepted - Run Script <a href="/smartai/script/654600">654600</a> ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY * 100 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY * 100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Tabetha - In Combat - Say Line 0 '),
  (@ENTRY * 100, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 11, 9097, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tabetha - In Combat - Cast "<a href="http://wowhead.com/spell=9097">Summon Demon of the Orb</a>" ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY * 100 + 1 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY * 100 + 1, 9, 100, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 6550, 1, 600000, 0, 0, 0, 8, 0, 0, 0, 0, -4019.22, -3383.91, 38.2265, 2.7963, 'Tabetha - In Combat - Summon "<a href="http://wowhead.com/npc=6550">Mana Surge</a>" '),
  (@ENTRY * 100 + 1, 9, 101, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 6550, 1, 600000, 0, 0, 0, 8, 0, 0, 0, 0, -4019.22, -3383.91, 38.2265, 2.7963, 'Tabetha - In Combat - Summon "<a href="http://wowhead.com/npc=6550">Mana Surge</a>" '),
  (@ENTRY * 100 + 1, 9, 102, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 6550, 1, 600000, 0, 0, 0, 8, 0, 0, 0, 0, -4019.22, -3383.91, 38.2265, 2.7963, 'Tabetha - In Combat - Summon "<a href="http://wowhead.com/npc=6550">Mana Surge</a>" ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY * 100 + 2 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY * 100 + 2, 9, 200, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 6550, 1, 600000, 0, 0, 0, 8, 0, 0, 0, 0, -4019.99, -3394.54, 38.5507, 1.8342, 'Tabetha - In Combat - Summon "<a href="http://wowhead.com/npc=6550">Mana Surge</a>" '),
  (@ENTRY * 100 + 2, 9, 201, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 6550, 1, 600000, 0, 0, 0, 8, 0, 0, 0, 0, -4019.99, -3394.54, 38.5507, 1.8342, 'Tabetha - In Combat - Summon "<a href="http://wowhead.com/npc=6550">Mana Surge</a>" ');
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY * 100 + 3 AND source_type = 9;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY * 100 + 3, 9, 300, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 6550, 1, 600000, 0, 0, 0, 8, 0, 0, 0, 0, -4013.29, -3385.14, 38.4656, 2.3801, 'Tabetha - In Combat - Summon "<a href="http://wowhead.com/npc=6550">Mana Surge</a>" '),
  (@ENTRY * 100 + 3, 9, 301, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 6550, 1, 600000, 0, 0, 0, 8, 0, 0, 0, 0, -4013.29, -3385.14, 38.4656, 2.3801, 'Tabetha - In Combat - Summon "<a href="http://wowhead.com/npc=6550">Mana Surge</a>" '),
  (@ENTRY * 100 + 3, 9, 302, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 6550, 1, 600000, 0, 0, 0, 8, 0, 0, 0, 0, -4013.29, -3385.14, 38.4656, 2.3801, 'Tabetha - In Combat - Summon "<a href="http://wowhead.com/npc=6550">Mana Surge</a>" ');

-- NPC 2375
SET @ENTRY = 2375;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 1, 0, 100, 513, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Out of Combat - Disable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Out of Combat - Stop Attacking (While Charmed)'),
  (@ENTRY, 0, 2, 3, 4, 0, 100, 0, 0, 0, 0, 0, 11, 10277, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - On Aggro - Cast "<a href="http://wowhead.com/spell=10277">Throw</a>" '),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 512, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - On Aggro - Increase Phase By 1 (While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 0, 100, 0, 5, 30, 2300, 3900, 11, 10277, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=10277">Throw</a>" '),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Within 5-30 Range - Set Sheath Ranged '),
  (@ENTRY, 0, 6, 7, 9, 0, 100, 512, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Within 25-80 Range - Enable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 7, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Within 25-80 Range - Start Attacking (While Charmed)'),
  (@ENTRY, 0, 8, 0, 9, 0, 100, 512, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Within 0-5 Range - Enable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 9, 10, 9, 0, 100, 0, 0, 0, 0, 500, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Within 0-0 Range - Set Sheath Melee '),
  (@ENTRY, 0, 10, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Within 0-0 Range - Start Attacking (While Charmed)'),
  (@ENTRY, 0, 11, 12, 9, 0, 100, 512, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Within 5-15 Range - Disable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 12, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Within 5-15 Range - Stop Attacking (While Charmed)'),
  (@ENTRY, 0, 13, 0, 2, 0, 100, 513, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Between 0-15% HP - Increase Phase By 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 14, 15, 2, 0, 100, 513, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Between 0-15% HP - Enable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 15, 16, 61, 0, 100, 1, 0, 0, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Between 0-15% HP - Flee For Assist (No Repeat)'),
  (@ENTRY, 0, 16, 0, 61, 0, 100, 0, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Coastrunner - Between 0-15% HP - Set Sheath Melee ');

-- NPC 15945
SET @ENTRY = 15945;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 15, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Apprentice Meledor - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Apprentice Meledor - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 17805
SET @ENTRY = 17805;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 80, 1780501, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Slavemaster - On Aggro - Run Script <a href="/smartai/script/1780501">1780501</a> '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 7500, 15000, 17500, 30000, 11, 6713, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Slavemaster - In Combat - Cast "<a href="http://wowhead.com/spell=6713">Disarm</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 15000, 30000, 30000, 40000, 11, 10987, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Slavemaster - In Combat - Cast "<a href="http://wowhead.com/spell=10987">Geyser</a>" '),
  (@ENTRY, 0, 3, 4, 2, 0, 100, 1, 0, 15, 120000, 120000, 11, 8269, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Slavemaster - Between 0-15% HP - Cast "<a href="http://wowhead.com/spell=8269">Enrage</a>" (No Repeat)'),
  (@ENTRY, 0, 4, 0, 61, 0, 100, 1, 0, 15, 120000, 120000, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Slavemaster - Between 0-15% HP - Say Line 1 (No Repeat)'),
  (@ENTRY, 0, 5, 0, 6, 0, 100, 0, 0, 0, 0, 0, 45, 0, 2, 0, 0, 0, 0, 9, 1, 17799, 0, 30, 0, 0, 0, 0, 'Coilfang Slavemaster - On Death - Set Data 0 2 '),
  (@ENTRY, 0, 6, 0, 25, 0, 100, 512, 0, 0, 0, 0, 28, 8269, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Slavemaster - On Reset - Remove Aura "<a href="http://wowhead.com/spell=8269">Enrage</a>" (While Charmed)');

-- NPC 17455
SET @ENTRY = 17455;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 5000, 10000, 15000, 20000, 11, 10966, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Bonechewer Beastmaster - In Combat - Cast "<a href="http://wowhead.com/spell=10966">Uppercut</a>" '),
  (@ENTRY, 0, 1, 7, 0, 0, 100, 0, 0, 10000, 20000, 30000, 11, 30635, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bonechewer Beastmaster - In Combat - Cast "<a href="http://wowhead.com/spell=30635">Battle Shout</a>" '),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Bonechewer Beastmaster - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 3, 4, 0, 0, 100, 1, 20000, 20000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Bonechewer Beastmaster - In Combat - Say Line 1 (No Repeat)'),
  (@ENTRY, 0, 4, 5, 61, 0, 100, 1, 0, 0, 0, 0, 12, 17280, 4, 20000, 0, 1, 0, 8, 0, 0, 0, 0, -1255.45, 1486.72, 68.5583, 2.39657, 'Bonechewer Beastmaster - In Combat - Summon "<a href="http://wowhead.com/npc=17280">Shattered Hand Warhound</a>" (No Repeat)'),
  (@ENTRY, 0, 5, 6, 61, 0, 100, 1, 0, 0, 0, 0, 12, 17280, 4, 20000, 0, 1, 0, 8, 0, 0, 0, 0, -1257.07, 1482.1, 68.5662, 2.42249, 'Bonechewer Beastmaster - In Combat - Summon "<a href="http://wowhead.com/npc=17280">Shattered Hand Warhound</a>" (No Repeat)'),
  (@ENTRY, 0, 6, 0, 61, 0, 100, 1, 0, 0, 0, 0, 12, 17280, 4, 20000, 0, 1, 0, 8, 0, 0, 0, 0, -1260.76, 1479.03, 68.5755, 1.8892, 'Bonechewer Beastmaster - In Combat - Summon "<a href="http://wowhead.com/npc=17280">Shattered Hand Warhound</a>" (No Repeat)'),
  (@ENTRY, 0, 7, 0, 61, 0, 100, 512, 0, 0, 0, 0, 14, 0, 100, 0, 0, 0, 0, 17, 0, 0, 100, 0, 0, 0, 0, 0, 'Bonechewer Beastmaster - In Combat - Decrease All Threat By 0% (While Charmed)'),
  (@ENTRY, 0, 8, 0, 15, 0, 100, 0, 20, 5000, 7500, 0, 85, 22890, 0, 0, 0, 0, 0, 9, 0, 17280, 0, 20, 0, 0, 0, 0, 'Bonechewer Beastmaster - On Friendly CCed - Invoker Cast "<a href="http://wowhead.com/spell=22890">Undo Crowd Control</a>" ');

-- NPC 622
SET @ENTRY = 622;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 2, 0, 0, 2200, 3800, 11, 6660, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Goblin Engineer - In Combat - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 2, 500, 4500, 67800, 89000, 11, 3605, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Goblin Engineer - In Combat - Cast "<a href="http://wowhead.com/spell=3605">Summon Remote-Controlled Golem</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 3, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Goblin Engineer - Between 0-15% HP - Flee For Assist (No Repeat and  Normal Dungeon)');

-- NPC 6002
SET @ENTRY = 6002;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20823, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nethergarde Riftwatcher - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 9000, 14000, 14000, 18000, 11, 11975, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Nethergarde Riftwatcher - In Combat - Cast "<a href="http://wowhead.com/spell=11975">Arcane Explosion</a>" '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Nethergarde Riftwatcher - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 2335
SET @ENTRY = 2335;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magistrate Burnside - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 9, 0, 100, 0, 0, 8, 12000, 15000, 11, 11969, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Magistrate Burnside - Within 0-8 Range - Cast "<a href="http://wowhead.com/spell=11969">Fire Nova</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 5000, 7000, 16000, 20000, 11, 7739, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magistrate Burnside - In Combat - Cast "<a href="http://wowhead.com/spell=7739">Inferno Shell</a>" '),
  (@ENTRY, 0, 3, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Magistrate Burnside - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 24657
SET @ENTRY = 24657;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;

-- NPC 8298
SET @ENTRY = 8298;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20824, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Akubar the Seer - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 9, 0, 100, 0, 0, 30, 13800, 13800, 11, 20831, 0, 0, 0, 0, 0, 5, 0, 30, 1, 0, 0, 0, 0, 0, 'Akubar the Seer - Within 0-30 Range - Cast "<a href="http://wowhead.com/spell=20831">Chain Lightning</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 3000, 5000, 25700, 31300, 11, 11436, 0, 0, 0, 0, 0, 5, 0, 30, 1, 0, 0, 0, 0, 0, 'Akubar the Seer - In Combat - Cast "<a href="http://wowhead.com/spell=11436">Slow</a>" ');

-- NPC 18638
SET @ENTRY = 18638;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 2, 0, 0, 0, 0, 58, 1, 12471, 3000, 3250, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Zealot - On AI Initialize - Install Caster Template (Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 37, 0, 100, 4, 0, 0, 0, 0, 58, 1, 15472, 3000, 3250, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Zealot - On AI Initialize - Install Caster Template (Heroic Dungeon)'),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 40, 0, 0, 11, 33499, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Zealot - Between 0-40% HP - Cast "<a href="http://wowhead.com/spell=33499">Shape of the Beast</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 23, 0, 100, 0, 33499, 1, 4500, 15000, 75, 33958, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Zealot - On Has Aura "<a href="http://wowhead.com/spell=33499">Shape of the Beast</a>" - Add Aura "<a href="http://wowhead.com/spell=33958">Frenzy</a>" '),
  (@ENTRY, 0, 4, 0, 25, 0, 100, 0, 0, 0, 0, 0, 28, 33499, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cabal Zealot - On Reset - Remove Aura "<a href="http://wowhead.com/spell=33499">Shape of the Beast</a>" ');

-- NPC 17962
SET @ENTRY = 17962;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 10000, 20000, 10000, 20000, 11, 33787, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Collaborator - In Combat - Cast "<a href="http://wowhead.com/spell=33787">Cripple</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 0, 15000, 5000, 15000, 11, 19130, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Collaborator - In Combat - Cast "<a href="http://wowhead.com/spell=19130">Revenge</a>" '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 15, 120000, 120000, 11, 8269, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Collaborator - Between 0-15% HP - Cast "<a href="http://wowhead.com/spell=8269">Enrage</a>" (No Repeat)'),
  (@ENTRY, 0, 4, 0, 25, 0, 100, 0, 0, 0, 0, 0, 28, 8269, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilfang Collaborator - On Reset - Remove Aura "<a href="http://wowhead.com/spell=8269">Enrage</a>" ');

-- NPC 9241
SET @ENTRY = 9241;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 515, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 515, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 15795, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - On Aggro - Cast "<a href="http://wowhead.com/spell=15795">Throw</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 3900, 11, 15795, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=15795">Throw</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 3900, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 7, 9, 1, 100, 514, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 25-80 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 61, 1, 100, 514, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 25-80 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 10, 9, 1, 100, 514, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 0-5 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 2, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 0-5 Range - Set Sheath Melee (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 9, 61, 1, 100, 514, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 0-5 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 12, 9, 1, 100, 514, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 5-15 Range - Disable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 61, 1, 100, 514, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 5-15 Range - Stop Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 9, 0, 100, 2, 5, 30, 9000, 13000, 11, 16001, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=16001">Impale</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 14, 0, 9, 0, 100, 2, 5, 30, 9000, 13000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)'),
  (@ENTRY, 0, 15, 0, 0, 0, 100, 2, 5000, 10000, 22000, 26000, 11, 6016, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - In Combat - Cast "<a href="http://wowhead.com/spell=6016">Pierce Armor</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 16, 0, 2, 0, 100, 515, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 515, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 18, 0, 2, 0, 100, 3, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - Between 0-15% HP - Flee For Assist (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 19, 0, 7, 0, 100, 515, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 20, 0, 7, 0, 100, 3, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Headhunter - On Evade - Set Sheath Melee (No Repeat and  Normal Dungeon)');

-- NPC 2376
SET @ENTRY = 2376;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 9532, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Oracle - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 0, 0, 25, 25000, 35000, 11, 939, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Oracle - Between 0-25% HP - Cast "<a href="http://wowhead.com/spell=939">Healing Wave</a>" '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Torn Fin Oracle - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 7290
SET @ENTRY = 7290;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 515, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 515, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 6660, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - On Aggro - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 3900, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 3900, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 7, 9, 1, 100, 514, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Within 25-80 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 61, 1, 100, 514, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Within 25-80 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 10, 9, 1, 100, 514, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Within 0-5 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 2, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Within 0-5 Range - Set Sheath Melee (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 9, 61, 1, 100, 514, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Within 0-5 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 12, 9, 1, 100, 514, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Within 5-15 Range - Disable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 61, 1, 100, 514, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Within 5-15 Range - Stop Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 14, 0, 1, 100, 2, 9000, 13000, 30000, 36000, 11, 6685, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - In Combat - Cast "<a href="http://wowhead.com/spell=6685">Piercing Shot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 14, 0, 61, 1, 100, 2, 9000, 13000, 30000, 36000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - In Combat - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 15, 0, 2, 0, 100, 515, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 16, 0, 2, 0, 100, 515, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 3, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - Between 0-15% HP - Flee For Assist (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 18, 0, 7, 0, 100, 515, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 19, 0, 7, 0, 100, 3, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowforge Sharpshooter - On Evade - Set Sheath Melee (No Repeat and  Normal Dungeon)');

-- NPC 6008
SET @ENTRY = 6008;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 1, 1000, 1000, 0, 0, 11, 5108, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowsworn Warlock - Out of Combat - Cast "<a href="http://wowhead.com/spell=5108">Voidwalker</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20825, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowsworn Warlock - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 5000, 8000, 30000, 45000, 11, 11980, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowsworn Warlock - In Combat - Cast "<a href="http://wowhead.com/spell=11980">Curse of Weakness</a>" '),
  (@ENTRY, 0, 3, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowsworn Warlock - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 19580
SET @ENTRY = 19580;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;

-- NPC 17150
SET @ENTRY = 17150;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 13901, 2500, 2800, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vir&#039;aani Arcanist - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 23, 0, 100, 0, 33839, 0, 10000, 20000, 11, 33839, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vir&#039;aani Arcanist - On Missing Aura "<a href="http://wowhead.com/spell=33839">Vir"aani Concentration</a>" - Cast "<a href="http://wowhead.com/spell=33839">Vir"aani Concentration</a>" '),
  (@ENTRY, 0, 2, 0, 9, 0, 100, 1, 0, 10, 5000, 1000, 11, 13901, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Vir&#039;aani Arcanist - Within 0-10 Range - Cast "<a href="http://wowhead.com/spell=13901">Arcane Bolt</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 9, 0, 100, 1, 0, 5, 15000, 30000, 11, 14514, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Vir&#039;aani Arcanist - Within 0-5 Range - Cast "<a href="http://wowhead.com/spell=14514">Blink</a>" (No Repeat)'),
  (@ENTRY, 0, 4, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Vir&#039;aani Arcanist - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 1725
SET @ENTRY = 1725;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 519, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 519, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 7, 0, 0, 0, 0, 11, 6660, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - On Aggro - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (No Repeat, Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 519, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 6, 5, 30, 2200, 3800, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 6, 5, 30, 2200, 3800, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 7, 9, 1, 100, 518, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Within 25-80 Range - Enable Combat Movement (Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 61, 1, 100, 518, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Within 25-80 Range - Start Attacking (Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 10, 9, 1, 100, 518, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Within 0-5 Range - Enable Combat Movement (Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 6, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Within 0-5 Range - Set Sheath Melee (Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 9, 61, 1, 100, 518, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Within 0-5 Range - Start Attacking (Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 12, 9, 1, 100, 518, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Within 5-15 Range - Disable Combat Movement (Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 61, 1, 100, 518, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Within 5-15 Range - Stop Attacking (Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 2, 0, 100, 519, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 14, 0, 2, 0, 100, 519, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 15, 0, 2, 0, 100, 7, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - Between 0-15% HP - Flee For Assist (No Repeat, Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 16, 0, 7, 0, 100, 519, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 17, 0, 7, 0, 100, 7, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Defias Watchman - On Evade - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)');

-- NPC 18154
SET @ENTRY = 18154;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18154, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ssslith - On Just Summoned - Start Waypoint 18154 '),
  (@ENTRY, 0, 1, 0, 40, 0, 100, 0, 4, 18154, 0, 0, 80, 1815401, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ssslith - On Waypoint 4 Reached - Run Script <a href="/smartai/script/1815401">1815401</a> '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 2500, 5000, 15000, 25000, 11, 12674, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ssslith - In Combat - Cast "<a href="http://wowhead.com/spell=12674">Frost Nova</a>" '),
  (@ENTRY, 0, 3, 0, 6, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 10, 0, 62926, 17877, 30, 0, 0, 0, 0, 'Ssslith - On Death - Increase Phase By 1 ');

-- NPC 2276
SET @ENTRY = 2276;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 23, 0, 100, 0, 12544, 0, 15000, 30000, 11, 12544, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magistrate Henry Maleb - On Missing Aura "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" - Cast "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" '),
  (@ENTRY, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magistrate Henry Maleb - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 2, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 12737, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magistrate Henry Maleb - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 3, 0, 9, 0, 100, 0, 0, 8, 12000, 15000, 11, 15531, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magistrate Henry Maleb - Within 0-8 Range - Cast "<a href="http://wowhead.com/spell=15531">Frost Nova</a>" '),
  (@ENTRY, 0, 4, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Magistrate Henry Maleb - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 2346
SET @ENTRY = 2346;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 9734, 2500, 3000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dun Garok Priest - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 74, 0, 100, 0, 0, 75, 15000, 21000, 11, 11642, 1, 0, 0, 0, 0, 9, 21, 0, 0, 40, 0, 0, 0, 0, 'Dun Garok Priest - On Friendly Between 0-75% HP - Cast "<a href="http://wowhead.com/spell=11642">Heal</a>" '),
  (@ENTRY, 0, 2, 0, 12, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Dun Garok Priest - Target Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 2373
SET @ENTRY = 2373;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20805, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mudsnout Shaman - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 74, 0, 100, 0, 0, 75, 14000, 19000, 11, 939, 1, 0, 0, 0, 0, 9, 21, 0, 0, 40, 0, 0, 0, 0, 'Mudsnout Shaman - On Friendly Between 0-75% HP - Cast "<a href="http://wowhead.com/spell=939">Healing Wave</a>" '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Mudsnout Shaman - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 2387
SET @ENTRY = 2387;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 23, 0, 100, 0, 12544, 0, 15000, 30000, 11, 12544, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hillsbrad Councilman - On Missing Aura "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" - Cast "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" '),
  (@ENTRY, 0, 1, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20806, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hillsbrad Councilman - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 2, 0, 9, 0, 100, 0, 0, 10, 25000, 25000, 11, 122, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Hillsbrad Councilman - Within 0-10 Range - Cast "<a href="http://wowhead.com/spell=122">Frost Nova</a>" '),
  (@ENTRY, 0, 3, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hillsbrad Councilman - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 2706
SET @ENTRY = 2706;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 10, 0, 100, 0, 0, 8, 5000, 5000, 39, 30, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tor&#039;gan - Within 0-8 Range OOC LoS - Call For Help ');

-- NPC 8296
SET @ENTRY = 8296;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20825, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mojo the Twisted - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 9, 0, 100, 0, 0, 30, 9000, 14000, 11, 17228, 0, 0, 0, 0, 0, 5, 0, 30, 1, 0, 0, 0, 0, 0, 'Mojo the Twisted - Within 0-30 Range - Cast "<a href="http://wowhead.com/spell=17228">Shadow Bolt Volley</a>" ');

-- NPC 6906
SET @ENTRY = 6906;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 515, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 515, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 15620, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - On Aggro - Cast "<a href="http://wowhead.com/spell=15620">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 3900, 11, 15620, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=15620">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 3900, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 7, 9, 1, 100, 514, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Within 25-80 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 61, 1, 100, 514, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Within 25-80 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 10, 9, 1, 100, 514, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Within 0-5 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 2, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Within 0-5 Range - Set Sheath Melee (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 9, 61, 1, 100, 514, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Within 0-5 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 12, 9, 1, 100, 514, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Within 5-15 Range - Disable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 61, 1, 100, 514, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Within 5-15 Range - Stop Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 0, 0, 100, 2, 4000, 7000, 9000, 13000, 11, 14516, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - In Combat - Cast "<a href="http://wowhead.com/spell=14516">Strike</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 14, 0, 2, 0, 100, 515, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 15, 0, 2, 0, 100, 515, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 16, 0, 2, 0, 100, 3, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - Between 0-15% HP - Flee For Assist (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 17, 0, 7, 0, 100, 515, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 18, 0, 7, 0, 100, 3, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baelog - On Evade - Set Sheath Melee (No Repeat and  Normal Dungeon)');

-- NPC 7070
SET @ENTRY = 7070;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 25054, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Condemned Cleric - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 9, 0, 100, 0, 0, 40, 18000, 21000, 11, 15586, 1, 0, 0, 0, 0, 102, 5, 40, 75, 0, 0, 0, 0, 0, 'Condemned Cleric - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=15586">Heal</a>" ');

-- NPC 17670
SET @ENTRY = 17670;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 519, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 519, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 15620, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - On Aggro - Cast "<a href="http://wowhead.com/spell=15620">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 5000, 11, 15620, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=15620">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 5, 0, 0, 0, 0, 11, 22907, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - On Aggro - Cast "<a href="http://wowhead.com/spell=22907">Shoot</a>" (No Repeat and  Heroic Dungeon)'),
  (@ENTRY, 0, 7, 0, 4, 0, 100, 517, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - On Aggro - Increase Phase By 1 (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 8, 9, 9, 1, 100, 4, 5, 30, 2300, 5000, 11, 22907, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=22907">Shoot</a>" (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 4, 5, 30, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 5-30 Range - Set Sheath Ranged (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 11, 9, 1, 100, 519, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 25-80 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 0, 61, 1, 100, 519, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 25-80 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 14, 9, 1, 100, 519, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 0-5 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 61, 1, 100, 7, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 0-5 Range - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 14, 13, 61, 1, 100, 519, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 0-5 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 15, 16, 9, 1, 100, 519, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 5-15 Range - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 16, 0, 61, 1, 100, 519, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 5-15 Range - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 17, 0, 0, 0, 100, 2, 7000, 12000, 60000, 70000, 11, 34100, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - In Combat - Cast "<a href="http://wowhead.com/spell=34100">Volley</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 18, 0, 0, 0, 100, 2, 7000, 12000, 60000, 70000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - In Combat - Set Sheath Ranged (Normal Dungeon)'),
  (@ENTRY, 0, 19, 0, 0, 0, 100, 4, 7000, 9000, 60000, 65000, 11, 35950, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - In Combat - Cast "<a href="http://wowhead.com/spell=35950">Volley</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 20, 0, 0, 0, 100, 4, 7000, 9000, 60000, 65000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - In Combat - Set Sheath Ranged (Heroic Dungeon)'),
  (@ENTRY, 0, 21, 0, 9, 0, 100, 2, 5, 30, 12000, 16000, 11, 30932, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=30932">Impaling Bolt</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 22, 0, 9, 0, 100, 2, 5, 30, 12000, 16000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)'),
  (@ENTRY, 0, 23, 0, 9, 0, 100, 4, 5, 30, 12000, 16000, 11, 40248, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=40248">Impaling Bolt</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 24, 0, 9, 0, 100, 4, 5, 30, 12000, 16000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - Within 5-30 Range - Set Sheath Ranged (Heroic Dungeon)'),
  (@ENTRY, 0, 25, 0, 7, 0, 100, 519, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 26, 0, 7, 0, 100, 7, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Hand Houndmaster - On Evade - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)');

-- NPC 17820
SET @ENTRY = 17820;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 519, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 519, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 16100, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - On Aggro - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 5000, 11, 16100, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 5, 0, 0, 0, 0, 11, 22907, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - On Aggro - Cast "<a href="http://wowhead.com/spell=22907">Shoot</a>" (No Repeat and  Heroic Dungeon)'),
  (@ENTRY, 0, 7, 0, 4, 0, 100, 517, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - On Aggro - Increase Phase By 1 (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 8, 9, 9, 1, 100, 4, 5, 30, 2300, 5000, 11, 22907, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=22907">Shoot</a>" (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 4, 5, 30, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 5-30 Range - Set Sheath Ranged (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 11, 9, 1, 100, 519, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 25-80 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 0, 61, 1, 100, 519, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 25-80 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 14, 9, 1, 100, 519, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 0-5 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 61, 1, 100, 7, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 0-5 Range - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 14, 13, 61, 1, 100, 519, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 0-5 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 15, 16, 9, 1, 100, 519, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 5-15 Range - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 16, 0, 61, 1, 100, 519, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 5-15 Range - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 17, 18, 9, 1, 100, 2, 5, 30, 9000, 15000, 11, 31942, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=31942">Multi-Shot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 18, 0, 61, 1, 100, 2, 5, 30, 9000, 15000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 19, 20, 9, 1, 100, 4, 5, 30, 9000, 15000, 11, 38383, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=38383">Multi-Shot</a>" (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 20, 0, 61, 1, 100, 4, 5, 30, 9000, 15000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Within 5-30 Range - Set Sheath Ranged (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 21, 0, 2, 0, 100, 519, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 22, 0, 2, 0, 100, 519, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 23, 0, 2, 0, 100, 7, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - Between 0-15% HP - Flee For Assist (No Repeat, Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 24, 0, 7, 0, 100, 519, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 25, 0, 7, 0, 100, 7, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Durnholde Rifleman - On Evade - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)');

-- NPC 15970
SET @ENTRY = 15970;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Instructor Antheol - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Instructor Antheol - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 22431
SET @ENTRY = 22431;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 62, 0, 100, 512, 10683, 1, 0, 0, 80, 2243102, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anchorite Barada - On Gossip 10683 Option 1 Selected - Run Script <a href="/smartai/script/2243102">2243102</a> (While Charmed)'),
  (@ENTRY, 0, 1, 0, 40, 0, 100, 512, 2, 22431, 0, 0, 45, 0, 1, 0, 0, 0, 0, 9, 0, 22432, 0, 30, 0, 0, 0, 0, 'Anchorite Barada - On Waypoint 2 Reached - Set Data 0 1 (While Charmed)'),
  (@ENTRY, 0, 2, 0, 40, 0, 100, 512, 4, 22431, 0, 0, 80, 2243101, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anchorite Barada - On Waypoint 4 Reached - Run Script <a href="/smartai/script/2243101">2243101</a> (While Charmed)'),
  (@ENTRY, 0, 3, 0, 60, 1, 100, 0, 20000, 30000, 20000, 30000, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anchorite Barada - On Update - Say Line 2 (Phase 1)'),
  (@ENTRY, 0, 4, 0, 60, 1, 100, 512, 172000, 172000, 900000, 900000, 80, 2243104, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anchorite Barada - On Update - Run Script <a href="/smartai/script/2243104">2243104</a> (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 40, 0, 100, 512, 5, 22431, 0, 0, 80, 2243103, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anchorite Barada - On Waypoint 5 Reached - Run Script <a href="/smartai/script/2243103">2243103</a> (While Charmed)');

-- NPC 16459
SET @ENTRY = 16459;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 512, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 30, 0, 0, 0, 0, 0, 'Wanton Hostess - On Aggro - Set Event Phase 1 (While Charmed)'),
  (@ENTRY, 0, 1, 0, 103, 1, 100, 1, 1, 0, 0, 0, 11, 29485, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wanton Hostess - On Enter Phase 1 - Cast "<a href="http://wowhead.com/spell=29485">Alluring Aura</a>" (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 2, 0, 2, 1, 100, 1, 1, 50, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wanton Hostess - Between 1-50% HP - Set Event Phase 2 (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 3, 7, 103, 2, 100, 1, 2, 0, 0, 0, 11, 29472, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wanton Hostess - On Enter Phase 2 - Cast "<a href="http://wowhead.com/spell=29472">Wanton Hostess Transform</a>" (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 4, 0, 0, 2, 100, 1, 0, 0, 0, 0, 11, 29505, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wanton Hostess - In Combat - Cast "<a href="http://wowhead.com/spell=29505">Banshee Shriek</a>" (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 5, 0, 0, 2, 100, 0, 10000, 15000, 15000, 25000, 11, 29477, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Wanton Hostess - In Combat - Cast "<a href="http://wowhead.com/spell=29477">Banshee Wail</a>" (Phase 2)'),
  (@ENTRY, 0, 6, 0, 61, 2, 100, 1, 0, 0, 0, 0, 11, 29486, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wanton Hostess - On Enter Phase 2 - Cast "<a href="http://wowhead.com/spell=29486">Bewitching Aura</a>" (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 7, 6, 61, 2, 100, 1, 0, 0, 0, 0, 28, 29485, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wanton Hostess - On Enter Phase 2 - Remove Aura "<a href="http://wowhead.com/spell=29485">Alluring Aura</a>" (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 8, 0, 25, 0, 100, 0, 0, 0, 0, 0, 28, 29472, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wanton Hostess - On Reset - Remove Aura "<a href="http://wowhead.com/spell=29472">Wanton Hostess Transform</a>" '),
  (@ENTRY, 0, 9, 0, 25, 0, 100, 512, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wanton Hostess - On Reset - Set Event Phase 0 (While Charmed)'),
  (@ENTRY, 0, 10, 0, 25, 0, 100, 0, 0, 0, 0, 0, 28, 29486, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wanton Hostess - On Reset - Remove Aura "<a href="http://wowhead.com/spell=29486">Bewitching Aura</a>" ');

-- NPC 18152
SET @ENTRY = 18152;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 34, 0, 100, 1, 8, 0, 0, 0, 11, 24983, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Reached Point 0 - Cast "<a href="http://wowhead.com/spell=24983">Baby Murloc Passive</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 60, 0, 100, 1, 2500, 2500, 1, 1, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1170.34, 8144.97, 19.1958, 6.05553, 'Baby Murloc - On Update - Move To Pos (No Repeat)'),
  (@ENTRY, 0, 2, 0, 54, 0, 100, 0, 0, 0, 0, 0, 33, 18152, 0, 0, 0, 0, 0, 17, 0, 0, 30, 0, 0, 0, 0, 0, 'Baby Murloc - On Just Summoned - Quest Credit "<a href="http://wowhead.com/quest=18152">Baby Murloc</a>" '),
  (@ENTRY, 0, 3, 0, 34, 0, 100, 0, 8, 0, 0, 0, 17, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Reached Point 0 - Set Emote State 10 '),
  (@ENTRY, 0, 4, 0, 60, 0, 100, 1, 19000, 19000, 1, 1, 41, 0, 0, 0, 0, 0, 0, 13, 0, 182164, 0, 60, 0, 0, 0, 0, 'Baby Murloc - On Update - Despawn Instant (No Repeat)');

-- NPC 7667
SET @ENTRY = 7667;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 23, 0, 100, 0, 12544, 0, 1800000, 1800000, 11, 12544, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lady Sevine - On Missing Aura "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" - Cast "<a href="http://wowhead.com/spell=12544">Frost Armor</a>" '),
  (@ENTRY, 0, 1, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 12739, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lady Sevine - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 9000, 12000, 24000, 27000, 11, 12742, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Lady Sevine - In Combat - Cast "<a href="http://wowhead.com/spell=12742">Immolate</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 2000, 5000, 30000, 45000, 11, 12741, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lady Sevine - In Combat - Cast "<a href="http://wowhead.com/spell=12741">Curse of Weakness</a>" '),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 0, 7000, 9000, 15000, 25000, 11, 12740, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lady Sevine - In Combat - Cast "<a href="http://wowhead.com/spell=12740">Summon Infernal Servant</a>" ');

-- NPC 17892
SET @ENTRY = 17892;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 519, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 7, 1000, 1000, 0, 0, 11, 31326, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Out of Combat - Cast "<a href="http://wowhead.com/spell=31326">Corrupt Medivh</a>" (No Repeat, Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 2, 0, 0, 0, 20, 7, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - In Combat - Say Line 0 (No Repeat, Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 519, 0, 0, 0, 0, 28, 31326, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - On Aggro - Remove Aura "<a href="http://wowhead.com/spell=31326">Corrupt Medivh</a>" (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 0, 4, 0, 100, 519, 0, 0, 0, 0, 30, 1, 2, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - On Aggro - Set Random Phase (1, 2 and 4) (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 5, 8, 4, 2, 100, 3, 0, 0, 0, 0, 11, 15497, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - On Aggro - Cast "<a href="http://wowhead.com/spell=15497">Frostbolt</a>" (No Repeat and  Normal Dungeon)(Phase 2)'),
  (@ENTRY, 0, 6, 0, 9, 2, 100, 2, 0, 40, 2900, 5400, 11, 15497, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=15497">Frostbolt</a>" (Normal Dungeon)(Phase 2)'),
  (@ENTRY, 0, 8, 0, 61, 2, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 9, 0, 9, 2, 100, 4, 0, 40, 2900, 5400, 11, 12675, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=12675">Frostbolt</a>" (Heroic Dungeon)(Phase 2)'),
  (@ENTRY, 0, 10, 11, 3, 2, 100, 519, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Between 0-15% MP - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 11, 0, 61, 2, 100, 519, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Between 0-15% MP - Increase Phase By 1 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 12, 0, 9, 2, 100, 519, 35, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Within 35-80 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 13, 0, 9, 2, 100, 519, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Within 5-15 Range - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 14, 0, 9, 2, 100, 519, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Within 0-5 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 15, 0, 0, 2, 100, 2, 3700, 12900, 33800, 39800, 11, 15063, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - In Combat - Cast "<a href="http://wowhead.com/spell=15063">Frost Nova</a>" (Normal Dungeon)(Phase 2)'),
  (@ENTRY, 0, 16, 0, 0, 2, 100, 4, 3600, 8300, 22200, 25700, 11, 15531, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - In Combat - Cast "<a href="http://wowhead.com/spell=15531">Frost Nova</a>" (Heroic Dungeon)(Phase 2)'),
  (@ENTRY, 0, 17, 0, 3, 4, 100, 518, 30, 100, 100, 100, 23, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Between 30-100% MP - Decrease Phase By 0 (Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 3)'),
  (@ENTRY, 0, 18, 21, 4, 8, 100, 3, 0, 0, 0, 0, 11, 15124, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - On Aggro - Cast "<a href="http://wowhead.com/spell=15124">Arcane Bolt</a>" (No Repeat and  Normal Dungeon)(Phase 4)'),
  (@ENTRY, 0, 19, 0, 9, 8, 100, 2, 0, 40, 2900, 5400, 11, 15124, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=15124">Arcane Bolt</a>" (Normal Dungeon)(Phase 4)'),
  (@ENTRY, 0, 21, 0, 61, 8, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)(Phase 4)'),
  (@ENTRY, 0, 22, 0, 9, 8, 100, 4, 0, 40, 1200, 3400, 11, 15230, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=15230">Arcane Bolt</a>" (Heroic Dungeon)(Phase 4)'),
  (@ENTRY, 0, 23, 24, 3, 8, 100, 519, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Between 0-15% MP - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 4)'),
  (@ENTRY, 0, 24, 0, 61, 8, 100, 519, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Between 0-15% MP - Increase Phase By 1 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 4)'),
  (@ENTRY, 0, 25, 0, 9, 8, 100, 519, 35, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Within 35-80 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 4)'),
  (@ENTRY, 0, 26, 0, 9, 8, 100, 519, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Within 5-15 Range - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 4)'),
  (@ENTRY, 0, 27, 0, 9, 8, 100, 519, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Within 0-5 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 4)'),
  (@ENTRY, 0, 28, 0, 0, 8, 100, 2, 8600, 18200, 9500, 10100, 11, 33860, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - In Combat - Cast "<a href="http://wowhead.com/spell=33860">Arcane Explosion</a>" (Normal Dungeon)(Phase 4)'),
  (@ENTRY, 0, 29, 0, 0, 8, 100, 2, 8600, 18200, 8000, 10100, 11, 33623, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - In Combat - Cast "<a href="http://wowhead.com/spell=33623">Arcane Explosion</a>" (Normal Dungeon)(Phase 4)'),
  (@ENTRY, 0, 30, 0, 3, 0, 100, 518, 30, 100, 100, 100, 23, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - Between 30-100% MP - Decrease Phase By 0 (Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 31, 0, 7, 0, 100, 519, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 32, 0, 7, 0, 100, 7, 0, 0, 0, 0, 11, 31326, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Infinite Chronomancer - On Evade - Cast "<a href="http://wowhead.com/spell=31326">Corrupt Medivh</a>" (No Repeat, Normal Dungeon and  Heroic Dungeon)');

-- NPC 15547
SET @ENTRY = 15547;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 10000, 15000, 20000, 30000, 11, 29320, 0, 0, 0, 0, 0, 25, 0, 45, 1, 1, 0, 0, 0, 0, 'Spectral Charger - In Combat - Cast "<a href="http://wowhead.com/spell=29320">Charge</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 15000, 25000, 11, 29321, 0, 0, 0, 0, 0, 17, 0, 0, 20, 0, 0, 0, 0, 0, 'Spectral Charger - In Combat - Cast "<a href="http://wowhead.com/spell=29321">Fear</a>" ');

-- NPC 6009
SET @ENTRY = 6009;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20825, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowsworn Dreadweaver - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 8000, 11000, 19000, 24000, 11, 8994, 32, 0, 0, 0, 0, 6, 0, 40, 1, 0, 0, 0, 0, 0, 'Shadowsworn Dreadweaver - In Combat - Cast "<a href="http://wowhead.com/spell=8994">Banish</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 12000, 16000, 30000, 45000, 11, 7098, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Shadowsworn Dreadweaver - In Combat - Cast "<a href="http://wowhead.com/spell=7098">Curse of Mending</a>" ');

-- NPC 6221
SET @ENTRY = 6221;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 1, 0, 100, 513, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Out of Combat - Disable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Out of Combat - Stop Attacking (While Charmed)'),
  (@ENTRY, 0, 2, 0, 1, 0, 100, 1, 1000, 1000, 0, 0, 11, 7165, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Out of Combat - Cast "<a href="http://wowhead.com/spell=7165">Battle Stance</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 4, 4, 0, 100, 0, 0, 0, 0, 0, 11, 6660, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - On Aggro - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" '),
  (@ENTRY, 0, 4, 0, 61, 0, 100, 512, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - On Aggro - Increase Phase By 1 (While Charmed)'),
  (@ENTRY, 0, 5, 6, 9, 0, 100, 0, 5, 30, 2300, 3900, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" '),
  (@ENTRY, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Within 5-30 Range - Set Sheath Ranged '),
  (@ENTRY, 0, 7, 8, 9, 0, 100, 512, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Within 25-80 Range - Enable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 8, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Within 25-80 Range - Start Attacking (While Charmed)'),
  (@ENTRY, 0, 9, 0, 9, 0, 100, 512, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Within 0-5 Range - Enable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 10, 11, 9, 0, 100, 0, 0, 0, 0, 500, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Within 0-0 Range - Set Sheath Melee '),
  (@ENTRY, 0, 11, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Within 0-0 Range - Start Attacking (While Charmed)'),
  (@ENTRY, 0, 12, 13, 9, 0, 100, 512, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Within 5-15 Range - Disable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 13, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Within 5-15 Range - Stop Attacking (While Charmed)'),
  (@ENTRY, 0, 14, 0, 9, 0, 100, 0, 0, 5, 17000, 23000, 11, 9080, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Within 0-5 Range - Cast "<a href="http://wowhead.com/spell=9080">Hamstring</a>" '),
  (@ENTRY, 0, 15, 0, 0, 0, 100, 0, 7000, 9000, 13000, 16000, 11, 25712, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - In Combat - Cast "<a href="http://wowhead.com/spell=25712">Heroic Strike</a>" '),
  (@ENTRY, 0, 16, 0, 2, 0, 100, 0, 0, 30, 30000, 45000, 11, 2055, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Between 0-30% HP - Cast "<a href="http://wowhead.com/spell=2055">Heal</a>" '),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 513, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Between 0-15% HP - Increase Phase By 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 18, 19, 2, 0, 100, 513, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Between 0-15% HP - Enable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 19, 0, 61, 0, 100, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - Between 0-15% HP - Flee For Assist '),
  (@ENTRY, 0, 20, 0, 7, 0, 100, 0, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Addled Leper - On Evade - Set Sheath Melee ');

-- NPC 17311
SET @ENTRY = 17311;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 62, 0, 100, 0, 17311, 0, 0, 0, 5, 18, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cowlen - On Gossip 17311 Option 0 Selected - Play Emote 18 '),
  (@ENTRY, 0, 1, 0, 62, 0, 100, 0, 17313, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Cowlen - On Gossip 17313 Option 0 Selected - Close Gossip ');

-- NPC 7332
SET @ENTRY = 7332;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 515, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 515, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 6660, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - On Aggro - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 3900, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 3900, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 7, 9, 1, 100, 514, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Within 25-80 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 61, 1, 100, 514, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Within 25-80 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 10, 9, 1, 100, 514, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Within 0-5 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 2, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Within 0-5 Range - Set Sheath Melee (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 9, 61, 1, 100, 514, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Within 0-5 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 12, 9, 1, 100, 514, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Within 5-15 Range - Disable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 61, 1, 100, 514, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Within 5-15 Range - Stop Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 0, 0, 100, 2, 8000, 12000, 6000, 17000, 11, 11397, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - In Combat - Cast "<a href="http://wowhead.com/spell=11397">Diseased Shot</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 14, 0, 0, 0, 100, 2, 8000, 12000, 6000, 17000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - In Combat - Set Sheath Ranged (Normal Dungeon)'),
  (@ENTRY, 0, 15, 0, 2, 0, 100, 2, 0, 30, 120000, 120000, 11, 8599, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Between 0-30% HP - Cast "<a href="http://wowhead.com/spell=8599">Enrage</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 16, 0, 2, 0, 100, 2, 0, 30, 120000, 120000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Between 0-30% HP - Say Line 0 (Normal Dungeon)'),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 515, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 18, 0, 2, 0, 100, 515, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 19, 0, 2, 0, 100, 3, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - Between 0-15% HP - Flee For Assist (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 20, 0, 7, 0, 100, 515, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 21, 0, 7, 0, 100, 3, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Spearhide - On Evade - Set Sheath Melee (No Repeat and  Normal Dungeon)');

-- NPC 23486
SET @ENTRY = 23486;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;

-- NPC 8901
SET @ENTRY = 8901;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 515, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 515, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 3, 0, 0, 0, 0, 11, 9128, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - In Combat - Cast "<a href="http://wowhead.com/spell=9128">Battle Shout</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 6660, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - On Aggro - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 4, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 5, 6, 9, 1, 100, 2, 5, 30, 2200, 3800, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 61, 1, 100, 2, 5, 30, 2200, 3800, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 7, 8, 9, 1, 100, 514, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 25-80 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 0, 61, 1, 100, 514, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 25-80 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 11, 9, 1, 100, 514, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 0-5 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 10, 0, 61, 1, 100, 2, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - MISSING LINK - Set Sheath Melee (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 11, 9, 61, 1, 100, 514, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 0-5 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 13, 9, 1, 100, 514, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 5-15 Range - Disable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 61, 1, 100, 514, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 5-15 Range - Stop Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 14, 0, 0, 0, 100, 2, 4000, 6000, 12000, 15000, 11, 9080, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - In Combat - Cast "<a href="http://wowhead.com/spell=9080">Hamstring</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 15, 0, 0, 0, 100, 2, 8000, 11000, 6000, 9000, 11, 11976, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - In Combat - Cast "<a href="http://wowhead.com/spell=11976">Strike</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 16, 0, 2, 0, 100, 515, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 515, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 18, 0, 2, 0, 100, 3, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Between 0-15% HP - Flee For Assist (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 19, 0, 7, 0, 100, 515, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 20, 0, 7, 0, 100, 3, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - On Evade - Set Sheath Melee (No Repeat and  Normal Dungeon)');

-- NPC 8901
SET @ENTRY = 8901;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 515, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 515, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 3, 0, 0, 0, 0, 11, 9128, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - In Combat - Cast "<a href="http://wowhead.com/spell=9128">Battle Shout</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 6660, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - On Aggro - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 4, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 5, 6, 9, 1, 100, 2, 5, 30, 2200, 3800, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 61, 1, 100, 2, 5, 30, 2200, 3800, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 7, 8, 9, 1, 100, 514, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 25-80 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 0, 61, 1, 100, 514, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 25-80 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 11, 9, 1, 100, 514, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 0-5 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 10, 0, 61, 1, 100, 2, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 0-5 Range - Set Sheath Melee (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 11, 10, 61, 1, 100, 514, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 0-5 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 13, 9, 1, 100, 514, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 5-15 Range - Disable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 61, 1, 100, 514, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Within 5-15 Range - Stop Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 14, 0, 0, 0, 100, 2, 4000, 6000, 12000, 15000, 11, 9080, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - In Combat - Cast "<a href="http://wowhead.com/spell=9080">Hamstring</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 15, 0, 0, 0, 100, 2, 8000, 11000, 6000, 9000, 11, 11976, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - In Combat - Cast "<a href="http://wowhead.com/spell=11976">Strike</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 16, 0, 2, 0, 100, 515, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 515, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 18, 0, 2, 0, 100, 3, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - Between 0-15% HP - Flee For Assist (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 19, 0, 7, 0, 100, 515, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 20, 0, 7, 0, 100, 3, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Anvilrage Reservist - On Evade - Set Sheath Melee (No Repeat and  Normal Dungeon)');

-- NPC 9267
SET @ENTRY = 9267;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 515, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 515, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 15795, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - On Aggro - Cast "<a href="http://wowhead.com/spell=15795">Throw</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 3900, 11, 15795, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=15795">Throw</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 3900, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 7, 9, 1, 100, 514, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Within 25-80 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 61, 1, 100, 514, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Within 25-80 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 10, 9, 1, 100, 514, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Within 0-5 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 2, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Within 0-5 Range - Set Sheath Melee (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 9, 61, 1, 100, 514, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Within 0-5 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 12, 9, 1, 100, 514, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Within 5-15 Range - Disable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 61, 1, 100, 514, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Within 5-15 Range - Stop Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 0, 0, 100, 2, 6000, 9000, 9000, 12000, 11, 3391, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - In Combat - Cast "<a href="http://wowhead.com/spell=3391">Thrash</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 14, 0, 0, 0, 100, 2, 9000, 14000, 11000, 15000, 11, 11428, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - In Combat - Cast "<a href="http://wowhead.com/spell=11428">Knockdown</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 15, 0, 2, 0, 100, 515, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 16, 0, 2, 0, 100, 515, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 3, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - Between 0-15% HP - Flee For Assist (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 18, 0, 7, 0, 100, 515, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 19, 0, 7, 0, 100, 3, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Smolderthorn Axe Thrower - On Evade - Set Sheath Melee (No Repeat and  Normal Dungeon)');

-- NPC 18559
SET @ENTRY = 18559;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 2, 0, 0, 0, 0, 58, 2, 15547, 3000, 3500, 30, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - On AI Initialize - Install Turret Template (Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 2, 5000, 10000, 10000, 15000, 11, 31975, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - In Combat - Cast "<a href="http://wowhead.com/spell=31975">Serpent Sting</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 2, 0, 9, 0, 100, 0, 0, 5, 0, 500, 23, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - Within 0-5 Range - Increase Phase By 1 '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 4, 5000, 10000, 10000, 15000, 11, 35511, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - In Combat - Cast "<a href="http://wowhead.com/spell=35511">Serpent Sting</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 4, 0, 37, 0, 100, 4, 0, 0, 0, 0, 58, 2, 16100, 3000, 3500, 30, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - On AI Initialize - Install Turret Template (Heroic Dungeon)'),
  (@ENTRY, 0, 5, 0, 18, 0, 100, 4, 0, 100, 15000, 25000, 11, 37551, 32, 0, 0, 0, 0, 17, 0, 5, 35, 0, 0, 0, 0, 0, 'Phasing Stalker - Target Between 0-100% MP - Cast "<a href="http://wowhead.com/spell=37551">Viper Sting</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 7, 0, 23, 1, 100, 0, 32829, 0, 5000, 15000, 11, 32829, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - On Missing Aura "<a href="http://wowhead.com/spell=32829">Spirit Vengeance</a>" - Cast "<a href="http://wowhead.com/spell=32829">Spirit Vengeance</a>" (Phase 1)'),
  (@ENTRY, 0, 8, 0, 9, 1, 100, 1, 5, 40, 0, 500, 23, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Phasing Stalker - Within 5-40 Range - Decrease Phase By 0 (No Repeat)(Phase 1)');

-- NPC 18938
SET @ENTRY = 18938;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 11, 14313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Krexcil - On Aggro - Cast "<a href="http://wowhead.com/spell=14313">Summon Enraged Gryphon</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 14307, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Krexcil - On Aggro - Cast "<a href="http://wowhead.com/spell=14307">Summon Enraged Wyvern</a>" ');

-- NPC 10558
SET @ENTRY = 10558;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 515, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 515, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 16100, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - On Aggro - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 3900, 11, 16100, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 3900, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 7, 9, 1, 100, 514, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Within 25-80 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 61, 1, 100, 514, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Within 25-80 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 10, 9, 1, 100, 514, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Within 0-5 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 2, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Within 0-5 Range - Set Sheath Melee (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 9, 61, 1, 100, 514, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Within 0-5 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 12, 9, 1, 100, 514, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Within 5-15 Range - Disable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 61, 1, 100, 514, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Within 5-15 Range - Stop Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 0, 0, 100, 2, 9000, 14000, 9000, 14000, 11, 14443, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - In Combat - Cast "<a href="http://wowhead.com/spell=14443">Multi-Shot</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 14, 0, 0, 0, 100, 2, 9000, 14000, 9000, 14000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - In Combat - Set Sheath Ranged (Normal Dungeon)'),
  (@ENTRY, 0, 15, 0, 0, 0, 100, 2, 3000, 5000, 12000, 19000, 11, 16244, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - In Combat - Cast "<a href="http://wowhead.com/spell=16244">Demoralizing Shout</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 16, 0, 0, 0, 100, 2, 7000, 9000, 20000, 25000, 11, 16798, 1, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - In Combat - Cast "<a href="http://wowhead.com/spell=16798">Enchanting Lullaby</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 515, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 18, 0, 2, 0, 100, 515, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 19, 0, 2, 0, 100, 3, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - Between 0-15% HP - Flee For Assist (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 20, 0, 7, 0, 100, 515, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 21, 0, 7, 0, 100, 3, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Hearthsinger Forresten - On Evade - Set Sheath Melee (No Repeat and  Normal Dungeon)');

-- NPC 11454
SET @ENTRY = 11454;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 517, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Out of Combat - Disable Combat Movement (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 517, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Out of Combat - Stop Attacking (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 15, 5, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - On Aggro - Say Line 0 (No Repeat and  Heroic Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 5, 0, 0, 0, 0, 11, 16100, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - On Aggro - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (No Repeat and  Heroic Dungeon)'),
  (@ENTRY, 0, 4, 0, 4, 0, 100, 517, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - On Aggro - Increase Phase By 1 (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 5, 6, 9, 2, 100, 4, 5, 30, 2300, 3900, 11, 16100, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (Heroic Dungeon)(Phase 2)'),
  (@ENTRY, 0, 6, 0, 61, 2, 100, 4, 5, 30, 2300, 3900, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 5-30 Range - Set Sheath Ranged (Heroic Dungeon)(Phase 2)'),
  (@ENTRY, 0, 7, 8, 9, 2, 100, 516, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 25-80 Range - Enable Combat Movement (Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 8, 0, 61, 2, 100, 516, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 25-80 Range - Start Attacking (Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 9, 11, 9, 2, 100, 516, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 0-5 Range - Enable Combat Movement (Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 10, 0, 61, 2, 100, 4, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 0-5 Range - Set Sheath Melee (Heroic Dungeon)(Phase 2)'),
  (@ENTRY, 0, 11, 10, 61, 2, 100, 516, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 0-5 Range - Start Attacking (Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 12, 13, 9, 2, 100, 516, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 5-15 Range - Disable Combat Movement (Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 13, 0, 61, 2, 100, 516, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 5-15 Range - Stop Attacking (Heroic Dungeon and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 14, 15, 9, 1, 100, 6, 5, 30, 7800, 11400, 11, 18649, 40, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=18649">Shadow Shot</a>" (Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 15, 0, 61, 1, 100, 518, 5, 30, 7800, 11400, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 5-30 Range - Set Faction 0 (Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 16, 17, 9, 1, 100, 6, 5, 30, 9900, 13600, 11, 7896, 40, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=7896">Exploding Shot</a>" (Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 17, 0, 61, 1, 100, 518, 5, 30, 9900, 13600, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Within 5-30 Range - Set Faction 0 (Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 18, 0, 0, 1, 100, 6, 5000, 8000, 8000, 11000, 11, 11428, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - In Combat - Cast "<a href="http://wowhead.com/spell=11428">Knockdown</a>" (Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 19, 0, 2, 0, 100, 517, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Between 0-15% HP - Increase Phase By 1 (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 20, 0, 2, 0, 100, 517, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Between 0-15% HP - Enable Combat Movement (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 21, 0, 2, 0, 100, 5, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - Between 0-15% HP - Flee For Assist (No Repeat and  Heroic Dungeon)'),
  (@ENTRY, 0, 22, 0, 7, 0, 100, 517, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - On Evade - Set Event Phase 0 (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 23, 0, 7, 0, 100, 5, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wildspawn Betrayer - On Evade - Set Sheath Melee (No Repeat and  Heroic Dungeon)');

-- NPC 17085
SET @ENTRY = 17085;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 513, 4000, 4000, 1, 1, 80, 1708502, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Aeranas - On AI Initialize - Run Script <a href="/smartai/script/1708502">1708502</a> (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 513, 0, 25, 0, 0, 45, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Aeranas - Between 0-25% HP - Set Data 0 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 38, 0, 100, 512, 0, 1, 1, 1, 80, 1708501, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Aeranas - On Data Set 0 1 - Run Script <a href="/smartai/script/1708501">1708501</a> (While Charmed)'),
  (@ENTRY, 0, 3, 0, 20, 0, 100, 513, 9418, 0, 0, 0, 41, 20000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Aeranas - On Quest "<a href="http://wowhead.com/quest=9418">Avruu"s Orb</a>" Rewarded - Despawn In 20000ms (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 4, 0, 54, 0, 100, 513, 0, 0, 0, 0, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Aeranas - On Just Summoned - Set NPC Flag Quest Giver (No Repeat and  While Charmed)');

-- NPC 16332
SET @ENTRY = 16332;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 1, 0, 100, 513, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Out of Combat - Disable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Out of Combat - Stop Attacking (While Charmed)'),
  (@ENTRY, 0, 2, 3, 4, 0, 100, 0, 0, 0, 0, 0, 11, 6660, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - On Aggro - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" '),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 512, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - On Aggro - Increase Phase By 1 (While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 0, 100, 0, 5, 30, 2300, 3900, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" '),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Within 5-30 Range - Set Sheath Ranged '),
  (@ENTRY, 0, 6, 7, 9, 0, 100, 512, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Within 25-80 Range - Enable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 7, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Within 25-80 Range - Start Attacking (While Charmed)'),
  (@ENTRY, 0, 8, 9, 9, 0, 100, 512, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Within 0-5 Range - Enable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Within 0-5 Range - Set Sheath Melee '),
  (@ENTRY, 0, 10, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Within 0-5 Range - Start Attacking (While Charmed)'),
  (@ENTRY, 0, 11, 12, 9, 0, 100, 512, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Within 5-15 Range - Disable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 12, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Within 5-15 Range - Stop Attacking (While Charmed)'),
  (@ENTRY, 0, 13, 0, 9, 0, 100, 0, 0, 5, 5000, 9000, 11, 11976, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Within 0-5 Range - Cast "<a href="http://wowhead.com/spell=11976">Strike</a>" '),
  (@ENTRY, 0, 14, 0, 2, 0, 100, 513, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Between 0-15% HP - Increase Phase By 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 15, 16, 2, 0, 100, 513, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Between 0-15% HP - Enable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 16, 0, 61, 0, 100, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - Between 0-15% HP - Flee For Assist '),
  (@ENTRY, 0, 17, 0, 7, 0, 100, 0, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Darnassian Huntress - On Evade - Set Sheath Melee ');

-- NPC 18088
SET @ENTRY = 18088;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 34446, 5000, 5500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodscale Enchantress - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 90, 5000, 10000, 11, 33245, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodscale Enchantress - Between 0-90% HP - Cast "<a href="http://wowhead.com/spell=33245">Ice Barrier</a>" (No Repeat)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 6000, 8000, 16000, 22000, 11, 34787, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodscale Enchantress - In Combat - Cast "<a href="http://wowhead.com/spell=34787">Freezing Circle</a>" '),
  (@ENTRY, 0, 10, 0, 54, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18088, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodscale Enchantress - On Just Summoned - Start Waypoint 18088 '),
  (@ENTRY, 0, 11, 0, 38, 0, 100, 0, 1, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 10, 0, 62926, 17877, 50, 0, 0, 0, 0, 'Bloodscale Enchantress - On Data Set 1 1 - Start Attacking '),
  (@ENTRY, 0, 12, 0, 6, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 10, 0, 62926, 17877, 30, 0, 0, 0, 0, 'Bloodscale Enchantress - On Death - Increase Phase By 1 '),
  (@ENTRY, 0, 13, 0, 40, 0, 100, 0, 4, 18088, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodscale Enchantress - On Waypoint 4 Reached - Set Home Position ');

-- NPC 12996
SET @ENTRY = 12996;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 1, 0, 100, 513, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Out of Combat - Disable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Out of Combat - Stop Attacking (While Charmed)'),
  (@ENTRY, 0, 2, 3, 4, 0, 100, 0, 0, 0, 0, 0, 11, 6660, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - On Aggro - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" '),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 512, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - On Aggro - Increase Phase By 1 (While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 0, 100, 0, 5, 30, 2300, 3900, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=6660">Shoot</a>" '),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Within 5-30 Range - Set Sheath Ranged '),
  (@ENTRY, 0, 6, 7, 9, 0, 100, 512, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Within 25-80 Range - Enable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 7, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Within 25-80 Range - Start Attacking (While Charmed)'),
  (@ENTRY, 0, 8, 9, 9, 0, 100, 512, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Within 0-5 Range - Enable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Within 0-5 Range - Set Sheath Melee '),
  (@ENTRY, 0, 10, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Within 0-5 Range - Start Attacking (While Charmed)'),
  (@ENTRY, 0, 11, 12, 9, 0, 100, 512, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Within 5-15 Range - Disable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 12, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Within 5-15 Range - Stop Attacking (While Charmed)'),
  (@ENTRY, 0, 13, 0, 2, 0, 100, 513, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Between 0-15% HP - Increase Phase By 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 14, 15, 2, 0, 100, 513, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Between 0-15% HP - Enable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 15, 0, 61, 0, 100, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - Between 0-15% HP - Flee For Assist '),
  (@ENTRY, 0, 16, 0, 7, 0, 100, 0, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mounted Ironforge Mountaineer - On Evade - Set Sheath Melee ');

-- NPC 15417
SET @ENTRY = 15417;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Velan Brightoak - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Velan Brightoak - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 16525
SET @ENTRY = 16525;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 25, 0, 100, 0, 0, 5000, 15000, 20000, 11, 29920, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - On Reset - Cast "<a href="http://wowhead.com/spell=29920">Phasing Invisibility</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 0, 1500, 5000, 10000, 11, 29925, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - In Combat - Cast "<a href="http://wowhead.com/spell=29925">Fireball</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 0, 1500, 5000, 10000, 11, 29926, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - In Combat - Cast "<a href="http://wowhead.com/spell=29926">Frostbolt</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 0, 1500, 5000, 10000, 11, 29927, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - In Combat - Cast "<a href="http://wowhead.com/spell=29927">Shadow Bolt</a>" ');

-- NPC 13601
SET @ENTRY = 13601;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 515, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 515, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - On Aggro - Say Line 0 (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 16100, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - On Aggro - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 4, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 5, 6, 9, 1, 100, 2, 5, 30, 2300, 3900, 11, 16100, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 61, 1, 100, 2, 5, 30, 2300, 3900, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 7, 8, 9, 1, 100, 514, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Within 25-80 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 0, 61, 1, 100, 514, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Within 25-80 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 11, 9, 1, 100, 514, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Within 0-5 Range - Enable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 10, 0, 61, 1, 100, 2, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Within 0-5 Range - Set Sheath Melee (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 11, 10, 61, 1, 100, 514, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Within 0-5 Range - Start Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 13, 9, 1, 100, 514, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Within 5-15 Range - Disable Combat Movement (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 61, 1, 100, 514, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - Within 5-15 Range - Stop Attacking (Normal Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 14, 0, 0, 0, 100, 2, 9000, 12000, 14000, 17000, 11, 9143, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - In Combat - Cast "<a href="http://wowhead.com/spell=9143">Bomb</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 15, 0, 0, 0, 100, 2, 6000, 9000, 16000, 19000, 11, 21833, 40, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - In Combat - Cast "<a href="http://wowhead.com/spell=21833">Goblin Dragon Gun</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 16, 0, 0, 0, 100, 514, 6000, 9000, 16000, 19000, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - In Combat - Set Faction 0 (Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 17, 0, 0, 0, 100, 2, 25000, 25000, 25000, 25000, 11, 29419, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - In Combat - Cast "<a href="http://wowhead.com/spell=29419">Flash Bomb</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 18, 0, 7, 0, 100, 515, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 19, 0, 7, 0, 100, 3, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tinkerer Gizlock - On Evade - Set Sheath Melee (No Repeat and  Normal Dungeon)');

-- NPC 16397
SET @ENTRY = 16397;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ardeyn Riverwind - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Ardeyn Riverwind - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 15146
SET @ENTRY = 15146;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 3, 11, 0, 100, 0, 0, 0, 0, 0, 89, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mad Voidwalker - On Respawn - Start Random Movement '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 2, 7000, 9000, 11000, 13000, 11, 24614, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Mad Voidwalker - In Combat - Cast "<a href="http://wowhead.com/spell=24614">Consuming Shadows</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 2, 3000, 4000, 8000, 8000, 11, 24616, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Mad Voidwalker - In Combat - Cast "<a href="http://wowhead.com/spell=24616">Shadow Shock</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 512, 0, 0, 0, 0, 41, 180000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Mad Voidwalker - On Respawn - Despawn In 180000ms (While Charmed)');

-- NPC 15281
SET @ENTRY = 15281;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lanthan Perilon - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Lanthan Perilon - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 15401
SET @ENTRY = 15401;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ley-Keeper Velania - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Ley-Keeper Velania - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 15405
SET @ENTRY = 15405;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ley-Keeper Caidanis - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Ley-Keeper Caidanis - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 15418
SET @ENTRY = 15418;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Jaronis - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Magister Jaronis - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 18089
SET @ENTRY = 18089;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 32064, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodscale Slavedriver - On Aggro - Cast "<a href="http://wowhead.com/spell=32064">Battle Shout</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 54, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18089, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodscale Slavedriver - On Just Summoned - Start Waypoint 18089 '),
  (@ENTRY, 0, 2, 0, 38, 0, 100, 0, 1, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 10, 0, 62926, 17877, 50, 0, 0, 0, 0, 'Bloodscale Slavedriver - On Data Set 1 1 - Start Attacking '),
  (@ENTRY, 0, 3, 0, 6, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 10, 0, 62926, 17877, 30, 0, 0, 0, 0, 'Bloodscale Slavedriver - On Death - Increase Phase By 1 '),
  (@ENTRY, 0, 4, 0, 40, 0, 100, 0, 4, 18089, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodscale Slavedriver - On Waypoint 4 Reached - Set Home Position ');

-- NPC 24683
SET @ENTRY = 24683;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 519, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 519, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 7, 0, 0, 0, 0, 11, 44475, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - In Combat - Cast "<a href="http://wowhead.com/spell=44475">Magic Dampening Field</a>" (No Repeat, Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 44478, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - On Aggro - Cast "<a href="http://wowhead.com/spell=44478">Glaive Throw</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 4, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 5, 6, 9, 1, 100, 2, 0, 60, 2300, 5000, 11, 44478, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 0-60 Range - Cast "<a href="http://wowhead.com/spell=44478">Glaive Throw</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 61, 1, 100, 2, 0, 60, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 0-60 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 4, 0, 100, 5, 0, 0, 0, 0, 11, 46028, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - On Aggro - Cast "<a href="http://wowhead.com/spell=46028">Glaive Throw</a>" (No Repeat and  Heroic Dungeon)'),
  (@ENTRY, 0, 8, 0, 4, 0, 100, 517, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - On Aggro - Increase Phase By 1 (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 9, 10, 9, 1, 100, 4, 0, 60, 2300, 5000, 11, 46028, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 0-60 Range - Cast "<a href="http://wowhead.com/spell=46028">Glaive Throw</a>" (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 0, 61, 1, 100, 4, 0, 60, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 0-60 Range - Set Sheath Ranged (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 11, 12, 9, 1, 100, 519, 45, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 45-80 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 61, 1, 100, 519, 45, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 45-80 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 15, 9, 1, 100, 519, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 0-5 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 14, 0, 61, 1, 100, 7, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 0-5 Range - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 15, 14, 61, 1, 100, 519, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 0-5 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 16, 17, 9, 1, 100, 519, 5, 20, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 5-20 Range - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 17, 0, 61, 1, 100, 519, 5, 20, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Within 5-20 Range - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 18, 0, 2, 0, 100, 519, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 19, 0, 2, 0, 100, 519, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 20, 0, 2, 0, 100, 7, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - Between 0-15% HP - Flee For Assist (No Repeat, Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 21, 0, 7, 0, 100, 519, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 22, 0, 7, 0, 100, 7, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Sunblade Mage Guard - On Evade - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)');

-- NPC 15971
SET @ENTRY = 15971;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Silvermoon Apprentice - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Silvermoon Apprentice - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 16317
SET @ENTRY = 16317;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 0, 1000, 1000, 300000, 300000, 11, 29066, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Deatholme Necromancer - Out of Combat - Cast "<a href="http://wowhead.com/spell=29066">Summon Dreadbone Skeleton</a>" '),
  (@ENTRY, 0, 1, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 9613, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Deatholme Necromancer - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 0, 0, 20, 8000, 12000, 11, 29067, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Deatholme Necromancer - Between 0-20% HP - Cast "<a href="http://wowhead.com/spell=29067">Slave Drain</a>" '),
  (@ENTRY, 0, 3, 0, 2, 0, 100, 1, 0, 10, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Deatholme Necromancer - Between 0-10% HP - Flee For Assist (No Repeat)');

-- NPC 16318
SET @ENTRY = 16318;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 9613, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Deatholme Darkmage - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 7000, 11000, 32000, 36000, 11, 18267, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Deatholme Darkmage - In Combat - Cast "<a href="http://wowhead.com/spell=18267">Curse of Weakness</a>" '),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Deatholme Darkmage - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 16337
SET @ENTRY = 16337;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20802, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blackpaw Shaman - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 30, 15000, 25000, 11, 28902, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blackpaw Shaman - Between 0-30% HP - Cast "<a href="http://wowhead.com/spell=28902">Bloodlust</a>" (No Repeat)'),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Blackpaw Shaman - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 16358
SET @ENTRY = 16358;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20802, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kel&#039;gash the Wicked - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 9, 0, 100, 0, 0, 30, 9000, 13000, 11, 28900, 1, 0, 0, 0, 0, 5, 0, 30, 1, 0, 0, 0, 0, 0, 'Kel&#039;gash the Wicked - Within 0-30 Range - Cast "<a href="http://wowhead.com/spell=28900">Chain Lightning</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 7000, 10000, 15000, 22000, 11, 7289, 32, 0, 0, 0, 0, 5, 0, 30, 1, 0, 0, 0, 0, 0, 'Kel&#039;gash the Wicked - In Combat - Cast "<a href="http://wowhead.com/spell=7289">Shrink</a>" ');

-- NPC 16362
SET @ENTRY = 16362;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 6, 20811, 3000, 3500, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Runewarden Deryan - On AI Initialize - Install Caster SUN Template '),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Runewarden Deryan - Between 0-15% HP - Flee For Assist (No Repeat)');

-- NPC 16807
SET @ENTRY = 16807;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 38, 0, 100, 512, 1, 1, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Data Set 1 1 - Increase Phase By 1 (While Charmed)'),
  (@ENTRY, 0, 1, 0, 4, 15, 100, 1, 0, 0, 0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Aggro - Say Line 6 (No Repeat)(Phase 1, Phase 2, Phase 3 and  Phase 4)'),
  (@ENTRY, 0, 2, 0, 4, 16, 100, 1, 0, 0, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Aggro - Say Line 5 (No Repeat)(Phase 5)'),
  (@ENTRY, 0, 3, 0, 103, 1, 100, 513, 1, 0, 0, 0, 53, 0, 16807, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Enter Phase 1 - Start Waypoint 16807 (No Repeat and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 4, 0, 1, 1, 100, 0, 0, 0, 10000, 20000, 88, 1680700, 1680702, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - Out of Combat - Run Random Script Between 1680700 and 1680702 (Phase 1)'),
  (@ENTRY, 0, 5, 0, 103, 2, 100, 513, 2, 0, 0, 0, 80, 1680703, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Enter Phase 2 - Run Script <a href="/smartai/script/1680703">1680703</a> (No Repeat and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 6, 0, 1, 2, 100, 0, 20000, 20000, 10000, 20000, 88, 1680700, 1680702, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - Out of Combat - Run Random Script Between 1680700 and 1680702 (Phase 2)'),
  (@ENTRY, 0, 7, 0, 103, 4, 100, 513, 3, 40000, 0, 0, 80, 1680703, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Enter Phase 3 - Run Script <a href="/smartai/script/1680703">1680703</a> (No Repeat and  While Charmed)(Phase 3)'),
  (@ENTRY, 0, 8, 0, 1, 4, 100, 0, 20000, 20000, 10000, 20000, 88, 1680700, 1680702, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - Out of Combat - Run Random Script Between 1680700 and 1680702 (Phase 3)'),
  (@ENTRY, 0, 9, 0, 103, 8, 100, 513, 4, 40000, 0, 0, 80, 1680703, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Enter Phase 4 - Run Script <a href="/smartai/script/1680703">1680703</a> (No Repeat and  While Charmed)(Phase 4)'),
  (@ENTRY, 0, 10, 0, 1, 8, 100, 0, 20000, 20000, 10000, 20000, 88, 1680700, 1680702, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - Out of Combat - Run Random Script Between 1680700 and 1680702 (Phase 4)'),
  (@ENTRY, 0, 11, 0, 103, 16, 100, 513, 5, 40000, 0, 0, 80, 1680703, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Enter Phase 5 - Run Script <a href="/smartai/script/1680703">1680703</a> (No Repeat and  While Charmed)(Phase 5)'),
  (@ENTRY, 0, 12, 13, 1, 16, 100, 513, 5000, 5000, 0, 0, 55, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - Out of Combat - Stop Waypoint (No Repeat and  While Charmed)(Phase 5)'),
  (@ENTRY, 0, 13, 0, 61, 16, 100, 1, 5000, 5000, 0, 0, 49, 5000, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - Out of Combat - Start Attacking (No Repeat)(Phase 5)'),
  (@ENTRY, 0, 15, 0, 0, 0, 100, 512, 5000, 10000, 5000, 10000, 11, 30496, 2, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - In Combat - Cast "<a href="http://wowhead.com/spell=30496">Lesser Shadow Fissure</a>" (While Charmed)'),
  (@ENTRY, 0, 17, 0, 25, 0, 100, 512, 1, 0, 0, 0, 53, 0, 16807, 1, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Reset - Start Waypoint 16807 (While Charmed)'),
  (@ENTRY, 0, 18, 0, 4, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Aggro - Set Event Phase 0 '),
  (@ENTRY, 0, 19, 0, 9, 31, 100, 0, 0, 10, 100, 100, 49, 0, 0, 0, 0, 0, 0, 17, 0, 0, 10, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - Within 0-10 Range - Start Attacking (Phase 1, Phase 2, Phase 3, Phase 4 and  Phase 5)'),
  (@ENTRY, 0, 100, 101, 6, 0, 100, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 14, 0, 55988, 182540, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Death - Activate GO '),
  (@ENTRY, 0, 101, 0, 61, 0, 100, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 14, 0, 55987, 182539, 0, 0, 0, 0, 0, 'Grand Warlock Nethekurse - On Death - Activate GO ');

-- NPC 16939
SET @ENTRY = 16939;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 34236, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Void Baron Galaxis - On Aggro - Cast "<a href="http://wowhead.com/spell=34236">Baron"s Summons</a>" (No Repeat)'),
  (@ENTRY, 0, 1, 0, 2, 0, 100, 1, 34, 66, 1, 1, 11, 34239, 0, 0, 0, 0, 0, 9, 0, 19599, 0, 20, 0, 0, 0, 0, 'Void Baron Galaxis - Between 34-66% HP - Cast "<a href="http://wowhead.com/spell=34239">Absorb Life</a>" (No Repeat)'),
  (@ENTRY, 0, 2, 0, 2, 0, 100, 1, 1, 33, 1, 1, 11, 34239, 0, 0, 0, 0, 0, 9, 0, 19599, 0, 20, 0, 0, 0, 0, 'Void Baron Galaxis - Between 1-33% HP - Cast "<a href="http://wowhead.com/spell=34239">Absorb Life</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 54, 0, 100, 512, 0, 0, 0, 0, 152, 12949455, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1235.63, 1320.53, 3.21589, 1.35911, 'Void Baron Galaxis - On Just Summoned - Load Path 12949455 (While Charmed)'),
  (@ENTRY, 0, 4, 0, 7, 0, 100, 512, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Void Baron Galaxis - On Evade - Despawn Instant (While Charmed)'),
  (@ENTRY, 0, 5, 0, 54, 0, 100, 512, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Void Baron Galaxis - On Just Summoned - Set React State Passive (While Charmed)'),
  (@ENTRY, 0, 6, 0, 34, 0, 100, 512, 2, 1, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Void Baron Galaxis - On Reached Point 1 - Set React State Passive (While Charmed)');

-- NPC 17243
SET @ENTRY = 17243;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 62, 0, 100, 0, 8978, 0, 0, 0, 80, 1724300, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Engineer &quot;Spark&quot; Overgrind - On Gossip 8978 Option 0 Selected - Run Script <a href="/smartai/script/1724300">1724300</a> '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 0, 100, 5000, 8000, 11, 7978, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Engineer &quot;Spark&quot; Overgrind - In Combat - Cast "<a href="http://wowhead.com/spell=7978">Throw Dynamite</a>" '),
  (@ENTRY, 0, 2, 0, 54, 0, 100, 0, 0, 0, 0, 0, 53, 0, 17243, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Engineer &quot;Spark&quot; Overgrind - On Just Summoned - Start Waypoint 17243 '),
  (@ENTRY, 0, 3, 0, 40, 0, 100, 0, 2, 17243, 0, 0, 80, 1724301, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Engineer &quot;Spark&quot; Overgrind - On Waypoint 2 Reached - Run Script <a href="/smartai/script/1724301">1724301</a> '),
  (@ENTRY, 0, 4, 0, 40, 0, 100, 0, 4, 17243, 0, 0, 55, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Engineer &quot;Spark&quot; Overgrind - On Waypoint 4 Reached - Stop Waypoint '),
  (@ENTRY, 0, 5, 0, 7, 0, 100, 0, 0, 0, 0, 0, 2, 875, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Engineer &quot;Spark&quot; Overgrind - On Evade - Set Faction 875 '),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 0, 0, 0, 0, 0, 82, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Engineer &quot;Spark&quot; Overgrind - On Aggro - Set NPC Flag Gossip ');

-- NPC 17799
SET @ENTRY = 17799;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 2, 0, 100, 0, 0, 15, 120000, 120000, 11, 8269, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dreghood Slave - Between 0-15% HP - Cast "<a href="http://wowhead.com/spell=8269">Enrage</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 15, 120000, 120000, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dreghood Slave - Between 0-15% HP - Say Line 1 '),
  (@ENTRY, 0, 2, 0, 38, 0, 100, 1, 0, 2, 0, 0, 80, 1779901, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dreghood Slave - On Data Set 0 2 - Run Script <a href="/smartai/script/1779901">1779901</a> (No Repeat)'),
  (@ENTRY, 0, 5, 0, 25, 0, 100, 0, 0, 0, 0, 0, 28, 8269, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dreghood Slave - On Reset - Remove Aura "<a href="http://wowhead.com/spell=8269">Enrage</a>" '),
  (@ENTRY, 0, 6, 0, 38, 0, 100, 0, 0, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 12, 0, 1, 0, 0, 0, 0, 0, 0, 'Dreghood Slave - On Data Set 0 1 - Start Attacking ');

-- NPC 17815
SET @ENTRY = 17815;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 519, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 519, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 15620, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - On Aggro - Cast "<a href="http://wowhead.com/spell=15620">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 5000, 11, 15620, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=15620">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 5, 0, 0, 0, 0, 11, 16100, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - On Aggro - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (No Repeat and  Heroic Dungeon)'),
  (@ENTRY, 0, 7, 0, 4, 0, 100, 517, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - On Aggro - Increase Phase By 1 (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 8, 9, 9, 1, 100, 4, 5, 30, 2300, 5000, 11, 16100, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 4, 5, 30, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 5-30 Range - Set Sheath Ranged (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 11, 9, 1, 100, 519, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 25-80 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 0, 61, 1, 100, 519, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 25-80 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 14, 9, 1, 100, 519, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 0-5 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 61, 1, 100, 7, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 0-5 Range - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 14, 13, 61, 1, 100, 519, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 0-5 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 15, 16, 9, 1, 100, 519, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 5-15 Range - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 16, 0, 61, 1, 100, 519, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Within 5-15 Range - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 17, 0, 2, 0, 100, 519, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 18, 0, 2, 0, 100, 519, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 19, 0, 2, 0, 100, 7, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - Between 0-15% HP - Flee For Assist (No Repeat, Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 20, 0, 7, 0, 100, 519, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 21, 0, 7, 0, 100, 7, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Lordaeron Sentry - On Evade - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)');

-- NPC 17969
SET @ENTRY = 17969;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, 150, 2000, 2500, 11, 31401, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - In Combat - Cast "<a href="http://wowhead.com/spell=31401">Moonfire</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 5000, 7500, 12000, 15000, 11, 9739, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - In Combat - Cast "<a href="http://wowhead.com/spell=9739">Wrath</a>" '),
  (@ENTRY, 0, 2, 3, 19, 0, 100, 1, 9752, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Quest "<a href="http://wowhead.com/quest=9752">Escape from Umbrafen</a>" Accepted - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 512, 9752, 0, 0, 0, 53, 0, 17969, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Quest "<a href="http://wowhead.com/quest=9752">Escape from Umbrafen</a>" Accepted - Start Waypoint 17969 (While Charmed)'),
  (@ENTRY, 0, 4, 5, 40, 0, 100, 512, 4, 17969, 0, 0, 54, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Waypoint 4 Reached - Pause Waypoint 10000ms (While Charmed)'),
  (@ENTRY, 0, 5, 6, 61, 0, 100, 1, 4, 17969, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Waypoint 4 Reached - Say Line 1 (No Repeat)'),
  (@ENTRY, 0, 6, 0, 61, 0, 100, 512, 4, 17969, 0, 0, 80, 1796901, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Waypoint 4 Reached - Run Script <a href="/smartai/script/1796901">1796901</a> (While Charmed)'),
  (@ENTRY, 0, 7, 8, 60, 2, 100, 1, 4000, 4000, 1, 1, 1, 2, 179691, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Update - Say Line 2 (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 8, 0, 61, 2, 100, 513, 4000, 4000, 1, 1, 59, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Update - Set Run On (No Repeat and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 9, 10, 40, 2, 100, 513, 16, 17969, 0, 0, 54, 15000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Waypoint 16 Reached - Pause Waypoint 15000ms (No Repeat and  While Charmed)(Phase 2)'),
  (@ENTRY, 0, 10, 0, 61, 2, 100, 512, 16, 17969, 0, 0, 80, 1796902, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Waypoint 16 Reached - Run Script <a href="/smartai/script/1796902">1796902</a> (While Charmed)(Phase 2)'),
  (@ENTRY, 0, 11, 0, 60, 8, 100, 1, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Update - Say Line 4 (No Repeat)(Phase 4)'),
  (@ENTRY, 0, 12, 13, 40, 0, 100, 512, 23, 17969, 0, 0, 26, 9752, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Waypoint 23 Reached - Quest Credit "<a href="http://wowhead.com/quest=9752">Escape from Umbrafen</a>" (While Charmed)'),
  (@ENTRY, 0, 13, 16, 61, 0, 100, 0, 23, 17969, 0, 0, 1, 5, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Waypoint 23 Reached - Say Line 5 '),
  (@ENTRY, 0, 14, 0, 6, 0, 100, 512, 0, 0, 0, 0, 6, 9752, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Death - Fail Quest "<a href="http://wowhead.com/quest=9752">Escape from Umbrafen</a>" (While Charmed)'),
  (@ENTRY, 0, 15, 0, 19, 0, 100, 512, 9752, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Quest "<a href="http://wowhead.com/quest=9752">Escape from Umbrafen</a>" Accepted - Store Targetlist 0 (While Charmed)'),
  (@ENTRY, 0, 16, 0, 61, 0, 100, 512, 23, 17969, 0, 0, 55, 15000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Kayra Longmane - On Waypoint 23 Reached - Stop Waypoint (While Charmed)');

-- NPC 18094
SET @ENTRY = 18094;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 519, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 519, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 15620, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - On Aggro - Cast "<a href="http://wowhead.com/spell=15620">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 5000, 11, 15620, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=15620">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 5, 0, 0, 0, 0, 11, 16100, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - On Aggro - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (No Repeat and  Heroic Dungeon)'),
  (@ENTRY, 0, 7, 0, 4, 0, 100, 517, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - On Aggro - Increase Phase By 1 (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 8, 9, 9, 1, 100, 4, 5, 30, 2300, 5000, 11, 16100, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=16100">Shoot</a>" (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 4, 5, 30, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 5-30 Range - Set Sheath Ranged (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 11, 9, 1, 100, 519, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 25-80 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 0, 61, 1, 100, 519, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 25-80 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 14, 9, 1, 100, 519, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 0-5 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 61, 1, 100, 7, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 0-5 Range - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 14, 13, 61, 1, 100, 519, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 0-5 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 15, 16, 9, 1, 100, 519, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 5-15 Range - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 16, 0, 61, 1, 100, 519, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Within 5-15 Range - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 17, 18, 0, 1, 100, 6, 14000, 19000, 14000, 19000, 11, 17174, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - In Combat - Cast "<a href="http://wowhead.com/spell=17174">Concussive Shot</a>" (Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 18, 0, 61, 1, 100, 6, 14000, 19000, 14000, 19000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - In Combat - Set Sheath Ranged (Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 19, 20, 0, 1, 100, 6, 8000, 11000, 17000, 21000, 11, 35511, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - In Combat - Cast "<a href="http://wowhead.com/spell=35511">Serpent Sting</a>" (Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 20, 0, 61, 1, 100, 6, 8000, 11000, 17000, 21000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - In Combat - Set Sheath Ranged (Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 21, 0, 2, 0, 100, 519, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Between 0-15% HP - Increase Phase By 1 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 22, 0, 2, 0, 100, 519, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Between 0-15% HP - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 23, 0, 2, 0, 100, 7, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - Between 0-15% HP - Flee For Assist (No Repeat, Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 24, 0, 7, 0, 100, 519, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 25, 0, 7, 0, 100, 7, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Tarren Mill Lookout - On Evade - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)');

-- NPC 19556
SET @ENTRY = 19556;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 12, 54, 0, 100, 512, 0, 0, 0, 0, 43, 14744, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Just Summoned - Mount To Creature "<a href="http://wowhead.com/npc=14744">Frostwolf Riding Wolf</a>" (While Charmed)'),
  (@ENTRY, 0, 1, 0, 38, 0, 100, 512, 0, 1, 0, 0, 53, 1, 19556, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Data Set 0 1 - Start Waypoint 19556 (While Charmed)'),
  (@ENTRY, 0, 2, 0, 40, 0, 100, 512, 1, 19556, 0, 0, 80, 1955600, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Waypoint 1 Reached - Run Script <a href="/smartai/script/1955600">1955600</a> (While Charmed)'),
  (@ENTRY, 0, 3, 0, 40, 0, 100, 512, 2, 19556, 0, 0, 157, 1955600, 0, 0, 0, 0, 0, 19, 0, 19604, 30, 0, 0, 0, 0, 0, 'Thrall - On Waypoint 2 Reached - Add Target To Formation (While Charmed)'),
  (@ENTRY, 0, 4, 0, 40, 0, 100, 512, 13, 19556, 0, 0, 80, 1955601, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Waypoint 13 Reached - Run Script <a href="/smartai/script/1955601">1955601</a> (While Charmed)'),
  (@ENTRY, 0, 5, 0, 40, 0, 100, 512, 15, 19556, 0, 0, 80, 1955602, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Waypoint 15 Reached - Run Script <a href="/smartai/script/1955602">1955602</a> (While Charmed)'),
  (@ENTRY, 0, 6, 0, 40, 0, 100, 512, 24, 19556, 0, 0, 0, 1955603, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Waypoint 24 Reached - No Action Type (While Charmed)'),
  (@ENTRY, 0, 7, 0, 40, 0, 100, 512, 26, 19556, 0, 0, 0, 1955604, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Waypoint 26 Reached - No Action Type (While Charmed)'),
  (@ENTRY, 0, 8, 0, 40, 0, 100, 512, 34, 19556, 0, 0, 80, 1955605, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Waypoint 34 Reached - Run Script <a href="/smartai/script/1955605">1955605</a> (While Charmed)'),
  (@ENTRY, 0, 9, 0, 40, 0, 100, 512, 38, 19556, 0, 0, 80, 1955606, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Waypoint 38 Reached - Run Script <a href="/smartai/script/1955606">1955606</a> (While Charmed)'),
  (@ENTRY, 0, 10, 0, 38, 0, 100, 512, 0, 2, 0, 0, 80, 1955607, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Data Set 0 2 - Run Script <a href="/smartai/script/1955607">1955607</a> (While Charmed)'),
  (@ENTRY, 0, 11, 0, 40, 0, 100, 512, 47, 19556, 0, 0, 80, 1955608, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Waypoint 47 Reached - Run Script <a href="/smartai/script/1955608">1955608</a> (While Charmed)'),
  (@ENTRY, 0, 12, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Thrall - On Just Summoned - Say Line 0 ');

-- NPC 19916
SET @ENTRY = 19916;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 80, 1991600, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Archmage&#039;s Ritual Crystal - On Data Set 0 1 - Run Script <a href="/smartai/script/1991600">1991600</a> ');

-- NPC 20669
SET @ENTRY = 20669;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 1, 2, 54, 0, 100, 0, 0, 0, 0, 0, 11, 35424, 2, 0, 0, 0, 0, 19, 0, 20445, 20, 0, 0, 0, 0, 0, 'Shade of Mal&#039;druk - On Just Summoned - Cast "<a href="http://wowhead.com/spell=35424">Soul Shadows</a>" '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 155, 35424, 67, 0, 0, 0, 0, 19, 0, 20445, 20, 0, 0, 0, 0, 0, 'Shade of Mal&#039;druk - On Just Summoned - Assist Target ');

-- NPC 21035
SET @ENTRY = 21035;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 70, 0, 1, 120000, 1, 0, 0, 10, 0, 311207, 19554, 0, 0, 0, 0, 0, 'Dimensius the All-Devouring 000 - On Data Set 1 1 - Respawn Target '),
  (@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 120000, 1, 0, 0, 10, 0, 311207, 19554, 0, 0, 0, 0, 0, 'Dimensius the All-Devouring 000 - On Data Set 1 1 - Set Data 1 1 '),
  (@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dimensius the All-Devouring 000 - On Data Set 1 1 - Set Visibility Off '),
  (@ENTRY, 0, 3, 0, 38, 0, 100, 0, 1, 2, 0, 0, 47, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Dimensius the All-Devouring 000 - On Data Set 1 2 - Set Visibility On ');

-- NPC 21410
SET @ENTRY = 21410;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 54, 0, 100, 512, 0, 0, 0, 0, 59, 0, 21410, 0, 10570, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blood Lord Zarath - On Just Summoned - Set Run Off (While Charmed)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 69, 0, 1, 0, 0, 0, 0, 8, 0, 73739, 21293, 0, -4058.76, 1515.23, 91.292, 0, 'Blood Lord Zarath - On Just Summoned - Move To Pos '),
  (@ENTRY, 0, 3, 0, 38, 0, 100, 512, 0, 1, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 0, 21409, 10, 0, 0, 0, 0, 0, 'Blood Lord Zarath - On Data Set 0 1 - Set Orientation 0 (While Charmed)'),
  (@ENTRY, 0, 4, 5, 38, 0, 100, 512, 1, 1, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 4.716, 'Blood Lord Zarath - On Data Set 1 1 - Set Orientation 4.716 (While Charmed)'),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 512, 0, 0, 0, 0, 80, 2141000, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blood Lord Zarath - On Data Set 1 1 - Run Script <a href="/smartai/script/2141000">2141000</a> (While Charmed)'),
  (@ENTRY, 0, 6, 0, 40, 0, 100, 512, 1, 21410, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Blood Lord Zarath - On Waypoint 1 Reached - Set Home Position (While Charmed)');

-- NPC 21512
SET @ENTRY = 21512;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 8, 0, 100, 0, 37055, 0, 0, 0, 11, 41441, 0, 0, 0, 0, 0, 9, 0, 21316, 0, 100, 0, 0, 0, 0, 'Invis Legion Hold Glyph - On Spellhit "<a href="http://wowhead.com/spell=37055">Destroy Legion Hold Infernals</a>" - Cast "<a href="http://wowhead.com/spell=41441">Acid Geyser</a>" '),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 33, 21512, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 'Invis Legion Hold Glyph - On Spellhit "<a href="http://wowhead.com/spell=37055">Destroy Legion Hold Infernals</a>" - Quest Credit "<a href="http://wowhead.com/quest=21512">Invis Legion Hold Glyph</a>" ');

-- NPC 21694
SET @ENTRY = 21694;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 25, 0, 100, 3, 0, 0, 0, 0, 11, 37266, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bog Overlord - On Reset - Cast "<a href="http://wowhead.com/spell=37266">Disease Cloud</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 25, 0, 100, 5, 0, 0, 0, 0, 11, 37863, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bog Overlord - On Reset - Cast "<a href="http://wowhead.com/spell=37863">Disease Cloud</a>" (No Repeat and  Heroic Dungeon)'),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 2, 10000, 20000, 5000, 20000, 11, 37272, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Bog Overlord - In Combat - Cast "<a href="http://wowhead.com/spell=37272">Poison Bolt</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 4, 10000, 20000, 5000, 20000, 11, 37862, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Bog Overlord - In Combat - Cast "<a href="http://wowhead.com/spell=37862">Poison Bolt</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 4, 0, 0, 0, 100, 0, 5000, 10000, 15000, 25000, 11, 32065, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Bog Overlord - In Combat - Cast "<a href="http://wowhead.com/spell=32065">Fungal Decay</a>" '),
  (@ENTRY, 0, 5, 6, 2, 0, 100, 0, 0, 15, 120000, 125000, 11, 8599, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bog Overlord - Between 0-15% HP - Cast "<a href="http://wowhead.com/spell=8599">Enrage</a>" '),
  (@ENTRY, 0, 6, 0, 61, 0, 100, 0, 0, 15, 120000, 125000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bog Overlord - Between 0-15% HP - Say Line 0 '),
  (@ENTRY, 0, 7, 0, 25, 0, 100, 512, 0, 0, 0, 0, 28, 8599, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bog Overlord - On Reset - Remove Aura "<a href="http://wowhead.com/spell=8599">Enrage</a>" (While Charmed)');

-- NPC 22333
SET @ENTRY = 22333;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 60, 0, 100, 512, 500, 500, 2000, 2000, 45, 1, 2, 0, 0, 0, 0, 19, 0, 20771, 20, 0, 0, 0, 0, 0, 'Orb Collecting Totem - On Update - Set Data 1 2 (While Charmed)'),
  (@ENTRY, 0, 1, 0, 54, 0, 100, 512, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Orb Collecting Totem - On Just Summoned - Store Targetlist 1 (While Charmed)'),
  (@ENTRY, 0, 2, 0, 38, 0, 100, 512, 1, 1, 0, 0, 80, 2233300, 2, 0, 0, 0, 0, 1, 0, 1, 20, 0, 0, 0, 0, 0, 'Orb Collecting Totem - On Data Set 1 1 - Run Script <a href="/smartai/script/2233300">2233300</a> (While Charmed)');

-- NPC 24696
SET @ENTRY = 24696;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 519, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Out of Combat - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 519, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Out of Combat - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 35946, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - On Aggro - Cast "<a href="http://wowhead.com/spell=35946">Shoot</a>" (No Repeat and  Normal Dungeon)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 515, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - On Aggro - Increase Phase By 1 (No Repeat, Normal Dungeon and  While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 1, 100, 2, 5, 30, 2300, 5000, 11, 35946, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=35946">Shoot</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 2, 5, 30, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 5-30 Range - Set Sheath Ranged (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 5, 0, 0, 0, 0, 11, 22907, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - On Aggro - Cast "<a href="http://wowhead.com/spell=22907">Shoot</a>" (No Repeat and  Heroic Dungeon)'),
  (@ENTRY, 0, 7, 0, 4, 0, 100, 517, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - On Aggro - Increase Phase By 1 (No Repeat, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 8, 9, 9, 1, 100, 4, 5, 30, 2300, 5000, 11, 22907, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 5-30 Range - Cast "<a href="http://wowhead.com/spell=22907">Shoot</a>" (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 4, 5, 30, 2300, 5000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 5-30 Range - Set Sheath Ranged (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 10, 11, 9, 1, 100, 519, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 25-80 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 11, 0, 61, 1, 100, 519, 25, 80, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 25-80 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 12, 14, 9, 1, 100, 519, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 0-5 Range - Enable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 61, 1, 100, 7, 0, 5, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 0-5 Range - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 14, 13, 61, 1, 100, 519, 0, 5, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 0-5 Range - Start Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 15, 16, 9, 1, 100, 519, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 5-15 Range - Disable Combat Movement (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 16, 0, 61, 1, 100, 519, 5, 15, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 5-15 Range - Stop Attacking (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 17, 0, 9, 0, 100, 6, 0, 50, 8000, 15000, 11, 44639, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 0-50 Range - Cast "<a href="http://wowhead.com/spell=44639">Frost Arrow</a>" (Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 18, 0, 9, 0, 100, 6, 0, 50, 8000, 15000, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Within 0-50 Range - Set Sheath Ranged (Normal Dungeon and  Heroic Dungeon)'),
  (@ENTRY, 0, 19, 0, 0, 0, 100, 2, 3700, 7000, 15000, 20000, 11, 20299, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - In Combat - Cast "<a href="http://wowhead.com/spell=20299">Forked Lightning</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 20, 0, 0, 0, 100, 4, 3700, 7000, 15000, 20000, 11, 46150, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - In Combat - Cast "<a href="http://wowhead.com/spell=46150">Forked Lightning</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 21, 0, 2, 0, 100, 2, 0, 50, 70000, 85000, 11, 17741, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Between 0-50% HP - Cast "<a href="http://wowhead.com/spell=17741">Mana Shield</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 22, 0, 2, 0, 100, 4, 0, 50, 62000, 70000, 11, 46151, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - Between 0-50% HP - Cast "<a href="http://wowhead.com/spell=46151">Mana Shield</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 23, 0, 7, 0, 100, 519, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - On Evade - Set Event Phase 0 (No Repeat, Normal Dungeon, Heroic Dungeon and  While Charmed)'),
  (@ENTRY, 0, 24, 0, 7, 0, 100, 7, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Coilskar Witch - On Evade - Set Sheath Melee (No Repeat, Normal Dungeon and  Heroic Dungeon)');

-- NPC 25115
SET @ENTRY = 25115;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 11, 0, 100, 513, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Respawn - Disable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 1, 0, 100, 512, 0, 50, 4500, 8000, 11, 42580, 2, 0, 0, 0, 0, 9, 4, 25192, 0, 50, 0, 0, 0, 0, 'Shattered Sun Warrior - Out of Combat - Cast "<a href="http://wowhead.com/spell=42580">Shoot</a>" (While Charmed)'),
  (@ENTRY, 0, 2, 0, 37, 0, 100, 512, 0, 0, 0, 0, 31, 1, 4, 4, 8, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On AI Initialize - Set Phase Random Between 1-4 (While Charmed)'),
  (@ENTRY, 0, 3, 0, 103, 1, 100, 512, 1, 0, 0, 0, 3, 25120, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Enter Phase 1 - Morph To "25120" (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 4, 5, 68, 1, 100, 512, 36, 0, 0, 0, 3, 25121, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 36 Started - Morph To "25121" (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 5, 0, 61, 1, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 36 Started - Change Equipment (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 6, 7, 68, 1, 100, 512, 40, 0, 0, 0, 3, 25122, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 40 Started - Morph To "25122" (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 61, 1, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 40 Started - Change Equipment (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 9, 68, 1, 100, 512, 44, 0, 0, 0, 3, 25123, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 44 Started - Morph To "25123" (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 61, 1, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 44 Started - Change Equipment (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 10, 0, 103, 2, 100, 512, 2, 0, 0, 0, 3, 25116, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Enter Phase 2 - Morph To "25116" (While Charmed)(Phase 2)'),
  (@ENTRY, 0, 11, 12, 68, 2, 100, 512, 36, 0, 0, 0, 3, 25117, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 36 Started - Morph To "25117" (While Charmed)(Phase 2)'),
  (@ENTRY, 0, 12, 0, 61, 2, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 36 Started - Change Equipment (While Charmed)(Phase 2)'),
  (@ENTRY, 0, 13, 14, 68, 2, 100, 512, 40, 0, 0, 0, 3, 25118, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 40 Started - Morph To "25118" (While Charmed)(Phase 2)'),
  (@ENTRY, 0, 14, 0, 61, 2, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 40 Started - Change Equipment (While Charmed)(Phase 2)'),
  (@ENTRY, 0, 15, 16, 68, 2, 100, 512, 44, 0, 0, 0, 3, 25119, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 44 Started - Morph To "25119" (While Charmed)(Phase 2)'),
  (@ENTRY, 0, 16, 0, 61, 2, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 44 Started - Change Equipment (While Charmed)(Phase 2)'),
  (@ENTRY, 0, 17, 0, 103, 4, 100, 512, 3, 0, 0, 0, 3, 25128, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Enter Phase 3 - Morph To "25128" (While Charmed)(Phase 3)'),
  (@ENTRY, 0, 18, 19, 68, 4, 100, 512, 36, 0, 0, 0, 3, 25129, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 36 Started - Morph To "25129" (While Charmed)(Phase 3)'),
  (@ENTRY, 0, 19, 0, 61, 4, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 36 Started - Change Equipment (While Charmed)(Phase 3)'),
  (@ENTRY, 0, 20, 21, 68, 4, 100, 512, 40, 0, 0, 0, 3, 25130, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 40 Started - Morph To "25130" (While Charmed)(Phase 3)'),
  (@ENTRY, 0, 21, 0, 61, 4, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 40 Started - Change Equipment (While Charmed)(Phase 3)'),
  (@ENTRY, 0, 22, 23, 68, 4, 100, 512, 44, 0, 0, 0, 3, 25131, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 44 Started - Morph To "25131" (While Charmed)(Phase 3)'),
  (@ENTRY, 0, 23, 0, 61, 4, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 44 Started - Change Equipment (While Charmed)(Phase 3)'),
  (@ENTRY, 0, 24, 0, 103, 8, 100, 512, 4, 0, 0, 0, 3, 25124, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Enter Phase 4 - Morph To "25124" (While Charmed)(Phase 4)'),
  (@ENTRY, 0, 25, 26, 68, 8, 100, 512, 36, 0, 0, 0, 3, 25125, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 36 Started - Morph To "25125" (While Charmed)(Phase 4)'),
  (@ENTRY, 0, 26, 0, 61, 8, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 36 Started - Change Equipment (While Charmed)(Phase 4)'),
  (@ENTRY, 0, 27, 28, 68, 8, 100, 512, 40, 0, 0, 0, 3, 25126, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 40 Started - Morph To "25126" (While Charmed)(Phase 4)'),
  (@ENTRY, 0, 28, 0, 61, 8, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 40 Started - Change Equipment (While Charmed)(Phase 4)'),
  (@ENTRY, 0, 29, 30, 68, 8, 100, 512, 44, 0, 0, 0, 3, 25127, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 44 Started - Morph To "25127" (While Charmed)(Phase 4)'),
  (@ENTRY, 0, 30, 0, 61, 8, 100, 512, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Shattered Sun Warrior - On Game Event 44 Started - Change Equipment (While Charmed)(Phase 4)');

-- NPC 25145
SET @ENTRY = 25145;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 1, 0, 100, 513, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Out of Combat - Disable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Out of Combat - Stop Attacking (While Charmed)'),
  (@ENTRY, 0, 2, 3, 4, 0, 100, 0, 0, 0, 0, 0, 11, 23337, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - On Aggro - Cast "<a href="http://wowhead.com/spell=23337">Shoot</a>" '),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 512, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - On Aggro - Increase Phase By 1 (While Charmed)'),
  (@ENTRY, 0, 4, 5, 9, 0, 100, 0, 0, 45, 2300, 3900, 11, 23337, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Within 0-45 Range - Cast "<a href="http://wowhead.com/spell=23337">Shoot</a>" '),
  (@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Within 0-45 Range - Set Sheath Ranged '),
  (@ENTRY, 0, 6, 0, 9, 0, 100, 0, 0, 20, 8000, 13000, 11, 12024, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Within 0-20 Range - Cast "<a href="http://wowhead.com/spell=12024">Net</a>" '),
  (@ENTRY, 0, 7, 8, 9, 0, 100, 512, 25, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Within 25-80 Range - Enable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 8, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Within 25-80 Range - Start Attacking (While Charmed)'),
  (@ENTRY, 0, 9, 10, 9, 0, 100, 512, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Within 0-5 Range - Enable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 10, 11, 61, 0, 100, 0, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Within 0-5 Range - Set Sheath Melee '),
  (@ENTRY, 0, 11, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Within 0-5 Range - Start Attacking (While Charmed)'),
  (@ENTRY, 0, 12, 13, 9, 0, 100, 512, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Within 5-15 Range - Disable Combat Movement (While Charmed)'),
  (@ENTRY, 0, 13, 0, 61, 0, 100, 512, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - Within 5-15 Range - Stop Attacking (While Charmed)'),
  (@ENTRY, 0, 14, 0, 7, 0, 100, 0, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Budd&#039;s Bodyguard - On Evade - Set Sheath Melee ');

-- NPC 50106
SET @ENTRY = 50106;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 53, 1, 180891, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodscale Slavedriver - On Just Summoned - Start Waypoint 180891 '),
  (@ENTRY, 0, 1, 0, 38, 0, 100, 0, 1, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 10, 0, 62926, 17877, 50, 0, 0, 0, 0, 'Bloodscale Slavedriver - On Data Set 1 1 - Start Attacking '),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 32064, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodscale Slavedriver - On Aggro - Cast "<a href="http://wowhead.com/spell=32064">Battle Shout</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 6, 0, 100, 0, 1, 1, 0, 0, 23, 1, 0, 0, 0, 0, 0, 10, 0, 62926, 17877, 50, 0, 0, 0, 0, 'Bloodscale Slavedriver - On Death - Increase Phase By 1 ');

-- GO 183770
SET @ENTRY = 183770;
UPDATE gameobject_template SET AIName='SmartGameObjectAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 1;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 1, 0, 0, 62, 0, 100, 0, 8036, 0, 0, 0, 80, 18377001, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'B&#039;naar Control Console - On Gossip 8036 Option 0 Selected - Run Script <a href="/smartai/script/18377001">18377001</a> ');

-- NPC 2570
SET @ENTRY = 2570;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 1, 0, 100, 513, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - Out of Combat - Disable Combat Movement (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 1, 0, 4, 0, 5, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - On Aggro - Say Line 0 (No Repeat)'),
  (@ENTRY, 0, 2, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 9532, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - On Aggro - Cast "<a href="http://wowhead.com/spell=9532">Lightning Bolt</a>" (No Repeat)'),
  (@ENTRY, 0, 3, 0, 4, 0, 100, 513, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - On Aggro - Increase Phase By 1 (No Repeat and  While Charmed)'),
  (@ENTRY, 0, 4, 0, 9, 1, 100, 0, 0, 40, 3500, 6400, 11, 9532, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - Within 0-40 Range - Cast "<a href="http://wowhead.com/spell=9532">Lightning Bolt</a>" (Phase 1)'),
  (@ENTRY, 0, 5, 6, 3, 1, 100, 513, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - Between 0-15% MP - Enable Combat Movement (No Repeat and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 6, 0, 61, 1, 100, 513, 0, 15, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - Between 0-15% MP - Increase Phase By 1 (No Repeat and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 7, 0, 9, 1, 100, 513, 35, 80, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - Within 35-80 Range - Enable Combat Movement (No Repeat and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 8, 0, 9, 1, 100, 513, 0, 5, 0, 500, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - Within 0-5 Range - Enable Combat Movement (No Repeat and  While Charmed)(Phase 1)'),
  (@ENTRY, 0, 9, 0, 9, 1, 100, 512, 5, 15, 0, 500, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - Within 5-15 Range - Disable Combat Movement (While Charmed)(Phase 1)'),
  (@ENTRY, 0, 10, 0, 3, 0, 100, 512, 30, 100, 100, 100, 23, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - Between 30-100% MP - Decrease Phase By 0 (While Charmed)'),
  (@ENTRY, 0, 11, 0, 2, 0, 100, 1, 0, 45, 0, 0, 11, 6364, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - Between 0-45% HP - Cast "<a href="http://wowhead.com/spell=6364">Searing Totem</a>" (No Repeat)'),
  (@ENTRY, 0, 12, 0, 2, 0, 100, 1, 0, 40, 0, 0, 11, 11986, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - Between 0-40% HP - Cast "<a href="http://wowhead.com/spell=11986">Healing Wave</a>" (No Repeat)'),
  (@ENTRY, 0, 13, 0, 7, 0, 100, 513, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Boulderfist Shaman - On Evade - Set Event Phase 0 (No Repeat and  While Charmed)');

UPDATE conditions SET ConditionValue1 = 3, ConditionValue2 = 10321 WHERE SourceEntry = 16053;

# https://github.com/TrinityCore/TrinityCore/commit/f68df25a5667c90877a82de9ee4455937adc5acc
UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` IN(12256,12255,12254,12253,12252,12251,12249,12244);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN(12256,12255,12254,12253,12252,12251,12249,12244) AND `source_type`=0;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
  (12256, 0, 0, 1, 8, 0, 100, 0, 19250, 0, 120000, 120000, 33, 12247, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Kill Credit'),
  (12255, 0, 0, 1, 8, 0, 100, 0, 19250, 0, 120000, 120000, 33, 12247, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Kill Credit'),
  (12254, 0, 0, 1, 8, 0, 100, 0, 19250, 0, 120000, 120000, 33, 12247, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Kill Credit'),
  (12253, 0, 0, 1, 8, 0, 100, 0, 19250, 0, 120000, 120000, 33, 12247, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Kill Credit'),
  (12252, 0, 0, 1, 8, 0, 100, 0, 19250, 0, 120000, 120000, 33, 12247, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Kill Credit'),
  (12251, 0, 0, 1, 8, 0, 100, 0, 19250, 0, 120000, 120000, 33, 12247, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Kill Credit'),
  (12249, 0, 0, 1, 8, 0, 100, 0, 19250, 0, 120000, 120000, 33, 12247, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Kill Credit'),
  (12244, 0, 0, 1, 8, 0, 100, 0, 19250, 0, 120000, 120000, 33, 12247, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Kill Credit'),
  (12256, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 70, 120, 0, 0, 0, 0, 0, 20, 177668, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Despawn Mark of Detonation'),
  (12255, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 70, 120, 0, 0, 0, 0, 0, 20, 177668, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Despawn Mark of Detonation'),
  (12254, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 70, 120, 0, 0, 0, 0, 0, 20, 177668, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Despawn Mark of Detonation'),
  (12253, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 70, 120, 0, 0, 0, 0, 0, 20, 177668, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Despawn Mark of Detonation'),
  (12252, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 70, 120, 0, 0, 0, 0, 0, 20, 177668, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Despawn Mark of Detonation'),
  (12251, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 70, 120, 0, 0, 0, 0, 0, 20, 177668, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Despawn Mark of Detonation'),
  (12249, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 70, 120, 0, 0, 0, 0, 0, 20, 177668, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Despawn Mark of Detonation'),
  (12244, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 70, 120, 0, 0, 0, 0, 0, 20, 177668, 0, 0, 0, 0, 0, 0, 'Mark of Detonation - On Spellhit - Despawn Mark of Detonation');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=19250;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
  (13, 1, 19250, 0, 0, 31, 0, 3, 12256, 0, 0, 0, 0, '', 'Place Smokeys Mixture targets Mark of Detonation'),
  (13, 1, 19250, 0, 1, 31, 0, 3, 12255, 0, 0, 0, 0, '', 'Place Smokeys Mixture targets Mark of Detonation'),
  (13, 1, 19250, 0, 2, 31, 0, 3, 12254, 0, 0, 0, 0, '', 'Place Smokeys Mixture targets Mark of Detonation'),
  (13, 1, 19250, 0, 3, 31, 0, 3, 12253, 0, 0, 0, 0, '', 'Place Smokeys Mixture targets Mark of Detonation'),
  (13, 1, 19250, 0, 4, 31, 0, 3, 12252, 0, 0, 0, 0, '', 'Place Smokeys Mixture targets Mark of Detonation'),
  (13, 1, 19250, 0, 5, 31, 0, 3, 12251, 0, 0, 0, 0, '', 'Place Smokeys Mixture targets Mark of Detonation'),
  (13, 1, 19250, 0, 6, 31, 0, 3, 12249, 0, 0, 0, 0, '', 'Place Smokeys Mixture targets Mark of Detonation'),
  (13, 1, 19250, 0, 7, 31, 0, 3, 12244, 0, 0, 0, 0, '', 'Place Smokeys Mixture targets Mark of Detonation'),
  (13, 4, 19250, 0, 0, 31, 0, 3, 12247, 0, 0, 0, 0, '', 'Place Smokeys Mixture targets Scourge Structure');

DELETE FROM conditions WHERE SourceEntry = 38729;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
  (13,	1,	38729,	0,	0,	31,	0,	5,	22288,	0,	0,	0,	0,	'',	NULL),
  (13,	4,	38729,	0,	0,	31,	0,	3,	185191,	0,	0,	0,	0,	'',	NULL);

UPDATE conditions SET SourceGroup = 2 WHERE SourceEntry = 31927;

DELETE FROM conditions WHERE SourceEntry = 30098;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
  (13,	1,	30098,	0,	0,	31,	0,	5,	181653,	0,	0,	0,	0,	'',	NULL),
  (13,	4,	30098,	0,	0,	31,	0,	5,	300145,	0,	0,	0,	0,	'',	NULL),
  (13,	2,	30098,	0,	0,	31,	0,	3,	17253,	0,	0,	0,	0,	'',	NULL);

UPDATE conditions SET ConditionValue1 = 3, ConditionValue2 = 22395 WHERE SourceEntry = 39124;
UPDATE conditions SET ConditionValue1 = 3, ConditionValue2 = 22367 WHERE SourceEntry = 38629;
UPDATE conditions SET SourceGroup = 1 WHERE SourceEntry = 35739 AND ConditionValue1 = 5;
UPDATE conditions SET SourceGroup = 1 WHERE SourceEntry = 34387 AND ConditionValue1 = 5;
