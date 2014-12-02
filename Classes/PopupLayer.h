//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef __PopupLayer_H__
#define __PopupLayer_H__

#include "cocos2d.h"
#include "Settings.h"
class UT;
class HelloWorld;
class PopupSprite;

USING_NS_CC;
//https://github.com/leafsoar/ls-cocos2d-x/blob/master/MacCpp/Classes/PopupLayer/PopupScene.cpp
class PopupLayer : public cocos2d::Layer 
{
public:

     PopupLayer(HelloWorld* const & parent);
    ~PopupLayer();
	 
    static PopupLayer* create(HelloWorld* const & parent);
    virtual bool init(); 
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
       
    virtual void onEnter();
    virtual void onExit();

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    HelloWorld* m_Parent;
 
  protected:
 
    
  private:
    bool setAddingCharAddAction();
    bool setAddingCharRemoveAction();
	bool isPointInNode(Point pt, Node* node);
    void setBuyPoints(buttons_tags tag);
    int getPointsByTag(buttons_tags tag);
    template<typename T> bool containsPointInSprite(Node* node,
                    sign_tags signTAG,buttons_tags buttonsTAG,
                    Touch* &touch,T t); 
    cocos2d::EventListenerTouchOneByOne* _touchListener;
    Sprite* pBackgroundSprite;
    cocos2d::Size winSize;
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
 	UT* pUT;
	HelloWorld* HelloWorldlayer;
    PopupSprite* pPopupSprite;
 


    

};

#endif // __PopupLayerObj_H__
