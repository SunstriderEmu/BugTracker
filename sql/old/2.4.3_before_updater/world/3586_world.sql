UPDATE creature_template SET AIName = 'SmartAI' WHERE entry = 15362;
DELETE FROM smart_scripts WHERE entryorguid IN (15362, 1536200);
INSERT INTO smart_scripts VALUES
(15362, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Remove quest giver flag'),
(15362, 0, 1, 0, 25, 0, 100, 1, 0, 0, 0, 0, 80, 1536200, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Start talking'),
(1536200, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Boss emote'),
(1536200, 9, 1, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Emote'),
(1536200, 9, 2, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Say text 2'),
(1536200, 9, 3, 0, 0, 0, 100, 0, 15000, 15000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Say text 3'),
(1536200, 9, 4, 0, 0, 0, 100, 0, 20000, 20000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Say text 4'),
(1536200, 9, 5, 0, 0, 0, 100, 0, 20000, 20000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Say text 5'),
(1536200, 9, 6, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 82, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Set quest giver flag');

DELETE FROM creature_text WHERE entry = 15362;
INSERT INTO creature_text VALUES
(15362, 0, 0, "The walls of the chamber tremble. Something is happening...", 3, 0, 100, 0, 0, 0, ''),
(15362, 1, 0, "Malfurion Stormrage bows.", 2, 0, 100, 2, 0, 0, ''),
(15362, 2, 0, "Be steadfast, champion. I know why it is that you are here and I know what it is that you seek. Eranikus will not give up the shard freely. He has been twisted... twisted by the same force that you seek to destroy.", 0, 0, 100, 1, 0, 0, ''),
(15362, 3, 0, "Are you really surprised? Is it hard to believe that the power of an Old God could reach even inside the Dream? It is true - Eranikus, Tyrant of the Dream, wages a battle against us all. The Nightmare follows in his wake of destruction.", 0, 0, 100, 1, 0, 0, ''),
(15362, 4, 0, "Understand this, Eranikus wants nothing more than to be brought to Azeroth from the Dream. Once he is out, he will stop at nothing to destroy my physical manifestation. This, however, is the only way in which you could recover the scepter shard.", 0, 0, 100, 1, 0, 0, ''),
(15362, 5, 0, "You will bring him back into this world, champion.", 0, 0, 100, 1, 0, 0, '');
