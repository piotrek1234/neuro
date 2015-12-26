#include "modlife.h"
#include <iostream>

ModLife::~ModLife()
{

}

Mod *ModLife::clone() const
{
    return new ModLife(*this);
}

void ModLife::modify(TokenCreature* tc)
{
    tc->setLife(tc->getLife()+1);
}


