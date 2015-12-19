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

#include "calc_test_operator.h"

#include "../src/game.h"
#include "../src/player.h"
#include "../src/hex.h"
#include "../src/modadditionalaction.h"
#include "../src/tokencreature.h"
#include "../src/tokenhq.h"
#include "../src/tokenmodule.h"

using namespace boost;
using boost::unit_test::test_suite;

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

BOOST_AUTO_TEST_SUITE_END()
