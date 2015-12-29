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
#include <boost/foreach.hpp>
#include <iostream>

class TokenFactory
{
    public:
        typedef Token*(*TokenCreateFun)(ptree, Color);
        static TokenFactory& getInstance();
        void registerFun(std::string type, TokenCreateFun fun); //było register() i błąd że to słowo kluczowe
        Token* create(boost::property_tree::ptree::value_type const& xmlnode, Color color);
        std::vector<Token*> createTokensFromFile(std::string filename, Color color);
        
    private:
        std::map<std::string,TokenCreateFun> creators;
        TokenFactory();
        TokenFactory(const TokenFactory&);
};

#endif // TOKENFACTORY_H
