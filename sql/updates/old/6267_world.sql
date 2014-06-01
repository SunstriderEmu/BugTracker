#KJ fight
update creature_template set flags_extra = 2 WHERE entry = 25608;
update creature_template set InhabitType = 7 where entry = 25502;

DELETE FROM spell_script_target WHERE entry = 46707;
INSERT INTO spell_script_target VALUES (46707,1,25653);

UPDATE creature_template SET ScriptName = "npc_arenabeastmaster" where entry = 26307;