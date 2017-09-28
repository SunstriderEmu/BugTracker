DELETE FROM smart_scripts WHERE entryorguid = 26101;

UPDATE creature_template SET AIName = '', ScriptName = 'npc_fire_fiend' WHERE entry = 26101;
