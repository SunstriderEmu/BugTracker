 #Prêtre de l'aube : Nova sacrée decastable
#Cabaliste lamesoleil : Trait de l'ombre non décastable
#Prêtre du crépuscule lamesoleil : Fouet mental non décastable
#Prêtre du crépuscule lamesoleil : Peur non décastable
UPDATE `spell_template` SET `interruptFlags` = '4' WHERE `spell_template`.`id` = 46564;
UPDATE `spell_template` SET `interruptFlags` = '0' WHERE `spell_template`.`id` = 47248;
UPDATE `spell_template` SET `interruptFlags` = '0' WHERE `spell_template`.`id` = 46562;
UPDATE `spell_template` SET `interruptFlags` = '0' WHERE `spell_template`.`id` = 46561;

UPDATE `item_template` SET `Map` = '0' WHERE `item_template`.`entry` = 30094;
UPDATE `item_template` SET `area` = '0' WHERE `item_template`.`entry` = 30094;

UPDATE `item_template` SET `TotemCategory` = '21' WHERE `entry` = 35104;
UPDATE `item_template` SET `TotemCategory` = '21' WHERE `entry` = 22345;

UPDATE `spell_proc_event` SET `procFlags` = '86016' WHERE `entry` = 37655;
UPDATE `spell_proc_event` SET `procEx` = '65536' WHERE `entry` = 37655;
UPDATE `spell_proc_event` SET `CustomChance` = '10' WHERE `entry` = 37655;
UPDATE `spell_proc_event` SET `Cooldown` = '45' WHERE `entry` = 37655;

UPDATE `spell_proc_event` SET `procFlags` = '86016' WHERE `entry` = 29601;
UPDATE `spell_proc_event` SET `procEx` = '65536' WHERE `entry` = 29601;
UPDATE `spell_proc_event` SET `CustomChance` = '100' WHERE `entry` = 29601;

REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES ('39440', '0', '0', '0', '69632', '65536', '0', '100', '0');

UPDATE `spell_proc_event` SET `procEx` = '0' WHERE `entry` = 39444;
UPDATE `spell_proc_event` SET `procFlags` = '131208' WHERE `entry` = 39444;
UPDATE `spell_proc_event` SET `CustomChance` = '10' WHERE `entry` = 39444;

UPDATE `spell_proc_event` SET `CustomChance` = '10' WHERE `entry` = 45054;
UPDATE `spell_proc_event` SET `procFlags` = '262144' WHERE `entry` = 45054;

REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES ('38319', '0', '0', '0', '65536', '0', '0', '15', '15');

UPDATE `spell_proc_event` SET `Cooldown` = '0' WHERE `entry` = 27521;
UPDATE `spell_proc_event` SET `CustomChance` = '5' WHERE `entry` = 27521;
UPDATE `spell_proc_event` SET `procFlags` = '86016' WHERE `entry` = 27521;

UPDATE `spell_proc_event` SET `procEx` = '8' WHERE `entry` = 28789;
UPDATE `spell_proc_event` SET `CustomChance` = '100' WHERE `entry` = 28789;

UPDATE `spell_proc_event` SET `CustomChance` = '3' WHERE `entry` = 35077;
UPDATE `spell_proc_event` SET `Cooldown` = '45' WHERE `entry` = 35077;
UPDATE `spell_proc_event` SET `procFlags` = '72' WHERE `entry` = 35077;

DELETE FROM spell_affect WHERE entry IN (16998,16999) AND effectId = 1;