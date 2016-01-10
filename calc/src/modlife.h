#ifndef MODLIFE_H
#define MODLIFE_H

#include "mod.h"
#include "utils.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

/**
 * @brief The ModLife class is used to apply additional life for token creatures
 */
class CALC_DLL()ModLife : public Mod
{
public:
    ModLife(){}
    ModLife(std::vector<int> directions) : Mod(directions) {}
    virtual ~ModLife();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature *tc);
    static Mod* create(ptree xml);
    static std::string typeName() {return /*typeName_*/"life";}
    
private:
    //static std::string typeName_;
};

#endif // MODLIFE_H
