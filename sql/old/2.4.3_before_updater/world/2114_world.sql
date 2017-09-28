UPDATE gameobject_template SET type = 1 WHERE entry = 176215;
UPDATE gameobject_template SET scriptname = "go_cannonball_stack" WHERE entry = 176215;

UPDATE gameobject_template SET scriptname = "go_scarlet_cannon" WHERE entry IN (176216, 176217);
UPDATE gameobject SET spawntimesecs = 2 WHERE id IN (176216, 176217);
UPDATE gameobject_template SET data5 = 1 WHERE entry IN (176216, 176217); -- Was 0
