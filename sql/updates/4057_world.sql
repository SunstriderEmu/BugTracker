DELETE FROM gameobject WHERE guid BETWEEN 1000000 AND 1000004;
DELETE FROM gameobject WHERE id IN (180875, 180777, 180850, 180859);

INSERT INTO gameobject VALUES
(1000000, 180875, 1, 1, 7533.79, -2847.35, 459.247, 5.46736, 0, 0, 0.396692, -0.917952, 25, 0, 1),
(1000001, 180771, 1, 1, 7533.22, -2847.72, 460.413, 0.759774, 0, 0, 0.370816, 0.928706, 25, 0, 1),
(1000002, 180772, 1, 1, 7534.23, -2846.77, 460.413, 0.759774, 0, 0, 0.370816, 0.928706, 25, 0, 1),
(1000003, 180777, 1, 1, 7532.19, -2845.68, 459.757, 2.21494, 0, 0, 0.894571, 0.446925, 25, 0, 1),
(1000004, 180777, 1, 1, 7535.13, -2849.04, 458.702, 2.28519, 0, 0, 0.909715, 0.415234, 25, 0, 1);

DELETE FROM game_event_gameobject WHERE guid BETWEEN 1000000 AND 1000004;
INSERT INTO game_event_gameobject VALUES
(1000000, 7), (1000001, 7), (1000002, 7), (1000003, 7), (1000004, 7);

-- ImplicitTargetA1 was 40
UPDATE spell_template SET effectImplicitTargetA1 = 38 WHERE id IN (26286, 26292, 26294, 26295, 26293);
UPDATE spell_template SET effectImplicitTargetA1 = 46, effectImplicitTargetA2 = 38 WHERE id = 26291;
DELETE FROM spell_script_target WHERE entry IN (26286, 26291, 26292, 26294, 26295, 26293);
INSERT INTO spell_script_target VALUES (26286, 0, 180771), (26291, 0, 180771), (26292, 0, 180771), (26294, 0, 180771), (26295, 0, 180771), (26293, 0, 180771);
DELETE FROM spell_script_target WHERE entry IN (26344, 26345, 26347, 26348, 26349, 26346);
INSERT INTO spell_script_target VALUES (26344, 0, 180771), (26345, 0, 180771), (26347, 0, 180771), (26348, 0, 180771), (26349, 0, 180771), (26346, 0, 180771);

