/*
 * http://www.redblobgames.com/grids/hexagons/implementation.html
 */
#ifndef HEX_H
#define HEX_H

#include <vector>

///todo: podorzucać wyjątki

class Hex
{
public:
    Hex(int q, int r) : q_(q), r_(r), s_(-q_-r_){}
    ~Hex();
    int getQ() const { return q_; }
    int getR() const { return r_; }
    int getS() const { return s_; }
    Hex operator+(const Hex& val) const;
    Hex operator-(const Hex& val) const;
    bool operator==(const Hex& val) const;
    bool operator!=(const Hex& val) const { return !operator==(val); }

    static Hex direction(int dir_id) { return hex_directions_[dir_id % 6]; }
    Hex getNeighbor(int dir_id) const { return *this + hex_directions_[dir_id]; }
    bool isValid() const;

private:
    const int q_, r_, s_;
    static const std::vector<Hex> hex_directions_;
};

#endif // HEX_H
