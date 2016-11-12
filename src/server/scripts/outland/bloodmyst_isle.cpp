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
SDName: Bloodmyst_Isle
SD%Complete: 80
SDComment: Quest support: 9670, 9756(gossip items text needed).
SDCategory: Bloodmyst Isle
EndScriptData */

/* ContentData
mob_webbed_creature
npc_captured_sunhawk_agent
npc_razormaw
EndContentData */



/*######
## mob_webbed_creature
######*/

//possible creatures to be spawned
const uint32 possibleSpawns[32] = {17322, 17661, 17496, 17522, 17340, 17352, 17333, 17524, 17654, 17348, 17339, 17345, 17359, 17353, 17336, 17550, 17330, 17701, 17321, 17680, 17325, 17320, 17683, 17342, 17715, 17334, 17341, 17338, 17337, 17346, 17344, 17327};

struct mob_webbed_creatureAI : public ScriptedAI
{
    mob_webbed_creatureAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    override {
    }

    void JustDied(Unit* pKiller)
    override {
        uint32 spawnCreatureID;

        switch(rand()%3)
        {
            case 0:
                spawnCreatureID = 17681;
                if (pKiller->GetTypeId() == TYPEID_PLAYER)
                    (pKiller)->ToPlayer()->KilledMonsterCredit(spawnCreatureID, me->GetGUID());
                break;
            case 1:
            case 2:
                spawnCreatureID = possibleSpawns[rand()%31];
                break;
        }

        if(spawnCreatureID)
            DoSpawnCreature(spawnCreatureID,0,0,0,me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
    }
};

CreatureAI* GetAI_mob_webbed_creature(Creature* pCreature)
{
    return new mob_webbed_creatureAI (pCreature);
}

/*######
## npc_captured_sunhawk_agent
######*/

#define C_SUNHAWK_TRIGGER 17974

bool GossipHello_npc_captured_sunhawk_agent(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->HasAuraEffect(31609,1) && pPlayer->GetQuestStatus(9756) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU_TEXTID(9136, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU_TEXTID(9134, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_captured_sunhawk_agent(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9137, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9138, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9139, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9140, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9141, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TalkedToCreature(C_SUNHAWK_TRIGGER, pCreature->GetGUID());
            break;
    }
    return true;
}

/*######
## npc_exarch_admetius
######*/

bool QuestAccept_npc_exarch_admetius(Player* pPlayer, Creature* pCreature, Quest const *quest)
{
    if (quest->GetQuestId() == 9756)
        pPlayer->AddAura(31609, pPlayer);
        
    return true;
}

/*######
## npc_razormaw
######*/

struct npc_razormawAI : public ScriptedAI
{
    npc_razormawAI(Creature* c) : ScriptedAI(c)
    {
        me->SetDisableGravity(true);
        me->GetMotionMaster()->MovePoint(1, -1204.845581, -12465.271484, 94.779945, false);
        me->SetKeepActive(true);
        landed = false;
    }
    
    bool landed;
    
    void Reset() override
    {
    }
    
    void MovementInform(uint32 type, uint32 id)
    override {
        if (id == 1) {
            me->SetKeepActive(false);
            me->SetDisableGravity(false);
            landed = true;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
        }
    }
    
    void EnterCombat(Unit* who) override
    {
        me->SetDisableGravity(false);
        me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        landed = true;
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!landed)
            return;
            
        if (!UpdateVictim(false))
            return;
            
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_razormaw(Creature* creature)
{
    return new npc_razormawAI(creature);
}

void AddSC_bloodmyst_isle()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name="mob_webbed_creature";
    newscript->GetAI = &GetAI_mob_webbed_creature;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_captured_sunhawk_agent";
    newscript->OnGossipHello =  &GossipHello_npc_captured_sunhawk_agent;
    newscript->OnGossipSelect = &GossipSelect_npc_captured_sunhawk_agent;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_exarch_admetius";
    newscript->OnQuestAccept = &QuestAccept_npc_exarch_admetius;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_razormaw";
    newscript->GetAI = &GetAI_npc_razormaw;
    sScriptMgr->RegisterOLDScript(newscript);
}

