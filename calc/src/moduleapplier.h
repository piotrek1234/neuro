#ifndef MODULEAPPLIER_H
#define MODULEAPPLIER_H

#include <vector>
#include "tokenmodule.h"
#include "tokencreature.h"
#include "tokenhq.h"
#include "tokenmodhq.h"

using namespace std;

class CALC_DLL()ModuleApplier : public Visitor
{
public:
    ModuleApplier() {}
    void setTarget(TokenCreature* tc) { tc_ = tc; }
    virtual void visit(TokenCreature*) {}
    virtual void visit(TokenHQ* th);
    virtual void visit(TokenModule* tm);
private:
    TokenCreature* tc_;
};

#endif // MODULEAPPLIER_H
