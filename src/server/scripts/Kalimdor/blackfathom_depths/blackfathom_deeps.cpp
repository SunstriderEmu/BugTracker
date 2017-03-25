#include "def_blackfathom_deeps.h"

enum Spells
{
    SPELL_BLESSING_OF_BLACKFATHOM                          = 8733
};

class BlackFathomAltar : public GameObjectScript
{
public:
    BlackFathomAltar() : GameObjectScript("go_blackfathom_altar")
    {}

    bool OnGossipHello(Player* p, GameObject* go) override
    {
        if (!p->HasAuraEffect(SPELL_BLESSING_OF_BLACKFATHOM))
            p->AddAura(SPELL_BLESSING_OF_BLACKFATHOM, p);
        return true;
    }
};

class BlackFathomFire : public GameObjectScript
{
public:
    BlackFathomFire() : GameObjectScript("go_blackfathom_fire")
    {}

    bool OnGossipHello(Player* p, GameObject* go) override
    {
        InstanceScript* pInstance = ((InstanceScript*)go->GetInstanceScript());

        if (pInstance)
        {
            go->UseDoorOrButton();
            go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
            switch (go->GetEntry()) {
            case 21118: // North West
                for (uint8 i = 0; i < 4; i++) {
                    if (Creature* summon = p->SummonCreature(4825, -769.013123, -153.537262, -25.879938, 3.121223, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000))
                        summon->AI()->AttackStart(p);
                }
                break;
            case 21119: // North East
                for (uint8 i = 0; i < 4; i++) {
                    if (Creature* summon = p->SummonCreature(4823, -768.617126, -174.640518, -25.870447, 2.980356, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000))
                        summon->AI()->AttackStart(p);
                }
                break;
            case 21120: // South East
                for (uint8 i = 0; i < 2; i++) {
                    if (Creature* summon = p->SummonCreature(4978, -868.376831, -174.436081, -25.870043, 0.109292, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000))
                        summon->AI()->AttackStart(p);
                }
                break;
            case 21121: // South West
                for (uint8 i = 0; i < 8; i++) {
                    if (Creature* summon = p->SummonCreature(4977, -868.235535, -153.906906, -25.881172, 6.167040, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000))
                        summon->AI()->AttackStart(p);
                }
                break;
            }
            pInstance->SetData(DATA_FIRE, pInstance->GetData(DATA_FIRE) + 1);
            return true;
        }
        return false;
    }
};


void AddSC_blackfathom_deeps()
{
    new BlackFathomAltar();
    new BlackFathomFire();
}
