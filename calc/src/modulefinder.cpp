#include "modulefinder.h"

ModuleFinder::ModuleFinder()
{
}

void ModuleFinder::visit(TokenHQ *th)
{
    modules_.push_back(th);
}

void ModuleFinder::visit(TokenModule *tm)
{
    modules_.push_back(tm);
}

vector<TokenModHq*>::iterator ModuleFinder::getBegin()
{
    return modules_.begin();
}

vector<TokenModHq*>::iterator ModuleFinder::getEnd()
{
    return modules_.end();
}

void ModuleFinder::clear()
{
    modules_.clear();
}
