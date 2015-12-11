#include "modulefinder.h"

ModuleFinder::ModuleFinder()
{
}

void ModuleFinder::visit(TokenHQ *th)
{
    modules_.push_back(th);
}

vector<TokenModule*>::iterator ModuleFinder::getBegin()
{
    return creatures_.begin();
}

vector<TokenModule*>::iterator ModuleFinder::getEnd()
{
    return creatures_.end();
}

void ModuleFinder::clear()
{
    modules_.clear();
}
