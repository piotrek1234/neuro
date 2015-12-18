#include "modulefinder.h"

void ModuleFinder::visit(TokenHQ *th)
{
    if(th->getColor() == tc_->getColor())
    {
        //dla każdego kierunku moda
        for(auto it=th->getMod()->getDirectionBegin(); it != th->getMod()->getDirectionEnd(); ++it)
        {
            if(th->getPosition()+Hex::direction(*it+th->getAngle()) == tc_->getPosition()) //jeśli wskazuje na tc_
                th->getMod()->modify(tc_);
        }
    }
}

void ModuleFinder::visit(TokenModule *tm)
{
    if(tm->getColor() == tc_->getColor())
    {
        //dla każdego kierunku moda
        for(auto it=tm->getMod()->getDirectionBegin(); it != tm->getMod()->getDirectionEnd(); ++it)
        {
            if(tm->getPosition()+Hex::direction(*it+tm->getAngle()) == tc_->getPosition()) //jeśli wskazuje na tc_
                tm->getMod()->modify(tc_);
        }
    }
}
