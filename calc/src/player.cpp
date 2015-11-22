#include "player.h"

string Player::getName(){
    return this->name;
}

Color Player::getColor(){
    return this->stack.getColor();
}