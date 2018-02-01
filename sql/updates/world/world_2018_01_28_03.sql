UPDATE spell_proc SET SpellPhaseMask = 0 WHERE SpellPhaseMask != 0 AND NOT (ProcFlags & 2184528);

UPDATE conditions SET SourceGroup = 0 WHERE id IN (238, 236, 239, 237);
UPDATE conditions SET SourceGroup = 7 WHERE id IN (637, 638, 640, 1853);

UPDATE conditions SET SourceGroup = 1 WHERE SourceEntry = 38173;

DELETE FROM conditions WHERE id IN (247, 248, 249);

REPLACE INTO `conditions` (id, `SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) values(247, '13','1','37919','0','0','33','1','0','1','0','1','0','0','','Arcano-Dismantle effect 0 cannot hit self');
REPLACE INTO `conditions` (id, `SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) values(248, '13','2','37919','0','0','33','1','0','1','0','1','0','0','','Arcano-Dismantle effect 1 cannot hit self');
REPLACE INTO `conditions` (id, `SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) values(249, '13','1','37919','0','0','31','0','3','21909','0','0','0','0','','Arcano-Dismantle effect 0 can hit only Arcano-Scorp');
REPLACE INTO `conditions` (id, `SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) values(250, '13','2','37919','0','0','31','0','3','21909','0','0','0','0','','Arcano-Dismantle effect 1 can hit only Arcano-Scorp');

UPDATE conditions SET SourceGroup = 3 WHERE id IN (1348, 1355, 1359, 1378, 1747);
UPDATE conditions SET SourceGroup = 7 WHERE id IN (1367);


UPDATE creature_template SET AIName = "" WHERE AIName IN ("PetAI", "TotemAI");

UPDATE creature_template SET spell1 = 0 WHERE spell1 NOT IN (SELECT entry FROM spell_template);
UPDATE creature_template SET spell2 = 0 WHERE spell2 NOT IN (SELECT entry FROM spell_template);
UPDATE creature_template SET spell3 = 0 WHERE spell3 NOT IN (SELECT entry FROM spell_template);
UPDATE creature_template SET spell4 = 0 WHERE spell4 NOT IN (SELECT entry FROM spell_template);
UPDATE creature_template SET spell5 = 0 WHERE spell5 NOT IN (SELECT entry FROM spell_template);
UPDATE creature_template SET spell6 = 0 WHERE spell6 NOT IN (SELECT entry FROM spell_template);
UPDATE creature_template SET spell7 = 0 WHERE spell7 NOT IN (SELECT entry FROM spell_template);
UPDATE creature_template SET spell8 = 0 WHERE spell8 NOT IN (SELECT entry FROM spell_template);

DELETE FROM spell_affect WHERE effectId = 2 AND entry IN (14523, 14784, 14785, 14786, 14787, 16998, 16999);
DELETE FROM spell_affect WHERE entry = 53087;


DELETE FROM conditions WHERE SourceEntry = 53108;
UPDATE gameobject SET orientation = 0 WHERE guid = 7595;
UPDATE gameobject SET rotation2 = 0.999991, rotation3 = -0.00420371 WHERE guid = 13465;