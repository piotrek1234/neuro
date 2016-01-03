#ifndef TOKENMODULE_H
#define TOKENMODULE_H

#include <vector>
#include "tokenmodhq.h"
#include "hex.h"
#include "utils.h"
#include <string>
#include "modfactory.h"

class Mod;

class CALC_DLL()TokenModule : public TokenModHq
{
public:
    TokenModule();
    TokenModule(Color color) { setColor(color); }
    virtual ~TokenModule();
    virtual TokenPutable* clone() const;
    virtual void accept(Visitor& v);
    static Token* create(ptree Ptree, Color color);
    static std::string typeName() {return /*typeName_*/"module";}
    
private:
    //static std::string typeName_;
};

#endif // TOKENMODULE_H
