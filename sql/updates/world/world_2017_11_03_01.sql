# Spell 41381 listed in `spell_proc_event` probably not triggered spell
UPDATE spell_proc_event SET procFlags = 139264 WHERE entry = 41381;

# Table `spell_scripts` has unsupported spell (Id: 37867) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 37892) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 37894) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 38002) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 38053) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 38055) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 38120) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 38122) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 38125) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 38127) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 38129) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
# Table `spell_scripts` has unsupported spell (Id: 38173) without SPELL_EFFECT_SCRIPT_EFFECT (77) spell effect
DELETE FROM spell_scripts WHERE id IN (37867,37892,37894,38002,38053,38055,38120,38122,38125,38127,38129,38173);