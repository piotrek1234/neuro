#ifndef MODADDITIONALACTION_H
#define MODADDITIONALACTION_H

#ifdef CALC_EXPORTS
#define CALC_DLL(X) __declspec(dllexport)X
#else
#define CALC_DLL(X) X
#endif

#include "mod.h"

class ModAdditionalAction : public Mod
{
public:
    ModAdditionalAction(std::vector<int> &directions) : Mod(directions) {}
    virtual ~ModAdditionalAction();
    virtual void modify(TokenCreature* tc);
};

#endif // MODADDITIONALACTION_H
