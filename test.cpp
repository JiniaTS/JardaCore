/* lich test */


#include "ScriptPCH.h"
#include "stone_core.h"
#include "ScriptedCreature.h"


enum spell
{
  SPELL_FIREBALL              =21656,
  SPELL_FROSTFIREBOLT         =22555,
	SPELL_FLAMESTRIKE           =25645,
	SPELL_FEAR                  =15845,

};


enum event
{
	EVENT_FIREBALL              =1,
	EVENT_FROSTFIREBOLT,
	EVENT_FLAMESTRIKE,
	EVENT_FEAR,
	EVENT_STOP

};
enum Actions
{
	DO_MOVE,
};


/* Boss professor */


class boss_professor : public CreatureScript
{
public:
	boss_professor() : CreatureScript("boss_professor") {}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_professorAI(creature);
	}

	struct boss_professorAI : public BossAI
	{
		boss_professorAI(Creature* creature) : BossAI(creature, BOSS_BEAUTY,) {}

		EventMap events;


		void Reset()
		{
			me->SetVisible(true);
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_FIREBALL, urand(10000, 20000);
			events.ScheduleEvent(EVENT_FROSTFIREBOLT, urand(4000, 8000);
			events.ScheduleEvent(EVENT_FLAMESTRIKE, urand(12000, 15000);
			events.ScheduleEvent(EVENT_EVENT_STOP, (600000, 0);
		// delete	events.ScheduleEvent(EVENT_EVENT_FEAR, (610000, 0);
			
			DoZoneInCombat();

		}
};
};
	

void UpdateAI(uint32 diff)
		{
			if(!UpdateVictim())
				return;

			events.Update(diff);


			while(uint32 eventID = events.ExecuteEvent())
			{
				switch(eventID)
				{
				case EVENT_FIREBALL:
					
							DoCast(me->getVictim(), SPELL_FIREBALL);
					events.RescheduleEvent(SPELL_FIREBALL, urand(10000, 20000);

					break;


				case EVENT_FROSTFIREBOLT:
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0)) 


						DoCast(me->getVictim(), SPELL_FROSTFIREBOLT);
					events.RescheduleEvent(SPELL_FIREBALL, urand(4000, 8000);

					break;
				
				case Event_FLAMESTRIKE:
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0)) 


						DoCast(me->getVictim(), SPELL_FLAMESTRIKE);
					events.RescheduleEvent(SPELL_FLAMESTRIKE, urand(12000, 15000);

					break;

			  	    
				case EVENT_STOP 	
					me->AttackStop()
					me->SetReactState(REACT_PASSIVE);
          //events.ScheduleEvent(EVENT_FEAR, 5000);
          //DoAction(DO_MOVE);

					break;
          //case EVENT_FEAR:
          //if(Unit* target = SelectTarget(SELEC_TARGET_RANDOM, 0))
          //DoCast(target, SPELL_FEAR);
          //events.RescheduleEvent(EVENT_FEAR, 5000);
          //break;
				}
			};
};

				




void DoAction(int32 action)
			{
				switch(action)
				{
				case DO_MOVE:
					me->GetMotionMaster()->Movepoint(1241.01f, 457.14f, 248.45f, 1.5f, 1.0f);
                    me->GetMotionMaster()->MoveRotate(12000, ROTATE_DIRECTION_RIGTH);
					break;

					
					
				case EVENT_FEAR: //Delete
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0)) 


						DoCast(me->getVictim(), SPELL_FEAR);
					events.RescheduleEvent(SPELL_FEAR, (610000, 0);

					break;
				

		    }
			};
