REPLACE INTO trinity_string (entry, content_default, content_loc2) VALUES (11901,"You can\'t enter Black Morass until you rescue Thrall from Durnholde Keep.", "Vous ne pouvez pas entrer dans le Noir marécage tant que vous n\'avez pas libéré Thrall du Fort-de-Durn.");
REPLACE INTO trinity_string (entry, content_default, content_loc2) VALUES (11902,"Heroic Difficulty requires completion of the \"Hard to Kill\" quest.","Vous devez avoir terminé la quête \"L\'Increvable\" pour pouvoir accéder à la difficulté Héroïque.");

UPDATE access_requirement SET quest_failed_text = '0', heroic_quest_failed_text = '0';
ALTER TABLE access_requirement
	MODIFY quest_failed_text INT(11) UNSIGNED NOT NULL DEFAULT '0';
	
UPDATE access_requirement SET quest_failed_text = 11901 WHERE id = 16;
UPDATE access_requirement SET heroic_quest_failed_text = 11902 WHERE id = 51;

#Battle for Mount Hyjal - The Vials of Eternity
UPDATE access_requirement SET quest_done = 10445 WHERE id = 29;
