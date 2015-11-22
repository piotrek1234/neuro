#ifndef MODLIFE_H
#define MODLIFE_H

#include "mod.h"

class ModLife : public Mod
{
public:
    ModLife();
    virtual ~ModLife();
    virtual void visit(TokenCreature* tc);
    virtual void visit(TokenModule* tm);
private:
    int life;
};

#endif // MODLIFE_H
