/*XXXXXXXXXXXXXXXXXXXXXXXXXXXX
  XX Blackrock Caverns      XX
  XXXXXXXXXXXXXXXXXXXXXXXXXXXX*/

#include "ScriptPCH.h"
#include "Blackrock_Caverns.h"
#include "ScriptedCreature.h"

enum spells
{
  SPELL_AURA_OF_ACCELERATION             =75817,
	SPELL_AURA_OF_ACCELERATION_H           =87376,
	SPELL_DARK_COMMAND                     =75823,
	SPELL_DARK_COMMAND_H                   =93462,
	SPELL_DRAIN_ESENCE                     =75645,
	SPELL_TWILIGHT_EVOLUTION               =75732,
	SPELL_EVOLUTION                        =75697,
	SPELL_EVOLUTION_H                      =87378,
	//Trash
	SPELL_SHADOW_STRIKE                    =82362,
};

enum events
{
	EVENT_AURA_OF_ACCELERATION             =1,
	EVENT__AURA_OF_ACCELERATION_H,
	EVENT_DARK_COMMAND,
	EVENT_DARK_COMAND,
	EVENT_DRAIN_ESENCE,
	EVENT_TWILIGHT_EVOLUTION,
	EVENT_EVOLUTION,
	EVENT_EVOLUTION_H,
	//Trash
	EVENT_FORCE_BLAST_H,
	EVENT_FORCE_BLAST,
	EVENT_GRAVITY_STRIKE,
	EVENT_SHADOW_STRIKE
};

enum Npcs
{
	NPC_TWILIGHT                          =50284,
	NPC_TRIGER                           =,
};

enum Actions
{
	DO_CAST; //misto ; ,
	DO_EVOLU; // misto ; ,
}

const uint32 PlayerDebuf[1] = {75610}
const uint32 NetherBuff[1] = {75697}
const uint32 NetherBuff_H[1] = {87378}

#define SAY_AGGRO  "HERETICS! You will suffer for this interruption!" 
#define SAY_EVOLVED  "Bask in his power! Rise as an agent of the master's rage!"
#define SAY_KILL "There is only one true path of enlightenment! DEATH!"
#define SAY_DEATH  "For the master I die a thousand times... A thousan..."


/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  XX Corla, Herald of Twilight    XX
  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/

