UPDATE gameobject_template SET data1 = 18509, ScriptName = "go_sealed_tome" WHERE entry IN (181768, 181833, 181837, 181846, 181847, 181848);
UPDATE gameobject_loot_template SET ChanceOrQuestChance = 0, groupid = 1 WHERE entry = 18509;
UPDATE spell_template SET effectImplicitTargetA1 = 1, effectImplicitTargetB1 = 0 WHERE id IN (30762, 30763, 30764, 30765, 30766);
