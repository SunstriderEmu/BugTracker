
#define QUEST_BALANCEOFLIGHT   7622

#define CREATURE_ENRIS         14494
#define CREATURE_ARCHER        14489
#define CREATURE_PEASANTT1     14485
#define CREATURE_PEASANTT2     14484
#define CREATURE_FOOTSOLDIER   14486

#define SPELL_ARROW            22411
#define SPELL_DEATHSDOOR       23127 //on arrows
#define SPELL_SEETHINGPLAGUE   23072 //at inc

#define WAVE_TIMER             50000
#define WAVE_COUNT             5

//broadcast_text table
#define PEASANT_ARRIVAL_SAY1   1  //The Scourge are upon us ! Run ! Run for your lives !
#define PEASANT_ARRIVAL_SAY2   2  //Please help us ! The Prince has gone mad !
#define PEASANT_ARRIVAL_SAY3   3  //Seek sanctuary in Hearthglen ! It is our only hope !
#define ERIS_END_SAY1          4  //We are saved ! The peasants have escaped the Scourge ! / Nous sommes sauvés ! Les paysans ont échappés au Fléau !
#define ERIS_END_SAY2          5  //I have failed once more...
#define PEASANT_END_SAY1       6  //Thank you, kind stranger. May your heroism never be forgotten.
#define PEASANT_END_SAY2       7  //The power of the light is truly great and merciful.
#define PEASANT_END_SAY3       8  //Stranger, find the fallen Prince Menethil and end his reign of terror.

enum EventsErisHavenfire
{
    EVENT_START,
    EVENT_NEWWAVE,
    EVENT_PEASANT,
    EVENT_FOOTSOLDIERS,
    EVENT_END,
    EVENT_SUCCESS,
    EVENT_FAILURE,
};

struct Locations
{
    float x, y, z, o;
};

static Locations ArchersPositions[] ={
    { 3347.6f, -3071.3f, 177.9f,  1.6f},
    { 3357.0f,   -3063.8f, 172.4f,  1.8f},
    { 3371.9f, -3069.4f, 175.3f,  2.1f},
    { 3334.6f, -3053.3f, 174.05f, 0.9f},
    { 3369.6f, -3024.6f, 171.77f, 3.3f}
};

static Locations FootSoldiersPositions[] ={
    { 3344.922852f, -3047.982178f, 164.136826f, 0},
    { 3349.338379f, -3058.127197f, 168.775848f, 0},
    { 3367.953857f, -3043.435547f, 164.905167f, 0}
};

static Locations PeasantsPositions[] ={
    { 3358.496826f, -3055.713379f, 165.544006f, 0},
    { 3360.218018f, -3055.480469f, 165.379150f, 0},
    { 3362.431641f, -3056.194580f, 165.278198f, 0},
    { 3364.003662f, -3055.811279f, 165.295990f, 0},
    { 3365.399902f, -3055.755859f, 165.378128f, 0},
    { 3367.164063f, -3055.320801f, 165.716324f, 0},
    { 3367.295654f, -3057.399170f, 165.714828f, 0},
    { 3364.462402f, -3058.087646f, 165.585693f, 0},
    { 3360.964111f, -3058.046631f, 165.993729f, 0},
    { 3361.451416f, -3053.601074f, 165.298401f, 0},
    { 3365.114990f, -3060.439453f, 166.099304f, 0},
    { 3361.784668f, -3060.594971f, 166.723602f, 0},
    { 3368.362061f, -3057.696533f, 166.116379f, 0},
    { 3330.148193f, -2986.815674f, 160.813156f, 4.5} //End event position
};

#define ARRIVAL_POSITION_COUNT 5

static Locations PeasantsArrivalPositions[] = {
    { 3329.598877f, -2975.505127f, 160.366943f, 0},
    { 3333.926025f, -2973.781982f, 160.776489f, 0},
    { 3324.293457f, -2976.472900f, 160.308640f, 0},
    { 3331.634766f, -2974.401367f, 160.427734f, 0},
    { 3326.627930f, -2975.803223f, 160.591400f, 0}
};


class npc_eris_havenfire : public CreatureScript
{
public:
    npc_eris_havenfire() : CreatureScript("npc_eris_havenfire")
    { }

    class  npc_eris_havenfireAI : public ScriptedAI
    {
        public:
    
        npc_eris_havenfireAI(Creature * c) : ScriptedAI(c), Summons(me)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            SetCombatMovementAllowed(false);
        }
    
        bool EventStarted;
        bool EventDone;
        uint32 Wave_Timer;
        uint16 DiedCount;
        uint16 CurrentWave;
        uint16 EndPhase;
        SummonList Summons; //for the bad guys only
        Player* MyLittlePriest;
        uint32 FootSoldiers_Timer;
        uint32 Peasants_Timer;
        uint32 End_Timer;
        bool SoldiersFirstSpawn;
        bool Peasants_Spawned;
        Creature* EndPeasant;
    
