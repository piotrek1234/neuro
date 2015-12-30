/**
   calc library tests
   defines 'main' for cpp unit test
**/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "calc_test_operator.h"

#include "../src/game.h"
#include "../src/player.h"
#include "../src/board.h"
#include "../src/hex.h"
#include "../src/modadditionalaction.h"
#include "../src/tokencreature.h"
#include "../src/tokenhq.h"
#include "../src/tokenmodule.h"
#include "../src/tokenaction.h"
#include "../src/modpriority.h"
#include "../src/modlife.h"
#include "../src/modattack.h"
#include "../src/actiontype.h"
#include "../src/stack.h"
#include "../src/color.h"

using namespace boost;
using boost::unit_test::test_suite;
//std::string configPath="/home/magda/neurohex/calc/config.xml";
std::string configPath="calc/config.xml";

BOOST_AUTO_TEST_SUITE( calc_test )

BOOST_AUTO_TEST_CASE( CommandMgrTest )
{

	/*Game::getInstance().addPlayer("player1");
	int playersNum = Game::getInstance().getPlayersNames().size();
	BOOST_CHECK_EQUAL( playersNum, 1 );*/
}

BOOST_AUTO_TEST_CASE( HexTest )
{
    //constructor, q/r/s getter
    Hex h1(1, 2);
    BOOST_CHECK_EQUAL(h1.getQ(), 1);
    BOOST_CHECK_EQUAL(h1.getR(), 2);
    BOOST_CHECK_EQUAL(h1.getS(), -3);

    //isValid
    Hex h2(4, 5);
    BOOST_CHECK(h1.isValid());
    BOOST_CHECK(!h2.isValid());

    //operators
    Hex h3(1, 2);
    BOOST_CHECK_EQUAL(h1==h2, false);
    BOOST_CHECK_EQUAL(h1!=h2, true);
    BOOST_CHECK_EQUAL(h1==h3, true);
    BOOST_CHECK_EQUAL(h1!=h3, false);
    BOOST_CHECK_EQUAL(h1+h2, Hex(5, 7));
    BOOST_CHECK_EQUAL(h1-h2, Hex(-3, -3));
    Hex h4=h3;
    BOOST_CHECK_EQUAL(h4, Hex(1, 2));
    h3 = Hex(5,6);
    BOOST_CHECK_EQUAL(h4, Hex(1, 2));

    //direction
    BOOST_CHECK_EQUAL(Hex::direction(3), Hex(0,1));
    BOOST_CHECK_EQUAL(Hex::direction(3), Hex::direction(9));
    BOOST_CHECK_EQUAL(Hex::direction(4), Hex::direction(-2));
    BOOST_CHECK_EQUAL(Hex::direction(-1), Hex(1,-1));

    //revDirection
    BOOST_CHECK_EQUAL(Hex::revDirection(Hex(0,1)), 3);
    BOOST_CHECK_EQUAL(Hex::revDirection(Hex(0,0)), -1);

    //neighbors
    BOOST_CHECK_EQUAL(h1.getNeighbor(2), Hex(0,3));
    BOOST_CHECK_EQUAL(h1.getNeighbor(-2), Hex(2,2));
    BOOST_CHECK_EQUAL(h1.getNeighbor(Hex(0,-1)), Hex(1,1));
    BOOST_CHECK_EQUAL(h1.getNeighbor(Hex(0,0)), h1);
    BOOST_CHECK_EQUAL(h1.getNeighbor(Hex::revDirection(Hex(0,-1))), Hex(1,1));
}

BOOST_AUTO_TEST_CASE( ModTest )
{
    std::stringstream ss;

    //constructor, direction getter
    std::vector<int> vec0_5 = {0,1,2,3,4,5};
    std::vector<int> vec135 = {1,3,5};

    //directions 0..5
    Mod* maa = new ModAdditionalAction(vec0_5);
    for(auto i=maa->getDirectionBegin(); i!=maa->getDirectionEnd(); ++i)
        ss << *i;
    BOOST_CHECK_EQUAL(ss.str(), "012345");
    delete maa;
    ss.str("");

    //directions 1,3,5
    maa = new ModAdditionalAction(vec135);
    for(auto i=maa->getDirectionBegin(); i!=maa->getDirectionEnd(); ++i)
        ss << *i;
    BOOST_CHECK_EQUAL(ss.str(), "135");
    delete maa;
}

