#ifndef MODATTACK_H
#define MODATTACK_H

#include "mod.h"
#include "utils.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

class ModAttack : public Mod
{
public:
    ModAttack(std::vector<int> &directions, int attackBoost) : Mod(directions), attackBoost_(attackBoost) {}
    virtual ~ModAttack();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature* tc);
    static Mod* create(ptree xml);
private:
    int attackBoost_;
};

#endif // MODATTACK_H
