
/* ScriptData
SDName: Hyjal
SD%Complete: 80
SDComment: 
SDCategory: Caverns of Time, Mount Hyjal
EndScriptData */

/* ContentData
npc_jaina_proudmoore
npc_thrall
npc_tyrande_whisperwind
EndContentData */


#include "hyjalAI.h"

#define GOSSIP_MENU_BEGIN_ALLY      403
#define GOSSIP_ITEM_BEGIN_ALLY      395 // "My companions and I are with you, Lady Proudmoore."
#define GOSSIP_MENU_BEGIN_ALLY_2    404
#define GOSSIP_MENU_ANATHERON       405
#define GOSSIP_ITEM_ANETHERON       396 // "We are ready for whatever Archimonde might send our way, Lady Proudmoore."
#define GOSSIP_MENU_ANATHERON2      406
#define GOSSIP_MENU_RETREAT_ALLY    407
#define GOSSIP_ITEM_RETREAT_ALLY    399 // "Until we meet again, Lady Proudmoore."

#define GOSSIP_MENU_BEGIN_HORDE     408
#define GOSSIP_ITEM_BEGIN_HORDE     397 // "I am with you, Thrall."
#define GOSSIP_MENU_BEGIN_HORDE2    409
#define GOSSIP_MENU_AZGALOR         410
#define GOSSIP_ITEM_AZGALOR         398 // "We have nothing to fear."
#define GOSSIP_MENU_AZGALOR2        411
#define GOSSIP_MENU_RETREAT_HORDE   412
#define GOSSIP_ITEM_RETREAT_HORDE   402 // "Until we meet again, Thrall."

#define GOSSIP_MENU_TYRANDE         413
#define GOSSIP_ITEM_TYRANDE         400 // "I would be grateful for any aid you can provide, Priestess."
#define GOSSIP_MENU_TYRANDE2        414
#define ITEM_TEAR_OF_GODDESS        24494

class npc_jaina_proudmoore : public CreatureScript
{
public:
    npc_jaina_proudmoore() : CreatureScript("npc_jaina_proudmoore")
    { }

    class npc_jaina_proudmooreAI : public hyjalAI
    {
    public:
        npc_jaina_proudmooreAI(Creature *c) : hyjalAI(c)
        {}

        bool GossipHello(Player *player) override
        {
            if (EventBegun)
                return false;

            uint32 RageEncounter = GetInstanceScript(DATA_RAGEWINTERCHILLEVENT);
            uint32 AnetheronEncounter = GetInstanceScript(DATA_ANETHERONEVENT);

            if (player->IsGameMaster()) {
                player->ADD_GOSSIP_ITEM(2, "[GM] Toggle Debug Timers", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spawn Archimonde", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            }

            if (RageEncounter == NOT_STARTED)
            {
                player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_BEGIN_ALLY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_BEGIN_ALLY, me->GetGUID());
            }
            else if (RageEncounter == DONE && AnetheronEncounter == NOT_STARTED) {
                player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_ANETHERON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_ANATHERON, me->GetGUID());
            }
            else if (RageEncounter == DONE && AnetheronEncounter == DONE) {
                player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_RETREAT_ALLY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_RETREAT_ALLY, me->GetGUID());
            }
            return true;
        }

        bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                StartEvent(player);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_BEGIN_ALLY_2, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                FirstBossDead = true;
                WaveCount = 9;
                StartEvent(player);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_ANATHERON2, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                Retreat();
                break;
            case GOSSIP_ACTION_INFO_DEF:
                Debug = !Debug;
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                if (pInstance)
                    pInstance->SetData(DATA_AZGALOREVENT, DONE);
                break;
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        auto ai = new npc_jaina_proudmooreAI(creature);

        ai->Reset();
        ai->EnterEvadeMode(CreatureAI::EvadeReason::EVADE_REASON_OTHER);

        ai->Spell[0].SpellId = SPELL_BLIZZARD;
        ai->Spell[0].Cooldown = 15000 + rand() % 20000;
        ai->Spell[0].TargetType = TARGETTYPE_RANDOM;

        ai->Spell[1].SpellId = SPELL_PYROBLAST;
        ai->Spell[1].Cooldown = 5500 + rand() % 4000;
        ai->Spell[1].TargetType = TARGETTYPE_RANDOM;

