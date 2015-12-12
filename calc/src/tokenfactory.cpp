#include "tokenfactory.h"

static TokenFactory& TokenFactory::getInstance()
{
    static TokenFactory instance;
    return instance;
}

void TokenFactory::register(std::string type id, TokenCreateFun fun)
{
    creators.insert(std::pair<std::string, TokenCreateFun>(type, fun));
}

TokenPtr TokenFactory::create(boost::property_tree::ptree::value_type const& xmlnode, Color color)
{
    if(xmlnode.first=="token")
    {
        std::string type=xmlnode.second.get<std::string>("type");
        std::map<std::string,TokenCreateFun>::cons_iterator it=creators.find(type);
        if(it != creators.end() )
            return it->second()(xmlnode, color);
    }
    return std::nullptr;
}

std::vector<TokenPtr> TokenFactory::createTokensFromFile(std::string filename, Color color)
{
    //std::ifstream configFile (filename, std::ifstream::out);
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(filename, pt);

    std::vector<TokenPtr> tokens;
    for( ptree::value_type const& v, pt.get_child("tokens") )
    {
        TokenPtr token=create(v, color);
        if(token!=std::nullptr)
        {
            tokens.push_back(token);
        }
    }
    configFile.close();
    return tokens;
}

TokenPtr createTokenCreature(node const& xmlnode, Color color)
{
    TokenPtr token(new TokenCreature());
    token->setColor(color);
    token->setPriority(xmlnode.second.get<unsigned int>("priority"));
    token->setAdditionalAction(xmlnode.second.get<unsigned int>("additional_action"));
    token->setMovable(xmlnode.second.get<unsigned int>("movable"));
    token->setLife(xmlnode.second.get<unsigned int>("life"));
    //TODO read attack and shield values
    return token;
}

TokenPtr createTokenAction(node const& xmlnode, Color color)
{
    TokenPtr token(new TokenAction());
    token->setColor(color);
    return token;
}

TokenPtr createTokenHQ(node const& xmlnode, Color color)
{
    TokenPtr token(new TokenHQ());
    token->setColor(color);
    return token;
}

TokenPtr createTokenModuleLife(node const& xmlnode, Color color)
{
    TokenPtr token(new TokenModule());
    token->setColor(color);
    return token;
}

TokenPtr createTokenModuleAttack(node const& xmlnode, Color color)
{
    TokenPtr token(new TokenModule());
    token->setColor(color);
    return token;
}

TokenPtr createTokenModulePrioryty(node const& xmlnode, Color color)
{
    TokenPtr token(new TokenModule());
    token->setColor(color);
    return token;
}

TokenPtr createTokenModuleAddAction(node const& xmlnode, Color color)
{
    TokenPtr token(new TokenModule());
    token->setColor(color);
    return token;
}