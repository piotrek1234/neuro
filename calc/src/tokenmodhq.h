/*
 * Po co jest TokenModHQ?
 * TokenHQ może być trzymany w jednym kontenerze razem z TokenModule i jest tam traktowany jako TokenModule.
 * TokenHQ musi być oddzielną klasą, bo może atakować, ale nie wpływają na niego modyfikacje, czyli
 * prawie jest typem TokenCreature -> jest wizytowany inaczej niż TokenCreature i TokenModule.
 */
#ifndef TOKENMODHQ_H
#define TOKENMODHQ_H


#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif


#include "tokenputable.h"
#include "mod.h"

/**
 * @brief The TokenModHq class is a common interface for token modules and token hqs
 */
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
