#include "tokenhq.h"

TokenHQ::TokenHQ()
{

}

TokenHQ::~TokenHQ()
{

}

TokenPutable *TokenHQ::clone() const
{
    TokenHQ* token = new TokenHQ(*this);
    token->setMod(mod_->clone());
    return token;
}

void TokenHQ::accept(Visitor &v)
{
    v.visit(this);
}

Token* TokenHQ::create(ptree Ptree, Color color)
{
    Token* token = new TokenHQ(color);
    token->setId(Ptree.get<int>("id"));
    // + mod
    return token;
}
/*TokenHQ::TokenHQ(const TokenHQ &old)
{
    mod_ = old.getMod()->clone();
}*/

std::string TokenHQ::typeName="hq";



