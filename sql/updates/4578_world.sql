UPDATE creature_template SET AIName = "SmartAI" WHERE entry = 3946;
DELETE FROM smart_scripts WHERE entryorguid = 3946;
INSERT INTO smart_scripts VALUES (3946, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Velinde - Speak at spawn");
INSERT INTO creature_text VALUES (3946, 0, 0, "I have failed... I have failed in my duty... failed my people... The worgen run rampant, and the Scythe of my goddess is lost.", "J'ai échoué... J'ai échoué dans mon devoir... Trahi mon peuple... Les worgens courent, et la Faux de ma déesse est perdue.", 1, 0, 100, 0, 0, 0, "Velinde - text");

