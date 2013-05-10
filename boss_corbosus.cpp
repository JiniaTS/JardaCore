+ SPELL_RAGE    = 80158,
+ SPELL_CLEAVE  = 15496,
+ SPELL_DISGUE  = 121308,
+ SPELL_FLAY    = 79922,

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

+ new stonecore_warbringer();
+ new stonecore_flayer();
