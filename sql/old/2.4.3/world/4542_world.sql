/* Fix displayId for void zone */
UPDATE creature_template SET modelid_A = 15882, modelid_H = 15882 WHERE entry = 25879;
