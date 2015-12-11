#ifndef MODATTACK_H
#define MODATTACK_H

#include "mod.h"

class ModAttack : public Mod
{
public:
    ModAttack();
    virtual ~ModAttack();
    /*virtual void visit(TokenCreature* tc);
    virtual void visit(TokenHQ*){}  //sztabowi nie można ulepszyć siły ataku
    virtual void visit(TokenModule*){}*/
    virtual void modify(TokenCreature* tc);
};

#endif // MODATTACK_H
