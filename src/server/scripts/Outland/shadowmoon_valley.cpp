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
SDName: Shadowmoon_Valley
SD%Complete: 100
SDComment: Quest support: 10519, 10583, 10601, 10814, 10804, 10854, 10458, 10481, 10480, 11082, 10781, 10451. Vendor Drake Dealer Hurlunk.
SDCategory: Shadowmoon Valley
EndScriptData */

/* ContentData
mob_mature_netherwing_drake
mob_enslaved_netherwing_drake
npc_drake_dealer_hurlunk
npcs_flanis_swiftwing_and_kagrosh
npc_murkblood_overseer
npc_neltharaku
npc_oronok_tornheart
npc_overlord_morghor
npc_earthmender_wilda
mob_torloth_the_magnificent
mob_illidari_spawn
npc_lord_illidan_stormrage
go_crystal_prison
npc_enraged_spirit
npc_skartax
npc_invis_deathforge_caster
go_arcano_control_unit
npc_akama_prelude - quest 10944
npc_commander_arcus
npc_xiri
EndContentData */


#include "EscortAI.h"
#include "Pet.h"

/*#####
# mob_mature_netherwing_drake
#####*/

#define SPELL_PLACE_CARCASS             38439
#define SPELL_JUST_EATEN                38502
#define SPELL_NETHER_BREATH             38467

#define SAY_JUST_EATEN                  -1000222

struct mob_mature_netherwing_drakeAI : public ScriptedAI
{
    mob_mature_netherwing_drakeAI(Creature* c) : ScriptedAI(c)
    {
        PlayerGUID = 0;
    }

    uint64 PlayerGUID;

    bool IsEating;
    bool Evade;

    uint32 ResetTimer;
    uint32 CastTimer;
    uint32 EatTimer;

    void Reset()
    override {
        IsEating = false;
        Evade = false;

        ResetTimer = 120000;
        EatTimer = 5000;
        CastTimer = 5000;
    }

    void EnterCombat(Unit* who) override { }

