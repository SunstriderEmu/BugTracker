#setting Shimmerscale Eel inhabit type to water
UPDATE creature_template SET InhabitType = 2 WHERE entry = 18750;

#Subtlety resist dispell effect should affect every spell
UPDATE spell_affect SET SpellFamilyMask = 0x7FFFFFFFFFFFFF where entry IN (17118,17119,17120,17121,17122) AND effectId = 1;

#Sanctified Seals should apply on Seal of the Crusader
UPDATE spell_affect SET SpellFamilyMask = 4398214283776 WHERE entry IN (32043,35396,35397);

#Healing Grace resist dispell effect should affect every spell
UPDATE spell_affect SET SpellFamilyMask = 0x7FFFFFFFFFFFFF where entry IN (29187,29189,19191);

#Stoicism resist dispell effect should affect every spell
UPDATE spell_affect SET SpellFamilyMask = 0x7FFFFFFFFFFFFF where entry IN (31844,31845);

#Righteous Defense should be subjet to MELEE hit chance
UPDATE spell_template SET dmgClass = 2 WHERE id = 31790;

#Fixed wrong DB values for Shadowguard
UPDATE spell_template SET effectTriggerSpell1 = 28377 WHERE id = 18137;
UPDATE spell_template SET effectTriggerSpell1 = 28378 WHERE id = 19308;
UPDATE spell_template SET effectTriggerSpell1 = 28379 WHERE id = 19309;
UPDATE spell_template SET effectTriggerSpell1 = 28380 WHERE id = 19310;
UPDATE spell_template SET effectTriggerSpell1 = 28381 WHERE id = 19311;
UPDATE spell_template SET effectTriggerSpell1 = 28382 WHERE id = 19312;
UPDATE spell_template SET effectTriggerSpell1 = 28385 WHERE id = 25477;

#Moving some triggered id from core to db (these spells are already working)

#Greater Heal Refund
UPDATE spell_template SET effectTriggerSpell1 = 37595 WHERE id = 37594;

#Blessed Recovery
UPDATE spell_template SET effectTriggerSpell1 = 27813 WHERE id = 27811;
UPDATE spell_template SET effectTriggerSpell1 = 27817 WHERE id = 27815;
UPDATE spell_template SET effectTriggerSpell1 = 27818 WHERE id = 27816;

#Judgement of Light
UPDATE spell_template SET effectTriggerSpell1 = 20267 WHERE id = 20185;
UPDATE spell_template SET effectTriggerSpell1 = 20341 WHERE id = 20344;
UPDATE spell_template SET effectTriggerSpell1 = 20342 WHERE id = 20345;
UPDATE spell_template SET effectTriggerSpell1 = 20343 WHERE id = 20346;
UPDATE spell_template SET effectTriggerSpell1 = 27163 WHERE id = 27162;
#Judgement of Wisdom
UPDATE spell_template SET effectTriggerSpell1 = 20268 WHERE id = 20186;
UPDATE spell_template SET effectTriggerSpell1 = 20352 WHERE id = 20354;
UPDATE spell_template SET effectTriggerSpell1 = 20353 WHERE id = 20355;
UPDATE spell_template SET effectTriggerSpell1 = 27165 WHERE id = 27164;

#Lightning Shield (overwrite non existing triggered spell call in spell.dbc
UPDATE spell_template SET effectTriggerSpell1 = 26364 WHERE id = 324;
UPDATE spell_template SET effectTriggerSpell1 = 26365 WHERE id = 325;
UPDATE spell_template SET effectTriggerSpell1 = 26366 WHERE id = 905;
UPDATE spell_template SET effectTriggerSpell1 = 26367 WHERE id = 945;
UPDATE spell_template SET effectTriggerSpell1 = 26369 WHERE id = 8134;
UPDATE spell_template SET effectTriggerSpell1 = 26370 WHERE id = 10431;
UPDATE spell_template SET effectTriggerSpell1 = 26363 WHERE id = 10432;
UPDATE spell_template SET effectTriggerSpell1 = 26371 WHERE id = 25469;
UPDATE spell_template SET effectTriggerSpell1 = 26372 WHERE id = 25472;

#Warrior rampage
UPDATE spell_template SET effectTriggerSpell1 = 30029 WHERE id = 29801;
UPDATE spell_template SET effectTriggerSpell1 = 30031 WHERE id = 30030;
UPDATE spell_template SET effectTriggerSpell1 = 30032 WHERE id = 30033;

#Blazing speed
UPDATE spell_template SET effectTriggerSpell1 = 31643 WHERE id IN (31641,31642);

#Aegis of Preservation (Aegis of Preservation trinket)
UPDATE spell_template SET effectTriggerSpell1 = 23781 WHERE id = 23780;

#Desperate Defense (Stonescythe Whelp, Stonescythe Alpha, Stonescythe Ambusher)
UPDATE spell_template SET effectTriggerSpell1 = 33898 WHERE id = 33896;

#Moonkin Form (Passive)
UPDATE spell_template SET effectTriggerSpell1 = 33926 WHERE id = 24905;

#Leader of the Pack
UPDATE spell_template SET effectTriggerSpell1 = 34299 WHERE id = 24932;

#Lightning Capacitor
UPDATE spell_template SET effectTriggerSpell1 = 37661 WHERE id = 37657;

#Lightning Shield (The Ten Storms set)
UPDATE spell_template SET effectTriggerSpell1 = 23552 WHERE id = 23551;
UPDATE spell_template SET effectTriggerSpell1 = 27635 WHERE id = 23552;

#Mana Surge (The Earthfury set)
UPDATE spell_template SET effectTriggerSpell1 = 23571 WHERE id = 23572;