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
SDName: Zangarmarsh
SD%Complete: 100
SDComment: Quest support: 9785, 9803, 10009, 9752. Mark Of ... buffs.
SDCategory: Zangarmarsh
EndScriptData */

/* ContentData
npcs_ashyen_and_keleth
npc_cooshcoosh
npc_elder_kuruti
npc_mortog_steamhead
npc_kayra_longmane
npc_hchuu
EndContentData */


#include "EscortAI.h"
#include "Pet.h"

/*######
## npcs_ashyen_and_keleth
######*/

#define GOSSIP_ITEM_BLESS_ASH     "Grant me your mark, wise ancient."
#define GOSSIP_ITEM_BLESS_KEL     "Grant me your mark, mighty ancient."
#define GOSSIP_REWARD_BLESS       -1000359
//#define TEXT_BLESSINGS        "<You need higher standing with Cenarion Expedition to receive a blessing.>"

bool GossipHello_npcs_ashyen_and_keleth(Player *player, Creature *_Creature )
{
    if (player->GetReputationRank(942) > REP_NEUTRAL)
    {
        if ( _Creature->GetEntry() == 17900)
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_BLESS_ASH, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        if ( _Creature->GetEntry() == 17901)
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_BLESS_KEL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }
    SEND_PREPARED_GOSSIP_MENU(player, _Creature);

    return true;
}

bool GossipSelect_npcs_ashyen_and_keleth(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        _Creature->SetPowerType(POWER_MANA);
        _Creature->SetMaxPower(POWER_MANA,200);             //set a "fake" mana value, we can't depend on database doing it in this case
        _Creature->SetPower(POWER_MANA,200);

        if ( _Creature->GetEntry() == 17900)                //check which creature we are dealing with
        {
            switch (player->GetReputationRank(942))
            {                                               //mark of lore
                case REP_FRIENDLY:
                    _Creature->CastSpell(player, 31808, true);
                    DoScriptText(GOSSIP_REWARD_BLESS, _Creature);
                    break;
                case REP_HONORED:
                    _Creature->CastSpell(player, 31810, true);
                    DoScriptText(GOSSIP_REWARD_BLESS, _Creature);
                    break;
                case REP_REVERED:
                    _Creature->CastSpell(player, 31811, true);
                    DoScriptText(GOSSIP_REWARD_BLESS, _Creature);
                    break;
                case REP_EXALTED:
                    _Creature->CastSpell(player, 31815, true);
                    DoScriptText(GOSSIP_REWARD_BLESS, _Creature);
                    break;
                default:
                    break;
            }
        }

        if ( _Creature->GetEntry() == 17901)
        {
            switch (player->GetReputationRank(942))         //mark of war
            {
                case REP_FRIENDLY:
                    _Creature->CastSpell(player, 31807, true);
                    DoScriptText(GOSSIP_REWARD_BLESS, _Creature);
                    break;
                case REP_HONORED:
                    _Creature->CastSpell(player, 31812, true);
                    DoScriptText(GOSSIP_REWARD_BLESS, _Creature);
                    break;
                case REP_REVERED:
                    _Creature->CastSpell(player, 31813, true);
                    DoScriptText(GOSSIP_REWARD_BLESS, _Creature);
                    break;
                case REP_EXALTED:
                    _Creature->CastSpell(player, 31814, true);
                    DoScriptText(GOSSIP_REWARD_BLESS, _Creature);
                    break;
                default:
                    break;
            }
        }
        player->CLOSE_GOSSIP_MENU();
        player->TalkedToCreature(_Creature->GetEntry(), _Creature->GetGUID());
    }
    return true;
}

/*######
## npc_cooshcoosh
######*/

#define GOSSIP_COOSH            "You owe Sim'salabim money. Hand them over or die!"

#define FACTION_HOSTILE_CO      45
#define FACTION_FRIENDLY_CO     35

#define SPELL_LIGHTNING_BOLT    9532

struct npc_cooshcooshAI : public ScriptedAI
{
    npc_cooshcooshAI(Creature* c) : ScriptedAI(c) {}

