//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "SignContainer.h"
#include "Settings.h"

SignContainer::SignContainer()
{
    visibleSize = Director::getInstance()->getVisibleSize();
}

SignContainer::~SignContainer()
{

}


bool SignContainer::init(const std::string& frameName)
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Sprite::initWithSpriteFrameName(frameName) )
    {
        return false;
    }
   
    
     
	return true;
}


SignContainer* SignContainer::create(const std::string& frameName)
{
        auto sprite = new SignContainer;
        sprite->init(frameName);
        sprite->autorelease();
        return sprite;
} 