#ifndef MODADDITIONALACTION_H
#define MODADDITIONALACTION_H

#include "mod.h"

class ModAdditionalAction : public Mod
{
public:
    ModAdditionalAction();
    virtual ~ModAdditionalAction();
//    virtual void visit(TokenCreature* tc);
//    virtual void visit(TokenHQ* th);
//    virtual void visit(TokenModule*){}
    virtual void modify(TokenCreature* tc);
};

#endif // MODADDITIONALACTION_H
