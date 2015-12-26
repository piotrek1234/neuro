#ifndef MODLIFE_H
#define MODLIFE_H

#include "mod.h"

class ModLife : public Mod
{
public:
    ModLife(std::vector<int> directions) : Mod(directions) {}
    virtual ~ModLife();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature *tc);
};

#endif // MODLIFE_H
