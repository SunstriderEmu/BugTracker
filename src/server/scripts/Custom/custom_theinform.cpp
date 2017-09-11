#include "boost/lexical_cast.hpp"


class custom_theinform : public CreatureScript
{
public:
    custom_theinform() : CreatureScript("custom_theinform")
    { }

    class theinformAI : public ScriptedAI
    {
        public:
        theinformAI(Creature *c) : ScriptedAI(c) 
        {}
    
        void DamageTaken(Unit* who, uint32& damage) 
        override {
            RandomizeDisplayID();
            damage = 0;
        }
    
        void RandomizeDisplayID(uint32 depth = 0)
        {
            if(depth > 10) //prevent infinite loop
                return;
    
            uint32 random = urand(4,25958);
            if(sCreatureDisplayInfoStore.LookupEntry(random))
                me->SetDisplayId(random);
            else
                RandomizeDisplayID(++depth);
        }
    
        void UpdateAI(uint32 const diff) override
        {
            UpdateVictim();
        }
    
        void ReceiveEmote(Player* player, uint32 emote) override
        {
            me->HandleEmoteCommand(EMOTE_ONESHOT_DANCE);
            if(player->IsGameMaster())
            {
                uint32 displayID = me->GetDisplayId();
                me->Whisper("DisplayID " + boost::lexical_cast<std::string>(displayID), LANG_UNIVERSAL, player);
            }
        }
    
        void EnterCombat(Unit* /* who */) override {}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new theinformAI(creature);
    }
};

 
void AddSC_theinform()
{
 
    new custom_theinform();
}
