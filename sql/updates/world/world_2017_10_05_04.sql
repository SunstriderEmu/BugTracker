-- Ships members

-- Squibby Overspeck
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22829, npcflag = npcflag | 0x1 WHERE entry = 12137;
	-- Menu 22829
	DELETE FROM gossip_text WHERE ID = 1871913;
	INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871913, '','Of course there\'s no danger in everything catching flames and exploding like a huge helium bomb. This baby will get you to Undercity faster and safer than any boat, and the view is truly breathtaking. Speaking of breath, smoking is not allowed while on board the zeppelin, and fire spells are banned from being cast during the trip.', 'Of course there\'s no danger in everything catching flames and exploding like a huge helium bomb. This baby will get you to Undercity faster and safer than any boat, and the view is truly breathtaking. Speaking of breath, smoking is not allowed while on board the zeppelin');
	DELETE FROM gossip_menu WHERE entry = 22829;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22829, 1871913);
	INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, OptionBroadcastTextID, option_id, npc_option_npcflag, action_menu_id, action_poi_id, box_coded, box_money, box_text, BoxBroadcastTextID) VALUES (22829, "0","0", "Where is the zeppelin now?","22086","1","1",22832,"0","0","0","","0");

-- Nez'raz
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22830, npcflag = npcflag | 0x1 WHERE entry = 3149;
	-- Menu 22830
	DELETE FROM gossip_text WHERE ID = 1871915;
	INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871915, '','My brother said we could make great money with this trade route, but he didn\'t tell me I would be the one living on this side. If you come back this way on the Zeppelin, could you bring me something to eat? They sell some of the finest meat in Orgrimmar, and I sure could use something that didn\'t die weeks before it stopped moving.', 'My brother said we could make great money with this trade route, but he didn\'t tell me I would be the one living on this side. If you come back this way on the Zeppelin, could you bring me something to eat? They sell some of the finest meat in Orgrimmar, and I sure could use something that didn\'t die weeks before it stopped moving.');
	DELETE FROM gossip_menu WHERE entry = 22830;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22830, 1871915);
	INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, OptionBroadcastTextID, option_id, npc_option_npcflag, action_menu_id, action_poi_id, box_coded, box_money, box_text, BoxBroadcastTextID) VALUES (22830, "0","0", "Where is the zeppelin now?","22086","1","1",22833,"0","0","0","","0");
	
-- Chief Officer Brassbolt
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22824, npcflag = npcflag | 0x1 WHERE entry = 24926;
	-- Menu 22824
	DELETE FROM gossip_text WHERE ID = 1871903;
	INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871903, '','', '\"Iron Eagle.\" Hmph. It\'s a passenger ship, not a warbird! But hey, a job\'s a job, and I\'ll humor Captain \"Bombast\" so long as the prince is paying.$b$bIn any case, welcome aboard.');
	DELETE FROM gossip_menu WHERE entry = 22824;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22824, 1871903);
	
-- Navigator Sparksizzle
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22825, npcflag = npcflag | 0x1 WHERE entry = 24927;
	-- Menu 22825
	DELETE FROM gossip_text WHERE ID = 1871905;
	INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871905, '','Not right now, $gpal:sugar;... I got things to do. See ya around.', '');
	DELETE FROM gossip_menu WHERE entry = 22825;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22825, 1871905);
	
	-- Crewman Crosswire
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22826, npcflag = npcflag | 0x1 WHERE entry = 24929;
	-- Menu 22826
	DELETE FROM gossip_text WHERE ID = 1871907;
	INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871907, '','Sorta busy.', 'Sorta busy.');
	DELETE FROM gossip_menu WHERE entry = 22826;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22826, 1871907);
	
	-- Crewman Gazzlegear
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22827, npcflag = npcflag | 0x1 WHERE entry = 24930;
	-- Menu 22827
	DELETE FROM gossip_text WHERE ID = 1871909;
	INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871909, '','Sorta busy.', 'Sorta busy.');
	DELETE FROM gossip_menu WHERE entry = 22827;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22827, 1871909);
	
	-- Crewman Fastwrench
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22828, npcflag = npcflag | 0x1 WHERE entry = 24931;
	-- Menu 22828
	DELETE FROM gossip_text WHERE ID = 1871911;
	INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871911, '','Sorta busy.', 'Sorta busy.');
	DELETE FROM gossip_menu WHERE entry = 22828;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22828, 1871911);
	
	-- Chief Officer Coppernut
		-- Link creature to first menu and ensure gossip is enabled
		UPDATE creature_template SET gossip_menu_id = 22830, npcflag = npcflag | 0x1 WHERE entry = 25070;
		-- Menu 22830
		DELETE FROM gossip_text WHERE ID = 1871915;
		INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871915, '','', 'If you like excitement, our captain\'s the best!  I love this job!');
		DELETE FROM gossip_menu WHERE entry = 22830;
		INSERT INTO gossip_menu (entry, text_id) VALUES (22830, 1871915);
	
