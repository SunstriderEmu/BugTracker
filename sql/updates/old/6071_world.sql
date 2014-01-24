UPDATE version SET core_version = "Winrunner Rev: 6071";

#Muru added no heal effect on darkness P2
UPDATE spell_template SET durationIndex = 36, effect3 = 6, effectApplyAuraName3 = 118, 
effectBasePoints3 = -101, effectImplicitTargetA3 = 22, effectImplicitTargetB3 = 15, 
effectRadiusIndex3 = 15, effectBaseDice3 = 1
WHERE id = 46264;