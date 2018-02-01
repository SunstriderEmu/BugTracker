-- -- Stamina group
-- remove duplicate
DELETE FROM spell_group WHERE id = 1074;
DELETE FROM spell_group WHERE id = 1129;
-- scroll of stamina
REPLACE INTO spell_group VALUES (1129, 8099);
-- power word Fortitude
REPLACE INTO spell_group VALUES (1129, 1243);
-- Prayer of Fortitude
REPLACE INTO spell_group VALUES (1129, 21562);
REPLACE INTO spell_group_stack_rules VALUES (1129, 4);
-- --

-- -- Intellect group
-- remove duplicate
DELETE FROM spell_group WHERE id = 1072;
DELETE FROM spell_group WHERE id = 1080;
-- arcane brillance
REPLACE INTO spell_group VALUES (1080, 23028);
-- scroll of intellect 
REPLACE INTO spell_group VALUES (1080, 8096);
-- Arcane Intellect
REPLACE INTO spell_group VALUES (1080, 1459);
REPLACE INTO spell_group_stack_rules VALUES (1080, 4);
-- --

-- -- Spirit group
-- remove duplicate
DELETE FROM spell_group WHERE id = 1076;
DELETE FROM spell_group WHERE id = 1077;
-- prayer of spirit
REPLACE INTO spell_group VALUES (1077, 27681);
-- divine spirit
REPLACE INTO spell_group VALUES (1077, 14752);
-- scroll of spirit
REPLACE INTO spell_group VALUES (1077, 8112);
REPLACE INTO spell_group_stack_rules VALUES (1077, 4);
-- --

-- -- Blessings!
-- salvation
-- 1038

-- wisdom
-- 19742
-- greater wisdom
-- 25894
-- group 1005 already done

-- might 
-- 19740
-- greater might 
-- 25782
-- group 1002 already done

-- kings
-- 20217
-- greater kings
-- 25898
-- group 1006 already done

DELETE FROM spell_group WHERE id = 1004;
-- light 
REPLACE INTO spell_group VALUES (1004, 19977);
-- greater light
REPLACE INTO spell_group VALUES (1004, 25890);
REPLACE INTO spell_group_stack_rules VALUES (1004, 4);
-- -- 

-- earth shield
DELETE FROM spell_group WHERE id = 1074;
REPLACE INTO spell_group VALUES (1074, 974);
REPLACE INTO spell_group_stack_rules VALUES (1074, 4);

-- add Crystal Yield to debuff armor group 15235
REPLACE INTO spell_group VALUES (1013, 15235);

-- heroism + bloodlust + power infusion + icy vein group. Power Infusion: Infuses the target with power, increasing their spell haste by 20% and reducing the mana cost of all spells by 20%. Lasts for 15 seconds.This will not stack with other haste effects, such as Heroism, Bloodlust, or Icy Veins.
DELETE FROM spell_group WHERE id = 1072;
-- heroism
REPLACE INTO spell_group VALUES (1072, 32182);
-- bloodlust
REPLACE INTO spell_group VALUES (1072, 41185);
-- power infusion
REPLACE INTO spell_group VALUES (1072, 10060);
-- icy vein
REPLACE INTO spell_group VALUES (1072, 12472);
REPLACE INTO spell_group_stack_rules VALUES (1072, 4);

REPLACE INTO spell_template_override (entry, AttributesEx2, SpellFamilyName, COMMENT) VALUES (18191, 0x80000000, 0, "Added SPELL_ATTR2_FOOD_BUFF to windblossomBerries");
REPLACE INTO spell_template_override (entry, AttributesEx2, SpellFamilyName, COMMENT) VALUES (25804, 0x80000000, 0, "Added SPELL_ATTR2_FOOD_BUFF to rumsey rum");

-- healing stream totem DOES stack
DELETE FROM spell_group WHERE id = 1130;
DELETE FROM spell_group_stack_rules WHERE group_id = 1130;

-- duplicate mana stream
DELETE FROM spell_group WHERE id = 1131;
DELETE FROM spell_group_stack_rules WHERE group_id = 1131;

-- tranquil air totem
REPLACE INTO spell_group VALUES (1130, 25909);
REPLACE INTO spell_group_stack_rules VALUES (1130, 1);
 
-- nature resistance totem
REPLACE INTO spell_group VALUES (1137, 10596);
REPLACE INTO spell_group_stack_rules VALUES (1137, 4);
 
-- fire resistance totem
REPLACE INTO spell_group VALUES (1138, 8185);
REPLACE INTO spell_group_stack_rules VALUES (1138, 4);

-- wrath of air
REPLACE INTO spell_group VALUES (1139, 2895);
REPLACE INTO spell_group_stack_rules VALUES (1139, 4);

-- frost resistance totem
REPLACE INTO spell_group VALUES (1140, 8182);
REPLACE INTO spell_group_stack_rules VALUES (1140, 4);

-- stoneskin totem
REPLACE INTO spell_group VALUES (1141, 8072);
REPLACE INTO spell_group_stack_rules VALUES (1141, 4);

-- earthbind totem effect
REPLACE INTO spell_group VALUES (1142, 3600);
REPLACE INTO spell_group_stack_rules VALUES (1142, 1);

-- strenght of earth totem
REPLACE INTO spell_group VALUES (1143, 8076);
REPLACE INTO spell_group_stack_rules VALUES (1143, 4);

-- windwall totem
REPLACE INTO spell_group VALUES (1144, 15108);
REPLACE INTO spell_group_stack_rules VALUES (1144, 4);

-- grace of air totem
REPLACE INTO spell_group VALUES (1145, 8836);
REPLACE INTO spell_group_stack_rules VALUES (1145, 4);

-- wrong rules
DELETE FROM spell_group WHERE spell_id IN (12579, 6360, 8042);
DELETE FROM spell_group WHERE id = 1058;
DELETE FROM spell_group_stack_rules WHERE group_id = 1058;
