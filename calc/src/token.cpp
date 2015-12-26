#include "token.h"

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
int Token::getId() const
{
    return id_;
}

void Token::setId(int id)
{
    id_ = id;
}



