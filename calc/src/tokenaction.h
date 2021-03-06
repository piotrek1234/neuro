#ifndef TOKENACTION_H
#define TOKENACTION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif

#include "token.h"
#include "actiontype.h"
#include "utils.h"
#include <string>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

/**
 * @brief The TokenAction class is a token which can be used as action (battle, move, push)
 */
class CALC_DLL()TokenAction : public Token
{
public:
    TokenAction(){}
    TokenAction(ActionType actionType) : actionType_(actionType) {}
    virtual ~TokenAction();
    virtual bool isPutable() const { return false; }
    ActionType getType() const { return actionType_; }
    static Token* create(ptree Ptree, Color color);
    static std::string typeName() {return /*typeName_*/"action";}
    
private:
    ActionType actionType_;
    static ActionType getActionTypeByName(std::string name);
    //static std::string typeName_;
};

#endif // TOKENACTION_H
