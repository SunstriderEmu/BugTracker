#replace UNIT_NPC_FLAG_GUARD with CREATURE_FLAG_EXTRA_GUARD
UPDATE creature_template 
SET npcflag = npcflag & ~0x10000000, flags_extra = flags_extra |  0x01000000
WHERE npcflag & 0x10000000;

#remove unused UNIT_NPC_FLAG_OUTDOORPVP
UPDATE creature_template 
SET npcflag = npcflag & ~0x20000000
WHERE npcflag & 0x20000000;