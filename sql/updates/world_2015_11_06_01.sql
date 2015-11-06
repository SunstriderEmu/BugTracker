#remove CREATURE_TYPEFLAGS_BOSS from some creatures
UPDATE creature_template SET type_flags = type_flags - 4 WHERE entry IN (15,25,621);

#remove some CREATURE_TYPEFLAGS_GHOST from some creatures
UPDATE creature_template SET type_flags = type_flags - 2 WHERE entry IN (11,41,42,45,8999,91455,91503,91554);