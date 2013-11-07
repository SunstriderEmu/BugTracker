/* Changed supremus flamme invocation duration */
UPDATE spell_template SET durationIndex = 18 WHERE id = 40126;
/* Volcano eruption visual correct duration */
UPDATE spell_template SET durationIndex = 18 WHERE id = 40117;

/* New NonName Trigger creature (used for door opening emote on Najentus for now)*/
REPLACE INTO creature_template (entry,modelid_A,NAME,subname,faction_A,faction_H,flags_extra) 
VALUES (30000,892,"","NoName Trigger",35,35,128);
/* Set emote to text emote */
UPDATE script_texts SET type = 2 WHERE entry = '-1563999'; 