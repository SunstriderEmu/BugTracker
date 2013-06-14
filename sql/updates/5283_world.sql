DELETE FROM command WHERE name IN ("debug playerflags", "debug profile");
INSERT INTO command (name, security) VALUES
("debug playerflags", 5),
("debug profile", 5);
