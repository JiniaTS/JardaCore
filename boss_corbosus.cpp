+ SPELL_RAGE    = 80158,
+ SPELL_CLEAVE  = 15496,
+ SPELL_DISGUE  = 121308,

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
