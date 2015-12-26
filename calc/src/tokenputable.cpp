#include "tokenputable.h"

TokenPutable::~TokenPutable()
{

}
int TokenPutable::getLife() const
{
    return life_;
}

void TokenPutable::setLife(int value)
{
    life_ = value;
}

Hex TokenPutable::getPosition() const
{
    return position_;
}

void TokenPutable::setPosition(Hex pos)
{
    position_ = pos;
}

int TokenPutable::getAngle() const
{
    return angle_;
}

void TokenPutable::setAngle(int angle)
{
    angle_ = angle;
}




