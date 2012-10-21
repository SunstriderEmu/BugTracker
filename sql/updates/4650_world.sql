UPDATE creature_template SET mechanic_immune_mask = mechanic_immune_mask | 0x820001 WHERE entry = 25772;

DELETE FROM creature_scripts WHERE entryorguid IN (6109, 25824);
INSERT INTO creature_scripts VALUES
(6109, "boss_azuregos_new"),
(25824, "npc_void_spawn");
