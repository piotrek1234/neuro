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

void TokenPutable::setPosition(Hex pos)
{
    position_ = pos;
}




