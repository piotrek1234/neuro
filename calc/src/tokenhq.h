#ifndef TOKENHQ_H
#define TOKENHQ_H

#include "tokencreature.h"
#include "tokenmodule.h"

class TokenHQ: public TokenCreature, public TokenModule
{
public:
    TokenHQ();
    ~TokenHQ();
    virtual void accept(Visitor& v);
};

#endif // TOKENHQ_H
