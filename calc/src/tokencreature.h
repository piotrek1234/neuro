#ifndef TOKENCREATURE_H
#define TOKENCREATURE_H

#include "tokenputable.h"
#include "vector"

class TokenCreature : public TokenPutable
{
public:
    TokenCreature();
    virtual ~TokenCreature();
    virtual void accept(Visitor& v);
    //virtual TokenCreature* clone() const { return new TokenCreature(*this); }

    int getAdditionalAction() const;
    void setAdditionalAction(int value);

    int getPriority() const;
    void setPriority(int value);

    int getMovable() const; //przy bitwie/przesuwaniu używać jako bool getMovable()
    void setMovable(int value);

    void addAttack(int value, int dirId);

private:
    TokenCreature(const TokenCreature&) = default;
    int priority_;
    std::vector<int> attack_; //TODO wartość ataku w każdym kierunku
    std::vector<int> shield_;
    int additionalAction_;  //zieloni mają sztab dający możliwość udziału w dwóch inicjatywach
    int movable_;
};

#endif // TOKENCREATURE_H
