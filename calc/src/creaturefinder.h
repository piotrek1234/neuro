#ifndef CREATUREFINDER_H
#define CREATUREFINDER_H

#include "tokencreature.h"
#include "tokenmodule.h"
#include "tokenhq.h"
#include <vector>

using namespace std;

class CreatureFinder : public Visitor
{
public:
    CreatureFinder();
    virtual void visit(TokenCreature* tc);
    virtual void visit(TokenHQ* th);
    virtual void visit(TokenModule*) {}
    vector<TokenCreature*>::iterator getBegin();
    vector<TokenCreature*>::iterator getEnd();
    vector<TokenHQ*>::iterator getHqBegin();
    vector<TokenHQ*>::iterator getHqEnd();
    void clear();
private:
    vector<TokenCreature*> creatures_;
    vector<TokenHQ*> hq_;
};

#endif // CREATUREFINDER_H
