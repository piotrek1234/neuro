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
    //v.visit(dynamic_cast<TokenCreature*>(this));
   // v.visit(dynamic_cast<TokenModule*>(this));
    v.visit(this);
}
int TokenHQ::getPriority() const
{
    return priority_;
}

void TokenHQ::setPriority(int priority)
{
    priority_ = priority;
}
int TokenHQ::getAdditionalAction() const
{
    return additionalAction_;
}

void TokenHQ::setAdditionalAction(int additionalAction)
{
    additionalAction_ = additionalAction;
}



