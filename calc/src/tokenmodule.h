#ifndef TOKENMODULE_H
#define TOKENMODULE_H

#include "tokenputable.h"
#include <vector>

class Mod;
class TokenModule : public virtual TokenPutable
{
public:
    TokenModule();
    virtual ~TokenModule();
    virtual void accept(Visitor& v);
private:
    Mod* mod_;
    //vector<Kierunek> directions;
};

#endif // TOKENMODULE_H
