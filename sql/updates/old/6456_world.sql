#Silent Resolve should affect every spell
UPDATE spell_affect SET SpellFamilyMask = 0x7FFFFFFFFFFFFF where entry = 14787;