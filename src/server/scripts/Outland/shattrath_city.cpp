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
SDName: Shattrath_City
SD%Complete: 100
SDComment: Quest support: 10004, 10009, 10211, 10231. Flask vendors, Teleport to Caverns of Time
SDCategory: Shattrath City
EndScriptData */

/* ContentData
npc_raliq_the_drunk
npc_salsalabim
npc_shattrathflaskvendors
npc_zephyr
npc_kservant
npc_dirty_larry
npc_ishanah
npc_khadgar
EndContentData */


#include "EscortAI.h"

/*######
## npc_raliq_the_drunk
######*/

#define GOSSIP_RALIQ            "You owe Sim'salabim money. Hand them over or die!"

#define FACTION_HOSTILE_RD      45
#define FACTION_FRIENDLY_RD     35

#define SPELL_UPPERCUT          10966

struct npc_raliq_the_drunkAI : public ScriptedAI
{
    npc_raliq_the_drunkAI(Creature* c) : ScriptedAI(c) {}

    uint32 Uppercut_Timer;

    void Reset()
    override {
        Uppercut_Timer = 5000;
        me->SetFaction(FACTION_FRIENDLY_RD);
    }

    void EnterCombat(Unit *who) override {}

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
            return;

        if( Uppercut_Timer < diff )
        {
            DoCast(me->GetVictim(),SPELL_UPPERCUT);
            Uppercut_Timer = 15000;
        }else Uppercut_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_npc_raliq_the_drunk(Creature *_Creature)
{
    return new npc_raliq_the_drunkAI (_Creature);
}

bool GossipHello_npc_raliq_the_drunk(Player *player, Creature *_Creature )
{
    if( player->GetQuestStatus(10009) == QUEST_STATUS_INCOMPLETE )
        player->ADD_GOSSIP_ITEM(1, GOSSIP_RALIQ, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    player->SEND_GOSSIP_MENU_TEXTID(9440, _Creature->GetGUID());
    return true;
}

bool GossipSelect_npc_raliq_the_drunk(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{
    if( action == GOSSIP_ACTION_INFO_DEF+1 )
    {
        player->CLOSE_GOSSIP_MENU();
        _Creature->SetFaction(FACTION_HOSTILE_RD);
        ((npc_raliq_the_drunkAI*)_Creature->AI())->AttackStart(player);
    }
    return true;
}

/*######
# npc_salsalabim
######*/

#define FACTION_HOSTILE_SA              90
#define FACTION_FRIENDLY_SA             35
#define QUEST_10004                     10004

#define SPELL_MAGNETIC_PULL             31705

struct npc_salsalabimAI : public ScriptedAI
{
    npc_salsalabimAI(Creature* c) : ScriptedAI(c) {}

    uint32 MagneticPull_Timer;

    void Reset()
    override {
        MagneticPull_Timer = 15000;
        me->SetFaction(FACTION_FRIENDLY_SA);
    }

    void EnterCombat(Unit *who) override {}

    void DamageTaken(Unit *done_by, uint32 &damage)
    override {
        if( done_by->GetTypeId() == TYPEID_PLAYER )
            if( (me->GetHealth()-damage)*100 / me->GetMaxHealth() < 20 )
        {
            (done_by->ToPlayer())->GroupEventHappens(QUEST_10004,me);
            damage = 0;
            EnterEvadeMode();
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
            return;

        if( MagneticPull_Timer < diff )
        {
            DoCast(me->GetVictim(),SPELL_MAGNETIC_PULL);
            MagneticPull_Timer = 15000;
        }else MagneticPull_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_npc_salsalabim(Creature *_Creature)
{
    return new npc_salsalabimAI (_Creature);
}

bool GossipHello_npc_salsalabim(Player *player, Creature *_Creature)
{
    if( player->GetQuestStatus(QUEST_10004) == QUEST_STATUS_INCOMPLETE )
    {
        _Creature->SetFaction(FACTION_HOSTILE_SA);
        ((npc_salsalabimAI*)_Creature->AI())->AttackStart(player);
    }
    else
    {
        if( _Creature->IsQuestGiver() )
            player->PrepareQuestMenu( _Creature->GetGUID() );

        SEND_DEFAULT_GOSSIP_MENU(player, _Creature);    }
    return true;
}

/*
##################################################
Shattrath City Flask Vendors provides flasks to people exalted with 3 factions:
Haldor the Compulsive
Arcanist Xorith
Both sell special flasks for use in Outlands 25man raids only,
purchasable for one Mark of Illidari each
Purchase requires exalted reputation with Scryers/Aldor, Cenarion Expedition and The Sha'tar
##################################################
*/

bool GossipHello_npc_shattrathflaskvendors(Player *player, Creature *_Creature)
{
    if(_Creature->GetEntry() == 23484)
    {
        // Aldor vendor
        if( _Creature->IsVendor() && (player->GetReputationRank(932) == REP_EXALTED) && (player->GetReputationRank(935) == REP_EXALTED) && (player->GetReputationRank(942) == REP_EXALTED) )
        {
            player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            player->SEND_GOSSIP_MENU_TEXTID(11085, _Creature->GetGUID());
        }
        else
        {
            player->SEND_GOSSIP_MENU_TEXTID(11083, _Creature->GetGUID());
        }
    }

    if(_Creature->GetEntry() == 23483)
    {
        // Scryers vendor
        if( _Creature->IsVendor() && (player->GetReputationRank(934) == REP_EXALTED) && (player->GetReputationRank(935) == REP_EXALTED) && (player->GetReputationRank(942) == REP_EXALTED) )
        {
            player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            player->SEND_GOSSIP_MENU_TEXTID(11085, _Creature->GetGUID());
        }
        else
        {
            player->SEND_GOSSIP_MENU_TEXTID(11084, _Creature->GetGUID());
        }
    }

    return true;
}

bool GossipSelect_npc_shattrathflaskvendors(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if( action == GOSSIP_ACTION_TRADE )
        player->SEND_VENDORLIST( _Creature->GetGUID() );

    return true;
}

/*######
# npc_zephyr
######*/

//TODO : translate me
#define GOSSIP_HZ "Take me to the Caverns of Time."

bool GossipHello_npc_zephyr(Player *player, Creature *_Creature)
{
    if( player->GetReputationRank(989) >= REP_REVERED )
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HZ, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    SEND_DEFAULT_GOSSIP_MENU(player, _Creature);
    return true;
}

bool GossipSelect_npc_zephyr(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if( action == GOSSIP_ACTION_INFO_DEF+1 )
        player->CastSpell(player,37778,false);

    return true;
}

/*######
# npc_kservant
######*/

#define SAY1       -1000306
#define WHISP1     -1000307
#define WHISP2     -1000308
#define WHISP3     -1000309
#define WHISP4     -1000310
#define WHISP5     -1000311
#define WHISP6     -1000312
#define WHISP7     -1000313
#define WHISP8     -1000314
#define WHISP9     -1000315
#define WHISP10    -1000316
#define WHISP11    -1000317
#define WHISP12    -1000318
#define WHISP13    -1000319
#define WHISP14    -1000320
#define WHISP15    -1000321
#define WHISP16    -1000322
#define WHISP17    -1000323
#define WHISP18    -1000324
#define WHISP19    -1000325
#define WHISP20    -1000326
#define WHISP21    -1000327

struct npc_kservantAI : public npc_escortAI
{
public:
    npc_kservantAI(Creature *c) : npc_escortAI(c) {}


    void WaypointReached(uint32 i)
    override {
        Unit *pTemp = ObjectAccessor::GetUnit(*me,PlayerGUID);

        if( !pTemp )
            return;

        switch(i)
        {
            case 0: DoScriptText(SAY1, me, pTemp); break;
            case 4: DoScriptText(WHISP1, me, pTemp); break;
            case 6: DoScriptText(WHISP2, me, pTemp); break;
            case 7: DoScriptText(WHISP3, me, pTemp); break;
            case 8: DoScriptText(WHISP4, me, pTemp); break;
            case 17: DoScriptText(WHISP5, me, pTemp); break;
            case 18: DoScriptText(WHISP6, me, pTemp); break;
            case 19: DoScriptText(WHISP7, me, pTemp); break;
            case 33: DoScriptText(WHISP8, me, pTemp); break;
            case 34: DoScriptText(WHISP9, me, pTemp); break;
            case 35: DoScriptText(WHISP10, me, pTemp); break;
            case 36: DoScriptText(WHISP11, me, pTemp); break;
            case 43: DoScriptText(WHISP12, me, pTemp); break;
            case 44: DoScriptText(WHISP13, me, pTemp); break;
            case 49: DoScriptText(WHISP14, me, pTemp); break;
            case 50: DoScriptText(WHISP15, me, pTemp); break;
            case 51: DoScriptText(WHISP16, me, pTemp); break;
            case 52: DoScriptText(WHISP17, me, pTemp); break;
            case 53: DoScriptText(WHISP18, me, pTemp); break;
            case 54: DoScriptText(WHISP19, me, pTemp); break;
            case 55: DoScriptText(WHISP20, me, pTemp); break;
            case 56: DoScriptText(WHISP21, me, pTemp);
               if( PlayerGUID )
                {
                    Player* player = (GetPlayerForEscort());
                    if( player )
                    {
                        (player)->GroupEventHappens(10211,me);
                        player->CompleteQuest(10211); //attempt to force completion anyway
                    }
                }
                break;
        }
    }

    void EnterCombat(Unit* who) override {}

    void MoveInLineOfSight(Unit *who)
    override {
        if( HasEscortState(STATE_ESCORT_ESCORTING) )
            return;

        if( who->GetTypeId() == TYPEID_PLAYER )
        {
            if( (who->ToPlayer())->GetQuestStatus(10211) == QUEST_STATUS_INCOMPLETE )
            {
                float Radius = 10.0;
                if( me->IsWithinDistInMap(who, Radius) )
                {
                    ((npc_escortAI*)(me->AI()))->Start(false, false, false, who->GetGUID(), me->GetEntry());
                }
            }
        }
    }

    void Reset() override {}

    void UpdateAI(const uint32 diff)
    override {
        npc_escortAI::UpdateAI(diff);
    }
};
CreatureAI* GetAI_npc_kservantAI(Creature *pCreature)
{
    return new npc_kservantAI(pCreature);
}

/*######
# npc_dirty_larry
######*/

#define GOSSIP_BOOK "Ezekiel said that you might have a certain book..."

#define SAY_1       -1000328
#define SAY_2       -1000329
#define SAY_3       -1000330
#define SAY_4       -1000331
#define SAY_5       -1000332
#define SAY_GIVEUP  -1000333

#define QUEST_WBI       10231
#define NPC_CREEPJACK   19726
#define NPC_MALONE      19725

struct npc_dirty_larryAI : public ScriptedAI
{
    npc_dirty_larryAI(Creature* c) : ScriptedAI(c) {}

    bool Event;
    bool Attack;
    bool Done;

    uint64 PlayerGUID;

    uint32 SayTimer;
    uint32 Step;

    void Reset()
    override {
        Event = false;
        Attack = false;
        Done = false;

        PlayerGUID = 0;
        SayTimer = 0;
        Step = 0;

        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->SetFaction(1194);
        Unit* Creepjack = FindCreature(NPC_CREEPJACK, 20, me);
        if(Creepjack)
        {
            (Creepjack->ToCreature())->AI()->EnterEvadeMode();
            Creepjack->SetFaction(1194);
            Creepjack->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
        Unit* Malone = FindCreature(NPC_MALONE, 20, me);
        if(Malone)
        {
            (Malone->ToCreature())->AI()->EnterEvadeMode();
            Malone->SetFaction(1194);
            Malone->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    }

    uint32 NextStep(uint32 step)
    {
        Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);

        switch(step)
        {
        case 0:
		{ 
			me->SetInFront(player);
            Unit* Creepjack = FindCreature(NPC_CREEPJACK, 20, me);
            if(Creepjack)
                Creepjack->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
            Unit* Malone = FindCreature(NPC_MALONE, 20, me);
            if(Malone)
                Malone->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
			return 2000;
		}
        case 1: DoScriptText(SAY_1, me, player); return 3000;
        case 2: DoScriptText(SAY_2, me, player); return 5000;
        case 3: DoScriptText(SAY_3, me, player); return 2000;
        case 4: DoScriptText(SAY_4, me, player); return 2000;
        case 5: DoScriptText(SAY_5, me, player); return 2000;
        case 6: Attack = true; return 2000;
        default: return 0;
        }
    }

    void EnterCombat(Unit* who)override {}
    
    void DamageTaken(Unit *pSource, uint32 &damage)
    override {
        if (damage > me->GetHealth()) {
            damage = 0;
            Unit* Creepjack = FindCreature(NPC_CREEPJACK, 20, me);
            if(Creepjack)
            {
                (Creepjack->ToCreature())->AI()->EnterEvadeMode();
                Creepjack->SetFaction(1194);
                Creepjack->GetMotionMaster()->MoveTargetedHome();
                Creepjack->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
            Unit* Malone = FindCreature(NPC_MALONE, 20, me);
            if(Malone)
            {
                (Malone->ToCreature())->AI()->EnterEvadeMode();
                Malone->SetFaction(1194);
                Malone->GetMotionMaster()->MoveTargetedHome();
                Malone->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFaction(1194);
            Done = true;
            DoScriptText(SAY_GIVEUP, me, nullptr);
            me->DeleteThreatList();
            me->CombatStop();
            me->GetMotionMaster()->MoveTargetedHome();
            Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
            if(player)
                player->GroupEventHappens(QUEST_WBI, me);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(SayTimer < diff)
        {
            if(Event)
                SayTimer = NextStep(++Step);
        }
            else SayTimer -= diff;

        if (Attack)
        {
            Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
            me->SetFaction(14);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            if(player)
            {
            Unit* Creepjack = FindCreature(NPC_CREEPJACK, 20, me);
            if(Creepjack)
            {
                Creepjack->Attack(player, true);
                Creepjack->SetFaction(14);
                Creepjack->GetMotionMaster()->MoveChase(player);
                Creepjack->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
            Unit* Malone = FindCreature(NPC_MALONE, 20, me);
            if(Malone)
            {
                Malone->Attack(player, true);
                Malone->SetFaction(14);
                Malone->GetMotionMaster()->MoveChase(player);
                Malone->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
                DoStartMovement(player);
                AttackStart(player);
            }
            Attack = false;
        }

        DoMeleeAttackIfReady();
    }
};

bool GossipHello_npc_dirty_larry(Player *player, Creature *creature)
{
    if (creature->IsQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    if(player->GetQuestStatus(QUEST_WBI) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BOOK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    SEND_PREPARED_GOSSIP_MENU(player, creature);    return true;
}

bool GossipSelect_npc_dirty_larry(Player *player, Creature *creature, uint32 sender, uint32 action )
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        ((npc_dirty_larryAI*)creature->AI())->Reset();
        ((npc_dirty_larryAI*)creature->AI())->Event = true;
        ((npc_dirty_larryAI*)creature->AI())->PlayerGUID = player->GetGUID();
        player->CLOSE_GOSSIP_MENU();
    }

    return true;
}

CreatureAI* GetAI_npc_dirty_larryAI(Creature *_Creature)
{
    return new npc_dirty_larryAI (_Creature);
}

/*######
# npc_ishanah
######*/

#define ISANAH_GOSSIP_1 "Who are the Sha'tar?"
#define ISANAH_GOSSIP_2 "Isn't Shattrath a draenei city? Why do you allow others here?"

bool GossipHello_npc_ishanah(Player *player, Creature *_Creature)
{
    if (_Creature->IsQuestGiver())
        player->PrepareQuestMenu(_Creature->GetGUID());

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ISANAH_GOSSIP_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ISANAH_GOSSIP_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    SEND_PREPARED_GOSSIP_MENU(player, _Creature);
    return true;
}

bool GossipSelect_npc_ishanah(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if(action == GOSSIP_ACTION_INFO_DEF+1)
        player->SEND_GOSSIP_MENU_TEXTID(9458, _Creature->GetGUID());
    else if(action == GOSSIP_ACTION_INFO_DEF+2)
        player->SEND_GOSSIP_MENU_TEXTID(9459, _Creature->GetGUID());

    return true;
}

/*######
# npc_khadgar
######*/

// Khadgar : 18166
#define TEXT_HELLO             20037
#define TEXT_MENU1             20039
#define TEXT_MENU2             20041
#define TEXT_MENU3             20043
#define TEXT_MENU4             20045
#define TEXT_MENU5             20047
#define TEXT_MENU6             20049
#define GOSSIP_ITEM_1          20038
#define GOSSIP_ITEM_2          20040
#define GOSSIP_ITEM_3          20042
#define GOSSIP_ITEM_4          20044
#define GOSSIP_ITEM_5          20046
#define GOSSIP_ITEM_6          20048
#define GOSSIP_ITEM_7          20050

bool GossipHello_npc_khadgar(Player* player, Creature* _Creature)
{
    player->PrepareQuestMenu(_Creature->GetGUID());
    player->ADD_GOSSIP_ITEM_DB(0, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    player->SEND_GOSSIP_MENU_TEXTID(TEXT_HELLO,_Creature->GetGUID());
    return true;
}

bool GossipSelect_npc_khadgar(Player* player, Creature* _Creature, uint32 sender, uint32 action)
{
	switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->ADD_GOSSIP_ITEM_DB(0, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->SEND_GOSSIP_MENU_TEXTID(TEXT_MENU1,_Creature->GetGUID());
            break;
		case GOSSIP_ACTION_INFO_DEF+2:
            player->ADD_GOSSIP_ITEM_DB(0, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            player->SEND_GOSSIP_MENU_TEXTID(TEXT_MENU2,_Creature->GetGUID());
            break;
		case GOSSIP_ACTION_INFO_DEF+3:
            player->ADD_GOSSIP_ITEM_DB(0, GOSSIP_ITEM_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            player->SEND_GOSSIP_MENU_TEXTID(TEXT_MENU3,_Creature->GetGUID());
            break;
		case GOSSIP_ACTION_INFO_DEF+4:
            player->ADD_GOSSIP_ITEM_DB(0, GOSSIP_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            player->SEND_GOSSIP_MENU_TEXTID(TEXT_MENU4,_Creature->GetGUID());
            break;
		case GOSSIP_ACTION_INFO_DEF+5:
            player->ADD_GOSSIP_ITEM_DB(0, GOSSIP_ITEM_6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            player->SEND_GOSSIP_MENU_TEXTID(TEXT_MENU5,_Creature->GetGUID());
            break;
		case GOSSIP_ACTION_INFO_DEF+6:
            player->ADD_GOSSIP_ITEM_DB(0, GOSSIP_ITEM_7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
            player->SEND_GOSSIP_MENU_TEXTID(TEXT_MENU6,_Creature->GetGUID());
            break;
		case GOSSIP_ACTION_INFO_DEF+7:
            GossipHello_npc_khadgar(player,_Creature);
            break;
    }

    return true;
}

void AddSC_shattrath_city()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="npc_raliq_the_drunk";
    newscript->OnGossipHello =  &GossipHello_npc_raliq_the_drunk;
    newscript->OnGossipSelect = &GossipSelect_npc_raliq_the_drunk;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_salsalabim";
    newscript->GetAI = &GetAI_npc_salsalabim;
    newscript->OnGossipHello =  &GossipHello_npc_salsalabim;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_shattrathflaskvendors";
    newscript->OnGossipHello =  &GossipHello_npc_shattrathflaskvendors;
    newscript->OnGossipSelect = &GossipSelect_npc_shattrathflaskvendors;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_zephyr";
    newscript->OnGossipHello =  &GossipHello_npc_zephyr;
    newscript->OnGossipSelect = &GossipSelect_npc_zephyr;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_kservant";
    newscript->GetAI = &GetAI_npc_kservantAI;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_dirty_larry";
    newscript->GetAI = &GetAI_npc_dirty_larryAI;
    newscript->OnGossipHello =   &GossipHello_npc_dirty_larry;
    newscript->OnGossipSelect = &GossipSelect_npc_dirty_larry;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_ishanah";
    newscript->OnGossipHello =  &GossipHello_npc_ishanah;
    newscript->OnGossipSelect = &GossipSelect_npc_ishanah;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_khadgar";
    newscript->OnGossipHello =  &GossipHello_npc_khadgar;
    newscript->OnGossipSelect = &GossipSelect_npc_khadgar;
    sScriptMgr->RegisterOLDScript(newscript);
}

