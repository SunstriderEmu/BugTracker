/*
  Rework of SAI Templates with SMART_ACTION_STORE_PHASE and SMART_ACTION_RESTORE_PHASE.
 */

-- NPC 14324
SET @ENTRY = 14324;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 37, 0, 100, 1, 0, 0, 0, 0, 31, 1, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - On AI Initialize - Set Phase Random Between 1-3 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - On AI Initialize - Store Current Phase '),
  (@ENTRY, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 164, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - On Reset - Restore Phase '),
  (@ENTRY, 0, 10, 12, 37, 1, 100, 1, 0, 0, 0, 0, 58, 6, 15234, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - On AI Initialize - Install Caster SUN Template (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 61, 1, 100, 1, 0, 0, 0, 0, 124, 91606, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - On AI Initialize - Load Equipment #91606 (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 0, 1, 100, 0, 9000, 14000, 10000, 12000, 11, 15305, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - In Combat - Cast "<a href="http://wowhead.com/spell=15305">Chain Lightning</a>" (Phase 1)'),
  (@ENTRY, 0, 14, 0, 0, 1, 100, 0, 7000, 12000, 35000, 40000, 11, 8376, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - In Combat - Cast "<a href="http://wowhead.com/spell=8376">Earthgrab Totem</a>" (Phase 1)'),
  (@ENTRY, 0, 15, 0, 2, 1, 100, 0, 0, 50, 15000, 22000, 11, 15982, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - Between 0-50% HP - Cast "<a href="http://wowhead.com/spell=15982">Healing Wave</a>" (Phase 1)'),
  (@ENTRY, 0, 16, 0, 2, 1, 100, 1, 0, 30, 0, 0, 11, 16170, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - Between 0-30% HP - Cast "<a href="http://wowhead.com/spell=16170">Bloodlust</a>" (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 20, 21, 37, 2, 100, 1, 0, 0, 0, 0, 58, 6, 17290, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - On AI Initialize - Install Caster SUN Template (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 21, 0, 61, 2, 100, 1, 0, 0, 0, 0, 124, 91605, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - On AI Initialize - Load Equipment #91605 (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 22, 0, 0, 2, 100, 0, 8000, 11000, 10000, 14000, 11, 15531, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - In Combat - Cast "<a href="http://wowhead.com/spell=15531">Frost Nova</a>" (Phase 2)'),
  (@ENTRY, 0, 23, 0, 0, 2, 100, 0, 16000, 20000, 10000, 14000, 11, 13745, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - In Combat - Cast "<a href="http://wowhead.com/spell=13745">Arcane Explosion</a>" (Phase 2)'),
  (@ENTRY, 0, 30, 31, 37, 4, 100, 0, 0, 0, 0, 0, 58, 6, 17194, 1500, 2000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - On AI Initialize - Install Caster SUN Template (Phase 3)'),
  (@ENTRY, 0, 31, 0, 61, 4, 100, 1, 0, 0, 0, 0, 124, 91604, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - On AI Initialize - Load Equipment #91604 (No Repeat)(Phase 3)'),
  (@ENTRY, 0, 32, 0, 0, 4, 100, 0, 12000, 15000, 40000, 50000, 11, 17139, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - In Combat - Cast "<a href="http://wowhead.com/spell=17139">Power Word: Shield</a>" (Phase 3)'),
  (@ENTRY, 0, 33, 0, 0, 4, 100, 0, 9000, 11000, 19000, 24000, 11, 22884, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Cho&#039;Rush the Observer - In Combat - Cast "<a href="http://wowhead.com/spell=22884">Psychic Scream</a>" (Phase 3)');

-- NPC 16526 -- was using the system, shouldn't.
SET @ENTRY = 16526;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, 1500, 5000, 10000, 11, 29922, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Sorcerous Shade - In Combat - Cast "<a href="http://wowhead.com/spell=29922">Fireball Volley</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 0, 1500, 5000, 10000, 11, 29923, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Sorcerous Shade - In Combat - Cast "<a href="http://wowhead.com/spell=29923">Frostbolt Volley</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 0, 1500, 5000, 10000, 11, 29924, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Sorcerous Shade - In Combat - Cast "<a href="http://wowhead.com/spell=29924">Shadow Bolt Volley</a>" ');


-- NPC 16525 -- was using the system, shouldn't.
SET @ENTRY = 16525;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 3, 25, 0, 100, 0, 0, 5000, 15000, 20000, 11, 29920, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - On Reset - Cast "<a href="http://wowhead.com/spell=29920">Phasing Invisibility</a>" '),
  (@ENTRY, 0, 1, 0, 0, 0, 100, 0, 0, 1500, 5000, 10000, 11, 29925, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - In Combat - Cast "<a href="http://wowhead.com/spell=29925">Fireball</a>" '),
  (@ENTRY, 0, 2, 0, 0, 0, 100, 0, 0, 1500, 5000, 10000, 11, 29926, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - In Combat - Cast "<a href="http://wowhead.com/spell=29926">Frostbolt</a>" '),
  (@ENTRY, 0, 3, 0, 0, 0, 100, 0, 0, 1500, 5000, 10000, 11, 29927, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Spell Shade - In Combat - Cast "<a href="http://wowhead.com/spell=29927">Shadow Bolt</a>" ');

-- NPC 17771
SET @ENTRY = 17771;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 37, 0, 100, 1, 0, 0, 0, 0, 30, 1, 2, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - On AI Initialize - Set Random Phase (1, 2 and 3) (No Repeat)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - On AI Initialize - Store Current Phase '),
  (@ENTRY, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 164, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - On Reset - Restore Phase '),
  (@ENTRY, 0, 10, 0, 37, 1, 100, 2, 0, 0, 0, 0, 58, 1, 12471, 3000, 3500, 40, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - On AI Initialize - Install Caster Template (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 11, 0, 0, 1, 100, 2, 0, 10000, 15000, 25000, 11, 31405, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - In Combat - Cast "<a href="http://wowhead.com/spell=31405">Corruption</a>" (Normal Dungeon)(Phase 1)'),
  (@ENTRY, 0, 12, 0, 37, 1, 100, 4, 0, 0, 0, 0, 58, 1, 15232, 3000, 3500, 40, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - On AI Initialize - Install Caster Template (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 13, 0, 0, 1, 100, 4, 0, 10000, 15000, 25000, 11, 37113, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - In Combat - Cast "<a href="http://wowhead.com/spell=37113">Corruption</a>" (Heroic Dungeon)(Phase 1)'),
  (@ENTRY, 0, 20, 0, 37, 2, 100, 2, 0, 0, 0, 0, 58, 1, 15497, 3000, 3500, 40, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - On AI Initialize - Install Caster Template (Normal Dungeon)(Phase 2)'),
  (@ENTRY, 0, 21, 0, 0, 2, 100, 2, 15000, 25000, 25000, 35000, 11, 32192, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - In Combat - Cast "<a href="http://wowhead.com/spell=32192">Frost Nova</a>" (Normal Dungeon)(Phase 2)'),
  (@ENTRY, 0, 22, 0, 37, 2, 100, 4, 0, 0, 0, 0, 58, 1, 12675, 3000, 3500, 40, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - On AI Initialize - Install Caster Template (Heroic Dungeon)(Phase 2)'),
  (@ENTRY, 0, 23, 0, 0, 2, 100, 4, 15000, 25000, 25000, 35000, 11, 15531, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - In Combat - Cast "<a href="http://wowhead.com/spell=15531">Frost Nova</a>" (Heroic Dungeon)(Phase 2)'),
  (@ENTRY, 0, 30, 0, 37, 4, 100, 2, 0, 0, 0, 0, 58, 1, 14034, 3000, 3500, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - On AI Initialize - Install Caster Template (Normal Dungeon)(Phase 3)'),
  (@ENTRY, 0, 32, 0, 0, 4, 100, 2, 0, 5000, 7500, 15000, 11, 15241, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - In Combat - Cast "<a href="http://wowhead.com/spell=15241">Scorch</a>" (Normal Dungeon)(Phase 3)'),
  (@ENTRY, 0, 33, 0, 37, 4, 100, 4, 0, 0, 0, 0, 58, 1, 15228, 3000, 3500, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - On AI Initialize - Install Caster Template (Heroic Dungeon)(Phase 3)'),
  (@ENTRY, 0, 34, 0, 0, 4, 100, 2, 0, 7500, 7500, 15000, 11, 36807, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - In Combat - Cast "<a href="http://wowhead.com/spell=36807">Scorch</a>" (Normal Dungeon)(Phase 3)'),
  (@ENTRY, 0, 40, 0, 0, 6, 100, 0, 5000, 20000, 15000, 25000, 11, 12248, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - In Combat - Cast "<a href="http://wowhead.com/spell=12248">Amplify Damage</a>" (Phase 2 and  Phase 3)'),
  (@ENTRY, 0, 41, 0, 23, 6, 100, 0, 34880, 0, 15000, 20000, 11, 34880, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Murkblood Oracle - On Missing Aura "<a href="http://wowhead.com/spell=34880">Elemental Armor</a>" - Cast "<a href="http://wowhead.com/spell=34880">Elemental Armor</a>" (Phase 2 and  Phase 3)');

-- NPC 18493
SET @ENTRY = 18493;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 37, 0, 100, 1, 0, 0, 0, 0, 31, 1, 5, 4, 8, 16, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - On AI Initialize - Set Phase Random Between 1-5 (No Repeat)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - On AI Initialize - Store Current Phase '),
  (@ENTRY, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 164, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - On Reset - Restore Phase '),
  (@ENTRY, 0, 5, 0, 4, 0, 100, 2, 0, 0, 0, 0, 58, 1, 32860, 2500, 2750, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - On Aggro - Install Caster Template (Normal Dungeon)'),
  (@ENTRY, 0, 6, 0, 4, 0, 100, 4, 0, 0, 0, 0, 58, 1, 38778, 2500, 2750, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - On Aggro - Install Caster Template (Heroic Dungeon)'),
  (@ENTRY, 0, 7, 0, 0, 0, 100, 2, 10000, 20000, 15000, 30000, 11, 32858, 32, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - In Combat - Cast "<a href="http://wowhead.com/spell=32858">Touch of the Forgotten</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 8, 0, 0, 0, 100, 4, 10000, 20000, 15000, 30000, 11, 38377, 32, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - In Combat - Cast "<a href="http://wowhead.com/spell=38377">Touch of the Forgotten</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 9, 0, 0, 0, 100, 0, 15000, 30000, 15000, 30000, 11, 32859, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - In Combat - Cast "<a href="http://wowhead.com/spell=32859">Falter</a>" '),
  (@ENTRY, 0, 10, 0, 0, 1, 100, 1, 4000, 5000, 0, 0, 11, 32857, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - In Combat - Cast "<a href="http://wowhead.com/spell=32857">Summon Phantasmal Possessor</a>" (No Repeat)(Phase 1)'),
  (@ENTRY, 0, 20, 0, 0, 2, 100, 1, 4000, 5000, 0, 0, 11, 32855, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - In Combat - Cast "<a href="http://wowhead.com/spell=32855">Summon Unliving Cleric</a>" (No Repeat)(Phase 2)'),
  (@ENTRY, 0, 30, 0, 0, 4, 100, 1, 4000, 5000, 0, 0, 11, 32853, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - In Combat - Cast "<a href="http://wowhead.com/spell=32853">Summon Unliving Soldier</a>" (No Repeat)(Phase 3)'),
  (@ENTRY, 0, 40, 0, 0, 8, 100, 1, 4000, 5000, 0, 0, 11, 32854, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - In Combat - Cast "<a href="http://wowhead.com/spell=32854">Summon Unliving Sorcerer</a>" (No Repeat)(Phase 4)'),
  (@ENTRY, 0, 50, 0, 0, 16, 100, 1, 4000, 5000, 0, 0, 11, 32856, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Auchenai Soulpriest - In Combat - Cast "<a href="http://wowhead.com/spell=32856">Summon Unliving Stalker</a>" (No Repeat)(Phase 5)');
-- NPC 18499
SET @ENTRY = 18499;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
  (@ENTRY, 0, 0, 1, 54, 0, 100, 2, 0, 0, 0, 0, 58, 6, 12466, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Unliving Sorcerer - On Just Summoned - Install Caster SUN Template (Normal Dungeon)'),
  (@ENTRY, 0, 1, 0, 61, 0, 100, 2, 0, 0, 0, 0, 155, 6, 12466, 3000, 3500, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 'Unliving Sorcerer - On Just Summoned - Assist Target (Normal Dungeon)'),
  (@ENTRY, 0, 2, 3, 54, 0, 100, 4, 0, 0, 0, 0, 58, 6, 17290, 3000, 3500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Unliving Sorcerer - On Just Summoned - Install Caster SUN Template (Heroic Dungeon)'),
  (@ENTRY, 0, 3, 0, 61, 0, 100, 4, 0, 0, 0, 0, 155, 6, 12466, 3000, 3500, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 'Unliving Sorcerer - On Just Summoned - Assist Target (Heroic Dungeon)'),
  (@ENTRY, 0, 13, 0, 0, 0, 100, 2, 6000, 8000, 13000, 15000, 11, 15043, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Unliving Sorcerer - In Combat - Cast "<a href="http://wowhead.com/spell=15043">Frostbolt</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 14, 0, 0, 0, 100, 4, 6000, 8000, 13000, 15000, 11, 15530, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Unliving Sorcerer - In Combat - Cast "<a href="http://wowhead.com/spell=15530">Frostbolt</a>" (Heroic Dungeon)'),
  (@ENTRY, 0, 15, 0, 9, 0, 100, 2, 0, 10, 10000, 13000, 11, 15744, 0, 0, 0, 0, 0, 17, 0, 0, 10, 0, 0, 0, 0, 0, 'Unliving Sorcerer - Within 0-10 Range - Cast "<a href="http://wowhead.com/spell=15744">Blast Wave</a>" (Normal Dungeon)'),
  (@ENTRY, 0, 16, 0, 9, 0, 100, 4, 0, 10, 10000, 13000, 11, 22424, 0, 0, 0, 0, 0, 17, 0, 0, 10, 0, 0, 0, 0, 0, 'Unliving Sorcerer - Within 0-10 Range - Cast "<a href="http://wowhead.com/spell=22424">Blast Wave</a>" (Heroic Dungeon)');











