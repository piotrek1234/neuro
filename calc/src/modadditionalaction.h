#ifndef MODADDITIONALACTION_H
#define MODADDITIONALACTION_H

#include "mod.h"
#include "utils.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

/**
 * @brief The ModAdditionalAction class is used to apply additional action for token creatures
 */
class CALC_DLL()ModAdditionalAction : public Mod
{
public:
    ModAdditionalAction(){}
    ModAdditionalAction(std::vector<int> &directions) : Mod(directions) {}
    virtual ~ModAdditionalAction();
    virtual Mod* clone() const;
    virtual void modify(TokenCreature* tc);
    static Mod* create(ptree xml);
    static std::string typeName() {return /*typeName_*/"additional_action";}
    
private:
    //static const std::string typeName_;
};

#endif // MODADDITIONALACTION_H
