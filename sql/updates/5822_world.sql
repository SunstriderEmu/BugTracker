/* Added no initial aggro for vampirich touch energize effect */
UPDATE spell_template SET AttributesEx3 = 0x02020000 WHERE entry = 34919;

/* Vampiric embrace too? */