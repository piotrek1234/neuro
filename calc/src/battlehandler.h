#ifndef BATTLEHANDLER_H
#define BATTLEHANDLER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif

#include "board.h"
#include "game.h"
#include "creaturefinder.h"
#include "moduleapplier.h"

/**
 * @brief The BattleHandler class (singleton) is used to perform battle
 */
class CALC_DLL()BattleHandler {
public:
    BattleHandler() {}
    static BattleHandler& getInstance();
    void handleBattle();
};


#endif
