#ifndef TOKENFACTORY_H
#define TOKENFACTORY_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <boost/smart_ptr.hpp>
#include "token.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <fstream> 
#include "utils.h"

class TokenFactory
{
    public:
        typedef TokenPtr(*TokenCreateFun)(node);
        static TokenFactory& getInstance();
        void register(std::string type id, TokenCreateFun fun);
        TokenPtr create(boost::property_tree::ptree::value_type const& xmlnode);
        std::vector<TokenPtr> createTokensFromFile(std::string filename);
        TokenPtr createTokenCreature(node);
        TokenPtr createTokenAction(node);
        TokenPtr createTokenHQ(node);
        TokenPtr createTokenModuleLife(node);
        TokenPtr createTokenModuleAttack(node);
        TokenPtr createTokenModulePrioryty(node);
        TokenPtr createTokenModuleAddAction(node);
        
    private:
        std::map<std::string,TokenCreateFun> creators;
        TokenFactory(){}
        TokenFactory(const TokenFactory&);
}

#endif // TOKENFACTORY_H
