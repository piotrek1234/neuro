#include "battlehandler.h"

void BattleHandler::handleBattle()
{
    int lastPriority = 100;

    while(lastPriority)
    {
        int maxPriority = -1;
        Board* tmpBoard = Game::getInstance().getBoard()->clone();  //tymczasowa kopia planszy

        CreatureFinder creatureFinder;
        //przejrzenie żetonów na planszy i wyłowienie wszystkich TokenCreature i HQ
        for(auto it = tmpBoard->getMapBegin(); it != tmpBoard->getMapEnd(); ++it)
        {
            it->second->accept(creatureFinder);
        }

        ModuleApplier moduleApplier;
        //dla każdego TokenCreature trzeba znaleźć działające na niego TokenModule
        for(auto it = creatureFinder.getBegin(); it != creatureFinder.getEnd(); ++it)
        {
            moduleApplier.setTarget(*it);
            //znajdź którzy z sąsiadów są modułami i wskazują na token
            for(int i=0; i<6; ++i)
            {
                //jeśli sąsiedni TokenModule lub TokenHQ wskazują na token, to zastosuj mod
                TokenPutable* neighbor = tmpBoard->getNeighbourToken((*it)->getPosition(), i);
                if(neighbor != nullptr)
                    neighbor->accept(moduleApplier);
            }
        }

        vector<TokenCreature*> currentCreatures;
        // znalezienie maksymalnej wartości inicjatywy, ale mniejszej niż poprzednio grana.
        // (żetony na planszy nie zmieniły położenia) i wyłowienie tych TokenCreature
        for(auto it = creatureFinder.getBegin(); it != creatureFinder.getEnd(); ++it)
        {
            int tokenPriority = (*it)->getPriority();

            //jeśli token jeszcze nie brał udziału w bitwie
            if(tokenPriority<lastPriority)
            {
                if(tokenPriority > maxPriority)
                {
                    currentCreatures.clear();
                    maxPriority = tokenPriority;
                }
                if(tokenPriority == maxPriority)
                    currentCreatures.push_back(*it);
            }
            else if((tokenPriority == lastPriority)&&((*it)->getAdditionalAction()))
            {
                //brał udział w poprzedniej inicjatywie, ale ma dodatkową akcję
                currentCreatures.push_back(*it);
            }
        }

        //teraz w currentCreatures siedzą TokenCreature dla aktualnej inicjatywy,
        //żetony z currentCreatures atakują wrogich sąsiadów
        for(auto it = currentCreatures.begin(); it!=currentCreatures.end(); ++it)
        {
            //zaatakuj w każdym kierunku z odpowiednią siłą (0..n)
            for(int dir=0; dir<6; ++dir)
            {
                TokenPutable* neighbor = tmpBoard->\
                        getNeighbourToken(((TokenPutable*)(*it))->getPosition(),\
                                          dir+(*it)->getAngle());  //sąsiad
                if(neighbor != nullptr)
                    //jeśli sąsiad jest wrogiem i nie ma tarczy to go zaatakuj
                    if((*it)->getColor() != neighbor->getColor())
                        if(!neighbor->getShield(Hex::revDirection((*it)->getPosition()-neighbor->getPosition())))
                        {
                            //modyfikacja życia na tmpBoard i oryginalnym Board
                            neighbor->setLife(neighbor->getLife()-(*it)->getAttack(dir));
                            Game::getInstance().getBoard()->getToken(neighbor->getPosition())->\
                                    setLife(Game::getInstance().getBoard()->getToken(neighbor->getPosition())->\
                                            getLife()-(*it)->getAttack(dir));
                        }
            }
        }

        //jeśli trwa inicjatywa 0, to TokenHQ też atakują
        if(maxPriority < 1)
            for(auto it = creatureFinder.getHqBegin(); it != creatureFinder.getHqEnd(); ++it)
            {
                //zaatakuj w każdym kierunku z siłą 1
                for(int dir=0; dir<6; ++dir)
                {
                    TokenPutable* neighbor = Game::getInstance().getBoard()->\
                            getNeighbourToken(((TokenPutable*)(*it))->getPosition(), dir);  //sąsiad
                    if(neighbor != nullptr)
                        //jeśli sąsiad jest wrogiem i nie ma tarczy to go zaatakuj
                        if((*it)->getColor() != neighbor->getColor())
                            if(!neighbor->getShield(Hex::revDirection((*it)->getPosition()-neighbor->getPosition())))
                            {
                                //modyfikacja życia na tmpBoard i oryginalnym Board
                                neighbor->setLife(neighbor->getLife()-1);
                                Game::getInstance().getBoard()->getToken(neighbor->getPosition())->\
                                        setLife(Game::getInstance().getBoard()->getToken(neighbor->getPosition())->\
                                                getLife()-1);
                            }
                }
            }

        //obecna inicjatywa zakończyła się, sprawdzić czy któreś HQ nie zmarło
        for(auto it=creatureFinder.getHqBegin(); it!=creatureFinder.getHqEnd(); ++it)
        {
            if((*it)->getLife() < 1)
            {
                //+ powiadomić o porażce gracza
                //usunąć wszystkie żetony tego gracza
                //rozwiązane przez ustawienie życia żetonów na 0 (usuwanie jest zrobione dalej)
                for(auto i = Game::getInstance().getBoard()->getMapBegin(); \
                    i!= Game::getInstance().getBoard()->getMapEnd(); ++i)
                {
                    TokenPutable* token = i->second;
                    if((*it)->getColor() == token->getColor())
                        token->setLife(0);
                }
            }
        }

        //usunięcie zabitych żetonów z *oryginalnej* planszy
        for(auto it=tmpBoard->getMapBegin(); it!=tmpBoard->getMapEnd(); ++it)
        {
            if(it->second->getLife() < 1)
                Game::getInstance().getBoard()->deleteToken(it->first, true);
        }

        //jeśli skończyła się inicjatywa nr 0 to bitwa kończy się
        lastPriority = maxPriority;
        delete tmpBoard;
    }
    //bitwa zakończona
    //po bitwie warto sprwadzić czy został tylko 1 gracz, wtedy jest koniec gry
    //jeśli to była bitwa uruchomiona przez wyczerpanie stosu któregoś gracza,
    //to również następuje koniec gry, a wygrywa ten, czyjego HQ ma najwięcej życia
}

BattleHandler &BattleHandler::getInstance()
{
    static BattleHandler instance;
    return instance;
}
