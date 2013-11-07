/* New Aura duel area spell - update radius to 100m*/
update `spell_template` set effectRadiusIndex1 = '12' where id = '53086';

/* New mob tu use this aura */
insert into `smart_scripts` values('91535','0','0','0','37','0','100','0','0','0','0','0','11','53086','6','0','0','0','0','1','0','0','0','0','0','0','0','Duel Area - Apply aura at init');
insert into `creature_template` values('91535','0','18783','0','18783','0','Zone de duel','Portée de 100m',NULL,'1','1','5000','5000','0','0','0','21','21','0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','SmartAI','0','3','0','1','0','0','130','','0');