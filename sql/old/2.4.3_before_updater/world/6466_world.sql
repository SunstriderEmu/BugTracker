#Shadow Sight can't miss
UPDATE spell_template SET AttributesEx3 = 0x00040000 WHERE id = 34709;
#Allowing KJ Armageddon to target any enemy unit
UPDATE spell_template SET effectImplicitTargetA1 = 6 WHERE id = 45921;