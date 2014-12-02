//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _SignContainer_
#define _SignContainer_

#include "cocos2d.h"
 
USING_NS_CC;

class SignContainer : public Sprite
{
    public:
        SignContainer();
        ~SignContainer();
        static SignContainer* create(const std::string& frameName);
        virtual bool init(const std::string& frameName); 

    private:
        Size visibleSize;
};


#endif