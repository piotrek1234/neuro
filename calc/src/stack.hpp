#ifndef STACK_H
#define STACK_H

#ifdef CALC_EXPORTS
/** Workaround for Windows DLL library exports */
#define CALC_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define CALC_DLL(X) X
#endif

#include "token.h"
#include <vector>

class CALC_DLL( Stack ) {
public:
    Stack();
    void addToken(Token* token);
    int getSize();
    void throwToken();
    vector<int> getCurrentTokensIds();
    vector<int> getNextTokensIds();
    Token* getToken(int id);
    
private:
    vector<Token*> tokens;
    
};


#endif