#include "modadditionalaction.h"

ModAdditionalAction::ModAdditionalAction()
{

}

ModAdditionalAction::~ModAdditionalAction()
{

}

void ModAdditionalAction::visit(TokenCreature *tc)
{
    tc->setAdditionalAction(true);
}


