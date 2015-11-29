#ifndef TOKENHQ_H
#define TOKENHQ_H

#include "tokenputable.h"

class TokenHQ: public TokenPutable
{
public:
    TokenHQ();
    ~TokenHQ();
    virtual void accept(Visitor& v);
    int getPriority() const;
    void setPriority(int priority);

    int getAdditionalAction() const;
    void setAdditionalAction(int additionalAction);

private:
    int priority_;
    //std::vector<kierunek> attack; //zawsze po jednym ataku w każdym kierunku
    int additionalAction_;
};

#endif // TOKENHQ_H
