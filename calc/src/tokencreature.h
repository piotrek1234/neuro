#ifndef TOKENCREATURE_H
#define TOKENCREATURE_H

#include "tokenputable.h"
#include <map>

#ifdef CALC_EXPORTS
#define CALC_DLL(X) __declspec(dllexport)X
#else
#define CALC_DLL(X) X
#endif

class CALC_DLL()TokenCreature : public TokenPutable
{
public:
    TokenCreature();
    virtual ~TokenCreature();
    virtual void accept(Visitor& v);
    //virtual TokenPutable* clone() const;

    bool getAdditionalAction() const;
    void setAdditionalAction(bool value);

    int getPriority() const;
    void setPriority(int value);

    bool getMovable() const;
    void setMovable(bool value);

    void addAttack(int dirId, int value);
    int getAttack(int dirId) const;
    void clearAttack();

    void setShield(int dirId, bool value);
    virtual bool getShield(int dirId) const;
    void clearShield();

private:
    TokenCreature(const TokenCreature&) = default;
    int priority_;
    std::map<int, int> attack_;
    std::map<int, bool> shield_;
    bool additionalAction_;
    bool movable_;
};

#endif // TOKENCREATURE_H
