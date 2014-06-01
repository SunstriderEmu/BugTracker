#CREATURE_FLAG_EXTRA_DUAL_WIELD for Lady Sacrolash + no taunt
UPDATE creature_template SET flags_extra = 0x1+0x10000+0x200000 WHERE entry = 25165;
#up some melee dmg for alythess + no taunt
UPDATE creature_template SET mindmg = 3000, flags_extra = 0x1+0x10000 where entry = 25166;
#DUAL WIELD FOR IMAGES
UPDATE creature_template SET flags_extra = 0x200000 WHERE entry = 25214;
#NO TAUNT FOR FELMYST
UPDATE creature_template SET flags_extra = 0x1+0x10000 WHERE entry = 25038;