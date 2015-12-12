#ifndef MODPRIORITY_H
#define MODPRIORITY_H

#include "mod.h"

class ModPriority : public Mod
{
public:
    ModPriority(std::vector<int> directions) : Mod(directions) {}
    virtual ~ModPriority();
    virtual void modify(TokenCreature* tc);
};

#endif // MODPRIORITY_H
