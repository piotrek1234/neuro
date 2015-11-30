#ifndef MODADDITIONALACTION_H
#define MODADDITIONALACTION_H

#include "mod.h"

class ModAdditionalAction : public Mod
{
public:
    ModAdditionalAction();
    virtual ~ModAdditionalAction();
    virtual void visit(TokenCreature* tc);
    virtual void visit(TokenHQ* th);
    virtual void visit(TokenModule*){}

    virtual void detach(TokenModule*){}
    virtual void detach(TokenCreature*);
    virtual void detach(TokenHQ*th);
};

#endif // MODADDITIONALACTION_H