    uint32 LightningBolt_Timer;

    void Reset()
    override {
        LightningBolt_Timer = 2000;
        me->SetFaction(FACTION_FRIENDLY_CO);
    }

    void EnterCombat(Unit *who) override {}

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
            return;

        if( LightningBolt_Timer < diff )
        {
            DoCast(me->GetVictim(),SPELL_LIGHTNING_BOLT);
            LightningBolt_Timer = 5000;
        }else LightningBolt_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_npc_cooshcoosh(Creature *_Creature)
{
    return new npc_cooshcooshAI (_Creature);
}

bool GossipHello_npc_cooshcoosh(Player *player, Creature *_Creature )
{
    if( player->GetQuestStatus(10009) == QUEST_STATUS_INCOMPLETE )
        player->ADD_GOSSIP_ITEM(1, GOSSIP_COOSH, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    player->SEND_GOSSIP_MENU_TEXTID(9441, _Creature->GetGUID());
    return true;
}

bool GossipSelect_npc_cooshcoosh(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{
    if( action == GOSSIP_ACTION_INFO_DEF )
    {
        player->CLOSE_GOSSIP_MENU();
        _Creature->SetFaction(FACTION_HOSTILE_CO);
        ((npc_cooshcooshAI*)_Creature->AI())->AttackStart(player);
    }
    return true;
}

/*######
## npc_elder_kuruti
######*/

#define GOSSIP_ITEM_KUR1 "Offer treat"
#define GOSSIP_ITEM_KUR2 "Im a messenger for Draenei"
#define GOSSIP_ITEM_KUR3 "Get message"

bool GossipHello_npc_elder_kuruti(Player *player, Creature *_Creature )
{
    if( player->GetQuestStatus(9803) == QUEST_STATUS_INCOMPLETE )
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KUR1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    player->SEND_GOSSIP_MENU_TEXTID(9226,_Creature->GetGUID());

    return true;
}

bool GossipSelect_npc_elder_kuruti(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KUR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU_TEXTID(9227, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 1:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KUR3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU_TEXTID(9229, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
        {
            if( !player->HasItemCount(24573,1) )
            {
                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest, 24573, 1);
                if( msg == EQUIP_ERR_OK )
                {
                    player->StoreNewItem( dest, 24573, true);
                }
                else
                    player->SendEquipError( msg,nullptr,nullptr );
            }
            player->SEND_GOSSIP_MENU_TEXTID(9231, _Creature->GetGUID());
            break;
        }
    }
    return true;
}

/*######
## npc_mortog_steamhead
######*/

bool GossipHello_npc_mortog_steamhead(Player *player, Creature *_Creature)
{
    if (_Creature->IsVendor() && player->GetReputationRank(942) == REP_EXALTED)
        player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    SEND_PREPARED_GOSSIP_MENU(player, _Creature);

    return true;
}

bool GossipSelect_npc_mortog_steamhead(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_TRADE)
    {
        player->SEND_VENDORLIST( _Creature->GetGUID() );
    }
    return true;
}

/*######
## npc_kayra_longmane
######*/

#define SAY_PROGRESS_1  -1000360
#define SAY_PROGRESS_2  -1000361
#define SAY_PROGRESS_3  -1000362
#define SAY_PROGRESS_4  -1000363
#define SAY_PROGRESS_5  -1000364
#define SAY_PROGRESS_6  -1000365

#define QUEST_EFU   9752
#define MOB_AMBUSH  18042

struct npc_kayra_longmaneAI : public npc_escortAI
{
    npc_kayra_longmaneAI(Creature* c) : npc_escortAI(c) {}

    bool Completed;

    void Reset()
    override {
        Completed = false;
        me->SetFaction(1660);
    }

    void EnterCombat(Unit* who)override {}

    void JustSummoned(Creature *summoned)
    override {
        summoned->AI()->AttackStart(me);
        summoned->SetFaction(14);
    }

    void WaypointReached(uint32 i)
    override {
        Player* player = GetPlayerForEscort();

        switch(i)
        {
        case 0: DoScriptText(SAY_PROGRESS_1, me, player); break;
        case 5: DoScriptText(SAY_PROGRESS_2, me, player);
            me->SummonCreature(MOB_AMBUSH, -922.24, 5357.98, 17.93, 5.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
            me->SummonCreature(MOB_AMBUSH, -922.24, 5357.98, 17.93, 5.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
            break;
        case 6: DoScriptText(SAY_PROGRESS_3, me, player);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            break;
        case 18: DoScriptText(SAY_PROGRESS_4, me, player);
            me->SummonCreature(MOB_AMBUSH, -671.86, 5379.81, 22.12, 5.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
            me->SummonCreature(MOB_AMBUSH, -671.86, 5379.81, 22.12, 5.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
            break;
        case 19: me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            DoScriptText(SAY_PROGRESS_5, me, player); break;
        case 25: DoScriptText(SAY_PROGRESS_6, me, player);
            Completed = true;
            if(player)
                player->GroupEventHappens(QUEST_EFU, me);
            break;
        }
    }

    void JustDied(Unit* killer)
    override {
        if (PlayerGUID && !Completed)
        {
            Player* player = GetPlayerForEscort();
            if (player && !Completed)
                player->FailQuest(QUEST_EFU);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        npc_escortAI::UpdateAI(diff);
    }
};

bool QuestAccept_npc_kayra_longmane(Player* player, Creature* creature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_EFU)
    {
        ((npc_escortAI*)(creature->AI()))->Start(true, true, false, player->GetGUID(), creature->GetEntry());
        creature->SetFaction(113);
    }
    return true;
}

CreatureAI* GetAI_npc_kayra_longmaneAI(Creature* pCreature)
{
    return new npc_kayra_longmaneAI(pCreature);
}

/*######
## npc_hchuu
######*/

struct npc_hchuuAI : public ScriptedAI
{
    npc_hchuuAI(Creature* c) : ScriptedAI(c) 
    {
        SetCombatMovementAllowed(false);
    }
    
    void EnterCombat(Unit* pWho) override {}
    
    void MoveInLineOfSight(Unit* pWho)
    override {
        if (me->GetDistance(pWho) <= 5.0f && pWho->GetTypeId() == TYPEID_PLAYER) {
			if (uint64 critter_guid = pWho->ToPlayer()->GetCritterGUID())
				if (Creature* pet = pWho->GetMap()->GetCreature(critter_guid)) {
					if (pWho->ToPlayer()->GetQuestStatus(10945) == QUEST_STATUS_INCOMPLETE && pet->GetEntry() == 22817)
						pWho->ToPlayer()->AreaExploredOrEventHappens(10945);
				}
        }
    }
};

CreatureAI* GetAI_npc_hchuuAI(Creature* pCreature)
{
    return new npc_hchuuAI(pCreature);
}

/*######
## AddSC
######*/

void AddSC_zangarmarsh()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="npcs_ashyen_and_keleth";
    newscript->OnGossipHello =  &GossipHello_npcs_ashyen_and_keleth;
    newscript->OnGossipSelect = &GossipSelect_npcs_ashyen_and_keleth;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_cooshcoosh";
    newscript->OnGossipHello =  &GossipHello_npc_cooshcoosh;
    newscript->OnGossipSelect = &GossipSelect_npc_cooshcoosh;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_elder_kuruti";
    newscript->OnGossipHello =  &GossipHello_npc_elder_kuruti;
    newscript->OnGossipSelect = &GossipSelect_npc_elder_kuruti;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_mortog_steamhead";
    newscript->OnGossipHello =  &GossipHello_npc_mortog_steamhead;
    newscript->OnGossipSelect = &GossipSelect_npc_mortog_steamhead;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_kayra_longmane";
    newscript->GetAI = &GetAI_npc_kayra_longmaneAI;
    newscript->OnQuestAccept = &QuestAccept_npc_kayra_longmane;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name="npc_hchuu";
    newscript->GetAI = &GetAI_npc_hchuuAI;
    sScriptMgr->RegisterOLDScript(newscript);
}

