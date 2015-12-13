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
    //virtual TokenModule* clone() const { return new TokenModule(*this); }
    virtual void accept(Visitor& v);
    virtual Mod* getMod() const { return mod_; }
private:
    TokenModule(const TokenModule& tm);
    Mod* mod_;
    //std::vector<Hex> directions_; //tutaj albo w Mod
};

#endif // TOKENMODULE_H
