#include "modmove.h"

ModMove::ModMove()
{

}

ModMove::~ModMove()
{

}

void ModMove::visit(TokenCreature *tc)
{
    tc->setMovable(tc->getMovable()+1);
}

void ModMove::visit(TokenModule *tm)
{
    tm->setMovable(tm->getMovable()+1);
}