UPDATE spell_template SET durationIndex = 29 WHERE id IN (26286, 26291, 26292, 26294, 26295, 26293);
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (15882, 15879, 15880, 15884, 15883, 15881);
DELETE FROM smart_scripts WHERE entryorguid IN (15882, 15879, 15880, 15884, 15883, 15881);
INSERT INTO smart_scripts VALUES
(15882, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26347, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Red Rocket"),
(15882, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Red Rocket - Set data"),
(15879, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26344, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Blue Rocket"),
(15879, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Blue Rocket - Set data"),
(15880, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26345, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Green Rocket"),
(15880, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Green Rocket - Set data"),
(15884, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26348, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - White Rocket"),
(15884, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - White Rocket - Set data"),
(15883, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26349, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Yellow Rocket"),
(15883, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Yellow Rocket - Set data"),
(15881, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26346, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Purple Rocket"),
(15881, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Purple Rocket - Set data");

UPDATE creature_template SET flags_extra = flags_extra | 130 WHERE entry IN (15882, 15879, 15880, 15884, 15883, 15881);

DELETE FROM spell_script_target WHERE entry = 26521;
INSERT INTO spell_script_target VALUES
(26521, 0, 180772);

UPDATE spell_template SET effectImplicitTargetA1 = 38 WHERE id = 26521;
UPDATE spell_template SET durationIndex = 29 WHERE id = 26521;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 15918;
DELETE FROM smart_scripts WHERE entryorguid = 15918;
INSERT INTO smart_scripts VALUES
(15918, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26351, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lucky Lunar Rocket"),
(15918, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26351, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lucky Lunar Rocket"),
(15918, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26355, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lucky Lunar Rocket"),
(15918, 0, 3, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26355, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lucky Lunar Rocket"),
(15918, 0, 4, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26355, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lucky Lunar Rocket");

UPDATE spell_template SET effect3 = 64, effectTriggerSpell3 = 26522 WHERE id = 26521;
UPDATE spell_template SET effectImplicitTargetA1 = 1, effectImplicitTargetB1 = 0 WHERE id = 26522;

UPDATE creature_template SET flags_extra = flags_extra | 130 WHERE entry = 15918;

UPDATE spell_template SET effectImplicitTargetA1 = 38 WHERE id IN (26333, 26334, 26336, 26337, 26338, 26335);
DELETE FROM spell_script_target WHERE entry IN (26333, 26334, 26336, 26337, 26338, 26335);
INSERT INTO spell_script_target VALUES (26333, 0, 180771), (26334, 0, 180771), (26336, 0, 180771), (26337, 0, 180771), (26338, 0, 180771), (26335, 0, 180771);
DELETE FROM spell_script_target WHERE entry IN (26351, 26352, 26354, 26355, 26356, 26353);
INSERT INTO spell_script_target VALUES (26351, 0, 180771), (26352, 0, 180771), (26354, 0, 180771), (26355, 0, 180771), (26356, 0, 180771), (26353, 0, 180771);

UPDATE spell_template SET durationIndex = 29 WHERE id IN (26333, 26334, 26336, 26337, 26338, 26353);
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (15885, 15886, 15888, 15889, 15890, 15887);
DELETE FROM smart_scripts WHERE entryorguid IN (15885, 15886, 15888, 15889, 15890, 15887);
INSERT INTO smart_scripts VALUES
(15885, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26351, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Blue Rocket"),
(15885, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Big Blue Rocket - Set data"),
(15886, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26352, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Green Rocket"),
(15886, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Big Green Rocket - Set data"),
(15888, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26354, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Red Rocket"),
(15888, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Big Red Rocket - Set data"),
(15889, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26355, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big White Rocket"),
(15889, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Big White Rocket - Set data"),
(15890, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26356, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Yellow Rocket"),
(15890, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Big Yellow Rocket - Set data"),
(15887, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26353, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Purple Rocket"),
(15887, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 29092, 15, 0, 0, 0, 0, 0, "Lunar Festival - Big Purple Rocket - Set data");

UPDATE creature_template SET flags_extra = flags_extra | 130 WHERE entry IN (15885, 15886, 15888, 15889, 15890, 15887);

UPDATE spell_template SET effectImplicitTargetA1 = 38 WHERE id IN (26516, 26517, 26518, 26519, 26488, 26490, 26325, 26304, 26329, 26328, 26327, 26326, 26521); 

DELETE FROM spell_script_target WHERE entry IN (26516, 26517, 26518, 26519, 26488, 26490, 26325, 26304, 26329, 26328, 26327, 26326);
INSERT INTO spell_script_target VALUES (26516, 0, 180772), (26517, 0, 180772), (26518, 0, 180772), (26519, 0, 180772), (26488, 0, 180772), (26490, 0, 180772), (26325, 0, 180772), (26304, 0, 180772), (26329, 0, 180772), (26328, 0, 180772), (26327, 0, 180772), (26326, 0, 180772);

UPDATE spell_template SET effectMiscValue2 = 15913 WHERE id = 26516;
UPDATE spell_template SET effectMiscValue2 = 15914 WHERE id = 26517;
UPDATE spell_template SET effectMiscValue2 = 15915 WHERE id = 26518;
UPDATE spell_template SET effectMiscValue2 = 15916 WHERE id = 26519; 
UPDATE spell_template SET effectMiscValue2 = 15911 WHERE id = 26488;
UPDATE spell_template SET effectMiscValue2 = 15912 WHERE id = 26490;
UPDATE spell_template SET effectMiscValue2 = 15874 WHERE id = 26325;
UPDATE spell_template SET effectMiscValue2 = 15872 WHERE id = 26304;
UPDATE spell_template SET effectMiscValue2 = 15877 WHERE id = 26329;
UPDATE spell_template SET effectMiscValue2 = 15876 WHERE id = 26328;
UPDATE spell_template SET effectMiscValue2 = 15873 WHERE id = 26327;
UPDATE spell_template SET effectMiscValue2 = 15875 WHERE id = 26326;

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (15913, 15914, 15915, 15916, 15911, 15912, 15874, 15872, 15877, 15876, 15873, 15875);
DELETE FROM smart_scripts WHERE entryorguid IN (15913, 15914, 15915, 15916, 15911, 15912, 15874, 15872, 15877, 15876, 15873, 15875);
INSERT INTO smart_scripts VALUES
(15913, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26353, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Purple Cluster"),
(15913, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26353, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Purple Cluster"),
(15913, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26353, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Purple Cluster"),
(15914, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26354, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Red Cluster"),
(15914, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26354, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Red Cluster"),
(15914, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26354, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Red Cluster"),
(15915, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26355, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big White Cluster"),
(15915, 1, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26355, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big White Cluster"),
(15915, 2, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26355, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big White Cluster"),
(15916, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26356, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Yellow Cluster"),
(15916, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26356, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Yellow Cluster"),
(15916, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26356, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Yellow Cluster"),
(15911, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26351, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Blue Cluster"),
(15911, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26351, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Blue Cluster"),
(15911, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26351, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Blue Cluster"),
(15912, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26352, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Green Cluster"),
(15912, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26352, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Green Cluster"),
(15912, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26352, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Big Green Cluster"),

(15874, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26345, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Green Cluster"),
(15874, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26345, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Green Cluster"),
(15874, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26345, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Green Cluster"),
(15872, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26344, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Blue Cluster"),
(15872, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26344, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Blue Cluster"),
(15872, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26344, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Blue Cluster"),
(15877, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26349, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Yellow Cluster"),
(15877, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26349, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Yellow Cluster"),
(15877, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26349, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Yellow Cluster"),
(15876, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26348, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - White Cluster"),
(15876, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26348, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - White Cluster"),
(15876, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26348, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - White Cluster"),
(15873, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26347, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Red Cluster"),
(15873, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26347, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Red Cluster"),
(15873, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26347, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Red Cluster"),
(15875, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26346, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Purple Cluster"),
(15875, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26346, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Purple Cluster"),
(15875, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 26346, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival - Purple Cluster");

UPDATE creature_template SET faction_a = 14, faction_h = 14 WHERE entry = 15466;
UPDATE creature_template SET minhealth = 1044860, maxhealth = 1044860, flags_extra = flags_extra | 0x40000, regenhealth = 0 WHERE entry = 15467;

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 15467;
DELETE FROM smart_scripts WHERE entryorguid = 15467;
INSERT INTO smart_scripts VALUES
(15467, 0, 0, 0, 0, 0, 100, 0, 2000, 8000, 6000, 6000, 11, 26540, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Omen - IC Timer - Cast Starfall"),
(15467, 0, 1, 0, 0, 0, 100, 0, 10000, 12000, 18000, 25000, 11, 31345, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Omen - IC Timer - Cast Cleave"),
(15467, 0, 2, 0, 1, 0, 100, 1, 300000, 300000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Omen - OOC Timer - Despawn after 5 minutes"),
(15467, 0, 3, 4, 6, 0, 100, 0, 0, 0, 0, 0, 11, 26392, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Omen - Death - Cast Omen's Moonlight"),
(15467, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 75, 25824, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Omen - Death - Cast Spotlight");

DELETE FROM spell_script_target WHERE entry = 26393;
INSERT INTO spell_script_target VALUES (26393, 1, 12999);

DELETE FROM gameobject_template WHERE entry = 180877;
INSERT INTO gameobject_template VALUES (180877, 6, 327, "Elune's Blessing TRAP QUESTCREDIT", "", 35, 0, 0.01, 0, 255, 8, 26394, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", "");

UPDATE spell_template SET effectImplicitTargetA1 = 3, effectImplicitTargetB1 = 3, effectImplicitTargetA2 = 3, effectImplicitTargetB2 = 3 WHERE id = 26393;
UPDATE spell_template SET effectImplicitTargetA1 = 1, effectImplicitTargetB1 = 0, effectImplicitTargetA2 = 0, effectImplicitTargetB2 = 0 WHERE id = 26394;

DELETE FROM creature_template WHERE entry = 29092;
INSERT INTO creature_template (entry, modelid_A, modelid_H, name, minlevel, maxlevel, minhealth, maxhealth, faction_a, faction_h, unit_flags, flags_extra, AIName, ScriptName) VALUES (29092, 1126, 1126, "Omen trigger", 60, 60, 5000, 5000, 35, 35, 0x2000002, 130, "", "trigger_omen");

DELETE FROM creature WHERE id = 29092;
DELETE FROM creature WHERE guid = 1000149;
INSERT INTO creature VALUES (1000149, 29092, 1, 1, 0, 0, 7531.92, -2849.25, 458.895, 0.654924, 25, 0, 0, 5000, 0, 0, 0, 0, "");

DELETE FROM game_event_creature WHERE guid = 1000149;
INSERT INTO game_event_creature VALUES (1000149, 7);

UPDATE gameobject_template SET data1 = 2 WHERE entry = 300058;

UPDATE gameobject SET id = 180771 WHERE id IN (180850, 180868);
UPDATE gameobject SET id = 180772 WHERE id IN (180859, 180869, 180874);

SET @GUID := 1000005;
DELETE FROM gameobject WHERE id = 300058;
DELETE FROM gameobject WHERE guid BETWEEN @GUID AND @GUID+12;
INSERT INTO `gameobject` VALUES
(@GUID,300058,0,1,1642.07,239.839,62.5916,0.802851,0,0,0.390731,0.920505,25,0,1),
(@GUID+1,300058,1,1,-1031.95,-230.513,160.16,3.9619,0,0,0.91706,-0.39875,25,0,1),
(@GUID+2,300058,1,1,1983.05,-4255.89,31.6872,2.07694,0,0,0.861629,0.507539,25,0,1),
(@GUID+3,300058,0,1,-4663.16,-956.235,500.377,0.05236,0,0,0.026177,0.999657,25,0,1),
(@GUID+4,300058,0,1,-8748.48,1074.25,90.5373,0.471239,0,0,0.233445,0.97237,25,0,1),
(@GUID+5,300058,1,1,7570.15,-2220.81,473.438,3.85718,0,0,0.936672,-0.350209,25,0,1),
(@GUID+6,300058,1,1,7610.8,-2228.96,468.678,1.27409,0,0,0.594823,0.803857,25,0,1),
(@GUID+7,300058,1,1,7575.25,-2238.94,469.772,1.02974,0,0,0.492422,0.870357,25,0,1),
(@GUID+8,300058,1,1,7603.55,-2211.26,471.663,3.12414,0,0,0.999962,0.0087262,25,0,1),
(@GUID+9,300058,1,1,7585.15,-2205.24,475.287,0.959931,0,0,0.461749,0.887011,25,0,1),
(@GUID+10,300058,1,1,7595.64,-2247.22,466.874,4.32842,0,0,0.829037,-0.559194,25,0,1),
(@GUID+11,300058,1,1,10150.355469,2601.757568,1330.827515,4.716997,0,0,0.705476,-0.708734,25,0,1);

DELETE FROM game_event_gameobject WHERE guid BETWEEN @GUID AND @GUID+11;
INSERT INTO game_event_gameobject VALUES
(@GUID, 7), (@GUID+1, 7), (@GUID+2, 7), (@GUID+3, 7), (@GUID+4, 7), (@GUID+5, 7), (@GUID+6, 7), (@GUID+7, 7), (@GUID+8, 7), (@GUID+9, 7), (@GUID+10, 7), (@GUID+11, 7);

DELETE FROM creature WHERE guid = 1000150;
INSERT INTO creature (guid, id, map, spawnMask, position_x, position_y, position_z, orientation, spawntimesecs) VALUES
(1000150, 15897, 1, 1, 10150.355469, 2601.757568, 1330.827515, 4.716997, 25);

DELETE FROM game_event_creature WHERE guid = 1000150;
INSERT INTO game_event_creature VALUES (1000150, 7);

DELETE FROM creature_addon WHERE guid = 1000150;
INSERT INTO creature_addon VALUES (1000150, 0, 0, 16908544, 0, 4097, 0, 0, "25824 0");

DELETE FROM spell_script_target WHERE entry = 26373;
INSERT INTO spell_script_target VALUES (26373, 1, 15897);

UPDATE creature_template SET ScriptName = "lunar_large_spotlight" WHERE entry = 15897;

DELETE FROM creature WHERE guid BETWEEN 1000151 AND 1000155;
INSERT INTO `creature` VALUES
(1000151,15892,1,1,0,0,10151.2,2598.15,1330.83,1.70678,25,0,0,5725,0,0,0,0,''),
(1000152,15892,1,1,0,0,10153,2604.66,1330.83,3.86444,25,0,0,5725,0,0,0,0,''),
(1000153,15892,1,1,15873,0,10147.2,2603.22,1330.83,5.6257,25,0,0,5725,0,0,0,0,''),
(1000154,15895,1,1,0,0,10146,2595.14,1330.83,1.07868,25,0,0,5800,5013,0,0,0,''),
(1000155,15898,1,1,0,0,10156.7,2598.28,1330.83,2.67937,25,0,0,1500,5013,0,0,0,'');

DELETE FROM game_event_creature WHERE guid BETWEEN 1000151 AND 1000155;
INSERT INTO game_event_creature VALUES
(1000151, 7), (1000152, 7), (1000153, 7), (1000154, 7), (1000155, 7);

DELETE FROM gameobject WHERE guid BETWEEN @GUID+12 AND @GUID+23;
INSERT INTO `gameobject` VALUES
(@GUID+12,180771,1,1,10156.2,2601.08,1330.83,1.93673,0,0,0.823961,0.566646,25,0,1),
(@GUID+13,180771,1,1,10146.2,2597.28,1330.83,1.93673,0,0,0.823961,0.566646,25,0,1),
(@GUID+14,180771,1,1,10143.4,2604.82,1330.83,1.93673,0,0,0.823961,0.566646,25,0,1),
(@GUID+15,180771,1,1,10146.5,2606.02,1330.83,1.93673,0,0,0.823961,0.566646,25,0,1),
(@GUID+16,180771,1,1,10150.4,2607.51,1330.83,1.93673,0,0,0.823961,0.566646,25,0,1),
(@GUID+17,180771,1,1,10153.6,2608.74,1330.83,1.93673,0,0,0.823961,0.566646,25,0,1),
(@GUID+18,180772,1,1,10155.5,2603.78,1330.83,1.92168,0,0,0.819673,0.572832,25,0,1),
(@GUID+19,180772,1,1,10154.7,2605.75,1330.83,1.92168,0,0,0.819673,0.572832,25,0,1),
(@GUID+20,180772,1,1,10154.2,2607.28,1330.83,1.92168,0,0,0.819673,0.572832,25,0,1),
(@GUID+21,180772,1,1,10143.9,2603.53,1330.83,1.92168,0,0,0.819673,0.572832,25,0,1),
(@GUID+22,180772,1,1,10144.6,2601.79,1330.83,1.92168,0,0,0.819673,0.572832,25,0,1),
(@GUID+23,180772,1,1,10145.4,2599.62,1330.83,1.92168,0,0,0.819673,0.572832,25,0,1);

DELETE FROM game_event_gameobject WHERE guid BETWEEN @GUID+12 AND @GUID+23;
INSERT INTO game_event_gameobject VALUES
(@GUID+12, 7), (@GUID+13, 7), (@GUID+14, 7), (@GUID+15, 7), (@GUID+16, 7), (@GUID+17, 7), (@GUID+18, 7), (@GUID+19, 7), (@GUID+20, 7), (@GUID+21, 7), (@GUID+22, 7), (@GUID+23, 7);

DELETE FROM gameobject WHERE guid BETWEEN @GUID+24 AND @GUID+33;
INSERT INTO `gameobject` VALUES
(@GUID+24,180766,1,1,10154.3,2593.9,1330.76,0.115266,0,0,0.0576012,0.99834,25,0,1),
(@GUID+25,180766,1,1,10149.2,2592.56,1330.69,0.215623,0,0,0.107603,0.994194,25,0,1),
(@GUID+26,180766,1,1,10142.2,2599.96,1330.83,1.82133,0,0,0.789911,0.613222,25,0,1),
(@GUID+27,180766,1,1,10159,2604.06,1330.83,4.45154,0,0,0.793064,-0.609138,25,0,1),
(@GUID+28,180766,1,1,10152.6,2571.56,1320.48,4.12075,0,0,0.88253,-0.470256,25,0,1),
(@GUID+29,180766,1,1,10148.3,2573.68,1320.53,1.02476,0,0,0.490253,0.87158,25,0,1),
(@GUID+30,180777,1,1,10153.6,2571.21,1320.53,4.13668,0,0,0.878757,-0.47727,25,0,1),
(@GUID+31,180777,1,1,10147.4,2574.06,1320.66,1.15522,0,0,0.546025,0.837769,25,0,1),
(@GUID+32,180777,1,1,10147.9,2592.72,1330.72,1.44124,0,0,0.659851,0.751397,25,0,1),
(@GUID+33,180777,1,1,10156.3,2594.28,1330.51,5.04993,0,0,0.578287,-0.815833,25,0,1);

DELETE FROM game_event_gameobject WHERE guid BETWEEN @GUID+24 AND @GUID+33;
INSERT INTO game_event_gameobject VALUES
(@GUID+24, 7), (@GUID+25, 7), (@GUID+26, 7), (@GUID+27, 7), (@GUID+28, 7), (@GUID+29, 7), (@GUID+30, 7), (@GUID+31, 7), (@GUID+32, 7), (@GUID+33, 7);

UPDATE creature_addon JOIN creature ON creature.guid = creature_addon.guid SET emote = 10 WHERE creature.id IN (15694, 15906, 15907, 15908, 15905, 15719);

DELETE FROM item_loot_template WHERE entry BETWEEN 21740 AND 21743;
INSERT INTO item_loot_template VALUES
(21740, 21726, 0, 1, 1, 1, 0, 0, 0),
(21740, 21725, 0, 1, 1, 1, 0, 0, 0),
(21740, 21724, 0, 1, 1, 1, 0, 0, 0),

(21741, 21732, 0, 1, 1, 1, 0, 0, 0),
(21741, 21731, 0, 1, 1, 1, 0, 0, 0),
(21741, 21730, 0, 1, 1, 1, 0, 0, 0),

(21742, 21729, 0, 1, 1, 1, 0, 0, 0),
(21742, 21728, 0, 1, 1, 1, 0, 0, 0),
(21742, 21727, 0, 1, 1, 1, 0, 0, 0),

(21743, 21735, 0, 1, 1, 1, 0, 0, 0),
(21743, 21734, 0, 1, 1, 1, 0, 0, 0),
(21743, 21733, 0, 1, 1, 1, 0, 0, 0);

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (15694, 15906, 15907, 15908, 15905, 15719);
DELETE FROM smart_scripts WHERE entryorguid IN (15694, 15906, 15907, 15908, 15905, 15719);
INSERT INTO smart_scripts VALUES
(15694, 0, 0, 0, 22, 0, 100, 0, 34, 100, 100, 0, 11, 26035, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival Reveler - Buff player on /dance"),
(15906, 0, 0, 0, 22, 0, 100, 0, 34, 100, 100, 0, 11, 26035, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival Reveler - Buff player on /dance"),
(15907, 0, 0, 0, 22, 0, 100, 0, 34, 100, 100, 0, 11, 26035, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival Reveler - Buff player on /dance"),
(15908, 0, 0, 0, 22, 0, 100, 0, 34, 100, 100, 0, 11, 26035, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival Reveler - Buff player on /dance"),
(15905, 0, 0, 0, 22, 0, 100, 0, 34, 100, 100, 0, 11, 26035, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival Reveler - Buff player on /dance"),
(15719, 0, 0, 0, 22, 0, 100, 0, 34, 100, 100, 0, 11, 26035, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Lunar Festival Reveler - Buff player on /dance");
