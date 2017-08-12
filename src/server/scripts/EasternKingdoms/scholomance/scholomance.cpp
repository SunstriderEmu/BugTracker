/* ScriptData
SDName: Scholomance
SD%Complete: 100
SDComment: Entrance lever...
SDCategory: Scholomance
EndScriptData */


#include "def_scholomance.h"

class ScholomanceTorch : public GameObjectScript
{
public:
    ScholomanceTorch() : GameObjectScript("go_scholo_torch")
    {}

    struct ScholomanceTorchAI : public GameObjectAI
    {
        ScholomanceTorchAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (GameObject *door = pPlayer->FindNearestGameObject(174626, 10.0f)) {
                door->UseDoorOrButton();

                return true;
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new ScholomanceTorchAI(go);
    }
};

void AddSC_scholomance() {
    new ScholomanceTorch();
}
