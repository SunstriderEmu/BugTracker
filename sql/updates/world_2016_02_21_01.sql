UPDATE creature c 
 JOIN creature_template ct ON c.id = ct.entry AND c.modelid = ct.modelid1
SET c.modelid = 0;

ALTER TABLE `spell_template`   
  CHANGE `spellFamilyFlags1` `spellFamilyFlags` BIGINT(20) UNSIGNED DEFAULT 0  NOT NULL;

UPDATE spell_template
	SET spellFamilyFlags = spellFamilyFlags & (spellFamilyFlags2 * POWER(2,32))
	WHERE spellFamilyFlags2 != 0;
	
 ALTER TABLE  `spell_template`
	DROP COLUMN spellFamilyFlags2;