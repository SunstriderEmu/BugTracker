DELETE FROM creature_template WHERE entry = 90000;
INSERT INTO creature_template(entry,modelid_A,NAME,minhealth,maxhealth,faction_A,faction_H,flags_extra,scriptname)
VALUES (90000,892,'L\'informe',10000,10000,21,21,2,'custom_theinform');