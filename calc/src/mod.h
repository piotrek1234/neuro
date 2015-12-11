#ifndef MOD_H
#define MOD_H

//#include "visitor.h"
#include "tokencreature.h"
//#include "tokenmodule.h"
//#include "tokenhq.h"
#include "hex.h"
#include <vector>

class Mod : public Visitor
{
public:
    Mod();
    virtual ~Mod() = 0;
    virtual void modify(TokenCreature*)=0;
protected:
    std::vector<Hex> directions;
    std::vector<TokenPutable*> modded_;
};

#endif // MOD_H
