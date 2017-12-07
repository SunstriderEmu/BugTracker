-- Added some armor for escort npcs with none
UPDATE creature_template SET ArmorModifier = 1 WHERE entry IN (3439,3465,1978,11856,2917,16993,17312,17982,20415,16295,18209);