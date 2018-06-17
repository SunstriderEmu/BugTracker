-- Fixed wrong armor for training dummy 17 <no armor>
UPDATE creature_template SET ArmorModifier = 0 WHERE entry = 17;