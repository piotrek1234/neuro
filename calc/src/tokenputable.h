#ifndef TOKENPUTABLE_H
#define TOKENPUTABLE_H

#include "visitor.h"
#include "token.h"
#include "hex.h"

class TokenPutable : public Token
{
public:
    TokenPutable(int life) : life_(life), angle_(0), position_(Hex(5,5)) {}
    virtual ~TokenPutable();
    virtual bool isPutable() const { return true; }
    virtual void accept(Visitor& v) = 0;
    //virtual TokenPutable* clone() = 0;

    int getLife() const;
    void setLife(int value);
    Hex getPosition() const;
    void setPosition(Hex pos);

private:
    int life_;
    int angle_;  //chyba int
    Hex position_;
};

#endif // TOKENPUTABLE_H
