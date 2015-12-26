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
		Player player(name);
        Color nextColor = getNextColor();
        if(tokensFiles.find(nextColor)!=tokensFiles.end())
        {
            player.setStack(nextColor, tokensFiles[nextColor]);
            players.push_back(player);
            return true;
        }
    }
    return false;
}

Color Game::getNextColor()
{
	switch(players.size())
	{
		case 0:
			return Color::BLUE;
		case 1:
			return Color::RED;
		case 2:
			return Color::YELLOW;
		case 3:
			return Color::GREEN;
		default:
			return Color::NONE;
	}
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

std::vector<std::string> Game::getPlayersNames()
{
    std::vector<std::string> names;
    for(auto i=players.begin(); i<players.end(); ++i)
    {
        names.push_back(i->getName());
    }
    return names;
}

void Game::addTokenConfigPath(Color color, string path)
{
    tokensFiles[color] = path;
}