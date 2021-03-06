#ifndef TOKENPUTABLE_H
#define TOKENPUTABLE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif

#include "visitor.h"
#include "token.h"
#include "hex.h"

/**
 * @brief The TokenPutable class is an interface for tokens which can be put on board
 */
class CALC_DLL()TokenPutable : public Token
{
public:
    TokenPutable() : life_(1), angle_(0), position_(Hex(5,5)) {}
    TokenPutable(int life) : life_(life), angle_(0), position_(Hex(5,5)) {}
    virtual ~TokenPutable();
    virtual bool isPutable() const { return true; }
    virtual void accept(Visitor& v) = 0;
    virtual TokenPutable* clone() const = 0;

    int getLife() const;
    void setLife(int value);
    Hex getPosition() const;
    void setPosition(Hex pos);
    int getAngle() const;
    void setAngle(int angle);
    virtual bool getShield(int dirId) const = 0;

private:
    int life_;
    int angle_;
    Hex position_;
};

#endif // TOKENPUTABLE_H
