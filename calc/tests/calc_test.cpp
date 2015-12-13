/**
   calc library tests
   defines 'main' for cpp unit test
**/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>


#include "../src/game.h"
#include "../src/player.h"
#include "../src/hex.h"

using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE( calc_test )

BOOST_AUTO_TEST_CASE( CommandMgrTest )
{

	/*Game::getInstance().addPlayer("player1");
	int playersNum = Game::getInstance().getPlayersNames().size();
	BOOST_CHECK_EQUAL( playersNum, 1 );*/
}

/*BOOST_AUTO_TEST_CASE( HexTest )
{
    //constructor, q/r/s getter
    Hex h1(1, 2);
    BOOST_CHECK_EQUAL(h1.getQ(), 1);
    BOOST_CHECK_EQUAL(h1.getR(), 2);
    BOOST_CHECK_EQUAL(h1.getS(), -3);

    //isValid
    Hex h2(4, 5);
    BOOST_CHECK(!h1.isValid());

    //operators
    Hex h3(1, 2);
    BOOST_CHECK_EQUAL(h1==h2, false);
    BOOST_CHECK_EQUAL(h1!=h2, true);
    BOOST_CHECK_EQUAL(h1==h3, true);
    BOOST_CHECK_EQUAL(h1!=h3, false);
    BOOST_CHECK_EQUAL(h1+h2, Hex(5, 7));
    BOOST_CHECK_EQUAL(h1-h2, Hex(-3, -3));

    //direction
    BOOST_CHECK_EQUAL(Hex::direction(3), Hex(-1,0));
    BOOST_CHECK_EQUAL(Hex::direction(3), Hex::direction(9));
    BOOST_CHECK_EQUAL(Hex::direction(4), Hex::direction(-2));

    //neighbors
    BOOST_CHECK_EQUAL(h1.getNeighbor(2), Hex(1,1));
    BOOST_CHECK_EQUAL(h1.getNeighbor(-2), Hex(0,3));
    BOOST_CHECK_EQUAL(h1.getNeighbor(Hex(0,-1)), Hex(1,1));
    BOOST_CHECK_EQUAL(h1.getNeighbor(Hex(0,0)), h1);
}*/

BOOST_AUTO_TEST_SUITE_END()
