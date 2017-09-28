UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 9457;

DELETE FROM smart_scripts WHERE entryorguid = 9457;
INSERT INTO smart_scripts VALUES
(9457, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Horde Axe Thrower - Stop combat movement on aggro"),
(9457, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Horde Axe Thrower - Allow combat movement on reset"),
(9457, 0, 2, 0, 0, 0, 100, 0, 2000, 3000, 2000, 3000, 11, 10277, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Horde Axe Thrower - Cast Throw"),
(9457, 0, 3, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Horde Axe Thrower - Say text on aggro");

DELETE FROM creature_text WHERE entry = 9457;
INSERT INTO creature_text VALUES
(9457, 0, 0, "Défendez les bunkers !", 0, 0, 50, 0, 0, 0, "Horde Axe Thrower - Aggro"),
(9457, 0, 1, "Nos ennemis vont tomber !", 0, 0, 50, 0, 0, 0, "Horde Axe Thrower - Aggro"),
(9457, 0, 2, "Pour la Horde !", 0, 0, 50, 0, 0, 0, "Horde Axe Thrower - Aggro");

UPDATE creature_template SET ScriptName = "npc_regthar_deathgate" WHERE entry = 3389;

DELETE FROM script_texts WHERE entry BETWEEN -1000803 AND -1000800;
INSERT INTO script_texts (entry, content_default, content_loc2, type, comment) VALUES
(-1000800, "Half way there...", "La moitié est morte...", 1, "YELL_COUNTERATTACK_LANTIGAH"),
(-1000801, "A defender has fallen!", "Un défenseur est tombé !", 0, "SAY_COUNTERATTACK_DEFENDER"),
(-1000802, "Beware, $N! Look to the west!", "Faites attention, $N. Regardez à l'ouest !", 0, "SAY_COUNTERATTACK_BEWARE"),
(-1000803, "The Kolkar are the strongest!", "Les Kolkars sont les plus forts !", 1, "YELL_COUNTERATTACK_KROMZAR");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 9456;

DELETE FROM smart_scripts WHERE entryorguid = 9456;
INSERT INTO smart_scripts VALUES
(9456, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 32064, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Warlord Krom'zar - Cast Battle Shout on aggro"),
(9456, 0, 1, 0, 0, 0, 100, 0, 1000, 2000, 3000, 5000, 11, 11976, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Warlord Krom'zar - Cast Strike on victim");
