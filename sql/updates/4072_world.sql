DELETE FROM npc_vendor WHERE item IN (21833, 21829, 21815);
DELETE FROM game_event_npc_vendor WHERE item IN (21833, 21829, 21815);

INSERT INTO game_event_npc_vendor (event, guid, item, maxcount, incrtime, ExtendedCost) SELECT 8, guid, 21833, 0, 0, 0 FROM creature JOIN creature_template ON creature_template.entry = creature.id WHERE npcflag & 0x10080 = 0x10080;
INSERT INTO game_event_npc_vendor (event, guid, item, maxcount, incrtime, ExtendedCost) SELECT 8, guid, 21829, 0, 0, 0 FROM creature JOIN creature_template ON creature_template.entry = creature.id WHERE npcflag & 0x10080 = 0x10080;
INSERT INTO game_event_npc_vendor (event, guid, item, maxcount, incrtime, ExtendedCost) SELECT 8, guid, 21815, 10, 43200, 0 FROM creature JOIN creature_template ON creature_template.entry = creature.id WHERE npcflag & 0x10080 = 0x10080;

DELETE FROM spell_linked_spell WHERE spell_trigger IN 526681, 26682);
INSERT INTO spell_linked_spell VALUES (26681, -26682, 0, "Love is in the Air Perfume"), (26682, -26681, 0, "Love is in the Air Perfume");
