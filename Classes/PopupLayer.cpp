//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "PopupLayer.h"
#include "UT.h"
#include "HelloWorldScene.h"
#include "PopupSprite.h"
#include "Settings.h"
#include "config/ConstAppDefine.h"
#include "ScoreManager.h"
 
 
 
PopupLayer::PopupLayer(HelloWorld* const & parent)
{
     
	 
    pUT = new UT();
    m_Parent = parent;
	 
}
PopupLayer* PopupLayer::create(HelloWorld* const & parent)
{
        PopupLayer* pPopupLayer = new PopupLayer(parent);
        pPopupLayer->init();
        pPopupLayer->autorelease();
        return pPopupLayer;
} 
// on "init" you need to initialize your instance
bool PopupLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    this->setTag(layer_tages::POP_UP_BASE);
	winSize = Director::getInstance()->getWinSize();
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    pBackgroundSprite = PopupSprite::create(m_Parent);   
    //this->addChild(pBackgroundSprite,0,1);
    /*Size maskSize = pBackgroundSprite->getBoundingBox().size;
    auto clipNode = pUT->createRoundedRectMaskNode(maskSize, 10, 1.0f, 10);
     
    clipNode->addChild(pBackgroundSprite);    
    clipNode->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 a = clipNode->getAnchorPoint();
    Vec2 a2 = clipNode->getPosition();
    Vec2 aa = pBackgroundSprite->getAnchorPoint();
    Vec2 aa2 = pBackgroundSprite->getPosition();
    float sss = -100;
    clipNode->setPositionY(sss);
    clipNode->setPositionX(-150);*/
    this->addChild(pBackgroundSprite,0,1);
    

	 // add a "close" icon to exit the progress. it's an autorelease object
    std::string openclose = sOpenclose_icon;
    Sprite* button_close_up = Sprite::createWithSpriteFrameName(openclose);  
	Sprite* button_close_down = Sprite::createWithSpriteFrameName(openclose);  
    button_close_up->retain();
    button_close_down->retain();
	button_close_up->setAnchorPoint(Point::ZERO);
	button_close_down->setAnchorPoint(Point::ZERO);
    auto closeItem = MenuItemSprite::create(
                                           button_close_up,
                                           button_close_down,
                                           CC_CALLBACK_1(PopupLayer::menuCloseCallback, this));
    closeItem->setPosition(Point(pBackgroundSprite->getContentSize().width,pBackgroundSprite->getContentSize().height));
	//closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                            origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    pBackgroundSprite->addChild(menu,5);




	return true;
}
void PopupLayer::onExit()
{
    Layer::onExit();
    
}
void PopupLayer::onEnter()
{
    Layer::onEnter();
     _touchListener = EventListenerTouchOneByOne::create(); 
     
    _touchListener->onTouchBegan = CC_CALLBACK_2(PopupLayer::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(PopupLayer::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(PopupLayer::onTouchEnded, this);
	_touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
	 
    //std::string backgroundImage = m_ImageComponentMap["payline_schedule"]; 
   
	
}

bool PopupLayer::isPointInNode(Point pt, Node* node)
{
    Point locationInNode = node->convertToNodeSpace(pt);
    Size s = node->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
        return true;
    }
    return false;
}


bool PopupLayer::onTouchBegan(Touch* touch, Event* event)
{
    bool touched = false;
    Vector<Node *> thisSelectionChildren = pBackgroundSprite->getChildren();        
    for (auto iter = thisSelectionChildren.begin(); iter != thisSelectionChildren.end(); ++iter) 
    {
        Node *childNode = *iter; 
          
        if(containsPointInSprite(childNode,sign_tags::NONE,GET_ADDCHAR_FOR5,touch,pBackgroundSprite))
        {
            Sprite* pSprite = static_cast<Sprite*>(*iter); 
            core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);   
            setBuyPoints(GET_ADDCHAR_FOR5);
            log("GET_ADDCHAR_FOR5");
            touched = true;
            break;
                
        }
        
        if(containsPointInSprite(childNode,sign_tags::NONE,GET_REMOVECHAR_FOR5,touch,pBackgroundSprite))
        {
            Sprite* pSprite = static_cast<Sprite*>(*iter); 
            core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);
            setBuyPoints(GET_REMOVECHAR_FOR5);
            log("GET_REMOVECHAR_FOR5");
            touched = true;
            break;
                
        }

        if(containsPointInSprite(childNode,sign_tags::NONE,BUY_FOR099,touch,pBackgroundSprite))
        {
            Sprite* pSprite = static_cast<Sprite*>(*iter); 
            core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);
            setBuyPoints(BUY_FOR099);
            log("BUY_FOR099");
            touched = true;
            break;
                
        }

        if(containsPointInSprite(childNode,sign_tags::NONE,BUY_FOR999,touch,pBackgroundSprite))
        {
            Sprite* pSprite = static_cast<Sprite*>(*iter); 
            core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);	
            log("BUY_FOR999");
            setBuyPoints(BUY_FOR999);
            touched = true;
            break;
                
        }

        if(containsPointInSprite(childNode,sign_tags::NONE,BUY_FOR1999,touch,pBackgroundSprite))
        {
            Sprite* pSprite = static_cast<Sprite*>(*iter); 
            core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);
            log("BUY_FOR1999");
            setBuyPoints(BUY_FOR1999);
            touched = true;
            break;
                
        }
    }
    event->stopPropagation();
    return touched;  
   
}

