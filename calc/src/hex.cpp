#include "hex.h"
#include <cmath>

const std::vector<Hex> Hex::hexDirections_ = {Hex(1, 0), Hex(1, -1), Hex(0, -1), Hex(-1, 0), Hex(-1, 1), Hex(0, 1)};

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

bool Hex::operator<(const Hex &val) const
{
    if(q_ < val.getQ())
        return true;
    if(r_ < val.getR())
        return true;
    return false;
}

bool Hex::isValid() const
{
    if(std::abs(q_) < 3)
        if(std::abs(r_) < 3)
            return true;
    return false;
}

/*Hex hex_direction(int direction)
{
    return hexDirections_[direction];
}*/

