#Tranquility healing effect should not be affected by LoS
UPDATE spell_template SET AttributesEx2 = 0x60000000 + 0x004 WHERE id IN (44203,44205,44206,44207,44208);

REPLACE INTO command VALUES
("gameobject setvalue",3,"Syntax : .gobject setvalue #guid #index #value [uint32/uint64/float]",0),
("gameobject getvalue",3,"Syntax : .gobject getvalue #guid #index [uint32/uint64/float]",0),
("debug getvalue",3,"Syntax : .debug getvalue #index [uint32/uint64/float]",0),
("debug setvalue",3,"Syntax : .debug getvalue #index #value [uint32/uint64/float]",0);