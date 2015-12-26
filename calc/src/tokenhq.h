#ifndef TOKENHQ_H
#define TOKENHQ_H

#include "tokenmodhq.h"

class Mod;

class TokenHQ: public TokenModHq
{
public:
    TokenHQ();
    virtual ~TokenHQ();
    virtual TokenPutable* clone() const;
    virtual void accept(Visitor& v);
private:
    //TokenHQ(const TokenHQ& old);
};

#endif // TOKENHQ_H
