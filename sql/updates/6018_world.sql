UPDATE version SET core_version = "Winrunner Rev: 6018";

UPDATE spell_template
SET effect2 = 6, effectImplicitTargetA2 = 1, effectApplyAuraName2 = 23, effectAmplitude2 = 15000
WHERE id = 40879;

#add dual wield to mother shahraz
UPDATE creature_template SET flags_extra = 41 + 0x20 WHERE entry = 22947;

#Fatal Attraction dummy aura set to 2 sec (this is used to determine if players are far away enough from each others)
UPDATE spell_template SET durationIndex = 39 WHERE id = 40871;