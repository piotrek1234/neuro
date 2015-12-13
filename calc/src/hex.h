/*
 * http://www.redblobgames.com/grids/hexagons/implementation.html
 */
#ifndef HEX_H
#define HEX_H

#include <vector>

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
    bool operator<(const Hex& val) const;   //konieczne dla std::map

    static Hex direction(int dir_id) { return hexDirections_[dir_id % 6]; }
    Hex getNeighbor(int dir_id) const { return *this + hexDirections_[dir_id]; }
    Hex getNeighbor(const Hex& dir) const { return *this + dir; }
    bool isValid() const;

private:
    const int q_, r_, s_;
    static const std::vector<Hex> hexDirections_;
};

#endif // HEX_H
