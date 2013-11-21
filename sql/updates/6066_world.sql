UPDATE version SET core_version = "Winrunner Rev: 6066";

#muru darkness
UPDATE creature_model_info SET bounding_radius = 0, combat_reach = 0 WHERE modelid = 15882;
#supremus
UPDATE creature_model_info SET bounding_radius = 19, combat_reach = 18 WHERE modelid = 21145;
#Muru : 2s void zone immune when bumped by 46264
UPDATE spell_template SET durationIndex = 39, effect2 = 6, effectApplyAuraName2 = 259, effectImplicitTargetA2 = 6, effectMiscValue2 = 46264 WHERE id = 46264;
#some immune for void sentinels
UPDATE creature_template SET mechanic_immune_mask = 617299803 WHERE entry = 25772;