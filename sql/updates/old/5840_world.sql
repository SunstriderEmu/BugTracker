/* RoS update */
/* Suffering */
UPDATE creature_template SET mindmg = 800, maxdmg =1125 WHERE entry = 23418; 
UPDATE script_texts SET content_loc2 = "%s devient fou furieux !" WHERE entry = -1564054;
/* Desire */
UPDATE creature_template SET minhealth = 3000000, maxhealth = 30000000, mindmg = 9000, maxdmg = 12700 WHERE entry = 23419;
/* Anger */
UPDATE creature_template SET minhealth = 3000000, maxhealth = 30000000, mindmg = 11000, maxdmg = 15500 WHERE entry = 23420;