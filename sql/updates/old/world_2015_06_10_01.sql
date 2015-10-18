ALTER TABLE creature_template
	ADD COLUMN `gossip_menu_id` mediumint(8) unsigned NOT NULL DEFAULT '0'
	AFTER IconName;
	
#udpate gossip_menu_id column. This request is not entirely valid since the subrequest can return NULL, but mysql does not complain and replace it by 0.
UPDATE creature_template ct
SET gossip_menu_id = (
	#subrequest should always return one row, do not limit so that we detect errors
	SELECT cg.menu_id
	FROM creature_gossip cg
	JOIN creature c ON cg.npc_guid = c.guid
	WHERE c.id = ct.entry
	#omit creatures having multiples menus for same id (but different guid)
	AND c.id NOT IN (10445, 14823, 15303, 19148, 19178, 21859, 26007)
	GROUP BY cg.menu_id
)

UPDATE creature_template SET gossip_menu_id = 10215 WHERE entry = 26007;
DELETE FROM creature_gossip WHERE menu_id = 10215;
UPDATE creature_template SET gossip_menu_id = 11966 WHERE entry = 19178;
DELETE FROM creature_gossip WHERE menu_id = 11966;

DELETE FROM creature_gossip
WHERE npc_guid IN (
	SELECT guid FROM creature WHERE id NOT IN (10445, 14823, 15303, 19148, 19178, 21859, 26007)
)