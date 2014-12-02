//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "FontSelectionContainer.h"
#include "ImageExpressionContainer.h"
#include "ScoreContainer.h"
#include "SolutionContainer.h"
#include "config/ConstAppDefine.h"


#if defined(USE_FACEBOOK_INTEGRATION)
#include <iostream>
#include "screw/screw.h"
#include "network/HttpClient.h"
#include "settings/Settings.h"
#include "screw/Notification.h"


USING_NS_SCREW;
USING_NS_SCREW_FACEBOOK;
using namespace cocos2d::network;
#endif

class LevelsManager;
class SignFactory;
class PopupLayer;
class FacebookLayer;
class FacebookAPI;
class UT;
USING_NS_CC;
 

class HelloWorld : public cocos2d::Layer
{
    friend class LevelsManager;
    friend class ScoreManager;
    friend class SignFactory;
    friend class SolutionContainer;
    friend class FontSelectionContainer;
    friend class PopupLayer;
    friend class FacebookLayer;
    friend class FacebookAPI;

    friend class core::Settings;
public:
   
    ~HelloWorld();
     HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    Size winSize;
    Size visibleSize;
    Point origin;
    virtual void onEnter();
    virtual void onExit();

	void registerTouchListener();
 	bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchEnded(Touch* touch, Event  *event);
	cocos2d::EventListenerTouchOneByOne* _touchListenerTouchOneByOne;
    SpriteBatchNode* pSpriteBatchNode;
    bool getNextButtonIsVisible();
    void setNextButtonIsVisible(bool b);
 
protected:
    cocos2d::CustomCommand _customCommand;
    void onDraw();

private:
    void runParticals(float dt);
    void tick(float dt);
    void invokeParticals();
    void afterCaptured(bool succeed, const std::string& outputFile);
    void capture(const std::string imageName);
    template<typename T> bool containsPointInSprite(Node* node,
                                                    sign_tags signTAG,
                                                    buttons_tags buttonsTAG,
                                                    Touch* &touch,T t);
    void setFirstBeforGameStart();
    void setPopUpWindow();
    void setFacebookPopUpWindow();
    template<typename T> float getSpriteBoundingBoxHeight(T s);
    template<typename T> bool CurrentTouchInBoundary(float currentTouchY,T s);
    bool ImageExpressionContainerTouchHandler(Touch* &touch);
    bool FontSelectionContainerTouchHandler(Touch* &touch);
    bool ScoreContainerTouchHandler(Touch* &touch);
    bool SolutionContainerTouchHandler(Touch* &touch);
    bool MainContainerTouchHandler(Touch* &touch);
    bool TouchDistributor(Vec2& location,Touch* &touch);
    void setFileConfigurationToZero();
    void loadSpriteFrames();
    void setStartingLevelNumber();
    FontSelectionContainer *pFontSelectionContainer;
    SolutionContainer* pSolutionContainer;
    ImageExpressionContainer* pImageExpressionContainer;
    ScoreContainer* pScoreContainer;
    PopupLayer* pPopupLayer;
    FacebookLayer* pFacebookLayer;  
    bool m_bNextButtonIsVisible;    
    UT* pUT;
    
   
};

#endif // __HELLOWORLD_SCENE_H__
