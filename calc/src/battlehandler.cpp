#include "battlehandler.h"

void BattleHandler::handleBattle()
{
    int lastPriority = 100;

    while(lastPriority)
    {
        int maxPriority = -1;
        Board* tmpBoard = Game::getInstance().getBoard()->clone();  //tymczasowa kopia planszy

        CreatureFinder creatureFinder;
        //przejrzenie żetonów na planszy i wyłowienie wszystkich TokenCreature
        for(auto it = tmpBoard->getMapBegin(); it != tmpBoard->getMapEnd(); ++it)
        {
            it->second->accept(creatureFinder);
        }

        ModuleFinder moduleFinder;
        //dla każdego TokenCreature trzeba znaleźć działające na niego TokenModule
        for(auto it = creatureFinder.getBegin(); it != creatureFinder.getEnd(); ++it)
        {
            moduleFinder.setTarget(*it);
            //znajdź którzy z sąsiadów są modułami i wskazują na token
            for(int i=0; i<6; ++i)
            {
                //jeśli sąsiedni TokenModule lub TokenHQ wskazują na token, to zastosuj mod
                Game::getInstance().getBoard()->getNeighbourToken((*it)->getPosition(), i)->accept(moduleFinder);
            }
        }

        vector<TokenCreature*> currentCreatures;
        // znalezienie maksymalnej wartości inicjatywy, ale mniejszej niż poprzednio grana.
        // (żetony na planszy nie zmieniły położenia) i wyłowienie tych TokenCreature
        for(auto it = creatureFinder.getBegin(); it != creatureFinder.getEnd(); ++it)
        {
            if(((*it)->getPriority() > maxPriority)&&((*it)->getPriority()<lastPriority))
            {
                currentCreatures.clear();
                currentCreatures.push_back(*it);
                maxPriority = (*it)->getPriority();
            }
        }

        //teraz w currentCreatures siedzą TokenCreature dla aktualnej inicjatywy,
        //żetony z currentCreatures atakują wrogich sąsiadów
        for(auto it = currentCreatures.begin(); it!=currentCreatures.end(); ++it)
        {
            //zaatakuj w każdym kierunku z odpowiednią siła (0..n)
            for(int dir=0; dir<6; ++dir)
            {
                TokenPutable* neighbor = Game::getInstance().getBoard()->\
                        getNeighbourToken(((TokenPutable*)(*it))->getPosition(), dir);  //sąsiad
                //jeśli sąsiad jest wrogiem to go zaatakuj
                if((*it)->getColor() != neighbor->getColor())
                    neighbor->setLife(neighbor->getLife()-(*it)->getAttack(dir));
            }
        }

        //obecna inicjatywa zakończyła się, sprawdzić czy któreś HQ nie zmarło
        for(auto it=creatureFinder.getHqBegin(); it!=creatureFinder.getHqEnd(); ++it)
        {
            if((*it)->getLife() < 1)
            {
                /// powiadomić o porażce gracza
                //usunąć wszystkie żetony tego gracza

            }
        }

        //usunięcie zabitych żetonów z *oryginalnej* planszy
        for(auto it=tmpBoard->getMapBegin(); it!=tmpBoard->getMapEnd(); ++it)
        {
            if(it->second->getLife() < 1)
                Game::getInstance().getBoard()->deleteToken(it->first);
        }

        //jeśli skończyła się inicjatywa nr 0 to bitwa kończy się
        lastPriority = maxPriority;
    }
    //tu można sprawdzić czy został tylko 1 żywy gracz
}
