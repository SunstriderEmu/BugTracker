UPDATE creature_template SET ScriptName = "npc_overlord_mokmorokk" WHERE entry = 4500;
UPDATE creature_questrelation SET id = 23951 WHERE quest = 1220;
UPDATE creature_template SET ScriptName = "npc_stinky" WHERE entry = 4880;

DELETE FROM creature_questrelation WHERE quest = 1288;
INSERT INTO creature_questrelation (id, quest) VALUES (4944, 1288);

UPDATE creature_template SET unit_flags = unit_flags | 0x80 WHERE entry = 17119;

UPDATE item_template SET maxcount = 0 WHERE entry = 4614;
