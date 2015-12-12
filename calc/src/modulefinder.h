#ifndef MODULEFINDER_H
#define MODULEFINDER_H

#include <vector>
#include "tokenmodule.h"
#include "tokencreature.h"
#include "tokenhq.h"

using namespace std;

class ModuleFinder : public Visitor
{
public:
    ModuleFinder();
    virtual void visit(TokenCreature*) {}
    virtual void visit(TokenHQ* th);
    virtual void visit(TokenModule* tm);
    vector<TokenModule*>::iterator getBegin();
    vector<TokenModule*>::iterator getEnd();
    void clear();
private:
    vector<TokenModule*> modules_;
};

#endif // MODULEFINDER_H
