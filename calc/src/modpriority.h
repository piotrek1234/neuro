#ifndef MODPRIORITY_H
#define MODPRIORITY_H

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
 * @brief The ModPriority class is used to apply higher priority for token creatures
 */
class CALC_DLL()ModPriority : public Mod
{
public:
    ModPriority(){}
    ModPriority(std::vector<int> directions) : Mod(directions) {}
    virtual ~ModPriority();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature* tc);
    static Mod* create(ptree xml);
    static std::string typeName() {return /*typeName_*/"priority";}
    
private:
    //static std::string typeName_;
};

#endif // MODPRIORITY_H
