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
    void addToken(TokenPtr token);
    int getSize();
    bool deleteToken(unsigned int id);
    std::vector<int> getCurrentTokensIds();
    std::vector<int> getNextTokensIds();
    Color getColor() const { return color_; }
    TokenPtr getToken(int id);
    void readTokens(Color color, std::string tokensConfigPath);
    
private:
    bool hq;
    std::vector<TokenPtr> tokens;
    std::vector<TokenPtr> currentTokens;
    Color color_;
    std::vector<TokenPtr>::iterator findInCurrent(int id);
    
};


#endif
