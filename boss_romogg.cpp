/*XXXXXXXXXXXXXXXXXXXXXXXXX
  X   Blackrock Caverns  XX
  XXXXXXXXXXXXXXXXXXXXXXXXX*/



#include "ScriptPCH.h"
#include "blackrock_caverns.h"
#include "ScriptedCreature.h"


enum Spells

{
      SPELL_CALL_FOR_HELP         =82137,
	  SPELL_QUAKE                 =75272,
	  SPELL_THE_SKULLCRACKER      =75543,
	  SPELL_WOUNDING_STRIKE       =75571,
	  SPELL_WOUNDING_STRIKE_H     =69651,
	  SPELL_CHAINS_OF_WOE_VISUAL = 75441,
	  SPELL_CHAINS_OF_WOE_AURA =  82192,
	  SPELL_CHAINS_OF_WOE_TELE	= 75464,
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
#define EMOTE_CALL		"Rom'ogg Bonecrusher calls  for help."


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
		boss_romoggAI(Creature* creature) : BossAI(creature, DATA_BONECRUSHER), summons(creature)
		{
			me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_THE_SKULLCRACKER, true);
		}

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
			events.ScheduleEvent(EVENT_QUAKE, 15000);
	        events.ScheduleEvent(EVENT_WOUNDING_STRIKE, 5000);
		}

		void EnterCombat(Unit* /*who*/)
		{	        
			me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, 0);
			DoCastAOE(SPELL_CALL_FOR_HELP);
			me->MonsterTextEmote(EMOTE_CALL, 0, false);
		}

		void KilledUnit(Unit* who)
		{
			if(who->GetTypeId() == TYPEID_PLAYER)
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

			switch(summon->GetEntry())
			{
			case NPC_CHAINS_OF_WHO:
				summon->CastSpell(me, SPELL_CHAINS_OF_WOE_VISUAL);
				break;
			}
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
				me->MonsterYell(SAY_SPECIAL, LANG_UNIVERSAL, 0);
				me->SummonCreature(NPC_CHAINS_OF_WHO, me->GetPositionX() + irand(-6, 6), me->GetPositionY() + irand(-6,6), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
				DoCastAOE(SPELL_THE_SKULLCRACKER);
				SkulcrackOne = true;
			}

			if(HealthBelowPct(33) && !SkulcrackTwo)
			{
				me->MonsterTextEmote(EMOTE_SPECIAL, 0, true);
				me->MonsterYell(SAY_SPECIAL, LANG_UNIVERSAL, 0);
				me->SummonCreature(NPC_CHAINS_OF_WHO, me->GetPositionX() + irand(-6, 6), me->GetPositionY() + irand(-6,6), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
				DoCastAOE(SPELL_THE_SKULLCRACKER);
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
                            events.RescheduleEvent(EVENT_WOUNDING_STRIKE, 7000);                                                
						break;

				case EVENT_QUAKE:
						DoCastAOE(SPELL_QUAKE);
						if(IsHeroic())
						{
							DoCastAOE(SPELL_QUAKE);
							if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
								for(uint8 i = 0; i < 5; ++i)
									me->SummonCreature(NPC_ANGER, target->GetPositionX() + irand(-6, 6), target->GetPositionY() + irand(-6, 6), target->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
						}
						events.RescheduleEvent(EVENT_QUAKE, 15000);
						break;
				}
			}
			DoMeleeAttackIfReady();
		}
	};
};

class chains_of_woe : public CreatureScript
{
public:
	chains_of_woe() : CreatureScript("chains_of_woe") {}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new chains_of_woeAI(creature);
	}

	struct chains_of_woeAI : public ScriptedAI
	{
		chains_of_woeAI(Creature* creature) : ScriptedAI(creature) {instance = creature->GetInstanceScript();}

		uint32 chains;
		InstanceScript* instance;

		void Reset()
		{
			me->setFaction(16);
			me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
			chains = 1000;
		}

		void UpdateAI(uint32 diff)
		{
			if(!UpdateVictim())
				return;
			
				if(chains <= diff)
				{
					Map::PlayerList const &PlayerList = instance->instance->GetPlayers();

					for(Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
						if(Player* player = i->getSource())
						{
							if(Creature* chain = me->FindNearestCreature(NPC_CHAINS_OF_WHO, 100, true))
							{
								player->CastSpell(chain, SPELL_CHAINS_OF_WOE_TELE);
							}
							player->CastSpell(player, SPELL_CHAINS_OF_WOE_AURA);
						}
					chains = 2000;
				}else chains -= diff;
		}
	};
};
void AddSC_boss_romogg()
{
	new boss_romogg();
	new chains_of_woe();
}
