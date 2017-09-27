ALTER TABLE waypoint_data
	ADD COLUMN orientation FLOAT NOT NULL DEFAULT 0.0 AFTER position_z;
	
REPLACE INTO smart_scripts VALUES (25001,0,2,0,11,0,100,0,0,0,0,0,11,45227,0,0,0,0,0,1,0,0,0,0,0,0,0,'Abyssal Flamewalker - On spawn - Cast Abyssal Meteor Fall');

REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) values('1139','   Follow player %s (lowguid %u)',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) values('1140','   Follow creature %s (lowguid %u)',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) values('1141','   Follow <NULL>',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) values('1142','   Effect movement',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);

DROP TABLE IF EXISTS `pack58`;

CREATE TABLE `pack58` (
  `class` smallint(5) unsigned NOT NULL,
  `type` smallint(5) unsigned NOT NULL COMMENT 'melee/heal/tank/magic',
  `item` mediumint(8) unsigned NOT NULL COMMENT 'item id',
  PRIMARY KEY (`class`,`type`,`item`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


#Prêtre (Spécialisation heal)

REPLACE INTO pack58 VALUES (5,1,16693);
REPLACE INTO pack58 VALUES (5,1,16695);
REPLACE INTO pack58 VALUES (5,1,16690);
REPLACE INTO pack58 VALUES (5,1,16696);
REPLACE INTO pack58 VALUES (5,1,16694);
REPLACE INTO pack58 VALUES (5,1,16691);
REPLACE INTO pack58 VALUES (5,1,16697);
REPLACE INTO pack58 VALUES (5,1,16692);
REPLACE INTO pack58 VALUES (5,1,22327);
REPLACE INTO pack58 VALUES (5,1,19530);
REPLACE INTO pack58 VALUES (5,1,22334);
REPLACE INTO pack58 VALUES (5,1,13392);
REPLACE INTO pack58 VALUES (5,1,18469);
REPLACE INTO pack58 VALUES (5,1,11819);
REPLACE INTO pack58 VALUES (5,1,22254);
REPLACE INTO pack58 VALUES (5,1,22394);

#Prêtre (Spécialisation Ombre)

REPLACE INTO pack58 VALUES (5,3,16686);
REPLACE INTO pack58 VALUES (5,3,16689);
REPLACE INTO pack58 VALUES (5,3,16688);
REPLACE INTO pack58 VALUES (5,3,16685);
REPLACE INTO pack58 VALUES (5,3,16687);
REPLACE INTO pack58 VALUES (5,3,16682);
REPLACE INTO pack58 VALUES (5,3,16683);
REPLACE INTO pack58 VALUES (5,3,16684);
REPLACE INTO pack58 VALUES (5,3,18691);
REPLACE INTO pack58 VALUES (5,3,12968);
REPLACE INTO pack58 VALUES (5,3,12926);
REPLACE INTO pack58 VALUES (5,3,22339);
REPLACE INTO pack58 VALUES (5,3,12930);
REPLACE INTO pack58 VALUES (5,3,11832);
REPLACE INTO pack58 VALUES (5,3,13396);
REPLACE INTO pack58 VALUES (5,3,22335);

#Demo

REPLACE INTO pack58 VALUES (9,3,16698);
REPLACE INTO pack58 VALUES (9,3,16701);
REPLACE INTO pack58 VALUES (9,3,16700);
REPLACE INTO pack58 VALUES (9,3,16702);
REPLACE INTO pack58 VALUES (9,3,16699);
REPLACE INTO pack58 VALUES (9,3,16704);
REPLACE INTO pack58 VALUES (9,3,16703);
REPLACE INTO pack58 VALUES (9,3,16705);
REPLACE INTO pack58 VALUES (9,3,10829);
REPLACE INTO pack58 VALUES (9,3,12967);
REPLACE INTO pack58 VALUES (9,3,12926);
REPLACE INTO pack58 VALUES (9,3,22433);
REPLACE INTO pack58 VALUES (9,3,18467);
REPLACE INTO pack58 VALUES (9,3,11832);
REPLACE INTO pack58 VALUES (9,3,13938);
REPLACE INTO pack58 VALUES (9,3,22335);

#Mage

REPLACE INTO pack58 VALUES (8,3,16686);
REPLACE INTO pack58 VALUES (8,3,16689);
REPLACE INTO pack58 VALUES (8,3,16688);
REPLACE INTO pack58 VALUES (8,3,16685);
REPLACE INTO pack58 VALUES (8,3,16687);
REPLACE INTO pack58 VALUES (8,3,16682);
REPLACE INTO pack58 VALUES (8,3,16683);
REPLACE INTO pack58 VALUES (8,3,16684);
REPLACE INTO pack58 VALUES (8,3,10829);
REPLACE INTO pack58 VALUES (8,3,12967);
REPLACE INTO pack58 VALUES (8,3,12926);
REPLACE INTO pack58 VALUES (8,3,22433);
REPLACE INTO pack58 VALUES (8,3,12930);
REPLACE INTO pack58 VALUES (8,3,11832);
REPLACE INTO pack58 VALUES (8,3,13938);
REPLACE INTO pack58 VALUES (8,3,22335);

#Chasseur

REPLACE INTO pack58 VALUES (3,0,16677);
REPLACE INTO pack58 VALUES (3,0,16679);
REPLACE INTO pack58 VALUES (3,0,16674);
REPLACE INTO pack58 VALUES (3,0,16680);
REPLACE INTO pack58 VALUES (3,0,16678);
REPLACE INTO pack58 VALUES (3,0,16675);
REPLACE INTO pack58 VALUES (3,0,16681);
REPLACE INTO pack58 VALUES (3,0,16676);
REPLACE INTO pack58 VALUES (3,0,11933);
REPLACE INTO pack58 VALUES (3,0,13340);
REPLACE INTO pack58 VALUES (3,0,18701);
REPLACE INTO pack58 VALUES (3,0,13098);
REPLACE INTO pack58 VALUES (3,0,18473);
REPLACE INTO pack58 VALUES (3,0,19991);
REPLACE INTO pack58 VALUES (3,0,22314);
REPLACE INTO pack58 VALUES (3,0,18680);

#Druidequi

REPLACE INTO pack58 VALUES (11,3,16720);
REPLACE INTO pack58 VALUES (11,3,16718);
REPLACE INTO pack58 VALUES (11,3,16706);
REPLACE INTO pack58 VALUES (11,3,16716);
REPLACE INTO pack58 VALUES (11,3,16719);
REPLACE INTO pack58 VALUES (11,3,16715);
REPLACE INTO pack58 VALUES (11,3,16714);
REPLACE INTO pack58 VALUES (11,3,16717);
REPLACE INTO pack58 VALUES (11,3,18289);
REPLACE INTO pack58 VALUES (11,3,12967);
REPLACE INTO pack58 VALUES (11,3,12926);
REPLACE INTO pack58 VALUES (11,3,22433);
REPLACE INTO pack58 VALUES (11,3,12930);
REPLACE INTO pack58 VALUES (11,3,11832);
REPLACE INTO pack58 VALUES (11,3,22335);

#Druidheal

REPLACE INTO pack58 VALUES (11,1,16720);
REPLACE INTO pack58 VALUES (11,1,16718);
REPLACE INTO pack58 VALUES (11,1,16706);
REPLACE INTO pack58 VALUES (11,1,16716);
REPLACE INTO pack58 VALUES (11,1,16719);
REPLACE INTO pack58 VALUES (11,1,16715);
REPLACE INTO pack58 VALUES (11,1,16714);
REPLACE INTO pack58 VALUES (11,1,16717);
REPLACE INTO pack58 VALUES (11,1,22327);
REPLACE INTO pack58 VALUES (11,1,19530);
REPLACE INTO pack58 VALUES (11,1,22334);
REPLACE INTO pack58 VALUES (11,1,13392);
REPLACE INTO pack58 VALUES (11,1,18470);
REPLACE INTO pack58 VALUES (11,1,11819);
REPLACE INTO pack58 VALUES (11,1,22398);
REPLACE INTO pack58 VALUES (11,1,22394);

#druidchat

REPLACE INTO pack58 VALUES (11,0,16707);
REPLACE INTO pack58 VALUES (11,0,16708);
REPLACE INTO pack58 VALUES (11,0,16721);
REPLACE INTO pack58 VALUES (11,0,16713);
REPLACE INTO pack58 VALUES (11,0,16709);
REPLACE INTO pack58 VALUES (11,0,16711);
REPLACE INTO pack58 VALUES (11,0,16710);
REPLACE INTO pack58 VALUES (11,0,16712);
REPLACE INTO pack58 VALUES (11,0,22340);
REPLACE INTO pack58 VALUES (11,0,13340);
REPLACE INTO pack58 VALUES (11,0,18701);
REPLACE INTO pack58 VALUES (11,0,18500);
REPLACE INTO pack58 VALUES (11,0,22321);
REPLACE INTO pack58 VALUES (11,0,11815);
REPLACE INTO pack58 VALUES (11,0,22397);
REPLACE INTO pack58 VALUES (11,0,13047);

#Wartank

REPLACE INTO pack58 VALUES (1,2,12952);
REPLACE INTO pack58 VALUES (1,2,13955);
REPLACE INTO pack58 VALUES (1,2,18503);
REPLACE INTO pack58 VALUES (1,2,19051);
REPLACE INTO pack58 VALUES (1,2,18690);
REPLACE INTO pack58 VALUES (1,2,18521);
REPLACE INTO pack58 VALUES (1,2,18754);
REPLACE INTO pack58 VALUES (1,2,18383);
REPLACE INTO pack58 VALUES (1,2,12229);
REPLACE INTO pack58 VALUES (1,2,18689);
REPLACE INTO pack58 VALUES (1,2,22331);
REPLACE INTO pack58 VALUES (1,2,11669);
REPLACE INTO pack58 VALUES (1,2,18466);
REPLACE INTO pack58 VALUES (1,2,11810);
REPLACE INTO pack58 VALUES (1,2,12939);
REPLACE INTO pack58 VALUES (1,2,12602);
REPLACE INTO pack58 VALUES (1,2,13380);

#Warmelee

REPLACE INTO pack58 VALUES (1,0,16731);
REPLACE INTO pack58 VALUES (1,0,16733);
REPLACE INTO pack58 VALUES (1,0,16730);
REPLACE INTO pack58 VALUES (1,0,16736);
REPLACE INTO pack58 VALUES (1,0,16732);
REPLACE INTO pack58 VALUES (1,0,16734);
REPLACE INTO pack58 VALUES (1,0,16735);
REPLACE INTO pack58 VALUES (1,0,16737);
REPLACE INTO pack58 VALUES (1,0,11933);
REPLACE INTO pack58 VALUES (1,0,22337);
REPLACE INTO pack58 VALUES (1,0,13098);
REPLACE INTO pack58 VALUES (1,0,13373);
REPLACE INTO pack58 VALUES (1,0,22321);
REPLACE INTO pack58 VALUES (1,0,11815);
REPLACE INTO pack58 VALUES (1,0,13361);
REPLACE INTO pack58 VALUES (1,0,13361);
REPLACE INTO pack58 VALUES (1,0,12653);

#palatank

REPLACE INTO pack58 VALUES (2,2,18718);
REPLACE INTO pack58 VALUES (2,2,18384);
REPLACE INTO pack58 VALUES (2,2,14624);
REPLACE INTO pack58 VALUES (2,2,14620);
REPLACE INTO pack58 VALUES (2,2,14623);
REPLACE INTO pack58 VALUES (2,2,14621);
REPLACE INTO pack58 VALUES (2,2,18754);
REPLACE INTO pack58 VALUES (2,2,14622);
REPLACE INTO pack58 VALUES (2,2,13091);
REPLACE INTO pack58 VALUES (2,2,18689);
REPLACE INTO pack58 VALUES (2,2,11669);
REPLACE INTO pack58 VALUES (2,2,21753);
REPLACE INTO pack58 VALUES (2,2,18472);
REPLACE INTO pack58 VALUES (2,2,11810);
REPLACE INTO pack58 VALUES (2,2,22400);
REPLACE INTO pack58 VALUES (2,2,18048);
REPLACE INTO pack58 VALUES (2,2,22336);

#palaheal

REPLACE INTO pack58 VALUES (2,1,16727);
REPLACE INTO pack58 VALUES (2,1,16729);
REPLACE INTO pack58 VALUES (2,1,16726);
REPLACE INTO pack58 VALUES (2,1,16723);
REPLACE INTO pack58 VALUES (2,1,16728);
REPLACE INTO pack58 VALUES (2,1,16725);
REPLACE INTO pack58 VALUES (2,1,16722);
REPLACE INTO pack58 VALUES (2,1,16724);
REPLACE INTO pack58 VALUES (2,1,22327);
REPLACE INTO pack58 VALUES (2,1,19530);
REPLACE INTO pack58 VALUES (2,1,22334);
REPLACE INTO pack58 VALUES (2,1,13178);
REPLACE INTO pack58 VALUES (2,1,18472);
REPLACE INTO pack58 VALUES (2,1,11819);
REPLACE INTO pack58 VALUES (2,1,23201);
REPLACE INTO pack58 VALUES (2,1,11923);
REPLACE INTO pack58 VALUES (2,1,22336);

#paladps

REPLACE INTO pack58 VALUES (2,0,16731);
REPLACE INTO pack58 VALUES (2,0,16733);
REPLACE INTO pack58 VALUES (2,0,16730);
REPLACE INTO pack58 VALUES (2,0,16736);
REPLACE INTO pack58 VALUES (2,0,16732);
REPLACE INTO pack58 VALUES (2,0,16734);
REPLACE INTO pack58 VALUES (2,0,16735);
REPLACE INTO pack58 VALUES (2,0,16737);
REPLACE INTO pack58 VALUES (2,0,11933);
REPLACE INTO pack58 VALUES (2,0,13203);
REPLACE INTO pack58 VALUES (2,0,13098);
REPLACE INTO pack58 VALUES (2,0,13373);
REPLACE INTO pack58 VALUES (2,0,22321);
REPLACE INTO pack58 VALUES (2,0,11815);
REPLACE INTO pack58 VALUES (2,0,22401);
REPLACE INTO pack58 VALUES (2,0,12583);

#voleur

REPLACE INTO pack58 VALUES (4,0,16707);
REPLACE INTO pack58 VALUES (4,0,16708);
REPLACE INTO pack58 VALUES (4,0,16721);
REPLACE INTO pack58 VALUES (4,0,16713);
REPLACE INTO pack58 VALUES (4,0,16709);
REPLACE INTO pack58 VALUES (4,0,16711);
REPLACE INTO pack58 VALUES (4,0,16710);
REPLACE INTO pack58 VALUES (4,0,16712);
REPLACE INTO pack58 VALUES (4,0,22340);
REPLACE INTO pack58 VALUES (4,0,13340);
REPLACE INTO pack58 VALUES (4,0,18701);
REPLACE INTO pack58 VALUES (4,0,18500);
REPLACE INTO pack58 VALUES (4,0,22321);
REPLACE INTO pack58 VALUES (4,0,11815);
REPLACE INTO pack58 VALUES (4,0,13361);
REPLACE INTO pack58 VALUES (4,0,13953);
REPLACE INTO pack58 VALUES (4,0,28972);

#chamheal

REPLACE INTO pack58 VALUES (7,1,16667);
REPLACE INTO pack58 VALUES (7,1,16669);
REPLACE INTO pack58 VALUES (7,1,16666);
REPLACE INTO pack58 VALUES (7,1,16673);
REPLACE INTO pack58 VALUES (7,1,16668);
REPLACE INTO pack58 VALUES (7,1,16670);
REPLACE INTO pack58 VALUES (7,1,16671);
REPLACE INTO pack58 VALUES (7,1,16672);
REPLACE INTO pack58 VALUES (7,1,22327);
REPLACE INTO pack58 VALUES (7,1,19530);
REPLACE INTO pack58 VALUES (7,1,22334);
REPLACE INTO pack58 VALUES (7,1,13178);
REPLACE INTO pack58 VALUES (7,1,22268);
REPLACE INTO pack58 VALUES (7,1,11819);
REPLACE INTO pack58 VALUES (7,1,23200);
REPLACE INTO pack58 VALUES (7,1,11923);
REPLACE INTO pack58 VALUES (7,1,22336);

#chamelem

REPLACE INTO pack58 VALUES (7,3,16667);
REPLACE INTO pack58 VALUES (7,3,16669);
REPLACE INTO pack58 VALUES (7,3,16666);
REPLACE INTO pack58 VALUES (7,3,16673);
REPLACE INTO pack58 VALUES (7,3,16668);
REPLACE INTO pack58 VALUES (7,3,16670);
REPLACE INTO pack58 VALUES (7,3,16671);
REPLACE INTO pack58 VALUES (7,3,16672);
REPLACE INTO pack58 VALUES (7,3,10829);
REPLACE INTO pack58 VALUES (7,3,12967);
REPLACE INTO pack58 VALUES (7,3,12926);
REPLACE INTO pack58 VALUES (7,3,22433);
REPLACE INTO pack58 VALUES (7,3,12930);
REPLACE INTO pack58 VALUES (7,3,18471);
REPLACE INTO pack58 VALUES (7,3,22395);
REPLACE INTO pack58 VALUES (7,3,13964);
REPLACE INTO pack58 VALUES (7,3,22336);

#chamelio

REPLACE INTO pack58 VALUES (7,0,16677);
REPLACE INTO pack58 VALUES (7,0,16679);
REPLACE INTO pack58 VALUES (7,0,16674);
REPLACE INTO pack58 VALUES (7,0,16680);
REPLACE INTO pack58 VALUES (7,0,16678);
REPLACE INTO pack58 VALUES (7,0,16675);
REPLACE INTO pack58 VALUES (7,0,16681);
REPLACE INTO pack58 VALUES (7,0,16676);
REPLACE INTO pack58 VALUES (7,0,11933);
REPLACE INTO pack58 VALUES (7,0,13203);
REPLACE INTO pack58 VALUES (7,0,13098);
REPLACE INTO pack58 VALUES (7,0,13373);
REPLACE INTO pack58 VALUES (7,0,22321);
REPLACE INTO pack58 VALUES (7,0,11815);
REPLACE INTO pack58 VALUES (7,0,22395);
REPLACE INTO pack58 VALUES (7,0,12621);
REPLACE INTO pack58 VALUES (7,0,12621);

UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '397';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '6721';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '6722';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '7463';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8316';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8376';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8377';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8378';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8379';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8380';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8381';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8382';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8559';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8596';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8544';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8557';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8556';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8558';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8560';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8561';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8562';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8621';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8623';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8626';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8634';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8637';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8592';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8593';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8594';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8655';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8660';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8661';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8602';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8603';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8665';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8622';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8624';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8625';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8627';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8628';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8629';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8689';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8692';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8693';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8630';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8631';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8632';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8633';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8638';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8694';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8695';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8696';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8639';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8640';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8641';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8656';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8657';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8658';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8659';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8662';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8663';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8664';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8690';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8666';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8691';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8667';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8668';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8669';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8697';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8698';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8699';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8700';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8701';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8702';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8703';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8704';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8705';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8706';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8707';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8708';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8709';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8710';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8711';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8712';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8926';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8927';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8905';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8906';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8931';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8932';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8933';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8934';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8935';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8907';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8908';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8909';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8910';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8911';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8936';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8937';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8938';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8939';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8912';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8913';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8914';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8915';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8940';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8941';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8942';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8943';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8944';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8916';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8917';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8918';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8919';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8920';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8999';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '8951';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '8952';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9000';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9001';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '9002';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9003';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '9004';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9005';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9006';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '8953';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '8954';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '8955';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '8956';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '8957';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9007';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9008';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9009';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '9010';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '8958';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '8959';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '9011';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9012';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9013';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9014';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9034';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9036';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9037';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9038';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9039';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9040';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9016';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9041';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9042';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '9043';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9017';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9018';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9019';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '9020';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9021';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '9044';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '9045';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '9046';
UPDATE quest_template SET SkillOrClass = '-1' WHERE entry = '9022';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '9047';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '9048';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '9049';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '9050';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9086';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9087';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9054';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9055';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9056';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9057';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9088';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9089';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9090';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9091';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9092';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9058';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9059';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9060';
UPDATE quest_template SET SkillOrClass = '-4' WHERE entry = '9061';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9093';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9116';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '9068';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '9069';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '9070';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '9071';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '9072';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '9073';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '9074';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '9075';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '9077';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '9079';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '9080';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '9081';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '9082';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '9083';
UPDATE quest_template SET SkillOrClass = '-8' WHERE entry = '9084';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9095';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9096';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9097';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9098';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9099';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9100';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9101';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9102';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9103';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9104';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9105';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9106';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9107';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9108';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9109';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9110';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9111';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9112';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9113';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9114';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9115';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9117';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9118';
UPDATE quest_template SET SkillOrClass = '-16' WHERE entry = '9257';
UPDATE quest_template SET SkillOrClass = '-1024' WHERE entry = '9269';
UPDATE quest_template SET SkillOrClass = '-128' WHERE entry = '9270';
UPDATE quest_template SET SkillOrClass = '-256' WHERE entry = '9271';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '10494';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '10495';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '10496';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '10497';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '10498';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '10499';
UPDATE quest_template SET SkillOrClass = '-64' WHERE entry = '10492';
UPDATE quest_template SET SkillOrClass = '-2' WHERE entry = '10493';
UPDATE quest_template SET SkillOrClass = '-1106' WHERE entry = '80008';
UPDATE quest_template SET SkillOrClass = '-1106' WHERE entry = '80009';
UPDATE quest_template SET SkillOrClass = '-1103' WHERE entry = '80010';
UPDATE quest_template SET SkillOrClass = '-1103' WHERE entry = '80011';
UPDATE quest_template SET SkillOrClass = '-3' WHERE entry = '80012';
UPDATE quest_template SET SkillOrClass = '-3' WHERE entry = '80013';
UPDATE quest_template SET SkillOrClass = '-1424' WHERE entry = '80014';
UPDATE quest_template SET SkillOrClass = '-1424' WHERE entry = '80015';