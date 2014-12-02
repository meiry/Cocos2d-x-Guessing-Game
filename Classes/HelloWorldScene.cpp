//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "HelloWorldScene.h"
#include "SignFactory.h"
#include "Settings.h"
#include "Sign.h"
#include "LevelsManager.h"
#include "PopupLayer.h"
#include "SimpleAudioEngine.h"
#include "ScoreManager.h"
#include "FacebookLayer.h"
#include "FacebookAPI.h"
#include "ParticleFactory.h"
#include "VisibleRect.h"
#include "UT.h"




HelloWorld::HelloWorld() :m_bNextButtonIsVisible(false)
{
   ;
}
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    winSize = Director::getInstance()->getWinSize();
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    Rect rec = VisibleRect::getVisibleRect();
    float thisVisibleSizeWidth = visibleSize.width;
    float thisVisibleSizeHeight = visibleSize.height;
    //calculate the screen 
    float ScoreContainerHeight =  (thisVisibleSizeHeight * iScoreContainerHeightPercentage) /100 ;
    float ImageExpressionContainerHeight =  (thisVisibleSizeHeight * iImageExpressionContainerHeightPercentage) /100 ;
    float SolutionContainerHeight =   (thisVisibleSizeHeight * iSolutionContainerHeightPercentage) /100 ;
    float FontSelectionContainerHeight = (thisVisibleSizeHeight * iFontSelectionContainerHeightPercentage) /100 ;
    
    
    
    
   

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	 

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,200);
#endif
    
   
    pUT = new UT();
    loadSpriteFrames();
    



    pFontSelectionContainer = FontSelectionContainer::create(this);
    pFontSelectionContainer->setAnchorPoint(Vec2(0.0,0.0));
    pFontSelectionContainer->setPosition(Vec2(0,0)); 
    pFontSelectionContainer->setTextureRect(Rect(0, 0,thisVisibleSizeWidth , FontSelectionContainerHeight));
    pFontSelectionContainer->setColor(FontSelectionContainer_bk_color); 
    this->addChild(pFontSelectionContainer,2,children_tags::FONTSELECTIONCONTAINER);
 
    pSolutionContainer = SolutionContainer::create(this);
    pSolutionContainer->setAnchorPoint(Vec2(0.0,0.0));
    float solutionContainerYPos = pFontSelectionContainer->getPositionY()+pFontSelectionContainer->getContentSize().height;
    pSolutionContainer->setPosition(Vec2(0,solutionContainerYPos)); 
    pSolutionContainer->setTextureRect(Rect(0, 0, thisVisibleSizeWidth, SolutionContainerHeight));
    pSolutionContainer->setColor(SolutionContainer_bk_color); 
    //pSolutionContainer->setSpriteExtra();
    this->addChild(pSolutionContainer,2,children_tags::SOLUTIONCONTAINER);

    pImageExpressionContainer = ImageExpressionContainer::create();
    pImageExpressionContainer->setAnchorPoint(Vec2(0.0,0.0));
    float pImageExpressionContainerYPos = pSolutionContainer->getPositionY()+pSolutionContainer->getContentSize().height;
    pImageExpressionContainer->setPosition(Vec2(0,pImageExpressionContainerYPos)); 
    pImageExpressionContainer->setTextureRect(Rect(0, 0, thisVisibleSizeWidth, ImageExpressionContainerHeight));
    pImageExpressionContainer->setColor(ImageExpressionContainer_bk_color); 
   // pImageExpressionContainer->setSpriteExtra();
    this->addChild(pImageExpressionContainer,2,children_tags::IMAGEEXPRESSIONCONTAINER); 


    pScoreContainer = ScoreContainer::create(this);
    pScoreContainer->setAnchorPoint(Vec2(0.0,0.0));
    float pScoreContainerYPos = pImageExpressionContainer->getPositionY()+pImageExpressionContainer->getContentSize().height;
    pScoreContainer->setPosition(Vec2(0,pScoreContainerYPos)); 
    pScoreContainer->setTextureRect(Rect(0, 0, thisVisibleSizeWidth, ScoreContainerHeight));
    pScoreContainer->setColor(ScoreContainer_bk_color);
    //pScoreContainer->setSpriteExtra();
    this->addChild(pScoreContainer,2,children_tags::SCORECONTAINER);
    
    setFirstBeforGameStart();
    
     
    this->schedule(schedule_selector(HelloWorld::tick), 0.6f);
    
    return true;
    
}     

void HelloWorld::tick(float dt)
{
    ParticleFactory::getInstance()->runParticalsEveryN(dt);
}

void HelloWorld::invokeParticals()
{
    std::vector<ParticleSystemQuad*> pStarParticlesEmitterVector = pSolutionContainer->getStarParticlesEmitterVector();
    ParticleFactory::getInstance()->invokeParticals(particaleType::EXPLOSION_FIREWORKS_RING_FROM_FILE,pStarParticlesEmitterVector);
    
}

