#include "game.h"

Game::Game() : MaxPlayersNum(4)
{
    std::cout<<"game constructor"<<std::endl;
    boost::mpl::for_each<modsTypes>(RegisterTypeInFactory<ModFactory>());
    boost::mpl::for_each<tokensTypes>(RegisterTypeInFactory<TokenFactory>());
    TokenFactory::getInstance().registerFun(TokenModule::typeName, TokenModule::create);
    std::cout<<"tokens registered"<<std::endl;
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
    return board_;
}

bool Game::addPlayer(std::string name)
{
    if (players.size()<=MaxPlayersNum)
    {
		Player player(name);
        Color nextColor = getNextColor();
        if(tokensFiles.find(nextColor)!=tokensFiles.end())
        {
            player.setStack(nextColor, tokensFiles[nextColor]);
            players.push_back(player);
            playersMap[nextColor]=players.size()-1;
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
    players.clear();
    playersMap.clear();
}

std::vector<std::string> Game::getPlayersNames()
{
    std::vector<std::string> names;
    for(auto i=players.begin(); i<players.end(); ++i)
    {
        names.push_back(i->getName());
    }
    return names;
}

void Game::addTokenConfigPath(Color color, string path)
{
    tokensFiles[color] = path;
}

std::vector<Player> Game::getPlayers()
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

bool Game::addToken(int tokenId, Color color, Hex pos)
{
    TokenPutable* token=dynamic_cast<TokenPutable*>(players[getPlayerId(color)].getToken(tokenId));
    return board_->addToken(pos, token);
}

bool Game::throwToken(int tokenId, Color color)
{
    return players[getPlayerId(color)].throwToken(tokenId);
}

Player Game::getNextPlayer()
{
    currentPlayerNum = (currentPlayerNum + 1)%MaxPlayersNum;
    players[currentPlayerNum].getNextTokensOnHandIds();
    return getCurrentPlayer();
}

Player Game::getCurrentPlayer()
{
    return players[currentPlayerNum];
}

bool Game::actionToken(int tokenId, Color color, ActionArgs args)
{
    TokenAction* token=dynamic_cast<TokenAction*>(players[getPlayerId(color)].getToken(tokenId));
    if(token->getType() == ActionType::BATTLE)
    {
        //BattleHandler::getInstance().handleBattle();
        return true;
    }
    if(token->getType() == ActionType::MOVE)
    {
            std::pair<Hex, Hex> fromTo = boost::get<std::pair<Hex, Hex>>(args);
            Hex from = fromTo.first;
            Hex to = fromTo.second;
            TokenPutable* tokenToMove = board_->getToken(from);
            if (color==tokenToMove->getColor())
            {
                return board_->moveToken(from, to);
            }
            return false;
    }
    if(token->getType() == ActionType::PUSH)
    {
        std::pair<Hex, Hex> fromTo = boost::get<std::pair<Hex, Hex>>(args);
        Hex from = fromTo.first;
        Hex to = fromTo.second;
        TokenPutable* tokenToMove = board_->getToken(from);
        if (color!=tokenToMove->getColor())
        {
            return board_->pushToken(from, to);
        }
        return false;
    }
    return false;
}

bool Game::killPlayer(Color color)
{
    int id=getPlayerId(color);
    if(id!=-1)
    {
        players.erase(players.begin() + id);
        playersMap.erase(color);
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