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

class Game {
public:
    ~Game();
    static Game& getInstance();
    bool addPlayer(std::string name);
    void removeAllPlayers();
    std::vector<std::string> getPlayersNames();
    Board* getBoard();
    //TODO Magda
    std::vector<Player> getPlayers();
    void restartGame();
    bool addToken(int tokenId, Color color, Hex pos);
    bool throwToken(int tokenId, Color color);
    Player getNextPlayer();
    Player getCurrentPlayer();
    bool actionToken(int tokenId, Color color);
    bool killPlayer(Color color);
    void addTokenConfigPath(Color color, string path);
    
private:
    Game();
    std::vector<Player> players;
    Board* board_;
    Color getNextColor();
    Game(const Game&) = delete;
	Game operator=(const Game&) = delete;
    std::map<Color, std::string> tokensFiles;
    unsigned int currentPlayerNum;
    const unsigned int MaxPlayersNum;
    std::map<Color, int> playersMap;
    int getPlayerId(Color color);
    typedef boost::mpl::vector<TokenAction, TokenCreature, TokenModule, TokenHQ> tokensTypes;
    typedef boost::mpl::vector<ModAdditionalAction, ModAttack, ModLife, ModPriority> modsTypes;
    template<typename F> struct RegisterTypeInFactory
    {
        template<typename T> void operator()(T)
        {
            F::getInstance().registerFun(T::typeName, T::create);
        }
    };

};


#endif
