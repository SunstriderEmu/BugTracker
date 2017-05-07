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
SDName: Areatrigger_Scripts
SD%Complete: 100
SDComment: Scripts for areatriggers
SDCategory: Areatrigger
EndScriptData */

/* ContentData
at_legion_teleporter    4560 Teleporter TO Invasion Point: Cataclysm
at_test                 script test only
at_coilfang_waterfall   4591
at_mechanar             4614
at_botanica             4612
at_orb_of_command
at_childweek_quest911   3549
at_quest_whispers_raven_god
at_quest_ravenholdt     3066
EndContentData */

#include "Pet.h"

class ATLegionTeleporter : AreaTriggerScript
{
public:
    ATLegionTeleporter() : AreaTriggerScript("at_legion_teleporter") {}
    
    enum
    {
        SPELL_TELE_A_TO = 37387,
        SPELL_TELE_H_TO = 37389
    };

    bool OnTrigger(Player *player, AreaTriggerEntry const *at) override
    {
        if (player->IsAlive() && !player->IsInCombat())
        {
            if (player->GetTeam() == ALLIANCE && player->GetQuestRewardStatus(10589))
            {
                player->CastSpell(player, SPELL_TELE_A_TO, false);
                return true;
            }

            if (player->GetTeam() == HORDE && player->GetQuestRewardStatus(10604))
            {
                player->CastSpell(player, SPELL_TELE_H_TO, false);
                return true;
            }

            return false;
        }
        return false;
    }

};

class ATTest : AreaTriggerScript
{
public:
    ATTest() : AreaTriggerScript("at_test") {}

    bool OnTrigger(Player *player, AreaTriggerEntry const *at) override
    {
        player->Say("Hi!", LANG_UNIVERSAL);
        return true;
    }
};

class ATCoilfangWaterfall : AreaTriggerScript
{
public:
    ATCoilfangWaterfall() : AreaTriggerScript("at_coilfang_waterfall") {}

    enum
    {
        GO_COILFANG_WATERFALL = 184212
    };

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        if (GameObject* pGo = pPlayer->FindNearestGameObject(GO_COILFANG_WATERFALL, 50.0f))
        {
            if (pGo->getLootState() == GO_READY)
                pGo->UseDoorOrButton();
        }

        return false;
    }
};

class ATScentLarkorwi : AreaTriggerScript
{
public:
    ATScentLarkorwi() : AreaTriggerScript("at_scent_larkorwi") {}

    enum eScentLarkorwi
    {
        QUEST_SCENT_OF_LARKORWI = 4291,
        NPC_LARKORWI_MATE = 9683
    };

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        if (!pPlayer->IsDead() && pPlayer->GetQuestStatus(QUEST_SCENT_OF_LARKORWI) == QUEST_STATUS_INCOMPLETE)
        {
            if (!pPlayer->FindNearestCreature(NPC_LARKORWI_MATE, 15, true))
                pPlayer->SummonCreature(NPC_LARKORWI_MATE, pPlayer->GetPositionX() + 5, pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 3.3, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000);
        }

        return false;
    }
};

class ATMechanar : AreaTriggerScript
{
public:
    ATMechanar() : AreaTriggerScript("at_mechanar") {}

    const int DATA_PATHALEON = 5;

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        if (InstanceScript* pInstance = ((InstanceScript*)pPlayer->GetInstanceScript())) {
            if (pInstance->GetData(DATA_PATHALEON) == DONE)
                pPlayer->TeleportTo(554, -25.639709, 0.213936, -1.812820, 3.076223);

            return true;
        }
        return false;
    }
};

/*######
## at_botanica
######*/

class ATBotanica : AreaTriggerScript
{
public:
    ATBotanica() : AreaTriggerScript("at_botanica") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        pPlayer->TeleportTo(553, 41.069, -29.975, -1.12, 5.49);

        return true;
    }
};

class ATOrbOfCommand : AreaTriggerScript
{
public:
    ATOrbOfCommand() : AreaTriggerScript("at_orb_of_command") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        if (pPlayer->IsDead() && pPlayer->GetQuestRewardStatus(7761))       // TODO: Check that player's corpse is in instance
            pPlayer->TeleportTo(469, -7673.03, -1106.08, 396.65, 0.7);

        return true;
    }
};

class ATChildWeekQuest
{
public:
    bool HandleTrigger(Player* player, uint32 questId, uint32 childId)
    {
        if (player->GetQuestStatus(questId) == QUEST_STATUS_INCOMPLETE) {
            if (Pet* pet = player->GetMiniPet()) {
                if (pet->GetEntry() == childId)
                    player->AreaExploredOrEventHappens(questId);
            }
        }
        return true;
    };
};

class ATChildWeekQuest911 : AreaTriggerScript, ATChildWeekQuest
{
public:
    ATChildWeekQuest911() : AreaTriggerScript("at_childweek_quest911") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        return HandleTrigger(pPlayer, 911, 14444);
    }
};

class ATChildWeekQuest1800 : AreaTriggerScript, ATChildWeekQuest
{
public:
    ATChildWeekQuest1800() : AreaTriggerScript("at_childweek_quest1800") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        return HandleTrigger(pPlayer, 1800, 14444);
    }
};

