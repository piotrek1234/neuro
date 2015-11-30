#ifndef TOKEN_H
#define TOKEN_H

#include "color.h"

class Token
{
public:
    Token();
    virtual ~Token();
    virtual bool isPutable() const = 0;
    Color getColor() const;
    void setColor(const Color &value);

private:
    Color color_;
};

#endif // TOKEN_H
