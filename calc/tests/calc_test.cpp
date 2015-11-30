/**
   calc library tests
   defines 'main' for cpp unit test
**/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>


#include "../src/game.h"
#include "../src/player.h"

using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE( calc_test )

BOOST_AUTO_TEST_CASE( CommandMgrTest )
{

	Game::getInstance().addPlayer("player1");
	int playersNum = Game::getInstance().getPlayersNames().size();
	BOOST_CHECK_EQUAL( playersNum, 1 );
}

BOOST_AUTO_TEST_SUITE_END()
