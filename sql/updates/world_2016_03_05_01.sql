UPDATE creature_text
SET text = CONCAT(text)
WHERE `type` = 16 AND `text` NOT LIKE "\%s%";

UPDATE locales_creature_text lct
JOIN creature_text ct ON ct.entry = lct.entry
SET text_loc2 = CONCAT("%s ", text_loc2)
WHERE `type` = 16 AND `text_loc2` NOT LIKE "\%s%";