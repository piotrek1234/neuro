#ifndef MODLIFE_H
#define MODLIFE_H

#include "mod.h"
#include "utils.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

class ModLife : public Mod
{
public:
    ModLife(std::vector<int> directions) : Mod(directions) {}
    virtual ~ModLife();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature *tc);
    static Mod* create(ptree xml);
};

#endif // MODLIFE_H