    void MoveInLineOfSight(Unit* who)
    override {
        if(me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
            return;

        ScriptedAI::MoveInLineOfSight(who);
    }

    void SpellHit(Unit* caster, const SpellInfo* spell)
    override {
        if(!caster)
            return;

        if(caster->GetTypeId() == TYPEID_PLAYER && spell->Id == SPELL_PLACE_CARCASS && !me->HasAuraEffect(SPELL_JUST_EATEN, 0) && !PlayerGUID)
        {
            float PlayerX, PlayerY, PlayerZ;
            caster->GetClosePoint(PlayerX, PlayerY, PlayerZ, me->GetCombatReach());
            me->SetDisableGravity(true);
            me->GetMotionMaster()->MovePoint(1, PlayerX, PlayerY, PlayerZ);
            PlayerGUID = caster->GetGUID();
        }
    }

    void MovementInform(uint32 type, uint32 id)
    override {
        if(type != POINT_MOTION_TYPE)
            return;

        if(id == 1)
        {
            IsEating = true;
            EatTimer = 5000;
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_ATTACKUNARMED);
            me->SetDisableGravity(false);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(IsEating)
        {
            if(EatTimer < diff)
            {
                IsEating = false;
                DoCast(me, SPELL_JUST_EATEN);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                DoScriptText(SAY_JUST_EATEN, me);
                if(PlayerGUID)
                {
                    Player* plr = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                    if(plr && plr->GetQuestStatus(10804) == QUEST_STATUS_INCOMPLETE)
                    {
                        plr->KilledMonsterCredit(22131, me->GetGUID());
                        Evade = true;
                        PlayerGUID = 0;
                    }
                }
            } else { EatTimer -= diff; }
        }

        if(Evade)
        {
            if(ResetTimer < diff)
            {
                EnterEvadeMode();
                return;
            } else { ResetTimer -= diff; }
        }

        if(!UpdateVictim())
            return;

        if(CastTimer < diff)
        {
            DoCast(me->GetVictim(), SPELL_NETHER_BREATH);
            CastTimer = 5000;
        }else CastTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_mature_netherwing_drake(Creature *_creature)
{
    return new mob_mature_netherwing_drakeAI(_creature);
}

/*###
# mob_enslaved_netherwing_drake
####*/

#define FACTION_DEFAULT     62
#define FACTION_FRIENDLY    1840                            // Not sure if this is correct, it was taken off of Mordenai.

#define SPELL_HIT_FORCE_OF_NELTHARAKU   38762
#define SPELL_FORCE_OF_NELTHARAKU       38775

#define CREATURE_DRAGONMAW_SUBJUGATOR   21718
#define CREATURE_ESCAPE_DUMMY           22317

struct mob_enslaved_netherwing_drakeAI : public ScriptedAI
{
    mob_enslaved_netherwing_drakeAI(Creature* c) : ScriptedAI(c)
    {
        PlayerGUID = 0;
        Tapped = false;
    }

    uint64 PlayerGUID;
    uint32 FlyTimer;
    bool Tapped;

    void Reset()
    override {
        if(!Tapped)
            me->SetFaction(FACTION_DEFAULT);

        FlyTimer = 10000;
        me->SetDisableGravity(false);
        me->SetVisible(true);
    }

    void EnterCombat(Unit* who) override { }

    void SpellHit(Unit* caster, const SpellInfo* spell)
    override {
        if(!caster)
            return;

        if(caster->GetTypeId() == TYPEID_PLAYER && spell->Id == SPELL_HIT_FORCE_OF_NELTHARAKU && !Tapped)
        {
            Tapped = true;
            PlayerGUID = caster->GetGUID();

            me->SetFaction(FACTION_FRIENDLY);
            DoCast(caster, SPELL_FORCE_OF_NELTHARAKU, true);

            Unit* Dragonmaw = FindCreature(CREATURE_DRAGONMAW_SUBJUGATOR, 50, me);

            if(Dragonmaw)
            {
                me->AddThreat(Dragonmaw, 100000.0f);
                AttackStart(Dragonmaw);
            }

            HostileReference* ref = me->getThreatManager().getOnlineContainer().getReferenceByTarget(caster);
            if(ref)
                ref->removeReference();
        }
    }

    void MovementInform(uint32 type, uint32 id)
    override {
        if(type != POINT_MOTION_TYPE)
            return;

        if(id == 1)
        {
            if(PlayerGUID)
            {
                Unit* plr = ObjectAccessor::GetUnit((*me), PlayerGUID);
                if(plr)
                    DoCast(plr, SPELL_FORCE_OF_NELTHARAKU, true);

                PlayerGUID = 0;
            }
            me->SetVisible(false);
            me->SetDisableGravity(false);
            me->DespawnOrUnsummon();
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
        {
            if(Tapped)
            {
                if(FlyTimer < diff)
                {
                    Tapped = false;
                    if(PlayerGUID)
                    {
                        Player* plr = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                        if(plr && plr->GetQuestStatus(10854) == QUEST_STATUS_INCOMPLETE)
                        {
                            plr->KilledMonsterCredit(22316, me->GetGUID());

                            float dx, dy, dz;

                            Unit* EscapeDummy = FindCreature(CREATURE_ESCAPE_DUMMY, 30, me);
                            if(EscapeDummy)
                                EscapeDummy->GetPosition(dx, dy, dz);
                            else
                            {
                                me->GetRandomPoint(me, 20, dx, dy, dz);
                                dz += 25;
                            }

                            me->SetDisableGravity(true);
                            me->GetMotionMaster()->MovePoint(1, dx, dy, dz);
                        }
                    }
                }else FlyTimer -= diff;
            }
            return;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_enslaved_netherwing_drake(Creature* _Creature)
{
    return new mob_enslaved_netherwing_drakeAI(_Creature);
}

/*#####
# mob_dragonmaw_peon
#####*/

enum eDragonmawPeon {
    SPELL_KICK          = 34802,
    SPELL_SUNDER_ARMOR  = 15572
};

struct mob_dragonmaw_peonAI : public ScriptedAI
{
    mob_dragonmaw_peonAI(Creature* c) : ScriptedAI(c) {}

    uint64 PlayerGUID;
    bool Tapped;
    uint32 PoisonTimer;
    uint32 KickTimer, SunderArmorTimer;

    void Reset()
    override {
        SetCombatMovementAllowed(true);
        PlayerGUID = 0;
        Tapped = false;
        PoisonTimer = 0;
        KickTimer = 15000;
        SunderArmorTimer = 500;
    }

    void EnterCombat(Unit* who) override { }

    void SpellHit(Unit* caster, const SpellInfo* spell)
    override {
        if(!caster)
            return;

        if(caster->GetTypeId() == TYPEID_PLAYER && spell->Id == 40468 && !Tapped)
        {
            PlayerGUID = caster->GetGUID();

            Tapped = true;
            float x, y, z;
            caster->GetClosePoint(x, y, z, me->GetCombatReach());

            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            me->GetMotionMaster()->MovePoint(1, x, y, z);
        }
    }

    void MovementInform(uint32 type, uint32 id)
    override {
        if(type != POINT_MOTION_TYPE)
            return;

        if(id)
        {
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_EAT);
            PoisonTimer = 5000;
            SetCombatMovementAllowed(false);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(PoisonTimer)
        {
            if(PoisonTimer <= diff)
            {
                if(PlayerGUID)
                {
                    Player* plr = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                    if(plr && plr->GetQuestStatus(11020) == QUEST_STATUS_INCOMPLETE)
                        plr->KilledMonsterCredit(23209, me->GetGUID());
                }
                PoisonTimer = 0;
                me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
            } else PoisonTimer -= diff;
            
            return;
        }
        
        if(!UpdateVictim())
            return;
        
        if (KickTimer <= diff) {
            if (me->GetVictim()) {
                DoCast(me->GetVictim(), SPELL_KICK, false);
                KickTimer = 15000;
            }
        }else KickTimer -= diff;
        
        if (SunderArmorTimer <= diff) {
            if (me->GetVictim()) {
                DoCast(me->GetVictim(), SPELL_SUNDER_ARMOR, false);
                SunderArmorTimer = 8000;
            }
        }else SunderArmorTimer -= diff;
        
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_dragonmaw_peon(Creature* _Creature)
{
    return new mob_dragonmaw_peonAI(_Creature);
}

/*######
## npc_drake_dealer_hurlunk
######*/

bool GossipHello_npc_drake_dealer_hurlunk(Player *player, Creature *_Creature)
{
    if (_Creature->IsVendor() && player->GetReputationRank(1015) == REP_EXALTED)
        player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    SEND_PREPARED_GOSSIP_MENU(player, _Creature);

    return true;
}

bool GossipSelect_npc_drake_dealer_hurlunk(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_TRADE)
        player->SEND_VENDORLIST( _Creature->GetGUID() );

    return true;
}

/*######
## npc_flanis_swiftwing_and_kagrosh
######*/

#define GOSSIP_HSK1 "Take Flanis's Pack"
#define GOSSIP_HSK2 "Take Kagrosh's Pack"

bool GossipHello_npcs_flanis_swiftwing_and_kagrosh(Player *player, Creature *_Creature)
{
    if (player->GetQuestStatus(10583) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(30658,1,true))
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HSK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    if (player->GetQuestStatus(10601) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(30659,1,true))
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HSK2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    SEND_PREPARED_GOSSIP_MENU(player, _Creature);

    return true;
}

bool GossipSelect_npcs_flanis_swiftwing_and_kagrosh(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        ItemPosCountVec dest;
        uint8 msg = player->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest, 30658, 1);
        if( msg == EQUIP_ERR_OK )
        {
            player->StoreNewItem( dest, 30658, 1, true);
            player->PlayerTalkClass->ClearMenus();
        }
    }
    if (action == GOSSIP_ACTION_INFO_DEF+2)
    {
        ItemPosCountVec dest;
        uint8 msg = player->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest, 30659, 1);
        if( msg == EQUIP_ERR_OK )
        {
            player->StoreNewItem( dest, 30659, 1, true);
            player->PlayerTalkClass->ClearMenus();
        }
    }
    return true;
}

/*######
## npc_murkblood_overseer
######*/

#define QUEST_11082     11082

#define GOSSIP_HMO "I am here for you, overseer."
#define GOSSIP_SMO1 "How dare you question an overseer of the Dragonmaw!"
#define GOSSIP_SMO2 "Who speaks of me? What are you talking about, broken?"
#define GOSSIP_SMO3 "Continue please."
#define GOSSIP_SMO4 "Who are these bidders?"
#define GOSSIP_SMO5 "Well... yes."

bool GossipHello_npc_murkblood_overseer(Player *player, Creature *_Creature)
{
    if (player->GetQuestStatus(QUEST_11082) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HMO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    player->SEND_GOSSIP_MENU_TEXTID(10940, _Creature->GetGUID());
    return true;
}

bool GossipSelect_npc_murkblood_overseer(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SMO1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                                                            //correct id not known
            player->SEND_GOSSIP_MENU_TEXTID(10940, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SMO2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                                                            //correct id not known
            player->SEND_GOSSIP_MENU_TEXTID(10940, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SMO3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                                                            //correct id not known
            player->SEND_GOSSIP_MENU_TEXTID(10940, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SMO4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                                                            //correct id not known
            player->SEND_GOSSIP_MENU_TEXTID(10940, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SMO5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                                                            //correct id not known
            player->SEND_GOSSIP_MENU_TEXTID(10940, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
                                                            //correct id not known
            player->SEND_GOSSIP_MENU_TEXTID(10940, _Creature->GetGUID());
            _Creature->CastSpell(player,41121,false);
            player->AreaExploredOrEventHappens(QUEST_11082);
            break;
    }
    return true;
}

/*######
## npc_neltharaku
######*/

#define GOSSIP_HN "I am listening, dragon"
#define GOSSIP_SN1 "But you are dragons! How could orcs do this to you?"
#define GOSSIP_SN2 "Your mate?"
#define GOSSIP_SN3 "I have battled many beasts, dragon. I will help you."

bool GossipHello_npc_neltharaku(Player *player, Creature *_Creature)
{
    if (_Creature->IsQuestGiver())
        player->PrepareQuestMenu( _Creature->GetGUID() );

    if (player->GetQuestStatus(10814) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    player->SEND_GOSSIP_MENU_TEXTID(10613, _Creature->GetGUID());

    return true;
}

bool GossipSelect_npc_neltharaku(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SN1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->SEND_GOSSIP_MENU_TEXTID(10614, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SN2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            player->SEND_GOSSIP_MENU_TEXTID(10615, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SN3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            player->SEND_GOSSIP_MENU_TEXTID(10616, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            player->CLOSE_GOSSIP_MENU();
            player->AreaExploredOrEventHappens(10814);
            break;
    }
    return true;
}

/*######
## npc_oronok
######*/

#define GOSSIP_ORONOK1 "I am ready to hear your story, Oronok."
#define GOSSIP_ORONOK2 "How do I find the cipher?"
#define GOSSIP_ORONOK3 "How do you know all of this?"
#define GOSSIP_ORONOK4 "Yet what? What is it, Oronok?"
#define GOSSIP_ORONOK5 "Continue, please."
#define GOSSIP_ORONOK6 "So what of the cipher now? And your boys?"
#define GOSSIP_ORONOK7 "I will find your boys and the cipher, Oronok."

bool GossipHello_npc_oronok_tornheart(Player *player, Creature *_Creature)
{
    if (_Creature->IsQuestGiver())
        player->PrepareQuestMenu( _Creature->GetGUID() );
    if (_Creature->IsVendor())
        player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    if (player->GetQuestStatus(10519) == QUEST_STATUS_INCOMPLETE)
    {
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ORONOK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->SEND_GOSSIP_MENU_TEXTID(10312, _Creature->GetGUID());
    }else
        SEND_PREPARED_GOSSIP_MENU(player, _Creature);

    return true;
}

bool GossipSelect_npc_oronok_tornheart(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_TRADE:
            player->SEND_VENDORLIST( _Creature->GetGUID() );
            break;
        case GOSSIP_ACTION_INFO_DEF:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ORONOK2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU_TEXTID(10313, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ORONOK3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->SEND_GOSSIP_MENU_TEXTID(10314, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ORONOK4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            player->SEND_GOSSIP_MENU_TEXTID(10315, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ORONOK5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            player->SEND_GOSSIP_MENU_TEXTID(10316, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ORONOK6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            player->SEND_GOSSIP_MENU_TEXTID(10317, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ORONOK7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            player->SEND_GOSSIP_MENU_TEXTID(10318, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            player->CLOSE_GOSSIP_MENU();
            player->AreaExploredOrEventHappens(10519);
            break;
    }
    return true;
}

/*####
# npc_overlord_morghor
####*/

#define QUEST_LORD_ILLIDAN_STORMRAGE 11108

#define C_ILLIDAN 22083
#define C_YARZILL 23141

#define SPELL_RED_BOLT 39990 // Red Lightning Bolt
#define SPELL_MARK_OF_STORMRAGE 41528 // Mark of Stormrage

#define OVERLORD_SAY_1 -1000206
#define OVERLORD_SAY_2 -1000207
#define OVERLORD_SAY_3 -1000208
#define OVERLORD_SAY_4 -1000209
#define OVERLORD_SAY_5 -1000210
#define OVERLORD_SAY_6 -1000211

#define OVERLORD_YELL_1 -1000212
#define OVERLORD_YELL_2 -1000213

#define LORD_ILLIDAN_SAY_1 -1000214
#define LORD_ILLIDAN_SAY_2 -1000215
#define LORD_ILLIDAN_SAY_3 -1000216
#define LORD_ILLIDAN_SAY_4 -1000217
#define LORD_ILLIDAN_SAY_5 -1000218
#define LORD_ILLIDAN_SAY_6 -1000219
#define LORD_ILLIDAN_SAY_7 -1000220

#define YARZILL_THE_MERC_SAY -1000221

struct npc_overlord_morghorAI : public ScriptedAI
{
    npc_overlord_morghorAI(Creature *c) : ScriptedAI(c) {}

    uint64 PlayerGUID;
    uint64 IllidanGUID;

    uint32 ConversationTimer;
    uint32 Step;

    bool Event;

    void Reset()
    override {
        PlayerGUID = 0;
        IllidanGUID = 0;

        ConversationTimer = 0;
        Step = 0;

        Event = false;
        me->SetUInt32Value(UNIT_NPC_FLAGS, 2);
    }

    void EnterCombat(Unit* who)override {}

    void StartEvent()
    {
        me->SetUInt32Value(UNIT_NPC_FLAGS, 0);
        me->SetUInt32Value(UNIT_FIELD_BYTES_1,0);
        
        Unit* Illidan = me->SummonCreature(C_ILLIDAN, -5107.83, 602.584, 85.2393, 4.92598, TEMPSUMMON_CORPSE_DESPAWN, 0);
        if (Illidan) {
            IllidanGUID = Illidan->GetGUID();
            Illidan->SetVisible(false);
            Illidan->ToCreature()->SetReactState(REACT_PASSIVE);
            Illidan->SetFaction(FACTION_MONSTER);
            Illidan->SetMaxHealth(4200000);
            Illidan->SetHealth(Illidan->GetMaxHealth());
            Illidan->SetMaxPower(POWER_MANA, 1400000);
            Illidan->SetPower(POWER_MANA, Illidan->GetMaxPower(POWER_MANA));
        }
        
        if(PlayerGUID) {
            Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
            if(player)
                DoScriptText(OVERLORD_SAY_1, me, player);
        }

        ConversationTimer = 4200;
        Step = 0;
        Event = true;
    }

    uint32 NextStep(uint32 step)
    {
        Player* plr = ObjectAccessor::GetPlayer(*me, PlayerGUID);

        Unit* Illi = ObjectAccessor::GetUnit((*me), IllidanGUID);

        if (!plr || (!Illi && step < 23)) {
            EnterEvadeMode();
            return 0;
        }

        switch(step)
        {
        case 0:
            return 0;
        case 1:
            me->GetMotionMaster()->MovePoint(0, -5104.41, 595.297, 85.6838);
            return 9000;
        case 2:
            DoScriptText(OVERLORD_YELL_1, me, plr);
            return 4500;
        case 3:
            me->SetInFront(plr);
            return 3200;
        case 4:
            DoScriptText(OVERLORD_SAY_2, me, plr);
            return 2000;
        case 5:
            Illi->SetVisible(true);
            Illi->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            return 350;
        case 6:
            Illi->CastSpell(Illi, SPELL_RED_BOLT, true);
            Illi->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
            me->SetUInt64Value(UNIT_FIELD_TARGET, IllidanGUID);
            return 2000;
        case 7:
            DoScriptText(OVERLORD_YELL_2, me);
            return 4500;
        case 8:
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, 8);
            return 2500;
        case 9:
            DoScriptText(OVERLORD_SAY_3, me);
            return 6500;
        case 10:
            DoScriptText(LORD_ILLIDAN_SAY_1, Illi);
            return 5000;
        case 11:
            DoScriptText(OVERLORD_SAY_4, me, plr);
            return 6000;
        case 12:
            DoScriptText(LORD_ILLIDAN_SAY_2, Illi);
            return 5500;
        case 13:
            DoScriptText(LORD_ILLIDAN_SAY_3, Illi);
            return 4000;
        case 14:
            Illi->SetUInt64Value(UNIT_FIELD_TARGET, PlayerGUID);
            return 1500;
        case 15:
            DoScriptText(LORD_ILLIDAN_SAY_4, Illi);
            return 1500;
        case 16:
            if (plr) {
                plr->CastSpell(plr, SPELL_MARK_OF_STORMRAGE, true);
                return 5000;
            }
            else {
                Step = 30;
                return 100;
            }

            break;
        case 17:
            DoScriptText(LORD_ILLIDAN_SAY_5, Illi);
            return 5000;
        case 18: 
            DoScriptText(LORD_ILLIDAN_SAY_6, Illi);
            return 5000;
        case 19: 
            DoScriptText(LORD_ILLIDAN_SAY_7, Illi);
            return 5000;
        case 20:
            Illi->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
            Illi->SetDisableGravity(true);
            return 500;
        case 21:
            DoScriptText(OVERLORD_SAY_5, me);
            return 500;
        case 22:
            Illi->SetVisible(false);
            Illi->SetDeathState(JUST_DIED);
            return 1000;
        case 23: 
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
            return 2000;
        case 24: 
            me->SetUInt64Value(UNIT_FIELD_TARGET, PlayerGUID);
            return 5000;
        case 25: 
            DoScriptText(OVERLORD_SAY_6, me);
            return 2000;
        case 26:
            if (plr)
                plr->GroupEventHappens(QUEST_LORD_ILLIDAN_STORMRAGE, me);

            return 6000;
        case 27:
        {
            Unit* Yarzill = FindCreature(C_YARZILL, 50, me);
            if (Yarzill)
                Yarzill->SetUInt64Value(UNIT_FIELD_TARGET, PlayerGUID);

            return 500;
        }
        case 28:
            plr->RemoveAurasDueToSpell(SPELL_MARK_OF_STORMRAGE);
            plr->RemoveAurasDueToSpell(41519);

            return 1000;
        case 29:
        {
            Unit* Yarzill = FindCreature(C_YARZILL, 50, me);
            if(Yarzill)
                DoScriptText(YARZILL_THE_MERC_SAY, Yarzill, plr);
    
            return 5000;
        }
        case 30:
        {
            Unit* Yarzill = FindCreature(C_YARZILL, 50, me);
            if (Yarzill)
                Yarzill->SetUInt64Value(UNIT_FIELD_TARGET, 0);

            return 5000;
        }
        case 31:
        {
            std::vector<uint32> nodes;

            nodes.resize(2);
            nodes[0] = 173;                                     //from
            nodes[1] = 174;                                     //end at
            plr->ActivateTaxiPathTo(nodes);

            return 1000;
        }

        case 32:
            me->GetMotionMaster()->MovePoint(0, -5085.77, 577.231, 86.6719);
            return 5000;
        case 33:
            Reset();
            return 100;
        default:
            return 0;
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!ConversationTimer)
            return;

        if(ConversationTimer <= diff) {
            if(Event && IllidanGUID && PlayerGUID)
                ConversationTimer = NextStep(++Step);
        }
        else
            ConversationTimer -= diff;
    }
};

CreatureAI* GetAI_npc_overlord_morghorAI(Creature *_Creature)
{
return new npc_overlord_morghorAI(_Creature);
}

bool QuestAccept_npc_overlord_morghor(Player *player, Creature *_Creature, const Quest *_Quest )
{
    if(_Quest->GetQuestId() == QUEST_LORD_ILLIDAN_STORMRAGE)
    {
        ((npc_overlord_morghorAI*)_Creature->AI())->PlayerGUID = player->GetGUID();
        ((npc_overlord_morghorAI*)_Creature->AI())->StartEvent();
        return true;
    }
    return false;
}

/*####
# npc_earthmender_wilda
####*/

#define SAY_START -1000223
#define SAY_AGGRO1 -1000224
#define SAY_AGGRO2 -1000225
#define ASSASSIN_SAY_AGGRO1 -1000226
#define ASSASSIN_SAY_AGGRO2 -1000227
#define SAY_PROGRESS1 -1000228
#define SAY_PROGRESS2 -1000229
#define SAY_PROGRESS3 -1000230
#define SAY_PROGRESS4 -1000231
#define SAY_PROGRESS5 -1000232
#define SAY_PROGRESS6 -1000233
#define SAY_END -1000234

#define QUEST_ESCAPE_FROM_COILSKAR_CISTERN 10451
#define NPC_COILSKAR_ASSASSIN 21044

struct npc_earthmender_wildaAI : public npc_escortAI
{
    npc_earthmender_wildaAI(Creature *c) : npc_escortAI(c) {}

    bool Completed;

    void EnterCombat(Unit *who)
    override {
        Player* player = GetPlayerForEscort();

        if(who->GetTypeId() == TYPEID_UNIT && who->GetEntry() == NPC_COILSKAR_ASSASSIN)
            DoScriptText(SAY_AGGRO2, me, player);
        else DoScriptText(SAY_AGGRO1, me, player);
    }

    void Reset()
    override {
        me->SetFaction(1726);
        Completed = false;
    }

    void WaypointReached(uint32 i)
    override {
        Player* player = GetPlayerForEscort();

        if (!player)
            return;

        switch(i)
        {
               case 0: DoScriptText(SAY_START, me, player); break;
               case 13: DoScriptText(SAY_PROGRESS1, me, player);
                   SummonAssassin();
                   break;
               case 14: SummonAssassin(); break;
               case 15: DoScriptText(SAY_PROGRESS3, me, player); break;
               case 19:
                   switch(rand()%3)
                   {
                   case 0: DoScriptText(SAY_PROGRESS2, me, player); break;
                   case 1: DoScriptText(SAY_PROGRESS4, me, player); break;
                   case 2: DoScriptText(SAY_PROGRESS5, me, player); break;
                   }
                   break;
               case 20: SummonAssassin(); break;
               case 26:
                   switch(rand()%3)
                   {
                   case 0: DoScriptText(SAY_PROGRESS2, me, player); break;
                   case 1: DoScriptText(SAY_PROGRESS4, me, player); break;
                   case 2: DoScriptText(SAY_PROGRESS5, me, player); break;
                   }
                   break;
               case 27: SummonAssassin(); break;
               case 33:
                   switch(rand()%3)
                   {
                   case 0: DoScriptText(SAY_PROGRESS2, me, player); break;
                   case 1: DoScriptText(SAY_PROGRESS4, me, player); break;
                   case 2: DoScriptText(SAY_PROGRESS5, me, player); break;
                   }
                   break;
               case 34: SummonAssassin(); break;
               case 37:
                   switch(rand()%3)
                   {
                   case 0: DoScriptText(SAY_PROGRESS2, me, player); break;
                   case 1: DoScriptText(SAY_PROGRESS4, me, player); break;
                   case 2: DoScriptText(SAY_PROGRESS5, me, player); break;
                   }
                   break;
               case 38: SummonAssassin(); break;
               case 39: DoScriptText(SAY_PROGRESS6, me, player); break;
               case 43:
                   switch(rand()%3)
                   {
                   case 0: DoScriptText(SAY_PROGRESS2, me, player); break;
                   case 1: DoScriptText(SAY_PROGRESS4, me, player); break;
                   case 2: DoScriptText(SAY_PROGRESS5, me, player); break;
                   }
                   break;
               case 44: SummonAssassin(); break;
               case 50:
                   DoScriptText(SAY_END, me, player);
                   player->GroupEventHappens(QUEST_ESCAPE_FROM_COILSKAR_CISTERN, me);
                   Completed = true;
                   break;
               }
       }

       void SummonAssassin()
       {
           Player* player = GetPlayerForEscort();

           Unit* CoilskarAssassin = me->SummonCreature(NPC_COILSKAR_ASSASSIN, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0);
           if( CoilskarAssassin )
           {
               switch(rand()%2)
               {
               case 0: DoScriptText(ASSASSIN_SAY_AGGRO1, CoilskarAssassin, player); break;
               case 1: DoScriptText(ASSASSIN_SAY_AGGRO2, CoilskarAssassin, player); break;
               }
               (CoilskarAssassin->ToCreature())->AI()->AttackStart(me);
           }
           else error_log("TSCR ERROR: Coilskar Assassin couldn't be summmoned");
       }

       void JustDied(Unit* killer)
       override {
           if (PlayerGUID && !Completed)
           {
               Player* player = GetPlayerForEscort();
               if (player)
                   player->FailQuest(QUEST_ESCAPE_FROM_COILSKAR_CISTERN);
           }
       }

       void UpdateAI(const uint32 diff)
       override {
               npc_escortAI::UpdateAI(diff);
       }
};

CreatureAI* GetAI_npc_earthmender_wildaAI(Creature *pCreature)
{
    return new npc_earthmender_wildaAI(pCreature);
}

bool QuestAccept_npc_earthmender_wilda(Player* player, Creature* creature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_ESCAPE_FROM_COILSKAR_CISTERN)
    {
        creature->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
        ((npc_escortAI*)(creature->AI()))->Start(true, true, false, player->GetGUID(), creature->GetEntry());
    }
    return true;
}

/*#####
# Quest: Battle of the crimson watch
#####*/

/* ContentData
Battle of the crimson watch - creatures, gameobjects and defines
mob_illidari_spawn : Adds that are summoned in the Crimson Watch battle.
mob_torloth_the_magnificent : Final creature that players have to face before quest is completed
npc_lord_illidan_stormrage : Creature that controls the event.
go_crystal_prison : GameObject that begins the event and hands out quest
EndContentData */

#define END_TEXT -1000366

#define QUEST_BATTLE_OF_THE_CRIMSON_WATCH 10781
#define EVENT_AREA_RADIUS 65 //65yds
#define EVENT_COOLDOWN 30000 //in ms. appear after event completed or failed (should be = Adds despawn time)

struct TorlothCinematic
{
    int32 TextId;
    uint32 Creature, Timer;
};

// Creature 0 - Torloth, 1 - Illidan
static TorlothCinematic TorlothAnim[]=
{
    {-1000367, 0, 2000},
    {-1000368, 1, 7000},
    {-1000369, 0, 3000},
    {0, 0, 2000}, // Torloth stand
    {-1000370, 0, 1000},
    {0, 0, 3000},
    {0, 0, 0}
};

struct Location
{
    float x, y, z, o;
};

//Cordinates for Spawns
static Location SpawnLocation[]=
{
    //Cords used for:
    {-4615.8556f, 1342.2532f, 139.9f, 1.612f},//Illidari Soldier
    {-4598.9365f, 1377.3182f, 139.9f, 3.917f},//Illidari Soldier
    {-4598.4697f, 1360.8999f, 139.9f, 2.427f},//Illidari Soldier
    {-4589.3599f, 1369.1061f, 139.9f, 3.165f},//Illidari Soldier
    {-4608.3477f, 1386.0076f, 139.9f, 4.108f},//Illidari Soldier
    {-4633.1889f, 1359.8033f, 139.9f, 0.949f},//Illidari Soldier
    {-4623.5791f, 1351.4574f, 139.9f, 0.971f},//Illidari Soldier
    {-4607.2988f, 1351.6099f, 139.9f, 2.416f},//Illidari Soldier
    {-4633.7764f, 1376.0417f, 139.9f, 5.608f},//Illidari Soldier
    {-4600.2461f, 1369.1240f, 139.9f, 3.056f},//Illidari Mind Breaker
    {-4631.7808f, 1367.9459f, 139.9f, 0.020f},//Illidari Mind Breaker
    {-4600.2461f, 1369.1240f, 139.9f, 3.056f},//Illidari Highlord
    {-4631.7808f, 1367.9459f, 139.9f, 0.020f},//Illidari Highlord
    {-4615.5586f, 1353.0031f, 139.9f, 1.540f},//Illidari Highlord
    {-4616.4736f, 1384.2170f, 139.9f, 4.971f},//Illidari Highlord
    {-4627.1240f, 1378.8752f, 139.9f, 2.544f} //Torloth The Magnificent
};

struct WaveData
{
    uint8 SpawnCount, UsedSpawnPoint;
    uint32 CreatureId, SpawnTimer,YellTimer;
    int32 WaveTextId;
};

static WaveData WavesInfo[]=
{
    {9, 0, 22075, 10000, 7000, -1000371},   //Illidari Soldier
    {2, 9, 22074, 10000, 7000, -1000372},   //Illidari Mind Breaker
    {4, 11, 19797, 10000, 7000, -1000373},  //Illidari Highlord
    {1, 15, 22076, 10000, 7000, -1000374}   //Torloth The Magnificent
};

struct SpawnSpells
{
 uint32 Timer1, Timer2, SpellId;
};

static SpawnSpells SpawnCast[]=
{
    {10000, 15000, 35871},  // Illidari Soldier Cast - Spellbreaker
    {10000, 10000, 38985},  // Illidari Mind Breake Cast - Focused Bursts
    {35000, 35000, 22884},  // Illidari Mind Breake Cast - Psychic Scream
    {20000, 20000, 17194},  // Illidari Mind Breake Cast - Mind Blast
    {8000, 15000, 38010},   // Illidari Highlord Cast - Curse of Flames
    {12000, 20000, 16102},  // Illidari Highlord Cast - Flamestrike
    {10000, 15000, 15284},  // Torloth the Magnificent Cast - Cleave
    {18000, 20000, 39082},  // Torloth the Magnificent Cast - Shadowfury
    {25000, 28000, 33961}   // Torloth the Magnificent Cast - Spell Reflection
};

/*######
# mob_illidari_spawn
######*/

struct mob_illidari_spawnAI : public ScriptedAI
{
    mob_illidari_spawnAI(Creature* c) : ScriptedAI(c)
    {
        LordIllidanGUID = 0;
    }

    uint64 LordIllidanGUID;
    uint32 SpellTimer1, SpellTimer2, SpellTimer3;
    bool Timers;

    void Reset()
    override {
        Timers = false;
    }

    void EnterCombat(Unit* who) override {}
    void JustDied(Unit* slayer) override;

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
            return;

        if(!Timers)
        {
            if(me->GetEntry() == 22075)//Illidari Soldier
            {
                SpellTimer1 = SpawnCast[0].Timer1 + (rand()%4 * 1000);
            }
            if(me->GetEntry() == 22074)//Illidari Mind Breaker
            {
                SpellTimer1 = SpawnCast[1].Timer1 + (rand()%10 * 1000);
                SpellTimer2 = SpawnCast[2].Timer1 + (rand()%4 * 1000);
                SpellTimer3 = SpawnCast[3].Timer1 + (rand()%4 * 1000);
            }
            if(me->GetEntry() == 19797)// Illidari Highlord
            {
                SpellTimer1 = SpawnCast[4].Timer1 + (rand()%4 * 1000);
                SpellTimer2 = SpawnCast[5].Timer1 + (rand()%4 * 1000);
            }
            Timers = true;
        }
        //Illidari Soldier
        if(me->GetEntry() == 22075)
        {
            if(SpellTimer1 < diff)
            {
                DoCast(me->GetVictim(), SpawnCast[0].SpellId);//Spellbreaker
                SpellTimer1 = SpawnCast[0].Timer2 + (rand()%5 * 1000);
            }else SpellTimer1 -= diff;
        }
        //Illidari Mind Breaker
        if(me->GetEntry() == 22074)
        {
            if(SpellTimer1 < diff)
            {
                if(Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                {
                    if(target->GetTypeId() == TYPEID_PLAYER)
                    {
                        DoCast(target, SpawnCast[1].SpellId); //Focused Bursts
                        SpellTimer1 = SpawnCast[1].Timer2 + (rand()%5 * 1000);
                    }else SpellTimer1 = 2000;
                }
            }else SpellTimer1 -= diff;

            if(SpellTimer2 < diff)
            {
                DoCast(me->GetVictim(), SpawnCast[2].SpellId);//Psychic Scream
                SpellTimer2 = SpawnCast[2].Timer2 + (rand()%13 * 1000);
            }else SpellTimer2 -= diff;

            if(SpellTimer3 < diff)
            {
                DoCast(me->GetVictim(), SpawnCast[3].SpellId);//Mind Blast
                SpellTimer3 = SpawnCast[3].Timer2 + (rand()%8 * 1000);
            }else SpellTimer3 -= diff;
        }
        //Illidari Highlord
        if(me->GetEntry() == 19797)
        {
            if(SpellTimer1 < diff)
            {
                DoCast(me->GetVictim(), SpawnCast[4].SpellId);//Curse Of Flames
                SpellTimer1 = SpawnCast[4].Timer2 + (rand()%10 * 1000);
            }else SpellTimer1 -= diff;

            if(SpellTimer2 < diff)
            {
                DoCast(me->GetVictim(), SpawnCast[5].SpellId);//Flamestrike
                SpellTimer2 = SpawnCast[5].Timer2 + (rand()%7 * 13000);
            }else SpellTimer2 -= diff;
        }

        DoMeleeAttackIfReady();
    }
};

/*######
# mob_torloth_the_magnificent
#####*/

struct mob_torloth_the_magnificentAI : public ScriptedAI
{
    mob_torloth_the_magnificentAI(Creature* c) : ScriptedAI(c) {}

    uint32 AnimationTimer, SpellTimer1, SpellTimer2, SpellTimer3;

    uint8 AnimationCount;

    uint64 LordIllidanGUID;
    uint64 AggroTargetGUID;

    bool Timers;

    void Reset()
    override {
        AnimationTimer = 4000;
        AnimationCount = 0;
        LordIllidanGUID = 0;
        AggroTargetGUID = 0;
        Timers = false;

        me->AddUnitState(UNIT_STATE_ROOT);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->SetUInt64Value(UNIT_FIELD_TARGET, 0);
    }

    void EnterCombat(Unit* who)override {}

    void HandleAnimation()
    {
        Creature* pCreature = me;

        if(TorlothAnim[AnimationCount].Creature == 1)
        {
            pCreature = (ObjectAccessor::GetCreature(*me, LordIllidanGUID));

            if(!pCreature)
                return;
        }

        if(TorlothAnim[AnimationCount].TextId)
            DoScriptText(TorlothAnim[AnimationCount].TextId, pCreature);

        AnimationTimer = TorlothAnim[AnimationCount].Timer;

        switch(AnimationCount)
        {
        case 0:
            me->SetUInt32Value(UNIT_FIELD_BYTES_1,8);
            break;
        case 3:
            me->RemoveFlag(UNIT_FIELD_BYTES_1,8);
            break;
        case 5:
            if(Player* AggroTarget = (ObjectAccessor::GetPlayer(*me, AggroTargetGUID)))
            {
                me->SetUInt64Value(UNIT_FIELD_TARGET, AggroTarget->GetGUID());
                me->AddThreat(AggroTarget, 1);
                me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
            }
            break;
        case 6:
            if(Player* AggroTarget = (ObjectAccessor::GetPlayer(*me, AggroTargetGUID)))
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->ClearUnitState(UNIT_STATE_ROOT);

                float x, y, z;
                AggroTarget->GetPosition(x,y,z);
                me->GetMotionMaster()->MovePoint(0,x,y,z);
            }
            break;
        }
        ++AnimationCount;
    }

    void UpdateAI(const uint32 diff)
    override {
        if(AnimationTimer)
        {
            if(AnimationTimer <= diff)
            {
                HandleAnimation();
            }else AnimationTimer -= diff;
        }

        if(AnimationCount < 6)
        {
            me->CombatStop();
        }else if(!Timers)
        {

            SpellTimer1 = SpawnCast[6].Timer1;
            SpellTimer2 = SpawnCast[7].Timer1;
            SpellTimer3 = SpawnCast[8].Timer1;
            Timers = true;
        }

        if(Timers)
        {
            if(SpellTimer1 < diff)
            {
                DoCast(me->GetVictim(), SpawnCast[6].SpellId);//Cleave
                SpellTimer1 = SpawnCast[6].Timer2 + (rand()%10 * 1000);
            }else SpellTimer1 -= diff;

            if(SpellTimer2 < diff)
            {
                DoCast(me->GetVictim(), SpawnCast[7].SpellId);//Shadowfury
                SpellTimer2 = SpawnCast[7].Timer2 + (rand()%5 * 1000);
            }else SpellTimer2 -= diff;

            if(SpellTimer3 < diff)
            {
                DoCast(me, SpawnCast[8].SpellId);
                SpellTimer3 = SpawnCast[8].Timer2 + (rand()%7 * 1000);//Spell Reflection
            }else SpellTimer3 -= diff;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* slayer)
    override {
        if(slayer)
            switch(slayer->GetTypeId())
        {
            case TYPEID_UNIT:
                if((slayer->ToCreature())->IsPet() && ((Pet*)slayer)->GetOwner()->GetTypeId() == TYPEID_PLAYER)
                    ((Pet*)slayer)->GetOwner()->ToPlayer()->GroupEventHappens(QUEST_BATTLE_OF_THE_CRIMSON_WATCH, me);
                break;

            case TYPEID_PLAYER:
                (slayer->ToPlayer())->GroupEventHappens(QUEST_BATTLE_OF_THE_CRIMSON_WATCH, me);
                break;
        }

        if(Creature* LordIllidan = (ObjectAccessor::GetCreature(*me, LordIllidanGUID)))
        {
            DoScriptText(END_TEXT, LordIllidan, slayer);
            LordIllidan->AI()->EnterEvadeMode();
        }
    }
};

/*#####
# npc_lord_illidan_stormrage
#####*/

struct npc_lord_illidan_stormrageAI : public ScriptedAI
{
    npc_lord_illidan_stormrageAI(Creature* c) : ScriptedAI(c) {}

    uint64 PlayerGUID;

    uint32 WaveTimer;
    uint32 AnnounceTimer;

    int8 LiveCount;
    uint8 WaveCount;

    bool EventStarted;
    bool Announced;
    bool Failed;

    void Reset()
    override {
        PlayerGUID = 0;

        WaveTimer = 10000;
        AnnounceTimer = 7000;
        LiveCount = 0;
        WaveCount = 0;

        EventStarted = false;
        Announced = false;
        Failed = false;

        me->SetVisible(false);
    }

    void EnterCombat(Unit* who) override {}
    void MoveInLineOfSight(Unit* who) override {}
    void AttackStart(Unit* who) override {}

    void SummonNextWave()
    {
        uint8 count = WavesInfo[WaveCount].SpawnCount;
        uint8 locIndex = WavesInfo[WaveCount].UsedSpawnPoint;
        srand(time(nullptr));//initializing random seed
        uint8 FelguardCount = 0;
        uint8 DreadlordCount = 0;

        for(uint8 i = 0; i < count; ++i)
        {
            Creature* Spawn = nullptr;
            float X = SpawnLocation[locIndex + i].x;
            float Y = SpawnLocation[locIndex + i].y;
            float Z = SpawnLocation[locIndex + i].z;
            float O = SpawnLocation[locIndex + i].o;
            Spawn = me->SummonCreature(WavesInfo[WaveCount].CreatureId, X, Y, Z, O, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
            ++LiveCount;

            if(Spawn)
            {
                Spawn->InitCreatureAddon(true);

                if(WaveCount == 0)//1 Wave
                {
                    if(rand()%3 == 1 && FelguardCount<2)
                    {
                        Spawn->SetUInt32Value(UNIT_FIELD_DISPLAYID,18654);
                        ++FelguardCount;
                    }
                    else if(DreadlordCount < 3)
                    {
                        Spawn->SetUInt32Value(UNIT_FIELD_DISPLAYID,19991);
                        ++DreadlordCount;
                    }
                    else if(FelguardCount<2)
                    {
                        Spawn->SetUInt32Value(UNIT_FIELD_DISPLAYID,18654);
                        ++FelguardCount;
                    }
                }

                if(WaveCount < 3)//1-3 Wave
                {
                    if(PlayerGUID)
                    {
                        if(Player* pTarget = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                        {
                            float x, y, z;
                            pTarget->GetPosition(x,y,z);
                            Spawn->GetMotionMaster()->MovePoint(0,x, y, z);
                        }
                    }
                    ((mob_illidari_spawnAI*)Spawn->AI())->LordIllidanGUID = me->GetGUID();
                }

                if(WavesInfo[WaveCount].CreatureId == 22076) // Torloth
                {
                    ((mob_torloth_the_magnificentAI*)Spawn->AI())->LordIllidanGUID = me->GetGUID();
                    if(PlayerGUID)
                        ((mob_torloth_the_magnificentAI*)Spawn->AI())->AggroTargetGUID = PlayerGUID;
                }
            }
        }
        ++WaveCount;
        WaveTimer = WavesInfo[WaveCount].SpawnTimer;
        AnnounceTimer = WavesInfo[WaveCount].YellTimer;
    }
    
    void SummonedCreatureDespawn(Creature* creature)
    override {
        LiveCounter();
    }

    void CheckEventFail()
    {
        Player* pPlayer = ObjectAccessor::GetPlayer(*me, PlayerGUID);

        if (!pPlayer) {
            Failed = true;
            EventStarted = false;
            EnterEvadeMode();
            
            return;
        }

        if(Group *EventGroup = pPlayer->GetGroup())
        {
            Player* GroupMember;

            uint8 GroupMemberCount = 0;
            uint8 DeadMemberCount = 0;
            uint8 FailedMemberCount = 0;

            const Group::MemberSlotList members = EventGroup->GetMemberSlots();

            for(const auto & member : members)
            {
                GroupMember = (ObjectAccessor::GetPlayer(*me, member.guid));
                if(!GroupMember)
                    continue;
                if(!GroupMember->IsWithinDistInMap(me, EVENT_AREA_RADIUS) && GroupMember->GetQuestStatus(QUEST_BATTLE_OF_THE_CRIMSON_WATCH) == QUEST_STATUS_INCOMPLETE)
                {
                    GroupMember->FailQuest(QUEST_BATTLE_OF_THE_CRIMSON_WATCH);
                    GroupMember->SetQuestStatus(QUEST_BATTLE_OF_THE_CRIMSON_WATCH, QUEST_STATUS_NONE);
                    ++FailedMemberCount;
                }
                ++GroupMemberCount;

                if(GroupMember->IsDead())
                {
                    ++DeadMemberCount;
                }
            }

            if(GroupMemberCount == FailedMemberCount)
            {
                Failed = true;
            }

            if(GroupMemberCount == DeadMemberCount)
            {
                for(const auto & member : members)
                {
                    GroupMember = ObjectAccessor::GetPlayer(*me, member.guid);

                    if(GroupMember && GroupMember->GetQuestStatus(QUEST_BATTLE_OF_THE_CRIMSON_WATCH) == QUEST_STATUS_INCOMPLETE)
                    {
                        GroupMember->FailQuest(QUEST_BATTLE_OF_THE_CRIMSON_WATCH);
                        GroupMember->SetQuestStatus(QUEST_BATTLE_OF_THE_CRIMSON_WATCH, QUEST_STATUS_NONE);
                    }
                }
                Failed = true;
            }
        }else if (pPlayer->IsDead() || !pPlayer->IsWithinDistInMap(me, EVENT_AREA_RADIUS))
        {
            pPlayer->FailQuest(QUEST_BATTLE_OF_THE_CRIMSON_WATCH);
            Failed = true;
            EventStarted = false;
        }
    }

    void LiveCounter()
    {
        --LiveCount;
        if(!LiveCount)
            Announced = false;
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!PlayerGUID || !EventStarted)
            return;

        if(!LiveCount && WaveCount < 4)
        {
            if(!Announced && AnnounceTimer < diff)
            {
                DoScriptText(WavesInfo[WaveCount].WaveTextId, me);
                Announced = true;
            }else AnnounceTimer -= diff;

            if(WaveTimer < diff)
            {
                SummonNextWave();
            }else WaveTimer -= diff;
        }
        CheckEventFail();

        if (Failed)
            EnterEvadeMode();
    }
};

void mob_illidari_spawnAI::JustDied(Unit *slayer)
{
    me->RemoveCorpse();
}

class CrystalPrison : public GameObjectScript
{
public:
    CrystalPrison() : GameObjectScript("go_crystal_prison")
    {}

    bool OnQuestAccept(Player* plr, GameObject* go, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_BATTLE_OF_THE_CRIMSON_WATCH)
        {
            Unit* Illidan = FindCreature(22083, 50, plr);

            if (Illidan && !(((npc_lord_illidan_stormrageAI*)(Illidan->ToCreature())->AI())->EventStarted))
            {
                ((npc_lord_illidan_stormrageAI*)(Illidan->ToCreature())->AI())->PlayerGUID = plr->GetGUID();
                ((npc_lord_illidan_stormrageAI*)(Illidan->ToCreature())->AI())->LiveCount = 0;
                ((npc_lord_illidan_stormrageAI*)(Illidan->ToCreature())->AI())->EventStarted = true;
            }
        }
        return true;
    }
};

CreatureAI* GetAI_npc_lord_illidan_stormrage(Creature* c)
{
    return new npc_lord_illidan_stormrageAI(c);
}

CreatureAI* GetAI_mob_illidari_spawn(Creature* c)
{
    return new mob_illidari_spawnAI(c);
}

CreatureAI* GetAI_mob_torloth_the_magnificent(Creature* c)
{
    return new mob_torloth_the_magnificentAI(c);
}

/*####
# npc_enraged_spirits
####*/

/* QUESTS */
#define QUEST_ENRAGED_SPIRITS_FIRE_EARTH 10458
#define QUEST_ENRAGED_SPIRITS_AIR 10481
#define QUEST_ENRAGED_SPIRITS_WATER 10480

/* Totem */
#define ENTRY_TOTEM_OF_SPIRITS 21071
#define RADIUS_TOTEM_OF_SPIRITS 15

/* SPIRITS */
#define ENTRY_ENRAGED_EARTH_SPIRIT 21050
#define ENTRY_ENRAGED_FIRE_SPIRIT 21061
#define ENTRY_ENRAGED_AIR_SPIRIT 21060
#define ENTRY_ENRAGED_WATER_SPIRIT 21059

/* SOULS */
#define ENTRY_EARTHEN_SOUL 21073
#define ENTRY_FIERY_SOUL 21097
#define ENTRY_ENRAGED_AIRY_SOUL 21116
#define ENTRY_ENRAGED_WATERY_SOUL 21109  // wrong model

/* SPELL KILLCREDIT - not working!?! - using KilledMonster */
#define SPELL_EARTHEN_SOUL_CAPTURED_CREDIT 36108
#define SPELL_FIERY_SOUL_CAPTURED_CREDIT 36117
#define SPELL_AIRY_SOUL_CAPTURED_CREDIT 36182
#define SPELL_WATERY_SOUL_CAPTURED_CREDIT 36171

/* KilledMonster Workaround */
#define CREDIT_FIRE 21094
#define CREDIT_WATER 21095
#define CREDIT_AIR 21096
#define CREDIT_EARTH 21092

/* Captured Spell/Buff */
#define SPELL_SOUL_CAPTURED 36115

/* Factions */
#define ENRAGED_SOUL_FRIENDLY 35
#define ENRAGED_SOUL_HOSTILE 14

struct npc_enraged_spiritAI : public ScriptedAI
{
    npc_enraged_spiritAI(Creature *c) : ScriptedAI(c) {}

    void Reset()   override { }

    void EnterCombat(Unit *who)override {}

    void JustDied(Unit* killer)
    override {
        // always spawn spirit on death
        // if totem around
        // move spirit to totem and cast kill count
        uint32 entry = 0;
        uint32 credit = 0;

        switch(me->GetEntry()) {
          case ENTRY_ENRAGED_FIRE_SPIRIT:
            entry  = ENTRY_FIERY_SOUL;
            //credit = SPELL_FIERY_SOUL_CAPTURED_CREDIT;
            credit = CREDIT_FIRE;
          break;
          case ENTRY_ENRAGED_EARTH_SPIRIT:
            entry  = ENTRY_EARTHEN_SOUL;
            //credit = SPELL_EARTHEN_SOUL_CAPTURED_CREDIT;
            credit = CREDIT_EARTH;
          break;
          case ENTRY_ENRAGED_AIR_SPIRIT:
            entry  = ENTRY_ENRAGED_AIRY_SOUL;
            //credit = SPELL_AIRY_SOUL_CAPTURED_CREDIT;
            credit = CREDIT_AIR;
          break;
          case ENTRY_ENRAGED_WATER_SPIRIT:
            entry  = ENTRY_ENRAGED_WATERY_SOUL;
            //credit = SPELL_WATERY_SOUL_CAPTURED_CREDIT;
            credit = CREDIT_WATER;
          break;
        }

        // Spawn Soul on Kill ALWAYS!
        Creature* Summoned = nullptr;
        Unit* totemOspirits = nullptr;

        if ( entry != 0 )
            Summoned = DoSpawnCreature(entry, 0, 0, 1, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 5000);

        // FIND TOTEM, PROCESS QUEST
        if (Summoned)
        {
             totemOspirits = FindCreature(ENTRY_TOTEM_OF_SPIRITS, RADIUS_TOTEM_OF_SPIRITS, me);
             if (totemOspirits)
             {
                 Summoned->SetFaction(ENRAGED_SOUL_FRIENDLY);
                 Summoned->GetMotionMaster()->MovePoint(0,totemOspirits->GetPositionX(), totemOspirits->GetPositionY(), Summoned->GetPositionZ());

                 Player* Owner = totemOspirits->GetOwner()->ToPlayer();
                 if (Owner)
                     // DoCast(Owner, credit); -- not working!
                     Owner->KilledMonsterCredit(credit, Summoned->GetGUID());
                 DoCast(totemOspirits,SPELL_SOUL_CAPTURED);
             }
        }
    }
};

CreatureAI* GetAI_npc_enraged_spirit(Creature *_Creature)
{
return new npc_enraged_spiritAI(_Creature);
}

/*######
## npc_spirits_totem
######*/

struct npc_spirits_totemAI : public ScriptedAI
{
    npc_spirits_totemAI(Creature* c) : ScriptedAI(c) {}
    
    uint32 checkTimer;
    
    void Reset()
    override {
        me->SetReactState(REACT_PASSIVE);
        checkTimer = 1000;
    }
    
    void EnterCombat(Unit* who) override {}
    
    void UpdateAI(uint32 const diff)
    override {
        uint32 souls[] = {21073, 21097, 21116, 21109}, credits[] = {21092, 21094, 21096, 21095};
    
        if (!me->GetOwner())
            return;
            
        if (!me->GetOwner()->ToPlayer())
            return;

        if (checkTimer <= diff) {
            for (uint8 i = 0; i < 4; i++) {
                if (Creature* soul = me->FindNearestCreature(souls[i], 30.0f, true)) {
                    me->GetOwner()->ToPlayer()->KilledMonsterCredit(credits[i], soul->GetGUID());
                    DoCast(me, SPELL_SOUL_CAPTURED);
                    soul->DisappearAndDie();
                }
            }
            
            checkTimer = 1000;
        }
        else
            checkTimer -= diff;
    }
};

CreatureAI* GetAI_npc_spirits_totem(Creature* creature)
{
    return new npc_spirits_totemAI(creature);
}

/*######
## npc_skartax
######*/

#define SPELL_PURPLE_BEAM        36384
#define SPELL_AUTO_AURA            36382
#define SPELL_SHADOWBOLT        12471
#define SPELL_INCINERATE        38401

struct npc_skartaxAI : public ScriptedAI
{
    npc_skartaxAI(Creature *c) : ScriptedAI(c) {}
    
    uint32 SummonTimer;
    uint32 ShadowBoltTimer;
    uint32 IncinerateTimer;
    
    void Reset()
    override {
        me->AddAura(SPELL_AUTO_AURA, me);
        DoCast(me, SPELL_PURPLE_BEAM);
        
        SummonTimer = 2000;
        ShadowBoltTimer = 2000;
        IncinerateTimer = 500;
    }
    void EnterCombat(Unit *pWho)
    override {
        me->InterruptNonMeleeSpells(true);
        me->RemoveAurasDueToSpell(SPELL_AUTO_AURA);
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (SummonTimer <= diff) {
            me->SummonCreature(19757, -3368.94, 2145.35, -8.28, 0.382, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 180000);
            SummonTimer = 180000;
        }
        else
            SummonTimer -= diff;
            
        if (ShadowBoltTimer <= diff) {
            DoCast(me->GetVictim(), SPELL_SHADOWBOLT);
            ShadowBoltTimer = 5000;
        }
        else
            ShadowBoltTimer -= diff;
            
        if (IncinerateTimer <= diff) {
            DoCast(me->GetVictim(), SPELL_INCINERATE);
            IncinerateTimer = 10000;
        }
        else
            IncinerateTimer -= diff;
            
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_skartax(Creature *pCreature)
{
    return new npc_skartaxAI(pCreature);
}

/*######
## npc_invis_deathforge_caster
######*/

struct npc_invis_deathforge_casterAI : public ScriptedAI
{
    npc_invis_deathforge_casterAI(Creature *c) : ScriptedAI(c) {}
    
    void EnterCombat(Unit *pWho) override {}
    
    void UpdateAI(uint32 const diff)
    override {
        if (Creature *pTarget = me->FindNearestCreature(21207, 30.0f)) {
            if (!pTarget->HasAuraEffect(36384))
                DoCast(pTarget, 36384);
        }
    }
};

CreatureAI* GetAI_npc_invis_deathforge_caster(Creature *pCreature)
{
    return new npc_invis_deathforge_casterAI(pCreature);
}

class ArcanoControlUnit : public GameObjectScript
{
public:
    ArcanoControlUnit() : GameObjectScript("go_arcano_control_unit")
    {}

    bool OnGossipHello(Player* pPlayer, GameObject* _GO) override
    {
        if (Creature *pCreature = pPlayer->FindNearestCreature(21909, 25.0f)) {
            pPlayer->CastSpell(pCreature, 37868, true);
            pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            return true;
        }

        return false;
    }
};

/*######
## npc_quest_spectrecles
######*/

/* Alliance quests : 10643 (item 30719) - 10644 (item 30721)
   Horde quests : 10625 (item 30719), 10633 (item 30721)
   */
bool GossipHello_npc_quest_spectrecles(Player* player, Creature* creature)
{
    if (creature->IsQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    const char* lostText = "J'ai perdu mes Lunectoplasmes";
    
    if (player->GetQuestStatus(10625) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(30719, 1, true))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, lostText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
    if (player->GetQuestStatus(10643) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(30719, 1, true))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, lostText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
    if (player->GetQuestStatus(10633) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(30721, 1, true))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, lostText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    if (player->GetQuestStatus(10644) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(30721, 1, true))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, lostText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    SEND_PREPARED_GOSSIP_MENU(player, creature);

    return true;
}

bool GossipSelect_npc_quest_spectrecles(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF) {
        player->CastSpell(player, 37602, true); //        Replace Lost Spectrecles T1
    }
    else if (action == GOSSIP_ACTION_INFO_DEF + 1) {
        player->CastSpell(player, 37700, true); //        Replace Lost Spectrecles T2
    }
    
    player->CLOSE_GOSSIP_MENU();
    
    return true;
}

/*######
## npc_akama_prelude
######*/

/*
TODO
* change olum modelid
*/

enum akamaPreludeData {
    QUEST_SECRET_COMPROMISED    = 10944,
    
    NPC_SEER_OLUM               = 22820,
    NPC_OLUM_SPIRIT             = 22870,
    NPC_ILLIDAN_PRESENCE        = 22865,
    
    SPELL_OLUM_SACRIFICE        = 39552,
    SPELL_SHADOWFORM            = 40973,
    SPELL_KNEEL                 = 39656,
   
    SAY_OLUM_1          = -1000729,
    SAY_AKAMA_1         = -1000730,
    SAY_OLUM_2          = -1000731,
    SAY_AKAMA_2         = -1000732,
    SAY_OLUM_3          = -1000733,
    SAY_AKAMA_3         = -1000734,
    SAY_OLUM_4          = -1000735,
    SAY_AKAMA_4         = -1000736,
    SAY_OLUM_5          = -1000737,
    SAY_AKAMA_5         = -1000738,
    SAY_AKAMA_6         = -1000739,
    SAY_ILLIDAN_1       = -1000740,
    SAY_AKAMA_7         = -1000741,
    SAY_ILLIDAN_2       = -1000742,
    SAY_ILLIDAN_3       = -1000743,
    SAY_AKAMA_8         = -1000744
};

struct npc_akama_preludeAI : public ScriptedAI
{
    npc_akama_preludeAI(Creature* c) : ScriptedAI(c)
    {
        eventTimer = 0;
        step = 0;
        talkId = 0;
        olumGUID = 0;
        presenceGUID = 0;
    }
    
    uint64 olumGUID;
    uint64 presenceGUID;
    
    uint32 eventTimer;
    int32 talkId;

    uint8 step;
    
    void Reset() override {}
    
    void EnterCombat(Unit* who) override {}
    
    void StartEvent()
    {
        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
        eventTimer = 500;
        step = 0;
        talkId = 0;
        olumGUID = 0;
        presenceGUID = 0;
    }
    
    void EndEvent()
    {
        if (Creature* presence = ObjectAccessor::GetCreature(*me, presenceGUID))
            presence->DisappearAndDie();

        me->RemoveAurasDueToSpell(SPELL_KNEEL);
        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
        eventTimer = 0;
        step = 0;
        talkId = 0;
        olumGUID = 0;
        presenceGUID = 0;
    }
    
    void OnSpellFinish(Unit* caster, uint32 spellId, Unit* target, bool ok)
    override {
        if (spellId == SPELL_OLUM_SACRIFICE) {
            me->Kill(target);
            if (Creature* spirit = me->SummonCreature(NPC_OLUM_SPIRIT, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), target->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 16000)) {
                spirit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                spirit->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
                spirit->GetMotionMaster()->MovePoint(0, spirit->GetPositionX(), spirit->GetPositionY(), spirit->GetPositionZ() + 4.0f, false);
            }
        }
    }
    
    void MovementInform(uint32 type, uint32 id)
    override {
        if (id == 0) {
            if (Creature* olum = ObjectAccessor::GetCreature(*me, olumGUID))
                DoCast(olum, SPELL_OLUM_SACRIFICE);
        }
    }
    
    uint32 NextStep()
    {
        uint32 timer = 0;

        switch (step) {
        case 0:
            if (olumGUID)
                break;

            if (Creature* olum = me->SummonCreature(NPC_SEER_OLUM, -3729.779541, 1037.054443, 55.956562, 5.667850, TEMPSUMMON_MANUAL_DESPAWN, 0)) {
                olumGUID = olum->GetGUID();
                DoScriptText(SAY_OLUM_1, olum, nullptr);
                olum->GetMotionMaster()->MovePoint(0, -3722.463867, 1032.153564, 55.956562);
                olum->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            }

            timer = 11000;
            break;
        case 1:
            DoScriptText(SAY_AKAMA_1, me, nullptr);
            timer = 4500;
            break;
        case 2:
            if (Creature* olum = ObjectAccessor::GetCreature(*me, olumGUID))
                DoScriptText(SAY_OLUM_2, olum, nullptr);
                
            timer = 7000;
            break;
        case 3:
            DoScriptText(SAY_AKAMA_2, me, nullptr);
            timer = 6500;
            break;
        case 4:
            if (Creature* olum = ObjectAccessor::GetCreature(*me, olumGUID))
                DoScriptText(SAY_OLUM_3, olum, nullptr);
                
            timer = 26000;
            break;
        case 5:
            DoScriptText(SAY_AKAMA_3, me, nullptr);
            timer = 6500;
            break;
        case 6:
            if (Creature* olum = ObjectAccessor::GetCreature(*me, olumGUID))
                DoScriptText(SAY_OLUM_4, olum, nullptr);
                
            timer = 14000;
            break;
        case 7:
            DoScriptText(SAY_AKAMA_4, me, nullptr);
            timer = 9500;
            break;
        case 8:
            if (Creature* olum = ObjectAccessor::GetCreature(*me, olumGUID))
                DoScriptText(SAY_OLUM_5, olum, nullptr);
                
            timer = 15000;
            break;
        case 9: // Akama moves to kill Olum
            me->GetMotionMaster()->MovePoint(0, -3718.926514, 1030.366211, 55.956562);
            timer = 14000;
            break;
        case 10:
            DoScriptText(SAY_AKAMA_5, me, nullptr);
            timer = 13000;
            break;
        case 11:
            me->GetMotionMaster()->MoveTargetedHome();
            timer = 5000;
            break;
        case 12:
            DoScriptText(SAY_AKAMA_6, me, nullptr);
            DoCast(me, SPELL_KNEEL, true);
            if (Creature* presence = me->SummonCreature(NPC_ILLIDAN_PRESENCE, -3724.522705, 1029.824463, 55.955868, 6.259977, TEMPSUMMON_MANUAL_DESPAWN, 0)) {
                presenceGUID = presence->GetGUID();
                presence->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                presence->CastSpell(presence, SPELL_SHADOWFORM, true);
                presence->SetReactState(REACT_PASSIVE);
            }
                
            timer = 9000;
            break;
        case 13:
            if (Creature* presence = ObjectAccessor::GetCreature(*me, presenceGUID))
                DoScriptText(SAY_ILLIDAN_1, presence, nullptr);
            
            timer = 13000;
            break;
        case 14:
            if (Creature* olum = ObjectAccessor::GetCreature(*me, olumGUID))
                olum->DisappearAndDie();

            DoScriptText(SAY_AKAMA_7, me, nullptr);
            timer = 18000;
            break;
        case 15:
            if (Creature* presence = ObjectAccessor::GetCreature(*me, presenceGUID))
                DoScriptText(SAY_ILLIDAN_2, presence, nullptr);
            
            timer = 20000;
            break;
        case 16:
            if (Creature* presence = ObjectAccessor::GetCreature(*me, presenceGUID))
                DoScriptText(SAY_ILLIDAN_3, presence, nullptr);
            
            timer = 21500;
            break;
        case 17:
            DoScriptText(SAY_AKAMA_8, me, nullptr);
            timer = 2500;
            break;
        case 18:
            EndEvent();
            return 0;
        }
        
        step++;
        return timer;
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!eventTimer)
            return;
            
        if (eventTimer <= diff)
            eventTimer = NextStep();
        else
            eventTimer -= diff;
    }
};

CreatureAI* GetAI_npc_akama_prelude(Creature* creature)
{
    return new npc_akama_preludeAI(creature);
}

bool ChooseReward_npc_akama_prelude(Player* player, Creature* creature, Quest const* quest, uint32 opt)
{
    if (quest->GetQuestId() == QUEST_SECRET_COMPROMISED)
        ((npc_akama_preludeAI*)creature->AI())->StartEvent();
    
    return true;
}

/*######
## Quests 11101 && 11097
######*/

#define QUEST_DEADLIEST_TRAP_ALDOR  11101
#define QUEST_DEADLIEST_TRAP_SCYER  11097

#define COMMANDER_HOBB_SAY1         -1000745
#define COMMANDER_HOBB_SAY2         -1000746
#define COMMANDER_HOBB_SAY3         -1000756
#define SKYBREAKER_SAY1             -1000747
#define SKYBREAKER_SAY2             -1000748
#define SKYBREAKER_SAY3             -1000749
#define SKYBREAKER_SAYALDOR1        -1000750
#define SKYBREAKER_SAYALDOR2        -1000751
#define SKYBREAKER_SAYSCYER1        -1000752
#define SKYBREAKER_SAYSCYER2        -1000753
#define COMMANDER_ARCUS_SAY1        -1000754
#define COMMANDER_ARCUS_SAY2        -1000755
#define COMMANDER_ARCUS_SAY3         -1000757

#define SPELL_AIMED_SHOT            38370
#define SPELL_MULTI_SHOT            41448
#define SPELL_SHOOT                 41440

#define NPC_DRAGONMAW_SKYBREAKER_SCYER  23440
#define NPC_DRAGONMAW_SKYBREAKER_ALDOR  23441

#define NPC_DEFENDER_SCYER              23435
#define NPC_DEFENDER_ALDOR              23453

float skybreakerPosAldor[10][3] = {
    { -3150.351807, 756.830444, 37.261200 },
    { -3158.962646, 745.880676, 37.261200 },
    { -3170.083252, 731.739441, 37.261200 },
    { -3176.036865, 716.404663, 37.261200 },
    { -3179.811768, 706.681763, 37.261200 },
    { -3183.206543, 697.937683, 37.261200 },
    { -3185.165039, 684.075378, 37.261200 },
    { -3186.469482, 674.786499, 37.261200 },
    { -3187.608398, 666.676086, 37.261200 },
    { -3128.346436, 763.912537, 37.261200 }};

float skybreakerPosScyer[10][3] = {
    { -4080.790527, 970.862976, 79.887848 },
    { -4067.590820, 974.339661, 79.887848 },
    { -4053.443359, 978.065979, 79.887848 },
    { -4041.665039, 981.168274, 79.887848 },
    { -4027.382080, 984.930298, 79.887848 },
    { -4016.010010, 987.925659, 79.887848 },
    { -4007.221436, 1001.788818, 77.243546 },
    { -3996.254883, 1010.603210, 77.243546 },
    { -3985.991211, 1031.524292, 74.557518 },
    { -4114.185059, 975.281982, 74.557518 }};
    
// Orientation 2.337
float defendersPosAldor[10][3] = {
    { -3081.971924, 700.679260, -16.377661 },
    { -3083.283691, 697.540344, -16.844158 },
    { -3084.743896, 694.046204, -17.461650 },
    { -3085.826416, 691.456299, -17.954538 },
    { -3086.954834, 688.756592, -18.279066 },
    { -3088.004883, 686.244202, -18.166872 },
    { -3089.394043, 682.920410, -17.503175 },
    { -3093.030029, 677.387085, -16.527822 },
    { -3095.304199, 675.197266, -16.083666 },
    { -3097.482422, 673.099731, -15.411659 }};
    
// Orientation 5.109
float defendersPosScyer[10][3] = {
    { -4059.349121, 1075.253418, 31.234081 },
    { -4062.739014, 1074.006592, 30.966137 },
    { -4064.821533, 1073.240601, 30.761585 },
    { -4064.855469, 1068.144043, 30.224163 },
    { -4067.918457, 1069.042358, 30.359905 },
    { -4069.360596, 1063.678589, 30.409506 },
    { -4074.669922, 1065.100098, 30.804943 },
    { -4079.707275, 1065.286499, 31.153090 },
    { -4082.981689, 1062.328369, 31.237562 },
    { -4085.491699, 1058.670410, 30.850157 }};
    // -4072.696777, 1071.352295, 30.769413

struct npc_commander_arcusAI : public ScriptedAI
{
    npc_commander_arcusAI(Creature* c) : ScriptedAI(c), summons(me)
    {
        playerGUID = 0;
        isEvent = false;
    }
    
    float homeX, homeY, homeZ, homeOri;
    
    bool isEvent;
    
    uint64 playerGUID;
    
    uint32 aimedShotTimer;
    uint32 multiShotTimer;
    uint32 shootTimer;
    uint32 killCounter;
    uint32 summonTimer;
    
    SummonList summons;
    
    void Reset()
    override {
        aimedShotTimer = 5000;
        multiShotTimer = 10000;
        shootTimer = 1000;
        killCounter = 0;
        summonTimer = 0;
    }

    void EnterCombat(Unit* who) override {}
    
    void JustSummoned(Creature* summon)
    override {
        summons.Summon(summon);
        
        if (Unit *target = me->FindNearestCreature(0, 150.0f, true))
            summon->AI()->AttackStart(target);
    }
    
    void SummonedCreatureDespawn(Creature* summon)
    override {
        summons.Despawn(summon);
        if (summon->GetEntry() == NPC_DRAGONMAW_SKYBREAKER_ALDOR)
            killCounter++;
    }
    
    void MovementInform(uint32 type, uint32 id)
    override {
        if (id == 0) {
            DoScriptText(COMMANDER_ARCUS_SAY2, me);
            Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
            summonTimer = 15000 + rand() % 10000;
            for (auto & i : skybreakerPosAldor) {
                if (Creature* skybreaker = me->SummonCreature(NPC_DRAGONMAW_SKYBREAKER_ALDOR, i[0], i[1], i[2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000)) {
                    skybreaker->SetDisableGravity(true);
                    if (player)
                        skybreaker->AI()->AttackStart(player);
                }
            }
        }
    }
    
    void StartEvent()
    {
        isEvent = true;
        DoScriptText(COMMANDER_ARCUS_SAY1, me, nullptr);
        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        me->RemoveUnitMovementFlag(MOVEFLAG_WALK);
        me->GetMotionMaster()->MovePoint(0, -3098.666748, 682.178040, -18.633110, true);
        
        for (auto & i : defendersPosAldor)
            me->SummonCreature(NPC_DEFENDER_ALDOR, i[0], i[1], i[2], 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
        
        me->GetHomePosition(homeX, homeY, homeZ, homeOri);
        me->SetHomePosition(-3098.666748, 682.178040, -18.633110, me->GetOrientation());
    }
    
    void EndEvent(bool success)
    {
        Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
        if (success) {
            DoScriptText(COMMANDER_ARCUS_SAY3, me);
            if (player)
                player->GroupEventHappens(QUEST_DEADLIEST_TRAP_ALDOR, me);
        }
        else {
            if (player)
                player->FailQuest(QUEST_DEADLIEST_TRAP_ALDOR);
        }

        playerGUID = 0;
        me->SetHomePosition(homeX, homeY, homeZ, homeOri);
        EnterEvadeMode();
        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        summons.DespawnAll();
        isEvent = false;
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!isEvent)
            return;

        Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
        if (!player || player->GetDistance(me) > 110.0f) {
            EndEvent(false);
            return;
        }
            
        if (killCounter >= 15) {
            EndEvent(true);
            return;
        }

        if (summonTimer) {
            if (summonTimer <= diff) {
                if (Creature* skybreaker = me->SummonCreature(NPC_DRAGONMAW_SKYBREAKER_ALDOR, skybreakerPosAldor[rand()%10][0], skybreakerPosAldor[rand()%10][1], skybreakerPosAldor[rand()%10][2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000)) {
                    skybreaker->SetDisableGravity(true);
                    skybreaker->AI()->AttackStart(player);
                }
                
                summonTimer = 15000 + rand() % 10000;
            }
            else
                summonTimer -= diff;
        }

        if (!UpdateVictim(false))
            return;

        if (aimedShotTimer <= diff) {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_AIMED_SHOT);
            aimedShotTimer = 5000 + rand() % 3000;
        }
        else
            aimedShotTimer -= diff;
            
        if (multiShotTimer <= diff) {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_MULTI_SHOT);
            multiShotTimer = 5000 + rand() % 3000;
        }
        else
            multiShotTimer -= diff;
            
        if (shootTimer <= diff) {
            DoCast(me->GetVictim(), SPELL_SHOOT);
            shootTimer = 5000 + rand() % 3000;
        }
        else
            shootTimer -= diff;
        
        if (me->GetVictim()->IsWithinMeleeRange(me))
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_commander_arcus(Creature* creature)
{
    return new npc_commander_arcusAI(creature);
}

bool QuestAccept_npc_commander_arcus(Player* player, Creature* creature, Quest const* quest)
{
    if (creature->IsQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    if (quest->GetQuestId() == QUEST_DEADLIEST_TRAP_ALDOR) {
        ((npc_commander_arcusAI*)creature->AI())->playerGUID = player->GetGUID();
        ((npc_commander_arcusAI*)creature->AI())->StartEvent();
    }
    
    return true;
}

struct npc_commander_hobbAI : public ScriptedAI
{
    npc_commander_hobbAI(Creature* c) : ScriptedAI(c), summons(me)
    {
        playerGUID = 0;
        isEvent = false;
    }
    
    float homeX, homeY, homeZ, homeOri;
    
    bool isEvent;
    
    uint64 playerGUID;
    
    uint32 aimedShotTimer;
    uint32 multiShotTimer;
    uint32 shootTimer;
    uint32 killCounter;
    uint32 summonTimer;
    
    SummonList summons;
    
    void Reset()
    override {
        aimedShotTimer = 5000;
        multiShotTimer = 10000;
        shootTimer = 1000;
        killCounter = 0;
        summonTimer = 0;
    }

    void EnterCombat(Unit* who) override {}
    
    void JustSummoned(Creature* summon)
    override {
        summons.Summon(summon);
        
        if (Unit *target = me->FindNearestCreature(0, 150.0f, true))
            summon->AI()->AttackStart(target);
    }
    
    void SummonedCreatureDespawn(Creature* summon)
    override {
        summons.Despawn(summon);
        if (summon->GetEntry() == NPC_DRAGONMAW_SKYBREAKER_SCYER)
            killCounter++;
    }
    
    void MovementInform(uint32 type, uint32 id)
    override {
        if (id == 0) {
            DoScriptText(COMMANDER_HOBB_SAY2, me);
            Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
            summonTimer = 15000 + rand() % 10000;
            for (auto & i : skybreakerPosScyer) {
                if (Creature* skybreaker = me->SummonCreature(NPC_DRAGONMAW_SKYBREAKER_SCYER, i[0], i[1], i[2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000)) {
                    skybreaker->SetDisableGravity(true);
                    if (player)
                        skybreaker->AI()->AttackStart(player);
                }
            }
        }
    }
    
    void StartEvent()
    {
        isEvent = true;
        DoScriptText(COMMANDER_HOBB_SAY1, me, nullptr);
        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        me->RemoveUnitMovementFlag(MOVEFLAG_WALK);
        me->GetMotionMaster()->MovePoint(0, -4072.696777, 1071.352295, 30.769413, true);
        
        for (auto & i : defendersPosScyer)
            me->SummonCreature(NPC_DEFENDER_SCYER, i[0], i[1], i[2], 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
        
        me->GetHomePosition(homeX, homeY, homeZ, homeOri);
        me->SetHomePosition(-4072.696777, 1071.352295, 30.769413, me->GetOrientation());
    }
    
    void EndEvent(bool success)
    {
        Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
        if (success) {
            DoScriptText(COMMANDER_HOBB_SAY3, me);
            if (player)
                player->GroupEventHappens(QUEST_DEADLIEST_TRAP_SCYER, me);
        }
        else {
            if (player)
                player->FailQuest(QUEST_DEADLIEST_TRAP_SCYER);
        }

        playerGUID = 0;
        me->SetHomePosition(homeX, homeY, homeZ, homeOri);
        EnterEvadeMode();
        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        summons.DespawnAll();
        isEvent = false;
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!isEvent)
            return;

        Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
        if (!player || player->GetDistance(me) > 110.0f) {
            EndEvent(false);
            return;
        }
            
        if (killCounter >= 15) {
            EndEvent(true);
            return;
        }

        if (summonTimer) {
            if (summonTimer <= diff) {
                if (Creature* skybreaker = me->SummonCreature(NPC_DRAGONMAW_SKYBREAKER_SCYER, skybreakerPosScyer[rand()%10][0], skybreakerPosScyer[rand()%10][1], skybreakerPosScyer[rand()%10][2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000)) {
                    skybreaker->SetDisableGravity(true);
                    skybreaker->AI()->AttackStart(player);
                }
                
                summonTimer = 15000 + rand() % 10000;
            }
            else
                summonTimer -= diff;
        }

        if (!UpdateVictim(false))
            return;

        if (aimedShotTimer <= diff) {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_AIMED_SHOT);
            aimedShotTimer = 5000 + rand() % 3000;
        }
        else
            aimedShotTimer -= diff;
            
        if (multiShotTimer <= diff) {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_MULTI_SHOT);
            multiShotTimer = 5000 + rand() % 3000;
        }
        else
            multiShotTimer -= diff;
            
        if (shootTimer <= diff) {
            DoCast(me->GetVictim(), SPELL_SHOOT);
            shootTimer = 5000 + rand() % 3000;
        }
        else
            shootTimer -= diff;
        
        if (me->GetVictim()->IsWithinMeleeRange(me))
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_commander_hobb(Creature* creature)
{
    return new npc_commander_hobbAI(creature);
}

bool QuestAccept_npc_commander_hobb(Player* player, Creature* creature, Quest const* quest)
{
    if (creature->IsQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    if (quest->GetQuestId() == QUEST_DEADLIEST_TRAP_SCYER) {
        ((npc_commander_hobbAI*)creature->AI())->playerGUID = player->GetGUID();
        ((npc_commander_hobbAI*)creature->AI())->StartEvent();
    }
    
    return true;
}

struct npc_dragonmaw_skybreakerAI : public ScriptedAI
{
    npc_dragonmaw_skybreakerAI(Creature* c) : ScriptedAI(c)
    {
        aldor = (me->GetEntry() == NPC_DRAGONMAW_SKYBREAKER_ALDOR) ? true : false;
    }
    
    bool aldor;
    
    uint32 aimedShotTimer;
    uint32 multiShotTimer;
    uint32 scatterShotTimer;
    uint32 shootTimer;
    
    uint32 randomTauntTimer;
    
    void Reset()
    override {
        randomTauntTimer = 1000 + rand() % 5000;
    }
    
    void EnterCombat(Unit* who)
    override {
        if (rand()%10 < 6)
            return;

        DoScriptText(RAND(SKYBREAKER_SAY1, SKYBREAKER_SAY2), me, nullptr);
    }
    
    void UpdateAI(uint32 const diff)
    override {
        me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);

        if (!UpdateVictim(false))
            return;
            
        if (randomTauntTimer <= diff) {
            if (aldor)
                DoScriptText(RAND(SKYBREAKER_SAYALDOR1, SKYBREAKER_SAYALDOR2, SKYBREAKER_SAY3), me);
            else
                DoScriptText(RAND(SKYBREAKER_SAYSCYER1, SKYBREAKER_SAYSCYER2, SKYBREAKER_SAY3), me);
                
            randomTauntTimer = 8000 + rand() % 4000;
        }
        else
            randomTauntTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_dragonmaw_skybreaker(Creature* creature)
{
    return new npc_dragonmaw_skybreakerAI(creature);
}

/*######
## npc_xiri
######*/

/*

SPELLS

39828 - self cast - effet de traits blancs qui montent
39829 - idem mais une seule fois
39831 - grosse explosion blanche

NPCS

22863 - défenseur clairvoyant
22864 - chef clairvoyant
22861 - défenseur aldor
22862 - chef aldor
18528 - xi'ri
21166 - seigneur de l'effroi illidari

VIDEO

http://www.youtube.com/watch?v=zET3VQusn9o (lien privé)

*/

struct npc_xiriAI : public ScriptedAI
{
    npc_xiriAI(Creature* c) : ScriptedAI(c)
    {
        isEvent = false;
        SetCombatMovementAllowed(false);
    }
    
    bool isEvent;
    
    uint32 summonTimer;
    
    void Reset()
    override {
        isEvent = false;
        summonTimer = 15000;
    }
    
    void EnterCombat(Unit* who) override {}
    
    void StartEvent()
    {
        isEvent = true;
    }
    
    void StopEvent()
    {
        isEvent = false;
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!isEvent)
            return;

        
    }
};

CreatureAI* GetAI_npc_xiri(Creature* creature)
{
    return new npc_xiriAI(creature);
}

bool GossipHello_npc_xiri(Player* player, Creature* creature)
{
    if (creature->IsQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());
        
    //todo translate
    if (player->GetQuestStatus(10985) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je suis prêt à rejoindre vos forces dans la bataille, Xi'ri.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        
    SEND_PREPARED_GOSSIP_MENU(player, creature);
    
    return true;
}

bool GossipSelect_npc_xiri(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF) {
        player->CLOSE_GOSSIP_MENU();
        ((npc_xiriAI*)creature->AI())->StartEvent();
    }
    
    return true;
}

/*######
## AddSC
#######*/

void AddSC_shadowmoon_valley()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name = "mob_mature_netherwing_drake";
    newscript->GetAI = &GetAI_mob_mature_netherwing_drake;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "mob_enslaved_netherwing_drake";
    newscript->GetAI = &GetAI_mob_enslaved_netherwing_drake;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "mob_dragonmaw_peon";
    newscript->GetAI = &GetAI_mob_dragonmaw_peon;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_drake_dealer_hurlunk";
    newscript->OnGossipHello =  &GossipHello_npc_drake_dealer_hurlunk;
    newscript->OnGossipSelect = &GossipSelect_npc_drake_dealer_hurlunk;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npcs_flanis_swiftwing_and_kagrosh";
    newscript->OnGossipHello =  &GossipHello_npcs_flanis_swiftwing_and_kagrosh;
    newscript->OnGossipSelect = &GossipSelect_npcs_flanis_swiftwing_and_kagrosh;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_murkblood_overseer";
    newscript->OnGossipHello =  &GossipHello_npc_murkblood_overseer;
    newscript->OnGossipSelect = &GossipSelect_npc_murkblood_overseer;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_neltharaku";
    newscript->OnGossipHello =  &GossipHello_npc_neltharaku;
    newscript->OnGossipSelect = &GossipSelect_npc_neltharaku;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_oronok_tornheart";
    newscript->OnGossipHello =  &GossipHello_npc_oronok_tornheart;
    newscript->OnGossipSelect = &GossipSelect_npc_oronok_tornheart;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_overlord_morghor";
    newscript->GetAI = &GetAI_npc_overlord_morghorAI;
    newscript->OnQuestAccept = &QuestAccept_npc_overlord_morghor;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_earthmender_wilda";
    newscript->GetAI = &GetAI_npc_earthmender_wildaAI;
    newscript->OnQuestAccept = &QuestAccept_npc_earthmender_wilda;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_lord_illidan_stormrage";
    newscript->GetAI = &GetAI_npc_lord_illidan_stormrage;
    sScriptMgr->RegisterOLDScript(newscript);

    new CrystalPrison();

    newscript = new OLDScript;
    newscript->Name = "mob_illidari_spawn";
    newscript->GetAI = &GetAI_mob_illidari_spawn;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "mob_torloth_the_magnificent";
    newscript->GetAI = &GetAI_mob_torloth_the_magnificent;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_enraged_spirit";
    newscript->GetAI = &GetAI_npc_enraged_spirit;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_spirits_totem";
    newscript->GetAI = &GetAI_npc_spirits_totem;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_skartax";
    newscript->GetAI = &GetAI_npc_skartax;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_invis_deathforge_caster";
    newscript->GetAI = &GetAI_npc_invis_deathforge_caster;
    sScriptMgr->RegisterOLDScript(newscript);
    
    new ArcanoControlUnit();
    
    newscript = new OLDScript;
    newscript->Name = "npc_quest_spectrecles";
    newscript->OnGossipHello = &GossipHello_npc_quest_spectrecles;
    newscript->OnGossipSelect = &GossipSelect_npc_quest_spectrecles;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_akama_prelude";
    newscript->GetAI = &GetAI_npc_akama_prelude;
    newscript->OnQuestReward = &ChooseReward_npc_akama_prelude;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_commander_arcus";
    newscript->GetAI = &GetAI_npc_commander_arcus;
    newscript->OnQuestAccept = &QuestAccept_npc_commander_arcus;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_commander_hobb";
    newscript->GetAI = &GetAI_npc_commander_hobb;
    newscript->OnQuestAccept = &QuestAccept_npc_commander_hobb;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_dragonmaw_skybreaker";
    newscript->GetAI = &GetAI_npc_dragonmaw_skybreaker;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_xiri";
    newscript->GetAI = &GetAI_npc_xiri;
    newscript->OnGossipHello = &GossipHello_npc_xiri;
    newscript->OnGossipSelect = &GossipSelect_npc_xiri;
    sScriptMgr->RegisterOLDScript(newscript);
}
