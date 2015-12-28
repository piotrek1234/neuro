#include "tokenmodule.h"

TokenModule::TokenModule()
{

}

TokenModule::~TokenModule()
{
    //delete mod; //sypie warningiem
}

TokenPutable *TokenModule::clone() const
{
    TokenPutable* token = new TokenModule(*this);
    return token;
}

void TokenModule::accept(Visitor &v)
{
    v.visit(this);
}

TokenModule::TokenModule(const TokenModule &old)
{
    setMod(old.getMod()->clone());
}

Token* TokenModule::create(ptree Ptree, Color color)
{
    TokenModule* token=new TokenModule();
    token->setColor(color);
    token->setMod(ModFactory::getInstance().create(Ptree));
    return token;
}

std::string TokenModule::typeName="module";