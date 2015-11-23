#include "token.h"

Token::Token()
{

}

Token::~Token()
{

}
Color Token::getColor() const
{
    return color_;
}

void Token::setColor(const Color &value)
{
    color_ = value;
}

int Token::getId()
{
    return this->id;
}
