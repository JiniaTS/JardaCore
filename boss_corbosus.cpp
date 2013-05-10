/*########################
# Jarda WoW (c)  		 #
#########################*/

#include "ScriptPCH.h"
#include "stone_core.h"
#include "ScriptedCreature.h"

enum Spells
{
	SPELL_BURROW		= 125383,
	SPELL_WAVE			= 82415,
	SPELL_WAVE_H		= 92650,
	SPELL_CRYSTAL_H		= 92648,
	SPELL_CRYSTAL		= 86881,
	SPELL_EMERGE		= 66947,
	SPELL_CHARGE		= 81828,
	SPELL_ROCK_BORE		= 80028,
	//Trash
	SPELL_BLUR			= 81216,
	SPELL_FEAR			= 81442,
	SPELL_SHADOWBOLT	= 81439,
	SPELL_SHADOWFURY	= 81441,
	SPELL_VOLLEY		= 81440,
	SPELL_DOOM			= 86830,
   SPELL_RAGE    = 80158,
 SPELL_CLEAVE  = 15496,
 SPELL_DISGUE  = 121308,
 SPELL_FLAY    = 79922,
};

enum Events
{
	EVENT_CRYSTAL		= 1,
	EVENT_WAVE,
	EVENT_BURROW,
	EVENT_EMERGE,
	EVENT_UNDERGROUND,
	EVENT_SUMMONADDS,
	//Trash
	EVENT_FEAR,
	EVENT_SHADOWBOLT,
	EVENT_VOLLEY,
	EVENT_SHADOWFURY

};

enum Npcs
{
	NPC_ROCK	= 42845,
	NPC_FORCE	= 43552,
};

enum Phases
{
	PHASE_NULL,
	PHASE_GROUND,
	PHASE_UNDERGROUND,
	PHASE_ONE,
	PHASE_TWO,
	PHASE_THREE
};

enum Actions
{
	DO_MOVE,
	DO_JUMP,
};

/*########################
# Boss Corborus			 #
#########################*/

