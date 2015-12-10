#include "battlehandler.h"

void BattleHandler::handleBattle()
{
    int maxPriority = -1;

    Board* tmpBoard = Game::getInstance().getBoard()->clone();  //tymczasowa kopia planszy

    CreatureFinder creatureFinder;
    //przejrzenie żetonów na planszy i wyłowienie wszystkich TokenCreature
    for(auto it = tmpBoard->getMapBegin(); it != tmpBoard->getMapEnd(); ++it)
    {
        it->second->accept(creatureFinder);
    }

    //dla każdego TokenCreature trzeba znaleźć działające na niego TokenModule
    for(auto it = creatureFinder.getBegin(); it != creatureFinder.getEnd(); ++it)
    {
        for(int i=0; i<6; ++i)
        {
            //todo
        }
    }

}
