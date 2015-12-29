#include "modattack.h"

ModAttack::~ModAttack()
{

}

Mod *ModAttack::clone() const
{
    return new ModAttack(*this);
}

void ModAttack::modify(TokenCreature *tc)
{
    for(int i=0; i<6; ++i)
    {
        if(tc->getAttack(i) > 0)
            tc->addAttack(i, attackBoost_);
    }
}

Mod* ModAttack::create(ptree xml)
{
    int val=xml.get<int>("value");    
    std::vector<int> directions;
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, xml.get_child("directions") )
    {
        directions.push_back(std::stoi(v.second.data()));
    }
    return new ModAttack(directions, val);
}

std::string ModAttack::typeName="attack";