#ifndef BOARD_H
#define BOARD_H

#include "tokenputable.h"
#include "hex.h"
#include <map>

using namespace std;

class CALC_DLL()Board {
public:
    Board();
    ~Board();
    bool addToken(Hex pos, TokenPutable* token);
    bool moveToken(Hex src, Hex dst);
    bool deleteToken(Hex pos, bool permanent = true);
    bool pushToken(Hex pusher, Hex pushed);
    TokenPutable* getToken(Hex pos);
    TokenPutable* getNeighbourToken(Hex hex, int dir);
    Board* clone();
    map<Hex, TokenPutable*>::iterator getMapBegin();
    map<Hex, TokenPutable*>::iterator getMapEnd();
    void clear();
private:
    map<Hex, TokenPutable*> board_;
};

#endif
