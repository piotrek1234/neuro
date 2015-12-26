#include "tokenfactory.h"

TokenFactory& TokenFactory::getInstance()
{
    static TokenFactory instance;
    return instance;
}

TokenFactory::TokenFactory()
{
    actions["battle"] = ActionType::BATTLE;
    actions["move"] = ActionType::MOVE;
    actions["push"] = ActionType::PUSH;
}

void TokenFactory::registerFun(std::string type, TokenCreateFun fun)
{
    creators.insert(std::pair<std::string, TokenCreateFun>(type, fun));
}

TokenPtr TokenFactory::create(boost::property_tree::ptree::value_type const& xmlnode, Color color)
{
    if(xmlnode.first=="token")
    {
        ptree tokenNode = xmlnode.second;
        std::string type=xmlnode.second.get<std::string>("type");
        std::map<std::string,TokenCreateFun>::const_iterator it=creators.find(type);
        if(it != creators.end() )
            return it->second(tokenNode, color);
    }
    return nullptr;
}

std::vector<TokenPtr> TokenFactory::createTokensFromFile(std::string filename, Color color)
{
    //std::ifstream configFile (filename, std::ifstream::out);
    //using boost::property_tree::ptree;
    boost::property_tree::ptree pt;
    boost::property_tree::read_xml(filename, pt);

    std::vector<TokenPtr> tokens;
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, pt.get_child("tokens") )
    {
        TokenPtr token=create(v, color);
        if(token!=nullptr)
        {
            tokens.push_back(token);
        }
    }
    return tokens;
}

TokenPtr createTokenCreature(ptree const& xmlnode, Color color)
{
    boost::shared_ptr<TokenCreature> token(new TokenCreature());
    token->setColor(color);
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, xmlnode.get_child("") )
    {
        std::string label = v.first;
        if(label == "priority")
        {
            token->setPriority(xmlnode.get<unsigned int>("priority"));
            break;
        }
        if(label == "additional_action")
        {
            token->setAdditionalAction(xmlnode.get<unsigned int>("additional_action"));
            break;
        }
        if(label ==  "movable")
        {
            token->setMovable(xmlnode.get<unsigned int>("movable"));
            break;
        }
        if(label == "life")
        {
            token->setLife(xmlnode.get<unsigned int>("life"));
            break;
        }
        if(label == "attack")
        {
            token->addAttack(v.second.get<unsigned int>("dir_id"), v.second.get<unsigned int>("value"));
            break;
        }
        if(label == "shield")
        {
            token->setShield(v.second.get<unsigned int>("dir_id"), v.second.get<bool>("value"));
            break;
        }
    }
    return token;
}

TokenPtr createTokenAction(ptree const& xmlnode, Color color)
{
    std::string type = xmlnode.get<std::string>("action_type");
    ActionType action=actions[type];
    TokenPtr token(new TokenAction(action));
    token->setColor(color);
    return token;
}

TokenPtr createTokenHQ(ptree const& xmlnode, Color color)
{
    TokenPtr token(new TokenHQ());
    token->setColor(color);
    return token;
}

TokenPtr createTokenModuleLife(ptree const& xmlnode, Color color)
{
    TokenPtr token(new TokenModule());
    token->setColor(color);
    return token;
}

TokenPtr createTokenModuleAttack(ptree const& xmlnode, Color color)
{
    TokenPtr token(new TokenModule());
    token->setColor(color);
    return token;
}

TokenPtr createTokenModulePrioryty(ptree const& xmlnode, Color color)
{
    TokenPtr token(new TokenModule());
    token->setColor(color);
    return token;
}

TokenPtr createTokenModuleAddAction(ptree const& xmlnode, Color color)
{
    TokenPtr token(new TokenModule());
    token->setColor(color);
    return token;
}
