 /* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* ScriptData
SDName: Boss_Nalorakk
SD%Complete: 100
SDComment:
SDCategory: Zul'Aman
EndScriptData */


#include "def_zulaman.h"
#include "GridNotifiers.h"
#include "World.h"

//Trash Waves
float NalorakkWay[8][3] =
{
    { 18.569f, 1414.512f, 11.42f},// waypoint 1
    {-17.264f, 1419.551f, 12.62f},
    {-52.642f, 1419.357f, 27.31f},// waypoint 2
    {-69.908f, 1419.721f, 27.31f},
    {-79.929f, 1395.958f, 27.31f},
    {-80.072f, 1374.555f, 40.87f},// waypoint 3
    {-80.072f, 1314.398f, 40.87f},
    {-80.072f, 1295.775f, 48.60f} // waypoint 4
};

#define YELL_NALORAKK_WAVE1     "Gardes ! Bougez-vous, c'est l'heure du massacre !"
#define SOUND_NALORAKK_WAVE1    12066
#define YELL_NALORAKK_WAVE2     "Gardes ! Allez ! C'est quoi qui vous fait le plus peur hein ? Eux... Ou moi ?"
#define SOUND_NALORAKK_WAVE2    12067
#define YELL_NALORAKK_WAVE3     "Au galop ! Et rapportez-moi des têtes."
#define SOUND_NALORAKK_WAVE3    12068
#define YELL_NALORAKK_WAVE4     "Je vais perdre ma patience ! Allez-y, et faites-leur regretter d'être nés !"
#define SOUND_NALORAKK_WAVE4    12069

//Unimplemented SoundIDs
/*
#define SOUND_NALORAKK_EVENT1   12078
#define SOUND_NALORAKK_EVENT2   12079
*/

//General defines
#define YELL_AGGRO              "Vous s'rez mort bien vite !"
#define SOUND_YELL_AGGRO        12070
#define YELL_KILL_ONE           "Mua-ha-ha ! Allons, qu'est-ce que t'as à dire, hein ?"
#define SOUND_YELL_KILL_ONE     12075
#define YELL_KILL_TWO           "Les Amanis, ils vont régner à nouveau !"
#define SOUND_YELL_KILL_TWO     12076
#define YELL_DEATH              "Je vous... attendrai de l'autre côté..."
#define SOUND_YELL_DEATH        12077
#define YELL_BERSERK            "C'était votre chance ! Maintenant, c'est trop tard !" //Never seen this being used, so just guessing from what I hear.
#define SOUND_YELL_BERSERK      12074

#define SPELL_BERSERK           45078

//Defines for Troll form
#define SPELL_BRUTALSWIPE       42384
#define SPELL_MANGLE            42389
#define SPELL_MANGLEEFFECT      44955
#define SPELL_SURGE             42402
#define SPELL_BEARFORM          42377

#define YELL_SURGE              "Ca va faire mal !"
#define SOUND_YELL_SURGE        12071

#define YELL_SHIFTEDTOTROLL     "Place ! Voilà le Nalorakk !"
#define SOUND_YELL_TOTROLL      12073

//Defines for Bear form
#define SPELL_LACERATINGSLASH   42395
#define SPELL_RENDFLESH         42397
#define SPELL_DEAFENINGROAR     42398

#define YELL_SHIFTEDTOBEAR      "Vous demandez la bête, je vais vous donner la bête !"
#define SOUND_YELL_TOBEAR       12072



class boss_nalorakk : public CreatureScript
{
public:
    boss_nalorakk() : CreatureScript("boss_nalorakk")
    { }

