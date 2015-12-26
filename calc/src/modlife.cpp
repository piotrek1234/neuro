#include "modlife.h"
#include <iostream>

ModLife::~ModLife()
{

}

Mod *ModLife::clone() const
{
    return new ModLife(*this);
}

void ModLife::modify(TokenCreature* tc)
{
    tc->setLife(tc->getLife()+1);
}

Mod* ModLife::create(ptree xml)
{
    std::vector<int> directions;
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, xml.get_child("directions") )
    {
        directions.push_back(v.second.get<int>("dir_id"));
    }
    return new ModLife(directions);
}