#ifndef TOKENCREATURE_H
#define TOKENCREATURE_H

#include "tokenputable.h"
#include "vector"
#include "hex.h"

class TokenCreature : virtual public TokenPutable
{
public:
    TokenCreature();
    virtual ~TokenCreature();
    virtual void accept(Visitor& v);
    int getAdditionalAction() const;
    void setAdditionalAction(int value);

    int getPriority() const;
    void setPriority(int value);

private:
    int priority_;
    std::vector<Hex> attack;
    std::vector<Hex> shoot;
    std::vector<Hex> net;
    std::vector<Hex> shield;
    int additionalAction_;  //zieloni mają sztab dający możliwość udziału w dwóch inicjatywach
};

#endif // TOKENCREATURE_H
