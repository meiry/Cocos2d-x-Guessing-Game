#include "FacebookSprite.h"
#include "UT.h"
#include "HelloWorldScene.h"
#include "Settings.h"
#include "FacebookAPI.h"
#include "TextInput.h"
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\


FacebookSprite::FacebookSprite(HelloWorld* const & parent)
    :fOffSetFromButtom(0),
    fCaturedImageOffSetFromButtom(0)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    pUT = new UT();
    m_Parent = parent;
}

FacebookSprite::~FacebookSprite()
{

}

bool FacebookSprite::init()
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Sprite::init() )
    {
        return false;
    }
    
        
    thisPopupWidth = visibleSize.width - (20 * visibleSize.width / 100);
    thisPopupHeight = visibleSize.height - (30 * visibleSize.height / 100);
    this->setTextureRect(Rect(0, 0,thisPopupWidth , thisPopupHeight));
	this->setColor(FacebookContainer_bk_color);
    thisSize =  this->getBoundingBox().size;
    m_buttonsScalFacor = 0.7f;
    fOffSetFromButtom = 10.0f;
    
    setButtons();
    setCapturedImage(pSendToFacebookButt);
    setTextField(pCaturedImage);
     
	return true;
}
 
FacebookSprite* FacebookSprite::create(HelloWorld* const & parent)
{
        auto sprite = new FacebookSprite(parent);
        sprite->init();
        sprite->autorelease();
        return sprite;
} 

void FacebookSprite::setCapturedImage(Sprite* &butt)
{
    float imgScaleFactor = 0.45f;
    if(butt->getTag() !=buttons_tags::SEND_TO_FACEBOOK)
    {
        CCASSERT(true, "must be SEND_TO_FACEBOOK");   
    }
    Image* capturedImage = new Image();
    std::string CapturedImagePath = FacebookAPI::getInstance()->getcurrentCapturedImagePath();
    capturedImage->initWithImageFile(CapturedImagePath);
    Texture2D* pTexture2D = new Texture2D();
    pTexture2D->initWithImage(capturedImage);
    pCaturedImage = Sprite::createWithTexture(pTexture2D);
    pCaturedImage->retain();
    pCaturedImage->setTag(buttons_tags::CAPTURED_IMAGE);
    pCaturedImage->setScale(imgScaleFactor);
    pCaturedImage->setAnchorPoint(Vec2(0.5f,0.0f));
    fCaturedImageOffSetFromButtom = butt->getPositionY() + butt->getBoundingBox().size.height + 20;
    pCaturedImage->setPosition(this->getBoundingBox().size.width / 2.0f,fCaturedImageOffSetFromButtom);
    this->addChild(pCaturedImage,1);
}

void FacebookSprite::setButtons()
{
    
    float buttScaleFactor = 0.6f;
    
    pSendToFacebookButt = Sprite::createWithSpriteFrameName(sSendTofacebook_icon);
    pSendToFacebookButt->retain();
    pSendToFacebookButt->setTag(buttons_tags::SEND_TO_FACEBOOK);
    pSendToFacebookButt->setScale(buttScaleFactor);
    pSendToFacebookButt->setAnchorPoint(Vec2(0.0f,0.0f));
    this->addChild(pSendToFacebookButt,1);
    
    pCancelSendToFacebookButt = Sprite::createWithSpriteFrameName(sCancelSendTofacebook_icon);
    pCancelSendToFacebookButt->retain();
    pCancelSendToFacebookButt->setTag(buttons_tags::CANCEL_SEND_TO_FACEBOOK);
    pCancelSendToFacebookButt->setScale(buttScaleFactor);
    pCancelSendToFacebookButt->setAnchorPoint(Vec2(0.0f,0.0f));    
    this->addChild(pCancelSendToFacebookButt,1);
    Size s = pCancelSendToFacebookButt->getContentSize();
    float thistBoundingBoxWidth = this->getBoundingBox().size.width;
    float pSendToFacebookButtBoundingWidthX2 = pSendToFacebookButt->getBoundingBox().size.width*2;
    float tempCalcButtPosX = (thistBoundingBoxWidth - pSendToFacebookButtBoundingWidthX2);
    float sendButPosX = tempCalcButtPosX/3;
    pSendToFacebookButt->setPosition(sendButPosX,fOffSetFromButtom);
    float cancelSendButPosX = pSendToFacebookButt->getPositionX()+pSendToFacebookButt->getBoundingBox().size.width+(tempCalcButtPosX/3);
    pCancelSendToFacebookButt->setPosition(cancelSendButPosX,fOffSetFromButtom);
    
}

