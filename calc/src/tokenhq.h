#ifndef TOKENHQ_H
#define TOKENHQ_H

#include "tokenmodhq.h"

class Mod;

class CALC_DLL()TokenHQ: public TokenModHq
{
public:
    TokenHQ();
    virtual ~TokenHQ();
    virtual TokenPutable* clone() const;
    virtual void accept(Visitor& v);
    static TokenPtr create(ptree Ptree, Color color);
private:
    //TokenHQ(const TokenHQ& old);
};

#endif // TOKENHQ_H
