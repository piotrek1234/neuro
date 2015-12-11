#include "modpriority.h"

ModPriority::~ModPriority()
{

}

void ModPriority::modify(TokenCreature *tc)
{
    tc->setPriority(tc->getPriority()+priority_);
}

