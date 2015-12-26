#ifndef MODADDITIONALACTION_H
#define MODADDITIONALACTION_H

#include "mod.h"
#include "utils.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

class CALC_DLL()ModAdditionalAction : public Mod
{
public:
    ModAdditionalAction(std::vector<int> &directions) : Mod(directions) {}
    virtual ~ModAdditionalAction();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature* tc);
    static Mod* create(ptree xml);
};

#endif // MODADDITIONALACTION_H