class boss_corbosus : public CreatureScript
{
public:
	boss_corbosus() : CreatureScript("boss_corbosus") {}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_corbosusAI(creature);
	}

	struct boss_corbosusAI : public BossAI
	{
		boss_corbosusAI(Creature* creature) : BossAI(creature, BOSS_CORBOSUS), summons(creature), phase(PHASE_NULL) {}

		EventMap events;
		SummonList summons;
		Phases phase;

		void Reset()
		{
			me->SetVisible(true);
			summons.DespawnAll();
			phase = PHASE_NULL;
			events.SetPhase(PHASE_NULL);
			me->SetSpeed(MOVE_RUN, 1.0f);
			instance->SetData(DATA_ROCK_DOOR, GO_STATE_ACTIVE);
			events.Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_CRYSTAL, 13600, 0, PHASE_GROUND);
			events.ScheduleEvent(EVENT_WAVE, 25000, 0, PHASE_GROUND);
			events.ScheduleEvent(EVENT_BURROW, 33000, 0, PHASE_GROUND);
			events.ScheduleEvent(EVENT_SUMMONADDS, 2000, 0, PHASE_UNDERGROUND);
			events.SetPhase(PHASE_GROUND);
			phase = PHASE_GROUND;
			DoZoneInCombat();
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

		void JustDied(Unit* /*Killer*/)
		{
			summons.DespawnAll();
			instance->SetData(DATA_ROCK_DOOR, GO_STATE_READY);
		}

		void SummonAdds()
		{
			if(!IsHeroic())
				if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
					for(uint8 i = 0; i < 2; ++i)
						me->SummonCreature(NPC_ROCK, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);

			if(IsHeroic())
				if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
					for(uint8 i = 0; i < 2; ++i)
						me->SummonCreature(NPC_ROCK, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
		}

		void DoAction(int32 action)
		{
			switch(action)
			{
			case DO_MOVE:
				me->SetSpeed(MOVE_RUN, 5.0f);
				me->GetMotionMaster()->MovePoint(0, 1156.29f, 885.55f, 284.96f);
				me->SetOrientation(3.2f);
				instance->SetData(DATA_ROCK_DOOR, GO_STATE_READY);
				break;
			}
		}


		void UpdateAI(uint32 diff)
		{
			if(!UpdateVictim())
				return;

			events.Update(diff);

			if(phase == PHASE_GROUND || phase == PHASE_UNDERGROUND)
			{

			while(uint32 eventID = events.ExecuteEvent())
			{
				switch(eventID)
				{
				case EVENT_CRYSTAL:
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
						if(!IsHeroic())
							DoCast(target, SPELL_CRYSTAL);
						else 
							DoCast(target, SPELL_CRYSTAL_H);
					events.RescheduleEvent(EVENT_CRYSTAL, 12000, 0, PHASE_GROUND);
					break;
				case EVENT_WAVE:
					if(!IsHeroic())
						DoCastAOE(SPELL_WAVE);
					else
						DoCastAOE(SPELL_WAVE_H);
					events.RescheduleEvent(EVENT_WAVE, 20000, 0, PHASE_GROUND);
					break;
				case EVENT_BURROW:
					DoCast(me, SPELL_BURROW);
					me->SetVisible(false);
					me->AttackStop();
					events.DelayEvents(32000);
					events.ScheduleEvent(EVENT_EMERGE, 30000);
					events.RescheduleEvent(EVENT_BURROW, 30000, 0, PHASE_GROUND);
					events.ScheduleEvent(EVENT_CHARGE, 6000, 0, PHASE_UNDERGROUND);
					phase = PHASE_UNDERGROUND;
					events.SetPhase(PHASE_UNDERGROUND);
					break;
				case EVENT_EMERGE:
					DoCast(me, SPELL_EMERGE);
					me->SetVisible(true);
					DoMeleeAttackIfReady();
					phase = PHASE_GROUND;
					events.SetPhase(PHASE_GROUND);
					events.CancelEvent(EVENT_EMERGE);
					events.CancelEvent(EVENT_CHARGE);
					break;
				case EVENT_UNDERGROUND:
					me->GetMotionMaster()->MoveRandom(50);
					me->SetSpeed(MOVE_RUN, 2.5f);
					DoCast(me,SPELL_CHARGE);
					events.RescheduleEvent(EVENT_CHARGE, 5000, 0, PHASE_UNDERGROUND);
					break;
				case EVENT_SUMMONADDS:
					SummonAdds();
					events.RescheduleEvent(EVENT_SUMMONADDS, 2000, 0, PHASE_UNDERGROUND);
				}
			}

			DoMeleeAttackIfReady();
			}
		}
		};
		};
	class npc_rock_borer : public CreatureScript
	{
	public:
			npc_rock_borer() : CreatureScript("npc_rock_borer") {}

			CreatureAI* GetAI(Creature* creature) const
			{
				return new npc_rock_borerAI(creature);
			}

			struct npc_rock_borerAI : ScriptedAI
			{
				npc_rock_borerAI(Creature* creature) : ScriptedAI(creature) {}

				uint32 rock_boreTimer;

				void Reset()
				{
					rock_boreTimer = 5000;
				}

				void UpdateAI(uint32 diff)
				{
					if(!UpdateVictim())
						return;

					if(rock_boreTimer <= diff)
					{
						DoCast(me->getVictim(), SPELL_ROCK_BORE);
						rock_boreTimer = 2000;
					}else rock_boreTimer -= diff;
				DoMeleeAttackIfReady();
				}
			};
	};