    class boss_nalorakkAI : public ScriptedAI
    {
        public:
        boss_nalorakkAI(Creature* c) : ScriptedAI(c)
        {
            MoveEvent = true;
            MovePhase = 0;
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript* pInstance;
    
        uint32 BrutalSwipe_Timer;
        uint32 Mangle_Timer;
        uint32 Surge_Timer;
    
        uint32 LaceratingSlash_Timer;
        uint32 RendFlesh_Timer;
        uint32 DeafeningRoar_Timer;
    
        uint32 ShapeShift_Timer;
        uint32 Berserk_Timer;
    
        bool inBearForm;
        bool MoveEvent;
        bool inMove;
        uint32 MovePhase;
        uint32 waitTimer;

        bool isBlizzLike;
    
        void Reset()
        override {
            isBlizzLike = true;
            if(MoveEvent)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                inMove = false;
                waitTimer = 0;
                me->SetSpeedRate(MOVE_RUN,2);
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            }else
            {
                (*me).GetMotionMaster()->MovePoint(0,NalorakkWay[7][0],NalorakkWay[7][1],NalorakkWay[7][2]);
            }
    
            if(pInstance && pInstance->GetData(DATA_NALORAKKEVENT) != DONE)
                pInstance->SetData(DATA_NALORAKKEVENT, NOT_STARTED);
    
            Surge_Timer = 15000 + rand()%5000;
            BrutalSwipe_Timer = 7000 + rand()%5000;
            Mangle_Timer = 10000 + rand()%5000;
            ShapeShift_Timer = 45000 + rand()%5000;
            Berserk_Timer = 600000;
    
            inBearForm = false;
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + 1, 5122);
            me->SetOrientation(1.5f);
            
            ResetThreatList();
        }
    
        void SendAttacker(Unit* target)
        {
            std::list<Creature*> templist;
            float x, y, z;
            me->GetPosition(x, y, z);
    
            {
                CellCoord pair(Trinity::ComputeCellCoord(x, y));
                Cell cell(pair);
                cell.data.Part.reserved = ALL_DISTRICT;
                cell.SetNoCreate();
    
                Trinity::AllFriendlyCreaturesInGrid check(me);
                Trinity::CreatureListSearcher<Trinity::AllFriendlyCreaturesInGrid> searcher(me, templist, check);
    
                TypeContainerVisitor<Trinity::CreatureListSearcher<Trinity::AllFriendlyCreaturesInGrid>, GridTypeMapContainer> cSearcher(searcher);
    
                cell.Visit(pair, cSearcher, *(me->GetMap()), *me, me->GetGridActivationRange());
            }
    
            if(!templist.size())
                return;
    
            for(auto & i : templist)
            {
                if(i && me->IsWithinDistInMap(i,25))
                {
                    i->SetNoCallAssistance(true);
                    i->AI()->AttackStart(target);
                }
            }
        }
    
        void AttackStart(Unit* who)
        override {
            if(!MoveEvent)
                ScriptedAI::AttackStart(who);
        }
    

        virtual void ReceiveEmote(Player* pPlayer, uint32 textEmote) override
        {
            switch (textEmote)
            {
            case TEXTEMOTE_TRAIN: // /train
                if(isBlizzLike)
                {
                    isBlizzLike = false;
                    me->Say("OMFG ITS NOT BLIZZLIKE!");
                    me->HandleEmoteCommand(EMOTE_ONESHOT_BATTLE_ROAR);
                }
                break;
            default:
                break;
            }
        }

