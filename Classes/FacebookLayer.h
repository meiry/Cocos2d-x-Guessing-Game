#ifndef __FacebookLayer_H__
#define __FacebookLayer_H__

//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "cocos2d.h"
#include "Settings.h"
class UT;
class HelloWorld;
class FacebookSprite;

USING_NS_CC;
//https://github.com/leafsoar/ls-cocos2d-x/blob/master/MacCpp/Classes/FacebookLayer/PopupScene.cpp
class FacebookLayer : public cocos2d::Layer 
{
public:

     FacebookLayer(HelloWorld* const & parent);
    ~FacebookLayer();
	 
    static FacebookLayer* create(HelloWorld* const & parent);
    virtual bool init(); 
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
       
    virtual void onEnter();
    virtual void onExit();

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onSendToFacebookDoneCallback(EventCustom *event);
    HelloWorld* m_Parent;
 
  protected:
 
    
  private:
    
	bool isPointInNode(Point pt, Node* node);        
    template<typename T> bool containsPointInSprite(Node* node,
                    sign_tags signTAG,buttons_tags buttonsTAG,
                    Touch* &touch,T t); 
    cocos2d::EventListenerTouchOneByOne* _touchListener;
    FacebookSprite* pBackgroundSprite;
    cocos2d::Size winSize;
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
 	UT* pUT;
	HelloWorld* HelloWorldlayer;
    FacebookSprite* pPopupSprite;
    bool bSendOnce;
 


    

};

#endif // __FacebookLayerObj_H__
