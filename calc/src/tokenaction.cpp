#include "tokenaction.h"

TokenAction::~TokenAction()
{

}

Token* TokenAction::create(ptree xmlnode, Color color)
{
    std::string type = xmlnode.get<std::string>("action_type");
    ActionType action=TokenAction::getActionTypeByName(type);
    Token* token=new TokenAction(action);
    token->setColor(color);
    token->setId(xmlnode.get<int>("id"));
    token->setName(xmlnode.get<std::string>("name"));
    return token;
}

ActionType TokenAction::getActionTypeByName(std::string name)
{
    if(name=="battle")
            return ActionType::BATTLE;
    if(name=="move")
            return ActionType::MOVE;
    if(name=="push")
            return ActionType::PUSH;
    return ActionType::NONE;
}

// std::string TokenAction::typeName_="action";
