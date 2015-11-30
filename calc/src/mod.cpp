#include "mod.h"

Mod::Mod()
{

}

void Mod::detachMods()
{
    for(TokenPutable* tp : modded_)
    {
        //this->detach(tp);
    }
}

Mod::~Mod()
{

}



