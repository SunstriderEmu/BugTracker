-- set "execute event while charmed" flag on all events except:
-- -) movement actions
-- -) nontriggered cast actions
-- -) talk/emote/sound actions
-- -) ally summon actions
ALTER TABLE `smart_scripts` MODIFY COLUMN `event_flags` SMALLINT(3) UNSIGNED NOT NULL DEFAULT '0';
UPDATE `smart_scripts` SET `event_flags`=(`event_flags`|0x200) WHERE `source_type`=0 AND
	(`action_type` not in (1,4,5,10,11,12,17,25,27,38,39,40,49,62,69,84,85,86,89,92,97,103,107,114) OR
	(`action_type` in (11,86) AND (`action_param2`&2)=2));