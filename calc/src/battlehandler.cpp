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
        ModuleFinder moduleFinder;
        //dla każdego kierunku
        {
            //sąsiad->accept(moduleFinder);
        }
        //for(auto it = moduleFinder.getBegin(); it != moduleFinder.getEnd(); ++it)
        {
            //jeśli moduł wskazuje na żeton w środku:
            //(*it)->modify(żeton w środku);
        }
    }

}
