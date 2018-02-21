ALTER TABLE creature_loot_template 
  CHANGE `entry` `Entry` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `item` `Item` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `Reference` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL AFTER `Item`,
  ADD COLUMN `Chance` FLOAT DEFAULT 100  NOT NULL AFTER `Reference`,
  ADD COLUMN `QuestRequired` TINYINT(1) DEFAULT 0  NOT NULL AFTER `Chance`,
  ADD COLUMN `LootMode` SMALLINT(5) UNSIGNED DEFAULT 1  NOT NULL AFTER `QuestRequired`,
  CHANGE `groupid` `GroupId` TINYINT(3) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `MinCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL AFTER `GroupId`,
  CHANGE `maxcount` `MaxCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL,
  ADD COLUMN `Comment` VARCHAR(255) NULL AFTER `condition_value2`;
  
-- fill reference
UPDATE creature_loot_template SET Reference = -mincountOrRef WHERE mincountOrRef < 0;
-- fill chance
UPDATE creature_loot_template SET Chance = ABS(ChanceOrQuestChance);
-- fill questrequired
UPDATE creature_loot_template SET QuestRequired = 1 WHERE ChanceOrQuestChance < 0;
-- fill mincount
UPDATE creature_loot_template SET MinCount = mincountOrRef WHERE mincountOrRef > 0;

ALTER TABLE creature_loot_template DROP mincountOrRef, DROP ChanceOrQuestChance, DROP lootcondition, DROP condition_value1, DROP condition_value2, DROP PRIMARY KEY, ADD PRIMARY KEY (`Entry`, `Item`);

ALTER TABLE disenchant_loot_template 
  CHANGE `entry` `Entry` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `item` `Item` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `Reference` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL AFTER `Item`,
  ADD COLUMN `Chance` FLOAT DEFAULT 100  NOT NULL AFTER `Reference`,
  ADD COLUMN `QuestRequired` TINYINT(1) DEFAULT 0  NOT NULL AFTER `Chance`,
  ADD COLUMN `LootMode` SMALLINT(5) UNSIGNED DEFAULT 1  NOT NULL AFTER `QuestRequired`,
  CHANGE `groupid` `GroupId` TINYINT(3) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `MinCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL AFTER `GroupId`,
  CHANGE `maxcount` `MaxCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL,
  ADD COLUMN `Comment` VARCHAR(255) NULL AFTER `condition_value2`;
  
-- fill reference
UPDATE disenchant_loot_template SET Reference = -mincountOrRef WHERE mincountOrRef < 0;
-- fill chance
UPDATE disenchant_loot_template SET Chance = ABS(ChanceOrQuestChance);
-- fill questrequired
UPDATE disenchant_loot_template SET QuestRequired = 1 WHERE ChanceOrQuestChance < 0;
-- fill mincount
UPDATE disenchant_loot_template SET MinCount = mincountOrRef WHERE mincountOrRef > 0;

ALTER TABLE disenchant_loot_template DROP mincountOrRef, DROP ChanceOrQuestChance, DROP lootcondition, DROP condition_value1, DROP condition_value2, DROP PRIMARY KEY, ADD PRIMARY KEY (`Entry`, `Item`);

ALTER TABLE fishing_loot_template 
  CHANGE `entry` `Entry` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `item` `Item` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `Reference` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL AFTER `Item`,
  ADD COLUMN `Chance` FLOAT DEFAULT 100  NOT NULL AFTER `Reference`,
  ADD COLUMN `QuestRequired` TINYINT(1) DEFAULT 0  NOT NULL AFTER `Chance`,
  ADD COLUMN `LootMode` SMALLINT(5) UNSIGNED DEFAULT 1  NOT NULL AFTER `QuestRequired`,
  CHANGE `groupid` `GroupId` TINYINT(3) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `MinCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL AFTER `GroupId`,
  CHANGE `maxcount` `MaxCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL,
  ADD COLUMN `Comment` VARCHAR(255) NULL AFTER `condition_value2`;
  
