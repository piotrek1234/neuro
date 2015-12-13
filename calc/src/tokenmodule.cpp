#include "tokenmodule.h"

TokenModule::TokenModule()
{

}

TokenModule::~TokenModule()
{
    //delete mod; //sypie warningiem
}

void TokenModule::accept(Visitor &v)
{
    v.visit(this);
}

TokenModule::TokenModule(const TokenModule &tm)
{
    //głeboka kopia ze względu na mod_
    ///sprawdzić czy to ma sens
    Mod* copy = new Mod(*mod_);
    return copy;
}

