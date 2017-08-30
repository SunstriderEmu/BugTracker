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
SDName: Guards
SD%Complete: 100
SDComment: All Guard gossip data, quite some npc_text-id's still missing, adding constantly as new id's are known. CombatAI should be organized better for future.
SDCategory: Guards
EndScriptData */

/* ContentData
guard_azuremyst
guard_bluffwatcher
guard_contested
guard_darnassus
guard_dunmorogh
guard_durotar
guard_elwynnforest
guard_eversong
guard_exodar
guard_ironforge
guard_mulgore
guard_orgrimmar
guard_shattrath
guard_shattrath_aldor
guard_shattrath_scryer
guard_silvermoon
guard_stormwind
guard_teldrassil
guard_tirisfal
guard_undercity
EndContentData */


#include "GuardAI.h"

//script spesific action
#define GOSSIP_ACTION_TAVERN                  101
#define GOSSIP_ACTION_GEMMERCHANT             102
#define GOSSIP_ACTION_MANALOOM                103

//script spesific sender
#define GOSSIP_SENDER_SEC_GEMMERCHANT         101
#define GOSSIP_SENDER_SEC_AUCTIONHOUSE        102

//script spesific gossip text
//TODO TRANSLATE
#define GOSSIP_TEXT_TAVERN                    "Taverne du Bout du Monde"
#define GOSSIP_TEXT_BANKSCYERS                "Banque des Clairvoyants"
#define GOSSIP_TEXT_BANKALDOR                 "Banque de l'Aldor"
#define GOSSIP_TEXT_INNSCYERS                 "Auberge des Clairvoyants"
#define GOSSIP_TEXT_INNALDOR                  "Auberge de l'Aldor"
#define GOSSIP_TEXT_STABLESCYERS              "Etable des Clairvoyants"
#define GOSSIP_TEXT_STABLEALDOR               "Etable de l'Aldor"
#define GOSSIP_TEXT_BATTLEMASTERALLIANCE      "Maîtres de guerre de l'Alliance"
#define GOSSIP_TEXT_BATTLEMASTERHORDE         "Maîtres de guerre de la Horde"
#define GOSSIP_TEXT_BATTLEMASTERARENA         "Maîtres de guerre de l'arène"
#define GOSSIP_TEXT_MANALOOM                  "Métier à tisser le mana"
#define GOSSIP_TEXT_ALCHEMYLAB                "Laboratoire d'alchimie"
#define GOSSIP_TEXT_GEMMERCHANT               "Marchand de gemmes"
#define GOSSIP_TEXT_GEMSCYERS                 "Marchand de gemmes des Clairvoyants"
#define GOSSIP_TEXT_GEMALDOR                  "Marchand de gemmes de l'Aldor"

#define GOSSIP_TEXT_AH_SILVERMOON_1           "Hotel des ventes de l'Ouest"
#define GOSSIP_TEXT_AH_SILVERMOON_2           "Hotel des ventes Royal Exchange"

#define GOSSIP_TEXT_INN_SILVERMOON_1          "Auberge de Lune-d'Argent"
#define GOSSIP_TEXT_INN_SILVERMOON_2          "Auberge des voyageurs"

//common used for guards in main cities
void DoReplyToTextEmote(Creature *_Creature,uint32 em)
{
    switch(em)
    {
        case TEXTEMOTE_KISS:    _Creature->HandleEmoteCommand(EMOTE_ONESHOT_BOW); break;
        case TEXTEMOTE_WAVE:    _Creature->HandleEmoteCommand(EMOTE_ONESHOT_WAVE); break;
        case TEXTEMOTE_SALUTE:  _Creature->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE); break;
        case TEXTEMOTE_SHY:     _Creature->HandleEmoteCommand(EMOTE_ONESHOT_FLEX); break;
        case TEXTEMOTE_RUDE:
        case TEXTEMOTE_CHICKEN: _Creature->HandleEmoteCommand(EMOTE_ONESHOT_POINT); break;
    }
}

class guard_azuremyst : public CreatureScript
{
public:
    guard_azuremyst() : CreatureScript("guard_azuremyst")
    { }

