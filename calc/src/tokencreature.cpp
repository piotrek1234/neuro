#include "tokencreature.h"

TokenCreature::TokenCreature()
{

}

TokenCreature::~TokenCreature()
{

}

void TokenCreature::accept(Visitor &v)
{
    v.visit(this);
}
int TokenCreature::getAdditionalAction() const
{
    return additionalAction_;
}

void TokenCreature::setAdditionalAction(int value)
{
    additionalAction_ = value;
}
int TokenCreature::getPriority() const
{
    return priority_;
}

void TokenCreature::setPriority(int value)
{
    priority_ = value;
}

void TokenCreature::addAttack(int value, int dirId)
{
    Hex::direction
}

