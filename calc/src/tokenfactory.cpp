#include "tokenfactory.h"

TokenFactory& TokenFactory::getInstance()
{
    static TokenFactory instance;
    return instance;
}

TokenFactory::TokenFactory()
{
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
