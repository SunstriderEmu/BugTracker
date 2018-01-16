
DROP TABLE IF EXISTS `quest_request_items`;
CREATE TABLE `quest_request_items` (
  `ID` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `EmoteOnComplete` smallint(5) unsigned NOT NULL DEFAULT 0,
  `EmoteOnIncomplete` smallint(5) unsigned NOT NULL DEFAULT 0,
  `CompletionText` text DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

REPLACE INTO quest_request_items (ID, EmoteOnComplete, EmoteOnIncomplete, CompletionText)
SELECT entry, CompleteEmote, IncompleteEmote, RequestItemsText FROM quest_template;

DROP TABLE IF EXISTS `quest_offer_reward`;
CREATE TABLE `quest_offer_reward` (
  `ID` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `Emote1` smallint(5) unsigned NOT NULL DEFAULT 0,
  `Emote2` smallint(5) unsigned NOT NULL DEFAULT 0,
  `Emote3` smallint(5) unsigned NOT NULL DEFAULT 0,
  `Emote4` smallint(5) unsigned NOT NULL DEFAULT 0,
  `EmoteDelay1` int(10) unsigned NOT NULL DEFAULT 0,
  `EmoteDelay2` int(10) unsigned NOT NULL DEFAULT 0,
  `EmoteDelay3` int(10) unsigned NOT NULL DEFAULT 0,
  `EmoteDelay4` int(10) unsigned NOT NULL DEFAULT 0,
  `RewardText` text DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

REPLACE INTO quest_offer_reward (ID, Emote1, Emote2, Emote3, Emote4, EmoteDelay1, EmoteDelay2, EmoteDelay3, EmoteDelay4, RewardText)
SELECT entry, OfferRewardEmote1, OfferRewardEmote2, OfferRewardEmote3, OfferRewardEmote4, 0, 0, 0, 0, OfferRewardText FROM quest_template;

DROP TABLE IF EXISTS `quest_greeting`;
CREATE TABLE `quest_greeting` (
  `ID` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `Type` tinyint(3) unsigned NOT NULL DEFAULT 0,
  `GreetEmoteType` smallint(5) unsigned NOT NULL DEFAULT 0,
  `GreetEmoteDelay` int(10) unsigned NOT NULL DEFAULT 0,
  `Greeting` text DEFAULT NULL,
  PRIMARY KEY (`ID`,`Type`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


replace into `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`) values('234','0','1','0','A foul corruption has crept into Westfall.  While I was upholding my duty on the battlefields of Lordaeron these honest farms were overrun and made into hide-outs for thugs and murderers. The People\'s Militia needs your help.'),
('235','0','0','0','Welcome to our humble abode! It\'s always nice to see a friendly face. And what strong arms you have. My husband and I are always looking for help around the farm. Now that most the good folk have left, it\'s hard to find an able body to help out.'),
('237','0','0','0','Nothing but trouble in these parts.  I tried to tell that fool Saldean to get out while he still could but he won\'t hear of it.  But I ain\'t no fool.  Verna and I are gonna mosey on out as soon as we get this wagon fixed.'),
('238','0','0','0','Sometimes I think there\'s a big gray cloud in the sky, just raining down bad luck upon us. First, we\'re driven off our land, and now we can\'t even get out of Westfall. Everything\'s a mess. Something needs to be done.'),
('253','0','0','0','Aha! Good day, good day, Master $C! Come, sit down and have a drink. You have an enterprising look in your eye, and I think you\'ll find speaking to me worth your time...'),
('261','0','0','0','Hello, citizen.  You look like a $g man : woman; with a purpose - do you have business with the Stormwind Army?'),
('342','0','0','0','Hail, $n. Welcome to my humble garden. The weather has been perfect lately. Let us hope it holds steady for a ripe harvest.'),
('714','0','0','0','Greetings, $c! Fine day for hunting, wouldn\'t you say? I\'ve been having more than a little luck with boars, myself. Perhaps you\'d like a shot?'),
('786','0','0','0','Greetings, $G lad : lass;. I\'m Grelin Whitebeard. I\'m here to examine the threat posed by the growing numbers of trolls in Coldridge Valley. What have I found? It\'s a bit troubling...'),
('823','0','1','0','Hello there, $c.  Normally I\'d be out on the beat looking after the folk of Stormwind, but a lot of the Stormwind guards are fighting in the other lands.  So here I am, deputized and offering bounties when I\'d rather be on patrol...'),
('1374','0','0','0','Curse that Brewers\'\' League! They have access to all the best ingredients, while we\'\'re stuck here grubbing for grain and hops!'),
('1499','0','0','0','Ah, you there! I have tasks to give, and I need not waste time explaining their crucial nature. Listen close.'),
('1500','0','0','0','I hope you\'re well, all things considered.$B$BSit for a spell, and hear my tale. It\'s a tragedy, of course, but one I hope will end in revenge!'),
('1515','0','0','0','The Scarlet Crusade is encroaching on our homeland. The foolish zealots do not realize that the loyal servants of The Dark Lady shall see to their demise.'),
('1518','0','0','0','The Dark Lady has put forth the challenge. It is up to us to meet it.'),
('2519','0','0','0','Hello!  The spirits say you here to aid my chief.  Say it loud, they do.'),
('2930','0','0','0','Corruption sneaks into nature\'s grove. The forest must be protected at all costs.'),
('3446','0','0','0','Yes yes yes! You\'re just the $r I\'m looking for!$B$BSit! We have much to discuss!!'),
('3453','0','0','0','Something I can help you with, $n? There\'s a shipment I\'ve got to see to otherwise.'),
('5887','0','0','0','I welcome you back, $n.'),
('7876','0','0','0','Some people wonder what we\'re doing out here in the desert.  Well... If I told you, then you\'d stay and try to make our profits!'),
('240','0','0','0','Ach, it\'s hard enough keeping order around here without all these new troubles popping up!  I hope you have good news, $n...'),
('344','0','5','0','Redridge is awash in chaos!'),
('264','0','0','0','At ease, $c. If you are just passing though I suggest you stick to the roads and only travel by day. If your business is here in Darkshire, consider lending your abilities to the Night Watch. Our Skill is unquestionable but our numbers are small.'),
('3519','0','0','0','I, Arynia Cloudsbreak, have been tasked with protecting the sanctity of the Oracle Grove.'),
('392','0','0','0','Do not be alarmed, $r.  I have long since passed from this land but I intend no harm to your kind.  I have witnessed too much death in my time.  My only wish now is for peace.  Perhaps you can help my cause.'),
('900','0','6','0','What business brings you before the Court of Lakeshire and the Honorable Magistrate Solomon?'),
('3567','0','1','0','Well met, $n. It is good to see that $cs like yourself are taking an active part in protecting the groves.'),
('11862','0','0','0',''),
('10537','0','0','0','We cannot take care of all the threats in this area alone. We could use another fighting hand, $n.'),
('5641','0','1','0','The main threat Thrall wishes dealt with is the Burning Blade---members of the Horde that have given their loyalty to the demons. They seek to practice their dark magic and care little for Thrall\'s visions of the Horde\'s future here in Kalimdor.'),
('737','0','0','0','Well,, hello there. You seem like you wouldn\'t be opposed to making some coin,, hm? I can tell from the look in your eyes. I am Mogul Kebok,, overseer of operations in Azeroth,, and if it is riches you seek,, perhaps I can make arrangements.'),
('773','0','0','0','$C,, eh? I am Krazek,, Baron Revilgaz\'s secretary. I know everything about the goings on in this jungle and beyond. Perhaps you\'d be interested in knowing the going price on oil in Ratchet? No? Looking for work,, maybe? I can help you there.'),
('2498','0','0','0','What what?!?  We all have profit to make... and we won\'t do it by standing idle.'),
('3845','0','0','0','We elves have a long history.  Let us hope this history does not return to haunt us.'),
('5204','0','0','0','If we are to make our place in this world,, then we will do so through study,, and through the will to ignore our fading human instincts.'),
('7882','0','1','0','We\'re here to make a profit.  And having our goods stolen is no way to make a profit.'),
('7900','0','0','0','Hello,, $N. Perhaps you have some time to chat?'),
('9078','0','1','0','Dear $g boy:girl;,, you have arrived just in time to assist the Kargath Expeditionary Force.'),
('10926','0','0','0','I never feel warm anymore...'),
('11039','0','1','0','Greetings,, $N. I am Duke Nicholas Zverenhoff of the Argent Dawn.');

DROP TABLE IF EXISTS `quest_greeting_locale`;
CREATE TABLE `quest_greeting_locale` (
  `ID` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `Type` tinyint(3) unsigned NOT NULL DEFAULT 0,
  `locale` varchar(4) NOT NULL,
  `Greeting` text DEFAULT NULL,
  PRIMARY KEY (`ID`,`Type`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `quest_details`;
CREATE TABLE `quest_details` (
  `ID` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `Emote1` smallint(5) unsigned NOT NULL DEFAULT 0,
  `Emote2` smallint(5) unsigned NOT NULL DEFAULT 0,
  `Emote3` smallint(5) unsigned NOT NULL DEFAULT 0,
  `Emote4` smallint(5) unsigned NOT NULL DEFAULT 0,
  `EmoteDelay1` int(10) unsigned NOT NULL DEFAULT 0,
  `EmoteDelay2` int(10) unsigned NOT NULL DEFAULT 0,
  `EmoteDelay3` int(10) unsigned NOT NULL DEFAULT 0,
  `EmoteDelay4` int(10) unsigned NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

REPLACE INTO quest_details (ID, `Emote1`, Emote2, Emote3, Emote4, EmoteDelay1, EmoteDelay2, EmoteDelay3, EmoteDelay4)
SELECT entry, DetailsEmote1, DetailsEmote2, DetailsEmote3, DetailsEmote4, 0, 0, 0, 0 FROM quest_template;

ALTER TABLE quest_template 
	DROP IF EXISTS OfferRewardEmote1, DROP IF EXISTS OfferRewardEmote2, DROP IF EXISTS OfferRewardEmote3, DROP IF EXISTS OfferRewardEmote4, DROP IF EXISTS OfferRewardText, DROP IF EXISTS CompleteEmote, DROP IF EXISTS IncompleteEmote, DROP IF EXISTS RequestItemsText, DROP IF EXISTS DetailsEmote1, DROP IF EXISTS DetailsEmote2, DROP IF EXISTS DetailsEmote3, DROP IF EXISTS DetailsEmote4;