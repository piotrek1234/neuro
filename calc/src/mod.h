#ifndef MOD_H
#define MOD_H

#include "tokencreature.h"
#include "hex.h"
#include <vector>

class Mod : public Visitor
{
public:
    Mod();
    virtual ~Mod() = 0;
    virtual void modify(TokenCreature*)=0;
protected:
    std::vector<int> directions;
};

#endif // MOD_H
