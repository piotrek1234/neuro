/**
 * \file calcpy.cpp
 * \brief the Python interface for C++ calculation library
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//msvc disable warnings for Boost.Python
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4512)
 #pragma warning(disable:4003)
#endif


#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <string>
#include "game.h"
#include "color.h"
#include "player.h"
#include "board.h"
#include "hex.h"
#include <iostream>

using namespace boost::python;
using namespace std;

/**
 * @brief The CommandManagerPy class exports methods needed to perform game to Python library.
 */
class CommandManagerPy {
public:
	
	bool addPlayer(std::string name)
	{
        //std::cout<<"add player"<<std::endl;
		return Game::getInstance().addPlayer(name);
	}
    /**
     * @brief getPlayersNames
     * @return vector of strings containing all players' names
     */
	boost::python::list getPlayersNames()
	{
		std::vector<std::string> players = Game::getInstance().getPlayersNames();
		boost::python::list out;
		for(std::vector<std::string>::const_iterator i=players.begin(); i!=players.end(); ++i)
		{
			out.append(*i);
		}
		return out;
	}
	
	void removeAllPlayers()
	{
		Game::getInstance().removeAllPlayers();
	}
    /**
     * @brief getPlayers
     * @return python list of player dictionaries
     */
	boost::python::list getPlayers()
	{
		std::vector<Player*> players = Game::getInstance().getPlayers();
		boost::python::list out;
		for(std::vector<Player*>::const_iterator i=players.begin(); i!=players.end(); ++i)
		{
			boost::python::dict player = playerDict(*i);
			out.append(player);
		}
		return out;
	}
    /**
     * @brief getBoard
     * @return dictionary containing details on board's contents.
     * Key is python tuple containing position (as in Hex class).
     * Value contains token dictionary.
     */
	boost::python::dict getBoard()
	{
		boost::python::dict out;
		Board* board = Game::getInstance().getBoard();
		for(auto i=board->getMapBegin(); i!=board->getMapEnd(); ++i)
		{
			if(i->second!=nullptr)
			{
				Hex pos = i->first;
				//out[i->second->getId()] = boost::python::make_tuple(pos.getQ(), pos.getR(), pos.getS());
                //out[boost::python::make_tuple(pos.getQ(), pos.getR())] = tokenDict(i->second);
                        //boost::python::make_tuple(i->second->getId(), i->second->getColor());

                out[boost::python::make_tuple(pos.getQ(), pos.getR())] = tokenDict(i->second);
			}
		}
		return out;
	}
    /**
     * @brief restartGame
     * Deletes all players and reverts game state to initial.
     */
	void restartGame()
	{
		Game::getInstance().restartGame();
	}
	
