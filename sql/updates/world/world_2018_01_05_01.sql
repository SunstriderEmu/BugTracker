-- valithria LK dummy is now a trigger
UPDATE `creature_template` SET `flags_extra`=(`flags_extra`&(~0x02) | 0x80) WHERE `entry`=16980;

UPDATE creature SET spawntimesecs = 7200 WHERE id = 15718;