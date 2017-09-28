#Setting bg spell target from TARGET_UNIT_CASTER to TARGET_UNIT_TARGET_ANY
UPDATE spell_template SET effectImplicitTargetA1 = 25 WHERE id = 23493;

ALTER TABLE spell_template CHANGE id entry INT UNSIGNED;