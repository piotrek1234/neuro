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
    //virtual TokenPutable* clone() const;

    int getAdditionalAction() const;
    void setAdditionalAction(int value);

    int getPriority() const;
    void setPriority(int value);

    bool getMovable() const;
    void setMovable(bool value);

    void addAttack(int dirId, int value);
    int getAttack(int dirId) const;
    void clearAttack();

    void setShield(int dirId, bool value);
    bool getShield(int dirId) const;
    void clearShield();

private:
    TokenCreature(const TokenCreature&) = default;
    int priority_;
    std::map<int, int> attack_;
    std::map<int, bool> shield_;
    int additionalAction_;
    int movable_;
};

#endif // TOKENCREATURE_H
