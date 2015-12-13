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
    Board(int size);    //potrzebne? size jest stały
    bool addToken(Hex pos, TokenPutable* token);
    bool moveToken(Hex src, Hex dst);
    bool deleteToken(Hex pos);
    bool pushToken(Hex pusher, Hex pushed);
    Hex getNeighbour(Hex hex, int direction);
    TokenPutable* getToken(Hex pos);
    TokenPutable* getNeighbourToken(Hex hex, int dir);  //potrzebne?
    Board* clone(); //albo zamiast tego zrobić konstruktor kopiujący
    map<Hex, TokenPutable*>::iterator getMapBegin();
    map<Hex, TokenPutable*>::iterator getMapEnd();
private:
    int size_;  //do czego służy size_?
    map<Hex, TokenPutable*> board_;
};

#endif