/*########################
# Trash Moobs			 #
#########################*/

	class npc_millhouse : public CreatureScript
	{
	public:
		npc_millhouse() : CreatureScript("npc_millhouse") {}

		CreatureAI* GetAI(Creature* creature) const
		{
			return new npc_millhouseAI(creature);
		}

		struct npc_millhouseAI : BossAI
		{
			npc_millhouseAI(Creature* creature) : BossAI(creature, BOSS_CORBOSUS), phase(PHASE_NULL) {}

			EventMap events;
			Phases phase;

			void Reset()
			{
				_Reset();
			}

			void EnterCombat(Unit* /*who*/)
			{
				events.ScheduleEvent(EVENT_SHADOWFURY, 10000);
				events.ScheduleEvent(EVENT_VOLLEY, 12000);
				events.ScheduleEvent(EVENT_SHADOWBOLT, 3000);
				events.ScheduleEvent(EVENT_FEAR, 15000);
				phase = PHASE_ONE;
				events.SetPhase(PHASE_ONE);
				DoZoneInCombat();
			}

			void MoveInLineOfSight(Unit* who)
			{
				if(phase == PHASE_THREE && me->IsWithinDistInMap(who, 20.0f))
				{
					if(Creature* boss = me->GetCreature(*me, instance->GetData64(DATA_CORBOSUS)))
						boss->AI()->DoAction(DO_MOVE);
					DoAction(DO_JUMP);
				}
			}


			void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
			{
				if(phase == PHASE_ONE)
				{
				if(HealthAbovePct(51))
				{
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
						me->SummonCreature(NPC_FORCE, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
					me->AttackStop();
					me->GetMotionMaster()->MovePoint(0, 982.38f, 891.59f, 305.03f);
					me->SetOrientation(1.9f);
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
					me->SetHealth(int32(me->GetMaxHealth()));
				}
				}
				if(phase == PHASE_TWO)
				{
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
						me->SummonCreature(NPC_FORCE, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
					me->AttackStop();
					me->GetMotionMaster()->MovePoint(0, 1052.17f, 868.07f, 294.52f);
					me->SetOrientation(2.9f);
					me->SetHealth(int32(me->GetMaxHealth()));
				}

				if(phase == PHASE_THREE)
				{
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
						me->SummonCreature(NPC_FORCE, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
					me->AttackStop();
					me->GetMotionMaster()->MovePoint(0, 1156.29f, 885.55f, 284.96f);
					me->SetOrientation(2.9f);
					me->SetHealth(int32(me->GetMaxHealth()));
				}
			}

			void DoAction(int32 action)
			{
				switch(action)
				{
				case DO_JUMP:
					me->GetMotionMaster()->MoveJump(1162.27f, 847.06f, 303.43f, 1.5f, 1.0f);
					me->DespawnOrUnsummon(10000);
					break;
				}
			}

			void UpdateAI(uint32 diff)
			{
				if(!UpdateVictim())
					return;

				events.Update(diff);

				while(uint32 eventId = events.ExecuteEvent())
				{
					switch(eventId)
					{
					case EVENT_FEAR:
						if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
							DoCast(target, SPELL_FEAR);
						events.RescheduleEvent(EVENT_FEAR, 15000);
						events.DelayEvents(3000);
						break;
					case EVENT_VOLLEY:
						DoCastAOE(SPELL_VOLLEY);
						events.RescheduleEvent(EVENT_VOLLEY, urand(15000, 18000));
						events.DelayEvents(3000);
						break;
					case EVENT_SHADOWBOLT:
						if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
							DoCast(target, SPELL_SHADOWBOLT);
						events.DelayEvents(3000);
						events.RescheduleEvent(EVENT_SHADOWBOLT, 3000);
						break;
					case EVENT_SHADOWFURY:
						if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
							DoCast(target, SPELL_SHADOWFURY);
						events.DelayEvents(3000);
						events.RescheduleEvent(EVENT_SHADOWFURY, 18000);
						break;
					}
				}

				if(phase == PHASE_THREE)
				{
					events.CancelEvent(EVENT_FEAR);
					events.CancelEvent(EVENT_SHADOWFURY);
					events.CancelEvent(EVENT_VOLLEY);
					events.CancelEvent(EVENT_SHADOWBOLT);
					DoCast(SPELL_DOOM);
				}
			}
			};
			};

class stonecore_warbringer : public CreatureScript
{
public:

stonecore_warbringer() : CreatureScript("stonecore_warbringer") {}

CreatureAI* GetAI(Creature* creature) const
{
return new stonecore_warbringerAI(creature);
}

struct stonecore_warbringerAI : public ScriptedAI
{
stonecore_warbringerAI(Creature* creature) : ScriptedAI(creature)

uint32 cleaveTimer;
uint32 RageTimer;

void Reset()
{
cleaveTimer = 5000;
rageTimer = 30000;
}

void EnterCombat(Unit* /*who*/)
{
DoCast(me, SPELL_DISGUE);
}

void UpdateAI(uint32 diff)
{
if(!UpdateVictim())
return;

if(cleaveTimer <= diff)
{
DoCast(SPELL_CLEAVE);
cleaveTimer = 5000;
}else cleaveTimer -= diff;

if(rageTimer <= diff)
DoCast(me, SPELL_RAGE);
rageTimer = 30000;
}else rageTimer -= diff;

DoMeleeAttackIfReady();
}
};
};

class stonecore_flayer : public CreatureScript
{
  public:
  
  stonecore_flayer() : CreatureScript("stonecore_flayer") {}
  
  CreatureAI* GetAI(Creature* creature) const
  {
    return new stonecore_flayerAI(creature);
  }
  
  struct stonecore_flayerAI : public ScriptedAI
  {
    stonecore_flayerAI(Creature* creature) : ScriptesAI(creature)
    {
      me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_USESTANDING)
    }
    
    uint32 flaytimer;
    
    void Reset()
    {
      flaytimer = 25000;
    }
    
    void UpdateAI(uint32 diff)
    {
      if(flaytimer <= diff)
      {
        DoCast(me->getVictim(), SPELL_FLAY);
        flaytimer = 25000;
      }else flaytimer -= diff;
      
      DoMeleeAttackIfReady();
    }
};
};

  void AddSC_boss_corbosus()
	{
		new boss_corbosus();
		new npc_rock_borer();
    new npc_millhouse();
    new stonecore_warbringer();
    new stonecore_flayer();
	}
