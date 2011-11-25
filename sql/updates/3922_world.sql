DELETE FROM quest_mail_loot_template WHERE entry = 161;
INSERT INTO quest_mail_loot_template VALUES (161, 21216, 100, 0, 20, 20, 0, 0, 0);
UPDATE quest_template SET RewMailTemplateId = 161 WHERE entry IN (8746, 8762);
