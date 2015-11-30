#ifndef TOKENACTION_H
#define TOKENACTION_H

#include "token.h"

class TokenAction : public Token
{
public:
    TokenAction();
    virtual ~TokenAction();
    virtual bool isPutable() const { return false; }
private:
    //ActionType action;
};

#endif // TOKENACTION_H
