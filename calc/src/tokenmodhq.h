/*
 * Po co jest TokenModHQ?
 * TokenHQ może być trzymany w jednym kontenerze razem z TokenModule i jest tam traktowany jako TokenModule.
 * TokenHQ musi być oddzielną klasą, bo może atakować, ale nie wpływają na niego modyfikacje, czyli
 * prawie jest typem TokenCreature -> jest wizytowany inaczej niż TokenCreature i TokenModule.
 */
#ifndef TOKENMODHQ_H
#define TOKENMODHQ_H

#include "tokenputable.h"
#include "mod.h"

//class Mod;

class CALC_DLL()TokenModHq : public TokenPutable
{
public:
    Mod* getMod() const { return mod_; }
    void setMod(Mod* mod) { mod_ = mod; }
    Mod* getMod() { return mod_ ; } // for testing
    virtual bool getShield(int) const { return false; }
protected:
    TokenModHq();
    virtual ~TokenModHq();
    Mod* mod_;
};

#endif // TOKENMODHQ_H
