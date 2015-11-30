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
#endif


#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <string>
#include "game.h"

using namespace boost::python;
using namespace std;

/** Python intreface to CommandManager
 */
class CommandManagerPy {
public:
	
	void addPlayer(std::string name)
	{
		Game::getInstance().addPlayer(name);
	}
	
	std::vector<std::string> getPlayers()
	{
		return Game::getInstance().getPlayersNames();
	}
};

/**
 * Python wrapper using Boost.Python
 */
BOOST_PYTHON_MODULE( calc )
{
    //! exports getNumber to Python
    //boost::python::def( "getNumber", getNumber );

    /*boost::python::enum_<mt4cpp::CommandDesc::State>("CommandState")
        .value("NONE",mt4cpp::CommandDesc::NONE)
        .value("QUEUED",mt4cpp::CommandDesc::QUEUED)
        .value("PENDING",mt4cpp::CommandDesc::PENDING)
        .value("INTERRUPTED",mt4cpp::CommandDesc::INTERRUPTED)
        .value("EXCEPTION",mt4cpp::CommandDesc::EXCEPTION)
        .value("DONE",mt4cpp::CommandDesc::DONE)
        .export_values()
        ;*/
		
	class_<std::vector<std::string> >("vectorOfStrings")
		.def(vector_indexing_suite<std::vector<std::string> >() )
		;

    class_<CommandManagerPy>("CommandManager")
		.def( "addPlayer", &CommandManagerPy::addPlayer )
		.def( "getPlayers", &CommandManagerPy::getPlayers )
        ;

}
