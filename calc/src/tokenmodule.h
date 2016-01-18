#ifndef TOKENMODULE_H
#define TOKENMODULE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4003)
#pragma warning(disable:4251)
#endif

#include <vector>
#include "tokenmodhq.h"
#include "hex.h"
#include "utils.h"
#include <string>
#include "modfactory.h"

class Mod;

/**
 * @brief The TokenModule class is a token with ability to modify token creatures
 */
class CALC_DLL()TokenModule : public TokenModHq
{
public:
    TokenModule();
    TokenModule(Color color) { setColor(color); }
    virtual ~TokenModule();
    virtual TokenPutable* clone() const;
    virtual void accept(Visitor& v);
    static Token* create(ptree Ptree, Color color);
    static std::string typeName() {return /*typeName_*/"module";}
    
private:
    //static std::string typeName_;
};

#endif // TOKENMODULE_H
