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
#include "utils.h"

class Player {
public:
	Player(std::string name_);
    std::string getName();
    void setStack(Color color, std::string tokensConfigPath);
    Color getColor();
    Token* getToken(unsigned int tokenId);
    bool throwToken(unsigned int tokenId);
    std::vector<int> getTokensOnHandIds();
    std::vector<int> getNextTokensOnHandIds();
    
private:
    Stack stack;
    std::string name;
    //Board *board;
};


#endif