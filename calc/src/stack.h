#ifndef STACK_H
#define STACK_H

#include "token.h"
#include <vector>
#include <map>

class Stack {
public:
    Stack();
    void addToken(Token* token);
    int getSize();
    void deleteToken(unsigned int id);
    std::vector<int> getCurrentTokensIds();
    std::vector<int> getNextTokensIds(int num);
    Token* getToken(int id);
    Color getColor();
    
private:
    //TODO change to sharedptr
    std::vector<Token*> tokens;
    std::vector<int> currentTokens;
    Color color;
    std::vector<int>::iterator findInCurrent(int id);
    std::vector<Token*>::iterator findInTokens(int id);
    
};


#endif