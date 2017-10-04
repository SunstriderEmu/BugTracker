
/* ScriptData
SDName: Black_Temple
SD%Complete: 95
SDComment: Spirit of Olum: Player Teleporter to Seer Kanai Teleport after defeating Naj'entus and Supremus. TODO: Find proper gossip.
SDCategory: Black Temple
EndScriptData */

/* ContentData
npc_spirit_of_olum
npc_spirit_of_udalo
EndContentData */


#include "def_black_temple.h"

/*###
# npc_spirit_of_olum
####*/

//TODO translate
#define SPELL_TELEPORT      41566                           // s41566 - Teleport to Ashtongue NPC's
#define GOSSIP_OPTION_OLUM1        "Téléportez-moi au Sanctuaire des ombres."
#define SPELL_TELEPORT_UDALO    41570
#define GOSSIP_OPTION_UDALO            "Teleportez-moi au Conseil Illidari."

class npc_spirit_of_olum : public CreatureScript
{
public:
    npc_spirit_of_olum() : CreatureScript("npc_spirit_of_olum")
    { }

   class npc_spirit_of_olumAI : public ScriptedAI
   {
   public:
        npc_spirit_of_olumAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            InstanceScript* pInstance = ((InstanceScript*)me->GetInstanceScript());

            if (pInstance)
            {
                if (pInstance->GetData(DATA_SUPREMUSEVENT) == DONE && pInstance->GetData(DATA_HIGHWARLORDNAJENTUSEVENT) == DONE)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION_OLUM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->SEND_GOSSIP_MENU_TEXTID(4100, me->GetGUID());
                    return true;
                }
                if (pInstance->GetData(DATA_ILLIDARICOUNCILEVENT) == DONE)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION_UDALO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(4100, me->GetGUID());
                    return true;
                }
            }
            player->SEND_GOSSIP_MENU_TEXTID(4101, me->GetGUID());
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            player->CLOSE_GOSSIP_MENU();
            if(action == GOSSIP_ACTION_INFO_DEF + 1) {
                player->InterruptNonMeleeSpells(false);
                player->CastSpell(player, SPELL_TELEPORT, false);
            }
            else if (action == GOSSIP_ACTION_INFO_DEF + 2) {
                player->InterruptNonMeleeSpells(false);
                player->CastSpell(player, SPELL_TELEPORT_UDALO, false);
            }

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_spirit_of_olumAI(creature);
    }
};



/*######
## npc_spirit_of_udalo
######*/

class npc_spirit_of_udalo : public CreatureScript
{
public:
    npc_spirit_of_udalo() : CreatureScript("npc_spirit_of_udalo")
    { }

   class npc_spirit_of_udaloAI : public ScriptedAI
   {
   public:
        npc_spirit_of_udaloAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            InstanceScript* pInstance = ((InstanceScript*)me->GetInstanceScript());

            if(pInstance && (pInstance->GetData(DATA_ILLIDARICOUNCILEVENT) >= DONE))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION_UDALO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            SEND_PREPARED_GOSSIP_MENU(player, me);
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if(action == GOSSIP_ACTION_INFO_DEF + 1)
                player->CLOSE_GOSSIP_MENU();

            player->InterruptNonMeleeSpells(false);
            player->CastSpell(player, SPELL_TELEPORT_UDALO, false);
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_spirit_of_udaloAI(creature);
    }
};



void AddSC_black_temple()
{

    new npc_spirit_of_olum();
    
    new npc_spirit_of_udalo();
}

