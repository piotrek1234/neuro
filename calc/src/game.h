#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"
#include <vector>
#include <string>
#include <map>
#include "color.h"
#include "actiontype.h"
#include "tokenfactory.h"
#include <boost/mpl/vector.hpp>
#include "tokenaction.h"
#include "tokencreature.h"
#include "tokenhq.h"
#include "tokenmodule.h"
#include <boost/mpl/for_each.hpp>
#include "modadditionalaction.h"
#include "modlife.h"
#include "modpriority.h"
#include "modattack.h"
#include "modfactory.h"
#include "boost/variant.hpp"
#include <iostream>
#include "battlehandler.h"

class Game {
public:
    ~Game();
    typedef boost::variant<std::pair<Hex, Hex>, bool> ActionArgs;
    static Game& getInstance();
    bool addPlayer(std::string name);
    void removeAllPlayers();
    std::vector<std::string> getPlayersNames();
    Board* getBoard();
    std::vector<Player*> getPlayers();
    void restartGame();
    bool addToken(int tokenId, Color color, Hex pos, int angle);
    bool throwToken(int tokenId, Color color);
    Player* getNextPlayer();
    Player* getCurrentPlayer();
    bool actionToken(int tokenId, Color color, ActionArgs args);
    bool killPlayer(Color color);
    void addTokenConfigPath(Color color, string path);
    
private:
    Game();
    std::vector<Player*> players;
    Board* board_;
    Color getNextColor();
    Game(const Game&) = delete;
	Game operator=(const Game&) = delete;
    std::map<Color, std::string> tokensFiles;
    unsigned int currentPlayerNum;
    const unsigned int MaxPlayersNum;
    std::map<Color, int> playersMap;
    int getPlayerId(Color color);
    typedef boost::mpl::vector<TokenAction, TokenCreature> tokensTypes;
    typedef boost::mpl::vector<ModAdditionalAction, ModAttack, ModLife, ModPriority> modsTypes;
    template<typename F> struct RegisterTypeInFactory
    {
        template<typename T> void operator()(T)
        {
            std::cout<<"register fig"<<std::endl;
            F::getInstance().registerFun(T::typeName(), T::create);
            std::cout<<"register fig ended"<<std::endl;
        }
    };

};


#endif
