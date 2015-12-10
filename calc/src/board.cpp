#include "board.h"

Board::Board()
{

}

TokenPutable *Board::getNeighbourToken(Hex hex, int dir)
{
    return board.find(hex.getNeighbor(dir))->second;
}

Board::~Board()
{

}

Board *Board::clone()
{
    Board* cloned = new Board;
    //tutaj głeboka kopia
    return cloned;
}

map<Hex, TokenPutable*>::iterator Board::getMapBegin()
{
    return board.begin();
}

map<Hex, TokenPutable*>::iterator Board::getMapEnd()
{
    return board.end();
}

#include "board.h"