BOOST_AUTO_TEST_CASE( TokenCreatureTest )
{
    TokenCreature* tc = new TokenCreature;

    //common (Token)
    //set/get color
    BOOST_CHECK_EQUAL(tc->getColor(), Color::NONE);
    tc->setColor(Color::RED);
    BOOST_CHECK_EQUAL(tc->getColor(), Color::RED);

    //isPutable
    BOOST_CHECK_EQUAL(tc->isPutable(), true);

    //common (TokenPutable)
    //set/get life
    BOOST_CHECK_EQUAL(tc->getLife(), 1);
    tc->setLife(3);
    BOOST_CHECK_EQUAL(tc->getLife(), 3);

    //set/get position
    BOOST_CHECK_EQUAL(tc->getPosition(), Hex(5,5));
    tc->setPosition(Hex(0,1));
    BOOST_CHECK_EQUAL(tc->getPosition(), Hex(0,1));

    //set/get angle
    BOOST_CHECK_EQUAL(tc->getAngle(), 0);
    tc->setAngle(3);
    BOOST_CHECK_EQUAL(tc->getAngle(), 3);

    //TokenCreature
    //set/get movable
    BOOST_CHECK_EQUAL(tc->getMovable(), false);
    tc->setMovable(true);
    BOOST_CHECK_EQUAL(tc->getMovable(), true);

    //set/get AdditionalAction
    BOOST_CHECK_EQUAL(tc->getAdditionalAction(), false);
    tc->setAdditionalAction(true);
    BOOST_CHECK_EQUAL(tc->getAdditionalAction(), true);

    //set/get priority
    BOOST_CHECK_EQUAL(tc->getPriority(), 0);
    tc->setPriority(3);
    BOOST_CHECK_EQUAL(tc->getPriority(), 3);

    //shield: set, get, clear
    stringstream ss;
    for(int i=0; i<6; ++i)
        ss << tc->getShield(i);
    BOOST_CHECK_EQUAL(ss.str(), "000000");
    ss.str("");

    for(int i=0; i<6; ++i)
        tc->setShield(i, i%2);
    for(int i=0; i<6; ++i)
        ss << tc->getShield(i);
    BOOST_CHECK_EQUAL(ss.str(), "010101");
    ss.str("");

    for(int i=0; i<6; ++i)
        tc->setShield(i, i%3);
    for(int i=0; i<6; ++i)
        ss << tc->getShield(i);
    BOOST_CHECK_EQUAL(ss.str(), "011011");
    ss.str("");

    tc->clearShield();
    for(int i=0; i<6; ++i)
        ss << tc->getShield(i);
    BOOST_CHECK_EQUAL(ss.str(), "000000");
    ss.str("");

    //attack: add, get, clear
    for(int i=0; i<6; ++i)
        ss << tc->getAttack(i);
    BOOST_CHECK_EQUAL(ss.str(), "000000");
    ss.str("");

    for(int i=0; i<6; ++i)
        tc->addAttack(i, i);
    for(int i=0; i<6; ++i)
        ss << tc->getAttack(i);
    BOOST_CHECK_EQUAL(ss.str(), "012345");
    ss.str("");

    for(int i=0; i<6; ++i)
        tc->addAttack(i, 2);
    for(int i=0; i<6; ++i)
        ss << tc->getAttack(i);
    BOOST_CHECK_EQUAL(ss.str(), "234567");
    ss.str("");

    tc->clearAttack();
    for(int i=0; i<6; ++i)
        ss << tc->getAttack(i);
    BOOST_CHECK_EQUAL(ss.str(), "000000");
    ss.str("");

    //clone
    ///todo
}

