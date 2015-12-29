#ifndef TOKENHQ_H
#define TOKENHQ_H

#include "tokenmodhq.h"

class Mod;

class CALC_DLL()TokenHQ: public TokenModHq
{
public:
    TokenHQ();
    virtual ~TokenHQ();
    TokenHQ(const TokenHQ& old);
    virtual TokenPutable* clone() const;
    virtual void accept(Visitor& v);
    static Token* create(ptree Ptree, Color color);
    static std::string typeName;
};

#endif // TOKENHQ_H
