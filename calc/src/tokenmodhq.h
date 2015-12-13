#ifndef TOKENMODHQ_H
#define TOKENMODHQ_H

#include "tokenputable.h"
#include "mod.h"

class TokenModHq : public TokenPutable
{
public:
    TokenModHq();
    virtual ~TokenModHq() = 0;
    virtual Mod* getMod() const = 0;
    //virtual void accept(Visitor& v)=0;
};

#endif // TOKENMODHQ_H
