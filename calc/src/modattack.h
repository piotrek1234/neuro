#ifndef MODATTACK_H
#define MODATTACK_H

#include "mod.h"

class ModAttack : public Mod
{
public:
    ModAttack();
    virtual ~ModAttack();
    virtual void visit(TokenCreature* tc);
    virtual void visit(TokenModule*){}
};

#endif // MODATTACK_H
