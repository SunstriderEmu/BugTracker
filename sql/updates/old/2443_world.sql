DELETE FROM script_texts WHERE entry BETWEEN -1000506 AND -1000500;
INSERT INTO script_texts (entry,content_default,content_loc2,sound,type,language,emote,comment) VALUES
(-1000500,'Help! Please, You must help me!','A l''aide ! Vous devez m''aider !',0,0,0,0,'Galen - periodic say'),
(-1000501,'Let us leave this place.','Quittons cet endroit.',0,0,0,0,'Galen - quest accepted'),
(-1000502,'Look out! The $c attacks!','Regardez ! Le $c m''attaque !',0,0,0,0,'Galen - aggro 1'),
(-1000503,'Help! I\'m under attack!','A l''aide ! Je suis attaqué !',0,0,0,0,'Galen - aggro 2'),
(-1000504,'Thank you $N. I will remember you always. You can find my strongbox in my camp, north of Stonard.','Merci $N. Je me rappellerai toujours de vous. Vous pouvez trouver mon coffre-fort à mon camp, au nord de Stonard.',0,0,0,0,'Galen - quest complete'),
(-1000505,'%s whispers to $N the secret to opening his strongbox.','%s chuchote à $N le secret pour ouvrir son coffre-fort.',0,2,0,0,'Galen - emote whisper'),
(-1000506,'%s disappears into the swamp.','%s disparaît dans le marais.',0,2,0,0,'Galen - emote disapper');

DELETE FROM escort_waypoints WHERE entry=5391;
INSERT INTO escort_waypoints VALUES
(5391, 0, -9901.12, -3727.29, 22.11, 3000, ''),
(5391, 1, -9909.27, -3727.81, 23.25, 0, ''),
(5391, 2, -9935.25, -3729.02, 22.11, 0, ''),
(5391, 3, -9945.83, -3719.34, 21.68, 0, ''),
(5391, 4, -9963.41, -3710.18, 21.71, 0, ''),
(5391, 5, -9972.75, -3690.13, 21.68, 0, ''),
(5391, 6, -9989.70, -3669.67, 21.67, 0, ''),
(5391, 7, -9989.21, -3647.76, 23.00, 0, ''),
(5391, 8, -9992.27, -3633.74, 21.67, 0, ''),
(5391, 9,-10002.32, -3611.67, 22.26, 0, ''),
(5391,10, -9999.25, -3586.33, 21.85, 0, ''),
(5391,11,-10006.53, -3571.99, 21.67, 0, ''),
(5391,12,-10014.30, -3545.24, 21.67, 0, ''),
(5391,13,-10018.91, -3525.03, 21.68, 0, ''),
(5391,14,-10030.22, -3514.77, 21.67, 0, ''),
(5391,15,-10045.11, -3501.49, 21.67, 0, ''),
(5391,16,-10052.91, -3479.13, 21.67, 0, ''),
(5391,17,-10060.68, -3460.31, 21.67, 0, ''),
(5391,18,-10074.68, -3436.85, 20.97, 0, ''),
(5391,19,-10074.68, -3436.85, 20.97, 0, ''),
(5391,20,-10072.86, -3408.92, 20.43, 15000, ''),
(5391,21,-10108.01, -3406.05, 22.06, 0, '');

UPDATE creature_template SET ScriptName='npc_galen_goodward' WHERE entry=5391;