-- fill reference
UPDATE fishing_loot_template SET Reference = -mincountOrRef WHERE mincountOrRef < 0;
-- fill chance
UPDATE fishing_loot_template SET Chance = ABS(ChanceOrQuestChance);
-- fill questrequired
UPDATE fishing_loot_template SET QuestRequired = 1 WHERE ChanceOrQuestChance < 0;
-- fill mincount
UPDATE fishing_loot_template SET MinCount = mincountOrRef WHERE mincountOrRef > 0;

ALTER TABLE gameobject_loot_template 
  CHANGE `entry` `Entry` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `item` `Item` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `Reference` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL AFTER `Item`,
  ADD COLUMN `Chance` FLOAT DEFAULT 100  NOT NULL AFTER `Reference`,
  ADD COLUMN `QuestRequired` TINYINT(1) DEFAULT 0  NOT NULL AFTER `Chance`,
  ADD COLUMN `LootMode` SMALLINT(5) UNSIGNED DEFAULT 1  NOT NULL AFTER `QuestRequired`,
  CHANGE `groupid` `GroupId` TINYINT(3) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `MinCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL AFTER `GroupId`,
  CHANGE `maxcount` `MaxCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL,
  ADD COLUMN `Comment` VARCHAR(255) NULL AFTER `condition_value2`;
  
-- fill reference
UPDATE gameobject_loot_template SET Reference = -mincountOrRef WHERE mincountOrRef < 0;
-- fill chance
UPDATE gameobject_loot_template SET Chance = ABS(ChanceOrQuestChance);
-- fill questrequired
UPDATE gameobject_loot_template SET QuestRequired = 1 WHERE ChanceOrQuestChance < 0;
-- fill mincount
UPDATE gameobject_loot_template SET MinCount = mincountOrRef WHERE mincountOrRef > 0;

ALTER TABLE gameobject_loot_template DROP mincountOrRef, DROP ChanceOrQuestChance, DROP lootcondition, DROP condition_value1, DROP condition_value2, DROP PRIMARY KEY, ADD PRIMARY KEY (`Entry`, `Item`);

ALTER TABLE item_loot_template 
  CHANGE `entry` `Entry` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `item` `Item` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `Reference` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL AFTER `Item`,
  ADD COLUMN `Chance` FLOAT DEFAULT 100  NOT NULL AFTER `Reference`,
  ADD COLUMN `QuestRequired` TINYINT(1) DEFAULT 0  NOT NULL AFTER `Chance`,
  ADD COLUMN `LootMode` SMALLINT(5) UNSIGNED DEFAULT 1  NOT NULL AFTER `QuestRequired`,
  CHANGE `groupid` `GroupId` TINYINT(3) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `MinCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL AFTER `GroupId`,
  CHANGE `maxcount` `MaxCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL,
  ADD COLUMN `Comment` VARCHAR(255) NULL AFTER `condition_value2`;
  
-- fill reference
UPDATE item_loot_template SET Reference = -mincountOrRef WHERE mincountOrRef < 0;
-- fill chance
UPDATE item_loot_template SET Chance = ABS(ChanceOrQuestChance);
-- fill questrequired
UPDATE item_loot_template SET QuestRequired = 1 WHERE ChanceOrQuestChance < 0;
-- fill mincount
UPDATE item_loot_template SET mincountOrRef = 255 WHERE mincountOrRef > 255;
UPDATE item_loot_template SET MinCount = mincountOrRef WHERE mincountOrRef > 0;

ALTER TABLE item_loot_template DROP mincountOrRef, DROP ChanceOrQuestChance, DROP lootcondition, DROP condition_value1, DROP condition_value2, DROP PRIMARY KEY, ADD PRIMARY KEY (`Entry`, `Item`);

