#ifndef MODULEFINDER_H
#define MODULEFINDER_H

#include <vector>
#include "tokenmodule.h"
#include "tokencreature.h"
#include "tokenhq.h"
#include "tokenmodhq.h"

using namespace std;

class ModuleFinder : public Visitor
{
public:
    ModuleFinder();
    virtual void visit(TokenCreature*) {}
    virtual void visit(TokenHQ* th);
    virtual void visit(TokenModule* tm);
    vector<TokenModHq*>::iterator getBegin();
    vector<TokenModHq*>::iterator getEnd();
    void clear();
private:
    vector<TokenModHq*> modules_;
};

#endif // MODULEFINDER_H
