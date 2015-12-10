#include "game.h"

Game::Game()
{
    board_ = new Board;
}

Game::~Game()
{
    delete board_;
}

Game& Game::getInstance() {
	static Game instance;
	return instance;
}



Board *Game::getBoard()
{
    return board_;
}

bool Game::addPlayer(std::string name)
{
    if (players.size()<=4)
    {
        players.push_back(Player(name));
        return true;
    }
    return false;
}

void Game::removePlayer(std::string name)
{
    for(auto i=players.begin(); i<players.end(); ++i)
    {
        if(i->getName() == name){
            players.erase(i);
            return;
        }
    }
}

void Game::removeAllPlayers(std::string name)
{
    players.clear();
}

std::vector<std::string> Game::getPlayersNames(){
    std::vector<std::string> names;
    for(auto i=players.begin(); i<players.end(); ++i)
    {
        names.push_back(i->getName());
    }
    return names;
}
