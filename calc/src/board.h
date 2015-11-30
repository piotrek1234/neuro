#ifndef BOARD_H
#define BOARD_H

#include "token.h"
#include "hex.h"
#include <vector>

class Board {
public:
    Board(int size);
    void addToken(Hex pos, Token* token);
    void moveToken(Hex src, Hex dst);
    void deleteToken(Hex pos);
    Token* getNeighbour(Hex hex, int direction);
    Token* getToken(Hex pos);
    Token* getNeighbourToken(Hex hex, int direction);
    
private:
    int size;
    map<Hex, Token*, > board;
    
    
};

#endif