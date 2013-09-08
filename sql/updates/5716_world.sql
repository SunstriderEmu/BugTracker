/* Searing Whelp (4324) script */
update creature_template
set ScriptName="npc_searingwhelp", mindmg=30, maxdmg=50
where entry=4324;

update spell_template
set effectBasePoints1=10, castingTimeIndex=16
where id=11021;