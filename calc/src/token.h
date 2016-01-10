#ifndef TOKEN_H
#define TOKEN_H

#ifdef CALC_EXPORTS
#define CALC_DLL(X) __declspec(dllexport)X
#else
#define CALC_DLL(X) X
#endif

#include "color.h"
#include <string>

/**
 * @brief The Token class is an interface for tokens
 */
class CALC_DLL()Token
{
public:
    Token() : color_(Color::NONE), id_(-1) {}
    Token(Color color) : color_(color), id_(-1) {}
    virtual ~Token();
    virtual bool isPutable() const = 0;
    Color getColor() const;
    void setColor(const Color &value);
    int getId() const;
    void setId(int id);
    void setName(std::string name);
    std::string getName();
private:
    Color color_;
    int id_;
    std::string name_;
};

#endif // TOKEN_H
