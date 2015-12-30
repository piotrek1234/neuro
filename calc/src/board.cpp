#include "board.h"

Board::Board()
{

}

bool Board::addToken(Hex pos, TokenPutable *token, int angle)
{
    if(!pos.isValid())
        return false;
    if(board_.find(pos) == board_.end())
    {
        token->setPosition(pos);
        if(angle != -1) //jeśli angle jest nieustawiony, to zostawić domyślny
            token->setAngle(angle);
        board_.insert(std::pair<Hex, TokenPutable*>(pos, token));
        return true;
    }
    return false;
}

bool Board::moveToken(Hex src, Hex dst, int angle)
{
    auto srcField = board_.find(src);

    if(srcField == board_.end())    //jeśli pole źródłowe jest puste
        return false;
    //czy pola leżą na plaszy
    if(!src.isValid())
        return false;
    if(!dst.isValid())
        return false;

    if((board_.find(dst) == board_.end())||(dst == src))  //pole docelowe jest wolne lub robimy tylko obrót
    {
        srcField->second->setPosition(dst);

        if(angle != -1)
            srcField->second->setAngle(angle);

        if(dst != src)  //przesunięcie
        {
            addToken(dst, srcField->second);
            deleteToken(src, false);
        }
        return true;
    }
    return false;
}

bool Board::deleteToken(Hex pos, bool permanent)
{
    auto field = board_.find(pos);

    if(field == board_.end())    //jeśli pole źródłowe jest puste
        return false;

    if(permanent)   //przy przesuwaniu usunięcie musi być słabe
        delete field->second;

    board_.erase(field);
    return true;
}

TokenPutable *Board::getNeighbourToken(Hex hex, int dir)
{
    auto neighbor = board_.find(hex.getNeighbor(dir));
    if(neighbor != board_.end())
        return neighbor->second;
    return nullptr;
}

Board::~Board()
{
    for(auto it=board_.begin(); it!= board_.end(); ++it)
    {
        delete it->second;
    }
}

Board *Board::clone()
{
    Board* cloned = new Board;

    //dla każdego żetonu z oryginalnej planszy wstaw sklonowany w takie samo miejsce na nowej planszy
    for(auto it=board_.begin(); it!=board_.end(); ++it)
    {
        cloned->addToken(it->first, it->second->clone());
    }

    return cloned;
}

unordered_map<Hex, TokenPutable*>::iterator Board::getMapBegin()
{
    return board_.begin();
}

unordered_map<Hex, TokenPutable*>::iterator Board::getMapEnd()
{
    return board_.end();
}

bool Board::pushToken(Hex pusher, Hex pushed)
{
    if(board_.find(pusher) == board_.end()) //pusher nie istnieje
        return false;
    if(board_.find(pushed) == board_.end()) //pushed nie istnieje
        return false;
    if(pusher == pushed)    //pchnięcie samego siebie
        return false;

    Hex destination = pushed.getNeighbor(pushed - pusher);

    if(destination.isValid()) //pole jest na planszy
    {
        if(board_.find(destination) == board_.end())  //pole jest wolne
        {
            moveToken(pushed, destination);
            return true;
        }
    }
    return false;
}

TokenPutable *Board::getToken(Hex pos)
{
    auto a = pos;
    auto token = board_.find(a);
    if(token != board_.end())
        return token->second;
    return nullptr;
}

void Board::clear()
{
    board_.clear();   
}
