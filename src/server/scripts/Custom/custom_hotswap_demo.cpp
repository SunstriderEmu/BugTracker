#include "TaskScheduler.h"

//AI for Hand of the Deceiver
class custom_hostwap_demo : public CreatureScript
{
public:
    custom_hostwap_demo() : CreatureScript("custom_hostwap_demo") {}

    class custom_hostwap_demoAI : public CreatureAI
    {
        private:
		
        public:
            custom_hostwap_demoAI(Creature* creature) : CreatureAI(creature)
            {
				
            }

			TaskScheduler scheduler;
			
            void Reset()
            override {
                me->Yell("Script reloaded!", LANG_UNIVERSAL);
				
				scheduler.CancelAll();

				/*
				scheduler.Schedule(Seconds(10), [=](TaskContext context)
				{
					me->Yell("Hello, this is a demo!", LANG_UNIVERSAL);
					context.Repeat();
				});
				*/

				scheduler.Schedule(Seconds(6), [=](TaskContext context)
				{
					me->Yell("Nested scheduling begin...", LANG_UNIVERSAL);

					context.Schedule(Seconds(2), [=](TaskContext context)
					{
						me->Yell("Hi you!", LANG_UNIVERSAL);
						me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);

						context.Schedule(Seconds(2), [=](TaskContext context)
						{
							me->HandleEmoteCommand(EMOTE_ONESHOT_SHY);
						});
					});

					context.Repeat();
				});
            }

            void EnterCombat(Unit* victim)
            override {
				me->Yell("Enter Combat", LANG_UNIVERSAL);
            }

            void JustDied(Unit* /*killer*/)
            override {
               
            }

			void DamageTaken(Unit* /*attacker*/, uint32& damage)
				override {
				me->Yell("DAMAGE TAKEN", LANG_UNIVERSAL);
			}

			void UpdateAI(uint32 const diff) override
			{
				scheduler.Update(diff, [this]{});

				if (!UpdateVictim())
					return;

				DoMeleeAttackIfReady();
			}

    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new custom_hostwap_demoAI(creature);
    }
};

void AddSC_custom_hostwap_demo()
{
    new custom_hostwap_demo();
}
