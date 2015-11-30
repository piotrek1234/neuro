#include "modadditionalaction.h"

ModAdditionalAction::ModAdditionalAction()
{

}

ModAdditionalAction::~ModAdditionalAction()
{

}

void ModAdditionalAction::visit(TokenCreature *tc)
{
    tc->setAdditionalAction(tc->getAdditionalAction()+1);
}

void ModAdditionalAction::visit(TokenHQ *th)
{
    th->setAdditionalAction(th->getAdditionalAction()+1);
}

void ModAdditionalAction::detach(TokenCreature *)
{
    //th->setAdditionalAction(th->getAdditionalAction()-1);
}

void ModAdditionalAction::detach(TokenHQ *th)
{
    th->setAdditionalAction(th->getAdditionalAction()-1);
}


