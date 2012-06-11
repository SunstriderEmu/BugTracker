UPDATE spell_template SET effect1 = 6, effectApplyAuraName1 = 23, effectMiscValue1 = 0, effectImplicitTargetA1 = 1, effectAmplitude1 = 1000 WHERE id = 37386;

DELETE FROM spell_template WHERE id = 18350;
INSERT INTO spell_template (id, spellName3, effect1, effectApplyAuraName1, effectMiscValue1, effectImplicitTargetA1, durationIndex, equippedItemClass, effectBasePoints1, powerType) VALUES (18350, "Résistance du familier", 6, 22, 127, 5, 65, -1, 130, 0);
