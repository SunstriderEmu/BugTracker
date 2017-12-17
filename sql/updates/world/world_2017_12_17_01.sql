# http://www.wowhead.com/forums&topic=20500/can-mana-burn-crit#p185635
# Fix Mana Burn crit
DELETE FROM spell_template_override WHERE entry IN (8129,8131,10874,10875,10876,25379,25380);
INSERT INTO spell_template_override (entry, attributesEx2, comment) VALUES
(8129, 537395200,'Add SPELL_ATTR2_CANT_CRIT to Priest\'s spell Mana Burn Rank 1'),
(8131, 537395200,'Add SPELL_ATTR2_CANT_CRIT to Priest\'s spell Mana Burn Rank 2'),
(10874, 537395200,'Add SPELL_ATTR2_CANT_CRIT to Priest\'s spell Mana Burn Rank 3'),
(10875, 537395200,'Add SPELL_ATTR2_CANT_CRIT to Priest\'s spell Mana Burn Rank 4'),
(10876, 537395200,'Add SPELL_ATTR2_CANT_CRIT to Priest\'s spell Mana Burn Rank 5'),
(25379, 537395200,'Add SPELL_ATTR2_CANT_CRIT to Priest\'s spell Mana Burn Rank 6'),
(25380, 537395200,'Add SPELL_ATTR2_CANT_CRIT to Priest\'s spell Mana Burn Rank 7');