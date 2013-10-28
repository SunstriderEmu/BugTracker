#Demoralizing Roar threat
REPLACE INTO spell_threat (entry,flatMod) VALUES 
(99,7),
(1735,14),
(9490,22),
(9747,28),
(9898,35),
(26998,42);

#lacerate
UPDATE spell_threat SET flatMod = 1425 WHERE entry = 33745;