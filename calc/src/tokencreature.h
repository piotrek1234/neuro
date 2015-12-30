#ifndef TOKENCREATURE_H
#define TOKENCREATURE_H

#include "tokenputable.h"
#include "utils.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <map>

class CALC_DLL()TokenCreature : public TokenPutable
{
public:
    TokenCreature() : priority_(0), additionalAction_(false), movable_(false) {}
    TokenCreature(Color color) : TokenCreature() { setColor(color); }
    virtual ~TokenCreature();
    virtual void accept(Visitor& v);
    virtual TokenPutable* clone() const;

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
    
    static Token* create(ptree Ptree, Color color);
    static std::string typeName;

private:
    //TokenCreature(const TokenCreature&) = default;
    std::map<int, int> attack_;
    std::map<int, bool> shield_;
    int priority_;
    bool additionalAction_;
    bool movable_;
};

#endif // TOKENCREATURE_H
