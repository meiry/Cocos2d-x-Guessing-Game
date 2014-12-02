#include "FacebookLayer.h"
#include "UT.h"
#include "HelloWorldScene.h"
#include "FacebookSprite.h"
#include "Settings.h"
#include "config/ConstAppDefine.h"
#include "ScoreManager.h"
#include "FacebookAPI.h"
 
 
FacebookLayer::FacebookLayer(HelloWorld* const & parent)
{
     
	 
    pUT = new UT();
    m_Parent = parent;
	 
}
FacebookLayer* FacebookLayer::create(HelloWorld* const & parent)
{
        FacebookLayer* pFacebookLayer = new FacebookLayer(parent);
        pFacebookLayer->init();
        pFacebookLayer->autorelease();
        return pFacebookLayer;
} 
// on "init" you need to initialize your instance
bool FacebookLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
 #if defined(USE_FACEBOOK_INTEGRATION)
    EventDispatcher *dispatcher = Director::getInstance()->getEventDispatcher();
    EventListenerCustom *listener;
    listener = EventListenerCustom::create(FacebookPublishWithPhotoNotification, [=](EventCustom *event){
        this->onSendToFacebookDoneCallback(event);
    });
    dispatcher->addEventListenerWithSceneGraphPriority(listener,m_Parent);
#endif
    bSendOnce = false;
    this->setTag(layer_tages::POP_UP_BASE);
	winSize = Director::getInstance()->getWinSize();
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    pBackgroundSprite = FacebookSprite::create(m_Parent);   
   
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
                                           CC_CALLBACK_1(FacebookLayer::menuCloseCallback, this));
    closeItem->setPosition(Point(pBackgroundSprite->getContentSize().width,pBackgroundSprite->getContentSize().height));
	 
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    pBackgroundSprite->addChild(menu,5);




	return true;
}
void FacebookLayer::onExit()
{
    Layer::onExit();
    
}
void FacebookLayer::onEnter()
{
    Layer::onEnter();
     _touchListener = EventListenerTouchOneByOne::create(); 
     
    _touchListener->onTouchBegan = CC_CALLBACK_2(FacebookLayer::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(FacebookLayer::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(FacebookLayer::onTouchEnded, this);
	_touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
	 
   
}

bool FacebookLayer::isPointInNode(Point pt, Node* node)
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


bool FacebookLayer::onTouchBegan(Touch* touch, Event* event)
{
    bool touched = false;
    Vector<Node *> thisSelectionChildren = pBackgroundSprite->getChildren();        
    for (auto iter = thisSelectionChildren.begin(); iter != thisSelectionChildren.end(); ++iter) 
    {
        Node *childNode = *iter; 
          
        if(containsPointInSprite(childNode,sign_tags::NONE,GET_ADDCHAR_FOR5,touch,pBackgroundSprite))
        {
            //Sprite* pSprite = static_cast<Sprite*>(*iter);
            core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);               
            touched = true;
            break;
                
        }
        if(containsPointInSprite(childNode,sign_tags::NONE,CANCEL_SEND_TO_FACEBOOK,touch,pBackgroundSprite))
        {
            //Sprite* pSprite = static_cast<Sprite*>(*iter);
            core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);   
            this->removeFromParent();
            touched = true;
            break;
                
        }
        if(containsPointInSprite(childNode,sign_tags::NONE,SEND_TO_FACEBOOK,touch,pBackgroundSprite))
        {
            if(!bSendOnce)
            {
                core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);
                std::string sTextForFacebook  = pBackgroundSprite->getTextForFacebook();
                std::string sImgPathForFacebook  = FacebookAPI::getInstance()->getcurrentCapturedImagePath();
                FacebookAPI::getInstance()->publishWithPhoto(sImgPathForFacebook,sTextForFacebook) ;
                bSendOnce = true;
            }
            touched = true;
            break;
            
        }
     }
    event->stopPropagation();
    return touched;  
   
}

template<typename T>
bool FacebookLayer::containsPointInSprite(Node* node,
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


void FacebookLayer::onTouchMoved(Touch* touch, Event* event)
{
    //event->stopPropagation();
	 
}

void FacebookLayer::onTouchEnded(Touch* touch, Event* event)
{
   //event->stopPropagation(); 
    
    
     
}
 
void FacebookLayer::onSendToFacebookDoneCallback(EventCustom *event)
{
    this->removeFromParent();
}

FacebookLayer::~FacebookLayer()
{
    // Removes Touch Event Listener
    _eventDispatcher->removeEventListener(_touchListener);
     
}
void FacebookLayer::menuCloseCallback(Object* pSender)
{
	this->removeFromParent();
	//Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
}
