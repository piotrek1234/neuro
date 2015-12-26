/**
 * \file player.hpp
 * \class decribing player
 */

#ifndef PLAYER_H
#define PLAYER_H


#include "stack.h"
#include <string>
//#include "board.h"
#include <vector>
#include "color.h"
#include "tokenfactory.h"

class Player {
public:
	Player(std::string name_);
    std::string getName();
    void setStack(Color color, std::string tokensConfigPath);
    Color getColor();
    //void putTokenOnBoard(unsigned int tokenId);
    //void throwToken(unsigned int tokenId);
    //vector<int> getTokensOnHandIds();
    
private:
    Stack stack;
    std::string name;
    //Board *board;
};


#endif