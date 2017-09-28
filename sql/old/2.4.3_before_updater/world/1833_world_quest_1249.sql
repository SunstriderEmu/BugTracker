-- Remove mob_eventai script and make a real SD2 script instead
DELETE FROM eventai_scripts WHERE creature_id = 4962;
UPDATE creature_template SET scriptname = "npc_tapoke_jahn", npcflag = 3 WHERE entry = 4962;
