#fixed Darkness of a Thousand Souls damages
UPDATE spell_template SET effectBasePoints3 = 45657 WHERE id = 46605;

UPDATE creature_template SET AIName = "PassiveAI" WHERE entry = 25608;
UPDATE spell_template SET effectImplicitTargetB1 = 25 WHERE id = 45680;