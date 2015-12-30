#ifndef BOARD_H
#define BOARD_H

#include "tokenputable.h"
#include "hex.h"
#include <unordered_map>

using namespace std;

class CALC_DLL()Board {
public:
    Board();
    ~Board();
    bool addToken(Hex pos, TokenPutable* token, int angle=-1);
    bool moveToken(Hex src, Hex dst, int angle=-1);
    bool deleteToken(Hex pos, bool permanent = true);
    bool pushToken(Hex pusher, Hex pushed);
    TokenPutable* getToken(Hex pos);
    TokenPutable* getNeighbourToken(Hex hex, int dir);
    Board* clone();
    unordered_map<Hex, TokenPutable*>::iterator getMapBegin();
    unordered_map<Hex, TokenPutable*>::iterator getMapEnd();
    void clear();
private:
    unordered_map<Hex, TokenPutable*, hash<Hex> > board_;
};

#endif
