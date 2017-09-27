UPDATE quest_template SET RewMailTemplateId = 108, RewMailDelaySecs = 86400 WHERE entry IN (6963, 7042);
DELETE FROM quest_mail_loot_template WHERE entry IN (6963, 7042);
INSERT INTO quest_mail_loot_template VALUES (6963, 17712, 100, 0, 1, 1, 0, 0, 0), (7042, 17712, 100, 0, 1, 1, 0, 0, 0);
