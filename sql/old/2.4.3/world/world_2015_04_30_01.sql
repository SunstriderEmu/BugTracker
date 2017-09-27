#fixing some incorrects chat types in creature_text
UPDATE creature_text SET TYPE = 2 WHERE TYPE = 16;
UPDATE creature_text SET TYPE = 1 WHERE TYPE = 14;
UPDATE creature_text SET TYPE = 0 WHERE TYPE = 12;

#removing some duplicates scripts
DELETE FROM quest_end_scripts WHERE id = 3321;
DELETE FROM smart_scripts WHERE entryorguid = 2391 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 2921 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 3692 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 3692 AND id = 1;
DELETE FROM smart_scripts WHERE entryorguid = 3693 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 6176 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 6546 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 7207 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 7790 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 7802 AND id = 1;
DELETE FROM smart_scripts WHERE entryorguid = 7802 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 7804 AND id = 1;
DELETE FROM smart_scripts WHERE entryorguid = 7853 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 9117 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 21797 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 22373 AND id = 0;
DELETE FROM smart_scripts WHERE entryorguid = 23905 AND id = 1;

DELETE FROM smart_scripts WHERE entryorguid = 6546 AND id = 2;
DELETE FROM smart_scripts WHERE entryorguid = 7750 AND id = 0;

DELETE FROM quest_start_scripts WHERE id = 1149 AND dataint = 2000000042;
DELETE FROM quest_start_scripts WHERE id = 945 AND command = 3;
DELETE FROM quest_start_scripts WHERE id = 945 and dataint = 2000000017;
DELETE FROM quest_start_scripts WHERE id = 945 AND dataint = 2000000018;
DELETE FROM quest_start_scripts WHERE id = 11198 AND dataint = 2000000033;
DELETE FROM quest_start_scripts WHERE id = 9962 and dataint = 2000000001;
DELETE FROM quest_start_scripts WHERE id = 9962 and dataint = 2000000003;
DELETE FROM quest_start_scripts WHERE id = 9962 and dataint = 2000000002;
 
