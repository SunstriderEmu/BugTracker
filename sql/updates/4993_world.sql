UPDATE script_texts SET content_loc2 = "Contemplez Ragnaros, le Seigneur du feu. Celui qui était ancien alors que ce monde était jeune. Inclinez vous devant lui mortels, inclinez vous devant votre mort !" WHERE entry = -1409008;
UPDATE script_texts SET content_loc2 = "TROP TÔT, TU M'AS EVEILLÉ TROP TÔT EXECUTUS. QUE SIGNIFIE CETTE INTRUSION?" WHERE entry = -1409009;
UPDATE script_texts SET content_loc2 = "Seigneur ! Ces mortels infidèles ont envahis votre sanctuaire, et voulaient voler vos secrets !" WHERE entry = -1409010;
UPDATE script_texts SET content_loc2 = "IDIOT ! TU AS LAISSÉ CES INSECTES RAMPER À TRAVERS CE NOYAU SACRÉ, ET TU LES AS CONDUITS DANS MON REPAIRE? TU AS ECHOUÉ EXECUTUS ! JUSTICE SERA FAITE EN VERITÉ." WHERE entry = -1409011;
UPDATE script_texts SET content_loc2 = "À VOTRE TOUR INSECTES. VOUS VOULIEZ CONNAÎTRE LE POUVOIR DE RAGNAROS, VOUS ALLEZ LE DÉCOUVRIR !" WHERE entry = -1409012;
UPDATE script_texts SET content_loc2 = "VENEZ OH MES SERVITEURS ! VENEZ DÉFENDRE VOTRE MAÎTRE !" WHERE entry = -1409013;
UPDATE script_texts SET content_loc2 = "VOUS NE POUVEZ PAS DÉFAIRE LA FLAMME VIVANTE ! VENEZ SUPPÔTS DU FEU ! VENEZ CRÉATURES DE LA HAINE ! VOTRE MAÎTRE VOUS APPELLE !" WHERE entry = -1409014;
UPDATE script_texts SET content_loc2 = "PAR LE FEU SOYEZ PURIFIÉS !" WHERE entry = -1409015;
UPDATE script_texts SET content_loc2 = "GOÛTEZ AUX FLAMMES DE SULFURON !" WHERE entry = -1409016;
UPDATE script_texts SET content_loc2 = "MEURT INSECTE !" WHERE entry = -1409017;
UPDATE script_texts SET content_loc2 = "MA PATIENCE S'ÉPUISE, VENEZ VOUS FAIRE TUER ! MOUCHERONS !" WHERE entry = -1409018;

UPDATE creature_template SET ScriptName = "mob_eventai", minlevel = 73, maxlevel = 73, faction_A = 91, faction_H = 91 WHERE entry = 13148;
DELETE FROM `eventai_scripts` WHERE `creature_id` = 13148;
INSERT INTO `eventai_scripts` (`creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) values('13148','0','0','100','0','0','0','0','0','11','21155','0','3','0','0','0','0','0','0','0','0','Flame of Ragnaros - Intense Heat');

INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) values('21886','409','818.972290','-870.415100','-229.0','0');
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) values('21900','409','839.632568','-874.043518','-229.0','0');
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) values('21901','409','860.547852','-868.619629','-229.0','0');
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) values('21902','409','872.576233','-852.417969','-229.0','0');
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) values('21903','409','872.763733','-832.229614','-229.0','0');
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) values('21904','409','866.243530','-809.703613','-229.0','0');
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) values('21905','409','848.195496','-797.044434','-229.0','0');
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) values('21906','409','827.053101','-799.908081','-229.0','0');
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) values('21907','409','814.249084','-814.484314','-229.0','0');
