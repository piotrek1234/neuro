#ifndef MODLIFE_H
#define MODLIFE_H

#include "mod.h"

class ModLife : public Mod
{
public:
    ModLife();
    virtual ~ModLife();
    /*virtual void visit(TokenCreature* tc);
    virtual void visit(TokenHQ* th);
    virtual void visit(TokenModule* tm);*/
    virtual void modify(TokenCreature *tc);
private:
    int life;
};

#endif // MODLIFE_H
