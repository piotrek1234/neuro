#ifndef TOKENCREATURE_H
#define TOKENCREATURE_H

#include "tokenputable.h"
#include <map>

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

    int getMovable() const;
    void setMovable(int value);

    void addAttack(int dirId, int value);
    int getAttack(int dirId) const;

    void setShield(int dirId, bool value);
    bool getShield(int dirId) const;

private:
    TokenCreature(const TokenCreature&) = default;
    int priority_;
    std::map<int, int> attack_; //TODO wartość ataku w każdym kierunku
    std::map<int, bool> shield_;
    int additionalAction_;  //zieloni mają sztab dający możliwość udziału w dwóch inicjatywach
    int movable_;
};

#endif // TOKENCREATURE_H
