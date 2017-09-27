UPDATE creature SET position_x=-8643.06,position_y=2019.63,position_z=108.76,orientation=3.65 WHERE id=15378 AND map=531;
UPDATE creature SET position_x=-8666.49,position_y=2037.38,position_z=108.76,orientation=4.31 WHERE id=15380 AND map=531;
UPDATE creature_template SET faction_A=31,faction_H=31 WHERE entry BETWEEN 15378 AND 15380;
