
#include "def_black_temple.h"

//Speech'n'Sounds
enum Says
{
    SAY_TAUNT1              = -1564018,
    SAY_TAUNT2              = -1564019,
    SAY_TAUNT3              = -1564020,
    SAY_AGGRO               = -1564021,
    SAY_SPELL1              = -1564022,
    SAY_SPELL2              = -1564023,
    SAY_SPELL3              = -1564024,
    SAY_SLAY1               = -1564025,
    SAY_SLAY2               = -1564026,
    SAY_ENRAGE              = -1564027,
    SAY_DEATH               = -1564028
};

//Spells
enum Spells
{
    SPELL_BEAM_SINISTER             = 40859,
    SPELL_BEAM_SINISTER_TRIGGER     = 40863,
    SPELL_BEAM_VILE                 = 40860,
    SPELL_BEAM_VILE_TRIGGER         = 40865,
    SPELL_BEAM_WICKED               = 40861,
    SPELL_BEAM_WICKED_TRIGGER       = 40866,
    SPELL_BEAM_SINFUL               = 40827,
    SPELL_BEAM_SINFUL_TRIGGER       = 40862,
    //SPELL_ATTRACTION_DUMMY          = 40870, //unused
    SPELL_ATTRACTION                = 40871, //AoE damage + dummy aura on ally
    SPELL_ATTRACTION_VIS            = 41001, //only visual, periodically trigger 40870
    SPELL_SILENCING_SHRIEK          = 40823,
    SPELL_ENRAGE                    = 23537,
    SPELL_SABER_LASH                = 40810, //76k damage (43267 = same with 47500 damage )
    SPELL_SABER_LASH_TRIGGER        = 40816, //trigger proc 40810 & periodic 43690
    SPELL_SABER_LASH_IMM            = 43690, //immunity
    SPELL_TELEPORT_VISUAL           = 40869,
    SPELL_BERSERK                   = 45078,
    
    SPELL_PRISMATIC_SHIELD          = 40879, //cast random prismatic auras
 /*   SPELL_PRISMATIC_AURA_SHADOW     = 40880,
    SPELL_PRISMATIC_AURA_FIRE       = 40882,
    SPELL_PRISMATIC_AURA_NATURE     = 40883,
    SPELL_PRISMATIC_AURA_ARCANE     = 40891,
    SPELL_PRISMATIC_AURA_FROST      = 40896,
    SPELL_PRISMATIC_AURA_HOLY       = 40897, */
};

enum Timers 
{
    TIMER_BEAM_FIRST = 12000,
    TIMER_BEAM = 9000,
    TIMER_PRISMATIC_SHIELD = 15000,
    TIMER_FATAL_ATTRACTION_FIRST = 12000,
    TIMER_SABER_LASH = 10000,
    TIMER_ENRAGE = 600000
};

#define TIMER_RANDOM_YELL 70000 + rand()%41 * 1000
#define TIMER_FATAL_ATTRACTION 18000 + rand()%7000
#define TIMER_SILENCING_SHRIEK 20000 + rand()%5000

