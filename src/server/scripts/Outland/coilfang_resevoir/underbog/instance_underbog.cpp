
//"Watch out, melee DPS. On heroic these little bastards can hit you with a very strong ability called "Tentacle Lash" if you're behind them."
class spell_tentacle_lash : public SpellScript
{
    PrepareSpellScript(spell_tentacle_lash);

    void SelectTarget(WorldObject*& target)
    {
        auto AI = GetCaster()->GetAI();
        if (!AI)
            return;
        target = AI->SelectTarget(SELECT_TARGET_RANDOM, 0, [&](Unit* target) {
            return GetCaster()->IsWithinMeleeRange(target) && !GetCaster()->HasInArc(static_cast<float>(M_PI), target);
        });
    }

    void Register() override
    {
        OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_tentacle_lash::SelectTarget, EFFECT_0, TARGET_UNIT_TARGET_ENEMY);
    }
};

void AddSC_instance_underbog()
{
    RegisterSpellScript(spell_tentacle_lash);
}