        void Reset()
        override {
            Summons.DespawnAll();
            EventDone = false;
            EventStarted = false;
            DiedCount = 0;
            CurrentWave = 1;
            EndPhase = 1;
            Wave_Timer = WAVE_TIMER;
            MyLittlePriest = nullptr;
            FootSoldiers_Timer = 12000;
            Peasants_Timer = 7000;
            End_Timer = 12000;
            SoldiersFirstSpawn = true;
            Peasants_Spawned = false;
            EndPeasant = nullptr;
        }
        
        void EnterCombat(Unit* who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if (EventStarted && MyLittlePriest) {
                if (!EventDone) {
                    if (CurrentWave <= WAVE_COUNT) {
                        if (CurrentWave >= 2 && FootSoldiers_Timer < diff) {
                            PlayEvent(EVENT_FOOTSOLDIERS);
                        }
                        else FootSoldiers_Timer -= diff;
    
                        if (!Peasants_Spawned && Peasants_Timer < diff) {
                            PlayEvent(EVENT_PEASANT);
                        }
                        else Peasants_Timer -= diff;
    
                        if (Wave_Timer < diff)
                        {
                            PlayEvent(EVENT_NEWWAVE);
                        }
                        else Wave_Timer -= diff;
                    }
    
                    if (DiedCount >= 15) {
                        PlayEvent(EVENT_FAILURE);
                    }
                }
                else {
                    if (End_Timer < diff)
                        PlayEvent(EVENT_END);
                    else End_Timer -= diff;
                }
            }
        }
    
