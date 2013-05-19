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
	  NPC_CHAINS_OF_WHO           = 40447,
	  NPC_ANGER					  = 50376,
};

#define SAY_AGGRO		"Boss Cho'gall not gonna be happy 'bout dis!"
#define SAY_KILL		"That what you get! Nothing!"
#define SAY_SPECIAL		"Stand still! Rom'ogg crack your skulls!"
#define SAY_DEATH		"Rom'ogg...sorry..."
#define EMOTE_SPECIAL	"Rom'ogg Bonecrusher prepares to unleash The Skullcracker on nearby enemies!"


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
		boss_romoggAI(Creature* creature) : BossAI(creature, DATA_BONECRUSHER), summons(creature){}

		EventMap events;
		bool SkulcrackOne;
		bool SkulcrackTwo;
		SummonList summons;

		void Reset()
		{
			_Reset();
			SkulcrackOne = false;
			SkulcrackTwo = false;
			summons.DespawnAll();
		}

		void EnterCombat(Unit* /*who*/)
		{	        
			events.ScheduleEvent(EVENT_QUAKE, 25000);
	        events.ScheduleEvent(EVENT_WOUNDING_STRIKE, 7000);
			me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, 0);
		}

		void KilledUnit(Unit* /*victim*/)
		{
			me->MonsterYell(SAY_KILL, LANG_UNIVERSAL, 0);
		}

		void JustDied(Unit* /*who*/)
		{
			me->MonsterYell(SAY_DEATH, LANG_UNIVERSAL, 0);
			summons.DespawnAll();
		}

		void JustSummoned(Creature* summon)
		{
			if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
				summon->AI()->AttackStart(target);
		}

		void SummonedCreatureDespawn(Creature* summon)
		{
			summons.Despawn(summon);
		}

		void UpdateAI(uint32 diff)
		{
			if(!UpdateVictim())
				return;

			events.Update(diff);

			if(HealthBelowPct(66) && !SkulcrackOne)
			{
				me->MonsterTextEmote(EMOTE_SPECIAL, 0, true);
				me->SummonCreature(NPC_CHAINS_OF_WHO, me->GetPositionX() + irand(-6, 6), me->GetPositionY() + irand(-6,6), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
				DoCast(me->getVictim(), SPELL_THE_SKULLCRACKER );
				SkulcrackOne = true;
			}

			if(HealthBelowPct(33) && !SkulcrackTwo)
			{
				me->MonsterTextEmote(EMOTE_SPECIAL, 0, true);
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
						DoCastAOE(SPELL_QUAKE);
						if(IsHeroic())
						{
							DoCastAOE(SPELL_QUAKE);
							if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
								for(uint8 i = 8; i < 5; ++i)
									me->SummonCreature(NPC_ANGER, target->GetPositionX() + irand(-6, 6), target->GetPositionY() + irand(-6, 6), target->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
						}
						events.RescheduleEvent(SPELL_QUAKE, 35000);
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
