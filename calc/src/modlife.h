#ifndef MODLIFE_H
#define MODLIFE_H

#include "mod.h"

class ModLife : public Mod
{
public:
    ModLife(int life) : life_(life) {}
    virtual ~ModLife();
    virtual void modify(TokenCreature *tc);
private:
    int life_;
};

#endif // MODLIFE_H
