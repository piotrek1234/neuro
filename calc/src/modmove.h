#ifndef MODMOVE_H
#define MODMOVE_H

#include "mod.h"

/*
 * - po ruszeniu usunąć movable
 * - co jeśli żeton domyślnie miał umiejętność movable?
 * - co jeśli więcej niż 1 moduł dawał umiejętność movable?
 * (rozwiązanie: tymczasowo movable jest intem)
 */

class ModMove : public Mod
{
public:
    ModMove();
    virtual ~ModMove();
    virtual void visit(TokenCreature* tc);
    virtual void visit(TokenModule* tm);
};

#endif // MODMOVE_H
