#fixes some wrong texts
UPDATE npc_gossip JOIN creature c ON c.guid = npc_guid SET textid = 7339 WHERE id = 14822;
UPDATE npc_gossip JOIN creature c ON c.guid = npc_guid SET textid = 7382 WHERE id = 14849;
REPLACE INTO game_event_npc_gossip VALUES (8936, 23, 7354);
REPLACE INTO game_event_npc_gossip VALUES (8938, 23, 7354);