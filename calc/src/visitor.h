#ifndef VISITOR_H
#define VISITOR_H
/*
#include "tokencreature.h"
#include "tokenmodule.h"
*/
class TokenCreature;
class TokenModule;

class Visitor
{
public:
    Visitor();
    virtual ~Visitor();
    virtual void visit(TokenCreature*)=0;
    virtual void visit(TokenModule*)=0;
};

#endif // VISITOR_H
