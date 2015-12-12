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
#include "modadditionalaction.h"
#include "modattack.h"
#include "modlife.h"
#include "modpriority.h"

class TokenFactory
{
    public:
        typedef TokenPtr(*TokenCreateFun)(node, Color);
        static TokenFactory& getInstance();
        void register(std::string type id, TokenCreateFun fun);
        TokenPtr create(boost::property_tree::ptree::value_type const& xmlnode);
        std::vector<TokenPtr> createTokensFromFile(std::string filename, Color color);
        TokenPtr createTokenCreature(node const&, Color);
        TokenPtr createTokenAction(node const&, Color);
        TokenPtr createTokenHQ(node const&, Color);
        TokenPtr createTokenModuleLife(node const&, Color);
        TokenPtr createTokenModuleAttack(node const&, Color);
        TokenPtr createTokenModulePrioryty(node const&, Color);
        TokenPtr createTokenModuleAddAction(node const&, Color);
        
    private:
        std::map<std::string,TokenCreateFun> creators;
        TokenFactory(){}
        TokenFactory(const TokenFactory&);
}

#endif // TOKENFACTORY_H
