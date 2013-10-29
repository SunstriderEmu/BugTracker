#lacerate & devastate
replace into `spell_threat` (`entry`, `flatMod`, `pctMod`) values('20243','76','0.5');
replace into `spell_threat` (`entry`, `flatMod`, `pctMod`) values('30016','91','0.5');
replace into `spell_threat` (`entry`, `flatMod`, `pctMod`) values('30022','106','0.5');
replace into `spell_threat` (`entry`, `flatMod`, `pctMod`) values('33745','285','0.2');

alter table spell_threat drop column apPctMod;