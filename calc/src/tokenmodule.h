#ifndef TOKENMODULE_H
#define TOKENMODULE_H

#include "tokenputable.h"
#include "hex.h"
#include <vector>

class Mod;
class TokenModule : public TokenPutable
{
public:
    TokenModule();
    virtual ~TokenModule();
    virtual void accept(Visitor& v);
private:
    Mod* mod_;
    //std::vector<Hex> directions_; //tutaj albo w Mod
};

#endif // TOKENMODULE_H
