#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"
#include <vector>
#include <string>
#include <map>
#include "color.h"
#include "actiontype.h"

class Game {
public:
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
    Game();
    std::vector<Player> players;
    Board* board_;
    Color getNextColor();
    Game(const Game&) = delete;
	Game operator=(const Game&) = delete;
    std::map<Color, std::string> tokensFiles;

};


#endif