void HelloWorld::setFirstBeforGameStart()
{
    //sign init 
    SignFactory::getInstance()->init(this);
    //level init
    LevelsManager::getInstance()->init(this);    
	ScoreManager::getInstance()->init(this);
    pScoreContainer->setSpriteExtra();
    pSolutionContainer->setSpriteExtra();
    pImageExpressionContainer->setSpriteExtra();
    FacebookAPI::getInstance()->init(this);
    ParticleFactory::getInstance()->init(this);
    core::Settings::getInstance()->init(this);

   
    
}

void HelloWorld::onExit()
{
    Layer::onExit();   
}

void HelloWorld::registerTouchListener()
{
	 
	_touchListenerTouchOneByOne = EventListenerTouchOneByOne::create(); 
	_touchListenerTouchOneByOne->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);    
    _touchListenerTouchOneByOne->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListenerTouchOneByOne, this);
	
}

void HelloWorld::onEnter()
{
     Layer::onEnter();
	 registerTouchListener();
     //set init game level after the view is render
     setStartingLevelNumber();
     
	 
}


void HelloWorld::setStartingLevelNumber()
{
    int ilevelnumber = core::Settings::getInstance()->levelnumber;
    LevelsManager::getInstance()->setLevelNumber(ilevelnumber);
    
}


void HelloWorld::setPopUpWindow()
{
    pPopupLayer = PopupLayer::create(this);
    pPopupLayer->setAnchorPoint(Point::ANCHOR_MIDDLE);
    pPopupLayer->setPosition(visibleSize.width/2,
                                        visibleSize.height/2);
    pPopupLayer ->setContentSize(Size(visibleSize.width,
                                            visibleSize.height));
    this->addChild(pPopupLayer,150);
}

void HelloWorld::afterCaptured(bool succeed, const std::string& outputFile)
{
    if (succeed)
    {
        log("%s",outputFile.c_str());
        FacebookAPI::getInstance()->setcurrentCapturedImagePath(outputFile);
        pFacebookLayer = FacebookLayer::create(this);
        pFacebookLayer->setAnchorPoint(Point::ANCHOR_MIDDLE);
        pFacebookLayer->setPosition(visibleSize.width/2,
                                            visibleSize.height/2);
        pFacebookLayer ->setContentSize(Size(visibleSize.width,
                                                visibleSize.height));
        this->addChild(pFacebookLayer,150);
#if defined(USE_FACEBOOK_INTEGRATION)
        //this->publishWithPhoto(outputFile);
#endif
    }
    else
    {
        log("Capture screen failed.");
    }
}

void HelloWorld::capture(const std::string imageName)
{
    cocos2d::utils::captureScreen(CC_CALLBACK_2(HelloWorld::afterCaptured,this),imageName);
}

void HelloWorld::setFacebookPopUpWindow()
{
    
      capture(sImageCapturedName_icon);


}

bool HelloWorld::getNextButtonIsVisible()
{
    return m_bNextButtonIsVisible;
}

void HelloWorld::setNextButtonIsVisible(bool b)
{
    m_bNextButtonIsVisible = b;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event  *event)
{
    return true;
}

template<typename T>
float HelloWorld::getSpriteBoundingBoxHeight(T s)
{
    float h =  s->getPositionY()+s->getBoundingBox().size.height;
    return h;
}

template<typename T>
bool HelloWorld::CurrentTouchInBoundary(float currentTouchY,T s) 
{
    if(currentTouchY > s->getPositionY() && currentTouchY < getSpriteBoundingBoxHeight(s))
    {
        return true;
    }
    return false;
}
 
bool HelloWorld::TouchDistributor(Vec2& location,Touch* &touch)
{
     
    float CurrentTouchY = location.y;
    if(!getNextButtonIsVisible())
    {
        if(CurrentTouchInBoundary(CurrentTouchY,pImageExpressionContainer))
        {
            ImageExpressionContainerTouchHandler(touch);
        }
        else if(CurrentTouchInBoundary(CurrentTouchY,pScoreContainer))
        {
             ScoreContainerTouchHandler(touch);
        }
        else if(CurrentTouchInBoundary(CurrentTouchY,pSolutionContainer))
        {
             MainContainerTouchHandler(touch);
        }
        else if(CurrentTouchInBoundary(CurrentTouchY,pFontSelectionContainer))
        {
             FontSelectionContainerTouchHandler(touch);
        }
        else
        {
             MainContainerTouchHandler(touch);
        }
    }
    else
    {
            MainContainerTouchHandler(touch);
    }
    return true;
}

bool HelloWorld::MainContainerTouchHandler(Touch* &touch)
{
    bool touched = false;
    Vector<Node *> thisSelectionChildren = this->getChildren();        
    for (auto iter = thisSelectionChildren.begin(); iter != thisSelectionChildren.end(); ++iter) 
    {
        Node *childNode = *iter; 
        if(!getNextButtonIsVisible()) //if Next button Not triggered
        {
            
            if(containsPointInSprite(childNode,LETTER_SIGH,NONE_,touch,this))
            {
                Sign* pSign = static_cast<Sign*>(*iter); 
                core::Settings::getInstance()->getSoundManager().playSoundEffect(pSign,SOLUTION_TO_FONT);
				pFontSelectionContainer->removeFromMainParantAndSetInSprite(pSign);
                touched = true;
                break;
                
            }
        }
        
        if(containsPointInSprite(childNode,sign_tags::NONE,NEXT_BT,touch,this))
        {          
            
                //ONLY TO TEST PARTICALES
            
                if(ParticleFactory::getInstance()->getRunParticales())
                {
                    ParticleFactory::getInstance()->setRunParticales(false);
                }
                LevelsManager::getInstance()->moveNextLevel();
                touched = true;  
        }
    }
    return touched;  
}


