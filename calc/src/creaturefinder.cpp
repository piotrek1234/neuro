#include "creaturefinder.h"

CreatureFinder::CreatureFinder()
{
}

void CreatureFinder::visit(TokenCreature *tc)
{
    creatures_.push_back(tc);
}

void CreatureFinder::visit(TokenHQ* th)
{
    hq_.push_back(th);
}

vector<TokenCreature*>::iterator CreatureFinder::getBegin()
{
    return creatures_.begin();
}

vector<TokenCreature*>::iterator CreatureFinder::getEnd()
{
    return creatures_.end();
}

vector<TokenHQ*>::iterator CreatureFinder::getHqBegin()
{
    return hq_.begin();
}

vector<TokenHQ*>::iterator CreatureFinder::getHqEnd()
{
    return hq_.end();
}

void CreatureFinder::clear()
{
    creatures_.clear();
    hq_.clear();
}

