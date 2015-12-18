#ifndef VISITOR_H
#define VISITOR_H

/*#include "tokencreature.h"
#include "tokenmodule.h"
#include "tokenhq.h"*/

#ifdef CALC_EXPORTS
#define CALC_DLL(X) __declspec(dllexport)X
#else
#define CALC_DLL(X) X
#endif

class TokenCreature;
class TokenModule;
class TokenHQ;

class Visitor
{
public:
    Visitor();
    virtual ~Visitor();
    virtual void visit(TokenCreature*)=0;
    virtual void visit(TokenModule*)=0;
    virtual void visit(TokenHQ*)=0;
};

#endif // VISITOR_H
