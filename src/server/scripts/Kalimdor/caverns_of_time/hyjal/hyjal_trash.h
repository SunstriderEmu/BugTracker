
#ifndef SC_HYJAL_TRASH_AI_H
#define SC_HYJAL_TRASH_AI_H

#include "def_hyjal.h"
#include "EscortAI.h"

#define MINRAIDDAMAGE  700000//minimal damage before trash can drop loot and reputation, resets if faction leader dies

struct hyjal_trashAI : public EscortAI
{
    hyjal_trashAI(Creature *c);

    void Reset() override;

    //void EnterEvadeMode();

    void JustEngagedWith(Unit *who) override;

    void UpdateAI(const uint32 diff) override;

    void MovementInform(uint32 MovementType, uint32 Data) override;

    void JustDied(Unit* /*killer*/) override;

    void DamageTaken(Unit *done_by, uint32 &damage) override;

    public:
        InstanceScript* pInstance;
        bool IsEvent;
        uint32 Delay;
        uint32 LastOverronPos;
        bool IsOverrun;
        bool SetupOverrun;
        uint32 OverrunType;
        uint8 faction;
        bool useFlyPath;
        uint32 damageTaken;
        float DummyTarget[3];
        bool cannibalism;

    //private:
};
#endif
