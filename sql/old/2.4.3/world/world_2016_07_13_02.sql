REPLACE INTO spell_script_names VALUES (33393, "spell_summon_infernals");
REPLACE INTO spell_script_names VALUES (32148, "spell_infernal_missile");

UPDATE creature_template SET AIName = "", ScriptName = "dark_portal_event_fel_soldier" WHERE entry = 18944;
UPDATE creature_template SET AIName = "",  ScriptName = "dark_portal_event_wrath_master" WHERE entry = 19005;
UPDATE creature_template SET AIName = "", ScriptName = "dark_portal_event_pit_lord" WHERE entry = 18945;
#infernal relay as trigger
UPDATE creature_template SET flags_extra = 130, InhabitType = 7 WHERE entry = 19215;

#incorrect path for Melgromm Highmountain
UPDATE creature_template_addon SET path_id = 0 WHERE entry = 18969;
#magma flow totem (Melgromm Highmountain)
UPDATE creature_template SET spell1 = 33561 WHERE entry = 19222;
#Strength of the Storm Totem
UPDATE creature_template SET spell1 = 33571 WHERE entry = 19225;
