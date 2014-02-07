#illidari council, re setting SPELL_EMPOWERED_SMITE interruptible

UPDATE spell_template
SET interruptFlags = 15
WHERE id = 41471;