REPLACE INTO command (name, security, help) VALUES ("tests", 4, "This commands passes argument to catch, so see Catch documentation. You can also run .tests -? to get help directly from Catch.");

DELETE FROM COMMAND WHERE name LIKE "irc%";