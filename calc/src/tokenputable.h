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

    int getMovable() const; //przy bitwie/przesuwaniu używać jako bool getMovable()
    void setMovable(int value);

    bool getActive() const;
    void setActive(bool value);

private:
    int life_;
    int angle_;  //chyba int
    int movable_;    //int żeby nie było konfliktu przy kasowaniu jednego z kilku modułów tego typu
    Hex position_;
    Hex direction_;
    bool active_;    //sieciarz może deaktywować żeton: nie bierze udziału w bitwie, nie można go przesuwać

};

#endif // TOKENPUTABLE_H
