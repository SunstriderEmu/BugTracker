DELETE FROM spell_proc WHERE SpellId IN (36659, 35244, 32065, 30702, 30703, 30704, 30705);
UPDATE spell_proc SET SpellPhaseMask = 2 WHERE SpellId IN (37603, 38394, 40478, 45054);
UPDATE spell_proc SET SpellPhaseMask = 0 WHERE SpellId IN (-30701);

REPLACE INTO spell_template_override (entry, procFlags, Comment) VALUES (32065, 0, "Removed procFlags"),  (35244, 0, "Removed procFlags"),  (36659, 0, "Removed procFlags");