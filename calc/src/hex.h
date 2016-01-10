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
#include <cmath>
#include <ostream>

/**
 * @brief The Hex class is a pair of numbers used to define position of token on board
 */
class CALC_DLL()Hex
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
    static int revDirection(const Hex& dir_hex);
    Hex getNeighbor(int dir_id) const { return *this + direction(dir_id); }
    Hex getNeighbor(const Hex& dir) const { return *this + dir; }
    bool isValid() const;

private:
    int q_, r_, s_;
    static const std::vector<Hex> hexDirections_;
};

namespace std {
    template <>
    /**
     * @brief The hash<Hex> struct is used to calculate hash for Hex objects (used in unordered_map)
     */
    struct hash<Hex> {
        size_t operator()(const Hex& h) const {
            hash<int> int_hash;
            size_t hq = int_hash(h.getQ());
            size_t hr = int_hash(h.getR());
            return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
        }
    };
}

#endif // HEX_H
