#include "creaturefinder.h"

CreatureFinder::CreatureFinder()
{
}

void CreatureFinder::visit(TokenCreature *tc)
{
    creatures_.push_back(tc);
}

vector<TokenCreature*>::iterator CreatureFinder::getBegin()
{
    return creatures_.begin();
}

vector<TokenCreature*>::iterator CreatureFinder::getEnd()
{
    return creatures_.end();
}

void CreatureFinder::clear()
{
    creatures_.clear();
}
