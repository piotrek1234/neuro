#ifndef MODFACTORY_H
#define MODFACTORY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif

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

/**
 * @brief The ModFactory class creates mods from XML
 */
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
