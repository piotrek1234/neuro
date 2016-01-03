#ifndef MODPRIORITY_H
#define MODPRIORITY_H

#include "mod.h"
#include "utils.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

class CALC_DLL()ModPriority : public Mod
{
public:
    ModPriority(){}
    ModPriority(std::vector<int> directions) : Mod(directions) {}
    virtual ~ModPriority();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature* tc);
    static Mod* create(ptree xml);
    static std::string typeName() {return typeName_;}
    
private:
    static std::string typeName_;
};

#endif // MODPRIORITY_H
