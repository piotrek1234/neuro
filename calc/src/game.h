#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"
#include <vector>
#include <string>
#include <map>
#include "color.h"

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
    //TODO Magda
    //getPlayers
    //getGameState
    //addToken
    //throwToken
    //getNextPlayer
    //ActionTokens
    //set path for tokens config
    
private:
    std::vector<Player> players;
    Board* board_;  ///pomyśleć nad zmianą na shared_ptr
    Color getNextColor();
    Game(const Game&) = delete;
	Game operator=(const Game&) = delete;
    map<Color, std::string> tokensFiles;

};


#endif
