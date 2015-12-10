#ifndef TOKENPUTABLE_H
#define TOKENPUTABLE_H

#include "visitor.h"
#include "token.h"
#include "hex.h"

class TokenPutable : public Token
{
public:
    TokenPutable() : position_(Hex(5,5)), direction_(Hex(0,-1)){}
    virtual ~TokenPutable();
    virtual bool isPutable() const { return true; }
    virtual void accept(Visitor& v)=0;
    int getLife() const;
    void setLife(int value);



private:
    int life_;
    int angle_;  //chyba int
    Hex position_;
    Hex direction_;

};

#endif // TOKENPUTABLE_H
