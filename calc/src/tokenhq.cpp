#include "tokenhq.h"

TokenHQ::TokenHQ()
{

}

TokenHQ::~TokenHQ()
{

}

void TokenHQ::accept(Visitor &v)
{
    //TODO: rozwiązać to inaczej
    v.visit(dynamic_cast<TokenCreature*>(this));
    v.visit(dynamic_cast<TokenModule*>(this));
}

