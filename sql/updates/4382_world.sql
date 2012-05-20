UPDATE trinity_string SET content_default = "|cffff0000[Automatic]: %s|r", content_loc2 = "|cffff0000[Automatique]: %s|r" WHERE entry = 786;

DROP TABLE IF EXISTS auto_ann_by_time;
CREATE TABLE auto_ann_by_time ( id INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY, message TEXT NOT NULL DEFAULT '', hour INTEGER NOT NULL DEFAULT 0, minute INTEGER NOT NULL DEFAULT 0 ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
INSERT INTO auto_ann_by_time VALUES ('', "A partir de 20h, session d'arène dédiée à la 3v3 !", 19, 30), ('', "La session d'arène dédiée à la 3v3 commence pour une durée de 2 heures !", 20, 00);
