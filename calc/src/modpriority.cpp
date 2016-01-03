#include "modpriority.h"

ModPriority::~ModPriority()
{

}

Mod *ModPriority::clone() const
{
    return new ModPriority(*this);
}

void ModPriority::modify(TokenCreature *tc)
{
    tc->setPriority(tc->getPriority()+1);
}

Mod* ModPriority::create(ptree xml)
{
    std::vector<int> directions;
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, xml.get_child("directions") )
    {
        directions.push_back(std::stoi(v.second.data()));
    }
    return new ModPriority(directions);
}

// std::string ModPriority::typeName_="priority";