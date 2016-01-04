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
    TokenModule* token = new TokenModule(*this);
    token->setMod(mod_->clone());
    return token;
}

void TokenModule::accept(Visitor &v)
{
    v.visit(this);
}

Token* TokenModule::create(ptree Ptree, Color color)
{
    TokenModule* token=new TokenModule(color);
    token->setId(Ptree.get<int>("id"));
    token->setName(Ptree.get<std::string>("name"));
    token->setMod(ModFactory::getInstance().create(Ptree));
    return token;
}

//std::string TokenModule::typeName_="module";
