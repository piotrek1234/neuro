#ifndef BOARD_H
#define BOARD_H

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif

#include "tokenputable.h"
#include "hex.h"
#include <unordered_map>

using namespace std;
/**
 * @brief The Board class contains board and its tokens
 */
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
