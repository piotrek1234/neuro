#ifndef MODATTACK_H
#define MODATTACK_H

#include "mod.h"

class CALC_DLL()ModAttack : public Mod
{
public:
    ModAttack(std::vector<int> &directions, int attackBoost) : Mod(directions), attackBoost_(attackBoost) {}
    virtual ~ModAttack();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature* tc);
private:
    int attackBoost_;
};

#endif // MODATTACK_H
