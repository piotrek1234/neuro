#ifndef MODATTACK_H
#define MODATTACK_H

#include "mod.h"
#include "utils.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

class CALC_DLL()ModAttack : public Mod
{
public:
    ModAttack(){}
    ModAttack(std::vector<int> &directions, int attackBoost) : Mod(directions), attackBoost_(attackBoost) {}
    virtual ~ModAttack();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature* tc);
    int getAttackValue(){return attackBoost_;}
    static Mod* create(ptree xml);
    static std::string typeName() {return typeName_;}
    
private:
    static std::string typeName_;
    int attackBoost_;
};

#endif // MODATTACK_H
