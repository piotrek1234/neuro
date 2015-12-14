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
    ModuleFinder() {}
    void setTarget(TokenCreature* tc) { tc_ = tc; }
    virtual void visit(TokenCreature*) {}
    virtual void visit(TokenHQ* th);
    virtual void visit(TokenModule* tm);
private:
    TokenCreature* tc_;
};

#endif // MODULEFINDER_H