ALTER TABLE pickpocketing_loot_template 
  CHANGE `entry` `Entry` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `item` `Item` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `Reference` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL AFTER `Item`,
  ADD COLUMN `Chance` FLOAT DEFAULT 100  NOT NULL AFTER `Reference`,
  ADD COLUMN `QuestRequired` TINYINT(1) DEFAULT 0  NOT NULL AFTER `Chance`,
  ADD COLUMN `LootMode` SMALLINT(5) UNSIGNED DEFAULT 1  NOT NULL AFTER `QuestRequired`,
  CHANGE `groupid` `GroupId` TINYINT(3) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `MinCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL AFTER `GroupId`,
  CHANGE `maxcount` `MaxCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL,
  ADD COLUMN `Comment` VARCHAR(255) NULL AFTER `condition_value2`;
  
-- fill reference
UPDATE pickpocketing_loot_template SET Reference = -mincountOrRef WHERE mincountOrRef < 0;
-- fill chance
UPDATE pickpocketing_loot_template SET Chance = ABS(ChanceOrQuestChance);
-- fill questrequired
UPDATE pickpocketing_loot_template SET QuestRequired = 1 WHERE ChanceOrQuestChance < 0;
-- fill mincount
UPDATE pickpocketing_loot_template SET MinCount = mincountOrRef WHERE mincountOrRef > 0;

ALTER TABLE pickpocketing_loot_template DROP mincountOrRef, DROP ChanceOrQuestChance, DROP lootcondition, DROP condition_value1, DROP condition_value2, DROP PRIMARY KEY, ADD PRIMARY KEY (`Entry`, `Item`);

ALTER TABLE prospecting_loot_template 
  CHANGE `entry` `Entry` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `item` `Item` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `Reference` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL AFTER `Item`,
  ADD COLUMN `Chance` FLOAT DEFAULT 100  NOT NULL AFTER `Reference`,
  ADD COLUMN `QuestRequired` TINYINT(1) DEFAULT 0  NOT NULL AFTER `Chance`,
  ADD COLUMN `LootMode` SMALLINT(5) UNSIGNED DEFAULT 1  NOT NULL AFTER `QuestRequired`,
  CHANGE `groupid` `GroupId` TINYINT(3) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `MinCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL AFTER `GroupId`,
  CHANGE `maxcount` `MaxCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL,
  ADD COLUMN `Comment` VARCHAR(255) NULL AFTER `condition_value2`;
  
-- fill reference
UPDATE prospecting_loot_template SET Reference = -mincountOrRef WHERE mincountOrRef < 0;
-- fill chance
UPDATE prospecting_loot_template SET Chance = ABS(ChanceOrQuestChance);
-- fill questrequired
UPDATE prospecting_loot_template SET QuestRequired = 1 WHERE ChanceOrQuestChance < 0;
-- fill mincount
UPDATE prospecting_loot_template SET MinCount = mincountOrRef WHERE mincountOrRef > 0;

ALTER TABLE prospecting_loot_template DROP mincountOrRef, DROP ChanceOrQuestChance, DROP lootcondition, DROP condition_value1, DROP condition_value2, DROP PRIMARY KEY, ADD PRIMARY KEY (`Entry`, `Item`);

ALTER TABLE quest_mail_loot_template 
  CHANGE `entry` `Entry` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `item` `Item` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `Reference` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL AFTER `Item`,
  ADD COLUMN `Chance` FLOAT DEFAULT 100  NOT NULL AFTER `Reference`,
  ADD COLUMN `QuestRequired` TINYINT(1) DEFAULT 0  NOT NULL AFTER `Chance`,
  ADD COLUMN `LootMode` SMALLINT(5) UNSIGNED DEFAULT 1  NOT NULL AFTER `QuestRequired`,
  CHANGE `groupid` `GroupId` TINYINT(3) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `MinCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL AFTER `GroupId`,
  CHANGE `maxcount` `MaxCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL,
  ADD COLUMN `Comment` VARCHAR(255) NULL AFTER `condition_value2`;
  
