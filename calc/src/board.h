#ifndef BOARD_H
#define BOARD_H

#include "tokenputable.h"
#include "hex.h"
#include <map>

using namespace std;

class Board {
public:
    Board();
    ~Board();
    Board(int size);
    void addToken(Hex pos, TokenPutable* token);
    void moveToken(Hex src, Hex dst);
    void deleteToken(Hex pos);
    Hex getNeighbour(Hex hex, int direction);
    TokenPutable* getToken(Hex pos);
    TokenPutable* getNeighbourToken(Hex hex, int dir);
    Board* clone();
    map<Hex, TokenPutable*>::iterator getMapBegin();
    map<Hex, TokenPutable*>::iterator getMapEnd();
private:
    int size;
    map<Hex, TokenPutable*> board;
};

#endif
