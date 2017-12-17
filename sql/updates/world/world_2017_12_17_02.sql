-- kalecgos spectral blast
DELETE FROM spell_linked_spell WHERE spell_trigger = 44869;

replace into `spell_script_names` (`spell_id`, `ScriptName`) values('44811','spell_kalecgos_spectral_realm_trigger');
replace into `spell_script_names` (`spell_id`, `ScriptName`) values('44869','spell_kalecgos_spectral_blast');

-- Removed useless NullCreatureAI in db
UPDATE creature_template SET AIName = "" WHERE AIName = "NullCreatureAI" AND ScriptName != "" AND ScriptName IS NOT NULL;

-- Some KJ texts

replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('25608','0','0','All my plans have led to this!','14','0','100','0','0','12495','25544','0','KJ - SAY_KJ_OFFCOMBAT1');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('25608','0','1','Stay on task, do not waste time!','14','0','100','0','0','12496','25545','0','KJ - SAY_KJ_OFFCOMBAT2');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('25608','0','2','I have waited long enough!','14','0','100','0','0','12497','25546','0','KJ - SAY_KJ_OFFCOMBAT3');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('25608','0','3','Fail me and suffer for eternity!','14','0','100','0','0','12498','25547','0','KJ - SAY_KJ_OFFCOMBAT4');
replace into `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) values('25608','0','4','Drain the girl! Drain her power until there is nothing but a vacant shell!','14','0','100','0','0','12499','25548','0','KJ - SAY_KJ_OFFCOMBAT5');

replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('25544','0','All my plans have led to this!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('25545','0','Stay on task, do not waste time!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('25546','0','I have waited long enough!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('25547','0','Fail me and suffer for eternity!','','0','0','0','0','0','0','0','0','1','18019');
replace into `broadcast_text` (`ID`, `Language`, `MaleText`, `FemaleText`, `EmoteID0`, `EmoteID1`, `EmoteID2`, `EmoteDelay0`, `EmoteDelay1`, `EmoteDelay2`, `SoundId`, `Unk1`, `Unk2`, `VerifiedBuild`) values('25548','0','Drain the girl! Drain her power until there is nothing but a vacant shell!','','0','0','0','0','0','0','0','0','1','18019');
