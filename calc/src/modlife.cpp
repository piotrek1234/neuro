#include "modlife.h"

ModLife::ModLife()
{

}

ModLife::~ModLife()
{

}

void ModLife::visit(TokenCreature *tc)
{
    tc->setLife(tc->getLife()+1);
}

void ModLife::visit(TokenModule *tm)
{
    tm->setLife(tm->getLife()+1);
}

