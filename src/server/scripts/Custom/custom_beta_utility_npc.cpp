//TODO:
//give me a mount
//respec

#include "RecupMgr.h"
#include "GameEventMgr.h"

class beta_utility_npc : public CreatureScript
{
public:
    beta_utility_npc() : CreatureScript("beta_utility_npc") { }

    class beta_utility_npcAI : public CreatureAI
    {
    public:
        beta_utility_npcAI(Creature* creature) : CreatureAI(creature)
        {
          
        }

        void Reset()
            override {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        //note that client does not update this correctly if event is started/stopped after player has already talked to the creature, there is some cache involved
        bool GossipHello(Player* player) override
        {
            bool betaActive = sGameEventMgr->IsActiveEvent(GAME_EVENT_BETA);
            bool instant70active = sGameEventMgr->IsActiveEvent(GAME_EVENT_INSTANT_70_SERVER);

            //prevent usage of this npc when beta is not enabled
            if (player->GetSession()->GetSecurity() == SEC_PLAYER && !betaActive && !instant70active)
            {
                me->Whisper("Server must be in beta/instant70 mode", LANG_UNIVERSAL, player);
                return true;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Change my level", MENU_MAIN, MAIN_MENU_ACTION_LEVEL);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Give me some equipments", MENU_MAIN, MAIN_MENU_ACTION_EQUIPMENT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Give me some spells", MENU_MAIN, MAIN_MENU_ACTION_SPELLS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Professions", MENU_MAIN, MAIN_MENU_ACTION_PROFESSION);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn me some skills", MENU_MAIN, MAIN_MENU_ACTION_SKILLS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport me", MENU_MAIN, MAIN_MENU_ACTION_TELEPORT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Give me a mount", MENU_MAIN, MAIN_MENU_ACTION_MOUNT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reset my talents", MENU_MAIN, MAIN_MENU_ACTION_RESET_TALENTS);

            if (betaActive)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Give me some money", MENU_MAIN, MAIN_MENU_ACTION_MONEY);
            }

            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;
        }

        bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            uint32 const sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
            ClearGossipMenuFor(player);
            switch (sender)
            {
            case MENU_EQUIPMENT:
                SelectInEquipmentMenu(player, me, action);
                break;
            case MENU_EQUIPMENT_SET:
                SelectInEquipmentSetMenu(player, me, action);
                break;
            case MENU_SPELLS:
                SelectInSpellsMenu(player, me, action);
                break;
            case MENU_LEVEL:
                SelectInLevelMenu(player, me, action);
                break;
            case MENU_SKILLS:
                SelectInSkillsMenu(player, me, action);
                break;
            case MENU_PROFESSIONS:
                SelectInProfessionsMenu(player, me, action);
                break;
            case MENU_TELEPORT:
                SelectInTeleportMenu(player, me, action);
                break;
            case MENU_MAIN:
            default:
                SelectInMainMenu(player, me, action);
                break;
            }
            return true;
        }

        enum Menus
        {
            MENU_MAIN = GOSSIP_SENDER_MAIN,
            MENU_EQUIPMENT,
            MENU_EQUIPMENT_SET,
            MENU_SPELLS,
            MENU_LEVEL,
            MENU_SKILLS,
            MENU_PROFESSIONS,
            MENU_TELEPORT,
        };

        // ###### MAIN MENU ######

        enum MainMenuAction
        {
            MAIN_MENU_ACTION_LEVEL,
            MAIN_MENU_ACTION_EQUIPMENT,
            MAIN_MENU_ACTION_SPELLS,
            MAIN_MENU_ACTION_PROFESSION,
            MAIN_MENU_ACTION_SKILLS,
            MAIN_MENU_ACTION_TELEPORT,
            MAIN_MENU_ACTION_MONEY,
            MAIN_MENU_ACTION_MOUNT,
            MAIN_MENU_ACTION_RESET_TALENTS,
        };

        void SelectInMainMenu(Player* p, Creature* creature, uint32 action)
        {
            switch (action)
            {
            case MAIN_MENU_ACTION_LEVEL:         SendLevelMenu(p, creature);                           break;
            case MAIN_MENU_ACTION_EQUIPMENT:     SendEquipmentMenu(p, creature);                       break;
            case MAIN_MENU_ACTION_SPELLS:        SendSpellsMenu(p, creature);                          break;
            case MAIN_MENU_ACTION_PROFESSION:    SendProfessionsMenu(p, creature);                     break;
            case MAIN_MENU_ACTION_SKILLS:        SendSkillsMenu(p, creature);                          break;
            case MAIN_MENU_ACTION_TELEPORT:      SendTeleportMenu(p, creature);                        break;
            case MAIN_MENU_ACTION_MONEY:         p->ModifyMoney(2000 * GOLD); p->CLOSE_GOSSIP_MENU();  break;
            case MAIN_MENU_ACTION_MOUNT:         SendMountMenu(p, creature);                           break;
            case MAIN_MENU_ACTION_RESET_TALENTS: p->ResetTalents(true); p->CLOSE_GOSSIP_MENU();        break;
            }
        }

        // ###### ###### ######

        // ###### SPELLS MENU ######

        enum SpellsMenuAction
        {
            SPELL_MENU_ACTION_LEARN,
        };

        void SendSpellsMenu(Player* p, Creature* creature)
        {
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn me my class spells", MENU_SPELLS, SPELL_MENU_ACTION_LEARN);

            SEND_PREPARED_GOSSIP_MENU(p, creature);
        }

        void SelectInSpellsMenu(Player* p, Creature* creature, uint32 action)
        {
            switch (action)
            {
            case SPELL_MENU_ACTION_LEARN:
                p->LearnAllClassSpells();
                break;
            }
            p->CLOSE_GOSSIP_MENU();
        }


        // ###### ###### ######

        // ###### LEVEL MENU ######

        enum LevelMenuAction
        {
            LEVEL_MENU_ACTION_58,
            LEVEL_MENU_ACTION_70,
        };

        void SendLevelMenu(Player* p, Creature* creature)
        {
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Change my level to 58 (does disconnect you)", MENU_LEVEL, LEVEL_MENU_ACTION_58);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Change my level to 70", MENU_LEVEL, LEVEL_MENU_ACTION_70);

            SEND_PREPARED_GOSSIP_MENU(p, creature);
        }

        void SelectInLevelMenu(Player* p, Creature* creature, uint32 action)
        {
            switch (action)
            {
            case LEVEL_MENU_ACTION_58: if (p->GetLevel() == 58) return; else break;
            case LEVEL_MENU_ACTION_70: if (p->GetLevel() == 70) return; else break;
            }

            switch (action)
            {
            case LEVEL_MENU_ACTION_58:
                p->ResetTalents();
                p->resetSpells();
                p->SetLevel(58);
                break;
            case LEVEL_MENU_ACTION_70:
                p->SetLevel(70);
                break;
            }

            p->LearnAllClassSpells();
            //this is to auto unequip item
            if (action == LEVEL_MENU_ACTION_58)
                p->GetSession()->KickPlayer();

            p->CLOSE_GOSSIP_MENU();
        }

        // ###### ###### ######

        // ###### SKILLS MENU ######

        enum SkillsMenuAction
        {
            SKILLS_MENU_ACTION_PROFICIENCIES,
            SKILLS_MENU_ACTION_MOUNTING_SKILLS,
        };

        void SendSkillsMenu(Player* p, Creature* creature)
        {
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn me all my class proficiencies", MENU_SKILLS, SKILLS_MENU_ACTION_PROFICIENCIES);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn me how to mount", MENU_SKILLS, SKILLS_MENU_ACTION_MOUNTING_SKILLS);

            SEND_PREPARED_GOSSIP_MENU(p, creature);
        }

        void SelectInSkillsMenu(Player* p, Creature* creature, uint32 action)
        {
            switch (action)
            {
            case SKILLS_MENU_ACTION_PROFICIENCIES:
                p->LearnAllClassProficiencies();
                break;
            case SKILLS_MENU_ACTION_MOUNTING_SKILLS:
                p->AddSpell(34091, true); //mount 280 
                break;
            }

            p->CLOSE_GOSSIP_MENU();
        }

        // ###### ###### ######

        // ###### SKILLS MENU ######

        enum TeleportMenuAction
        {
            TELEPORT_MENU_ACTION_SHATTRATH,
            TELEPORT_MENU_ACTION_RACE_STARTING_ZONE,
            TELEPORT_MENU_ACTION_BETA_LANDING_ZONE,

            TELEPORT_MENU_ACTION_ORGRIMMAR,
            TELEPORT_MENU_ACTION_THUNDERBLUFF,
            TELEPORT_MENU_ACTION_UNDERCITY,
            TELEPORT_MENU_ACTION_SILVERMOON,
            TELEPORT_MENU_ACTION_IRONFORGE,
            TELEPORT_MENU_ACTION_STORMWIND,
            TELEPORT_MENU_ACTION_DARNASSUS,
            TELEPORT_MENU_ACTION_EXODAR,
        };

        void SendTeleportMenu(Player* p, Creature* creature)
        {
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Beta landing zone", MENU_TELEPORT, TELEPORT_MENU_ACTION_BETA_LANDING_ZONE);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Race starting zone", MENU_TELEPORT, TELEPORT_MENU_ACTION_RACE_STARTING_ZONE);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Shattrath", MENU_TELEPORT, TELEPORT_MENU_ACTION_SHATTRATH);

            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Orgrimmar", MENU_TELEPORT, TELEPORT_MENU_ACTION_ORGRIMMAR);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Thunderbluff", MENU_TELEPORT, TELEPORT_MENU_ACTION_THUNDERBLUFF);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Undercity", MENU_TELEPORT, TELEPORT_MENU_ACTION_UNDERCITY);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Silvermoon City", MENU_TELEPORT, TELEPORT_MENU_ACTION_SILVERMOON);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ironforge", MENU_TELEPORT, TELEPORT_MENU_ACTION_IRONFORGE);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stormwind", MENU_TELEPORT, TELEPORT_MENU_ACTION_STORMWIND);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Darnassus", MENU_TELEPORT, TELEPORT_MENU_ACTION_DARNASSUS);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Exodar", MENU_TELEPORT, TELEPORT_MENU_ACTION_EXODAR);

            SEND_PREPARED_GOSSIP_MENU(p, creature);
        }

        void SelectInTeleportMenu(Player* p, Creature* creature, uint32 action)
        {
            switch (action)
            {
            case TELEPORT_MENU_ACTION_RACE_STARTING_ZONE:
            {
                PlayerInfo const* info = sObjectMgr->GetPlayerInfo(p->GetRace(), p->GetClass());
                if (!info)
                {
                    creature->Whisper("Could not find race starting zone", LANG_UNIVERSAL, p);
                    break;
                }
                p->TeleportTo(info->mapId, info->positionX, info->positionY, info->positionZ, 0.0f);
                break;
            }
            case TELEPORT_MENU_ACTION_SHATTRATH:
                p->TeleportTo(530, -1838.16f, 5301.79f, -12.428f, 5.9517f);
                break;
            case TELEPORT_MENU_ACTION_BETA_LANDING_ZONE:
                p->TeleportToBetaZone();
                break;
            case TELEPORT_MENU_ACTION_ORGRIMMAR:
                p->TeleportTo(1, 1629.36f, -4373.39f, 31.2564f, 3.54839f);
                break;
            case TELEPORT_MENU_ACTION_THUNDERBLUFF:
                p->TeleportTo(1, -1277.37f, 124.804f, 131.287f, 5.22274f);
                break;
            case TELEPORT_MENU_ACTION_UNDERCITY:
                p->TeleportTo(0, 1584.07f, 241.987f, -52.1534f, 0.0f);
                break;
            case TELEPORT_MENU_ACTION_SILVERMOON:
                p->TeleportTo(530, 9487.69f, -7279.2f, 14.2866f, 6.16478f);
                break;
            case TELEPORT_MENU_ACTION_IRONFORGE:
                p->TeleportTo(0, -4918.88f, -940.406f, 501.564f, 5.42347f);
                break;
            case TELEPORT_MENU_ACTION_STORMWIND:
                p->TeleportTo(0, -8833.38f, 628.628f, 94.0066f, 1.06535f);
                break;
            case TELEPORT_MENU_ACTION_DARNASSUS:
                p->TeleportTo(1, 9949.56f, 2284.21f, 1341.4f, 1.59587f);
                break;
            case TELEPORT_MENU_ACTION_EXODAR:
                p->TeleportTo(530, -3965.7f, -11653.6f, -138.844f, 0.852154f);
                break;
            }

            p->CLOSE_GOSSIP_MENU();
        }

        // ###### ###### ######

        // ###### PROFESSIONS MENU ######

        enum ProfessionMenuActions
        {
            PROFESSION_MENU_ACTION_MAX_PROFESSIONS,
        };

        void SendProfessionsMenu(Player* p, Creature* creature)
        {
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Max my professions", MENU_PROFESSIONS, PROFESSION_MENU_ACTION_MAX_PROFESSIONS);

            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "First Aid", MENU_PROFESSIONS, RECUP_PROFESSION_FIRST_AID);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Cooking", MENU_PROFESSIONS, RECUP_PROFESSION_COOKING);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Fishing", MENU_PROFESSIONS, RECUP_PROFESSION_FISHING);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Enchantment", MENU_PROFESSIONS, RECUP_PROFESSION_ENCHANTMENT);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mining", MENU_PROFESSIONS, RECUP_PROFESSION_MINING);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Forge", MENU_PROFESSIONS, RECUP_PROFESSION_FORGE);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Engineering", MENU_PROFESSIONS, RECUP_PROFESSION_ENGINEERING);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Leatherworking", MENU_PROFESSIONS, RECUP_PROFESSION_LEATHERWORKING);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Skinning", MENU_PROFESSIONS, RECUP_PROFESSION_SKINNING);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Alchemy", MENU_PROFESSIONS, RECUP_PROFESSION_ALCHEMY);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tailoring", MENU_PROFESSIONS, RECUP_PROFESSION_TAILORING);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Jewelcrafting", MENU_PROFESSIONS, RECUP_PROFESSION_JEWELCRAFTING);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Herbalism", MENU_PROFESSIONS, RECUP_PROFESSION_HERBALISM);
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lockpicking", MENU_PROFESSIONS, RECUP_PROFESSION_LOCKPICKING);

            SEND_PREPARED_GOSSIP_MENU(p, creature);
        }

        void SelectInProfessionsMenu(Player* p, Creature* creature, uint32 action)
        {
            RecupMgr::RecupProfession(p, RecupProfessionType(action));
            switch (action)
            {
            case PROFESSION_MENU_ACTION_MAX_PROFESSIONS:
                p->UpdateSkillsToMaxSkillsForLevel();
                break;
            }

            p->CLOSE_GOSSIP_MENU();
        }

        // ###### ###### ######

        // ###### EQUIPMENT MENU ######

        enum EquipMenuAction
        {
            EQUIP_MENU_ACTION_SETS,
        };

        void SendEquipmentMenu(Player* p, Creature* creature)
        {
            p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Equipment sets", MENU_EQUIPMENT, EQUIP_MENU_ACTION_SETS);

            SEND_PREPARED_GOSSIP_MENU(p, creature);
        }

        void SelectInEquipmentMenu(Player* p, Creature* creature, uint32 action)
        {
            switch (action)
            {
            case EQUIP_MENU_ACTION_SETS:
                SendEquipmentSetMenu(p, creature);
                break;
            }
        }

        void SendEquipmentSetMenu(Player* p, Creature* creature)
        {
            switch (p->GetClass())
            {
            case CLASS_WARRIOR:
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tank", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_TANK);
            case CLASS_HUNTER:
            case CLASS_ROGUE:
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "DPS", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_DPS);
                break;
            case CLASS_PALADIN:
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "DPS", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_DPS);
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tank", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_TANK);
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Heal", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_HEAL);
                break;
            case CLASS_PRIEST:
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "DPS", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_DPS);
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Heal", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_HEAL);
                break;
            case CLASS_MAGE:
            case CLASS_WARLOCK:
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "DPS", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_DPS);
                break;
            case CLASS_SHAMAN:
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "DPS Magic", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_DPS_ALT);
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "DPS Melee", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_DPS);
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Heal", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_HEAL);
                break;
            case CLASS_DRUID:
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "DPS Magic", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_DPS_ALT);
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "DPS Melee", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_DPS);
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Heal", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_HEAL);
                p->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tank", MENU_EQUIPMENT_SET, RECUP_EQUIP_TYPE_TANK);
                break;
            }

            SEND_PREPARED_GOSSIP_MENU(p, creature);
        }

        void SelectInEquipmentSetMenu(Player* p, Creature* creature, uint32 action)
        {
            GiveBagsIfNeeded(p);
            p->LearnAllClassSpells();
            RecupMgr::Recup(p, RecupEquipmentType(action), RECUP_STUFF_LEVEL_0);
            p->CLOSE_GOSSIP_MENU();
        }

        // ###### ###### ######

        void SendMountMenu(Player* p, Creature* creature)
        {
            uint32 mountId = 0;
            switch (p->GetRace())
            {
                //TODO
            case RACE_HUMAN:
            case RACE_ORC:
            case RACE_DWARF:
            case RACE_NIGHTELF:
            case RACE_UNDEAD_PLAYER:
            case RACE_TAUREN:
            case RACE_GNOME:
            case RACE_TROLL:
            case RACE_BLOODELF:
            case RACE_DRAENEI:
            default:
                break;
            }

            if (!p->HasItemCount(mountId, 1))
                p->StoreNewItemInBestSlots(mountId, 1);
        }

        void GiveBagsIfNeeded(Player* p)
        {
            uint32 bagCount = 0;
            for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; i++)
                if (p->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
                    bagCount++;

            if (bagCount != 4)
                p->StoreNewItemInBestSlots(23162, 4 - bagCount);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
        override {
        return new beta_utility_npcAI(creature);
    }
};

void AddSC_beta_utility_npc()
{
    new beta_utility_npc();
}

