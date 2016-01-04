#include "game.h"

Game::Game() : MaxPlayersNum(4)
{
    boost::mpl::for_each<modsTypes>(RegisterTypeInFactory<ModFactory>());
    boost::mpl::for_each<tokensTypes>(RegisterTypeInFactory<TokenFactory>());
    TokenFactory::getInstance().registerFun(TokenModule::typeName(), TokenModule::create);
    TokenFactory::getInstance().registerFun(TokenHQ::typeName(), TokenHQ::create);
    //boost::mpl::for_each<modsTypes>(RegisterTypeInFactory<ModFactory>());
    board_ = new Board;
    currentPlayerNum=0;
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
    std::cout<<"game dest"<<std::endl;
    return board_;
    std::cout<<"game dest end"<<std::endl;
}

bool Game::addPlayer(std::string name)
{
    if (players.size()<=MaxPlayersNum)
    {
		Player* player=new Player(name);
        Color nextColor = getNextColor();
        if(tokensFiles.find(nextColor)!=tokensFiles.end())
        {
            player->setStack(nextColor, tokensFiles[nextColor]);
            players.push_back(player);
            playersMap[nextColor]=players.size()-1;
            //std::cout<<"returning true"<<std::endl;
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

void Game::removeAllPlayers()
{
    for(auto it=players.begin(); it!=players.end(); ++it)
    {
        delete *it;
    }
    players.clear();
    playersMap.clear();
}

std::vector<std::string> Game::getPlayersNames()
{
    std::vector<std::string> names;
    for(auto i=players.begin(); i<players.end(); ++i)
    {
        names.push_back((*i)->getName());
    }
    return names;
}

void Game::addTokenConfigPath(Color color, string path)
{
    tokensFiles[color] = path;
}

std::vector<Player*> Game::getPlayers()
{
    return players;
}

void Game::restartGame()
{
    removeAllPlayers();
    delete board_;
    board_=new Board();
    currentPlayerNum=0;    
}

bool Game::addToken(int tokenId, Color color, Hex pos, int angle)
{
    int playerId=getPlayerId(color);
    if(playerId!=-1 && board_->getToken(pos)==nullptr)
    {
        TokenPutable* token=dynamic_cast<TokenPutable*>(players[playerId]->getToken(tokenId));
        if(token!=nullptr)
        {
            token->setAngle(angle);
            return board_->addToken(pos, token);
        }
    }
    return false;
}

bool Game::throwToken(int tokenId, Color color)
{
    return players[getPlayerId(color)]->throwToken(tokenId);
}

Player* Game::getNextPlayer()
{
    currentPlayerNum = (currentPlayerNum + 1)%players.size();
    players[currentPlayerNum]->getNextTokensOnHandIds();
    return getCurrentPlayer();
}

Player* Game::getCurrentPlayer()
{
    if(currentPlayerNum<players.size())
        return players[currentPlayerNum];
    return nullptr;
}

bool Game::actionTokenBattle(int tokenId, Color color)
{
    TokenAction* token=dynamic_cast<TokenAction*>(players[getPlayerId(color)]->getToken(tokenId));
    if(token->getType() == ActionType::BATTLE)
    {
        //BattleHandler::getInstance().handleBattle();
        return true;
    }
    return false;
}

bool Game::actionTokenMove(int tokenId, Color color, Hex from, Hex to)
{
    int playerId=getPlayerId(color);
    if(playerId!=-1)
    {
        TokenAction* token=dynamic_cast<TokenAction*>(players[playerId]->getToken(tokenId));
        if(token->getType() == ActionType::MOVE)
        {
            TokenPutable* tokenToMove = board_->getToken(from);
            if (color==tokenToMove->getColor())
            {
                return board_->moveToken(from, to);
            }
            return false;
        }
    }
    return false;
}

bool Game::actionTokenPush(int tokenId, Color color, Hex from, Hex to)
{
    TokenAction* token=dynamic_cast<TokenAction*>(players[getPlayerId(color)]->getToken(tokenId));
    if(token->getType() == ActionType::PUSH)
    {
        TokenPutable* tokenToMove = board_->getToken(from);
        if (color!=tokenToMove->getColor())
        {
            return board_->pushToken(from, to);
        }
    }
    return false;
}

bool Game::killPlayer(Color color)
{
    int id=getPlayerId(color);
    if(id!=-1)
    {
        Player* player=players[id];
        players.erase(players.begin() + id);
        playersMap.erase(color);
        delete player;
        return true;
    }
    return false;
}

int Game::getPlayerId(Color color)
{
    auto it=playersMap.find(color);
    if(it!=playersMap.end())
        return playersMap[color];
    return -1;
}


std::string Game::getTokenName(int tokenId, Color color)
{
    Token* token = players[getPlayerId(color)]->getToken(tokenId);
    return token->getName();
}
