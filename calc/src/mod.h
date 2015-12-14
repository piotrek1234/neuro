#ifndef MOD_H
#define MOD_H

#include "tokencreature.h"
#include <vector>

class Mod : public Visitor
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