template<typename T>
bool PopupLayer::containsPointInSprite(Node* node,
                                        sign_tags signTAG,
                                        buttons_tags buttonsTAG,
                                        Touch* &touch,T t)
{
    Point thisTouchPositionSelection;
    if(node->getTag() == signTAG || node->getTag() == buttonsTAG)
    {
        Sprite* pSprite = static_cast<Sprite*>(node);
        thisTouchPositionSelection = t->convertTouchToNodeSpace(touch);  
        if(pSprite->getBoundingBox().containsPoint(thisTouchPositionSelection))
        {
            return true;
        }
    }
    return false;
}


void PopupLayer::onTouchMoved(Touch* touch, Event* event)
{
    //event->stopPropagation();
	 
}

void PopupLayer::onTouchEnded(Touch* touch, Event* event)
{
   //event->stopPropagation(); 
    
    
     
}
 
void PopupLayer::setBuyPoints(buttons_tags tag)
{
    switch(tag)
    {
        case BUY_FOR099:
        {
            ScoreManager::getInstance()->setScoring(getPointsByTag(BUY_FOR099));
            break;
        }
        case BUY_FOR999:
        {
            ScoreManager::getInstance()->setScoring(getPointsByTag(BUY_FOR999));
            break;
        }
        case BUY_FOR1999:
        {
            ScoreManager::getInstance()->setScoring(getPointsByTag(BUY_FOR1999));
            break;
        }
        case GET_REMOVECHAR_FOR5:
        {
            setAddingCharRemoveAction();
            break;
        }
        case GET_ADDCHAR_FOR5:
        {
            setAddingCharAddAction() ;
            break;
        }
    }
}


bool PopupLayer::setAddingCharAddAction()
{  
    //check there is points 
    int iPointsAccumulator = ScoreManager::getInstance()->getPointsAccumulator();
    int iPointsForChar = getPointsByTag(GET_ADDCHAR_FOR5)*-1;

    if(iPointsAccumulator>iPointsForChar)
    {
         ScoreManager::getInstance()->setScoring(getPointsByTag(GET_ADDCHAR_FOR5));
         ScoreManager::getInstance()->increaseAddCharAccumulator(INCREASE_ADDCHAR_FROM_FONT);
       
         return true;
    }
     else
    {
        log("Need to buy more points .. to add chars");
        return false;

    }
}

bool PopupLayer::setAddingCharRemoveAction()
{
    int iPointsAccumulator = ScoreManager::getInstance()->getPointsAccumulator();
    int iPointsForChar = getPointsByTag(GET_REMOVECHAR_FOR5)*-1;

    if(iPointsAccumulator>iPointsForChar)
    {
        ScoreManager::getInstance()->setScoring(getPointsByTag(GET_REMOVECHAR_FOR5));
        ScoreManager::getInstance()->increaseRemoveCharAccumulator(INCREASE_REMOVECHAR_FROM_FONT);
        
        return true;
    }
    else
    {
        log("Need to buy more points .. to remove chars");
        return false;
    }
}


int PopupLayer::getPointsByTag(buttons_tags tag)
{
    int returnInt = 0;
    switch(tag)
    {
        case BUY_FOR099:
        {
            returnInt = buy_for099_points;
            break;
        }
        case BUY_FOR999:
        {
            returnInt = buy_for999_points;
            break;
        }
        case BUY_FOR1999:
        {
            returnInt = buy_for1999_points;
            break;
        }
        case GET_REMOVECHAR_FOR5:
        {
            returnInt = buy_removechar_points *-1;
            break;
        }
        case GET_ADDCHAR_FOR5:
        {
            returnInt = buy_addchar_points *-1;
            break;
        }
        
    }
    return returnInt;
}

PopupLayer::~PopupLayer()
{
    // Removes Touch Event Listener
    _eventDispatcher->removeEventListener(_touchListener);
     
}
void PopupLayer::menuCloseCallback(Object* pSender)
{
	this->removeFromParent();
	//Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
}
