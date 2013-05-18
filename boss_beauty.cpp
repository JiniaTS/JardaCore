/*########################
# Jarda WoW (c)    	 #
#########################*/

#include "ScriptPCH.h"
#include "blackrock_caverns.h"
#include "ScriptedCreature.h"


enum Spells
{

	SPELL_BERSERKER_CHARGE_H               =76030,
	SPELL_BERSERKER_CHARGE                 =99827,
	SPELL_FLAMEBREAK_H                     =76032,
	SPELL_FLAMEBREAK                       =99830,
	SPELL_MAGMA_SPIT                       =76031,
	SPELL_TERRIFYNG_ROAR                   =42690,
	SPELL_TERRIFYNG_ROAR_H                 =76028,
	//Trash
	SPELL_LAVA_DROOL                       =76628,
	SPELL_LITTLE_BIG_FLAME_BREATH          =76665,  



};
enum event

{
    EVENT_BERSERKER_CHARGE               =1,
    EVENT_BERSERKER_CHARGE_H,
	EVENT_FLAMEBREAK,
	EVENT_FLAMEBREAK_H,
	EVENT_MAGMA_SPIT,
	EVENT_TERRIFYNG_ROAR,
	EVENT_TERRIFYNG_ROAR_H,
	//Trash
	EVENT_LAVA_DROOL,
	EVENT_LITTLE_BIG_FLAME_BREATH
};

/*########################
# Boss Beauty			 #
#########################*/

class boss_beauty : public CreatureScript
{
public:
	boss_beauty() : CreatureScript("boss_beauty") {}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_beautyAI(creature);
	}

	struct boss_beautyAI : public BossAI
	{
		boss_beautyAI(Creature* creature) : BossAI(creature, DATA_BEAUTY) {}

		EventMap events;


		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_BERSERKER_CHARGE, 14000);
			events.ScheduleEvent(EVENT_FLAMEBREAK, 20000);
			events.ScheduleEvent(EVENT_MAGMA_SPIT, 6000);
			events.ScheduleEvent(EVENT_TERRIFYNG_ROAR, 30000);
			DoZoneInCombat();
		}
		void UpdateAI(uint32 diff)
		{
			if(!UpdateVictim())
				return;

			events.Update(diff);

			while(uint32 eventID = events.ExecuteEvent())
			{
				switch(eventID)
				{
				case EVENT_BERSERKER_CHARGE:
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
						if(!IsHeroic())
							DoCast(target, SPELL_BERSERKER_CHARGE);
						else
							DoCast(target, SPELL_BERSERKER_CHARGE_H);
					events.RescheduleEvent(SPELL_BERSERKER_CHARGE, 12000);
					break;
				case EVENT_FLAMEBREAK:
						 if(!IsHeroic())
							DoCast(me->getVictim(), SPELL_FLAMEBREAK);
						 else
						    DoCast(me->getVictim(), SPELL_FLAMEBREAK_H);
					events.RescheduleEvent(SPELL_FLAMEBREAK, 12000, 0);
					break;
				case EVENT_MAGMA_SPIT:
							DoCast(me->getVictim(), SPELL_MAGMA_SPIT);
					events.RescheduleEvent(SPELL_MAGMA_SPIT, 12000);
					break;
				case EVENT_TERRIFYNG_ROAR:
					if(!IsHeroic())
					    DoCast(me->getVictim(), SPELL_TERRIFYNG_ROAR);
					else
						DoCastAOE(SPELL_TERRIFYNG_ROAR_H);
					events.RescheduleEvent(SPELL_TERRIFYNG_ROAR, 12000);
					break;
				}
			}
			DoMeleeAttackIfReady();
		}
	};
};

/*########################
# Psi	 #
#########################*/

