-- immune all bosses to spell slow 
UPDATE creature_template SET ScriptName = "boss_balinda" WHERE entry = 11949;
UPDATE creature_template SET ScriptName = "boss_galvangar" WHERE entry = 11947;

-- same immunties for all bosses
UPDATE creature_template SET AIName = "", mechanic_immune_mask = 617299803, flags_extra = flags_extra | 0x0000800 WHERE entry IN (11949, 11947, 11946, 11948);
-- marshals and warmasters
UPDATE creature_template SET AIName = "", ScriptName = "npc_av_marshal_or_warmaster" WHERE entry IN (14777,14776,14773,14772,14765,14764,14763,14762);

-- damages & modifiers

-- marshals and warmasters
UPDATE creature_template SET HealthModifier = 20, ArmorModifier = 1, DamageModifier = 7.5, ManaModifier = 0 WHERE entry IN (14777,14776,14773,14772,14765,14764,14763,14762);

--all bosses
UPDATE creature_template SET DamageModifier = 7.5, ArmorModifier = 1 WHERE entry IN (11949, 11947, 11946, 11948);
--drek & vanndar
UPDATE creature_template SET HealthModifier = 3, DamageModifer = 27.5 WHERE entry IN (11946, 11948);
--galv
UPDATE creature_template SET HealthModifier = 25 WHERE entry = 11947;
--balinda
UPDATE creature_template SET HealthModifier = 30, ManaModifier = 30 WHERE entry = 11949;

--archers
UPDATE creature_template SET HealthModifier = 1.5, DamageModifier = 1.5 WHERE entry = 13359;
UPDATE creature_model_info SET combat_reach = 1.5 WHERE modelid IN (13400, 13401);

-- some guards
UPDATE creature_template SET HealthModifier = 0.7 AND DamageModifier = 2 WHERE entry IN (12050, 12053)

-- remove unused smartscripts
DELETE FROM smart_scripts WHERE entryorguid IN (11949, 11947, 11946, 11948);
DELETE FROM smart_scripts WHERE entryorguid IN (14777,14776,14773,14772,14765,14764,14763,14762);
DELETE FROM creature_text WHERE CreatureId IN (14777,14776,14773,14772,14765,14764,14763,14762);

-- Balinda elemental
DELETE FROM smart_scripts WHERE entryorguid = 25040;
REPLACE INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_flags`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('25040','0','1','0','37','0','100','0','0','0','0','0','58','6','46983','3000','4000','0','0','2','0','0','0','0','0','0','0','0','Greater Water Elemental - On AI Initialize - Install Caster SUN Template ');


-- Balinda
REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11949','0','0','Begone, uncouth scum! The Alliance shall prevail in Alterac Valley!','14','0','100','0','0','0','10054','0','Captain Balinda Stonehearth');
REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11949','1','0','Filthy Frostwolf cowards! If you want a fight, you\'ll have to come to me!','14','0','100','0','0','0','10375','0','Captain Balinda Stonehearth');
REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11949','2','0','Take heart, Alliance! Throw these villains from Alterac Valley!','14','0','100','0','0','0','10056','0','Captain Balinda Stonehearth');

REPLACE INTO `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10054','0','','Begone, uncouth scum! The Alliance shall prevail in Alterac Valley!','0','0','0','0','0','0','0','0','1','18019');
REPLACE INTO `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10056','0','','Take heart, Alliance! Throw these villains from Alterac Valley!','0','0','0','0','0','0','0','0','1','18019');
REPLACE INTO `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10375','0','','Filthy Frostwolf cowards! If you want a fight, you\'ll have to come to me!','0','0','0','0','0','0','0','0','1','18019');

-- Galvangar
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11947','0','0','Die! Your kind has no place in Alterac Valley!','14','0','100','0','0','0','10055','0','Captain Galvangar');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11947','1','0','I\'ll never fall for that, fool! If you want a battle, it will be on my terms and in my lair.','14','0','100','0','0','0','10378','0','Captain Galvangar');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11947','2','0','Now is the time to attack! For the Horde!','14','0','100','0','0','0','10057','0','Captain Galvangar');

replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10055','0','Die! Your kind has no place in Alterac Valley!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10057','0','Now is the time to attack! For the Horde!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10378','0','I\'ll never fall for that, fool! If you want a battle, it will be on my terms and in my lair.','','0','0','0','0','0','0','0','0','1','18019');