void FacebookSprite::setTextField(Sprite* &img)
{
    if(img->getTag() !=buttons_tags::CAPTURED_IMAGE)
    {
        CCASSERT(true, "must be CAPTURED_IMAGE");   
    }  
    
    pFacebookValueLabel = Label::createWithTTF(sFacebookMSG,"fonts/Marker Felt.ttf",fFacebookInputTextSize);
    pFacebookValueLabel->retain();
    pFacebookValueLabel->setTag(buttons_tags::TEXT_FACEBOOK_LAYER);
    pFacebookValueLabel->setColor(FacebookMSG_bk_color);
    pFacebookValueLabel->setAnchorPoint(Vec2(0.5f,0.0f));
    float txtWidth = pFacebookValueLabel->getBoundingBox().size.width;
    float txtHight = pFacebookValueLabel->getBoundingBox().size.height;
    float testboxPosY=img->getBoundingBox().size.height + img->getPositionY()+fFacebookInputFromImageOffSize; 
    //testboxPosY = (this->boundingBox().size.height - txtHight)-10;
    pFacebookValueLabel->setPosition(this->boundingBox().size.width/2,testboxPosY);
    this->addChild(pFacebookValueLabel,3);


    pFacebookWarningValueLabel = Label::createWithTTF(sFacebookWarningMSG,"fonts/Marker Felt.ttf",fFacebookInputWarningTextSize);
    pFacebookWarningValueLabel->retain();
    pFacebookWarningValueLabel->setTag(buttons_tags::TEXT_FACEBOOKWARNING_LAYER);
    pFacebookWarningValueLabel->setColor(FacebookMSGWarning_bk_color);
    pFacebookWarningValueLabel->setAnchorPoint(Vec2(0.5f,0.0f));   
    float FacebookWarningPosY=pFacebookValueLabel->getBoundingBox().size.height + pFacebookValueLabel->getPositionY()+fFacebookInputFromImageOffSize; 
    pFacebookWarningValueLabel->setPosition(this->boundingBox().size.width/2,FacebookWarningPosY);
    this->addChild(pFacebookWarningValueLabel,3);

    
}

std::string FacebookSprite::getTextForFacebook()
{
    return sFacebookMSG;
}

 

//
//void FacebookSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
//{
//    _customCommand.init(_globalZOrder);
//    _customCommand.func = CC_CALLBACK_0(FacebookSprite::onDraw, this, transform, flags);
//    renderer->addCommand(&_customCommand);
//}
//
//void FacebookSprite::onDraw(const Mat4 &transform, uint32_t flags)
//{
//    Director* director = Director::getInstance();
//    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
//    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
//    auto labelSize = pFacebookValueLabel->getContentSize();
//    auto origin = Director::getInstance()->getWinSize();
//    
//    origin.width = origin.width / 2 - (labelSize.width / 2);
//    origin.height = origin.height / 2 - (labelSize.height / 2);
//    
//    Vec2 vertices[4]=
//    {
//        Vec2(origin.width, origin.height),
//        Vec2(labelSize.width + origin.width, origin.height),
//        Vec2(labelSize.width + origin.width, labelSize.height + origin.height),
//        Vec2(origin.width, labelSize.height + origin.height)
//    };
//    DrawPrimitives::drawPoly(vertices, 4, true);
//
//    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//}
//

  