class npc_buster : public CreatureScript
	{
	public:
		npc_buster() : CreatureScript("npc_buster") {}


		CreatureAI* GetAI(Creature* creature) const
		{
			return new npc_busterAI(creature);
		}
		struct npc_busterAI : BossAI
		{
			npc_busterAI(Creature* creature) : BossAI(creature, DATA_BEAUTY) {}

			EventMap events;

			void Reset()
			{
				_Reset();
			}

			void EnterCombat(Unit* /*who*/)
			{
				events.ScheduleEvent(EVENT_LAVA_DROOL, 10000);
				events.ScheduleEvent(EVENT_LITTLE_BIG_FLAME_BREATH, 12000);
				DoZoneInCombat();
			}
		void UpdateAI(uint32 diff)
		{
			if(!UpdateVictim())
				return;

			events.Update(diff);

			while(uint32 eventID = events.ExecuteEvent())
			{
				switch(eventID)
				{
				case EVENT_LAVA_DROOL:
							DoCast(me->getVictim(), SPELL_LAVA_DROOL);
					events.RescheduleEvent(SPELL_LAVA_DROOL, 12000);
					break;
				case EVENT_LITTLE_BIG_FLAME_BREATH:
							DoCast(me->getVictim(), SPELL_LITTLE_BIG_FLAME_BREATH);
					events.RescheduleEvent(SPELL_LITTLE_BIG_FLAME_BREATH, 12000);
					break;
				}
			}
			DoMeleeAttackIfReady();
		}
		};
};


class npc_runty : public CreatureScript
	{
	public:
		npc_runty() : CreatureScript("npc_runty") {}

		CreatureAI* GetAI(Creature* creature) const
		{
			return new npc_runtyAI(creature);
		}
		struct npc_runtyAI : BossAI
		{
			npc_runtyAI(Creature* creature) : BossAI(creature, DATA_BEAUTY) {}

			EventMap events;

			void Reset()
			{
				_Reset();
			}

			void EnterCombat(Unit* /*who*/)
			{
				events.ScheduleEvent(EVENT_LAVA_DROOL, 10000);
				events.ScheduleEvent(EVENT_LITTLE_BIG_FLAME_BREATH, 12000);
				DoZoneInCombat();
			}

		void UpdateAI(uint32 diff)
		{
			if(!UpdateVictim())
				return;

			events.Update(diff);

			while(uint32 eventID = events.ExecuteEvent())
			{
				switch(eventID)
				{
				case EVENT_LAVA_DROOL:
							DoCast(me->getVictim(), SPELL_LAVA_DROOL);
					events.RescheduleEvent(SPELL_LAVA_DROOL, 12000);
					break;
				case EVENT_LITTLE_BIG_FLAME_BREATH:
							DoCast(me->getVictim(), SPELL_LITTLE_BIG_FLAME_BREATH);
					events.RescheduleEvent(SPELL_LITTLE_BIG_FLAME_BREATH, 12000);
					break;
				}
			}
			DoMeleeAttackIfReady();
		}
		};
};

class npc_spot : public CreatureScript
	{
	public:
		npc_spot() : CreatureScript("npc_spot") {}

		CreatureAI* GetAI(Creature* creature) const
		{
			return new npc_spotAI(creature);
		}
		struct npc_spotAI : BossAI
		{
			npc_spotAI(Creature* creature) : BossAI(creature, DATA_BEAUTY) {}

			EventMap events;

			void Reset()
			{
				_Reset();
			}

			void EnterCombat(Unit* /*who*/)
			{
				events.ScheduleEvent(EVENT_LAVA_DROOL, 10000);
				events.ScheduleEvent(EVENT_LITTLE_BIG_FLAME_BREATH, 12000);
				DoZoneInCombat();
			}

			void UpdateAI(uint32 diff)
			{
			if(!UpdateVictim())
				return;

			events.Update(diff);

			while(uint32 eventID = events.ExecuteEvent())
			{
				switch(eventID)
				{
				case EVENT_LAVA_DROOL:
							DoCast(me->getVictim(), SPELL_LAVA_DROOL);
					events.RescheduleEvent(SPELL_LAVA_DROOL, 12000);
					break;
				case EVENT_LITTLE_BIG_FLAME_BREATH:
							DoCast(me->getVictim(), SPELL_LITTLE_BIG_FLAME_BREATH);
					events.RescheduleEvent(SPELL_LITTLE_BIG_FLAME_BREATH, 12000);
					break;
				}
			}
			DoMeleeAttackIfReady();
			}
		};
};

void AddSC_boss_beauty()
{
	new boss_beauty();
	new npc_spot();
	new npc_runty();
	new npc_buster();
}
