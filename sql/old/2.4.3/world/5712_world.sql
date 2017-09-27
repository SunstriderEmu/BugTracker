/* dream fog */
update creature_template 
set speed=0.8, scale=0.8, modelid_A=10045, modelid_H=10045, ScriptName="npc_dreamfog"
where entry=15224;

/* spirit shade */
update creature_template
set ScriptName="npc_spiritshade", minhealth=1000, maxhealth=1000, speed=0.7
where entry=15261;

/* lethon */
update creature_template
set ScriptName="boss_lethon"
where entry=14888;
