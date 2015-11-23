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
    int getId();

private:
    Color color_;
    int id;
};

#endif // TOKEN_H