        void MoveInLineOfSight(Unit* who)
        override {
            if(!MoveEvent)
            {
                ScriptedAI::MoveInLineOfSight(who);
            }
            else
            {
                if(me->IsHostileTo( who ))
                {
                    if(!inMove)
                    {
                        switch(MovePhase)
                        {
                            case 0:
                                if(me->IsWithinDistInMap(who, 50))
                                {
                                    me->Yell(YELL_NALORAKK_WAVE1, LANG_UNIVERSAL, nullptr);
                                    DoPlaySoundToSet(me, SOUND_NALORAKK_WAVE1);
    
                                    (*me).GetMotionMaster()->MovePoint(1,NalorakkWay[1][0],NalorakkWay[1][1],NalorakkWay[1][2]);
                                    MovePhase ++;
                                    inMove = true;
    
                                    SendAttacker(who);
                                }
                                break;
                            case 2:
                                if(me->IsWithinDistInMap(who, 40))
                                {
                                    me->Yell(YELL_NALORAKK_WAVE2, LANG_UNIVERSAL, nullptr);
                                    DoPlaySoundToSet(me, SOUND_NALORAKK_WAVE2);
    
                                    (*me).GetMotionMaster()->MovePoint(3,NalorakkWay[3][0],NalorakkWay[3][1],NalorakkWay[3][2]);
                                    MovePhase ++;
                                    inMove = true;
    
                                    SendAttacker(who);
                                }
                                break;
                            case 5:
                                if(me->IsWithinDistInMap(who, 40))
                                {
                                    me->Yell(YELL_NALORAKK_WAVE3, LANG_UNIVERSAL, nullptr);
                                    DoPlaySoundToSet(me, SOUND_NALORAKK_WAVE3);
    
                                    (*me).GetMotionMaster()->MovePoint(6,NalorakkWay[6][0],NalorakkWay[6][1],NalorakkWay[6][2]);
                                    MovePhase ++;
                                    inMove = true;
    
                                    SendAttacker(who);
                                }
                                break;
                            case 7:
                                if(me->IsWithinDistInMap(who, 50))
                                {
                                    SendAttacker(who);
    
                                    me->Yell(YELL_NALORAKK_WAVE4, LANG_UNIVERSAL, nullptr);
                                    DoPlaySoundToSet(me, SOUND_NALORAKK_WAVE4);
    
                                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    
                                    MoveEvent = false;
                                }
                                break;
                        }
                    }
                }
            }
        }
    
        void JustEngagedWith(Unit* who)
        override {
            if(pInstance)
                pInstance->SetData(DATA_NALORAKKEVENT, IN_PROGRESS);
    
            me->Yell(YELL_AGGRO, LANG_UNIVERSAL, nullptr);
            DoPlaySoundToSet(me, SOUND_YELL_AGGRO);
            DoZoneInCombat();
        }
    
        void JustDied(Unit* /*Killer*/)
        override {
            if(pInstance)
                pInstance->SetData(DATA_NALORAKKEVENT, DONE);
    
            me->Yell(YELL_DEATH,LANG_UNIVERSAL,nullptr);
            DoPlaySoundToSet(me, SOUND_YELL_DEATH);
        }
    
        void KilledUnit(Unit* victim)
        override {
            switch(rand()%2)
            {
            case 0:
                me->Yell(YELL_KILL_ONE, LANG_UNIVERSAL, nullptr);
                DoPlaySoundToSet(me, SOUND_YELL_KILL_ONE);
                break;
            case 1:
                me->Yell(YELL_KILL_TWO, LANG_UNIVERSAL, nullptr);
                DoPlaySoundToSet(me, SOUND_YELL_KILL_TWO);
                break;
            }
        }
    
