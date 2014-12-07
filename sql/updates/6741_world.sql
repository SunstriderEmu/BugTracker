#/!\ this update erase all attackpower in db
#With this the creatures damages should exactly match the old values, this sql patch reflect the re introduction of db attackpower for creatures in the core side

UPDATE creature_template SET baseattacktime = 2400 where baseattacktime < 50;
UPDATE creature_template SET rangeattacktime = 2400 where rangeattacktime < 50;

UPDATE creature_template SET baseattacktime = 2.4 WHERE baseattacktime = 0;
UPDATE creature_template SET attackpower = ROUND((mindmg + maxdmg) /6 / POWER(baseattacktime/1000,2) * 14);

UPDATE creature_template SET rangeattacktime = 2.4 WHERE rangeattacktime = 0;
UPDATE creature_template SET rangedattackpower = ROUND((minrangedmg + maxrangedmg) /6 / POWER(rangeattacktime/1000,2) * 14);