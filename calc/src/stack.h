#ifndef STACK_H
#define STACK_H

#include "token.h"
#include <vector>
#include <map>
#include "color.h"
#include "utils.h"
#include "tokenfactory.h"
#include <string>

class CALC_DLL()Stack {
public:
    Stack();
    ~Stack();
    void addToken(Token* token);
    int getSize();
    bool deleteToken(unsigned int id);
    std::vector<int> getCurrentTokensIds();
    std::vector<int> getNextTokensIds();
    Color getColor() const { return color_; }
    Token* getToken(int id, bool info_only=false);
    void readTokens(Color color, std::string tokensConfigPath);
    
private:
    bool hq;
    std::vector<Token*> tokens;
    std::vector<Token*> currentTokens;
    Color color_;
    std::vector<Token*>::iterator findInCurrent(int id);
    std::random_device rd;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
};


#endif
