#ifndef TOKENACTION_H
#define TOKENACTION_H

#include "token.h"
#include "actiontype.h"

class CALC_DLL()TokenAction : public Token
{
public:
    TokenAction(ActionType actionType) : actionType_(actionType) {}
    virtual ~TokenAction();
    virtual bool isPutable() const { return false; }
    ActionType getType() const { return actionType_; }
private:
    ActionType actionType_;
};

#endif // TOKENACTION_H
