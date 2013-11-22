/* Dragons immune + HOMELESS flag */
# Lethon
update creature_template
set mechanic_immune_mask=653213695, ScriptName="boss_lethon", flags_extra=flags_extra + 0x00040000
where entry=14888;

#Emeriss
update creature_template
set mechanic_immune_mask=653213695, flags_extra=flags_extra + 0x00040000
where entry=14889;

#Ysondre
update creature_template
set minhealth=820000, minhealth=820000, mechanic_immune_mask=653213695, flags_extra=flags_extra + 0x00040000
where entry=14887;

#Taerar
update creature_template
set mechanic_immune_mask=653213695, flags_extra=flags_extra + 0x00040000
where entry=14890;

#Shades dies when the boss reset
update creature_template
set ScriptName="npc_spiritshade", flags_extra=flags_extra + 0x00040000
where entry=15261;

update creature_template
set ScriptName="npc_dreamfog"
where entry=15224;
