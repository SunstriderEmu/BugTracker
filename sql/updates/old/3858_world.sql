DELETE FROM script_texts WHERE entry BETWEEN -1000757 AND -1000745;
INSERT INTO script_texts (entry, content_default, content_loc2, type, comment) VALUES
(-1000745, "Defenders, show these mongrels the fury of a Scyer!", "Défenseurs, montrez à ces bâtards la furie d'un Clairvoyant !", 1, "COMMANDER_HOBB_SAY1"),
(-1000746, "Stand tall, soldiers. Show them no quarter!", "Tenez bon, soldats. Ne faites pas de quartier !", 0, "COMMANDER_HOBB_SAY2"),
(-1000747, "BURN IT DOWN!", "BRÛLEZ TOUT !", 1, "SKYBREAKER_SAY1"),
(-1000748, "KILL THEM ALL!", "TUEZ LES TOUS !", 1, "SKYBREAKER_SAY2"),
(-1000749, "For the Dragonmaw!", "Pour les Gueule-de-dragon !", 1, "SKYBREAKER_SAY3"),
(-1000750, "Your bones will break under my boot, draenei!", "Tes os vont casser sous mes bottes, draenei !", 1, "SKYBREAKER_SAYALDOR1"),
(-1000751, "Long live the Dragonmaw! Die you worthless draenei!", "Longue vie aux Gueule-de-dragon ! Meurs, draenei inutile !", 1, "SKYBREAKER_SAYALDOR2"),
(-1000752, "Your bones will break under my boot, blood elf!", "Tes os vont casser sous mes bottes, elfe de sang !", 1, "SKYBREAKER_SAYSCYER1"),
(-1000753, "Long live the Dragonmaw! Die you worthless blood elf!", "Longue vie aux Gueule-de-dragon ! Meurs, elfe de sang inutile !", 1, "SKYBREAKER_SAYSCYER2"),
(-1000754, "Defenders, show these mongrels the fury of a Scyer!", "Défenseurs, montrez à ces bâtards la furie d'un membre de l'Aldor !", 1, "COMMANDER_ARCUS_SAY1"),
(-1000755, "Stand tall, soldiers. Show them no quarter!", "Tenez bon, soldats. Ne faites pas de quartier !", 0, "COMMANDER_ARCUS_SAY2"),
(-1000756, "Victory to the Scyers! The Dragonmaw has been defeated!", "Victoire aux Clairvoyants ! Les Gueule-de-dragon ont été défaits !", 1, "COMMANDER_HOBB_SAY3"),
(-1000757, "Victory to the Aldor! The Dragonmaw has been defeated!", "Victoire à l'Aldor ! Les Gueule-de-dragon ont été défaits !", 1, "COMMANDER_ARCUS_SAY3");

UPDATE creature_template SET unit_flags = 0x89000, minlevel = 68, maxlevel = 69, faction_a = 1776, faction_h = 1776, minhealth = 9000, maxhealth = 10000, mindmg = 197, maxdmg = 209, attackpower = 1420 WHERE entry = 23453;
UPDATE creature_template SET scriptname = "npc_commander_arcus" WHERE entry = 23452;
UPDATE creature_template SET scriptname = "npc_commander_hobb" WHERE entry = 23434;
UPDATE creature_template SET scriptname = "npc_dragonmaw_skybreaker", flags_extra = flags_extra | 0x40000 WHERE entry IN (23440, 23441);

DELETE FROM creature_template_addon WHERE entry IN (23440, 23441);
INSERT INTO creature_template_addon (entry, mount, bytes0, bytes2) VALUES (23440, 20684, 512, 4097), (23441, 20684, 512, 4097);
