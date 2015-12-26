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
#include "color.h"
#include "tokenaction.h"
#include "tokencreature.h"
#include "tokenhq.h"
#include "tokenmodule.h"
#include "modadditionalaction.h"
#include "modattack.h"
#include "modlife.h"
#include <boost/foreach.hpp>
#include "modpriority.h"

class TokenFactory
{
    public:
        typedef TokenPtr(*TokenCreateFun)(ptree, Color);
        static TokenFactory& getInstance();
        void registerFun(std::string type, TokenCreateFun fun); //było register() i błąd że to słowo kluczowe
        TokenPtr create(boost::property_tree::ptree::value_type const& xmlnode, Color color);
        std::vector<TokenPtr> createTokensFromFile(std::string filename, Color color);
        TokenPtr createTokenCreature(ptree const&, Color);
        TokenPtr createTokenAction(ptree const&, Color);
        TokenPtr createTokenHQ(ptree const&, Color);
        TokenPtr createTokenModuleLife(ptree const&, Color);
        TokenPtr createTokenModuleAttack(ptree const&, Color);
        TokenPtr createTokenModulePrioryty(ptree const&, Color);
        TokenPtr createTokenModuleAddAction(ptree const&, Color);
        
    private:
        std::map<std::string,TokenCreateFun> creators;
        TokenFactory();
        TokenFactory(const TokenFactory&);
        std::map<std::string, ActionType> actions;
};

#endif // TOKENFACTORY_H
