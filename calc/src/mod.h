#ifndef MOD_H
#define MOD_H

#include "visitor.h"
#include "tokencreature.h"
#include "tokenmodule.h"

/*
 * - co jeśli modyfikowany jest tokenHQ czyli obu typów na raz?
 * - jak rozwiązać cofanie moda?
 *    drugi wizytator odpalany przy przesuwaniu/usuwaniu TokenMod?
 */

class Mod : public Visitor
{
public:
    Mod();
    virtual ~Mod() = 0;
    //virtual void detach()=0;  //można przemyśleć jak to załatwić
//protected:
    //std::vector<Kierunek> directions;
};

#endif // MOD_H
