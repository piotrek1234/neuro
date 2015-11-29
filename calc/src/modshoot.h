#ifndef MODSHOOT_H
#define MODSHOOT_H

#include "mod.h"

class ModShoot : public Mod
{
public:
    ModShoot();
    virtual ~ModShoot();
    virtual void visit(TokenCreature* tc);
    virtual void visit(TokenModule*){}   // moduły nie strzelają
    virtual void visit(TokenHQ*){}  //sztaby nie strzelają
};

#endif // MODSHOOT_H
