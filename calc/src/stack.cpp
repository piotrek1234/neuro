#include "stack.h"

Stack::Stack()
{
    hq=true;
}

Stack::~Stack()
{
    for(auto i=currentTokens.begin(); i!=currentTokens.end(); ++i)
    {
        delete *i;
    }
    
    for(auto i=tokens.begin(); i!=tokens.end(); ++i)
    {
        delete *i;
    }
}

void Stack::readTokens(Color color, std::string tokensConfigPath)
{
    color_=color;
    tokens = TokenFactory::getInstance().createTokensFromFile(tokensConfigPath, color_);
}
        
void Stack::addToken(Token* token)
{
   this->tokens.push_back(token);
}

int Stack::getSize()
{
   return this->tokens.size() + currentTokens.size();
}

bool Stack::deleteToken(unsigned int id)
{
    auto it = findInCurrent(id);
    if(it!=currentTokens.end() && !hq)
    {
        this->currentTokens.erase(it);
        return true;
    }
    return false;
}

std::vector<int> Stack::getCurrentTokensIds()
{
    std::vector<int> ids;
    for(auto i=currentTokens.begin(); i!=currentTokens.end(); ++i)
    {
        ids.push_back((*i)->getId());
    }
    return ids;
}

std::vector<int> Stack::getNextTokensIds()
{
    if(hq)
    {
        currentTokens.push_back(tokens.front());
        tokens.erase(tokens.begin());
    }
    else
    {
        while(currentTokens.size()!=3)
        {
            currentTokens.push_back(tokens.front());
            tokens.erase(tokens.begin());
        }
    }
    return getCurrentTokensIds();
}

Token* Stack::getToken(int id)
{
    auto it = findInCurrent(id);
    if(it!=currentTokens.end())
    {
        Token* token = *it;
        this->currentTokens.erase(it);
        if(hq)
        {
            hq=false;
        }
        return token;
    }
    return nullptr;
}

std::vector<Token*>::iterator Stack::findInCurrent(int id)
{
    for(auto i=currentTokens.begin(); i!=currentTokens.end(); ++i)
    {
        if(id==(*i)->getId())
        {
            return i;
        }
    }
    return currentTokens.end();
}