        void MovementInform(uint32 type, uint32 id)
        override {
            if(MoveEvent)
            {
                if(type != POINT_MOTION_TYPE)
                    return;
    
                if(!inMove)
                    return;
    
                if(MovePhase != id)
                    return;
    
                switch(MovePhase)
                {
                    case 2:
                        me->SetOrientation(3.1415*2);
                        inMove = false;
                        return;
                    case 1:
                    case 3:
                    case 4:
                    case 6:
                        MovePhase ++;
                        waitTimer = 1;
                        inMove = true;
                        return;
                    case 5:
                        me->SetOrientation(3.1415*0.5);
                        inMove = false;
                        return;
                    case 7:
                        me->SetOrientation(3.1415*0.5);
                        inMove = false;
                        return;
                }
    
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(waitTimer)
            {
                if(inMove)
                {
                    if(waitTimer < diff)
                    {
                        (*me).GetMotionMaster()->MovementExpired();
                        (*me).GetMotionMaster()->MovePoint(MovePhase,NalorakkWay[MovePhase][0],NalorakkWay[MovePhase][1],NalorakkWay[MovePhase][2]);
                        waitTimer = 0;
                    } else { waitTimer -= diff; }
                }
            }
    
            if(!UpdateVictim())
                return;
                
            if (me->GetPositionY() >= 1380) { // Out of his room
                EnterEvadeMode();
                inMove = false;
                waitTimer = 0;
                MoveEvent = false;
            }
    
            if(Berserk_Timer < diff)
            {
                DoCast(me, SPELL_BERSERK, true);
                me->Yell(YELL_BERSERK, LANG_UNIVERSAL, nullptr);
                DoPlaySoundToSet(me, SOUND_YELL_BERSERK);
                Berserk_Timer = 600000;
            }else Berserk_Timer -= diff;
    
            if(ShapeShift_Timer < diff)
            {
                if(inBearForm)
                {
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + 1, 5122);
                    me->Yell(YELL_SHIFTEDTOTROLL, LANG_UNIVERSAL, nullptr);
                    DoPlaySoundToSet(me, SOUND_YELL_TOTROLL);
                    me->RemoveAurasDueToSpell(SPELL_BEARFORM);
                    Surge_Timer = 15000 + rand()%5000;
                    BrutalSwipe_Timer = 7000 + rand()%5000;
                    Mangle_Timer = 10000 + rand()%5000;
                    ShapeShift_Timer = 45000 + rand()%5000;
                    inBearForm = false;
                }
                else
                {
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + 1, 0);
                    me->Yell(YELL_SHIFTEDTOBEAR, LANG_UNIVERSAL, nullptr);
                    DoPlaySoundToSet(me, SOUND_YELL_TOBEAR);
                    DoCast(me, SPELL_BEARFORM, true);
                    LaceratingSlash_Timer = 2000; // dur 18s
                    RendFlesh_Timer = 3000;  // dur 5s
                    DeafeningRoar_Timer = 5000 + rand()%5000;  // dur 2s
                    ShapeShift_Timer = 20000 + rand()%5000; // dur 30s
                    inBearForm = true;
                }
            }else ShapeShift_Timer -= diff;
    
            if(!inBearForm)
            {
                if(BrutalSwipe_Timer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_BRUTALSWIPE);
                    BrutalSwipe_Timer = 7000 + rand()%5000;
                }else BrutalSwipe_Timer -= diff;
    
                if(Mangle_Timer < diff)
                {
                    if(me->GetVictim() && !me->GetVictim()->HasAuraEffect(SPELL_MANGLEEFFECT, 0))
                    {
                        //DoCast(me->GetVictim(), SPELL_MANGLE);
                        me->GetVictim()->CastSpell(me->GetVictim(), SPELL_MANGLE, TRIGGERED_FULL_MASK);
                        Mangle_Timer = 1000;
                    }
                    else Mangle_Timer = 10000 + rand()%5000;
                }else Mangle_Timer -= diff;
    
                if(Surge_Timer < diff)
                {
                    me->Yell(YELL_SURGE, LANG_UNIVERSAL, nullptr);
                    DoPlaySoundToSet(me, SOUND_YELL_SURGE);
                    if(SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_SURGE))
                    {
                        Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, spellInfo->GetMaxRange(), true, true);
                        if(target)
                            DoCast(target, SPELL_SURGE);
                    }
                    Surge_Timer = 15000 + rand()%5000;
                }else Surge_Timer -= diff;
            }
            else
            {
                if(LaceratingSlash_Timer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_LACERATINGSLASH);
                    LaceratingSlash_Timer = 18000 + rand()%5000;
                }else LaceratingSlash_Timer -= diff;
    
                if(RendFlesh_Timer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_RENDFLESH);
                    RendFlesh_Timer = 5000 + rand()%5000;
                }else RendFlesh_Timer -= diff;
    
                if(DeafeningRoar_Timer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_DEAFENINGROAR);
                    DeafeningRoar_Timer = 15000 + rand()%5000;
                }else DeafeningRoar_Timer -= diff;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_nalorakkAI(creature);
    }
};


void AddSC_boss_nalorakk()
{
    new boss_nalorakk();
}

