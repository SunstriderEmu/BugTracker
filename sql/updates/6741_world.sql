#/!\ this update erase all attackpower in db
#With this the creatures damages should exactly match the old values, this sql patch reflect the re introduction of db attackpower for creatures in the core side
UPDATE creature_template SET baseattacktime = 2.4 WHERE baseattacktime = 0;
UPDATE creature_template SET attackpower = ((mindmg + maxdmg) /6 / POWER(baseattacktime,2) * 14);

UPDATE creature_template SET rangeattacktime = 2.4 WHERE rangeattacktime = 0;
UPDATE creature_template SET rangedattackpower = ((minrangedmg + maxrangedmg) /6 / POWER(rangeattacktime,2) * 14);