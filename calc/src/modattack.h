#ifndef MODATTACK_H
#define MODATTACK_H

#include "mod.h"

class ModAttack : public Mod
{
public:
    ModAttack(std::vector<int> &directions, int attackBoost) : Mod(directions), attackBoost_(attackBoost) {}
    virtual ~ModAttack();
    virtual void modify(TokenCreature* tc);
private:
    int attackBoost_;
};

#endif // MODATTACK_H
