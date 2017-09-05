/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Ironforge
SD%Complete: 100
SDComment: Quest support: 3702
SDCategory: Ironforge
EndScriptData */

/* ContentData
npc_royal_historian_archesonus
EndContentData */



/*######
## npc_royal_historian_archesonus
######*/

#define GOSSIP_ITEM_ROYAL   "I am ready to listen"
#define GOSSIP_ITEM_ROYAL_1 "That is tragic. How did this happen?"
#define GOSSIP_ITEM_ROYAL_2 "Interesting, continue please."
#define GOSSIP_ITEM_ROYAL_3 "Unbelievable! How dare they??"
#define GOSSIP_ITEM_ROYAL_4 "Of course I will help!"

class npc_royal_historian_archesonus : public CreatureScript
{
public:
    npc_royal_historian_archesonus() : CreatureScript("npc_royal_historian_archesonus")
    { }

    class npc_royal_historian_archesonusAI : public ScriptedAI
    {
    public:
        npc_royal_historian_archesonusAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if (pPlayer->GetQuestStatus(3702) == QUEST_STATUS_INCOMPLETE)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ROYAL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(2235, me->GetGUID());
            }
            else
                SEND_DEFAULT_GOSSIP_MENU(pPlayer, me);

            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
        {
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ROYAL_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2236, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ROYAL_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2237, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ROYAL_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2238, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+3:
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ROYAL_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2239, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+4:
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AreaExploredOrEventHappens(3702);
                    break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_royal_historian_archesonusAI(creature);
    }
};



class npc_magni_bronzebeard : public CreatureScript
{
public:
    npc_magni_bronzebeard() : CreatureScript("npc_magni_bronzebeard")
    { }

    class npc_magni_bronzebeardAI : public ScriptedAI
    {
    public:
        npc_magni_bronzebeardAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual void QuestReward(Player* pPlayer, Quest const* pQuest, uint32 /*opt*/) override
        {
            if (pQuest->GetQuestId() == 8484) {
                std::stringstream sst;
                //TODO TRANSLATE
                sst << "Sachez tous que " << pPlayer->GetName() << " - " << pPlayer->GetClass() << " de l'Alliance - a gagné le respect de Forgefer et de l'Alliance dans son entièreté. Il a engagé la diplomatie avec les Grumegueules et accompli diverses actions en notre nom. Il est allé bien au delà de l'appel du devoir. Trois félicitations pour " << pPlayer->GetName() << " - un vrai héros de l'Alliance !";
                me->Yell(sst.str().c_str(), LANG_UNIVERSAL);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_magni_bronzebeardAI(creature);
    }
};


void AddSC_ironforge()
{

    new npc_royal_historian_archesonus();
    
    new npc_magni_bronzebeard();
}

