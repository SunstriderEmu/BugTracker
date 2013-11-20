UPDATE version SET core_version = "Winrunner Rev: 6060";

#some immune for training dummy
UPDATE creature_template SET mechanic_immune_mask = 617299803 WHERE entry = 10;