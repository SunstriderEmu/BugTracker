/* Brightscale Wyrm (24761) script */
update creature_template
set AIName="SmartAI", ScriptName=""
where entry=24761;

insert into smart_scripts(entryorguid,source_type,event_type,action_type,action_param1,action_param2,target_type,event_flags,event_chance,comment)
values (24761, 0, 6, 11, 44406, 2, 1, 1, 100, "Cast energy Infusion on nearby players uppon dying");
delete from eventai_scripts where creature_id = 24761;