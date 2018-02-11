-- Fixed not first rank in spell proc for lifetap
UPDATE spell_proc SET SpellId = -15270 WHERE SpellId = -15337;
-- mana shield proc (Incanter's Regalia set)
replace into `spell_proc` (`SpellId`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask`, `ProcFlags`, `SpellTypeMask`, `SpellPhaseMask`, `HitMask`, `AttributesMask`, `ProcsPerMinute`, `Chance`, `Cooldown`, `Charges`) values('-1463','0','3','0','0','1','0','1024','0','0','0','0','0');

UPDATE spell_proc SET SpellPhaseMask = 0 WHERE SpellId = 15286;
UPDATE spell_proc SET SpellId = -SpellId WHERE SpellId = -6984;
UPDATE spell_proc SET SpellPhaseMask = 0 WHERE SpellId = 45054;
UPDATE spell_proc SET SpellTypeMask = 0, SpellPhaseMask = 0 WHERE SpellId = 37424;
UPDATE spell_proc SET SpellTypeMask = 0, SpellPhaseMask = 0 WHERE SpellId = -15270;

REPLACE INTO spell_ranks VALUES (27243, 27243, 1), (41635, 41635, 1), (33076, 33076, 1), (30482, 30482, 1);
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('30701','30701','1');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('30701','30702','2');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('30701','30703','3');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('30701','30704','4');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('30701','30705','5');

REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('16257','16257','1');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('16257','16277','2');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('16257','16278','3');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('16257','16279','4');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('16257','16280','5');

REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('12966','12966','1');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('12966','12967','2');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('12966','12968','3');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('12966','12969','4');
REPLACE INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES ('12966','12970','5');

-- not first rank
DELETE FROM spell_proc WHERE SpellId IN (25469,25472);
-- not on BC
DELETE FROM spell_proc WHERE SpellId IN (-7001);
UPDATE spell_proc SET HitMask = 0 WHERE SpellId = -15270;
UPDATE spell_proc SET charges = 0 WHERE SpellId = 34477;

-- no existing aura
UPDATE creature_template_addon SET auras = "12550" WHERE entry = 17160;

-- already existing under "spell_hun_entrapment"
DELETE FROM spell_script_names WHERE ScriptName = "spell_hunt_entrapment";
-- handled via spell_template_override
DELETE FROM spell_script_names WHERE ScriptName = "spell_pal_judgement_regen";

DELETE FROM spell_script_names WHERE spell_id IN (20577, 31968, 32865, 41635);
