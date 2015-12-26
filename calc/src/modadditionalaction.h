#ifndef MODADDITIONALACTION_H
#define MODADDITIONALACTION_H

#include "mod.h"

class CALC_DLL()ModAdditionalAction : public Mod
{
public:
    ModAdditionalAction(std::vector<int> &directions) : Mod(directions) {}
    virtual ~ModAdditionalAction();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature* tc);
};

#endif // MODADDITIONALACTION_H
