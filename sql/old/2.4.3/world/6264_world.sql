UPDATE `creature_template` SET `spell5` = '45848' WHERE `creature_template`.`entry` = 25653;
UPDATE `creature_template` SET `spell1` = '45862' WHERE `creature_template`.`entry` = 25653;
UPDATE `creature_template` SET `spell4` = '0' WHERE `creature_template`.`entry` = 25653;
UPDATE `creature_template` SET `spell2` = '45856' WHERE `creature_template`.`entry` = 25653;

#Soldat du soleil brisé :
REPLACE INTO creature_equip_template VALUES (3005,38099,48068,0,33490690,1540,0,781,14,0);
UPDATE creature_template SET equipment_id = 3005 WHERE entry = 26259;

#Ouvrefaille du soleil brisé :
REPLACE INTO creature_equip_template VALUES (91534,47909,0,0,33490690,0,0,781,0,0);
UPDATE creature_template SET equipment_id = 91534 WHERE entry = 26289; 

UPDATE `creature_equip_template` SET `equipslot1` = '10', `equipinfo1` = '772' WHERE `entry` = 3004;
UPDATE creature_template SET flags_extra = 2 WHERE entry = 7997;