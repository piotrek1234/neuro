#include "hex.h"

const std::vector<Hex> Hex::hexDirections_ = {Hex(0, -1), Hex(-1, 0), Hex(-1, 1), Hex(0, 1), Hex(1, 0), Hex(1, -1)};

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

Hex &Hex::operator=(const Hex &val)
{
    q_ = val.getQ();
    r_ = val.getR();
    s_ = val.getS();
    return *this;
}

bool Hex::operator<(const Hex &val) const
{
    if(q_ < val.getQ())
        return true;
    if(r_ < val.getR())
        return true;
    return false;
}

Hex Hex::direction(int dir_id)
{
    while(dir_id < 0)
        dir_id += 6;

    if(dir_id>5) dir_id %= 6;

    return hexDirections_[dir_id];
}

bool Hex::isValid() const
{
    /*if(std::abs(q_) < 3)
        if(std::abs(r_) < 3)
            return true;
    return false;*/
    if((std::abs(q_)+std::abs(r_)+std::abs(s_))/2 < 3)
        return true;
    return false;
}


int Hex::revDirection(const Hex& dir_hex)
{
    //ewentualnie rzucić wyjątek jeślidir_hex nie jest jednostkowy
    for(int i=0; i<6; ++i)
        if(Hex::direction(i) == dir_hex) return i;
    return -1;
}
