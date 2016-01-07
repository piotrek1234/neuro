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
    stack.getNextTokensIds();
}

Token* Player::getToken(unsigned int tokenId, bool info_only){
    return stack.getToken(tokenId, info_only);
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