struct boss_shahrazAI : public ScriptedAI
{
    boss_shahrazAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
    }

    InstanceScript* pInstance;

    uint64 AttractionTargetGUID[3];
    uint32 BeamTimer;
    uint32 BeamCount;
    uint32 CurrentBeam;
    uint32 FatalAttractionTimer;
    uint32 FatalAttractionExplodeTimer;
    uint32 ShriekTimer;
    uint32 SaberTimer;
    uint32 RandomYellTimer;
    uint32 EnrageTimer;
    uint32 CheckPlayersUndermapTimer;
    uint32 TooFarAwayCheckTimer;
    bool checkFatalAttractionDistance;
    bool Enraged;

    void Reset()
    override {
        if(pInstance && me->IsAlive())
            pInstance->SetData(DATA_MOTHERSHAHRAZEVENT, NOT_STARTED);

        memset(AttractionTargetGUID, 0, sizeof(uint64) * 3);

        BeamTimer = TIMER_BEAM;
        CurrentBeam = rand()%4;                                    // 0 - Sinister, 1 - Vile, 2 - Wicked, 3 - Sinful
        BeamCount = 0;
        FatalAttractionTimer = TIMER_FATAL_ATTRACTION_FIRST;
        FatalAttractionExplodeTimer = -1;
        ShriekTimer = TIMER_SILENCING_SHRIEK;
        SaberTimer = TIMER_SABER_LASH;
        RandomYellTimer = TIMER_RANDOM_YELL;
        EnrageTimer = TIMER_ENRAGE;
        CheckPlayersUndermapTimer = -1;
        TooFarAwayCheckTimer = 2000;
        checkFatalAttractionDistance = false;

        Enraged = false;
    }

    void EnterCombat(Unit *who)
    override {
        if(pInstance)
            pInstance->SetData(DATA_MOTHERSHAHRAZEVENT, IN_PROGRESS);

        DoZoneInCombat();
        DoScriptText(SAY_AGGRO, me);
        DoCast(me,SPELL_PRISMATIC_SHIELD,true);
    }

    void KilledUnit(Unit *victim)
    override {
        DoScriptText(RAND(SAY_SLAY1,SAY_SLAY2), me);
    }

    void JustDied(Unit *victim)
    override {
        if(pInstance)
            pInstance->SetData(DATA_MOTHERSHAHRAZEVENT, DONE);

        DoScriptText(SAY_DEATH, me);

        //clear attraction visual
        for (uint64 i : AttractionTargetGUID) 
            if (Player* plr = ObjectAccessor::GetPlayer(*me, i)) 
                plr->RemoveAurasDueToSpell(SPELL_ATTRACTION_VIS);
    }

    bool TeleportPlayers()
    {
        uint8 random = rand()%4;
        float angle = 0;
        switch(random)
        {
        case 0: angle = -M_PI/4;   break;
        case 1: angle = -3*M_PI/4; break;
        case 2: angle = 3*M_PI/4;  break;
        case 3: angle = M_PI/4;    break;
        }
        Position pos = me->GetFirstWalkableCollisionPosition(40.0f, angle, true);
        std::list<Unit*> targetList;
        SelectUnitList(targetList, 3, SELECT_TARGET_RANDOM, 120.0f, true, SPELL_SABER_LASH_IMM, 0);
        if(targetList.size() == 2 || targetList.size() == 3)
        {
            uint8 i = 0;
            for(auto target : targetList)
            {
                AttractionTargetGUID[i] = target->GetGUID();
                target->CastSpell(target, SPELL_TELEPORT_VISUAL, true);
                DoCast(target,SPELL_ATTRACTION_VIS,true);
                DoTeleportPlayer(target, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), target->GetOrientation());
                i++;
            }
            return true;
        }
        return false;
    }

    void UglyUndermapCheck(const uint32& diff)
    {
        // Only check fatal attraction targets
        if (CheckPlayersUndermapTimer < diff) 
        {
            for (uint64 & i : AttractionTargetGUID) 
            {
                if (Player* plr = ObjectAccessor::GetPlayer(*me, i)) 
                {
                    float z = plr->GetPositionZ();
                    if (z < 189)      // Player seems to be undermap (ugly hack, isn't it ?)
                    {
                        DoTeleportPlayer(plr, 945.6173, 198.3479, 192.00, 4.674);
                        i = 0;
                        plr->RemoveAurasDueToSpell(SPELL_ATTRACTION_VIS);
                    }
                }
            }
            
            CheckPlayersUndermapTimer = -1;
        }else CheckPlayersUndermapTimer -= diff;
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
            return;
            
        if (TooFarAwayCheckTimer <= diff) {
            if (me->GetPositionZ() < 180.0f) {
                EnterEvadeMode();
                return;
            }
                
            TooFarAwayCheckTimer = 2000;
        }
        else
            TooFarAwayCheckTimer -= diff;
        
        UglyUndermapCheck(diff);
        
        // Cast beam and randomize it every 4 beams
        if(BeamTimer < diff)
        {
            Unit* target = SelectTarget(0,0.0f,80.0f,true,true,false,SPELL_ATTRACTION_VIS,0);
            if(!target)
                return;

            BeamTimer = 9000;
            uint32 beamId = 0;
            switch(CurrentBeam)
            {
                case 0: beamId = SPELL_BEAM_SINISTER; break;
                case 1: beamId = SPELL_BEAM_VILE; break;
                case 2: beamId = SPELL_BEAM_WICKED; break;
                case 3: beamId = SPELL_BEAM_SINFUL; break;
            }

            DoCast(target, beamId);
            BeamCount++;
            uint32 lastBeam = CurrentBeam;
            //change beam every 3
            if(BeamCount >= 3)
            {
                while(CurrentBeam == lastBeam) //pick a different one
                    CurrentBeam = rand()%4;
                BeamCount = 0;
            }

        }else BeamTimer -= diff;

        // Select 3 random targets, teleport to a random location then make them cast explosions until they get away from each other.
        if(FatalAttractionTimer < diff)
        {
            if(TeleportPlayers())
            {
                DoScriptText(RAND(SAY_SPELL2,SAY_SPELL3), me);
                FatalAttractionExplodeTimer = 2500;
                checkFatalAttractionDistance = false;
                CheckPlayersUndermapTimer = 2000;
            }
            FatalAttractionTimer = TIMER_FATAL_ATTRACTION;
        }else FatalAttractionTimer -= diff;
        
        //Check distance with 2 others players targeted by fatal attraction. Remove if distance with both > 25, re cast explosion else.
        if(FatalAttractionExplodeTimer < diff)
        {
            bool clear = true;
            Player* p[3];
            for(uint8 i = 0; i < 3; i++)
                p[i] = ObjectAccessor::GetPlayer(*me, AttractionTargetGUID[i]);

            for(uint8 i = 0; i < 3; i++)
            {
                if(p[i])
                {
                    //remove invalid targets (gm, dead, etc)
                    if(me->CanAttack(p[i],true) != CAN_ATTACK_RESULT_OK)
                    {
                        AttractionTargetGUID[i] = 0;
                        p[i]->RemoveAurasDueToSpell(SPELL_ATTRACTION_VIS);
                        continue;
                    }

                    if(checkFatalAttractionDistance) //Clear fatal attraction target if needed (only after first cast, to give some time to te player to be teleported)
                    {
                        Player* other1 = p[(i+1)%3];
                        Player* other2 = p[(i+2)%3];
                        if(   (!other1 || other1->GetDistance2d(p[i]) > 25)
                           && (!other2 || other2->GetDistance2d(p[i]) > 25) )
                        {
                             AttractionTargetGUID[i] = 0;
                             p[i]->RemoveAurasDueToSpell(SPELL_ATTRACTION_VIS);
                             continue;
                        }
                    }
                    p[i]->CastSpell((Unit*)nullptr,SPELL_ATTRACTION,true);
                    clear = false;
                }
            }

            checkFatalAttractionDistance = true;
            if(clear)
                FatalAttractionExplodeTimer = -1;
            else
                FatalAttractionExplodeTimer = 1000;

        } else FatalAttractionExplodeTimer -= diff;
        
        if(ShriekTimer < diff)
        {
            if(DoCast(me->GetVictim(), SPELL_SILENCING_SHRIEK))
                ShriekTimer = TIMER_SILENCING_SHRIEK;
        } else ShriekTimer -= diff;

        if(SaberTimer < diff)
        {
            DoCast(me->GetVictim(), SPELL_SABER_LASH);
            SaberTimer = TIMER_SABER_LASH;
        } else SaberTimer -= diff;

        //Enrage
        if(!me->HasAuraEffect(SPELL_BERSERK, 0))
        {
            if(EnrageTimer < diff)
            {
                DoCast(me, SPELL_BERSERK);
                DoScriptText(SAY_ENRAGE, me);
            } else EnrageTimer -= diff;
        }
        
        //Random taunts
        if(RandomYellTimer < diff)
        {
            DoScriptText(RAND(SAY_TAUNT1,SAY_TAUNT2,SAY_TAUNT3), me);
            RandomYellTimer = TIMER_RANDOM_YELL;
        }else RandomYellTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_shahraz(Creature *_Creature)
{
    return new boss_shahrazAI (_Creature);
}

void AddSC_boss_mother_shahraz()
{
    OLDScript *newscript;
    newscript = new OLDScript;
    newscript->Name="boss_mother_shahraz";
    newscript->GetAI = &GetAI_boss_shahraz;
    sScriptMgr->RegisterOLDScript(newscript);
}

