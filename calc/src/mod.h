#ifndef MOD_H
#define MOD_H

#ifdef CALC_EXPORTS
#define CALC_DLL(X) __declspec(dllexport)X
#else
#define CALC_DLL(X) X
#endif

#include "visitor.h"
#include "tokencreature.h"

class TokenCreature;
class TokenModule;

#include <vector>

class CALC_DLL()Mod
{
public:
    Mod(std::vector<int> &directions) : directions_(directions) {}
    virtual ~Mod() = 0;
    Mod(const Mod& mod) = default;
    virtual void modify(TokenCreature*)=0;
    std::vector<int>::iterator getDirectionBegin();
    std::vector<int>::iterator getDirectionEnd();
protected:
    std::vector<int> directions_;
};

#endif // MOD_H
