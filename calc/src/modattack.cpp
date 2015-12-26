#include "modattack.h"

ModAttack::~ModAttack()
{

}

Mod *ModAttack::clone() const
{
    return new ModAttack(*this);
}

void ModAttack::modify(TokenCreature *tc)
{
    for(int i=0; i<6; ++i)
    {
        if(tc->getAttack(i) > 0)
            tc->addAttack(i, attackBoost_);
    }
}


