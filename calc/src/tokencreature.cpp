#include "tokencreature.h"

TokenCreature::~TokenCreature()
{

}

void TokenCreature::accept(Visitor &v)
{
    v.visit(this);
}

TokenPutable *TokenCreature::clone() const
{
    TokenPutable* token = new TokenCreature(*this);
    return token;
}

bool TokenCreature::getAdditionalAction() const
{
    return additionalAction_;
}

void TokenCreature::setAdditionalAction(bool value)
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

bool TokenCreature::getMovable() const
{
    return movable_;
}

void TokenCreature::setMovable(bool value)
{
    movable_ = value;
}

void TokenCreature::addAttack(int dirId, int value)
{
    if(attack_.find(dirId) == attack_.end())    //nie ma jeszcze ataku w tym kierunku
    {
        attack_.insert(std::pair<int, int>(dirId, value));
    }
    else
    {
        attack_[dirId] = attack_[dirId]+value;
    }
}

int TokenCreature::getAttack(int dirId) const
{
    auto strength = attack_.find(dirId);

    if(strength != attack_.end())
        return strength->second;
    return 0;
}

void TokenCreature::clearAttack()
{
    attack_.clear();
}

void TokenCreature::setShield(int dirId, bool value)
{
        shield_[dirId] = value;
        //jeśli było coś ustawione to nadpisze
        //jeśli nie było to wstawi
}

bool TokenCreature::getShield(int dirId) const
{
    auto temp = shield_.find(dirId);
    if(temp != shield_.end())
        return temp->second;
    return false;
}

void TokenCreature::clearShield()
{
    shield_.clear();
}

Token* TokenCreature::create(ptree xmlnode, Color color)
{
    TokenCreature* token = new TokenCreature();
    token->setColor(color);
    token->setId(xmlnode.get<int>("id"));
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, xmlnode.get_child("") )
    {
        std::string label = v.first;
        if(label == "priority")
        {
            token->setPriority(xmlnode.get<unsigned int>("priority"));
            //break;
        }
        if(label == "additional_action")
        {
            token->setAdditionalAction(xmlnode.get<unsigned int>("additional_action"));
            //break;
        }
        if(label ==  "movable")
        {
            token->setMovable(xmlnode.get<unsigned int>("movable"));
            //break;
        }
        if(label == "life")
        {
            token->setLife(xmlnode.get<unsigned int>("life"));
            //break;
        }
        if(label == "attack")
        {
            token->addAttack(v.second.get<unsigned int>("dir_id"), v.second.get<unsigned int>("value"));
            //break;
        }
        if(label == "shield")
        {
            token->setShield(v.second.get<unsigned int>("dir_id"), v.second.get<bool>("value"));
            //break;
        }
    }
    return token;
}

std::string TokenCreature::typeName="creature";