BOOST_AUTO_TEST_CASE( TokenModFactoryTest )
{
    TokenFactory::getInstance().registerFun(TokenModule::typeName, TokenModule::create);
    TokenFactory::getInstance().registerFun(TokenCreature::typeName, TokenCreature::create);
    TokenFactory::getInstance().registerFun(TokenAction::typeName, TokenAction::create);
    TokenFactory::getInstance().registerFun(TokenHQ::typeName, TokenHQ::create);
    
    ModFactory::getInstance().registerFun(ModAdditionalAction::typeName, ModAdditionalAction::create);
    ModFactory::getInstance().registerFun(ModAttack::typeName, ModAttack::create);
    ModFactory::getInstance().registerFun(ModLife::typeName, ModLife::create);
    ModFactory::getInstance().registerFun(ModPriority::typeName, ModPriority::create);
    
    std::vector<Token*> tokens=TokenFactory::getInstance().createTokensFromFile(configPath, Color::BLUE);
    BOOST_CHECK_EQUAL(tokens.size(), 7);
    
    TokenHQ* hq=dynamic_cast<TokenHQ*>(tokens[0]);
    BOOST_CHECK(hq!=nullptr);
    BOOST_CHECK_EQUAL(hq->getId(), 1);
    
    TokenCreature* creature=dynamic_cast<TokenCreature*>(tokens[1]);
    BOOST_CHECK(creature!=nullptr);
    BOOST_CHECK_EQUAL(creature->getLife(), 2);
    BOOST_CHECK_EQUAL(creature->getPriority(), 2);
    BOOST_CHECK_EQUAL(creature->getAdditionalAction(), false);
    BOOST_CHECK_EQUAL(creature->getAttack(1), 2);
    BOOST_CHECK_EQUAL(creature->getAttack(2), 0);
    BOOST_CHECK_EQUAL(creature->getShield(1), true);
    BOOST_CHECK_EQUAL(creature->getShield(2), 0);
    BOOST_CHECK_EQUAL(creature->getId(), 2);
    
    TokenAction* action=dynamic_cast<TokenAction*>(tokens[2]);
    BOOST_CHECK(action!=nullptr);
    BOOST_CHECK(action->getType()==ActionType::BATTLE);
    BOOST_CHECK_EQUAL(action->getId(), 3);
    
    TokenModule* modLife=dynamic_cast<TokenModule*>(tokens[3]);
    BOOST_CHECK(modLife!=nullptr);
    ModLife* life = dynamic_cast<ModLife*>(modLife->getMod());
    BOOST_CHECK(life!=nullptr);
    BOOST_CHECK_EQUAL(*(life->getDirectionBegin()), 1);
    BOOST_CHECK_EQUAL(*(life->getDirectionBegin()+1), 2);
    BOOST_CHECK_EQUAL(modLife->getId(), 4);
    
    TokenModule* modAttack=dynamic_cast<TokenModule*>(tokens[4]);
    BOOST_CHECK(modAttack!=nullptr);
    ModAttack* attack = dynamic_cast<ModAttack*>(modAttack->getMod());
    BOOST_CHECK(attack!=nullptr);
    BOOST_CHECK_EQUAL(attack->getAttackValue(), 2);
    BOOST_CHECK_EQUAL(*(attack->getDirectionBegin()), 1);
    BOOST_CHECK_EQUAL(modAttack->getId(), 5);
    
    TokenModule* modPri=dynamic_cast<TokenModule*>(tokens[5]);
    BOOST_CHECK(modPri!=nullptr);
    ModPriority* pri = dynamic_cast<ModPriority*>(modPri->getMod());
    BOOST_CHECK(pri!=nullptr);
    BOOST_CHECK_EQUAL(*(pri->getDirectionBegin()), 1);
    BOOST_CHECK_EQUAL(modPri->getId(), 6);
    
    TokenModule* modAA=dynamic_cast<TokenModule*>(tokens[6]);
    BOOST_CHECK(modAA!=nullptr);
    ModAdditionalAction* aa = dynamic_cast<ModAdditionalAction*>(modAA->getMod());
    BOOST_CHECK(aa!=nullptr);
    BOOST_CHECK_EQUAL(*(aa->getDirectionBegin()), 1);
    BOOST_CHECK_EQUAL(modAA->getId(), 7);
    
}

