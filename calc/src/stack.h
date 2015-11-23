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
#include <map>

class CALC_DLL( Stack ) {
public:
    Stack();
    void addToken(Token* token);
    int getSize();
    void deleteToken(unsigned int id);
    vector<int> getCurrentTokensIds();
    vector<int> getNextTokensIds(int num);
    Token* getToken(int id);
    Color getColor();
    
private:
    //TODO change to sharedptr
    vector<Token*> tokens;
    vector<int> currentTokens;
    Color color;
    vector<int>::iterator findInCurrent(int id);
    vector<Token*>::iterator findInTokens(int id);
    
};


#endif