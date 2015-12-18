#include "stack.h"

Stack::Stack()
{
    
}

void Stack::readTokens(Color color, std::string tokensConfigPath)
{
    /*color_=color;
    tokens = TokenFactory::getInstance().createTokensFormFile(tokensConfigPath, color_);*/
}
        
void Stack::addToken(Token* token)
{
   // this->tokens.push_back(token);
}

int Stack::getSize()
{
   // this->tokens.size();
}

void Stack::deleteToken(unsigned int id)
{
  /*  auto it = findInCurrent(id);
    if(it!=nullptr)
    {
        auto token = findInTokens(id);
        this->tokens.erase(token);
        this->currentTokens.erase(it);
    }*/
}

std::vector<int> Stack::getCurrentTokensIds()
{
    //return this->currentTokens;
}

std::vector<int> Stack::getNextTokensIds(int num)
{
   /* int dif=num - currentTokens.size();
    if(dif>0)
    {
        for(int i=1; i<=dif; i++)
        {
            std::vector<Token*>::iterator token=this->tokens.end()-i;
            this->currentTokens.push_back(token->getId());
        }
        
    }
    return getCurrentTokensId();*/
}

TokenPtr Stack::getToken(int id)
{
    /*auto it = findInCurrent(id);
    if(it!=nullptr)
    {
        auto token = findInTokens(id);
        this->tokens.erase(token);
        this->currentTokens.erase(it);
        return token;
    }
    return nullptr;*/
}

std::vector<int>::iterator Stack::findInCurrent(int id)
{
   /* for(auto i=currentTokens.begin(); i!=currentTokens.end(), ++i)
    {
        if(id==*i)
        {
            return i;
        }
    }
    return nullptr;*/
}

std::vector<TokenPtr>::iterator Stack::findInTokens(int id)
{
   /* for (auto i=tokens.end()-1; i>=tokens.begin(); --i)
    {
        if(i->getId == id)
        {
            return i;
        }
    }
    return nullptr;*/
}
