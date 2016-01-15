ALTER TABLE `locales_gossip_menu_option`   
  CHANGE `id` `id` SMALLINT(5) UNSIGNED DEFAULT 0  NOT NULL;
  
ALTER TABLE `game_event_condition`   
  CHANGE `event_id` `event_id` INT(11) UNSIGNED DEFAULT 0  NOT NULL;

ALTER TABLE `game_event`   
  CHANGE `entry` `entry` INT(11) UNSIGNED NOT NULL   COMMENT 'Entry of the game event';

ALTER TABLE `game_event_npcflag`   
  CHANGE `event_id` `event_id` INT(11) UNSIGNED DEFAULT 0  NOT NULL;

ALTER TABLE `game_event_npc_vendor`   
  CHANGE `event` `event` INT(11) UNSIGNED DEFAULT 0  NOT NULL;

ALTER TABLE `game_event_prerequisite`   
  CHANGE `event_id` `event_id` INT(11) UNSIGNED NOT NULL,
  CHANGE `prerequisite_event` `prerequisite_event` INT(11) UNSIGNED NOT NULL;

ALTER TABLE `game_event_quest_condition`   
  CHANGE `quest` `quest` INT(11) UNSIGNED DEFAULT 0  NOT NULL;

ALTER TABLE `playercreateinfo_spell`   
  CHANGE `Spell` `Spell` INT(11) UNSIGNED DEFAULT 0  NOT NULL;
  
ALTER TABLE `spell_pet_auras`   
  CHANGE `spell` `spell` INT(11) UNSIGNED NOT NULL   COMMENT 'dummy spell id',
  CHANGE `pet` `pet` INT(11) UNSIGNED DEFAULT 0  NOT NULL   COMMENT 'pet id; 0 = all',
  CHANGE `aura` `aura` INT(11) UNSIGNED NOT NULL   COMMENT 'pet aura id';

ALTER TABLE `access_requirement`   
  CHANGE `quest_failed_text` `quest_failed_text` INT(10) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `id` `id` INT(11) UNSIGNED NOT NULL   COMMENT 'Identifier';

ALTER TABLE `areatrigger_teleport`   
  CHANGE `access_id` `access_id` INT(11) UNSIGNED DEFAULT 0  NOT NULL;

ALTER TABLE `creature_onkill_reputation`   
  CHANGE `RewOnKillRepFaction1` `RewOnKillRepFaction1` INT(11) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `RewOnKillRepFaction2` `RewOnKillRepFaction2` INT(11) UNSIGNED DEFAULT 0  NOT NULL,
  CHANGE `RewOnKillRepValue1` `RewOnKillRepValue1` INT(11) DEFAULT 0  NOT NULL,
  CHANGE `RewOnKillRepValue2` `RewOnKillRepValue2` INT(11) DEFAULT 0  NOT NULL;
  
ALTER TABLE `game_event_creature`   
  CHANGE `event` `event` INT(11) DEFAULT 0  NOT NULL;

ALTER TABLE `item_loot_template`   
  CHANGE `maxcount` `maxcount` TINYINT(3) UNSIGNED DEFAULT 1  NOT NULL;
