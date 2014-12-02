#include "PopupSprite.h"
#include "UT.h"
#include "HelloWorldScene.h"
#include "Settings.h"



PopupSprite::PopupSprite(HelloWorld* const & parent) 
{
    visibleSize = Director::getInstance()->getVisibleSize();
    
    pUT = new UT();
    m_Parent = parent;
}

PopupSprite::~PopupSprite()
{

}

bool PopupSprite::init()
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Sprite::init() )
    {
        return false;
    }
    float popupWidth = visibleSize.width - (20 * visibleSize.width / 100);
    float popupHeight = visibleSize.height - (30 * visibleSize.height / 100);
    this->setTextureRect(Rect(0, 0,popupWidth , popupHeight));
	this->setColor(PopupLayer_bk_color);
    thisSize =  this->getBoundingBox().size;
    m_buttonsScalFacor =0.7f;
    
    creatGET_REMOVECHARFOR5(0);
    creatGET_ADDCHARFOR5(1);
    creatBUY_FOR099(2);
    creatBUY_FOR999(3);
    creatBUY_FOR1999(4);
    
    
	return true;
}

void PopupSprite::setButtPos(Sprite* &pSprite,int rawNum)
{
    
    float offSetFromTop = thisSize.height - 20.0f;
    float offSetFromEachOther = 10.0f;
    Size spriteSize = pSprite->getBoundingBox().size;
    switch(rawNum)
    {
        case 0:
        {
            float bttY = (offSetFromTop - (spriteSize.height /2)) - (spriteSize.height*rawNum);
            pSprite->setPosition(thisSize.width/2,bttY);
            break;
        }
        case 1:
        {
            float bttY = ((offSetFromTop-offSetFromEachOther*rawNum) - (spriteSize.height /2))- ((spriteSize.height*rawNum) );
            pSprite->setPosition(thisSize.width/2,bttY);
            break;
        }
        case 2:
        {
            float bttY = ((offSetFromTop-offSetFromEachOther*rawNum) - (spriteSize.height /2))- ((spriteSize.height*rawNum) );
            pSprite->setPosition(thisSize.width/2,bttY);
            break;
        }
        case 3:
        {
            float bttY = ((offSetFromTop-offSetFromEachOther*rawNum) - (spriteSize.height /2))- ((spriteSize.height*rawNum) );
            pSprite->setPosition(thisSize.width/2,bttY);
            break;
        }
        case 4:
        {
            float bttY = ((offSetFromTop-offSetFromEachOther*rawNum) - (spriteSize.height /2))- ((spriteSize.height*rawNum) );
            pSprite->setPosition(thisSize.width/2,bttY);
            break;
        }
    }
    
}

void PopupSprite::creatBUY_FOR099(int rawNum)
{
    pbutton_BUY_FOR099 = Sprite::createWithSpriteFrameName(buy_for099_icon);
    pbutton_BUY_FOR099->retain();
    pbutton_BUY_FOR099->setTag(BUY_FOR099);
    pbutton_BUY_FOR099->setScale(m_buttonsScalFacor);
    setButtPos(pbutton_BUY_FOR099,rawNum);
    this->addChild(pbutton_BUY_FOR099,1);
}
void PopupSprite::creatBUY_FOR999(int rawNum)
{
    pbutton_BUY_FOR999 = Sprite::createWithSpriteFrameName(buy_for999_icon); 
    pbutton_BUY_FOR999->retain();
    pbutton_BUY_FOR999->setTag(BUY_FOR999);
    pbutton_BUY_FOR999->setScale(m_buttonsScalFacor);
    setButtPos(pbutton_BUY_FOR999,rawNum);
    this->addChild(pbutton_BUY_FOR999,1);
}
void PopupSprite::creatBUY_FOR1999(int rawNum)
{ 
    pbutton_BUY_FOR1999 = Sprite::createWithSpriteFrameName(buy_for1999_icon);
    pbutton_BUY_FOR1999->retain();
    pbutton_BUY_FOR1999->setTag(BUY_FOR1999);
    pbutton_BUY_FOR1999->setScale(m_buttonsScalFacor);
    setButtPos(pbutton_BUY_FOR1999,rawNum);
    this->addChild(pbutton_BUY_FOR1999,1);
}
void PopupSprite::creatGET_REMOVECHARFOR5(int rawNum)
{
    pbutton_GET_REMOVECHAR_FOR5 = Sprite::createWithSpriteFrameName(get_removechar_for5_icon);
    pbutton_GET_REMOVECHAR_FOR5->retain();
    pbutton_GET_REMOVECHAR_FOR5->setTag(GET_REMOVECHAR_FOR5);
    pbutton_GET_REMOVECHAR_FOR5->setScale(m_buttonsScalFacor);
    setButtPos(pbutton_GET_REMOVECHAR_FOR5,rawNum);
    this->addChild(pbutton_GET_REMOVECHAR_FOR5,1);
}
void PopupSprite::creatGET_ADDCHARFOR5(int rawNum)
{
    pbutton_GET_ADDCHAR_FOR5 = Sprite::createWithSpriteFrameName(get_addchar_for5_icon);
    pbutton_GET_ADDCHAR_FOR5->retain();
    pbutton_GET_ADDCHAR_FOR5->setTag(GET_ADDCHAR_FOR5);
    pbutton_GET_ADDCHAR_FOR5->setScale(m_buttonsScalFacor);
    setButtPos(pbutton_GET_ADDCHAR_FOR5,rawNum);
    this->addChild(pbutton_GET_ADDCHAR_FOR5,1);
}

PopupSprite* PopupSprite::create(HelloWorld* const & parent)
{
        auto sprite = new PopupSprite(parent);
        sprite->init();
        sprite->autorelease();
        return sprite;
} 