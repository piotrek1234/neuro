#include "mod.h"

Mod::~Mod()
{

}

std::vector<int>::iterator Mod::getDirectionBegin()
{
    return directions_.begin();
}

std::vector<int>::iterator Mod::getDirectionEnd()
{
    return directions_.end();
}
