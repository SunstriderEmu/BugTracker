/* mutan war hound (23232) script */
update creature_template
set AIName="SmartAI", ScriptName=""
where entry=23232;

replace into smart_scripts(entryorguid,source_type,event_type,action_type,action_param1,action_param2,target_type,event_flags,event_chance,comment)
values (23232, 0, 6, 11, 41193, 2, 1, 1, 100, "Cast cloud of diseases uppon dying");