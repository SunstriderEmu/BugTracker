-- Grull Hawkwind
			-- Link creature to first menu and ensure gossip is enabled
			UPDATE creature_template SET gossip_menu_id = 22839, npcflag = npcflag | 0x1 WHERE entry = 2980;
			-- Menu 22839
			DELETE FROM gossip_text WHERE ID = 1871929;
			INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871929, '','Greetings, $N, and welcome to Camp Narache. News of your arrival spread quickly among the tribe.', '');
			DELETE FROM gossip_menu WHERE entry = 22839;
			INSERT INTO gossip_menu (entry, text_id) VALUES (22839, 1871929);