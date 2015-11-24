#ifndef HEX_H
#define HEX_H

#ifdef CALC_EXPORTS
/** Workaround for Windows DLL library exports */
#define CALC_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define CALC_DLL(X) X
#endif

class CALC_DLL( Hex ) {
public:
    Hex(int q_, int r_, int s_);
    int getq() const;
    int getr() const;
    int gets() const;
    Hex hex_add(Hex a, Hex b);
    bool compare(const Hex a, const Hex b);
    
private:
    const int q, r, s;
    
};


#endif