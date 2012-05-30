/* Void Spawn */
UPDATE creature_template SET AIName = "" where entry = 25824;

DELETE FROM creature_scripts WHERE entryorguid = 25824;
INSERT INTO creature_scripts (entryorguid, scriptname) VALUES (25824, 'npc_void_spawn');
