#ifndef TOKENPUTABLE_H
#define TOKENPUTABLE_H

#include "visitor.h"
#include "token.h"
#include "hex.h"

class TokenPutable : public Token
{
public:
    TokenPutable(int life) : position_(Hex(5,5)), angle_(0), life_(life) {}
    virtual ~TokenPutable();
    virtual bool isPutable() const { return true; }
    virtual void accept(Visitor& v) = 0;
    virtual TokenPutable* clone() = 0;

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
