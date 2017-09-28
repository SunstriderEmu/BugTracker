UPDATE creature_template ct
JOIN creature_scripts cs ON ct.entry = cs.entryorguid
SET ct.ScriptName = cs.scriptname

DROP table creature_scripts;