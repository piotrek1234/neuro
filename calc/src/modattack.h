#ifndef MODATTACK_H
#define MODATTACK_H

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif

#include "mod.h"
#include "utils.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

/**
 * @brief The ModAttack class is used to apply attack boost for token creatures
 */
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
    static std::string typeName() {return /*typeName_*/"attack";}
private:
    //static std::string typeName_;
    int attackBoost_;
};

#endif // MODATTACK_H