clas_boss_Corla / public CreatureScript // class boss_corla : public CreatureScript
{
public:
	boss_Corla() CreatureScript("boss_Corla"){}

	CreatureAI* GetAI (Creature* creature) const
	{
		return new Boss_CorlaAI(Creature);
	}
	struct boss_CorlaAI : public BossAI
	{
		boss_corlaiAI(Creature* creature) :BossAI(creature, Boss_CORLA,) sumons(creature){} // boss_Corla sumons na summons
		EventMap event; // event prepsat na events

		void reset()
		{
			me->SetVision(true); // me->SetVisible(true);
			summons.DespawnAll();
		}

		void EventCombat(unit/*who*/) // void EnterCombat(Unit* /*who*/)
		{
			me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, 0);
			Event.ScheduleEvent(Event_AURA_OF_ACCELERATION, 0); //events.Sche....(EVENT_.......
			Event.ScheduleEvent(Event_DARK_COMMAND, 20000); //events.Sche....(EVENT_.......
			Event.ScheduleEvent(Event_DRAIN_ESENCE, 1); //events.Sche....(EVENT_.......
		}

		void KilledUint(uint* /*who*/) // void KilledUnit(Unit* /*who*/)
		{
			if(who->GetTypeID() == TAPEID_PLAYR); // TYPEID_PLAYER) bez ;
			me->MonsterYell(SAY_KILL, LANG_UNIVERSAL, 0);
		}

		void JustDied(uint /*who*/
		{
			me->MonsterYyll(SAY_DEATH, LANG_UNIVERSAL, 0); // MonsterYell
			summons.DespamwnALL(); //summons.DespawnAll();
		}


		void UpdateAI(auint32 diff) // (uint32 diff)
		{
			if(!UbdateVictim()) // !UpdateVictim
				return;

			event.Update(diff); //events.Update(diff)

			while(uint32 eventID = events* ExecuteEvent()) // events.ExecuteEvent()
			{
				switch(eventID)
				{


			case DRAIN_ESENCE; // case EVENT_DRAIN_ESENCE:
				if (!me->isInCombat())

					 if(Unit* target = me->FindNearestCreature(npcID, distance)) // a jeje... distance v yardech for example 100.0f
						 DoCast (target, SPELL_DRAIN_ESENCE);
				 return false; // wtf? break;



			case EVENT_DARK_COMMAND;
				if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
				{
					if(!Heroic()) //If(!IsHeroic())
					DoCast(target, SPELL_DARK_COMMAND);
				
					else
						DoCast(target, DARK_COMMAND_H);
				}
				events.RescheduleEvent(EVENT_DARK_COMMAND, 20000);

				break;

			case EVENT_AURA_OF_ACCELERATION;

				DoCast(SPELL_AURA_OF_ACCELERATION)

				break;
				}
			}
			DoMeleeAttackIfReady();
		}

void DoAction(int32 action)
			{
				switch(action)
				{
				case DO_EVOLU:
					if(!IsHeroic); // if(!IsHeroic()) don't use ; 

					DOCast(SPELL_EVOLUTION); //DoCast

					else 
					DOCast(SPELL_EVOLUTION_H); //DoCast

				me->MonsterYell(SAY_EVOLVED, LAGN_UNIVERAL);//(SAY_EVOLVED, LANG_UNIVERSAL,0 );
                DoAction(DO_CAST); // any definition?
				break;
				}
}



/*XXXXXXXXXXXXXXXXXXXXXXX
  XX  MOBBY            XX
  XXXXXXXXXXXXXXXXXXXXXXX*/




class npc_twilight : public CreatureScript
	{
	public:
		npc_twilight() : CreatureScript("npc_twilight") {}


		CreatureAI* GetAI(Creature* creature) const
		{
			return new npc_twilightAI(creature);
		}
		struct npc_twilightAI : BossAI
		{
			npc_twilightAI(Creature* creature) : BossAI(creature, BOSS_CORLA) {} // ), phase(PHASE_NULL) ... need definition

			EventMap events;
			Phases phase;

			void Reset()
			{
				_Reset();
			}

			void EnterCombat(Unit* /*who*/)
			{
				events.ScheduleEvent(EVENT_SHADOW_STRIKE, 0);
				DoZoneInCombat();
			}

			void DoAvtions(int32* action) // DoAction
			{

				switch(action)
					case DO_CAST;
				     DoCast(me->getVictime(), SPELLSHADOW_STRIKE);
			 events.RescheduleEvent(EVENT_SHADOW_STRIKE, 3500);
			 break;

		};
};

class npc_triger : public CreatureScript
{
	public; // :
	npc_triger() : CreatureScript("NPC_triger") {}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_trigerAI(creatute); //creature
	}
	struct npc_trigerAI : BossAI
	{
		npc_trigerAI(Creature* creature) : BossAI(creature, BOSS_corla) {} // ), phase(PHASE_NULL) ... need definition

		EventMap enent;
		Phases phases;

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit/*who*/) // (Unit* /*who*/)
		{

			DoZoneInCombat();
		}


		void UpdateTriger()  // i read it this weekend
        {
            for (int j=0; j<1; ++j) 
                if (Creature* triger = Unit::GetCreature(*me, TrigerGUID[j]))
                {
                    
                    Unit* current = Unit::GetUnit(*triger, BeamTarget[j]);
                    
                    Unit* target = me;
                    if (Map* map = me->GetMap())
                    {
                        Map::PlayerList const& players = map->GetPlayers();

                      
                        for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
                        {
                            Player* p = i->getSource();
                            if (p && p->isAlive()
                                && (!target || target->GetDistance2d(triger)) 
                                && !p->HasAura(PlayerDebuff[j], 0)
                                target = p;
                        }
                    }
                   
                    if (target->GetTypeId() == TYPEID_PLAYER)
                        target->AddAura(PlayerDebuff[j], target);
                    else
                        target->AddAura(NetherBuff[j], target);
                   
                    if (!current || target != current)
                    {
                        BeamTarget[j] = target->GetGUID();
                        
                        if (Creature* beamer = Unit::GetCreature(*triger, BeamerGUID[j]))
                        {
                            beamer->CastSpell(target, TrigerBeam[j], false);
                            beamer->DisappearAndDie();
                            BeamerGUID[j] = 0;
						}
					}
				}

		}
	}
	 DoMeleeAttackIfReady();
}

class spell_triger_netherbuff : public SpellScriptLoader // i read it this weekend
{
    public:
        spell_triger_netherbuff() : SpellScriptLoader("spell_triger_netherbuff") { }

        class spell_triger_netherbuff_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_triger_netherbuff_AuraScript);

            void HandlePeriodic(AuraEffect const* /*aurEff*/)
            {
                PreventDefaultAction();
                if (GetStackAmount() != 1)
                    GetTarget()->RemoveAurasDueToSpell(NetherBuffAlphaId[GetStackAmount() - 2]);
                GetTarget()->CastSpell(GetTarget(), NetherBuffAlphaId[GetStackAmount() - 1], TRIGGERED_FULL_MASK);
                if (GetStackAmount() == 100)
                    Remove(AURA_REMOVE_BY_DEFAULT);
            }

            void OnRemove(AuraEffect const*, AuraEffectHandleModes)
            {
                if (GetStackAmount() != 100)
                    GetTarget()->RemoveAurasDueToSpell(NetherbuffAlphaId[GetStackAmount() - 1]);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_triger_netherbuff_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
                OnEffectRemove += AuraEffectRemoveFn(spell_triger_netherbuff_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
		DoAction(DO_EVOLU);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_triger_phase_netherbuff_AuraScript();
		}



class spell_triger_playerdebuff : public SpellScriptLoader // i read it this weekend
{
    public:
        spell_triger_playerdebuff() : SpellScriptLoader("spell_triger_playerdebuff") { }

        class spell_triger_playerdebuff_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_triger_playerdebuff_AuraScript);

            void HandlePeriodic(AuraEffect const* /*aurEff*/)
            {
                PreventDefaultAction();
                if (GetStackAmount() != 1)
                    GetTarget()->RemoveAurasDueToSpell(PlayerDebuffAlphaId[GetStackAmount() - 2]);
                GetTarget()->CastSpell(GetTarget(), PlayerDebuffAlphaId[GetStackAmount() - 1], TRIGGERED_FULL_MASK);
                if (GetStackAmount() == 100)
                    Remove(AURA_REMOVE_BY_DEFAULT);
            }

            void OnRemove(AuraEffect const*, AuraEffectHandleModes)
            {
                if (GetStackAmount() != 100)
                    GetTarget()->RemoveAurasDueToSpell(PlayerDebuffAlphaId[GetStackAmount() - 1]);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_triger_playerdebuff_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
                OnEffectRemove += AuraEffectRemoveFn(spell_triger_playerDebuff_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_triger_phase_netherbuff_AuraScript();
		}


}
}
}
};
};

void AddSC_boss_corla()
{
	new boss_corla();
	new npc_twilight();
	new npc_trigr();
}
