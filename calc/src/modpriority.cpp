#include "modpriority.h"

ModPriority::~ModPriority()
{

}

Mod *ModPriority::clone() const
{
    return new ModPriority(*this);
}

void ModPriority::modify(TokenCreature *tc)
{
    tc->setPriority(tc->getPriority()+1);
}

