#ifndef TOKENFACTORY_H
#define TOKENFACTORY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif

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

class CALC_DLL()TokenFactory
{
    public:
        typedef Token*(*TokenCreateFun)(ptree, Color);
        static TokenFactory& getInstance();
        void registerFun(std::string type, TokenCreateFun fun);
        Token* create(boost::property_tree::ptree::value_type const& xmlnode, Color color);
        std::vector<Token*> createTokensFromFile(std::string filename, Color color);
        
    private:
        std::map<std::string,TokenCreateFun> creators;
        TokenFactory();
        TokenFactory(const TokenFactory&);
};

#endif // TOKENFACTORY_H
