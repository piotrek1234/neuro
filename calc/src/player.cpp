#include "player.h"

Player::Player(std::string name_) : name(name_)
{
    
}

std::string Player::getName()
{
    return this->name;
}

Color Player::getColor(){
    return this->stack.getColor();
}

void Player::setStack(Color color, std::string tokensConfigPath)
{
    if(color!=Color::NONE)
    {
        stack.readTokens(color, tokensConfigPath);
    }
}

Token* Player::getToken(unsigned int tokenId){
    return stack.getToken(tokenId);
}

bool Player::throwToken(unsigned int tokenId){
    return this->stack.deleteToken(tokenId);
}

std::vector<int> Player::getTokensOnHandIds(){
    return this->stack.getCurrentTokensIds();
}

std::vector<int> Player::getNextTokensOnHandIds(){
    return this->stack.getNextTokensIds();
}