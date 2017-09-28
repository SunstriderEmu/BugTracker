UPDATE version SET core_version = "Winrunner Rev: 6021";

UPDATE spell_template
SET effect2 = 0, effectImplicitTargetA2 = 0, effectApplyAuraName2 = 0, effectAmplitude2 = 0, effectAmplitude1 = 15000
WHERE id = 40879;

UPDATE creature_template SET flags_extra = 41 + 0x00200000 WHERE entry = 22947;

UPDATE spell_template SET effect2 = 2, effectDieSides2 = 1000, effectBasePoints2 = 3499, 
effectImplicitTargetA2 = 6, effectMultipleValue2 = 4, effectChainTarget2 = 10
WHERE id = 40861;