        void PlayEvent(int event)
        {
            switch (event) {
            case EVENT_START:
                for (auto & ArchersPosition : ArchersPositions) {
                    Creature* Archer = me->SummonCreature(CREATURE_ARCHER, ArchersPosition.x, ArchersPosition.y, ArchersPosition.z, ArchersPosition.o, TEMPSUMMON_TIMED_DESPAWN, 300000);
                    if (Archer)
                        Summons.Summon(Archer);
                }
                break;
            case EVENT_NEWWAVE:
                CurrentWave++;
                if (CurrentWave > WAVE_COUNT)
                    EventDone = true;
                else {
                    SoldiersFirstSpawn = true;
                    FootSoldiers_Timer = 10000;
                    Peasants_Timer = 5000;
                    Peasants_Spawned = false;
                    Wave_Timer = WAVE_TIMER;
                }
                break;
            case EVENT_PEASANT:
                Creature* Peasant;
                for (int i = 0; i < 13; i++) {
                    uint32 summon = rand() % 8 ? CREATURE_PEASANTT2 : CREATURE_PEASANTT1;
                    Peasant = me->SummonCreature(summon, PeasantsPositions[i].x, PeasantsPositions[i].y, PeasantsPositions[i].z, 0, TEMPSUMMON_TIMED_DESPAWN, 67000);
                    if (Peasant) {
                        Peasant->SetOwnerGUID(me->GetGUID());
                        if (summon == CREATURE_PEASANTT1) 
                            Peasant->CastSpell(Peasant, SPELL_SEETHINGPLAGUE, true);
    
                        for (uint64 & Summon : Summons) {
                            if (Creature* BadGuy = ObjectAccessor::GetCreature((*me), Summon))
                                BadGuy->AddThreat(Peasant, 0);
                        }
                    }
                }
                if (Peasant) {
                    switch (CurrentWave) {
                    case 1:
                        Peasant->Say(PEASANT_ARRIVAL_SAY1);
                        break;
                    case 2:
                        Peasant->Say(PEASANT_ARRIVAL_SAY2);
                        break;
                    case 3:
                        Peasant->Say(PEASANT_ARRIVAL_SAY3);
                        break;
                    }
                }
                Peasants_Spawned = true;
                break;
            case EVENT_FOOTSOLDIERS:
                uint8 HowMuch;
                if (!SoldiersFirstSpawn) {
                    HowMuch = rand() % 3 + 1;
                }
                else {
                    HowMuch = 3;
                    SoldiersFirstSpawn = false;
                }
    
                for (int i = 0; i < HowMuch; i++) {
                    Creature* BadGuy = me->SummonCreature(CREATURE_FOOTSOLDIER, FootSoldiersPositions[i].x, FootSoldiersPositions[i].y, FootSoldiersPositions[i].z, 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    if (BadGuy) {
                        Summons.Summon(BadGuy);
                        BadGuy->AddThreat(MyLittlePriest, 0);
                        BadGuy->AI()->AttackStart(MyLittlePriest);
                    }
                }
                FootSoldiers_Timer = HowMuch * 5000;
                break;
            case EVENT_END:
                if (EndPeasant) {
                    switch (EndPhase) {
                    case 1:
                        PlayEvent(EVENT_SUCCESS);
                        break;
                    case 2:
                        EndPeasant->SetInFront(MyLittlePriest);
                        EndPeasant->StopMoving();
                        EndPeasant->Say(PEASANT_END_SAY1);
                        EndPeasant->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                        break;
                    case 3:
                        EndPeasant->SetInFront(MyLittlePriest);
                        EndPeasant->StopMoving();
                        EndPeasant->Say(PEASANT_END_SAY2);
                        EndPeasant->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                        break;
                    case 4:
                        EndPeasant->SetInFront(MyLittlePriest);
                        EndPeasant->StopMoving();
                        EndPeasant->Say(PEASANT_END_SAY3);
                        EndPeasant->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                        break;
                    case 5:
                        EndPeasant->DisappearAndDie();
                        Reset();
                        break;
                    }
    
                    EndPhase++;
                    End_Timer = 6000;
                }
                else {
                    EndPeasant = me->SummonCreature(CREATURE_PEASANTT2, PeasantsPositions[13].x, PeasantsPositions[13].y, PeasantsPositions[13].z, PeasantsPositions[13].o, TEMPSUMMON_DEAD_DESPAWN, 0);
                    if (EndPeasant)
                        EndPeasant->GetMotionMaster()->Clear();
                }
                break;
            case EVENT_SUCCESS:
                MyLittlePriest->AreaExploredOrEventHappens(QUEST_BALANCEOFLIGHT); //quest complete
                me->Say(ERIS_END_SAY1);
                Summons.DespawnAll();
                EventDone = true;
                break;
            case EVENT_FAILURE:
                MyLittlePriest->FailQuest(QUEST_BALANCEOFLIGHT);
                me->Say(ERIS_END_SAY2);
                Reset();
                me->DisappearAndDie();
                break;
            }
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (((npc_eris_havenfire::npc_eris_havenfireAI*) me->AI())->EventStarted == false) {

                ((npc_eris_havenfire::npc_eris_havenfireAI*) me->AI())->Reset();
                ((npc_eris_havenfire::npc_eris_havenfireAI*) me->AI())->EventStarted = true;
                ((npc_eris_havenfire::npc_eris_havenfireAI*) me->AI())->MyLittlePriest = pPlayer;
                ((npc_eris_havenfire::npc_eris_havenfireAI*) me->AI())->PlayEvent(EVENT_START);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_eris_havenfireAI(creature);
    }
};





class npc_escaping_peasant : public CreatureScript
{
public:
    npc_escaping_peasant() : CreatureScript("npc_escaping_peasant")
    { }

    class  npc_escaping_peasantAI : public ScriptedAI
    {
        public:
        npc_escaping_peasantAI(Creature * c) : ScriptedAI(c), updateTimer(0)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetWalk(true);
            uint8 pos = rand() % ARRIVAL_POSITION_COUNT;
            me->GetMotionMaster()->MovePoint(0, PeasantsArrivalPositions[pos].x, PeasantsArrivalPositions[pos].y, PeasantsArrivalPositions[pos].z);
            SetCombatMovementAllowed(false);
        }
        uint64 updateTimer;
    
        void JustDied(Unit* /* who */)
        override {
            if(Unit* Owner = me->GetOwner())
                if (Creature* Eris = Owner->ToCreature())
                    ((npc_eris_havenfire::npc_eris_havenfireAI*) Eris->AI())->DiedCount++;
        }
        
        void EnterCombat(Unit* who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if (updateTimer >= diff) {
               updateTimer -= diff;
               return;
            }
            updateTimer = 3000;
    
            if(Unit* Owner = me->GetOwner())
                if (Creature* Eris = Owner->ToCreature())
                    if (!((npc_eris_havenfire::npc_eris_havenfireAI*) Eris->AI())->EventStarted) //disappear at failure
                        me->DisappearAndDie();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_escaping_peasantAI(creature);
    }
};


class npc_scourge_archer : public CreatureScript
{
public:
    npc_scourge_archer() : CreatureScript("npc_scourge_archer")
    { }

    class npc_scourge_archerAI : public ScriptedAI
    {
        public:
    
        npc_scourge_archerAI(Creature * c) : ScriptedAI(c)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE);
            me->SetByteValue(UNIT_FIELD_BYTES_2, 0, SHEATH_STATE_RANGED);
            SetCombatMovementAllowed(false);
        }
        int Arrow_Timer;
        uint64 targetGUID;
    
        void Reset()
        override {
            Arrow_Timer = 2700;
            targetGUID = 0;
        }
    
        void EnterCombat(Unit* who) override {}
        
        void UpdateAI(const uint32 diff)
        override {
            if (Arrow_Timer < diff) {
                Creature* target = ObjectAccessor::GetCreature(*me, targetGUID);
                if (target && target->IsAlive() && me->GetDistance(target) < 60.0f) {
                    AttackStart(target);
                    me->AttackStop(); //visual debug purpose
                    Arrow_Timer = 2700;
                    DoCast(target, SPELL_ARROW, false);
                    if (rand() % 10 == 0) 
                        target->CastSpell(target, SPELL_DEATHSDOOR, true);
                }
                else {
                    Unit* uTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 60.0f, false);
                    if (uTarget && uTarget->GetTypeId() == TYPEID_UNIT && target->GetEntry() != CREATURE_ENRIS)
                        targetGUID = target->GetGUID();
                }
            }
            else Arrow_Timer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_scourge_archerAI(creature);
    }
};


void AddSC_the_balance_of_light_and_shadow()
{

    new npc_eris_havenfire();

    new npc_escaping_peasant();

    new npc_scourge_archer();
}