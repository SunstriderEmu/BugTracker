/* Anetheron hp */
UPDATE creature_template SET minhealth = 4630000, maxhealth = 4630000 WHERE entry = 17808;
/* vampiric aura duration */
UPDATE spell_template set durationIndex = 21 WHERE id = 38196;

/* inferno */
UPDATE creature_template SET minlevel = 72, maxlevel = 72, minhealth = 220000, maxhealth = 220000 WHERE entry = 17818;