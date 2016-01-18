#ifndef VISITOR_H
#define VISITOR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif

#ifdef CALC_EXPORTS
#define CALC_DLL(X) __declspec(dllexport)X
#else
#define CALC_DLL(X) X
#endif

class TokenCreature;
class TokenModule;
class TokenHQ;

/**
 * @brief The Visitor class is an interface for abstract visitor
 */
class CALC_DLL()Visitor
{
public:
    Visitor();
    virtual ~Visitor();
    virtual void visit(TokenCreature*)=0;
    virtual void visit(TokenModule*)=0;
    virtual void visit(TokenHQ*)=0;
};

#endif // VISITOR_H
