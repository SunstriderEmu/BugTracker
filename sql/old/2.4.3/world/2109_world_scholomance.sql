UPDATE gameobject_template SET scriptname = "go_scholo_torch" WHERE entry = 176767;
INSERT INTO eventai_scripts (id, creature_id, event_type, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action1_type, action1_param1, action1_param2, action1_param3, comment) VALUES (1050612, 10506, 6, 100, 3, 0, 0, 0, 0, 34, 8, 3, 0, "Set instance data at death");
