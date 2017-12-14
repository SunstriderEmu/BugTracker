DELETE FROM conditions WHERE SourceEntry = 30834 AND SourceTypeOrReferenceId = 13;
REPLACE INTO spell_template_override (entry, effectImplicitTargetA1, comment) VALUES (30834, 25, 'Karazhan Malcheezar fight, set TARGET_UNIT_TARGET_ANY to scripted spell');

-- Custom Infernal Relay spell can only target CREATURE_INFERNAL_RELAY
REPLACE INTO conditions (id, SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1, ConditionValue2)  VALUES (1505, 13, 1, 53108, 31, 3, 17645);