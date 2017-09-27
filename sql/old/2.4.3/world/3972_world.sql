UPDATE creature_template SET unit_flags = unit_flags | 0x2, flags_extra = 2 WHERE entry = 8130;

DELETE FROM areatrigger_scripts WHERE entry = 1447;
INSERT INTO areatrigger_scripts VALUES (1447, 'at_antusul');

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 8127;
DELETE FROM smart_scripts WHERE entryorguid = 8127;
INSERT INTO smart_scripts VALUES
(8127, 0, 0, 0, 4, 0, 100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - Aggro - Yells"),
(8127, 0, 1, 2, 4, 0, 100, 2, 0, 0, 0, 0, 12, 8138, 4, 30000, 0, 1, 0, 8, 0, 0, 0, 1813.572, 676.556, 14.0145, 0, "Antu'sul - Aggro - Summon Sul'lithuz Broodling"),
(8127, 0, 2, 3, 61, 0, 100, 2, 0, 0, 0, 0, 12, 8138, 4, 30000, 0, 1, 0, 8, 0, 0, 0, 1813.572, 676.556, 14.0145, 0, "Antu'sul - Aggro - Summon Sul'lithuz Broodling"),
(8127, 0, 3, 4, 61, 0, 100, 2, 0, 0, 0, 0, 12, 8138, 4, 30000, 0, 1, 0, 8, 0, 0, 0, 1813.572, 676.556, 14.0145, 0, "Antu'sul - Aggro - Summon Sul'lithuz Broodling"),
(8127, 0, 4, 5, 61, 0, 100, 2, 0, 0, 0, 0, 12, 8138, 4, 30000, 0, 1, 0, 8, 0, 0, 0, 1813.572, 676.556, 14.0145, 0, "Antu'sul - Aggro - Summon Sul'lithuz Broodling"),
(8127, 0, 5, 6, 61, 0, 100, 2, 0, 0, 0, 0, 12, 8138, 4, 30000, 0, 1, 0, 8, 0, 0, 0, 1813.572, 676.556, 14.0145, 0, "Antu'sul - Aggro - Summon Sul'lithuz Broodling"),
(8127, 0, 6, 0, 61, 0, 100, 2, 0, 0, 0, 0, 12, 8138, 4, 30000, 0, 1, 0, 8, 0, 0, 0, 1813.572, 676.556, 14.0145, 0, "Antu'sul - Aggro - Summon Sul'lithuz Broodling"),
(8127, 0, 7, 0, 2, 0, 100, 3, 70, 80, 0, 0, 12, 8156, 4, 30000, 0, 1, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - 80% health - Summon Servant of Antu'sul"),
(8127, 0, 8, 0, 2, 0, 100, 3, 50, 60, 0, 0, 12, 8156, 4, 30000, 0, 1, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - 60% health - Summon Servant of Antu'sul"),
(8127, 0, 9, 0, 2, 0, 100, 3, 30, 40, 0, 0, 12, 8156, 4, 30000, 0, 1, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - 40% health - Summon Servant of Antu'sul"),
(8127, 0, 10, 0, 2, 0, 100, 3, 10, 20, 0, 0, 12, 8156, 4, 30000, 0, 1, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - 20% health - Summon Servant of Antu'sul"),
(8127, 0, 11, 0, 0, 0, 100, 2, 5000, 8000, 15000, 22000, 11, 16006, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - IC Timer - Cast Chain Lightning"),
(8127, 0, 12, 0, 0, 0, 100, 2, 3000, 8000, 22000, 30000, 11, 11899, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - IC Timer - Cast Healing Ward"),
(8127, 0, 13, 0, 0, 0, 100, 2, 10000, 15000, 30000, 45000, 11, 8376, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - IC Timer - Cast Earthgrab Totem"),
(8127, 0, 14, 0, 0, 0, 100, 2, 10000, 22000, 10000, 25000, 11, 15501, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - IC Timer - Cast Earth Shock"),
(8127, 0, 15, 0, 0, 0, 100, 2, 15000, 20000, 30000, 45000, 11, 32062, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - IC Timer - Cast Fire Nova Totem"),
(8127, 0, 16, 0, 2, 0, 100, 2, 5, 40, 10000, 25000, 11, 12491, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - Less than 40% health - Cast Healing Wave"),
(8127, 0, 17, 0, 2, 0, 100, 2, 40, 80, 20000, 40000, 11, 11895, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Antu'Sul - 40-80% health - Cast Healing Wave of Antu'sul"),
(8127, 0, 18, 0, 17, 0, 100, 2, 8156, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - When summoning Servant - Yell"),
(8127, 0, 19, 0, 6, 0, 100, 2, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Antu'sul - Death - Yell");

DELETE FROM creature_text WHERE entry = 8127;
INSERT INTO creature_text (entry, groupid, id, text, `type`, probability, `comment`) VALUES
(8127, 0, 0, "Le déjeuner est servi, mes chers enfants. Écorchez-les vifs !", 1, 100, "Antu'sul - Aggro"),
(8127, 1, 0, "Levez-vous et défendez votre maître !", 1, 100, "Antu'sul - Summoning Servant of Antu'sul"),
(8127, 2, 0, "Les enchants de Sul protègeront leur maître. Vive Sul'lithuz !", 1, 100, "Antu'sul - Death");

UPDATE creature_template SET minlevel = 45, maxlevel = 47, mindmg = 89, maxdmg = 166, attackpower = 893 WHERE entry = 8149;
UPDATE creature_template SET faction_a = 107, faction_h = 107 WHERE entry = 8138;