    class guard_azuremystAI : public guardAI
    {
    public:
        guard_azuremystAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_HIPPOGRYPH      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN             , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->SEND_GOSSIP_MENU_TEXTID(10066,me->GetGUID());
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_azuremyst(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_azuremyst(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_azuremyst(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_azuremyst(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
                player->SEND_POI(-3918.95, -11544.7, 6, 6, 0, "Banque");
                player->SEND_GOSSIP_MENU_TEXTID(10067, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Hippogryph Master
                player->SEND_POI(-4057.15, -11788.6, 6, 6, 0, "Stephanos");
                player->SEND_GOSSIP_MENU_TEXTID(10071, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
                player->SEND_POI(-4092.43, -11626.6, 6, 6, 0, "Funaam");
                player->SEND_GOSSIP_MENU_TEXTID(10073, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
                player->SEND_POI(-4129.43, -12469, 6, 6, 0, "Caregiver Chellan");
                player->SEND_GOSSIP_MENU_TEXTID(10074, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Stable Master
                player->SEND_POI(-4146.42, -12492.7, 6, 6, 0, "Esbina");
                player->SEND_GOSSIP_MENU_TEXTID(10075, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->SEND_GOSSIP_MENU_TEXTID(10076, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 13);
                player->SEND_GOSSIP_MENU_TEXTID(10087, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_azuremyst(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
                player->SEND_POI(-4274.81, -11495.3, 6, 6, 0, "Shalannius");
                player->SEND_GOSSIP_MENU_TEXTID(10077, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
                player->SEND_POI(-4203.65, -12526.5, 6, 6, 0, "Acteon");
                player->SEND_GOSSIP_MENU_TEXTID(10078, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
                player->SEND_POI(-4149.62, -12530.1, 6, 6, 0, "Semid");
                player->SEND_GOSSIP_MENU_TEXTID(10081, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
                player->SEND_POI(-4138.98, -12468.5, 6, 6, 0, "Tullas");
                player->SEND_GOSSIP_MENU_TEXTID(10083, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
                player->SEND_POI(-4131.66, -12478.6, 6, 6, 0, "Guvan");
                player->SEND_GOSSIP_MENU_TEXTID(10084, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Shaman
                player->SEND_POI(-4162.33, -12456.1, 6, 6, 0, "Tuluun");
                player->SEND_GOSSIP_MENU_TEXTID(10085, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
                player->SEND_POI(-4165.05, -12536.4, 6, 6, 0, "Ruada");
                player->SEND_GOSSIP_MENU_TEXTID(10086, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_azuremyst(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(-4191.15, -12470, 6, 6, 0, "Daedal");
                player->SEND_GOSSIP_MENU_TEXTID(10088, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(-4726.29, -12387, 6, 6, 0, "Blacksmith Calypso");
                player->SEND_GOSSIP_MENU_TEXTID(10089, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-4710.87, -12400.6, 6, 6, 0, "'Cookie' McWeaksauce");
                player->SEND_GOSSIP_MENU_TEXTID(10090, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(-3882.85, -11496.7, 6, 6, 0, "Nahogg");
                player->SEND_GOSSIP_MENU_TEXTID(10091, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_POI(-4157.57, -12470.2, 6, 6, 0, "Artificer Daelo");
                player->SEND_GOSSIP_MENU_TEXTID(10092, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(-4199.11, -12469.9, 6, 6, 0, "Anchorite Fateema");
                player->SEND_GOSSIP_MENU_TEXTID(10093, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(-4266.38, -12985.1, 6, 6, 0, "Diktynna");
                player->SEND_GOSSIP_MENU_TEXTID(10094, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
                player->SEND_GOSSIP_MENU_TEXTID(10095, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Jewelcrafting
                player->SEND_POI(-3781.55, -11541.8, 6, 6, 0, "Farii");
                player->SEND_GOSSIP_MENU_TEXTID(10096, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Leatherworking
                player->SEND_POI(-3442.68, -12322.2, 6, 6, 0, "Moordo");
                player->SEND_GOSSIP_MENU_TEXTID(10098, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Mining
                player->SEND_POI(-4179.89, -12493.1, 6, 6, 0, "Dulvi");
                player->SEND_GOSSIP_MENU_TEXTID(10097, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Skinning
                player->SEND_POI(-3431.17, -12316.5, 6, 6, 0, "Gurf");
                player->SEND_GOSSIP_MENU_TEXTID(10098, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 13:                   //Tailoring
                player->SEND_POI(-4711.54, -12386.7, 6, 6, 0, "Erin Kelly");
                player->SEND_GOSSIP_MENU_TEXTID(10099, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_azuremystAI(creature);
    }
};


class guard_bluffwatcher : public CreatureScript
{
public:
    guard_bluffwatcher() : CreatureScript("guard_bluffwatcher")
    { }

    class guard_bluffwatcherAI : public guardAI
    {
    public:
        guard_bluffwatcherAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->SEND_GOSSIP_MENU_TEXTID(3543,me->GetGUID());
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_bluffwatcher(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_bluffwatcher(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_bluffwatcher(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_bluffwatcher(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_bluffwatcher(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
                player->SEND_POI(-1257.8, 24.14, 6, 6, 0, "Banque des Pitons du Tonnerre");
                player->SEND_GOSSIP_MENU_TEXTID(1292, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Wind master
                player->SEND_POI(-1196.43, 28.26, 6, 6, 0, "Maître des chevaucheurs du vent");
                player->SEND_GOSSIP_MENU_TEXTID(1293, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
                player->SEND_POI(-1296.5, 127.57, 6, 6, 0, "Information civile des Pitons du Tonnerre");
                player->SEND_GOSSIP_MENU_TEXTID(1291, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
                player->SEND_POI(-1296, 39.7, 6, 6, 0, "Auberge des Pitons du Tonnerre");
                player->SEND_GOSSIP_MENU_TEXTID(3153, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
                player->SEND_POI(-1263.59, 44.36, 6, 6, 0, "Boîte aux lettres des Pitons du Tonnerre");
                player->SEND_GOSSIP_MENU_TEXTID(3154, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Auction House
                player->SEND_POI(-1205.61, 106.06, 6, 6, 0, GOSSIP_TEXT_AUCTIONHOUSE);
                player->SEND_GOSSIP_MENU_TEXTID(3155, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Weapon master
                player->SEND_POI(-1282.31, 89.56, 6, 6, 0, "Ansekhwa");
                player->SEND_GOSSIP_MENU_TEXTID(4520, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Stable master
                player->SEND_POI(-1270.19, 48.84, 6, 6, 0, "Bulrug");
                player->SEND_GOSSIP_MENU_TEXTID(5977, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //battlemaster
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(7527, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->SEND_GOSSIP_MENU_TEXTID(3542, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->SEND_GOSSIP_MENU_TEXTID(3541, _Creature->GetGUID());
                break;
            }
        }

        void SendBattleMasterMenu_guard_bluffwatcher(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
                player->SEND_POI(-1387.82, -97.55, 6, 6, 0, "Taim Ragetotem");
                player->SEND_GOSSIP_MENU_TEXTID(7522, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
                player->SEND_POI(-997, 214.12, 6, 6, 0, "Martin Lindsey");
                player->SEND_GOSSIP_MENU_TEXTID(7648, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
                player->SEND_POI(-1384.94, -75.91, 6, 6, 0, "Kergul Bloodaxe");
                player->SEND_GOSSIP_MENU_TEXTID(7523, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_bluffwatcher(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
                player->SEND_POI(-1054.47, -285, 6, 6, 0, "Hall des Anciens");
                player->SEND_GOSSIP_MENU_TEXTID(1294, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
                player->SEND_POI(-1416.32, -114.28, 6, 6, 0, "Hall du Chasseur");
                player->SEND_GOSSIP_MENU_TEXTID(1295, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
                player->SEND_POI(-1061.2, 195.5, 6, 6, 0, "Bassins de la Vision");
                player->SEND_GOSSIP_MENU_TEXTID(1296, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Priest
                player->SEND_POI(-1061.2, 195.5, 6, 6, 0, "Bassins de la Vision");
                player->SEND_GOSSIP_MENU_TEXTID(1297, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Shaman
                player->SEND_POI(-989.54, 278.25, 6, 6, 0, "Hall des Esprits");
                player->SEND_GOSSIP_MENU_TEXTID(1298, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Warrior
                player->SEND_POI(-1416.32, -114.28, 6, 6, 0, "Hall du Chasseur");
                player->SEND_GOSSIP_MENU_TEXTID(1299, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_bluffwatcher(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(-1085.56, 27.29, 6, 6, 0, "Alchimie de Bena");
                player->SEND_GOSSIP_MENU_TEXTID(1332, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(-1239.75, 104.88, 6, 6, 0, "Forge de Karn");
                player->SEND_GOSSIP_MENU_TEXTID(1333, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-1214.5, -21.23, 6, 6, 0, "Cuisine d'Aska");
                player->SEND_GOSSIP_MENU_TEXTID(1334, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(-1112.65, 48.26, 6, 6, 0, "Enchantement Dawnstrider");
                player->SEND_GOSSIP_MENU_TEXTID(1335, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
                player->SEND_POI(-996.58, 200.5, 6, 6, 0, "Soin spirituel");
                player->SEND_GOSSIP_MENU_TEXTID(1336, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Fishing
                player->SEND_POI(-1169.35, -68.87, 6, 6, 0, "Mountaintop Bait & Tackle");
                player->SEND_GOSSIP_MENU_TEXTID(1337, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Herbalism
                player->SEND_POI(-1137.7, -1.51, 6, 6, 0, "Herborisme sacré");
                player->SEND_GOSSIP_MENU_TEXTID(1338, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Leatherworking
                player->SEND_POI(-1156.22, 66.86, 6, 6, 0, "Armuriers des Pitons du Tonnerre");
                player->SEND_GOSSIP_MENU_TEXTID(1339, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Mining
                player->SEND_POI(-1249.17, 155, 6, 6, 0, "Géologie Sabot-de-pierre");
                player->SEND_GOSSIP_MENU_TEXTID(1340, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Skinning
                player->SEND_POI(-1148.56, 51.18, 6, 6, 0, "Mooranta");
                player->SEND_GOSSIP_MENU_TEXTID(1343, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Tailoring
                player->SEND_POI(-1156.22, 66.86, 6, 6, 0, "Tisserands des Pitons du Tonnerre");
                player->SEND_GOSSIP_MENU_TEXTID(1341, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_bluffwatcherAI(creature);
    }
};

class guard_contested : public CreatureScript
{
public:
    guard_contested() : CreatureScript("guard_contested")
    { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guardAI(creature);
    }
};

class guard_darnassus : public CreatureScript
{
public:
    guard_darnassus() : CreatureScript("guard_darnassus")
    { }

    class guard_darnassusAI : public guardAI
    {
    public:
        guard_darnassusAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_HIPPOGRYPH     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX        , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->SEND_GOSSIP_MENU_TEXTID(3016, me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_darnassus(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_darnassus(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_darnassus(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_darnassus(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_darnassus(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction house
                player->SEND_POI(9861.23, 2334.55, 6, 6, 0, "Hotel des ventes de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3833, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
                player->SEND_POI(9938.45, 2512.35, 6, 6, 0, "Banque de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3017, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Wind master
                player->SEND_POI(9945.65, 2618.94, 6, 6, 0, "Rut'theran Village");
                player->SEND_GOSSIP_MENU_TEXTID(3018, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Guild master
                player->SEND_POI(10076.40, 2199.59, 6, 6, 0, "Maître de guilde de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3019, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Inn
                player->SEND_POI(10133.29, 2222.52, 6, 6, 0, "Auberge de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3020, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Mailbox
                player->SEND_POI(9942.17, 2495.48, 6, 6, 0, "Boîte aux lettres de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3021, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Stable master
                player->SEND_POI(10167.20, 2522.66, 6, 6, 0, "Alassin");
                player->SEND_GOSSIP_MENU_TEXTID(5980, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Weapon trainer
                player->SEND_POI(9907.11, 2329.70, 6, 6, 0, "Ilyenia Moonfire");
                player->SEND_GOSSIP_MENU_TEXTID(4517, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Battlemaster
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(7519, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU_TEXTID(4264, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->SEND_GOSSIP_MENU_TEXTID(4273, _Creature->GetGUID());
                break;
            }
        }

        void SendBattleMasterMenu_guard_darnassus(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
                player->SEND_POI(9923.61, 2327.43, 6, 6, 0, "Brogun Stoneshield");
                player->SEND_GOSSIP_MENU_TEXTID(7518, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
                player->SEND_POI(9977.37, 2324.39, 6, 6, 0, "Keras Wolfheart");
                player->SEND_GOSSIP_MENU_TEXTID(7651, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
                player->SEND_POI(9979.84, 2315.79, 6, 6, 0, "Aethalas");
                player->SEND_GOSSIP_MENU_TEXTID(7482, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_darnassus(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
                player->SEND_POI(10186, 2570.46, 6, 6, 0, "Maître des druides de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3024, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
                player->SEND_POI(10177.29, 2511.10, 6, 6, 0, "Maître des chasseurs de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3023, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
                player->SEND_POI(9659.12, 2524.88, 6, 6, 0, "Temple de la Lune");
                player->SEND_GOSSIP_MENU_TEXTID(3025, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Rogue
                player->SEND_POI(10122, 2599.12, 6, 6, 0, "Maître des voleurs de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3026, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
                player->SEND_POI(9951.91, 2280.38, 6, 6, 0, "Terrasse des guerriers");
                player->SEND_GOSSIP_MENU_TEXTID(3033, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_darnassus(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(10075.90, 2356.76, 6, 6, 0, "Maître d'alchimie de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3035, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Cooking
                player->SEND_POI(10088.59, 2419.21, 6, 6, 0, "Chef-cuisinier de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3036, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Enchanting
                player->SEND_POI(10146.09, 2313.42, 6, 6, 0, "Enchanteur de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3337, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //First Aid
                player->SEND_POI(10150.09, 2390.43, 6, 6, 0, "Entraîneur de Premiers Soins de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3037, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Fishing
                player->SEND_POI(9836.20, 2432.17, 6, 6, 0, "Maître de pêche de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3038, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Herbalism
                player->SEND_POI(9757.17, 2430.16, 6, 6, 0, "Maître herboriste de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3039, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
                player->SEND_POI(10086.59, 2255.77, 6, 6, 0, "Maître des travailleurs du cuir de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3040, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
                player->SEND_POI(10081.40, 2257.18, 6, 6, 0, "Maître des dépeceurs de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3042, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Tailoring
                player->SEND_POI(10079.70, 2268.19, 6, 6, 0, "Tailleur de Darnassus");
                player->SEND_GOSSIP_MENU_TEXTID(3044, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_darnassusAI(creature);
    }
};


/*******************************************************
 * guard_dunmorogh start
 *******************************************************/

class guard_dunmorogh : public CreatureScript
{
public:
    guard_dunmorogh() : CreatureScript("guard_dunmorogh")
    { }

    class guard_dunmoroghAI : public guardAI
    {
    public:
        guard_dunmoroghAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK             , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_HIPPOGRYPH       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN              , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->SEND_GOSSIP_MENU_TEXTID(4287,me->GetGUID());

            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_dunmorogh(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_dunmorogh(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_dunmorogh(player, me, action); break;
            }
            return true;

        }


        void SendDefaultMenu_guard_dunmorogh(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
                player->SEND_GOSSIP_MENU_TEXTID(4288, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Gryphon master
                player->SEND_GOSSIP_MENU_TEXTID(4289, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
                player->SEND_GOSSIP_MENU_TEXTID(4290, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
                player->SEND_POI(-5582.66, -525.89, 6, 6, 0, "Distillerie Thunderbrew");
                player->SEND_GOSSIP_MENU_TEXTID(4291, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Stable Master
                player->SEND_POI(-5604, -509.58, 6, 6, 0, "Shelby Stoneflint");
                player->SEND_GOSSIP_MENU_TEXTID(5985, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->SEND_GOSSIP_MENU_TEXTID(4292, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->SEND_GOSSIP_MENU_TEXTID(4300, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_dunmorogh(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
                player->SEND_POI(-5618.29, -454.25, 6, 6, 0, "Grif Wildheart");
                player->SEND_GOSSIP_MENU_TEXTID(4293, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
                player->SEND_POI(-5585.6, -539.99, 6, 6, 0, "Magis Sparkmantle");
                player->SEND_GOSSIP_MENU_TEXTID(4294, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Paladin
                player->SEND_POI(-5585.6, -539.99, 6, 6, 0, "Azar Stronghammer");
                player->SEND_GOSSIP_MENU_TEXTID(4295, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Priest
                player->SEND_POI(-5591.74, -525.61, 6, 6, 0, "Maxan Anvol");
                player->SEND_GOSSIP_MENU_TEXTID(4296, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Rogue
                player->SEND_POI(-5602.75, -542.4, 6, 6, 0, "Hogral Bakkan");
                player->SEND_GOSSIP_MENU_TEXTID(4297, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
                player->SEND_POI(-5641.97, -523.76, 6, 6, 0, "Gimrizz Shadowcog");
                player->SEND_GOSSIP_MENU_TEXTID(4298, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
                player->SEND_POI(-5604.79, -529.38, 6, 6, 0, "Granis Swiftaxe");
                player->SEND_GOSSIP_MENU_TEXTID(4299, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_dunmorogh(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_GOSSIP_MENU_TEXTID(4301, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(-5584.72, -428.41, 6, 6, 0, "Tognus Flintfire");
                player->SEND_GOSSIP_MENU_TEXTID(4302, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-5596.85, -541.43, 6, 6, 0, "Gremlock Pilsnor");
                player->SEND_GOSSIP_MENU_TEXTID(4303, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_GOSSIP_MENU_TEXTID(4304, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_POI(-5531, -666.53, 6, 6, 0, "Bronk Guzzlegear");
                player->SEND_GOSSIP_MENU_TEXTID(4305, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(-5603.67, -523.57, 6, 6, 0, "Thamner Pol");
                player->SEND_GOSSIP_MENU_TEXTID(4306, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(-5199.9, 58.58, 6, 6, 0, "Paxton Ganter");
                player->SEND_GOSSIP_MENU_TEXTID(4307, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
                player->SEND_GOSSIP_MENU_TEXTID(4308, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
                player->SEND_GOSSIP_MENU_TEXTID(4310, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
                player->SEND_POI(-5531, -666.53, 6, 6, 0, "Yarr Hamerstone");
                player->SEND_GOSSIP_MENU_TEXTID(4311, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
                player->SEND_GOSSIP_MENU_TEXTID(4312, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
                player->SEND_GOSSIP_MENU_TEXTID(4313, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_dunmoroghAI(creature);
    }
};


class guard_durotar : public CreatureScript
{
public:
    guard_durotar() : CreatureScript("guard_durotar")
    { }

    class guard_durotarAI : public guardAI
    {
    public:
        guard_durotarAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->SEND_GOSSIP_MENU_TEXTID(4037,me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_durotar(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_durotar(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_durotar(player, me, action); break;
            }
            return true;

        }


        void SendDefaultMenu_guard_durotar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
                player->SEND_GOSSIP_MENU_TEXTID(4032, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Wind rider
                player->SEND_GOSSIP_MENU_TEXTID(4033, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
                player->SEND_POI(338.7, -4688.87, 6, 6, 0, "Auberge de Razor Hill");
                player->SEND_GOSSIP_MENU_TEXTID(4034, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable master
                player->SEND_POI(330.31, -4710.66, 6, 6, 0, "Shoja'my");
                player->SEND_GOSSIP_MENU_TEXTID(5973, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->SEND_GOSSIP_MENU_TEXTID(4035, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->SEND_GOSSIP_MENU_TEXTID(4036, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_durotar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
                player->SEND_POI(276, -4706.72, 6, 6, 0, "Thotar");
                player->SEND_GOSSIP_MENU_TEXTID(4013, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
                player->SEND_POI(-839.33, -4935.6, 6, 6, 0, "Un'Thuwa");
                player->SEND_GOSSIP_MENU_TEXTID(4014, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
                player->SEND_POI(296.22, -4828.1, 6, 6, 0, "Tai'jin");
                player->SEND_GOSSIP_MENU_TEXTID(4015, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Rogue
                player->SEND_POI(265.76, -4709, 6, 6, 0, "Kaplak");
                player->SEND_GOSSIP_MENU_TEXTID(4016, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Shaman
                player->SEND_POI(307.79, -4836.97, 6, 6, 0, "Swart");
                player->SEND_GOSSIP_MENU_TEXTID(4017, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
                player->SEND_POI(355.88, -4836.45, 6, 6, 0, "Dhugru Gorelust");
                player->SEND_GOSSIP_MENU_TEXTID(4018, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
                player->SEND_POI(312.3, -4824.66, 6, 6, 0, "Tarshaw Jaggedscar");
                player->SEND_GOSSIP_MENU_TEXTID(4019, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_durotar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(-800.25, -4894.33, 6, 6, 0, "Miao'zan");
                player->SEND_GOSSIP_MENU_TEXTID(4020, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(373.24, -4716.45, 6, 6, 0, "Dwukk");
                player->SEND_GOSSIP_MENU_TEXTID(4021, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_GOSSIP_MENU_TEXTID(4022, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_GOSSIP_MENU_TEXTID(4023, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_POI(368.95, -4723.95, 6, 6, 0, "Mukdrak");
                player->SEND_GOSSIP_MENU_TEXTID(4024, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(327.17, -4825.62, 6, 6, 0, "Rawrk");
                player->SEND_GOSSIP_MENU_TEXTID(4025, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(-1065.48, -4777.43, 6, 6, 0, "Lau'Tiki");
                player->SEND_GOSSIP_MENU_TEXTID(4026, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
                player->SEND_POI(-836.25, -4896.89, 6, 6, 0, "Mishiki");
                player->SEND_GOSSIP_MENU_TEXTID(4027, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
                player->SEND_GOSSIP_MENU_TEXTID(4028, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
                player->SEND_POI(366.94, -4705, 6, 6, 0, "Krunn");
                player->SEND_GOSSIP_MENU_TEXTID(4029, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
                player->SEND_GOSSIP_MENU_TEXTID(4030, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
                player->SEND_GOSSIP_MENU_TEXTID(4031, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_durotarAI(creature);
    }
};


class guard_elwynnforest : public CreatureScript
{
public:
    guard_elwynnforest() : CreatureScript("guard_elwynnforest")
    { }

    class guard_elwynnforestAI : public guardAI
    {
    public:
        guard_elwynnforestAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GRYPHON       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->SEND_GOSSIP_MENU_TEXTID(933,me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_elwynnforest(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_elwynnforest(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_elwynnforest(player, me, action); break;
            }
            return true;

        }


        void SendDefaultMenu_guard_elwynnforest(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
                player->SEND_GOSSIP_MENU_TEXTID(4260, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Gryphon master
                player->SEND_GOSSIP_MENU_TEXTID(4261, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
                player->SEND_GOSSIP_MENU_TEXTID(4262, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
                player->SEND_POI(-9459.34, 42.08, 6, 6, 0, "Auberge Lion's Pride");
                player->SEND_GOSSIP_MENU_TEXTID(4263, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Stable Master
                player->SEND_POI(-9466.62, 45.87, 6, 6, 0, "Erma");
                player->SEND_GOSSIP_MENU_TEXTID(5983, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->SEND_GOSSIP_MENU_TEXTID(4264, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->SEND_GOSSIP_MENU_TEXTID(4273, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_elwynnforest(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
                player->SEND_GOSSIP_MENU_TEXTID(4265, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
                player->SEND_GOSSIP_MENU_TEXTID(4266, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
                player->SEND_POI(-9471.12, 33.44, 6, 6, 0, "Zaldimar Wefhellt");
                player->SEND_GOSSIP_MENU_TEXTID(4268, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
                player->SEND_POI(-9469, 108.05, 6, 6, 0, "Brother Wilhelm");
                player->SEND_GOSSIP_MENU_TEXTID(4269, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
                player->SEND_POI(-9461.07, 32.6, 6, 6, 0, "Priestess Josetta");
                player->SEND_GOSSIP_MENU_TEXTID(4267, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Rogue
                player->SEND_POI(-9465.13, 13.29, 6, 6, 0, "Keryn Sylvius");
                player->SEND_GOSSIP_MENU_TEXTID(4270, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Warlock
                player->SEND_POI(-9473.21, -4.08, 6, 6, 0, "Maximillian Crowe");
                player->SEND_GOSSIP_MENU_TEXTID(4272, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Warrior
                player->SEND_POI(-9461.82, 109.50, 6, 6, 0, "Lyria Du Lac");
                player->SEND_GOSSIP_MENU_TEXTID(4271, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_elwynnforest(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(-9057.04, 153.63, 6, 6, 0, "Alchimiste Mallory");
                player->SEND_GOSSIP_MENU_TEXTID(4274, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(-9456.58, 87.90, 6, 6, 0, "Smith Argus");
                player->SEND_GOSSIP_MENU_TEXTID(4275, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-9467.54, -3.16, 6, 6, 0, "Tomas");
                player->SEND_GOSSIP_MENU_TEXTID(4276, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_GOSSIP_MENU_TEXTID(4277, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_GOSSIP_MENU_TEXTID(4278, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(-9456.82, 30.49, 6, 6, 0, "Michelle Belle");
                player->SEND_GOSSIP_MENU_TEXTID(4279, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(-9386.54, -118.73, 6, 6, 0, "Lee Brown");
                player->SEND_GOSSIP_MENU_TEXTID(4280, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
                player->SEND_POI(-9060.70, 149.23, 6, 6, 0, "Herborisme Pomeroy");
                player->SEND_GOSSIP_MENU_TEXTID(4281, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
                player->SEND_POI(-9376.12, -75.23, 6, 6, 0, "Adele Fielder");
                player->SEND_GOSSIP_MENU_TEXTID(4282, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
                player->SEND_GOSSIP_MENU_TEXTID(4283, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
                player->SEND_POI(-9536.91, -1212.76, 6, 6, 0, "Helene Peltskinner");
                player->SEND_GOSSIP_MENU_TEXTID(4284, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
                player->SEND_POI(-9376.12, -75.23, 6, 6, 0, "Eldrin");
                player->SEND_GOSSIP_MENU_TEXTID(4285, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_elwynnforestAI(creature);
    }
};


class guard_eversong : public CreatureScript
{
public:
    guard_eversong() : CreatureScript("guard_eversong")
    { }

    class guard_eversongAI : public guardAI
    {
    public:
        guard_eversongAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATHANDLER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->SEND_GOSSIP_MENU_TEXTID(10180,me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_eversong(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_eversong(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_eversong(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_eversong(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bat Handler
                player->SEND_POI(9371.93, -7164.80, 6, 6, 0, "Skymistress Gloaming");
                player->SEND_GOSSIP_MENU_TEXTID(10181, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Guild master
                player->SEND_GOSSIP_MENU_TEXTID(10182, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
                player->SEND_POI(9483.74, -6844.58, 6, 6, 0, "Auberge de Delaniel");
                player->SEND_GOSSIP_MENU_TEXTID(10183, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable Master
                player->SEND_POI(9489.62, -6829.93, 6, 6, 0, "Anathos");
                player->SEND_GOSSIP_MENU_TEXTID(10184, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->SEND_GOSSIP_MENU_TEXTID(10180, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->SEND_GOSSIP_MENU_TEXTID(10180, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_eversong(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
                player->SEND_GOSSIP_MENU_TEXTID(10185, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
                player->SEND_POI(9527.44, -6865.25, 6, 6, 0, "Hannovia");
                player->SEND_GOSSIP_MENU_TEXTID(10186, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
                player->SEND_POI(9464.24, -6855.52, 6, 6, 0, "Garridel");
                player->SEND_GOSSIP_MENU_TEXTID(10187, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
                player->SEND_POI(9517.61, -6871.04, 6, 6, 0, "Noellene");
                player->SEND_GOSSIP_MENU_TEXTID(10189, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
                player->SEND_POI(9467.39, -6845.72, 6, 6, 0, "Ponaris");
                player->SEND_GOSSIP_MENU_TEXTID(10190, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Rogue
                player->SEND_POI(9533.67, -6877.39, 6, 6, 0, "Tannaria");
                player->SEND_GOSSIP_MENU_TEXTID(10191, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Warlock
                player->SEND_POI(9468.99, -6865.60, 6, 6, 0, "Celoenus");
                player->SEND_GOSSIP_MENU_TEXTID(10192, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_eversong(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(8659.90, -6368.12, 6, 6, 0, "Arcaniste Sheynathren");
                player->SEND_GOSSIP_MENU_TEXTID(10193, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(8984.21, -7419.21, 6, 6, 0, "Arathel Sunforge");
                player->SEND_GOSSIP_MENU_TEXTID(10194, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(9494.04, -6881.51, 6, 6, 0, "Quarelestra");
                player->SEND_GOSSIP_MENU_TEXTID(10195, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Engineering
                player->SEND_GOSSIP_MENU_TEXTID(10197, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
                player->SEND_POI(9479.46, -6879.16, 6, 6, 0, "Kanaria");
                player->SEND_GOSSIP_MENU_TEXTID(10198, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Fishing
                player->SEND_GOSSIP_MENU_TEXTID(10199, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Herbalism
                player->SEND_POI(8678.92, -6329.09, 6, 6, 0, "Botanist Tyniarrel");
                player->SEND_GOSSIP_MENU_TEXTID(10200, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Jewelcrafting
                player->SEND_POI(9484.32, -6874.98, 6, 6, 0, "Aleinia");
                player->SEND_GOSSIP_MENU_TEXTID(10203, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
                player->SEND_POI(9362.04, -7130.33, 6, 6, 0, "Sathein");
                player->SEND_GOSSIP_MENU_TEXTID(10204, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
                player->SEND_GOSSIP_MENU_TEXTID(10205, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
                player->SEND_POI(9362.04, -7130.33, 6, 6, 0, "Mathreyn");
                player->SEND_GOSSIP_MENU_TEXTID(10206, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
                player->SEND_POI(8680.36, -6327.51, 6, 6, 0, "Sempstress Ambershine");
                player->SEND_GOSSIP_MENU_TEXTID(10207, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_eversongAI(creature);
    }
};


class guard_exodar : public CreatureScript
{
public:
    guard_exodar() : CreatureScript("guard_exodar")
    { }

    class guard_exodarAI : public guardAI
    {
    public:
        guard_exodarAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_HIPPOGRYPH     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX        , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->SEND_GOSSIP_MENU_TEXTID(9551, me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_exodar(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_exodar(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_exodar(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_exodar(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_exodar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction house
                player->SEND_POI(-4023.6, -11739.3, 6, 6, 0, "Hotel des ventes de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9528, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
                player->SEND_POI(-3923.89, -11544.5, 6, 6, 0, "Banque de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9529, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
                player->SEND_POI(-4092.57, -11626.5, 6, 6, 0, "Maître de guilde de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9539, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Hippogryph master
                player->SEND_POI(-4060.46, -11787.1, 6, 6, 0, "Maître des hyppogryphes de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9530, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Inn
                player->SEND_POI(-3741.87, -11695.1, 6, 6, 0, "Auberge de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9545, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Mailbox
                player->SEND_POI(-3972.5, -11696.0, 6, 6, 0, "Boîte aux lettres");
                player->SEND_GOSSIP_MENU_TEXTID(10254, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Stable master
                player->SEND_POI(-3786.5, -11702.5, 6, 6, 0, "Maître des écuries Arthaid");
                player->SEND_GOSSIP_MENU_TEXTID(9558, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Weapon trainer
                player->SEND_POI(-4215.68, -11628.9, 6, 6, 0, "Maître d'armes Handiir");
                player->SEND_GOSSIP_MENU_TEXTID(9565, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Battlemaster
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARENA, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_EYEOFTHESTORM, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU_TEXTID(9531, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->SEND_GOSSIP_MENU_TEXTID(9533, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 13);
                player->SEND_GOSSIP_MENU_TEXTID(9555, _Creature->GetGUID());
                break;
            }
        }

        void SendBattleMasterMenu_guard_exodar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
                player->SEND_POI(-3978.1, -11357, 6, 6, 0, "Maître de guerre de la Vallée d'Alterac");
                player->SEND_GOSSIP_MENU_TEXTID(9531, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
                player->SEND_POI(-3998.9, -11345.2, 6, 6, 0, "Maître de guerre du Bassin d'Arathi");
                player->SEND_GOSSIP_MENU_TEXTID(9531, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //A
                player->SEND_POI(-3759.27, -11695.63, 6, 6, 0, "Miglik Blotstrom");
                player->SEND_GOSSIP_MENU_TEXTID(10223, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //EOS
                player->SEND_POI(-3978.1, -11357, 6, 6, 0, "Maître de guerre de l'Oeil du Cyclone");
                player->SEND_GOSSIP_MENU_TEXTID(9531, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //WSG
                player->SEND_POI(-3977.5, -11381.2, 6, 6, 0, "Maître de guerre du Goulet des Chanteguerres");
                player->SEND_GOSSIP_MENU_TEXTID(9531, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_exodar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
                player->SEND_POI(-4276.0, -11495, 6, 6, 0, "Maître des druides de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9534, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
                player->SEND_POI(-4210.6, -11575.2, 6, 6, 0, "Maître des chasseurs de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9544, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
                player->SEND_POI(-4057.32, -11556.5, 6, 6, 0, "Maître des mages de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9550, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
                player->SEND_POI(-4191.2, -11470.4, 6, 6, 0, "Maître des paladins de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9553, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
                player->SEND_POI(-3969.63, -11482.8, 6, 6, 0, "Maître des prêtres de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9554, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Shaman
                player->SEND_POI(-3805.5, -11380.7, 6, 6, 0, "Maître des chamans de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9556, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
                player->SEND_POI(-4189.43, -11653.7, 6, 6, 0, "Maître des guerriers de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9562, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_exodar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(-4040.6, -11364.5, 6, 6, 0, "Maître des alchimistes de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9527, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(-4229.5, -11706, 6, 6, 0, "Maître des forgerons de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9532, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-3798.3, -11651.7, 6, 6, 0, "Maître des cuisiniers de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9551, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(-3889.3, -11495, 6, 6, 0, "Maître des enchanteurs de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9535, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_POI(-4257.68, -11640.3, 6, 6, 0, "Maître des ingénieurs de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9536, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(-3769.5, -11479.6, 6, 6, 0, "Maître des premiers soins de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9537, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(-3725.5, -11385.2, 6, 6, 0, "Maître des pêcheurs de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9538, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Jewelcrafting
                player->SEND_POI(-3783, -11546, 6, 6, 0, "Maître des joalliers de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9547, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Herbalism
                player->SEND_POI(-4040.6, -11364.5, 6, 6, 0, "Maître des herboristes de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9543, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Leatherworking
                player->SEND_POI(-4140.6, -11776.7, 6, 6, 0, "Maître des travailleurs du cuir de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9549, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Mining
                player->SEND_POI(-4228, -11697, 6, 6, 0, "Maître des mineurs de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9552, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Skinning
                player->SEND_POI(-4134.97, -11760.5, 6, 6, 0, "Maître des dépeceurs de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9557, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 13:                   //Tailoring
                player->SEND_POI(-4092.5, -11744.5, 6, 6, 0, "Maître des tailleurs de l'Exodar");
                player->SEND_GOSSIP_MENU_TEXTID(9559, _Creature->GetGUID());
                break;
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_exodarAI(creature);
    }
};



class guard_ironforge : public CreatureScript
{
public:
    guard_ironforge() : CreatureScript("guard_ironforge")
    { }

    class guard_ironforgeAI : public guardAI
    {
    public:
        guard_ironforgeAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_IRONFORGE_BANK    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_DEEPRUNTRAM       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GRYPHON           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN               , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            player->SEND_GOSSIP_MENU_TEXTID(2760, me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_ironforge(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_ironforge(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_ironforge(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_ironforge(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_ironforge(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction House
                player->SEND_POI(-4957.39, -911.6, 6, 6, 0, "Hotel des ventes de Forgefer");
                player->SEND_GOSSIP_MENU_TEXTID(3014, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
                player->SEND_POI(-4891.91, -991.47, 6, 6, 0, "La Banque");
                player->SEND_GOSSIP_MENU_TEXTID(2761, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Tram
                player->SEND_POI(-4835.27, -1294.69, 6, 6, 0, "Tram des Profondeurs");
                player->SEND_GOSSIP_MENU_TEXTID(3814, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Gryphon Master
                player->SEND_POI(-4821.52, -1152.3, 6, 6, 0, "Maître des Gryphons de Forgefer");
                player->SEND_GOSSIP_MENU_TEXTID(2762, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Guild Master
                player->SEND_POI(-5021, -996.45, 6, 6, 0, "Centre des Visiteurs de Forgefer");
                player->SEND_GOSSIP_MENU_TEXTID(2764, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Inn
                player->SEND_POI(-4850.47, -872.57, 6, 6, 0, "Taverne Stonefire");
                player->SEND_GOSSIP_MENU_TEXTID(2768, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Mailbox
                player->SEND_POI(-4845.7, -880.55, 6, 6, 0, "Boîte aux lettres de Forgefer");
                player->SEND_GOSSIP_MENU_TEXTID(2769, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Stable Master
                player->SEND_POI(-5010.2, -1262, 6, 6, 0, "Ulbrek Firehand");
                player->SEND_GOSSIP_MENU_TEXTID(5986, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Weapons Trainer
                player->SEND_POI(-5040, -1201.88, 6, 6, 0, "Bixi et Buliwyf");
                player->SEND_GOSSIP_MENU_TEXTID(4518, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Battlemaster
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(7529, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Class Trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->SEND_GOSSIP_MENU_TEXTID(2766, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Profession Trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->SEND_GOSSIP_MENU_TEXTID(2793, _Creature->GetGUID());
                break;
            }
        }

        void SendBattleMasterMenu_guard_ironforge(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
                player->SEND_POI(-5047.87, -1263.77, 6, 6, 0, "Glordrum Steelbeard");
                player->SEND_GOSSIP_MENU_TEXTID(7483, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
                player->SEND_POI(-5038.37, -1266.39, 6, 6, 0, "Donal Osgood");
                player->SEND_GOSSIP_MENU_TEXTID(7649, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
                player->SEND_POI(-5037.24, -1274.82, 6, 6, 0, "Lylandris");
                player->SEND_GOSSIP_MENU_TEXTID(7528, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_ironforge(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
                player->SEND_POI(-5023, -1253.68, 6, 6, 0, "Hall of Arms");
                player->SEND_GOSSIP_MENU_TEXTID(2770, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
                player->SEND_POI(-4627, -926.45, 6, 6, 0, "Hall des Mystères");
                player->SEND_GOSSIP_MENU_TEXTID(2771, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Paladin
                player->SEND_POI(-4627.02, -926.45, 6, 6, 0, "Hall des Mystères");
                player->SEND_GOSSIP_MENU_TEXTID(2773, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Priest
                player->SEND_POI(-4627, -926.45, 6, 6, 0, "Hall des Mystères");
                player->SEND_GOSSIP_MENU_TEXTID(2772, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Rogue
                player->SEND_POI(-4647.83, -1124, 6, 6, 0, "Maître des voleurs de Forgefer");
                player->SEND_GOSSIP_MENU_TEXTID(2774, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
                player->SEND_POI(-4605, -1110.45, 6, 6, 0, "Maître des démonistes de Forgefer");
                player->SEND_GOSSIP_MENU_TEXTID(2775, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
                player->SEND_POI(-5023.08, -1253.68, 6, 6, 0, "Hall of Arms");
                player->SEND_GOSSIP_MENU_TEXTID(2776, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Shaman
                player->SEND_POI(-4732, -1147, 6, 6, 0, "Maître des chamans de Forgefer");
                //incorrect id
                player->SEND_GOSSIP_MENU_TEXTID(2766, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_ironforge(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(-4858.5, -1241.83, 6, 6, 0, "Potions et Mélanges de Berryfizz");
                player->SEND_GOSSIP_MENU_TEXTID(2794, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(-4796.97, -1110.17, 6, 6, 0, "La grande Forge");
                player->SEND_GOSSIP_MENU_TEXTID(2795, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-4767.83, -1184.59, 6, 6, 0, "La marmite de bronze");
                player->SEND_GOSSIP_MENU_TEXTID(2796, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(-4803.72, -1196.53, 6, 6, 0, "Arcanisterie de Thistlefuzz");
                player->SEND_GOSSIP_MENU_TEXTID(2797, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_POI(-4799.56, -1250.23, 6, 6, 0, "Gadgets de Springspindle");
                player->SEND_GOSSIP_MENU_TEXTID(2798, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(-4881.6, -1153.13, 6, 6, 0, "Physicien de Forgefer");
                player->SEND_GOSSIP_MENU_TEXTID(2799, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(-4597.91, -1091.93, 6, 6, 0, "Pêcheur voyageur");
                player->SEND_GOSSIP_MENU_TEXTID(2800, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
                player->SEND_POI(-4876.9, -1151.92, 6, 6, 0, "Physicien de Forgefer");
                player->SEND_GOSSIP_MENU_TEXTID(2801, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
                player->SEND_POI(-4745, -1027.57, 6, 6, 0, "Biens en cuir de Finespindle");
                player->SEND_GOSSIP_MENU_TEXTID(2802, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Minning
                player->SEND_POI(-4705.06, -1116.43, 6, 6, 0, "Guildes des mineurs de Deepmountain");
                player->SEND_GOSSIP_MENU_TEXTID(2804, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
                player->SEND_POI(-4745, -1027.57, 6, 6, 0, "Biens en cuir de Finespindle");
                player->SEND_GOSSIP_MENU_TEXTID(2805, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
                player->SEND_POI(-4719.60, -1056.96, 6, 6, 0, "Tailleur Stonebrow");
                player->SEND_GOSSIP_MENU_TEXTID(2807, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_ironforgeAI(creature);
    }
};


class guard_mulgore : public CreatureScript
{
public:
    guard_mulgore() : CreatureScript("guard_mulgore")
    { }

    class guard_mulgoreAI : public guardAI
    {
    public:
        guard_mulgoreAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->SEND_GOSSIP_MENU_TEXTID(3543,me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_mulgore(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_mulgore(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_mulgore(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_mulgore(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
                player->SEND_GOSSIP_MENU_TEXTID(4051, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Wind rider
                player->SEND_GOSSIP_MENU_TEXTID(4052, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
                player->SEND_POI(-2361.38, -349.19, 6, 6, 0, "Auberge de Sabot-de-Sang");
                player->SEND_GOSSIP_MENU_TEXTID(4053, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable master
                player->SEND_POI(-2338.86, -357.56, 6, 6, 0, "Seikwa");
                player->SEND_GOSSIP_MENU_TEXTID(5976, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->SEND_GOSSIP_MENU_TEXTID(4069, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->SEND_GOSSIP_MENU_TEXTID(4070, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_mulgore(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
                player->SEND_POI(-2312.15, -443.69, 6, 6, 0, "Gennia Runetotem");
                player->SEND_GOSSIP_MENU_TEXTID(4054, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
                player->SEND_POI(-2178.14, -406.14, 6, 6, 0, "Yaw Sharpmane");
                player->SEND_GOSSIP_MENU_TEXTID(4055, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Shaman
                player->SEND_POI(-2301.5, -439.87, 6, 6, 0, "Narm Skychaser");
                player->SEND_GOSSIP_MENU_TEXTID(4056, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Warrior
                player->SEND_POI(-2345.43, -494.11, 6, 6, 0, "Krang Stonehoof");
                player->SEND_GOSSIP_MENU_TEXTID(4057, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_mulgore(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_GOSSIP_MENU_TEXTID(4058, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_GOSSIP_MENU_TEXTID(4059, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-2263.34, -287.91, 6, 6, 0, "Pyall Silentstride");
                player->SEND_GOSSIP_MENU_TEXTID(4060, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_GOSSIP_MENU_TEXTID(4061, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
                player->SEND_POI(-2353.52, -355.82, 6, 6, 0, "Vira Younghoof");
                player->SEND_GOSSIP_MENU_TEXTID(4062, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Fishing
                player->SEND_POI(-2349.21, -241.37, 6, 6, 0, "Uthan Stillwater");
                player->SEND_GOSSIP_MENU_TEXTID(4063, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Herbalism
                player->SEND_GOSSIP_MENU_TEXTID(4064, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Leatherworking
                player->SEND_POI(-2257.12, -288.63, 6, 6, 0, "Chaw Stronghide");
                player->SEND_GOSSIP_MENU_TEXTID(4065, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Mining
                player->SEND_GOSSIP_MENU_TEXTID(4066, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Skinning
                player->SEND_POI(-2252.94, -291.32, 6, 6, 0, "Yonn Deepcut");
                player->SEND_GOSSIP_MENU_TEXTID(4067, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Tailoring
                player->SEND_GOSSIP_MENU_TEXTID(4068, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_mulgoreAI(creature);
    }
};


class guard_orgrimmar : public CreatureScript
{
public:
    guard_orgrimmar() : CreatureScript("guard_orgrimmar")
    { }

    class guard_orgrimmarAI : public guardAI
    {
    public:
        guard_orgrimmarAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_ZEPPLINMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_OFFICERS      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
            player->SEND_GOSSIP_MENU_TEXTID(2593,me->GetGUID());

            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_orgrimmar(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_orgrimmar(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_orgrimmar(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_orgrimmar(player, me, action); break;
            }
            return true;

        }

        virtual void ReceiveEmote(Player* player, uint32 emote) override
        {
            if( player->GetTeam() == HORDE )
                DoReplyToTextEmote(me,emote);
        }


        void SendDefaultMenu_guard_orgrimmar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
                player->SEND_POI(1631.51, -4375.33, 6, 6, 0, "Banque d'Orgrimmar");
                player->SEND_GOSSIP_MENU_TEXTID(2554, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //wind rider
                player->SEND_POI(1676.6, -4332.72, 6, 6, 0, "La tour du Ciel");
                player->SEND_GOSSIP_MENU_TEXTID(2555, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //guild master
                player->SEND_POI(1576.93, -4294.75, 6, 6, 0, "Embassade de la Horde");
                player->SEND_GOSSIP_MENU_TEXTID(2556, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
                player->SEND_POI(1644.51, -4447.27, 6, 6, 0, "Auberge d'Orgrimmar");
                player->SEND_GOSSIP_MENU_TEXTID(2557, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //mailbox
                player->SEND_POI(1622.53, -4388.79, 6, 6, 0, "Boîte aux lettres d'Orgrimmar");
                player->SEND_GOSSIP_MENU_TEXTID(2558, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //auction house
                player->SEND_POI(1679.21, -4450.1, 6, 6, 0, "Hotel des ventes d'Orgrimmar");
                player->SEND_GOSSIP_MENU_TEXTID(3075, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //zeppelin
                player->SEND_POI(1337.36, -4632.7, 6, 6, 0, "Tour des zeppelins d'Orgrimmar");
                player->SEND_GOSSIP_MENU_TEXTID(3173, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //weapon master
                player->SEND_POI(2092.56, -4823.95, 6, 6, 0, "Sayoc & Hanashi");
                player->SEND_GOSSIP_MENU_TEXTID(4519, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //stable master
                player->SEND_POI(2133.12, -4663.93, 6, 6, 0, "Xon'cha");
                player->SEND_GOSSIP_MENU_TEXTID(5974, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //officers lounge
                player->SEND_POI(1633.56, -4249.37, 6, 6, 0, "Hall des Légendes");
                player->SEND_GOSSIP_MENU_TEXTID(7046, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //battlemaster
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(7521, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->SEND_GOSSIP_MENU_TEXTID(2599, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 13:                   //profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->SEND_GOSSIP_MENU_TEXTID(2594, _Creature->GetGUID());
                break;
            }
        }

        void SendBattleMasterMenu_guard_orgrimmar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
                player->SEND_POI(1983.92, -4794.2, 6, 6, 0, "Hall des Braves");
                player->SEND_GOSSIP_MENU_TEXTID(7484, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
                player->SEND_POI(1983.92, -4794.2, 6, 6, 0, "Hall des Braves");
                player->SEND_GOSSIP_MENU_TEXTID(7644, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
                player->SEND_POI(1983.92, -4794.2, 6, 6, 0, "Hall des Braves");
                player->SEND_GOSSIP_MENU_TEXTID(7520, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_orgrimmar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
                player->SEND_POI(2114.84, -4625.31, 6, 6, 0, "Hall du chasseur d'Orgrimmar");
                player->SEND_GOSSIP_MENU_TEXTID(2559, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
                player->SEND_POI(1451.26, -4223.33, 6, 6, 0, "Darkbriar Lodge");
                player->SEND_GOSSIP_MENU_TEXTID(2560, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
                player->SEND_POI(1442.21, -4183.24, 6, 6, 0, "Spirit Lodge");
                player->SEND_GOSSIP_MENU_TEXTID(2561, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Shaman
                player->SEND_POI(1925.34, -4181.89, 6, 6, 0, "Forteresse de Thrall");
                player->SEND_GOSSIP_MENU_TEXTID(2562, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Rogue
                player->SEND_POI(1773.39, -4278.97, 6, 6, 0, "Confrérie Shadowswift");
                player->SEND_GOSSIP_MENU_TEXTID(2563, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
                player->SEND_POI(1849.57, -4359.68, 6, 6, 0, "Darkfire Enclave");
                player->SEND_GOSSIP_MENU_TEXTID(2564, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
                player->SEND_POI(1983.92, -4794.2, 6, 6, 0, "Hall des Braves");
                player->SEND_GOSSIP_MENU_TEXTID(2565, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Paladin
                player->SEND_POI(1906.65, -4134.26, 6, 6, 0, "Vallée de la Sagesse");
                player->SEND_GOSSIP_MENU_TEXTID(10843, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_orgrimmar(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(1955.17, -4475.79, 6, 6, 0, "Alchimie et potions de Yelmak");
                player->SEND_GOSSIP_MENU_TEXTID(2497, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(2054.34, -4831.85, 6, 6, 0, "L'enclume brûlante");
                player->SEND_GOSSIP_MENU_TEXTID(2499, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(1780.96, -4481.31, 6, 6, 0, "Borstan's Firepit");
                player->SEND_GOSSIP_MENU_TEXTID(2500, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(1917.5, -4434.95, 6, 6, 0, "Godan's Runeworks");
                player->SEND_GOSSIP_MENU_TEXTID(2501, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_POI(2038.45, -4744.75, 6, 6, 0, "Magasin de machines de Nogg");
                player->SEND_GOSSIP_MENU_TEXTID(2653, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(1485.21, -4160.91, 6, 6, 0, "Survie du plus apte");
                player->SEND_GOSSIP_MENU_TEXTID(2502, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(1994.15, -4655.7, 6, 6, 0, "Pêche Lumak");
                player->SEND_GOSSIP_MENU_TEXTID(2503, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
                player->SEND_POI(1898.61, -4454.93, 6, 6, 0, "Herborisme Jandi");
                player->SEND_GOSSIP_MENU_TEXTID(2504, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
                player->SEND_POI(1852.82, -4562.31, 6, 6, 0, "Travailleurs du cuirs Kodohide");
                player->SEND_GOSSIP_MENU_TEXTID(2513, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
                player->SEND_POI(2029.79, -4704, 6, 6, 0, "Minage du Canyon Rouge");
                player->SEND_GOSSIP_MENU_TEXTID(2515, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
                player->SEND_POI(1852.82, -4562.31, 6, 6, 0, "Travailleurs du cuirs Kodohide");
                player->SEND_GOSSIP_MENU_TEXTID(2516, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
                player->SEND_POI(1802.66, -4560.66, 6, 6, 0, "Biens en tissu Magar");
                player->SEND_GOSSIP_MENU_TEXTID(2518, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_orgrimmarAI(creature);
    }
};


class guard_shattrath : public CreatureScript
{
public:
    guard_shattrath() : CreatureScript("guard_shattrath")
    { }

    class guard_shattrathAI : public guardAI
    {
    public:
        guard_shattrathAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAVERN                       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK                         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN                          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_FLIGHTMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX                      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MANALOOM                     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMYLAB                   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GEMMERCHANT                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->SEND_GOSSIP_MENU_TEXTID(10321, me->GetGUID());

            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:              SendDefaultMenu_guard_shattrath(player, me, action); break;
                case GOSSIP_SENDER_SEC_BANK:          SendBankMenu_guard_shattrath(player, me, action); break;
                case GOSSIP_SENDER_SEC_INN:           SendInnMenu_guard_shattrath(player, me, action); break;
                case GOSSIP_SENDER_SEC_STABLEMASTER:  SendStableMasterMenu_guard_shattrath(player, me, action); break;
                case GOSSIP_SENDER_SEC_GEMMERCHANT:   SendGemMerchantMenu_guard_shattrath(player, me, action); break;
                case GOSSIP_SENDER_SEC_MAILBOX:       SendMailboxMenu_guard_shattrath(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:     SendProfTrainerMenu_guard_shattrath(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:    SendBattleMasterMenu_guard_shattrath(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_shattrath(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Tavern
                player->SEND_POI(-1759.5, 5165, 6, 6, 0, "Taverne du Bout du Monde");
                player->SEND_GOSSIP_MENU_TEXTID(10394, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANKALDOR, GOSSIP_SENDER_SEC_BANK, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANKSCYERS, GOSSIP_SENDER_SEC_BANK, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(10379, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INNALDOR, GOSSIP_SENDER_SEC_INN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INNSCYERS, GOSSIP_SENDER_SEC_INN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(10382, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Flight master
                player->SEND_POI(-1832, 5299, 6, 6, 0, "Maître de vol");
                player->SEND_GOSSIP_MENU_TEXTID(10385, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANKALDOR, GOSSIP_SENDER_SEC_MAILBOX, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INNALDOR, GOSSIP_SENDER_SEC_MAILBOX, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANKSCYERS, GOSSIP_SENDER_SEC_MAILBOX, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INNSCYERS, GOSSIP_SENDER_SEC_MAILBOX, GOSSIP_ACTION_INFO_DEF + 4);
                player->SEND_GOSSIP_MENU_TEXTID(10386, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Stable master
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEALDOR, GOSSIP_SENDER_SEC_STABLEMASTER, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLESCYERS, GOSSIP_SENDER_SEC_STABLEMASTER, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(10387, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Battlemaster
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERALLIANCE, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERHORDE, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERARENA, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(10388, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Profession master
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->SEND_GOSSIP_MENU_TEXTID(10391, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Mana Loom
                player->SEND_POI(-2070, 5265.5, 6, 6, 0, "Métier à tisser le mana");
                player->SEND_GOSSIP_MENU_TEXTID(10503, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Alchemy Lab
                player->SEND_POI(-1648.5, 5540, 6, 6, 0, "Laboratoire d'alchimie");
                player->SEND_GOSSIP_MENU_TEXTID(10321, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Gem Merchant
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GEMALDOR, GOSSIP_SENDER_SEC_GEMMERCHANT, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GEMSCYERS, GOSSIP_SENDER_SEC_GEMMERCHANT, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(10697, _Creature->GetGUID());
                break;
            }
        }

        void SendBankMenu_guard_shattrath(Player *player, Creature *_Creature, uint32 action)
        {
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                player->SEND_POI(-1730.5, 5496, 6, 6, 0, "Banque de l'Aldor");
                player->SEND_GOSSIP_MENU_TEXTID(10380, _Creature->GetGUID());
            }
            if (action == GOSSIP_ACTION_INFO_DEF + 2)
            {
                player->SEND_POI(-1997.7, 5363, 6, 6, 0, "Banque des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10381, _Creature->GetGUID());
            }
        }

        void SendInnMenu_guard_shattrath(Player *player, Creature *_Creature, uint32 action)
        {
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                player->SEND_POI(-1895, 5767, 6, 6, 0, "Auberge de l'Aldor");
                player->SEND_GOSSIP_MENU_TEXTID(10383, _Creature->GetGUID());
            }
            if (action == GOSSIP_ACTION_INFO_DEF + 2)
            {
                player->SEND_POI(-2178, 5405, 6, 6, 0, "Auberge des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10384, _Creature->GetGUID());
            }
        }

        void SendMailboxMenu_guard_shattrath(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->SEND_POI(-1730.5, 5496, 6, 6, 0, "Banque de l'Aldor");
                player->SEND_GOSSIP_MENU_TEXTID(10380, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->SEND_POI(-1895, 5767, 6, 6, 0, "Auberge de l'Aldor");
                player->SEND_GOSSIP_MENU_TEXTID(10383, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->SEND_POI(-1997.7, 5363, 6, 6, 0, "Banque des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10381, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->SEND_POI(-2178, 5405, 6, 6, 0, "Auberge des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10384, _Creature->GetGUID());
                break;
            }
        }

        void SendStableMasterMenu_guard_shattrath(Player *player, Creature *_Creature, uint32 action)
        {
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                player->SEND_POI(-1888.5, 5761, 6, 6, 0, "Ecuries de l'Aldor");
                player->SEND_GOSSIP_MENU_TEXTID(10321, _Creature->GetGUID());
            }
            if (action == GOSSIP_ACTION_INFO_DEF + 2)
            {
                player->SEND_POI(-2170, 5404, 6, 6, 0, "Ecuries des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10321, _Creature->GetGUID());
            }
        }

        void SendBattleMasterMenu_guard_shattrath(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->SEND_POI(-1774, 5251, 6, 6, 0, "Maîtres de guerre de l'Alliance");
                player->SEND_GOSSIP_MENU_TEXTID(10389, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->SEND_POI(-1963, 5263, 6, 6, 0, "Maîtres de guerre de la Horde");
                player->SEND_GOSSIP_MENU_TEXTID(10390, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->SEND_POI(-1960, 5175, 6, 6, 0, "Maîtres de guerre de l'arène");
                player->SEND_GOSSIP_MENU_TEXTID(12510, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_shattrath(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(-1648.5, 5534, 6, 6, 0, "Lorokeem");
                player->SEND_GOSSIP_MENU_TEXTID(10392, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(-1847, 5222, 6, 6, 0, "Kradu Grimblade and Zula Slagfury");
                player->SEND_GOSSIP_MENU_TEXTID(10400, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-2067.4, 5316.5, 6, 6, 0, "Jack Trapper");
                player->SEND_GOSSIP_MENU_TEXTID(10393, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(-2263.5, 5563.5, 6, 6, 0, "Haut Enchanteur Bardolan");
                player->SEND_GOSSIP_MENU_TEXTID(10395, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
                player->SEND_POI(-1591, 5265.5, 6, 6, 0, "Mildred Fletcher");
                player->SEND_GOSSIP_MENU_TEXTID(10396, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Jewelcrafting
                player->SEND_POI(-1654, 5667.5, 6, 6, 0, "Hamanar");
                player->SEND_GOSSIP_MENU_TEXTID(10397, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
                player->SEND_POI(-2060.5, 5256.5, 6, 6, 0, "Darmari");
                player->SEND_GOSSIP_MENU_TEXTID(10399, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
                player->SEND_POI(-2048, 5300, 6, 6, 0, "Seymour");
                player->SEND_GOSSIP_MENU_TEXTID(10398, _Creature->GetGUID());
                break;
            }
        }

        void SendGemMerchantMenu_guard_shattrath(Player *player, Creature *_Creature, uint32 action)
        {
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                player->SEND_POI(-1645, 5669.5, 6, 6, 0, "Marchand de gemmes de l'Aldor");
                player->SEND_GOSSIP_MENU_TEXTID(10698, _Creature->GetGUID());
            }
            if (action == GOSSIP_ACTION_INFO_DEF + 2)
            {
                player->SEND_POI(-2193, 5424.5, 6, 6, 0, "Marchand de gemmes des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10699, _Creature->GetGUID());
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_shattrathAI(creature);
    }
};

#define SPELL_BANISHED_SHATTRATH_A  36642
#define SPELL_BANISHED_SHATTRATH_S  36671
#define SPELL_BANISH_TELEPORT       36643
#define SPELL_EXILE                 39533


class guard_shattrath_aldor : public CreatureScript
{
public:
    guard_shattrath_aldor() : CreatureScript("guard_shattrath_aldor")
    { }

    class guard_shattrath_aldorAI : public guard_shattrath::guard_shattrathAI
    {
        public:
        guard_shattrath_aldorAI(Creature *c) : guard_shattrath::guard_shattrathAI(c) {}
    
        uint32 Exile_Timer;
        uint32 Banish_Timer;
        uint64 playerGUID;
        bool CanTeleport;
    
        void Reset()
        override {
            Banish_Timer = 5000;
            Exile_Timer = 8500;
            playerGUID = 0;
            CanTeleport = false;
        }
    
        void EnterCombat(Unit *who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            if( CanTeleport )
            {
                if( Exile_Timer < diff )
                {
                    if( Unit* temp = ObjectAccessor::GetUnit(*me,playerGUID) )
                    {
                        temp->CastSpell(temp,SPELL_EXILE,true);
                        temp->CastSpell(temp,SPELL_BANISH_TELEPORT,true);
                    }
                    playerGUID = 0;
                    Exile_Timer = 8500;
                    CanTeleport = false;
                }else Exile_Timer -= diff;
            }
            else if( Banish_Timer < diff )
            {
                Unit* temp = me->GetVictim();
                if( temp && temp->GetTypeId() == TYPEID_PLAYER )
                {
                    DoCast(temp,SPELL_BANISHED_SHATTRATH_A);
                    Banish_Timer = 9000;
                    playerGUID = temp->GetGUID();
                    if( playerGUID )
                        CanTeleport = true;
                }
            }else Banish_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAVERN                       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK                         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN                          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_FLIGHTMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX                      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MANALOOM                     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMYLAB                   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GEMMERCHANT                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->SEND_GOSSIP_MENU_TEXTID(10524, me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_shattrath_aldor(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_shattrath_aldor(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_shattrath(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_shattrath_aldor(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Tavern
                player->SEND_POI(-1759.5, 5165, 6, 6, 0, "Taverne du Bout du Monde");
                player->SEND_GOSSIP_MENU_TEXTID(10394, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
                player->SEND_POI(-1730.5, 5496, 6, 6, 0, "Banque de l'Aldor");
                player->SEND_GOSSIP_MENU_TEXTID(10380, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
                player->SEND_POI(-1895, 5767, 6, 6, 0, "Auberge de l'Aldor");
                player->SEND_GOSSIP_MENU_TEXTID(10525, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Flight master
                player->SEND_POI(-1832, 5299, 6, 6, 0, "Maître de vol de Shattrath");
                player->SEND_GOSSIP_MENU_TEXTID(10402, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
                player->SEND_POI(0, 0, 6, 6, 0, "Boîte aux lettres de Shattrath");
                //unknown
                player->SEND_GOSSIP_MENU_TEXTID(10524, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Stable master
                player->SEND_POI(-1888.5, 5761, 6, 6, 0, "Maître des écuries de l'Aldor");
                player->SEND_GOSSIP_MENU_TEXTID(10527, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Battlemaster
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERALLIANCE, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERHORDE, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERARENA, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(10388, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Profession master
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->SEND_GOSSIP_MENU_TEXTID(10391, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Mana Loom
                player->SEND_POI(-2070, 5265.5, 6, 6, 0, "Métier à tisser le mana");
                player->SEND_GOSSIP_MENU_TEXTID(10522, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Alchemy Lab
                player->SEND_POI(-1648.5, 5540, 6, 6, 0, "Laboratoire d'alchimie");
                player->SEND_GOSSIP_MENU_TEXTID(10696, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Gem Merchant
                player->SEND_POI(-1645, 5669.5, 6, 6, 0, "Marchand de gemms de l'Aldor");
                player->SEND_GOSSIP_MENU_TEXTID(10411, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_shattrath_aldor(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(-1648.5, 5534, 6, 6, 0, "Lorokeem");
                player->SEND_GOSSIP_MENU_TEXTID(10392, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(-1847, 5222, 6, 6, 0, "Kradu Grimblade and Zula Slagfury");
                player->SEND_GOSSIP_MENU_TEXTID(10400, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-2067.4, 5316.5, 6, 6, 0, "Jack Trapper");
                player->SEND_GOSSIP_MENU_TEXTID(10393, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(-2263.5, 5563.5, 6, 6, 0, "Haut Enchanteur Bardolan");
                player->SEND_GOSSIP_MENU_TEXTID(10528, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
                player->SEND_POI(-1591, 5265.5, 6, 6, 0, "Mildred Fletcher");
                player->SEND_GOSSIP_MENU_TEXTID(10396, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Jewelcrafting
                player->SEND_POI(-1654, 5667.5, 6, 6, 0, "Hamanar");
                player->SEND_GOSSIP_MENU_TEXTID(10529, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
                player->SEND_POI(-2060.5, 5256.5, 6, 6, 0, "Darmari");
                player->SEND_GOSSIP_MENU_TEXTID(10399, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
                player->SEND_POI(-2048, 5300, 6, 6, 0, "Seymour");
                player->SEND_GOSSIP_MENU_TEXTID(10419, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_shattrath_aldorAI(creature);
    }
};


class guard_shattrath_scryer : public CreatureScript
{
public:
    guard_shattrath_scryer() : CreatureScript("guard_shattrath_scryer")
    { }

    class guard_shattrath_scryerAI : public guard_shattrath::guard_shattrathAI
    {
        public:
        guard_shattrath_scryerAI(Creature *c) : guard_shattrath::guard_shattrathAI(c) {}
    
        uint32 Exile_Timer;
        uint32 Banish_Timer;
        uint64 playerGUID;
        bool CanTeleport;
    
        void Reset()
        override {
            Banish_Timer = 5000;
            Exile_Timer = 8500;
            playerGUID = 0;
            CanTeleport = false;
        }
    
        void EnterCombat(Unit *who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            if( CanTeleport )
            {
                if( Exile_Timer < diff )
                {
                    if( Unit* temp = ObjectAccessor::GetUnit(*me,playerGUID) )
                    {
                        temp->CastSpell(temp,SPELL_EXILE,true);
                        temp->CastSpell(temp,SPELL_BANISH_TELEPORT,true);
                    }
                    playerGUID = 0;
                    Exile_Timer = 8500;
                    CanTeleport = false;
                }else Exile_Timer -= diff;
            }
            else if( Banish_Timer < diff )
            {
                Unit* temp = me->GetVictim();
                if( temp && temp->GetTypeId() == TYPEID_PLAYER )
                {
                    DoCast(temp,SPELL_BANISHED_SHATTRATH_S);
                    Banish_Timer = 9000;
                    playerGUID = temp->GetGUID();
                    if( playerGUID )
                        CanTeleport = true;
                }
            }else Banish_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAVERN                       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK                         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN                          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_FLIGHTMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX                      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MANALOOM                     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMYLAB                   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GEMMERCHANT                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->SEND_GOSSIP_MENU_TEXTID(10430, me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_shattrath_scryer(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_shattrath_scryer(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_shattrath(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_shattrath_scryer(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Tavern
                player->SEND_POI(-1759.5, 5165, 6, 6, 0, "Taverne du Bout du Monde");
                player->SEND_GOSSIP_MENU_TEXTID(10431, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
                player->SEND_POI(-1996.6, 5363.7, 6, 6, 0, "Banque des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10432, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
                player->SEND_POI(-2176.6, 5405.8, 6, 6, 0, "Auberge des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10433, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Flight master
                player->SEND_POI(-1832, 5299, 6, 6, 0, "Maître de vol de Shattrath");
                player->SEND_GOSSIP_MENU_TEXTID(10435, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
                player->SEND_POI(-2174.3, 5411.4, 6, 6, 0, "Boîte aux lettres des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10436, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Stable master
                player->SEND_POI(-2169.9, 5405.1, 6, 6, 0, "Maître des écuries des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10437, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Battlemaster
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERALLIANCE, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERHORDE, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERARENA, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(10438, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Profession master
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->SEND_GOSSIP_MENU_TEXTID(10504, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Mana Loom
                player->SEND_POI(-2070, 5265.5, 6, 6, 0, "Métier à tisser le mana");
                player->SEND_GOSSIP_MENU_TEXTID(10522, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Alchemy Lab
                player->SEND_POI(-1648.5, 5540, 6, 6, 0, "Laboratoire d'alchimie");
                player->SEND_GOSSIP_MENU_TEXTID(10701, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Gem Merchant
                player->SEND_POI(-1645, 5669.5, 6, 6, 0, "Marchand de gemmes des Clairvoyants");
                player->SEND_GOSSIP_MENU_TEXTID(10702, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_shattrath_scryer(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(-1648.5, 5534, 6, 6, 0, "Lorokeem");
                player->SEND_GOSSIP_MENU_TEXTID(10516, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(-1847, 5222, 6, 6, 0, "Kradu Grimblade and Zula Slagfury");
                player->SEND_GOSSIP_MENU_TEXTID(10517, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-2067.4, 5316.5, 6, 6, 0, "Jack Trapper");
                player->SEND_GOSSIP_MENU_TEXTID(10518, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(-2263.5, 5563.5, 6, 6, 0, "Haut Enchanteur Bardolan");
                player->SEND_GOSSIP_MENU_TEXTID(10519, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
                player->SEND_POI(-1591, 5265.5, 6, 6, 0, "Mildred Fletcher");
                player->SEND_GOSSIP_MENU_TEXTID(10520, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Jewelcrafting
                player->SEND_POI(-1654, 5667.5, 6, 6, 0, "Hamanar");
                player->SEND_GOSSIP_MENU_TEXTID(10521, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
                player->SEND_POI(-2060.5, 5256.5, 6, 6, 0, "Darmari");
                player->SEND_GOSSIP_MENU_TEXTID(10523, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
                player->SEND_POI(-2048, 5300, 6, 6, 0, "Seymour");
                player->SEND_GOSSIP_MENU_TEXTID(10523, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_shattrath_scryerAI(creature);
    }
};


class guard_silvermoon : public CreatureScript
{
public:
    guard_silvermoon() : CreatureScript("guard_silvermoon")
    { }

    class guard_silvermoonAI : public guardAI
    {
    public:
        guard_silvermoonAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX        , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->SEND_GOSSIP_MENU_TEXTID(9316, me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:                SendDefaultMenu_guard_silvermoon(player, me, action); break;
                case GOSSIP_SENDER_SEC_AUCTIONHOUSE:    SendAuctionhouseMenu_guard_silvermoon(player, me, action); break;
                case GOSSIP_SENDER_SEC_INN:             SendInnMenu_guard_silvermoon(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:      SendClassTrainerMenu_guard_silvermoon(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:       SendProfTrainerMenu_guard_silvermoon(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:      SendBattleMasterMenu_guard_silvermoon(player, me, action); break;
            }
            return true;

        }


        void SendDefaultMenu_guard_silvermoon(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction house
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AH_SILVERMOON_1, GOSSIP_SENDER_SEC_AUCTIONHOUSE, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AH_SILVERMOON_2, GOSSIP_SENDER_SEC_AUCTIONHOUSE, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(9317, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
                player->SEND_POI(9808.4, -7488.16, 6, 6, 0, "Banque de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9322, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
                player->SEND_POI(9474.97, -7345.21, 6, 6, 0, "Tandrine");
                player->SEND_GOSSIP_MENU_TEXTID(9324, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN_SILVERMOON_1, GOSSIP_SENDER_SEC_INN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN_SILVERMOON_2, GOSSIP_SENDER_SEC_INN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(9602, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
                player->SEND_POI(9658.33, -7492.17, 6, 6, 0, "Boîte aux lettres de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9326, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Stable master
                player->SEND_POI(9904.95, -7404.31, 6, 6, 0, "Shalenn");
                player->SEND_GOSSIP_MENU_TEXTID(9327, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Weapon trainer
                player->SEND_POI(9841.17, -7505.13, 6, 6, 0, "Ileda");
                player->SEND_GOSSIP_MENU_TEXTID(9328, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Wind master
                player->SEND_POI(9378.45, -7163.94, 6, 6, 0, "Maître de vol de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(10181, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Battlemaster
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARENA, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_EYEOFTHESTORM, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU_TEXTID(9329, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->SEND_GOSSIP_MENU_TEXTID(9331, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 13);
                player->SEND_GOSSIP_MENU_TEXTID(9338, _Creature->GetGUID());
                break;
            }
        }

        void SendAuctionhouseMenu_guard_silvermoon(Player *player, Creature *_Creature, uint32 action)
        {
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                player->SEND_POI(9644.47, -7140.22, 6, 6, 0, "Hotel des ventes de l'Ouest");
                player->SEND_GOSSIP_MENU_TEXTID(9318, _Creature->GetGUID());
            }
            if (action == GOSSIP_ACTION_INFO_DEF + 2)
            {
                player->SEND_POI(9683.27, -7521.22, 6, 6, 0, "Hotel des ventes Royal Exchange");
                player->SEND_GOSSIP_MENU_TEXTID(9319, _Creature->GetGUID());
            }
        }

        void SendInnMenu_guard_silvermoon(Player *player, Creature *_Creature, uint32 action)
        {
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                player->SEND_POI(9677.7, -7368, 6, 6, 0, "Auberge de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9325, _Creature->GetGUID());
            }
            if (action == GOSSIP_ACTION_INFO_DEF + 2)
            {
                player->SEND_POI(9561.1, -7517.5, 6, 6, 0, "Auberge des voyageurs");
                player->SEND_GOSSIP_MENU_TEXTID(9603, _Creature->GetGUID());
            }
        }

        void SendBattleMasterMenu_guard_silvermoon(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
                player->SEND_POI(9850.49, -7572.26, 6, 6, 0, "Gurak");
                player->SEND_GOSSIP_MENU_TEXTID(9329, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
                player->SEND_POI(9857.18, -7564.36, 6, 6, 0, "Karen Wentworth");
                player->SEND_GOSSIP_MENU_TEXTID(9329, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //A
                player->SEND_POI(9850.6, -7559.25, 6, 6, 0, "Bipp Glizzitor");
                player->SEND_GOSSIP_MENU_TEXTID(9329, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //EOS
                player->SEND_POI(9857.18, -7564.36, 6, 6, 0, "Karen Wentworth");
                player->SEND_GOSSIP_MENU_TEXTID(9329, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //WSG
                player->SEND_POI(9845.45, -7562.58, 6, 6, 0, "Krukk");
                player->SEND_GOSSIP_MENU_TEXTID(9329, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_silvermoon(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
                player->SEND_POI(9700.55, -7262.57, 6, 6, 0, "Harene Plainwalker");
                player->SEND_GOSSIP_MENU_TEXTID(9330, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
                player->SEND_POI(9927.48, -7426.14, 6, 6, 0, "Zandine");
                player->SEND_GOSSIP_MENU_TEXTID(9332, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
                player->SEND_POI(9995.07, -7118.17, 6, 6, 0, "Quithas");
                player->SEND_GOSSIP_MENU_TEXTID(9333, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
                player->SEND_POI(9850.22, -7516.93, 6, 6, 0, "Champion Bachi");
                player->SEND_GOSSIP_MENU_TEXTID(9334, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
                player->SEND_POI(9926.79, -7066.66, 6, 6, 0, "Belestra");
                player->SEND_GOSSIP_MENU_TEXTID(9335, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Rogue
                player->SEND_POI(9739.88, -7374.33, 6, 6, 0, "Zelanis");
                player->SEND_GOSSIP_MENU_TEXTID(9336, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Warlock
                player->SEND_POI(9787.57, -7284.63, 6, 6, 0, "Alamma");
                player->SEND_GOSSIP_MENU_TEXTID(9337, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_silvermoon(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(9998.09, -7214.36, 6, 6, 0, "Maître des alchimistes de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9316, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(9841.43, -7361.53, 6, 6, 0, "Maître des forgerons de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9340, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(9577.26, -7243.6, 6, 6, 0, "Maître des cuisiniers de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9316, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(9962.57, -7246.18, 6, 6, 0, "Maître des enchanteurs de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9341, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_POI(9820.18, -7329.56, 6, 6, 0, "Maître des ingénieurs de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9316, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(9579.8, -7343.71, 6, 6, 0, "Maître des premiers soins de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9316, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(9602.73, -7328.3, 6, 6, 0, "Maître des pêcheurs de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9316, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Jewelcrafting
                player->SEND_POI(9553.54, -7506.43, 6, 6, 0, "Maître des joalliers de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9346, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Herbalism
                player->SEND_POI(10004.4, -7216.86, 6, 6, 0, "Maître des herboristes de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9316, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Leatherworking
                player->SEND_POI(9503.72, -7430.16, 6, 6, 0, "Maître des travailleurs du cuir de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9347, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Mining
                player->SEND_POI(9805.1, -7355.56, 6, 6, 0, "Maître des mineurs de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9348, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Skinning
                player->SEND_POI(9513.37, -7429.4, 6, 6, 0, "Maître des dépeceurs de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9316, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 13:                   //Tailoring
                player->SEND_POI(9750.55, -7095.28, 6, 6, 0, "Tailleur de Lune-d'Argent");
                player->SEND_GOSSIP_MENU_TEXTID(9350, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_silvermoonAI(creature);
    }
};


class guard_stormwind : public CreatureScript
{
public:
    guard_stormwind() : CreatureScript("guard_stormwind")
    { }

    class guard_stormwindAI : public guardAI
    {
    public:
        guard_stormwindAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STORMWIND_BANK    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_DEEPRUNTRAM       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN               , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GRYPHON           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_OFFICERS          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
            player->SEND_GOSSIP_MENU_TEXTID(933,me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_stormwind(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_stormwind(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_stormwind(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_stormwind(player, me, action); break;
            }
            return true;

        }

        virtual void ReceiveEmote(Player* player, uint32 emote) override
        {
            if( player->GetTeam() == ALLIANCE )
                DoReplyToTextEmote(me,emote);

        }

        void SendDefaultMenu_guard_stormwind(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
                //TODO translate
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction House
                player->SEND_POI(-8811.46, 667.46, 6, 6, 0, "Auction House" /*"Hotel des ventes de Hurlevent"*/);
                player->SEND_GOSSIP_MENU_TEXTID(3834, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
                player->SEND_POI(-8916.87, 622.87, 6, 6, 0, "Bank" /*"Banque de Hurlevent"*/);
                player->SEND_GOSSIP_MENU_TEXTID(764, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Deeprun tram
                player->SEND_POI(-8378.88, 554.23, 6, 6, 0, "Deeprun tram"/*"Le Tram des Profondeurs"*/);
                player->SEND_GOSSIP_MENU_TEXTID(3813, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
                player->SEND_POI(-8869.0, 675.4, 6, 6, 0, "The Gilded Rose");
                player->SEND_GOSSIP_MENU_TEXTID(3860, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Gryphon Master
                player->SEND_POI(-8837.0, 493.5, 6, 6, 0, "Gryphon Master"/*"Maître des gryphons de Hurlevent"*/);
                player->SEND_GOSSIP_MENU_TEXTID(879, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Guild Master
                player->SEND_POI(-8894.0, 611.2, 6, 6, 0, /* "Centre des visiteurs de Hurlevent"*/ "Guild Master");
                player->SEND_GOSSIP_MENU_TEXTID(882, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Mailbox
                player->SEND_POI(-8876.48, 649.18, 6, 6, 0, /*"Boîte aux lettres de Hurlevent"*/ "Mailbox");
                player->SEND_GOSSIP_MENU_TEXTID(3861, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Stable Master
                player->SEND_POI(-8433.0, 554.7, 6, 6, 0, "Jenova Stoneshield");
                player->SEND_GOSSIP_MENU_TEXTID(5984, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Weapon Trainer
                player->SEND_POI(-8797.0, 612.8, 6, 6, 0, "Woo Ping");
                player->SEND_GOSSIP_MENU_TEXTID(4516, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Officers Lounge
                player->SEND_POI(-8759.92, 399.69, 6, 6, 0, /*"Halls des Champions"*/ "Officer's Lounge");
                player->SEND_GOSSIP_MENU_TEXTID(7047, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Battlemasters
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(7499, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Class trainers
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->SEND_GOSSIP_MENU_TEXTID(898, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 13:                   //Profession trainers
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->SEND_GOSSIP_MENU_TEXTID(918, _Creature->GetGUID());
                break;
            }
        }

        void SendBattleMasterMenu_guard_stormwind(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
                player->SEND_POI(-8443.88, 335.99, 6, 6, 0, "Thelman Slatefist");
                player->SEND_GOSSIP_MENU_TEXTID(7500, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
                player->SEND_POI(-8443.88, 335.99, 6, 6, 0, "Lady Hoteshem");
                player->SEND_GOSSIP_MENU_TEXTID(7650, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
                player->SEND_POI(-8443.88, 335.99, 6, 6, 0, "Elfarran");
                player->SEND_GOSSIP_MENU_TEXTID(7501, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_stormwind(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Mage
                player->SEND_POI(-9012.0, 867.6, 6, 6, 0, "Wizard`s Sanctum");
                player->SEND_GOSSIP_MENU_TEXTID(899, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Rogue
                player->SEND_POI(-8753.0, 367.8, 6, 6, 0, "Hurlevent - Maison des voleurs");
                player->SEND_GOSSIP_MENU_TEXTID(900, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Warrior
                player->SEND_POI(-8690.11, 324.85, 6, 6, 0, "Centre de Commandement");
                player->SEND_GOSSIP_MENU_TEXTID(901, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Druid
                player->SEND_POI(-8751.0, 1124.5, 6, 6, 0, "Le parc");
                player->SEND_GOSSIP_MENU_TEXTID(902, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
                player->SEND_POI(-8512.0, 862.4, 6, 6, 0, "Cathédrale de la Lumière");
                player->SEND_GOSSIP_MENU_TEXTID(903, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Paladin
                player->SEND_POI(-8577.0, 881.7, 6, 6, 0, "Cathédrale de la Lumière");
                player->SEND_GOSSIP_MENU_TEXTID(904, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Hunter
                player->SEND_POI(-8413.0, 541.5, 6, 6, 0, "Hall du Chasseur");
                player->SEND_GOSSIP_MENU_TEXTID(905, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Warlock
                player->SEND_POI(-8948.91, 998.35, 6, 6, 0, "The Slaughtered Lamb");
                player->SEND_GOSSIP_MENU_TEXTID(906, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Shaman
                player->SEND_POI(-9033, 550, 6, 6, 0, "Vallée des Héros");
                //incorrect id
                player->SEND_GOSSIP_MENU_TEXTID(2593, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_stormwind(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(-8988.0, 759.60, 6, 6, 0, "Fournitures d'Alchimie");
                player->SEND_GOSSIP_MENU_TEXTID(919, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(-8424.0, 616.9, 6, 6, 0, "Therum Deepforge");
                player->SEND_GOSSIP_MENU_TEXTID(920, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(-8611.0, 364.6, 6, 6, 0, "Auberge de Pig et Whistle");
                player->SEND_GOSSIP_MENU_TEXTID(921, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(-8858.0, 803.7, 6, 6, 0, "Lucan Cordell");
                player->SEND_GOSSIP_MENU_TEXTID(941, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_POI(-8347.0, 644.1, 6, 6, 0, "Lilliam Sparkspindle");
                player->SEND_GOSSIP_MENU_TEXTID(922, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(-8513.0, 801.8, 6, 6, 0, "Shaina Fuller");
                player->SEND_GOSSIP_MENU_TEXTID(923, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(-8803.0, 767.5, 6, 6, 0, "Arnold Leland");
                player->SEND_GOSSIP_MENU_TEXTID(940, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
                player->SEND_POI(-8967.0, 779.5, 6, 6, 0, "Fournitures d'Alchimie");
                player->SEND_GOSSIP_MENU_TEXTID(924, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
                player->SEND_POI(-8726.0, 477.4, 6, 6, 0, "The Protective Hide");
                player->SEND_GOSSIP_MENU_TEXTID(925, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
                player->SEND_POI(-8434.0, 692.8, 6, 6, 0, "Gelman Stonehand");
                player->SEND_GOSSIP_MENU_TEXTID(927, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
                player->SEND_POI(-8716.0, 469.4, 6, 6, 0, "The Protective Hide");
                player->SEND_GOSSIP_MENU_TEXTID(928, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
                player->SEND_POI(-8938.0, 800.7, 6, 6, 0, "Textiles Duncan");
                player->SEND_GOSSIP_MENU_TEXTID(929, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_stormwindAI(creature);
    }
};



class guard_teldrassil : public CreatureScript
{
public:
    guard_teldrassil() : CreatureScript("guard_teldrassil")
    { }

    class guard_teldrassilAI : public guardAI
    {
    public:
        guard_teldrassilAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_FERRY        , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->SEND_GOSSIP_MENU_TEXTID(4316,me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_teldrassil(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_teldrassil(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_teldrassil(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_teldrassil(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
                player->SEND_GOSSIP_MENU_TEXTID(4317, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Rut`theran
                player->SEND_GOSSIP_MENU_TEXTID(4318, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
                player->SEND_GOSSIP_MENU_TEXTID(4319, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
                player->SEND_POI(9821.49, 960.13, 6, 6, 0, "Auberge de Dolanaar");
                player->SEND_GOSSIP_MENU_TEXTID(4320, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //stable master
                player->SEND_POI(9808.37, 931.1, 6, 6, 0, "Seriadne");
                player->SEND_GOSSIP_MENU_TEXTID(5982, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU_TEXTID(4264, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->SEND_GOSSIP_MENU_TEXTID(4273, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_teldrassil(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
                player->SEND_POI(9741.58, 963.7, 6, 6, 0, "Kal");
                player->SEND_GOSSIP_MENU_TEXTID(4323, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
                player->SEND_POI(9815.12, 926.28, 6, 6, 0, "Dazalar");
                player->SEND_GOSSIP_MENU_TEXTID(4324, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
                player->SEND_POI(9906.16, 986.63, 6, 6, 0, "Laurna Morninglight");
                player->SEND_GOSSIP_MENU_TEXTID(4325, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Rogue
                player->SEND_POI(9789, 942.86, 6, 6, 0, "Jannok Breezesong");
                player->SEND_GOSSIP_MENU_TEXTID(4326, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
                player->SEND_POI(9821.96, 950.61, 6, 6, 0, "Kyra Windblade");
                player->SEND_GOSSIP_MENU_TEXTID(4327, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_teldrassil(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(9767.59, 878.81, 6, 6, 0, "Cyndra Kindwhisper");
                player->SEND_GOSSIP_MENU_TEXTID(4329, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Cooking
                player->SEND_POI(9751.19, 906.13, 6, 6, 0, "Zarrin");
                player->SEND_GOSSIP_MENU_TEXTID(4330, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Enchanting
                player->SEND_POI(10677.59, 1946.56, 6, 6, 0, "Alanna Raveneye");
                player->SEND_GOSSIP_MENU_TEXTID(4331, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //First Aid
                player->SEND_POI(9903.12, 999, 6, 6, 0, "Byancie");
                player->SEND_GOSSIP_MENU_TEXTID(4332, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Fishing
                player->SEND_GOSSIP_MENU_TEXTID(4333, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Herbalism
                player->SEND_POI(9773.78, 875.88, 6, 6, 0, "Malorne Bladeleaf");
                player->SEND_GOSSIP_MENU_TEXTID(4334, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
                player->SEND_POI(10152.59, 1681.46, 6, 6, 0, "Nadyia Maneweaver");
                player->SEND_GOSSIP_MENU_TEXTID(4335, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
                player->SEND_POI(10135.59, 1673.18, 6, 6, 0, "Radnaal Maneweaver");
                player->SEND_GOSSIP_MENU_TEXTID(4336, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Tailoring
                player->SEND_GOSSIP_MENU_TEXTID(4337, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_teldrassilAI(creature);
    }
};


class guard_tirisfal : public CreatureScript
{
public:
    guard_tirisfal() : CreatureScript("guard_tirisfal")
    { }

    class guard_tirisfalAI : public guardAI
    {
    public:
        guard_tirisfalAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATHANDLER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN             , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->SEND_GOSSIP_MENU_TEXTID(4097,me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_tirisfal(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_tirisfal(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_tirisfal(player, me, action); break;
            }
            return true;

        }

        void SendDefaultMenu_guard_tirisfal(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
                player->SEND_GOSSIP_MENU_TEXTID(4074, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //bat handler
                player->SEND_GOSSIP_MENU_TEXTID(4075, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
                player->SEND_POI(2246.68, 241.89, 6, 6, 0, "Auberge Gallows` End");
                player->SEND_GOSSIP_MENU_TEXTID(4076, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable Master
                player->SEND_POI(2267.66, 319.32, 6, 6, 0, "Morganus");
                player->SEND_GOSSIP_MENU_TEXTID(5978, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU_TEXTID(4292, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->SEND_GOSSIP_MENU_TEXTID(4096, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_tirisfal(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Mage
                player->SEND_POI(2259.18, 240.93, 6, 6, 0, "Cain Firesong");
                player->SEND_GOSSIP_MENU_TEXTID(4077, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Priest
                player->SEND_POI(2259.18, 240.93, 6, 6, 0, "Dark Cleric Beryl");
                player->SEND_GOSSIP_MENU_TEXTID(4078, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Rogue
                player->SEND_POI(2259.18, 240.93, 6, 6, 0, "Marion Call");
                player->SEND_GOSSIP_MENU_TEXTID(4079, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Warlock
                player->SEND_POI(2259.18, 240.93, 6, 6, 0, "Rupert Boch");
                player->SEND_GOSSIP_MENU_TEXTID(4080, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
                player->SEND_POI(2256.48, 240.32, 6, 6, 0, "Austil de Mon");
                player->SEND_GOSSIP_MENU_TEXTID(4081, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_tirisfal(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(2263.25, 344.23, 6, 6, 0, "Carolai Anise");
                player->SEND_GOSSIP_MENU_TEXTID(4082, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_GOSSIP_MENU_TEXTID(4083, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_GOSSIP_MENU_TEXTID(4084, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(2250.35, 249.12, 6, 6, 0, "Vance Undergloom");
                player->SEND_GOSSIP_MENU_TEXTID(4085, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_GOSSIP_MENU_TEXTID(4086, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(2246.68, 241.89, 6, 6, 0, "Nurse Neela");
                player->SEND_GOSSIP_MENU_TEXTID(4087, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(2292.37, -10.72, 6, 6, 0, "Clyde Kellen");
                player->SEND_GOSSIP_MENU_TEXTID(4088, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
                player->SEND_POI(2268.21, 331.69, 6, 6, 0, "Faruza");
                player->SEND_GOSSIP_MENU_TEXTID(4089, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
                player->SEND_POI(2027, 78.72, 6, 6, 0, "Shelene Rhobart");
                player->SEND_GOSSIP_MENU_TEXTID(4090, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
                player->SEND_GOSSIP_MENU_TEXTID(4091, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
                player->SEND_POI(2027, 78.72, 6, 6, 0, "Rand Rhobart");
                player->SEND_GOSSIP_MENU_TEXTID(4092, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
                player->SEND_POI(2160.45, 659.93, 6, 6, 0, "Bowen Brisboise");
                player->SEND_GOSSIP_MENU_TEXTID(4093, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_tirisfalAI(creature);
    }
};



class guard_undercity : public CreatureScript
{
public:
    guard_undercity() : CreatureScript("guard_undercity")
    { }

    class guard_undercityAI : public guardAI
    {
    public:
        guard_undercityAI(Creature* creature) : guardAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATHANDLER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_ZEPPLINMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            player->SEND_GOSSIP_MENU_TEXTID(3543,me->GetGUID());
            return true;

        }

        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_undercity(player, me, action); break;
                case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_undercity(player, me, action); break;
                case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_undercity(player, me, action); break;
                case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_undercity(player, me, action); break;
            }
            return true;

        }


        void SendDefaultMenu_guard_undercity(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
                player->SEND_POI(1595.64, 232.45, 6, 6, 0, "Banque de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3514, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Bat handler
                player->SEND_POI(1565.9, 271.43, 6, 6, 0, "Maître des chauve-souris de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3515, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
                player->SEND_POI(1594.17, 205.57, 6, 6, 0, "Maître de guilde de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3516, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
                player->SEND_POI(1639.43, 220.99, 6, 6, 0, "Auberge de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3517, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
                player->SEND_POI(1632.68, 219.4, 6, 6, 0, "Boîte aux lettres de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3518, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //Auction House
                player->SEND_POI(1647.9, 258.49, 6, 6, 0, "Hotel des ventes de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3519, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Zeppelin
                player->SEND_POI(2059, 274.86, 6, 6, 0, "Zeppelin de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3520, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Weapon Master
                player->SEND_POI(1670.31, 324.66, 6, 6, 0, "Archibald");
                player->SEND_GOSSIP_MENU_TEXTID(4521, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Stable master
                player->SEND_POI(1634.18, 226.76, 6, 6, 0, "Anya Maulray");
                player->SEND_GOSSIP_MENU_TEXTID(5979, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Battlemaster
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(7527, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Class trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU_TEXTID(3542, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Profession trainer
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->SEND_GOSSIP_MENU_TEXTID(3541, _Creature->GetGUID());
                break;
            }
        }

        void SendBattleMasterMenu_guard_undercity(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
                player->SEND_POI(1329, 333.92, 6, 6, 0, "Grizzle Halfmane");
                player->SEND_GOSSIP_MENU_TEXTID(7525, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
                player->SEND_POI(1283.3, 287.16, 6, 6, 0, "Sir Malory Wheeler");
                player->SEND_GOSSIP_MENU_TEXTID(7646, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
                player->SEND_POI(1265, 351.18, 6, 6, 0, "Kurden Bloodclaw");
                player->SEND_GOSSIP_MENU_TEXTID(7526, _Creature->GetGUID());
                break;
            }
        }

        void SendClassTrainerMenu_guard_undercity(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Mage
                player->SEND_POI(1781, 53, 6, 6, 0, "Maîtres des mages de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3513, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Priest
                player->SEND_POI(1758.33, 401.5, 6, 6, 0, "Maîtres des prêtres de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3521, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Rogue
                player->SEND_POI(1418.56, 65, 6, 6, 0, "Maîtres des voleurs de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3524, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Warlock
                player->SEND_POI(1780.92, 53.16, 6, 6, 0, "Maîtres des démonistes de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3526, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
                player->SEND_POI(1775.59, 418.19, 6, 6, 0, "Maîtres des guerriers de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3527, _Creature->GetGUID());
                break;
            }
        }

        void SendProfTrainerMenu_guard_undercity(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
                player->SEND_POI(1419.82, 417.19, 6, 6, 0, "L'Apothicarium");
                player->SEND_GOSSIP_MENU_TEXTID(3528, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
                player->SEND_POI(1696, 285, 6, 6, 0, "Maître des forgerons de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3529, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
                player->SEND_POI(1596.34, 274.68, 6, 6, 0, "Maître des cuisiniers de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3530, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
                player->SEND_POI(1488.54, 280.19, 6, 6, 0, "Maître des enchanteurs de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3531, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
                player->SEND_POI(1408.58, 143.43, 6, 6, 0, "Maître des ingénieurs de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3532, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
                player->SEND_POI(1519.65, 167.19, 6, 6, 0, "Maître des premiers soins de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3533, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
                player->SEND_POI(1679.9, 89, 6, 6, 0, "Maître des pêcheurs de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3534, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
                player->SEND_POI(1558, 349.36, 6, 6, 0, "Maître des herboristes de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3535, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
                player->SEND_POI(1498.76, 196.43, 6, 6, 0, "Maître des travailleurs du cuir de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3536, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
                player->SEND_POI(1642.88, 335.58, 6, 6, 0, "Maître des mineurs de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3537, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
                player->SEND_POI(1498.6, 196.46, 6, 6, 0, "Maître des dépeceurs de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3538, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
                player->SEND_POI(1689.55, 193, 6, 6, 0, "Maître des couturiers de Fossoyeuse");
                player->SEND_GOSSIP_MENU_TEXTID(3539, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new guard_undercityAI(creature);
    }
};

void AddSC_guards()
{
    new guard_azuremyst();
    new guard_bluffwatcher();
    new guard_contested();
    new guard_darnassus();
    new guard_dunmorogh();
    new guard_durotar();
    new guard_elwynnforest();
    new guard_eversong();
    new guard_exodar();
    new guard_ironforge();
    new guard_mulgore();
    new guard_orgrimmar();
    new guard_shattrath();
    new guard_shattrath_aldor();
    new guard_shattrath_scryer();
    new guard_silvermoon();
    new guard_stormwind();
    new guard_teldrassil();
    new guard_tirisfal();
    new guard_undercity();
}

