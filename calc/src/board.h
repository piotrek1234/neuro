#ifndef BOARD_H
#define BOARD_H

#ifdef CALC_EXPORTS
/** Workaround for Windows DLL library exports */
#define CALC_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define CALC_DLL(X) X
#endif

#include "token.h"

class CALC_DLL( Board ) {
public:
    Board()
    
private:
    
};


#endif