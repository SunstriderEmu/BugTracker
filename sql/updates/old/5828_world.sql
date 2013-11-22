ALTER TABLE `uptime`
   ALTER `maxplayers` 
   SET DEFAULT '0';
   
/*  "Akama Soul Retrieve Channel" & co 2 */
UPDATE spell_template SET rangeIndex = 6, effectImplicitTargetA2 = 25, effectImplicitTargetA3 = 25 WHERE id = 40902;
UPDATE spell_template SET rangeIndex = 6 WHERE id = 40927;
UPDATE spell_template SET targets = 11,rangeIndex = 6, effectImplicitTargetA1 = 38 WHERE id = 40855;
REPLACE INTO spell_script_target values (40855,1,22990);