BOOST_AUTO_TEST_CASE( StackTest )
{
    Stack stack;
    stack.readTokens(Color::RED, configPath);
    BOOST_CHECK_EQUAL(stack.getSize(), 7);
    stack.addToken(new TokenAction(ActionType::BATTLE));
    BOOST_CHECK_EQUAL(stack.getSize(), 8);
    stack.deleteToken(1);
    BOOST_CHECK_EQUAL(stack.getSize(), 8);
    BOOST_CHECK_EQUAL(stack.getCurrentTokensIds().size(), 0);
    BOOST_CHECK_EQUAL(stack.getNextTokensIds().size(), 1);
    BOOST_CHECK_EQUAL(stack.getCurrentTokensIds().size(), 1);
    stack.deleteToken(1);
    BOOST_CHECK_EQUAL(stack.getCurrentTokensIds().size(), 1);
    stack.getToken(1);
    BOOST_CHECK_EQUAL(stack.getCurrentTokensIds().size(), 0);
    BOOST_CHECK_EQUAL(stack.getSize(), 7);
    BOOST_CHECK_EQUAL(stack.getNextTokensIds().size(), 3);
    BOOST_CHECK_EQUAL(stack.getCurrentTokensIds().size(), 3);
    stack.deleteToken(2);
    BOOST_CHECK_EQUAL(stack.getCurrentTokensIds().size(), 2);
    stack.deleteToken(10);
    BOOST_CHECK_EQUAL(stack.getCurrentTokensIds().size(), 2);
    stack.getToken(3);
    BOOST_CHECK_EQUAL(stack.getCurrentTokensIds().size(), 1);
}

BOOST_AUTO_TEST_CASE( PlayerTest )
{
    Player player("Pawel");
    BOOST_CHECK_EQUAL(player.getName(), "Pawel");
    player.setStack(Color::RED, configPath);
    BOOST_CHECK(player.getColor()==Color::RED);
    BOOST_CHECK(player.getToken(1)==nullptr);
    BOOST_CHECK_EQUAL(player.getTokensOnHandIds().size(), 0);
    BOOST_CHECK_EQUAL(player.getNextTokensOnHandIds().size(), 1);
    BOOST_CHECK(player.getToken(5)==nullptr);
    player.getToken(1);
    BOOST_CHECK_EQUAL(player.getTokensOnHandIds().size(), 0);
    BOOST_CHECK_EQUAL(player.getNextTokensOnHandIds().size(), 3);
    player.getToken(2);
    BOOST_CHECK_EQUAL(player.getTokensOnHandIds().size(), 2);
    BOOST_CHECK_EQUAL(player.getNextTokensOnHandIds().size(), 3);
    BOOST_CHECK_EQUAL(player.getTokensOnHandIds().size(), 3);
    player.throwToken(3);
    BOOST_CHECK_EQUAL(player.getTokensOnHandIds().size(), 2);
}

BOOST_AUTO_TEST_CASE( GameTest )
{
    Game::getInstance().addTokenConfigPath(Color::RED, configPath);
    Game::getInstance().addTokenConfigPath(Color::BLUE, configPath);
    Game::getInstance().addTokenConfigPath(Color::YELLOW, configPath);
    Game::getInstance().addTokenConfigPath(Color::GREEN, configPath);
    
    BOOST_CHECK_EQUAL( Game::getInstance().getPlayers().size(), 0);
    Game::getInstance().addPlayer("player1");
	BOOST_CHECK_EQUAL( Game::getInstance().getPlayers().size(), 1 );
    
    Game::getInstance().addPlayer("player2");
	BOOST_CHECK_EQUAL( Game::getInstance().getPlayers().size(), 2 );
    
    Game::getInstance().addPlayer("player3");
	BOOST_CHECK_EQUAL( Game::getInstance().getPlayers().size(), 3 );
    Game::getInstance().addPlayer("player4");
	BOOST_CHECK_EQUAL( Game::getInstance().getPlayers().size(), 4 );
    Game::getInstance().addPlayer("player5");
	BOOST_CHECK_EQUAL( Game::getInstance().getPlayers().size(), 4 );
    
    BOOST_CHECK_EQUAL(Game::getInstance().getPlayers()[0]->getName(), "player1");
    BOOST_CHECK(Game::getInstance().getPlayers()[0]->getColor()==Color::BLUE);
    BOOST_CHECK_EQUAL(Game::getInstance().getPlayers()[0]->stackSize(), 7);
    
    BOOST_CHECK_EQUAL(Game::getInstance().getPlayers()[1]->getName(), "player2");
    BOOST_CHECK(Game::getInstance().getPlayers()[1]->getColor()==Color::RED);
    BOOST_CHECK_EQUAL(Game::getInstance().getPlayers()[1]->stackSize(), 7);
    
    BOOST_CHECK_EQUAL(Game::getInstance().killPlayer(Color::GREEN), true);
    /*BOOST_CHECK_EQUAL(Game::getInstance().killPlayer(Color::YELLOW), true);
    BOOST_CHECK_EQUAL( Game::getInstance().getPlayers().size(), 2 );*/
}

