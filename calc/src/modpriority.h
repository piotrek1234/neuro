#ifndef MODPRIORITY_H
#define MODPRIORITY_H

#include "mod.h"
#include "tokencreature.h"
#include "tokenmodule.h"

class ModPriority : public Mod
{
public:
    ModPriority(int priority) : priority_(priority) {}
    virtual ~ModPriority();
    virtual void modify(TokenCreature* tc);
private:
    int priority_;
};

#endif // MODPRIORITY_H
