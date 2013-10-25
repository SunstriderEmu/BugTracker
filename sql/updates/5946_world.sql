ALTER TABLE command ADD COLUMN ircAllowed BOOL DEFAULT '0';
UPDATE version SET core_version = "Windrunner Rev : 4946";