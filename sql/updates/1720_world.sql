UPDATE `spell_affect` SET `SpellFamilyMask`=`SpellFamilyMask` & ~0x200000000 WHERE `SpellFamilyMask` & 0x200000000;
UPDATE `spell_proc_event` SET `SpellFamilyMask`=`SpellFamilyMask` & ~0x200000000 WHERE `SpellFamilyMask` & 0x200000000;
