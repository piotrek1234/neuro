#ifndef TOKENHQ_H
#define TOKENHQ_H

#include "tokenmodhq.h"
#include "modfactory.h"
#include <string>

class Mod;

class CALC_DLL()TokenHQ: public TokenModHq
{
public:
    TokenHQ();
    TokenHQ(Color color) { setColor(color); }
    virtual ~TokenHQ();
    //TokenHQ(const TokenHQ& old);
    virtual TokenPutable* clone() const;
    virtual void accept(Visitor& v);
    static Token* create(ptree Ptree, Color color);
    static std::string typeName() {return /*typeName_*/"hq";}
    
private:
    // static std::string typeName_;
};

#endif // TOKENHQ_H
