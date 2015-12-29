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
    token->setId(Ptree.get<int>("id"));
    return token;
}
TokenHQ::TokenHQ(const TokenHQ &old)
{
    setMod(old.getMod()->clone());
}

std::string TokenHQ::typeName="hq";



