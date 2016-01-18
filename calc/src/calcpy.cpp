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

/** Python intreface to CommandManager
 */
class CommandManagerPy {
public:
	
	bool addPlayer(std::string name)
	{
		std::cout<<"add player"<<std::endl;
		return Game::getInstance().addPlayer(name);
	}
	
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
	
	void restartGame()
	{
		Game::getInstance().restartGame();
	}
	
	
    bool addToken(int tokenId, Color color, int q, int r, int angle)
	{
		return Game::getInstance().addToken(tokenId, color, Hex(q, r), angle);
	}
	
    bool throwToken(int tokenId, Color color)
	{
		return Game::getInstance().throwToken(tokenId, color);	
	}
	
	boost::python::dict getNextPlayer()
	{
		Player* p=Game::getInstance().getNextPlayer();
		return playerDict(p);
	}
	
	boost::python::dict getCurrentPlayer()
	{
		Player* p=Game::getInstance().getCurrentPlayer();
		return playerDict(p);
	}
    
    bool killPlayer(Color color)
	{
		return Game::getInstance().killPlayer(color);
	}
	
    void addTokenConfigPath(Color color, std::string path)
	{
		Game::getInstance().addTokenConfigPath(color, path);
	}

    void performBattle()
    {
        Game::getInstance().performBattle();
    }

	bool actionTokenBattle(int tokenId, Color color)
	{
		return Game::getInstance().actionTokenBattle(tokenId, color);
	}
	
    bool actionTokenMove(int tokenId, Color color, int fromQ, int fromR, int toQ, int toR)
	{
		return Game::getInstance().actionTokenMove(tokenId, color, Hex(fromQ, fromR), Hex(toQ, toR));
	}
	
    bool actionTokenPush(int tokenId, Color color, int fromQ, int fromR, int toQ, int toR)
	{
		return Game::getInstance().actionTokenPush(tokenId, color, Hex(fromQ, fromR), Hex(toQ, toR));
	}

    boost::python::dict getTokenHand(int tokenId, Color color)
    {
        Token* token = Game::getInstance().getTokenHand(tokenId, color);
        return tokenDict(token);
    }

    boost::python::dict getTokenBoard(int q, int r)
    {
        Token* token = Game::getInstance().getTokenBoard(Hex(q, r));
        return tokenDict(token);
    }

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
