UPDATE gameobject_template SET scriptname = "go_blue_cluster" WHERE name = "Blue Cluster";
UPDATE gameobject_template SET scriptname = "go_green_cluster" WHERE name = "Green Cluster";
UPDATE gameobject_template SET scriptname = "go_red_cluster" WHERE name = "Red Cluster";
UPDATE gameobject_template SET scriptname = "go_yellow_cluster" WHERE name = "Yellow Cluster";

DELETE FROM spell_script_target WHERE entry IN (40165, 40166, 40167, 40055, 40437);
INSERT INTO spell_script_target VALUES (40165, 2, 0), (40166, 2, 0), (40167, 2, 0), (40055, 2, 0), (40437, 2, 0);
