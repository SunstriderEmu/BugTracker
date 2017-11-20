#update testing dummy hp, no health regen
UPDATE creature_template SET HealthModifier = 10000, flags_extra = flags_extra | 0x00800000 WHERE entry = 8;