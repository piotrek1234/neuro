#include "hex.h"
#include <math.h>

static const std::vector<Hex> hex_directions_ = {Hex(1, 0), Hex(1, -1), Hex(0, -1), Hex(-1, 0), Hex(-1, 1), Hex(0, 1)};

Hex::~Hex()
{

}

Hex Hex::operator+(const Hex& val) const
{
    return Hex(q_+val.getQ(), r_+val.getR());
}

Hex Hex::operator-(const Hex& val) const
{
    return Hex(q_-val.getQ(), r_-val.getR());
}

bool Hex::operator==(const Hex& val) const
{
    if(q_ == val.getQ())
        if(r_ == val.getR())
            return true;
    return false;
}

bool Hex::isValid() const
{
    if(abs(q_) < 3)
        if(abs(r_) < 3)
            return true;
    return false;
}

Hex hex_direction(int direction)
{
    return hex_directions_[direction];
}

