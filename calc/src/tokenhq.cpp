#include "tokenhq.h"

TokenHQ::TokenHQ()
{

}

TokenHQ::~TokenHQ()
{

}

TokenPutable *TokenHQ::clone() const
{
    TokenPutable* token = new TokenHQ(*this);
    return token;
}

void TokenHQ::accept(Visitor &v)
{
    v.visit(this);
}

/*TokenHQ::TokenHQ(const TokenHQ &old)
{
    TokenHQ token;
    Mod* mod = old.getMod()->clone();
    token.setMod(mod);
    return token;
}*/



