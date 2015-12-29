#include "tokenfactory.h"
#include <iostream>

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
    std::cout<<"register fun "<<type<<std::endl;
    creators[type]=fun;
    std::cout<<"register fun "<<type<<std::endl;
    //creators.insert(std::pair<std::string, TokenCreateFun>(type, fun));
}

Token* TokenFactory::create(boost::property_tree::ptree::value_type const& xmlnode, Color color)
{
    std::cout<<xmlnode.first<<std::endl;
    if(xmlnode.first=="token")
    {
        ptree tokenNode = xmlnode.second;
        std::string type=xmlnode.second.get<std::string>("type");
        std::cout<<type<<std::endl;
        std::map<std::string,TokenCreateFun>::const_iterator it=creators.find(type);
        if(it != creators.end() )
            return it->second(tokenNode, color);
        std::cout<<"creator not found"<<std::endl;
    }
    return nullptr;
}

std::vector<Token*> TokenFactory::createTokensFromFile(std::string filename, Color color)
{
    std::cout<<creators.size()<<std::endl;
    //std::ifstream configFile (filename, std::ifstream::out);
    //using boost::property_tree::ptree;
    boost::property_tree::ptree pt;
    boost::property_tree::read_xml(filename, pt);

    std::vector<Token*> tokens;
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, pt.get_child("tokens") )
    {
        std::cout<<"token!"<<std::endl;
        Token* token=create(v, color);
        if(token!=nullptr)
        {
            std::cout<<"not null ptr"<<std::endl;
            tokens.push_back(token);
        }
    }
    return tokens;
}
