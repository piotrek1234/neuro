#ifndef TOKENMODULE_H
#define TOKENMODULE_H

#include <vector>
#include "tokenmodhq.h"
#include "hex.h"
#include "utils.h"
//#include "mod.h"
#include <string>
#include "modfactory.h"

class Mod;
class TokenModule : public TokenModHq
{
public:
    TokenModule();
    virtual ~TokenModule();
    virtual TokenPutable* clone() const;
    virtual void accept(Visitor& v);
    static TokenPtr create(ptree Ptree, Color color);
private:
    TokenModule(const TokenModule& old);
};

#endif // TOKENMODULE_H
