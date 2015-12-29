#ifndef TOKEN_H
#define TOKEN_H

#ifdef CALC_EXPORTS
#define CALC_DLL(X) __declspec(dllexport)X
#else
#define CALC_DLL(X) X
#endif

#include "color.h"

class CALC_DLL()Token
{
public:
    Token() : color_(Color::NONE), id_(-1) {}
    virtual ~Token();
    virtual bool isPutable() const = 0;
    Color getColor() const;
    void setColor(const Color &value);
    int getId() const;
    void setId(int id);

private:
    Color color_;
    int id_;
};

#endif // TOKEN_H
