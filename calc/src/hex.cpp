#include "hex.h"

Hex::Hex(int q_, int r_, int s_) : q(q_), r(r_), s(s_){};

int Hex::getq()
{
    return q;
}

int Hex::getr() const
{
    return r;
}

int Hex::gets() const
{
    return s;
}

Hex Hex::hex_add(Hex a, Hex b);
{
    return Hex(a.q + b.q, a.r + b.r, a.s + b.s);
}

bool Hex::compare(const Hex a, const Hex b)
{
    if(a.q==b.q)
    {
        if(a.r==b.r)
        {
            return a.s>b.s;
        }
        return a.r>b.r;
    }
    return a.q>b.q;
}