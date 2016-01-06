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

void Token::setName(std::string name)
{
    name_ = name;
}


std::string Token::getName()
{
    return name_;
}
