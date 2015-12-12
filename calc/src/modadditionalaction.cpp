#include "modadditionalaction.h"

ModAdditionalAction::~ModAdditionalAction()
{

}

void ModAdditionalAction::modify(TokenCreature *tc)
{
    tc->setAdditionalAction(tc->getAdditionalAction()+1);
}




