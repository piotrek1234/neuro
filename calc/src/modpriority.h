#ifndef MODPRIORITY_H
#define MODPRIORITY_H

#include "mod.h"
#include "utils.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

class ModPriority : public Mod
{
public:
    ModPriority(std::vector<int> directions) : Mod(directions) {}
    virtual ~ModPriority();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature* tc);
    static Mod* create(ptree xml);
};

#endif // MODPRIORITY_H
