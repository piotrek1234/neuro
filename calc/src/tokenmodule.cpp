#include "tokenmodule.h"

TokenModule::TokenModule()
{

}

TokenModule::~TokenModule()
{
    //delete mod; //sypie warningiem
}

/*TokenPutable *TokenModule::clone() const
{
    TokenPutable* token = new TokenModule(*this);
    return token;
}*/

void TokenModule::accept(Visitor &v)
{
    v.visit(this);
}

/*TokenModule::TokenModule(const TokenModule &old)
{
    TokenModule token;
    Mod* mod = old.getMod()->clone();
    token.setMod(mod);
    return token;
}*/

