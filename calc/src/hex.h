/*
 * http://www.redblobgames.com/grids/hexagons/implementation.html
 */
#ifndef HEX_H
#define HEX_H

#ifdef CALC_EXPORTS
#define CALC_DLL(X) __declspec(dllexport)X
#else
#define CALC_DLL(X) X
#endif

#include <vector>

class CALC_DLL(Hex)
{
public:
    Hex(int q, int r) : q_(q), r_(r), s_(-q_-r_){}
    Hex() : q_(5), r_(5), s_(-10) {}
    ~Hex();
    int getQ() const { return q_; }
    int getR() const { return r_; }
    int getS() const { return s_; }
    Hex operator+(const Hex& val) const;
    Hex operator-(const Hex& val) const;
    bool operator==(const Hex& val) const;
    bool operator!=(const Hex& val) const { return !operator==(val); }
    Hex& operator=(const Hex& val);
    bool operator<(const Hex& val) const;   //konieczne dla std::map

    static Hex direction(int dir_id);
    Hex getNeighbor(int dir_id) const { return *this + direction(dir_id); }
    Hex getNeighbor(const Hex& dir) const { return *this + dir; }
    bool isValid() const;

private:
    int q_, r_, s_;
    static const std::vector<Hex> hexDirections_;
};

#endif // HEX_H
