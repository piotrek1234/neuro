#ifndef MODFACTORY_H
#define MODFACTORY_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <boost/smart_ptr.hpp>
#include "mod.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <string>
#include "utils.h"

class CALC_DLL()ModFactory
{
    public:
        typedef Mod*(*ModCreateFun)(ptree);
        static ModFactory& getInstance();
        void registerFun(std::string type, ModCreateFun fun); 
        Mod* create(ptree xml);
        
    private:
        std::map<std::string,ModCreateFun> creators;
        ModFactory();
        ModFactory(const ModFactory&);
};

#endif // MODFACTORY_H