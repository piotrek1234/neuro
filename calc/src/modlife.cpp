#include "modlife.h"
#include <iostream>

ModLife::ModLife()
{

}

ModLife::~ModLife()
{

}

void ModLife::modify(TokenCreature* tc)
{
    tc->setLife(tc->getLife()+1);
}


