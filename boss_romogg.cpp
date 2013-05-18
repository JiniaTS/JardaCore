/*XXXXXXXXXXXXXXXXXXXXXXXXX
  X   Blackrock Caverns  XX
  XXXXXXXXXXXXXXXXXXXXXXXXX*/



#include "ScriptPCH.h"
#include "blackrock_caverns.h"
#include "ScriptedCreature.h"


enum Spells

{
      SPELL_CALL_FOR_HELP         =82137,
    SPELL_CHAINS_OF_WOE         =75539,
	  SPELL_QUAKE                 =75272,
	  SPELL_THE_SKULLCRACKER      =75543,
	  SPELL_WOUNDING_STRIKE       =75571,
	  SPELL_WOUNDING_STRIKE_H     =69651,
};

enum Events
{
	  EVENT_CALL_FOR_HELP         =1,
	  EVENT_CHAINS_OF_WOE,
	  EVENT_QUAKE,
	  EVENT_THE_SKULLCRACKER,
	  EVENT_WOUNDING_STRIKE,
	  EVENT_WOUNDING_STRIKE_H
};

enum Npcs
{
	  NPC_CHAINS_OF_WHO           =40447,
};


/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  X  Rom'ogg Bonecrusher.cpp XX
  XXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/

class boss_romogg : public CreatureScript 
{
public:
	boss_romogg() : CreatureScript("boss_romogg"){}

	CreatureAI* GetAI (Creature* creature) const
	{
		return new boss_romoggAI(creature);
	}
	struct boss_romoggAI : public BossAI
	{
		boss_romoggAI(Creature* creature) : BossAI(creature, DATA_BONECRUSHER){}

		EventMap events;
		bool SkulcrackOne;
		bool SkulcrackTwo;

		void Reset()
		{
			_Reset();
			SkulcrackOne = false;
			SkulcrackTwo = false;
		}

		void EnterCombat(Unit* /*who*/)
		{	        
			events.ScheduleEvent(EVENT_QUAKE, 25000);
	        events.ScheduleEvent(EVENT_WOUNDING_STRIKE, 7000);
		}


		void UpdateAI(uint32 diff)
		{
			if(!UpdateVictim())
				return;

			events.Update(diff);

			if(HealthBelowPct(66) && !SkulcrackOne)
			{
				me->SummonCreature(NPC_CHAINS_OF_WHO, me->GetPositionX() + irand(-6, 6), me->GetPositionY() + irand(-6,6), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
				DoCast(me->getVictim(), SPELL_THE_SKULLCRACKER );
				SkulcrackOne = true;
			}

			if(HealthBelowPct(33) && !SkulcrackTwo)
			{
				me->SummonCreature(NPC_CHAINS_OF_WHO, me->GetPositionX() + irand(-6, 6), me->GetPositionY() + irand(-6,6), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
				DoCast(me->getVictim(), SPELL_THE_SKULLCRACKER );
				SkulcrackTwo = true;
			}

			while(uint32 eventID = events.ExecuteEvent())
			{
				switch(eventID)
				{
				case EVENT_WOUNDING_STRIKE:
						if(!IsHeroic())
							DoCast(me->getVictim(), SPELL_WOUNDING_STRIKE);
						else
						    DoCast(me->getVictim(), SPELL_WOUNDING_STRIKE_H);
                            events.RescheduleEvent(SPELL_WOUNDING_STRIKE, 7000);                                                
						break;

				case EVENT_QUAKE:
						DoCast (me->getVictim(), SPELL_QUAKE);
						events.RescheduleEvent(SPELL_QUAKE, 35000);
						if(!IsHeroic())
						DoCast(SPELL_CALL_FOR_HELP);
						break;
				}
			}
			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_boss_romogg()
{
	new boss_romogg();
}