        ai->Spell[2].SpellId = SPELL_SUMMON_ELEMENTALS;
        ai->Spell[2].Cooldown = 45000;
        ai->Spell[2].TargetType = TARGETTYPE_SELF;

        return ai;
    }
};


class npc_thrall : public CreatureScript
{
public:
    npc_thrall() : CreatureScript("npc_thrall")
    { }

    class npc_thrallAI : public hyjalAI
    {
    public:
        npc_thrallAI(Creature *c) : hyjalAI(c)
        {}

        bool GossipHello(Player *player) override
        {
            if (EventBegun)
                return false;

            if (player->IsGameMaster()) {
                player->ADD_GOSSIP_ITEM(2, "[GM] Toggle Debug Timers", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            }

            uint32 AnetheronEvent = GetInstanceScript(DATA_ANETHERONEVENT);
            // Only let them start the Horde phases if Anetheron is dead.
            if (AnetheronEvent == DONE && GetInstanceScript(DATA_ALLIANCE_RETREAT))
            {
                uint32 KazrogalEvent = GetInstanceScript(DATA_KAZROGALEVENT);
                uint32 AzgalorEvent = GetInstanceScript(DATA_AZGALOREVENT);
                if (KazrogalEvent == NOT_STARTED) {
                    player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_BEGIN_HORDE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_BEGIN_HORDE, me->GetGUID());
                }
                else if (KazrogalEvent == DONE && AzgalorEvent == NOT_STARTED) {
                    player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_AZGALOR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_AZGALOR, me->GetGUID());
                }
                else if (AzgalorEvent == DONE) {
                    player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_RETREAT_HORDE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_RETREAT_HORDE, me->GetGUID());
                }
            }

            return true;
        }

        bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            DeSpawnVeins();//despawn the alliance veins
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                StartEvent(player);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_BEGIN_HORDE2, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                FirstBossDead = true;
                WaveCount = 9;
                StartEvent(player);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_AZGALOR2, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                Retreat();
                break;
            case GOSSIP_ACTION_INFO_DEF:
                Debug = !Debug;
                break;
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        auto ai = new npc_thrallAI(creature);

        ai->Reset();
        ai->EnterEvadeMode(CreatureAI::EvadeReason::EVADE_REASON_OTHER);

        ai->Spell[0].SpellId = SPELL_CHAIN_LIGHTNING;
        ai->Spell[0].Cooldown = 3000 + rand() % 5000;
        ai->Spell[0].TargetType = TARGETTYPE_VICTIM;

        ai->Spell[1].SpellId = SPELL_SUMMON_DIRE_WOLF;
        ai->Spell[1].Cooldown = 60000;
        ai->Spell[1].TargetType = TARGETTYPE_SELF;

        return ai;
    }
};

class npc_tyrande_whisperwind : public CreatureScript
{
public:
    npc_tyrande_whisperwind() : CreatureScript("npc_tyrande_whisperwind")
    { }

    class npc_tyrande_whisperwindAI : public hyjalAI
    {
    public:
        npc_tyrande_whisperwindAI(Creature *c) : hyjalAI(c)
        {}

        bool GossipHello(Player *player) override
        {
            uint32 AzgalorEvent = GetInstanceScript(DATA_AZGALOREVENT);

            // Only let them get item if Azgalor is dead.
            if (AzgalorEvent == DONE && !player->HasItemCount(ITEM_TEAR_OF_GODDESS, 1))
                player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_TYRANDE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_TYRANDE, me->GetGUID());
            return true;
        }

        bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            if (action == GOSSIP_ACTION_INFO_DEF)
            {
                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_TEAR_OF_GODDESS, 1);
                if (msg == EQUIP_ERR_OK)
                {
                    Item* item = player->StoreNewItem(dest, ITEM_TEAR_OF_GODDESS, true);
                    if (item && player)
                        player->SendNewItem(item, 1, true, false, true);
                }
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_TYRANDE2, me->GetGUID());
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        auto ai = new npc_tyrande_whisperwindAI(creature);

        ai->Reset();
        ai->EnterEvadeMode(CreatureAI::EvadeReason::EVADE_REASON_OTHER);

        return ai;
    }
};

void AddSC_hyjal()
{
    new npc_jaina_proudmoore();
    new npc_thrall();
    new npc_tyrande_whisperwind();
}