-- Crewman Rusthammer
		-- Link creature to first menu and ensure gossip is enabled
		UPDATE creature_template SET gossip_menu_id = 22831, npcflag = npcflag | 0x1 WHERE entry = 25071;
		-- Menu 22831
		DELETE FROM gossip_text WHERE ID = 1871917;
		INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871917, '','<Grumbles>  I guess those mountains came out of nowhere...  All five times!', '');
		DELETE FROM gossip_menu WHERE entry = 22831;
		INSERT INTO gossip_menu (entry, text_id) VALUES (22831, 1871917);
	
-- Crewman Quickfix
		-- Link creature to first menu and ensure gossip is enabled
		UPDATE creature_template SET gossip_menu_id = 22832, npcflag = npcflag | 0x1 WHERE entry = 25072;
		-- Menu 22832
		DELETE FROM gossip_menu WHERE entry = 22832;
		INSERT INTO gossip_menu (entry, text_id) VALUES (22832, 1871917);
		
-- Crewman Sparkfly
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22833, npcflag = npcflag | 0x1 WHERE entry = 25074;
	-- Menu 22833
	DELETE FROM gossip_menu WHERE entry = 22833;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22833, 1871917);

-- Navigator Fairweather
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22834, npcflag = npcflag | 0x1 WHERE entry = 25076;
	-- Menu 22834
	DELETE FROM gossip_text WHERE ID = 1871919;
	INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871919, '','You can\'t blame me for our mishaps... I can\'t even see where I\'m going!$b$bThough maybe that means you can blame me...$b$bNo!  Wait!  I can dock this ship just fine... It\'s gotta be the orders the captain issues!  Maybe he likes pushing us to our limits and testing out our survival and repair skills.', '');
	DELETE FROM gossip_menu WHERE entry = 22834;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22834, 1871919);
	
-- Sky-Captain Bomblast
		-- Link creature to first menu and ensure gossip is enabled
		UPDATE creature_template SET gossip_menu_id = 22838, npcflag = npcflag | 0x1 WHERE entry = 24924;
		-- Menu 22838
		DELETE FROM gossip_text WHERE ID = 1871927;
		INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871927, '','I run the tightest airship in Azeroth. She used to be fitted with twin light cannons and enough bombs to flatten a city, you know... her mere shadow was enough to rout armies.$b$bWhat? Of course it\'s true!', '');
		DELETE FROM gossip_menu WHERE entry = 22838;
		INSERT INTO gossip_menu (entry, text_id) VALUES (22838, 1871927);
	

-- Sky-Captain Cloudkicker
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22835, npcflag = npcflag | 0x1 WHERE entry = 25077;
	-- Menu 22835
	DELETE FROM gossip_text WHERE ID = 1871921;
	INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871921, '','Welcome aboard the Thundercaller!$b$bDon\'t pay attention to the people that complain about explosions or the like.  I mean really, everyone makes mistakes.  We should cut people some slack.$b$bLook, I\'d understand if a captain managed to crash his ship 22 or 23 times... But anything less than that isn\'t worth mentioning.', '');
	DELETE FROM gossip_menu WHERE entry = 22835;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22835, 1871921);
	
	-- Deathguard Fowles
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22836, npcflag = npcflag | 0x1 WHERE entry = 25079;
	-- Menu 22836
	DELETE FROM gossip_text WHERE ID = 1871923;
	INSERT INTO gossip_text (ID, comment, text0_0, text0_1) VALUES (1871923, '','Don\'t ask...', '');
	DELETE FROM gossip_menu WHERE entry = 22836;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22836, 1871923);

-- Deathguard Lawson
	-- Link creature to first menu and ensure gossip is enabled
	UPDATE creature_template SET gossip_menu_id = 22837, npcflag = npcflag | 0x1 WHERE entry = 25083;
	-- Menu 22837
	DELETE FROM gossip_menu WHERE entry = 22837;
	INSERT INTO gossip_menu (entry, text_id) VALUES (22837, 1871923);
	
