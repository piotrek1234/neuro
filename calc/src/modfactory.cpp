#include "modfactory.h"

ModFactory& ModFactory::getInstance()
{
    static ModFactory instance;
    return instance;
}

ModFactory::ModFactory()
{
}

void ModFactory::registerFun(std::string type, ModCreateFun fun)
{
    creators.insert(std::pair<std::string, ModCreateFun>(type, fun));
}

Mod* ModFactory::create(ptree xml)
{
    std::string type = xml.get<std::string>("module_type");
    std::map<std::string,ModCreateFun>::const_iterator it=creators.find(type);
    if(it != creators.end() )
        return it->second(xml);
    return nullptr;
}