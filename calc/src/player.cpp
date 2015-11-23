#include "player.h"

string Player::getName(){
    return this->name;
}

Color Player::getColor(){
    return this->stack.getColor();
}

void Player::putTokenOnBoard(unsigned int tokenId){
    //this->board->
}

void Player::throwToken(unsigned int tokenId){
    this->stack.deleteToken(tokenId);
}

vector<int> Player::getTokensOnHandIds(){
    return this->stack.getCurrentTokensIds();
}