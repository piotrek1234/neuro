#include "player.h"

Player::Player(std::string name_) : name(name_)
{
    
}

Player::Player(std::string name_, Color color_) : name(name_)
{
    getStack(color_);
}

std::string Player::getName()
{
    return this->name;
}

Color Player::getColor(){
    return this->stack.color;
}

void Player::getStack(Color color)
{
    if(color!=Color::NONE)
    {
        stack.readTokens(color);
    }
}

/*
void Player::putTokenOnBoard(unsigned int tokenId){
    //this->board->
}

void Player::throwToken(unsigned int tokenId){
    //this->stack.deleteToken(tokenId);
}

vector<int> Player::getTokensOnHandIds(){
    return this->stack.getCurrentTokensIds();
}*/