REPLACE INTO spell_bonus_data VALUES
(15237, 0.163, -1,       -1,   -1,   'Priest - Holy Nova Damage');
REPLACE INTO spell_bonus_data VALUES
(23455, 0.163, -1,       -1,   -1,   'Priest - Holy Nova Heal');

DELETE FROM spell_bonus_data WHERE entry IN (23458,
                                             23459,
                                             27803,
                                             27804,
                                             27805,
                                             25329);
											 
DELETE FROM spell_bonus_data WHERE entry IN (15430,
                                             15431,
                                             27799,
                                             27800,
                                             27801,
                                             25331);