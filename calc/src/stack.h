#ifndef STACK_H
#define STACK_H

#include "token.h"
#include <vector>
#include <map>
#include "color.h"
#include "utils.h"
#include "tokenfactory.h"
#include <string>

class Stack {
public:
    Stack();
    void addToken(Token* token);
    int getSize();
    void deleteToken(unsigned int id);
    std::vector<int> getCurrentTokensIds();
    std::vector<int> getNextTokensIds(int num);
    Token* getToken(int id);
    void readTokens(Color color, std::string tokensConfigPath);
    
private:
    //TODO change to sharedptr
    std::vector<TokenPtr> tokens;
    std::vector<int> currentTokens;
    Color color;
    std::vector<int>::iterator findInCurrent(int id);
    std::vector<TokenPtr>::iterator findInTokens(int id);
    
};


#endif