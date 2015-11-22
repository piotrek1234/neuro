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