    /**
     * @brief addToken
     * Moves token from player's hand onto board.
     * @param tokenId id of player's token
     * @param color color of player
     * @param q first position of token
     * @param r second position of token
     * @param angle angle of token
     * @return true if token was added successfully, false otherwise
     */
    bool addToken(int tokenId, Color color, int q, int r, int angle)
	{
		return Game::getInstance().addToken(tokenId, color, Hex(q, r), angle);
	}
    /**
     * @brief throwToken destroys token from player's hand
     * @param tokenId id of player's token
     * @param color color of player
     * @return true if token was successfully destroyed, false otherwise
     */
    bool throwToken(int tokenId, Color color)
	{
		return Game::getInstance().throwToken(tokenId, color);	
	}
    /**
     * @brief getNextPlayer end current turn
     * @return python dictionary with next player's details
     */
	boost::python::dict getNextPlayer()
	{
		Player* p=Game::getInstance().getNextPlayer();
		return playerDict(p);
	}
    /**
     * @brief getCurrentPlayer
     * @return python dictionary with current player's details
     */
	boost::python::dict getCurrentPlayer()
	{
		Player* p=Game::getInstance().getCurrentPlayer();
		return playerDict(p);
	}
    /**
     * @brief killPlayer removes player from players' list
     * @param color color of player
     * @return true if removal was successfull, false otherwise
     */
    bool killPlayer(Color color)
	{
		return Game::getInstance().killPlayer(color);
	}
    /**
     * @brief addTokenConfigPath specifies tokens' configuration file for given color
     * @param color color of tokens
     * @param path path to xml
     */
    void addTokenConfigPath(Color color, std::string path)
	{
		Game::getInstance().addTokenConfigPath(color, path);
	}
    /**
     * @brief performBattle performs battle
     */
    void performBattle()
    {
        Game::getInstance().performBattle();
    }
    /**
     * @brief actionTokenBattle performs battle caused by action token (and destroys token)
     * @param tokenId id of action token
     * @param color color of player
     * @return true if battle was performed, false otherwise
     */
	bool actionTokenBattle(int tokenId, Color color)
	{
		return Game::getInstance().actionTokenBattle(tokenId, color);
	}
    /**
     * @brief actionTokenMove moves token caused by action token (and destroys action token)
     * @param tokenId id of action token
     * @param color color of player
     * @param fromQ first coordinate of source position
     * @param fromR second coordinate of source position
     * @param toQ first coordinate of destination position
     * @param toR second coordinate of destination position
     * @return true if token was successfully moved, false otherwise
     */
    bool actionTokenMove(int tokenId, Color color, int fromQ, int fromR, int toQ, int toR)
	{
		return Game::getInstance().actionTokenMove(tokenId, color, Hex(fromQ, fromR), Hex(toQ, toR));
	}
    /**
     * @brief actionTokenPush pushes hostile token (and destroys action token)
     * @param tokenId id of action token
     * @param color color of player
     * @param fromQ first coordinate of pusher's position
     * @param fromR second coordinate of pusher's position
     * @param toQ first coordinate of enemy's position
     * @param toR second coordinate of enemy's position
     * @return true if token was successfully pushed, false otherwise
     */
    bool actionTokenPush(int tokenId, Color color, int fromQ, int fromR, int toQ, int toR)
	{
		return Game::getInstance().actionTokenPush(tokenId, color, Hex(fromQ, fromR), Hex(toQ, toR));
	}
    /**
     * @brief getTokenHand
     * @param tokenId id of token on hand
     * @param color color of player
     * @return python dictionary containing details of given token from hand
     */
    boost::python::dict getTokenHand(int tokenId, Color color)
    {
        Token* token = Game::getInstance().getTokenHand(tokenId, color);
        return tokenDict(token);
    }
    /**
     * @brief getTokenBoard
     * @param q first coordinate on board
     * @param r second coordinate on board
     * @return python dictionary containing details of given token from board
     */
    boost::python::dict getTokenBoard(int q, int r)
    {
        Token* token = Game::getInstance().getTokenBoard(Hex(q, r));
        return tokenDict(token);
    }
    /**
     * @brief getMoves
     * @param q first coordinate on board
     * @param r second coordinate on board
     * @return python list of possible move destinations for given token
     */
    boost::python::list getMoves(int q, int r)
    {
        boost::python::list moves;
        for(Hex hex : Game::getInstance().getMoves(Hex(q, r)))
        {
            boost::python::dict move;
            move["q"] = hex.getQ();
            move["r"] = hex.getR();
            moves.append(move);
        }
        return moves;
    }
    /**
     * @brief getPushes
     * @param q first coordinate on board
     * @param r second coordinate on board
     * @return python list of possible pushes destinations for given token
     */
    boost::python::list getPushes(int q, int r)
    {
        boost::python::list pushes;
        for(Hex hex : Game::getInstance().getPushes(Hex(q, r)))
        {
            boost::python::dict push;
            push["q"] = hex.getQ();
            push["r"] = hex.getR();
            pushes.append(push);
        }
        return pushes;
    }
	
private:
	
