/**
 * \file player.hpp
 * \class decribing palyer
 */

#ifndef PLAYER_H
#define PLAYER_H

#ifdef CALC_EXPORTS
/** Workaround for Windows DLL library exports */
#define CALC_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define CALC_DLL(X) X
#endif

#include "stack.h"
#include "board.h"
#include <vector>

class CALC_DLL( Player ) {
public:
	Player(string name_, Stack &stack_, Board* board_) : name(name_), stack(stack_), board(board_);
    string getName();
    Color getColor();
    void putTokenOnBoard(unsigned int tokenId);
    void throwToken(unsigned int tokenId);
    vector<int> getTokensOnHandIds();
    
private:
    Stack stack;
    String name;
    Board *board;
};


#endif