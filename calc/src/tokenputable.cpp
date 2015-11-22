#include "tokenputable.h"

TokenPutable::TokenPutable()
{

}

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
int TokenPutable::getMovable() const
{
    return movable_;
}

void TokenPutable::setMovable(int value)
{
    movable_ = value;
}
bool TokenPutable::getActive() const
{
    return active_;
}

void TokenPutable::setActive(bool value)
{
    active_ = value;
}




