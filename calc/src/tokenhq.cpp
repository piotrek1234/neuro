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

Token* TokenHQ::create(ptree Ptree, Color color)
{
    Token* token = new TokenHQ();
    token->setColor(color);
    return token;
}
/*TokenHQ::TokenHQ(const TokenHQ &old)
{
    TokenHQ token;
    Mod* mod = old.getMod()->clone();
    token.setMod(mod);
    return token;
}*/

std::string TokenHQ::typeName="hq";



