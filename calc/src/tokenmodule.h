#ifndef TOKENMODULE_H
#define TOKENMODULE_H

#include "tokenmodhq.h"
#include "hex.h"
#include <vector>

class Mod;
class TokenModule : public TokenModHq
{
public:
    TokenModule();
    virtual ~TokenModule();
    //virtual TokenPutable* clone() const;
    virtual void accept(Visitor& v);
private:
    //TokenModule(const TokenModule& old);
};

#endif // TOKENMODULE_H
