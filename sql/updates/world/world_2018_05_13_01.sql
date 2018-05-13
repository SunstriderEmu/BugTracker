ALTER TABLE `spell_affect` COMMENT='You may add only first rank of spell';

-- delete some next ranks
DELETE FROM spell_affect WHERE entry IN (18175, 18176, 18177, 18178);