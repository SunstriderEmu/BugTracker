--removing cusstom flag SPELL_ATTR0_CU_ONE_STACK_PER_CASTER_SPECIAL, replaced with SPELL_GROUP_STACK_RULE_EXCLUSIVE_FROM_SAME_CASTER
REPLACE INTO spell_group VALUES (1122, 1120);
REPLACE INTO spell_group VALUES (1123, 8288);
REPLACE INTO spell_group VALUES (1124, 8289);
REPLACE INTO spell_group VALUES (1125, 11675);
REPLACE INTO spell_group VALUES (1126, 27217);
REPLACE INTO spell_group VALUES (1127, 41083);
REPLACE INTO spell_group VALUES (1128, 39123);

REPLACE INTO spell_group_stack_rules VALUES (1122, 2);
REPLACE INTO spell_group_stack_rules VALUES (1123, 2);
REPLACE INTO spell_group_stack_rules VALUES (1124, 2);
REPLACE INTO spell_group_stack_rules VALUES (1125, 2);
REPLACE INTO spell_group_stack_rules VALUES (1126, 2);
REPLACE INTO spell_group_stack_rules VALUES (1127, 2);
REPLACE INTO spell_group_stack_rules VALUES (1128, 2);

REPLACE INTO spell_script_names VALUES (13877, "spell_rog_blade_flurry");
REPLACE INTO spell_script_names VALUES (33735, "spell_rog_blade_flurry");
REPLACE INTO spell_script_names VALUES (-11185, "spell_mage_imp_blizzard");
REPLACE INTO spell_script_names VALUES (-19572, "spell_hun_improved_mend_pet");
REPLACE INTO spell_script_names VALUES (28716, "spell_dru_dreamwalker_raiment_2");
REPLACE INTO spell_script_names VALUES (28744, "spell_dru_dreamwalker_raiment_6");
REPLACE INTO spell_script_names VALUES (37447, "spell_item_improved_mana_gems");
REPLACE INTO spell_script_names VALUES (-1130, "spell_hunt_hunters_mark");
REPLACE INTO spell_script_names VALUES (-20467, "spell_pal_judgement_of_command");
REPLACE INTO spell_script_names VALUES (32676, "spell_pri_consume_magic");


REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) values('467','Target unit has %d auras:',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) values('468','id: %d %s effmask: %d charges: %d stack: %d slot %d duration: %d maxduration: %d %s %s caster: %s guid: %d',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) values('469','Target unit has %d auras of type %d:',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) values('470','id: %d eff: %d amount: %d',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
