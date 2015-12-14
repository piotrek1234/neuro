#include "modattack.h"

ModAttack::~ModAttack()
{

}

void ModAttack::modify(TokenCreature *tc)
{
    for(int i=0; i<6; ++i)
    {
        if(tc->getAttack(i) > 0)
            tc->addAttack(i, attackBoost_);
    }
}


