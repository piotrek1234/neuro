#ifndef GAME_H
#define GAME_H

#include "player.h"
//#include "board.h"
#include <vector>
#include <string>

class Game {
public:
    static Game& getInstance();
    void addPlayer(std::string name);
    void removePlayer(std::string name);
    void removeAllPlayers(std::string name);
    std::vector<std::string> getPlayersNames();
    
private:
    Game();
    std::vector<Player> players;
    
    Game(const Game&) = delete;
	Game operator=(const Game&) = delete;
};


#endif