-- Vanndar
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','0','0','Soldiers of Stormpike, your General is under attack! I require aid! Come! Come! Slay these mangy Frostwolf dogs.','14','0','100','0','0','0','10243','0','Vanndar Stormpike');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','1','0','You\'ll never get me out of me bunker, heathens!','14','0','100','0','0','0','10373','0','Vanndar Stormpike');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','1','1','Why don\'t ya try again without yer cheap tactics, pansies! Or are you too chicken???','14','0','100','0','0','0','10374','0','Vanndar Stormpike');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','2','0','I will tell you this much...Alterac Valley will be ours.','14','0','100','0','0','0','0','0','Vanndar Stormpike');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','2','1','Your attacks are weak! Go practice on some rabbits and come back when you\'re stronger.','14','0','100','0','0','0','8839','0','Vanndar Stormpike');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','2','2','We will not be swayed from our mission!','14','0','100','0','0','0','8842','0','Vanndar Stormpike');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','2','3','It\'ll take more than you rabble to bring me down!','14','0','100','0','0','0','8841','0','Vanndar Stormpike');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','2','4','We, the Alliance, will prevail!','14','0','100','0','0','0','8843','0','Vanndar Stormpike');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','2','5','The Stormpike clan bows to no one, especially the horde!','14','0','100','0','0','0','8838','0','Vanndar Stormpike');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','2','6','Is that the best you can do?','14','0','100','0','0','0','13130','0','Vanndar Stormpike');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11948','3','0','Take no prisoners! Drive these heathens from our lands!','14','0','100','0','0','0','12351','0','Vanndar Stormpike');

replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('8838','0','The Stormpike clan bows to no one, especially the horde!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('8839','0','Your attacks are weak! Go practice on some rabbits and come back when you\'re stronger.','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('8841','0','It\'ll take more than you rabble to bring me down!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('8842','0','We will not be swayed from our mission!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('8843','0','We, the Alliance, will prevail!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10243','0','Soldiers of Stormpike, your General is under attack! I require aid! Come! Come! Slay these mangy Frostwolf dogs.','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10373','0','You\'ll never get me out of me bunker, heathens!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10374','0','Why don\'t ya try again without yer cheap tactics, pansies! Or are you too chicken???','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('12351','0','Take no prisoners! Drive these heathens from our lands!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('13130','0','Is that the best you can do?','','0','0','0','0','0','0','0','0','1','18019');

-- Drek'
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11946','0','0','Stormpike filth! In my keep?! Slay them all!','14','0','100','0','0','0','10245','0','Drek\'Thar');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11946','1','0','You seek to draw the General of the Frostwolf legion out from his fortress? PREPOSTEROUS!','14','0','100','0','0','0','10377','0','Drek\'Thar');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11946','2','0','Stormpike weaklings, face me in my fortress - if you dare!','14','0','100','0','0','0','10376','0','Drek\'Thar');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11946','3','0','Your attacks are slowed by the cold, I think!','14','0','100','0','0','0','8846','0','Drek\'Thar');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11946','3','1','Today, you will meet your ancestors!','14','0','100','0','0','0','8849','0','Drek\'Thar');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11946','3','2','If you will not leave Alterac Valley on your own, then the Frostwolves will force you out!','14','0','100','0','0','0','8847','0','Drek\'Thar');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11946','3','3','You cannot defeat the Frostwolf clan!','14','0','100','0','0','0','8844','0','Drek\'Thar');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11946','3','4','You are no match for the strength of the Horde!','14','0','100','0','0','0','8848','0','Drek\'Thar');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11946','3','5','Leave no survivors!','14','0','100','0','0','0','12352','0','Drek\'Thar');

replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10245','0','Stormpike filth! In my keep?! Slay them all!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10377','0','You seek to draw the General of the Frostwolf legion out from his fortress? PREPOSTEROUS!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('10376','0','Stormpike weaklings, face me in my fortress - if you dare!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('8846','0','Your attacks are slowed by the cold, I think!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('8849','0','Today, you will meet your ancestors!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('8847','0','If you will not leave Alterac Valley on your own, then the Frostwolves will force you out!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('8844','0','You cannot defeat the Frostwolf clan!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('8848','0','You are no match for the strength of the Horde!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('12352','0','Leave no survivors!','','0','0','0','0','0','0','0','0','1','18019');

-- snivle text
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('11677','0','0','Snivvle is here! Snivvle claims the Coldtooth mine!','12','0','100','0','0','0','10025','0','Taskmaster Snivvle');
REPLACE INTO locales_creature_text (entry, groupid, id, text_loc2) VALUES ('11677','0','0', "Snivvle est là ! Snivvle s'empare de la mine de Froidedent !");

--Snowblind windcaller
DELETE FROM smart_scripts WHERE entryorguid = 11675;
REPLACE INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_flags`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('11675','0','1','0','37','0','100','0','0','0','0','0','58','6','9532','3400','4800','0','0','2','0','0','0','0','0','0','0','0','Snowblind Windcaller - On AI Initialize - Install Caster SUN Template ');
