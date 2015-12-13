#ifndef TOKENHQ_H
#define TOKENHQ_H

#include "tokenmodhq.h"

class Mod;

class TokenHQ: public TokenModHq
{
public:
    TokenHQ();
    virtual ~TokenHQ();
    //virtual TokenHQ* clone() const { return new TokenHQ(*this); }
    virtual void accept(Visitor& v);
    virtual Mod* getMod() const { return mod_; }
private:
    TokenHQ(const TokenHQ&) = default;
    Mod* mod_;
};

#endif // TOKENHQ_H
