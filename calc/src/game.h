#ifndef GAME_H
#define GAME_H

#ifdef CALC_EXPORTS
/** Workaround for Windows DLL library exports */
#define CALC_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define CALC_DLL(X) X
#endif

#include "player.h"
//#include "board.h"
#include <vector>
#include <string>

class CALC_DLL( Game ) {
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