UPDATE `creature_template` SET `ScriptName`='npc_maghar_captive' WHERE `entry`=18210;

INSERT INTO `script_texts` (`entry`,`content_default`,`sound`,`type`,`language`,`emote`,`comment`) VALUES
   (-1000482,'Look out!',0,0,0,0,'maghar captive SAY_MAG_START'),
   (-1000483,'Don''t let them escape! Kill the strong one first!',0,0,0,0,'maghar captive SAY_MAG_NO_ESCAPE'),
   (-1000484,'More of them coming! Watch out!',0,0,0,0,'maghar captive SAY_MAG_MORE'),
   (-1000485,'Where do you think you''re going? Kill them all!',0,0,0,0,'maghar captive SAY_MAG_MORE_REPLY'),
   (-1000486,'Ride the lightning, filth!',0,0,0,0,'maghar captive SAY_MAG_LIGHTNING'),
   (-1000487,'FROST SHOCK!!!',0,0,0,0,'maghar captive SAY_MAG_SHOCK'),
   (-1000488,'It is best that we split up now, in case they send more after us. Hopefully one of us will make it back to Garrosh. Farewell stranger.',0,0,0,0,'maghar captive SAY_MAG_COMPLETE');
