#ifndef BOARD_H
#define BOARD_H

#include "token.h"
#include "hex.h"
#include <vector>

class CALC_DLL( Board ) {
public:
    Board(int size);
    void addToken(Hex pos, Token* token);
    void moveToken(Hex src, Hex dst);
    void deleteToken(Hex pos);
    Hex getNeighbour(Hex hex, int direction);
    Token* getToken(Hex pos);
    Token* getNeighbourToken(Hex hex, int direction);
    
private:
    static const vector<Hex> hex_directions = {
        Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1),
        Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)
    };
    int size;
    std::map<Hex, Token*> board;
    
    
};

#endif