#ifndef TOKENHQ_H
#define TOKENHQ_H

#include "tokenputable.h"

class Mod;

class TokenHQ: public TokenPutable  //przemyśleć czy nie lepiej będzie :TokenModule
{
public:
    TokenHQ();
    ~TokenHQ();
    virtual void accept(Visitor& v);
private:
    int life_;
    Mod* mod_;
};

#endif // TOKENHQ_H
