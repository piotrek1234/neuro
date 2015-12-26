#include "modadditionalaction.h"

ModAdditionalAction::~ModAdditionalAction()
{

}

void ModAdditionalAction::modify(TokenCreature *tc)
{
    tc->setAdditionalAction(true);
}

Mod *ModAdditionalAction::clone() const
{
    return new ModAdditionalAction(*this);
}
