UPDATE `spell_affect` SET `SpellFamilyMask`=`SpellFamilyMask` & ~0x200000000 WHERE `Entry` IN ('15257', '15331', '15332', '15333', '15334');
UPDATE `spell_proc_event` SET `SpellFamilyMask`=`SpellFamilyMask` & ~0x200000000 WHERE `SpellFamilyMask` & 0x200000000 AND `SpellFamilyName`='6';
