#ifndef MODATTACK_H
#define MODATTACK_H

#include "mod.h"

class ModAttack : public Mod
{
public:
    ModAttack(int attackBoost) : attakBoost_(attackBoost) {}
    virtual ~ModAttack();
    virtual void modify(TokenCreature* tc);
private:
    int attakBoost_;
};

#endif // MODATTACK_H
