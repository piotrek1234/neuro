#ifndef MODULEAPPLIER_H
#define MODULEAPPLIER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif

#include <vector>
#include "tokenmodule.h"
#include "tokencreature.h"
#include "tokenhq.h"
#include "tokenmodhq.h"

using namespace std;

/**
 * @brief The ModuleApplier class is used to apply mod from token mods and hqs to given token creature
 */
class CALC_DLL()ModuleApplier : public Visitor
{
public:
    ModuleApplier() {}
    virtual ~ModuleApplier(){}
    void setTarget(TokenCreature* tc) { tc_ = tc; }
    virtual void visit(TokenCreature*) {}
    virtual void visit(TokenHQ* th);
    virtual void visit(TokenModule* tm);
private:
    TokenCreature* tc_;
};

#endif // MODULEAPPLIER_H
