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
SDName: Stormwind_City
SD%Complete: 100
SDComment: Quest support: 1640, 1447, 4185, 8356, 11223. Receive emote General Marcus
SDCategory: Stormwind City
EndScriptData */

/* ContentData
npc_archmage_malin
npc_bartleby
npc_dashel_stonefist
npc_general_marcus_jonathan
npc_lady_katrana_prestor
npc_innkeeper_allison
npc_monty
EndContentData */



/*######
## npc_archmage_malin
######*/

//TODO translate
#define GOSSIP_ITEM_MALIN "Pouvez-vous m'envoyer à Theramore ? J'ai un message urgent pour Jaina, de la part de Bolvar."

bool GossipHello_npc_archmage_malin(Player *player, Creature *_Creature)
{
    if(_Creature->IsQuestGiver())
        player->PrepareQuestMenu( _Creature->GetGUID() );

    if(player->GetQuestStatus(11223) == QUEST_STATUS_COMPLETE && !player->GetQuestRewardStatus(11223))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MALIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    SEND_PREPARED_GOSSIP_MENU(player, _Creature);

    return true;
}

bool GossipSelect_npc_archmage_malin(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if(action == GOSSIP_ACTION_INFO_DEF)
    {
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, 42711, true);
    }

    return true;
}

/*######
## npc_bartleby
######*/

struct npc_bartlebyAI : public ScriptedAI
{
    npc_bartlebyAI(Creature *c) : ScriptedAI(c) {}

    uint64 PlayerGUID;

    void Reset()
    override {
        me->SetFaction(11);
        me->SetEmoteState(EMOTE_ONESHOT_EAT);

        PlayerGUID = 0;
    }

    void JustDied(Unit *who)
    override {
        me->SetFaction(11);
    }

    void DamageTaken(Unit *done_by, uint32 & damage)
    override {
        if(damage > me->GetHealth() || ((me->GetHealth() - damage)*100 / me->GetMaxHealth() < 15))
        {
            //Take 0 damage
            damage = 0;

            if (done_by->GetTypeId() == TYPEID_PLAYER && done_by->GetGUID() == PlayerGUID)
            {
                (done_by->ToPlayer())->AttackStop();
                (done_by->ToPlayer())->AreaExploredOrEventHappens(1640);
            }
            me->CombatStop();
            EnterEvadeMode();
        }
    }

    void EnterCombat(Unit *who) override {}
};

bool QuestAccept_npc_bartleby(Player *player, Creature *_Creature, Quest const *_Quest)
{
    if(_Quest->GetQuestId() == 1640)
    {
        _Creature->SetFaction(168);
        ((npc_bartlebyAI*)_Creature->AI())->PlayerGUID = player->GetGUID();
        ((npc_bartlebyAI*)_Creature->AI())->AttackStart(player);
    }
    return true;
}

CreatureAI* GetAI_npc_bartleby(Creature *_creature)
{
    return new npc_bartlebyAI(_creature);
}

/*######
## npc_dashel_stonefist
######*/

struct npc_dashel_stonefistAI : public ScriptedAI
{
    npc_dashel_stonefistAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    override {
        me->SetFaction(11);
        me->SetEmoteState(EMOTE_ONESHOT_EAT);
    }

    void DamageTaken(Unit *done_by, uint32 & damage)
    override {
        if((damage > me->GetHealth()) || (me->GetHealth() - damage)*100 / me->GetMaxHealth() < 15)
        {
            //Take 0 damage
            damage = 0;

            if (done_by->GetTypeId() == TYPEID_PLAYER)
            {
                (done_by->ToPlayer())->AttackStop();
                (done_by->ToPlayer())->AreaExploredOrEventHappens(1447);
            }
            //me->CombatStop();
            EnterEvadeMode();
        }
    }

    void EnterCombat(Unit *who) override {}
};

bool QuestAccept_npc_dashel_stonefist(Player *player, Creature *_Creature, Quest const *_Quest)
{
    if(_Quest->GetQuestId() == 1447)
    {
        _Creature->SetFaction(168);
        ((npc_dashel_stonefistAI*)_Creature->AI())->AttackStart(player);
    }
    return true;
}

CreatureAI* GetAI_npc_dashel_stonefist(Creature *_creature)
{
    return new npc_dashel_stonefistAI(_creature);
}

/*######
## npc_general_marcus_jonathan
######*/

class npc_general_marcus_jonathan : public CreatureScript
{
public:
    npc_general_marcus_jonathan() : CreatureScript("npc_general_marcus_jonathan") {}

