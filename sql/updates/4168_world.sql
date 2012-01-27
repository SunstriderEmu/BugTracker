UPDATE creature_template SET unit_flags = unit_flags & ~0x100 WHERE entry = 19851;
UPDATE creature_template SET unit_flags = unit_flags & ~0x2000000 WHERE entry = 19849;
UPDATE quest_template SET SpecialFlags = 0, ReqCreatureOrGOId1 = 19851, ReqCreatureOrGOCount1 = 1 WHERE entry = 10248;
