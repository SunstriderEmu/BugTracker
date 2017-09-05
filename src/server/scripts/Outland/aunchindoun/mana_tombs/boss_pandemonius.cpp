
/* ScriptData
SDName: Boss_Pandemonius
SD%Complete: 75
SDComment: Not known how void blast is done (amount of rapid cast seems to be related to players in party). All mobs remaining in surrounding area should aggro when engaged.
SDCategory: Auchindoun, Mana Tombs
EndScriptData */



#define SAY_AGGRO_1                     -1557008
#define SAY_AGGRO_2                     -1557009
#define SAY_AGGRO_3                     -1557010

#define SAY_KILL_1                      -1557011
#define SAY_KILL_2                      -1557012

#define SAY_DEATH                       -1557013

#define EMOTE_DARK_SHELL                -1557014

#define SPELL_VOID_BLAST                32325
#define H_SPELL_VOID_BLAST              38760
#define SPELL_DARK_SHELL                32358
#define H_SPELL_DARK_SHELL              38759


class boss_pandemonius : public CreatureScript
{
public:
    boss_pandemonius() : CreatureScript("boss_pandemonius")
    { }

    class boss_pandemoniusAI : public ScriptedAI
    {
        public:
        boss_pandemoniusAI(Creature *c) : ScriptedAI(c)
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        bool HeroicMode;
        uint32 VoidBlast_Timer;
        uint32 DarkShell_Timer;
        uint32 VoidBlast_Counter;
    
        void Reset()
        override {
            VoidBlast_Timer = 30000;
            DarkShell_Timer = 20000;
            VoidBlast_Counter = 0;
        }
    
        void JustDied(Unit* Killer)
        override {
            DoScriptText(SAY_DEATH, me);
        }
    
        void KilledUnit(Unit* victim)
        override {
            switch(rand()%2)
            {
                case 0: DoScriptText(SAY_KILL_1, me); break;
                case 1: DoScriptText(SAY_KILL_2, me); break;
            }
        }
    
        void EnterCombat(Unit *who)
        override {
            switch(rand()%3)
            {
                case 0: DoScriptText(SAY_AGGRO_1, me); break;
                case 1: DoScriptText(SAY_AGGRO_2, me); break;
                case 2: DoScriptText(SAY_AGGRO_3, me); break;
            }
    
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if( VoidBlast_Timer < diff )
            {
                if( Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0) )
                {
                    DoCast(target,HeroicMode ? H_SPELL_VOID_BLAST : SPELL_VOID_BLAST);
                    VoidBlast_Timer = 500;
                    ++VoidBlast_Counter;
                }
    
                if( VoidBlast_Counter == 5 )
                {
                    VoidBlast_Timer = 25000+rand()%10000;
                    VoidBlast_Counter = 0;
                }
            }else VoidBlast_Timer -= diff;
    
            if( !VoidBlast_Counter )
            {
                if( DarkShell_Timer < diff )
                {
                    if( me->IsNonMeleeSpellCast(false) )
                        me->InterruptNonMeleeSpells(true);
    
                    DoScriptText(EMOTE_DARK_SHELL, me);
    
                    DoCast(me,HeroicMode ? H_SPELL_DARK_SHELL : SPELL_DARK_SHELL);
                    DarkShell_Timer = 20000;
                }else DarkShell_Timer -= diff;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_pandemoniusAI(creature);
    }
};


void AddSC_boss_pandemonius()
{
    new boss_pandemonius();
}