    class npc_general_marcus_jonathanAI : public CreatureAI
    {
    public:
        npc_general_marcus_jonathanAI(Creature* creature) : CreatureAI(creature)
        {
        }

        void ReceiveEmote(Player* player, uint32 emote) override
        {
            if (player->GetTeam() == ALLIANCE)
            {
                if (emote == TEXTEMOTE_SALUTE)
                {
                    me->SetOrientation(me->GetAngle(player));
                    me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                }
                if (emote == TEXTEMOTE_WAVE)
                {
                    //TODO: move to db to get translations
                    me->Say("Greetings citizen.", LANG_COMMON, nullptr);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
        override {
        return new npc_general_marcus_jonathanAI(creature);
    }
};

/*######
## npc_lady_katrana_prestor
######*/

//TODO translate
#define GOSSIP_ITEM_KAT_1 "Excusez mon intrusion, Dame Prestor, mais le Seigneur Bolvar a suggéré que je vous demande conseil."
#define GOSSIP_ITEM_KAT_2 "Mes excuses, Dame Prestor."
#define GOSSIP_ITEM_KAT_3 "Je vous demande pardon, Dame Prestor. Ce n'était pas mon intention."
#define GOSSIP_ITEM_KAT_4 "Merci pour votre temps, Dame Prestor."

bool GossipHello_npc_lady_katrana_prestor(Player *player, Creature *_Creature)
{
    if (_Creature->IsQuestGiver())
        player->PrepareQuestMenu( _Creature->GetGUID() );

    if (player->GetQuestStatus(4185) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    player->SEND_GOSSIP_MENU_TEXTID(2693, _Creature->GetGUID());

    return true;
}

bool GossipSelect_npc_lady_katrana_prestor(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU_TEXTID(2694, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU_TEXTID(2695, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->SEND_GOSSIP_MENU_TEXTID(2696, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            player->CLOSE_GOSSIP_MENU();
            player->AreaExploredOrEventHappens(4185);
            break;
    }
    return true;
}

/*######
## npc_innkeeper_allison
######*/

class npc_innkeeper_allison : public CreatureScript
{
public:
    npc_innkeeper_allison() : CreatureScript("npc_innkeeper_allison") {}

    class npc_innkeeper_allisonAI : public CreatureAI
    {
    public:
        const uint32 QUEST_FLEXING_NOUGAT = 8356;

        npc_innkeeper_allisonAI(Creature* creature) : CreatureAI(creature)
        {
        }

        void ReceiveEmote(Player* player, uint32 emote) override
        {
            if (emote == TEXTEMOTE_FLEX)
            {
                if (player->GetQuestStatus(QUEST_FLEXING_NOUGAT) == QUEST_STATUS_INCOMPLETE)
                    player->AreaExploredOrEventHappens(QUEST_FLEXING_NOUGAT);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
        override {
        return new npc_innkeeper_allisonAI(creature);
    }
};

/*######
## npc_monty
######*/

bool ChooseReward_npc_monty(Player* player, Creature* creature, const Quest* quest, uint32 option)
{
    if (quest->GetQuestId() == 6661) {
        DoScriptText(-1000765, creature, nullptr);
        Creature* rat = creature->FindNearestCreature(13017, 15.0f, true);
        while (rat) {
            rat->DisappearAndDie();
            rat->Respawn();
            rat = creature->FindNearestCreature(13017, 15.0f, true);
        }
    }
    
    return true;
}

/*######
## AddSC
######*/

void AddSC_stormwind_city()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="npc_archmage_malin";
    newscript->OnGossipHello = &GossipHello_npc_archmage_malin;
    newscript->OnGossipSelect = &GossipSelect_npc_archmage_malin;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_bartleby";
    newscript->GetAI = &GetAI_npc_bartleby;
    newscript->OnQuestAccept = &QuestAccept_npc_bartleby;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_dashel_stonefist";
    newscript->GetAI = &GetAI_npc_dashel_stonefist;
    newscript->OnQuestAccept = &QuestAccept_npc_dashel_stonefist;
    sScriptMgr->RegisterOLDScript(newscript);

    new npc_general_marcus_jonathan();

    newscript = new OLDScript;
    newscript->Name="npc_lady_katrana_prestor";
    newscript->OnGossipHello = &GossipHello_npc_lady_katrana_prestor;
    newscript->OnGossipSelect = &GossipSelect_npc_lady_katrana_prestor;
    sScriptMgr->RegisterOLDScript(newscript);
    
    new npc_innkeeper_allison();
    
    newscript = new OLDScript;
    newscript->Name = "npc_monty";
    newscript->OnQuestReward = &ChooseReward_npc_monty;
    sScriptMgr->RegisterOLDScript(newscript);
}

