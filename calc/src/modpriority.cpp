#include "modpriority.h"

ModPriority::ModPriority()
{

}

ModPriority::~ModPriority()
{

}

void ModPriority::visit(TokenCreature* tc)
{
    tc->setPriority(tc->getPriority()+1);
}

