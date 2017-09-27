DELETE FROM npc_trainer WHERE entry IN (16501, 16761) AND spell = 3127;
INSERT INTO npc_trainer VALUES (16501, 3127, 100, 0, 0, 8), (16761, 3127, 100, 0, 0, 8);
