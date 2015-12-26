#ifndef MODPRIORITY_H
#define MODPRIORITY_H

#include "mod.h"

class CALC_DLL()ModPriority : public Mod
{
public:
    ModPriority(std::vector<int> directions) : Mod(directions) {}
    virtual ~ModPriority();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature* tc);
};

#endif // MODPRIORITY_H
