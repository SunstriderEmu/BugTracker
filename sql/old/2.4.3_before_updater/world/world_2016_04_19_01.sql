# SPELL_TARGET_TYPE_GAMEOBJECT
REPLACE INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry,ConditionTypeOrReference,ConditionValue1,ConditionValue2)
SELECT 13, 1, entry, 31, 5, targetEntry FROM spell_script_target WHERE `type` = 0;

# SPELL_TARGET_TYPE_CREATURE 
REPLACE INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry,ConditionTypeOrReference,ConditionValue1,ConditionValue2)
SELECT 13, 1, entry, 31, 3, targetEntry FROM spell_script_target WHERE `type` = 1;

# SPELL_TARGET_TYPE_DEAD
REPLACE INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry,ConditionTypeOrReference,ConditionValue1,ConditionValue2)
SELECT 13, 1, entry, 31, 3, targetEntry FROM spell_script_target WHERE `type` = 2;
REPLACE INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry,ConditionTypeOrReference,NegativeCondition)
SELECT 13, 1, entry, 36, 1 FROM spell_script_target WHERE `type` = 2;

DROP TABLE spell_script_target;