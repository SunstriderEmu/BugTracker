-- Fixed chain for Blacksmithing 
DELETE FROM spell_ranks WHERE first_spell_id = 2018;
insert into `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) values('2018','2018','1');
insert into `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) values('2018','3100','2');
insert into `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) values('2018','3538','3');
insert into `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) values('2018','9785','4');
insert into `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) values('2018','29844','5');