class ATChildWeekQuest910 : AreaTriggerScript, ATChildWeekQuest
{
public:
    ATChildWeekQuest910() : AreaTriggerScript("at_childweek_quest910") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        return HandleTrigger(pPlayer, 910, 14444);
    }
};

class ATChildWeekQuest1479 : AreaTriggerScript, ATChildWeekQuest
{
public:
    ATChildWeekQuest1479() : AreaTriggerScript("at_childweek_quest1479") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        return HandleTrigger(pPlayer, 1479, 14305);
    }
};

class ATChildWeekQuest1558 : AreaTriggerScript, ATChildWeekQuest
{
public:
    ATChildWeekQuest1558() : AreaTriggerScript("at_childweek_quest1558") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        return HandleTrigger(pPlayer, 1558, 14305);
    }
};

class ATChildWeekQuest1687 : AreaTriggerScript, ATChildWeekQuest
{
public:
    ATChildWeekQuest1687() : AreaTriggerScript("at_childweek_quest1687") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        return HandleTrigger(pPlayer, 1687, 14305);
    }
};

class ATChildWeekQuest10951 : AreaTriggerScript
{
public:
    ATChildWeekQuest10951() : AreaTriggerScript("at_childweek_quest10951") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        if (pPlayer->GetQuestStatus(10951) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(10952) == QUEST_STATUS_INCOMPLETE) {
            if (Pet* pet = pPlayer->GetMiniPet()) {
                if (pet->GetEntry() == 22817)
                    pPlayer->AreaExploredOrEventHappens(10951); // Horde
                else if (pet->GetEntry() == 22818)
                    pPlayer->AreaExploredOrEventHappens(10952); // Alliance
            }
        }

        return true;
    }
};

class ATShadeOfEranikus : AreaTriggerScript
{
public:
    ATShadeOfEranikus() : AreaTriggerScript("at_shade_of_eranikus") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        if (pPlayer->GetQuestRewardStatus(8555) && pPlayer->GetReputationRank(910) >= REP_NEUTRAL) {
            if (!pPlayer->FindNearestCreature(15362, 100, true))
                pPlayer->SummonCreature(15362, -672.965149, 6.674169, -90.835663, 1.539716, TEMPSUMMON_TIMED_DESPAWN, 3600000);
        }
        return true;
    }
};

class ATCrashingWickerman : AreaTriggerScript
{
public:
    ATCrashingWickerman() : AreaTriggerScript("at_crashing_wickerman") {}

    bool OnTrigger(Player *player, AreaTriggerEntry const *at) override
    {
        if (player->GetQuestStatus(1658) == QUEST_STATUS_INCOMPLETE)
            player->AreaExploredOrEventHappens(1658);

        return true;
    }
};

class ATQuestWhispersRavenGod : AreaTriggerScript
{
public:
    ATQuestWhispersRavenGod() : AreaTriggerScript("at_quest_whispers_raven_god") {}

    bool OnTrigger(Player *player, AreaTriggerEntry const *at) override
    {
        if (player->GetQuestStatus(10607) != QUEST_STATUS_INCOMPLETE)
            return true;

        if (!player->HasAuraEffect(37466))
            return true;

        uint32 credit = 0;
        switch (at->id) {
        case 4613:
            credit = 22798;
            break;
        case 4615:
            credit = 22799;
            break;
        case 4616:
            credit = 22800;
            break;
        case 4617:
            credit = 22801;
            break;
        default:
            TC_LOG_ERROR("scripts", "AreaTrigger_at_quest_whispers_raven_god: wrong areatrigger %u", at->id);
            credit = 0;
            break;
        }

        player->KilledMonsterCredit(credit, 0);

        return true;
    }
};

class ATQuestRavenHoldt : AreaTriggerScript
{
public:
    ATQuestRavenHoldt() : AreaTriggerScript("at_quest_ravenholdt") {}

    bool OnTrigger(Player *player, AreaTriggerEntry const *at) override
    {
        if (player->GetQuestStatus(6681) != QUEST_STATUS_INCOMPLETE)
            return true;

        player->KilledMonsterCredit(13936, 0);
        return true;
    }
};

class ATQuestSimmerDownNow : AreaTriggerScript
{
public:
    ATQuestSimmerDownNow() : AreaTriggerScript("at_quest_simmer_down_now") {}

    bool OnTrigger(Player *player, AreaTriggerEntry const *at) override
    {
        if (player->GetQuestStatus(25) != QUEST_STATUS_INCOMPLETE)
            return true;

        player->AreaExploredOrEventHappens(25);
        return true;
    }
};

void AddSC_areatrigger_scripts()
{
    new ATLegionTeleporter();
    new ATTest();
    new ATCoilfangWaterfall();
    new ATScentLarkorwi();
    new ATMechanar();
    new ATBotanica();
    new ATOrbOfCommand();
    new ATChildWeekQuest911();
    new ATChildWeekQuest1800();
    new ATChildWeekQuest910();
    new ATChildWeekQuest1479();
    new ATChildWeekQuest1558();
    new ATChildWeekQuest1687();
    new ATChildWeekQuest10951();
    new ATShadeOfEranikus();
    new ATCrashingWickerman();
    new ATQuestWhispersRavenGod();
    new ATQuestRavenHoldt();
    new ATQuestSimmerDownNow();
}

