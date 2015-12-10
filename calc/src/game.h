#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"
#include <vector>
#include <string>

class Game {
public:
    Game();
    ~Game();
    static Game& getInstance();
    bool addPlayer(std::string name);
    void removePlayer(std::string name);
    void removeAllPlayers(std::string name);
    std::vector<std::string> getPlayersNames();
    Board* getBoard();
    
private:
    std::vector<Player> players;
    Board* board_;  ///pomyśleć nad zmianą na shared_ptr
    
    Game(const Game&) = delete;
	Game operator=(const Game&) = delete;

};


#endif
