#ifndef MODPRIORITY_H
#define MODPRIORITY_H

#include "mod.h"
#include "tokencreature.h"
#include "tokenmodule.h"

class ModPriority : public Mod
{
public:
    ModPriority();
    virtual ~ModPriority();
    virtual void visit(TokenCreature *tc);
    virtual void visit(TokenModule*){}
    virtual void visit(TokenHQ *th);
private:
    int priority;
};

#endif // MODPRIORITY_H
