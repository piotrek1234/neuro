#ifndef BATTLEHANDLER_H
#define BATTLEHANDLER_H

#include "board.h"
#include "game.h"
#include "creaturefinder.h"
#include "moduleapplier.h"

class CALC_DLL()BattleHandler {
public:
    static BattleHandler& getInstance();
    void handleBattle();
private:
    BattleHandler();
};


#endif
