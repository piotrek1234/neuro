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

TokenPtr TokenFactory::create(boost::property_tree::ptree::value_type const& xmlnode)
{
    if(xmlnode.first=="token")
    {
        std::string type=xmlnode.second.get<std::string>("type");
        std::map<std::string,TokenCreateFun>::cons_iterator it=creators.find(type);
        if(it != creators.end() )
            return it->second();
    }
    return std::nullptr;
}

std::vector<TokenPtr> TokenFactory::createTokensFromFile(std::string filename)
{
    std::ifstream configFile (filename, std::ifstream::out);
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(configFile, pt);

    std::vector<TokenPtr> tokens;
    BOOST_FOREACH( ptree::value_type const& v, pt.get_child("tokens") )
    {
        TokenPtr token=create(v);
        if(token!=std::nullptr)
        {
            tokens.push_back(token);
        }
    }
    configFile.close();
    return tokens;
}

TokenPtr createTokenCreature(node)
{
    
}

TokenPtr createTokenAction(node)
{
    
}

TokenPtr createTokenHQ(node)
{
    
}

TokenPtr createTokenModuleLife(node)
{
    
}

TokenPtr createTokenModuleAttack(node)
{
    
}

TokenPtr createTokenModulePrioryty(node)
{
    
}

TokenPtr createTokenModuleAddAction(node)
{
    
}