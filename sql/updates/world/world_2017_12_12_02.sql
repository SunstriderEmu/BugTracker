-- List warrior spells that were previously not in playercreateinfo_spell table but will be added with playercreateinfo_skills
-- SELECT pci_skills.*, m_spell, spellName1, pci_spells.*
-- FROM playercreateinfo_skills pci_skills
-- JOIN dbc.db_skilllineability_8606 dbc ON pci_skills.skill = dbc.m_skillLine AND m_classMask & 1
-- JOIN spell_template st ON st.entry = m_spell
-- LEFT JOIN playercreateinfo_spell pci_spells ON (pci_spells.class = 1 OR pci_spells.class = 0) AND pci_spells.Spell = dbc.m_spell
-- WHERE (pci_skills.classMask = 0 OR pci_skills.classMask & 1)
-- AND pci_spells.Active IS NULL

-- List spells from class 4 we wont get with playercreateinfo_skills but had with playercreateinfo_spell
-- SELECT *
-- FROM playercreateinfo_spell pci_spells
-- LEFT JOIN (
	-- SELECT m_spell
	-- FROM playercreateinfo_skills pci_skills
	-- JOIN dbc.db_skilllineability_8606 dbc ON pci_skills.skill = dbc.m_skillLine AND (m_classMask & 8 OR m_classMask = 0)
	-- WHERE (pci_skills.classMask = 0 OR pci_skills.classMask & 8)
-- ) dbc ON pci_spells.Spell = dbc.m_spell

-- WHERE pci_spells.class = 4 AND dbc.m_spell IS NULL

-- Okay so, we know which spells wont be learned with new playercreateinfo_skills. Let's empty playercreateinfo_spell as much as possible and leave the spells that wont't automatically added 
delete from playercreateinfo_spell;
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('8','1','2567','Thrown','1');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('8','1','2764','Throw','1');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('4','11','5419','Travel Form (Passive)','0');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('6','11','5419','Travel Form (Passive)','0');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('4','11','5420','Tree of Life','0');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('6','11','5420','Tree of Life','0');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('4','11','33948','Flight Form (Passive)','0');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('6','11','33948','Flight Form (Passive)','0');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('4','11','34123','Tree of Life(Passive)','0');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('6','11','34123','Tree of Life(Passive)','0');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('4','11','40121','Swift Flight Form (Passive)','0');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('6','11','40121','Swift Flight Form (Passive)','0');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('1','2','53087','Salvation (passive -50% threat on healing spells)','1');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('3','2','53087','Salvation (passive -50% threat on healing spells)','1');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('10','2','53087','Salvation (passive -50% threat on healing spells)','1');
insert into `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`, `Active`) values('11','2','53087','Salvation (passive -50% threat on healing spells)','1');

-- Create and fill new table
DROP TABLE IF EXISTS `playercreateinfo_skills`;
CREATE TABLE `playercreateinfo_skills` (
  `raceMask` int(10) unsigned NOT NULL,
  `classMask` int(10) unsigned NOT NULL,
  `skill` smallint(5) unsigned NOT NULL,
  `rank` smallint(5) unsigned NOT NULL DEFAULT 0,
  `comment` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`raceMask`,`classMask`,`skill`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

insert into `playercreateinfo_skills`(`raceMask`,`classMask`,`skill`,`rank`,`comment`) values 
(0,0,95,0,'Defense'),
(0,0,162,0,'Unarmed'),
(0,0,183,0,'GENERIC (DND)'),
(0,0,415,0,'Cloth'),
(0,0,777,0,'Mounts'),
(0,0,778,0,'Companion Pets'),
(0,1,26,0,'Warrior - Arms'),
(0,1,256,0,'Warrior - Fury'),
(0,1,257,0,'Warrior - Protection'),
(0,2,184,0,'Paladin - Retribution'),
(0,2,267,0,'Paladin - Protection'),
(0,2,594,0,'Paladin - Holy'),
(0,4,50,0,'Hunter - Beast Mastery'),
(0,4,51,0,'Hunter - Survival'),
(0,4,163,0,'Hunter - Marksmanship'),
(0,8,38,0,'Rogue - Combat'),
(0,8,39,0,'Rogue - Subtlety'),
(0,8,176,0,'Thrown'),
(0,8,253,0,'Rogue - Assassination'),
(0,16,56,0,'Priest - Holy'),
(0,16,78,0,'Priest - Shadow'),
(0,16,613,0,'Priest - Discipline'),
(0,3,55,0,'Two-Handed Swords'),
(0,3,413,0,'Mail'),
(0,5,44,0,'Axes'),
(0,5,172,0,'Two-Handed Axes'),
(0,7,43,0,'Swords'),
(0,8,118,0,'Dual Wield'),
(0,64,373,0,'Shaman - Enhancement'),
(0,64,374,0,'Shaman - Restoration'),
(0,64,375,0,'Shaman - Elemental'),
(0,67,433,0,'Shield'),
(0,128,6,0,'Mage - Frost'),
(0,128,8,0,'Mage - Fire'),
(0,128,237,0,'Mage - Arcane'),
(0,256,354,0,'Warlock - Demonology'),
(0,256,355,0,'Warlock - Affliction'),
(0,256,593,0,'Warlock - Destruction'),
(0,400,228,0,'Wands'),
(0,1024,134,0,'Druid - Feral'),
(0,1024,573,0,'Druid - Restoration'),
(0,1024,574,0,'Druid - Balance'),
(0,1107,54,0,'Maces'),
(0,1103,414,0,'Leather'),
(0,1488,136,0,'Staves'),
(1,0,754,0,'Human - Racial'),
(2,0,125,0,'Orc - Racial'),
(4,0,101,0,'Dwarf - Racial'),
(4,0,111,0,'Language: Dwarven'),
(8,0,113,0,'Language: Darnassian'),
(8,0,126,0,'Night Elf - Racial'),
(16,0,220,0,'Undead - Racial'),
(16,0,673,0,'Language: Forsaken'),
(32,0,115,0,'Language: Taurahe'),
(32,0,124,0,'Tauren - Racial'),
(36,4,46,0,'Guns'),
(64,0,313,0,'Language: Gnomish'),
(64,0,753,0,'Gnome - Racial'),
(128,0,315,0,'Language: Troll'),
(128,0,733,0,'Troll - Racial'),
(512,0,137,0,'Language: Thalassian'),
(512,0,756,0,'Blood Elf - Racial'),
(650,4,45,0,'Bows'),
(690,0,109,0,'Language: Orcish'),
(735,1293,173,0,'Daggers'),
(1024,0,759,0,'Language: Draenei'),
(1024,0,760,0,'Draenei - Racial'),
(1024,4,226,0,'Crossbows'),
(1061,3,160,0,'Two-Handed Maces'),
(1101,0,98,0,'Language: Common');