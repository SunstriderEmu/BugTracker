UPDATE creature_template SET ScriptName = "npc_monty" WHERE entry = 12997;
DELETE FROM script_texts WHERE entry = -1000765;
INSERT INTO script_texts (entry, content_default, content_loc2, comment) VALUES (-1000765, "Into the box me pretties! Thas it. One by one ye go.", "Dans la boîte mes jolis ! C'est ça. Un par un.", "Monty - Quest 6661");