	boost::python::list listOfInt(std::vector<int> v)
	{
		boost::python::list out;
		for(std::vector<int>::const_iterator i=v.begin(); i!=v.end(); ++i)
		{
			out.append(*i);
		}
		return out;
	}	
    /**
     * @brief playerDict contains details on given player as dictionary.
     * name (string), color(Color), tokens(list of int), stack_size(int)
     * @param p pointer to Player
     * @return python dictionary
     */
	boost::python::dict playerDict(Player* p)
	{
		boost::python::dict player;
		if(p!=nullptr)
		{
			player["name"] = p->getName();
			player["color"] = p->getColor();
			player["tokens"] = listOfInt(p->getTokensOnHandIds());
			player["stack_size"] = p->stackSize();
		}
		return player;
	}
    /**
     * @brief tokenDict contains details on given token as dictionary.
     * id(int), color(Color), name(string), type(string) - can be "putable" or "action".
     * If token is putable, it contains also: life(int), angle(int). If it is action, it
     * contains type(string), which can be "battle", "move" or "push".
     * @param t pointer to Token
     * @return python dicitionary
     */
    boost::python::dict tokenDict(Token* t)
    {
        boost::python::dict token;
        if(t!=nullptr)
        {
            token["id"]=t->getId();
            token["color"]=t->getColor();
            token["name"]=t->getName();
            if(TokenPutable* tp = dynamic_cast<TokenPutable*>(t))
            {
                token["life"]=tp->getLife();
                token["angle"]=tp->getAngle();
                token["type"]="putable";
            }
            else if(TokenAction* ta = dynamic_cast<TokenAction*>(t))
            {
                token["type"]="action";
                if(ta->getType() == ActionType::BATTLE)
                    token["action"]="battle";
                else if(ta->getType() == ActionType::MOVE)
                    token["action"]="move";
                else if(ta->getType() == ActionType::PUSH)
                    token["action"]="push";
            }
        }
        return token;
    }
};

/**
 * Python wrapper using Boost.Python
 */
BOOST_PYTHON_MODULE( calc )
{		
	class_<std::vector<std::string> >("vectorOfStrings")
		.def(vector_indexing_suite<std::vector<std::string> >() )
		;

    class_<CommandManagerPy>("CommandManager")
		.def( "addPlayer", &CommandManagerPy::addPlayer )
		.def( "getPlayersNames", &CommandManagerPy::getPlayersNames )
		.def( "removeAllPlayers", &CommandManagerPy::removeAllPlayers)
		.def( "getPlayers", &CommandManagerPy::getPlayers)
		.def( "getBoard", &CommandManagerPy::getBoard)
		.def( "restartGame", &CommandManagerPy::restartGame)
		.def( "addToken", &CommandManagerPy::addToken)
        .def( "throwToken", &CommandManagerPy::throwToken)
		.def( "getNextPlayer", &CommandManagerPy::getNextPlayer)
		.def( "getCurrentPlayer", &CommandManagerPy::getCurrentPlayer)
		.def( "killPlayer", &CommandManagerPy::killPlayer)
		.def( "addTokenConfigPath", &CommandManagerPy::addTokenConfigPath)
		.def( "actionTokenBattle", &CommandManagerPy::actionTokenBattle)
		.def( "actionTokenMove", &CommandManagerPy::actionTokenMove)
		.def( "actionTokenPush", &CommandManagerPy::actionTokenPush)
        .def( "getTokenHand", &CommandManagerPy::getTokenHand)
        .def( "getTokenBoard", &CommandManagerPy::getTokenBoard)
        .def( "performBattle", &CommandManagerPy::performBattle)
        .def( "getMoves", &CommandManagerPy::getMoves)
        .def( "getPushes", &CommandManagerPy::getPushes)
		;
		
	boost::python::enum_<Color>("Color")
		.value("RED", Color::RED)
		.value("BLUE", Color::BLUE)
		.value("YELLOW", Color::YELLOW)
		.value("GREEN", Color::GREEN)
		.value("NONE", Color::NONE)
		.export_values()
		;
}
