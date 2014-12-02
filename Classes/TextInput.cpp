//
//  TextInput.cpp
//  GuessGame
//
//  Created by meir yanovich on 9/20/14.
//
//

#include "TextInput.h"
#include "config/ConstAppDefine.h"

//////////////////////////////////////////////////////////////////////////
// local function
//////////////////////////////////////////////////////////////////////////

enum
{
    kTextFieldTTFDefaultTest = 0,
    kTextFieldTTFActionTest,
    kTextInputTestsCount,
};

#define FONT_NAME                       "fonts/Thonburi.ttf"
 

static int testIdx = -1;

static Rect getRect(Node * node)
{
    Rect rc;
    rc.origin = node->getPosition();
    rc.size = node->getContentSize();
    //rc.origin.x -= rc.size.width / 2;
    //rc.origin.y -= rc.size.height / 2;
    return rc;
}

TextInput::TextInput()
: _notificationLayer(0)
{
    
}

void TextInput::addKeyboardNotificationLayer(KeyboardNotificationLayer * layer)
{
    _notificationLayer = layer;
    addChild(layer);
}


void TextInput::onEnter()
{
    Layer::onEnter();
}



KeyboardNotificationLayer::KeyboardNotificationLayer()
: _trackNode(0)
{
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(KeyboardNotificationLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(KeyboardNotificationLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void KeyboardNotificationLayer::keyboardWillShow(IMEKeyboardNotificationInfo& info)
{
    CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
          info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);
    
    if (! _trackNode)
    {
        return;
    }
    
    auto rectTracked = getRect(_trackNode);
    CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
          rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);
    
    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! rectTracked.intersectsRect(info.end))
    {
        return;
    }
    
    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = info.end.getMaxY() - rectTracked.getMinY();
    CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);
    
    // move all the children node of KeyboardNotificationLayer
    auto& children = getChildren();
    Node * node = 0;
    ssize_t count = children.size();
    Vec2 pos;
    for (int i = 0; i < count; ++i)
    {
        node = children.at(i);
        pos = node->getPosition();
        pos.y += adjustVert;
        node->setPosition(pos);
    }
}

// Layer function

bool KeyboardNotificationLayer::onTouchBegan(Touch  *touch, Event  *event)
{
    CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
    _beginPos = touch->getLocation();
    return true;
}

void KeyboardNotificationLayer::onTouchEnded(Touch  *touch, Event  *event)
{
    if (! _trackNode)
    {
        return;
    }
    
    auto endPos = touch->getLocation();
    
    float delta = 5.0f;
    if (::abs(endPos.x - _beginPos.x) > delta
        || ::abs(endPos.y - _beginPos.y) > delta)
    {
        // not click
        _beginPos.x = _beginPos.y = -1;
        return;
    }
    
    // decide the trackNode is clicked.
    Rect rect;
    auto point = convertTouchToNodeSpaceAR(touch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);
    
    rect = getRect(_trackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
          rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    
    this->onClickTrackNode(rect.containsPoint(point));
    CCLOG("----------------------------------");
}

//////////////////////////////////////////////////////////////////////////
// implement TextFieldTTFDefaultTest
//////////////////////////////////////////////////////////////////////////
TextFieldTTFDefaultTest::TextFieldTTFDefaultTest(float x,float y)
:m_posX(x),m_posY(y)
{
    
}
std::string TextFieldTTFDefaultTest::subtitle() const
{
    return "TextFieldTTF with default behavior test";
}

void TextFieldTTFDefaultTest::onClickTrackNode(bool bClicked)
{
    auto pTextField = (TextFieldTTF*)_trackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("TextFieldTTFDefaultTest:TextFieldTTF attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("TextFieldTTFDefaultTest:TextFieldTTF detachWithIME");
        pTextField->detachWithIME();
    }
}

void TextFieldTTFDefaultTest::onEnter()
{
    KeyboardNotificationLayer::onEnter();
    
    // add TextFieldTTF
    auto s = Director::getInstance()->getWinSize();

    auto pTextField = TextFieldTTF::textFieldWithPlaceHolder(sFacebookMSG,
                                                             FONT_NAME,
                                                             fFacebookInputTextSize);
    pTextField->setAnchorPoint(Vec2(0.0f,0.0f));
    addChild(pTextField);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // on android, TextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position to make it visable
    //pTextField->setPosition(Vec2(s.width / 2, s.height/2 + 50));
    m_posY+=50;
    pTextField->setPosition(Vec2(m_posX,m_posY));
#else
    //pTextField->setPosition(Vec2(s.width / 2, s.height / 2));
    float xx =m_posX;
    float yy =m_posY;
    pTextField->setPosition(Vec2(xx,yy));
#endif
    
    _trackNode = pTextField;
}
