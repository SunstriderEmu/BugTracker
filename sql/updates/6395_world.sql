DELETE FROM creature_template_addon WHERE entry =17964;
update creature_template set AIName = "", ScriptName = "npc_wastewalker_worker" where entry = 17964;

SET @ENTRY := 17959;
UPDATE `creature_template` SET `AIName`="SmartAI",`ScriptName`="npc_coilfang_slavehandler" WHERE `entry`=@ENTRY;