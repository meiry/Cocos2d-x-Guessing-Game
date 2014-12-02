//
//  TextInput.h
//  GuessGame
//
//  Created by meir yanovich on 9/20/14.
//
//

#ifndef __GuessGame__TextInput__
#define __GuessGame__TextInput__

#include <stdio.h>
#include "cocos2d.h"
#include "VisibleRect.h"

USING_NS_CC;

class KeyboardNotificationLayer;

class TextInput: public cocos2d::Layer
{
    KeyboardNotificationLayer * _notificationLayer;
public:
    TextInput();
    void addKeyboardNotificationLayer(KeyboardNotificationLayer * layer);
    virtual void onEnter() override;
private:
   
    
};



//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public Layer, public IMEDelegate
{
public:
    KeyboardNotificationLayer();
    
    virtual std::string subtitle() const = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;
    
    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);
    
    // Layer
    bool onTouchBegan(Touch  *touch, Event  *event);
    void onTouchEnded(Touch  *touch, Event  *event);
    
protected:
   
    Node * _trackNode;
    Vec2  _beginPos;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFDefaultTest for test TextFieldTTF default behavior.
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFDefaultTest : public KeyboardNotificationLayer
{
public:
    TextFieldTTFDefaultTest(float x,float y);
    // KeyboardNotificationLayer
    virtual std::string subtitle() const override;
    virtual void onClickTrackNode(bool bClicked);
    
    // Layer
    virtual void onEnter() override;
protected:
    float m_posX;
    float m_posY;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFActionTest
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFActionTest : public KeyboardNotificationLayer, public TextFieldDelegate
{
    TextFieldTTF *    _textField;
    Action *          _textFieldAction;
    bool                _action;
    int                 _charLimit;       // the textfield max char limit
    
public:
    void callbackRemoveNodeWhenDidAction(Node * node);
    
    // KeyboardNotificationLayer
    virtual std::string subtitle() const override;
    virtual void onClickTrackNode(bool bClicked);
    
    // Layer
    virtual void onEnter() override;
    virtual void onExit() override;
    
    // TextFieldDelegate
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender);
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender);
    virtual bool onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen) override;
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen) override;
    virtual bool onDraw(TextFieldTTF * sender);
};


#endif /* defined(__GuessGame__TextInput__) */