bool HelloWorld::ImageExpressionContainerTouchHandler(Touch* &touch)
{
    bool touched = false;
    Vector<Node *> ImageExpressionContainerChildren = pImageExpressionContainer->getChildren();
    for (auto iter = ImageExpressionContainerChildren.begin(); iter != ImageExpressionContainerChildren.end(); ++iter)
    {
        Node *childNode = *iter;         
       
        if(containsPointInSprite(childNode,sign_tags::NONE,ADD_CHAR,touch,pImageExpressionContainer))
        {
                core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);
                log("ImageExpressionContainer ADD_CHAR touched");
                pFontSelectionContainer->AddChar();
                touched = true;
                break;
        }
        if(containsPointInSprite(childNode,sign_tags::NONE,REMOVE_CHAR,touch,pImageExpressionContainer))
        {
                core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);                
                log("ImageExpressionContainer REMOVE_CHAR touched");
                pFontSelectionContainer->removeChar();
                touched = true;
                break;
        }
    }
    return touched;
}

bool HelloWorld::FontSelectionContainerTouchHandler(Touch* &touch)
{
    bool touched = false;
    Vector<Node *> FontSelectionContainerChildren = pFontSelectionContainer->getChildren();
    for (auto iter = FontSelectionContainerChildren.begin(); iter != FontSelectionContainerChildren.end(); ++iter) 
    {
        Node *childNode = *iter;         
        if(containsPointInSprite(childNode,LETTER_SIGH,NONE_,touch,pFontSelectionContainer))
        {
                Sign* pSign = static_cast<Sign*>(*iter);    
                core::Settings::getInstance()->getSoundManager().playSoundEffect(pSign,FONT_TO_SOLUTION);
                pSolutionContainer->setFontSelectionToSulotionFont(pSign);
                touched = true;
                break;
        }
        if(containsPointInSprite(childNode,sign_tags::NONE,FACEBOOK_POST_TO_WALL,touch,pFontSelectionContainer))
        {
                core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1); 
                log("pFontSelectionContainer touched");
                setFacebookPopUpWindow();
 
                touched = true;
                break;
        }
        
        if(containsPointInSprite(childNode,sign_tags::NONE,HELP_BT,touch,pFontSelectionContainer))
        {
                core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);
                log("pFontSelectionContainer HELP_BT touched");
				setPopUpWindow();
                touched = true;
                break;
        }
    }
     return touched;  
}

bool HelloWorld::ScoreContainerTouchHandler(Touch* &touch)
{
    bool touched = false;
    Vector<Node *> ScoreContainerChildren = pScoreContainer->getChildren();
    for (auto iter = ScoreContainerChildren.begin(); iter != ScoreContainerChildren.end(); ++iter) 
    {
        Node *childNode = *iter;        
        if(containsPointInSprite(childNode,sign_tags::NONE,SOUND_BT,touch,pScoreContainer))
        {
                pScoreContainer->setSoundButtonSpriteFrame(true);
                touched = true;
                break;				 
		}
        if(containsPointInSprite(childNode,sign_tags::NONE,CONFIG_BT,touch,pScoreContainer))
        {
                LevelsManager::getInstance()->setLevelNumber(0);
                touched = true;
                break;	 
        }
        if(containsPointInSprite(childNode,sign_tags::NONE,COINS_IMG_BT,touch,pScoreContainer))
        { 
                setPopUpWindow();
                touched = true;
                break;
        }           
	}
   return touched;  
}

template<typename T>
bool HelloWorld::containsPointInSprite(Node* node,sign_tags signTAG,buttons_tags buttonsTAG,Touch* &touch,T t)
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

bool HelloWorld::SolutionContainerTouchHandler(Touch* &touch)
{
      bool touched = false;
      return touched;  
}

void HelloWorld::onTouchEnded(Touch* touch, Event  *event)
{ 
    if(!core::Settings::getInstance()->stopTouchesInMainLayer)
    {
        Vec2 location = touch->getLocation();
        TouchDistributor(location,touch);
    }
}
 
void HelloWorld::onDraw()
{
   
    
}

HelloWorld::~HelloWorld()
{
    
    
    _eventDispatcher->removeEventListener(_touchListener);
     
}

void HelloWorld::setFileConfigurationToZero()
{
    UserDefault::getInstance()->setIntegerForKey("level",1);
    UserDefault::getInstance()->setIntegerForKey("score",0);
}


void HelloWorld::loadSpriteFrames()
{
    //images
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("sprites.plist", "sprites.png");
    pSpriteBatchNode = SpriteBatchNode::create("sprites.png");
    this->addChild(pSpriteBatchNode,0);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
