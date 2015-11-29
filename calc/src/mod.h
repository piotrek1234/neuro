#ifndef MOD_H
#define MOD_H

#include "visitor.h"
#include "tokencreature.h"
#include "tokenmodule.h"
#include "tokenhq.h"
#include "hex.h"
#include <vector>

/*
 * - jak rozwiązać cofanie moda?
 *    drugi wizytator odpalany przy przesuwaniu/usuwaniu TokenMod?
 *    przy visit() dodawać zmodowane tokeny do listy, a przy odłączniu wywoływać im detach()?
 */

class Mod : public Visitor
{
public:
    Mod();
    virtual ~Mod() = 0;
    void detachMods();  //cofa mod dla każdego żetonu który zmodyfikował (woła detach(x))
    virtual void detach(TokenModule*)=0;  //można przemyśleć jak to załatwić
    virtual void detach(TokenCreature*)=0;
    virtual void detach(TokenHQ*)=0;
protected:
    std::vector<Hex> directions;
    std::vector<TokenPutable*> modded_;
};

#endif // MOD_H