BOOST_AUTO_TEST_CASE( BoardTest )
{
    Board* board = new Board();
    TokenPutable* tc = new TokenCreature();
    tc->setAngle(4);
    BOOST_CHECK_EQUAL(board->addToken(Hex(1,-1), tc), true);
    BOOST_CHECK_EQUAL(tc->getPosition(), Hex(1,-1));
    BOOST_CHECK_EQUAL(tc->getAngle(), 4);
    tc = tc->clone();
    board->addToken(Hex(2,-2), tc, 2);
    BOOST_CHECK_EQUAL(tc->getAngle(), 2);
    tc = tc->clone();
    BOOST_CHECK_EQUAL(board->addToken(Hex(1,-1), tc), false);
    BOOST_CHECK_EQUAL(board->addToken(Hex(10,-1), tc), false);

    board->addToken(Hex(0,0), tc);
    BOOST_CHECK_EQUAL(board->moveToken(Hex(0,-1), Hex(1, -2)), false);  //z pustego
    BOOST_CHECK_EQUAL(board->moveToken(Hex(10,-1), Hex(1, -2)), false); //spoza planszy
    BOOST_CHECK_EQUAL(board->moveToken(Hex(1,-1), Hex(2, -2)), false);  //na zajęte
    BOOST_CHECK_EQUAL(board->moveToken(Hex(2,-2), Hex(10, -2)), false); //poza planszę
    BOOST_CHECK_EQUAL(board->moveToken(Hex(0,0), Hex(0, -1)), true);  //na wolne
    BOOST_CHECK_EQUAL(tc->getPosition(), Hex(0, -1));   //czy token wie o nowym miejscu
    BOOST_CHECK_EQUAL(board->getToken(Hex(0,0)), nullptr);   //czy miejsce się zwolniło
    BOOST_CHECK_EQUAL(board->moveToken(Hex(0,-1), Hex(0,0), 3), true); //z powrotem, obrócony
    BOOST_CHECK_EQUAL(tc->getAngle(), 3);   //czy został obrócony

    tc = tc->clone();
    board->addToken(Hex(2,-1), tc);
    BOOST_CHECK_EQUAL(board->deleteToken(Hex(0,-1)), false);    //z pustego
    BOOST_CHECK_EQUAL(board->deleteToken(Hex(2,-1), true), true);   //z zajętego
    BOOST_CHECK_EQUAL(board->getToken(Hex(2,-1)), nullptr); //czy miejsce się zwolniło

    BOOST_CHECK_EQUAL(board->pushToken(Hex(0,-1), Hex(1,-1)), false);   //nie ma kto pchnąć
    BOOST_CHECK_EQUAL(board->pushToken(Hex(1,-1), Hex(2,-1)), false);   //nie ma kogo pchnąć
    BOOST_CHECK_EQUAL(board->pushToken(Hex(1,-1), Hex(1,-1)), false);   //pchnięcie siebie
    BOOST_CHECK_EQUAL(board->pushToken(Hex(1,-1), Hex(2,-2)), false);   //pchnięcie poza planszę
    BOOST_CHECK_EQUAL(board->pushToken(Hex(0,-0), Hex(1,-1)), false);   //pchnięcie na zajęte pole
    BOOST_CHECK_EQUAL(board->pushToken(Hex(1,-1), Hex(0,0)), true);     //prawidłowe pchnięcie
    BOOST_CHECK_EQUAL(board->getToken(Hex(0,0)), nullptr);  //czy miejsce się zwolniło
    BOOST_CHECK_EQUAL(board->getToken(Hex(-1,1))->getPosition(), Hex(-1,1));    //czy pchnięty wie o tym

    BOOST_CHECK_EQUAL(board->getNeighbourToken(Hex(1,-1), 0), nullptr);
    BOOST_CHECK_EQUAL(board->getNeighbourToken(Hex(1,-1), 5)->getPosition(), Hex(2,-2));
}


BOOST_AUTO_TEST_SUITE_END()
