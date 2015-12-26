#include "modadditionalaction.h"

ModAdditionalAction::~ModAdditionalAction()
{

}

void ModAdditionalAction::modify(TokenCreature *tc)
{
    tc->setAdditionalAction(true);
}

Mod *ModAdditionalAction::clone() const
{
    return new ModAdditionalAction(*this);
}

Mod* ModAdditionalAction::create(ptree xml)
{
    std::vector<int> directions;
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, xml.get_child("directions") )
    {
        directions.push_back(v.second.get<int>("dir_id"));
    }
    return new ModAdditionalAction(directions);
}