-- fill reference
UPDATE quest_mail_loot_template SET Reference = -mincountOrRef WHERE mincountOrRef < 0;
-- fill chance
UPDATE quest_mail_loot_template SET Chance = ABS(ChanceOrQuestChance);
-- fill questrequired
UPDATE quest_mail_loot_template SET QuestRequired = 1 WHERE ChanceOrQuestChance < 0;
-- fill mincount
UPDATE quest_mail_loot_template SET MinCount = mincountOrRef WHERE mincountOrRef > 0;

ALTER TABLE quest_mail_loot_template DROP mincountOrRef, DROP ChanceOrQuestChance, DROP lootcondition, DROP condition_value1, DROP condition_value2, DROP PRIMARY KEY, ADD PRIMARY KEY (`Entry`, `Item`);

ALTER TABLE reference_loot_template 
  CHANGE `entry` `Entry` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `item` `Item` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `Reference` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL AFTER `Item`,
  ADD COLUMN `Chance` FLOAT DEFAULT 100  NOT NULL AFTER `Reference`,
  ADD COLUMN `QuestRequired` TINYINT(1) DEFAULT 0  NOT NULL AFTER `Chance`,
  ADD COLUMN `LootMode` SMALLINT(5) UNSIGNED DEFAULT 1  NOT NULL AFTER `QuestRequired`,
  CHANGE `groupid` `GroupId` TINYINT(3) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `MinCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL AFTER `GroupId`,
  CHANGE `maxcount` `MaxCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL,
  ADD COLUMN `Comment` VARCHAR(255) NULL AFTER `condition_value2`;
  
-- fill reference
UPDATE reference_loot_template SET Reference = -mincountOrRef WHERE mincountOrRef < 0;
-- fill chance
UPDATE reference_loot_template SET Chance = ABS(ChanceOrQuestChance);
-- fill questrequired
UPDATE reference_loot_template SET QuestRequired = 1 WHERE ChanceOrQuestChance < 0;
-- fill mincount
UPDATE reference_loot_template SET MinCount = mincountOrRef WHERE mincountOrRef > 0;

ALTER TABLE reference_loot_template DROP mincountOrRef, DROP ChanceOrQuestChance, DROP lootcondition, DROP condition_value1, DROP condition_value2, DROP PRIMARY KEY, ADD PRIMARY KEY (`Entry`, `Item`);

ALTER TABLE skinning_loot_template 
  CHANGE `entry` `Entry` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `item` `Item` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `Reference` MEDIUMINT(8) UNSIGNED DEFAULT 0  NOT NULL AFTER `Item`,
  ADD COLUMN `Chance` FLOAT DEFAULT 100  NOT NULL AFTER `Reference`,
  ADD COLUMN `QuestRequired` TINYINT(1) DEFAULT 0  NOT NULL AFTER `Chance`,
  ADD COLUMN `LootMode` SMALLINT(5) UNSIGNED DEFAULT 1  NOT NULL AFTER `QuestRequired`,
  CHANGE `groupid` `GroupId` TINYINT(3) UNSIGNED DEFAULT 0  NOT NULL,
  ADD COLUMN `MinCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL AFTER `GroupId`,
  CHANGE `maxcount` `MaxCount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL,
  ADD COLUMN `Comment` VARCHAR(255) NULL AFTER `condition_value2`;
  
-- fill reference
UPDATE skinning_loot_template SET Reference = -mincountOrRef WHERE mincountOrRef < 0;
-- fill chance
UPDATE skinning_loot_template SET Chance = ABS(ChanceOrQuestChance);
-- fill questrequired
UPDATE skinning_loot_template SET QuestRequired = 1 WHERE ChanceOrQuestChance < 0;
-- fill mincount
UPDATE skinning_loot_template SET MinCount = mincountOrRef WHERE mincountOrRef > 0;

-- Fixed shattered halls conditional loot (related to prisoners alive)
UPDATE creature_loot_template SET LootMode = 0xE WHERE Entry = 20585 AND Item = 31716;