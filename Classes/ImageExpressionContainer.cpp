//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "ImageExpressionContainer.h"
#include "LevelsManager.h"
#include "Settings.h"
#include "config/ConstAppDefine.h"
#include "ScoreManager.h"
#include "UT.h"


ImageExpressionContainer::ImageExpressionContainer()
{
    ImageFrameToImageExpressionOffsetHeight = ImageExpressionContainerToImageFrameOffset;
}

ImageExpressionContainer::~ImageExpressionContainer()
{

}
bool ImageExpressionContainer::init()
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Sprite::init() )
    {
        return false;
    }
   
     pUT = new UT();
     
	return true;
}

Sprite* ImageExpressionContainer::setAddCharIcon()
{
    float scaleIcon = fAdd_char_icon_scale;
    Sprite* ptempAddChar = Sprite::createWithSpriteFrameName(sAdd_char_icon);
    ptempAddChar->retain();
	ptempAddChar->setTag(buttons_tags::ADD_CHAR);
    ptempAddChar->setScale(scaleIcon);
    ptempAddChar->setAnchorPoint(Vec2(0.0f,0.0f)); 
    
    return ptempAddChar;
}

Sprite* ImageExpressionContainer::setRemoveCharIcon()
{
    float scaleIcon = fRemove_char_icon_scale;
    Sprite* ptempRemoveChar = Sprite::createWithSpriteFrameName(sRemove_char_icon);
    ptempRemoveChar->retain();
	ptempRemoveChar->setTag(buttons_tags::REMOVE_CHAR);
    ptempRemoveChar->setScale(scaleIcon);
    //Vec2 v = this->getAnchorPoint();
    ptempRemoveChar->setAnchorPoint(Vec2(0.0f,0.0f)); 
    
    return ptempRemoveChar;
}




Sprite* ImageExpressionContainer::setFacebookIcon()
{
    float scaleIcon = fFacebook_post_to_wall_icon_scale;
    Sprite* ptempFaceBook_PostToWall = Sprite::createWithSpriteFrameName(sFacebook_post_to_wall_icon);
    ptempFaceBook_PostToWall->retain();
	ptempFaceBook_PostToWall->setTag(buttons_tags::FACEBOOK_POST_TO_WALL);
    ptempFaceBook_PostToWall->setScale(scaleIcon);
    //Vec2 v = this->getAnchorPoint();
    ptempFaceBook_PostToWall->setAnchorPoint(Vec2(0.0f,0.0f)); 
    
    return ptempFaceBook_PostToWall;
}

Sprite* ImageExpressionContainer::setHelpIcon()
{
    float scaleIcon = fHelp_icon_scale;
    Sprite* ptempHelp = Sprite::createWithSpriteFrameName(sHelp_icon);
    ptempHelp->retain();
	ptempHelp->setTag(buttons_tags::HELP_BT);
    ptempHelp->setScale(scaleIcon);
    ptempHelp->setAnchorPoint(Vec2(0.0f,0.0f)); 
    
    return ptempHelp;
}


void ImageExpressionContainer::setAllIconsInPlace()
{
    Sprite* pTmpFaceBook_PostToWall = NULL;     
    //Sprite* pTmpFaceBook_PostToWall = setThirdPartyIcones();
    //ImageFrameToImageExpressionOffsetHeight = pTmpFaceBook_PostToWall->getBoundingBox().size.height;
    setRightSideIcons();
    
}

Sprite* ImageExpressionContainer::setThirdPartyIcones()
{
    float iconesOffSet = 10.0f;
    float iconsWidth = 0.0f;
    float iconeXstartPos = 0.0f;
    float HelpXPosition = 0.0f;
#if defined(USE_HELP_INTEGRATION)
     Sprite* pHelp = pUT->setHelpIcon(); 
     #if defined(USE_ONLY_FACEBOOK_ICON) || defined(USE_FACEBOOK_INTEGRATION)
        Sprite* pFaceBook_PostToWall = pUT->setFacebookIcon();
        iconsWidth = pFaceBook_PostToWall->getBoundingBox().size.width + iconesOffSet + pHelp->getBoundingBox().size.width;
        iconeXstartPos = (this->boundingBox().size.width/2) - (iconsWidth/2);
        pFaceBook_PostToWall->setPosition(iconeXstartPos,
                                            0.0f);
        this->addChild(pFaceBook_PostToWall,4);
        HelpXPosition = iconeXstartPos+pFaceBook_PostToWall->getBoundingBox().size.width + iconesOffSet;
        
        #undef USE_ONLY_FACEBOOK_ICON
     #else
         iconsWidth = pHelp->getBoundingBox().size.width;
         iconeXstartPos = (this->boundingBox().size.width/2) - (iconsWidth/2);
         HelpXPosition = iconeXstartPos;
     #endif
     pHelp->setPosition(HelpXPosition,0.0f); 
     this->addChild(pHelp,4);
#endif 
#if defined(USE_ONLY_FACEBOOK_ICON)  
    pFaceBook_PostToWall = setFacebookIcon();
    iconsWidth = pFaceBook_PostToWall->getBoundingBox().size.width + iconesOffSet + pHelp->getBoundingBox().size.width;
    iconeXstartPos = (this->boundingBox().size.width/2) - (iconsWidth/2);
    pFaceBook_PostToWall->setPosition(iconeXstartPos,0.0f);
    this->addChild(pFaceBook_PostToWall,4);
    HelpXPosition = iconeXstartPos+pFaceBook_PostToWall->getBoundingBox().size.width + iconesOffSet;   
#endif
     return pFaceBook_PostToWall;
}

void ImageExpressionContainer::setRightSideIcons()
{
    setRemoveChar();
    setAddChar();
}

void ImageExpressionContainer::setAddChar()
{
    Size thisBoundingBoxSize = this->getBoundingBox().size;
    pAddChar =  setAddCharIcon(); 
    pAddChar->setAnchorPoint(Vec2(1.0f,1.0f));
    float Ypos = thisBoundingBoxSize.height;
    float Xpos = thisBoundingBoxSize.width;
    Ypos = Ypos-(pAddChar->getBoundingBox().size.height+fOffSetBetweenIcones);
    pAddChar->setPosition(Xpos,Ypos);
    std::string sPointsAccumulator = String::createWithFormat("%d",getAddCharCount())->getCString();;
    //Level progress font
	pAddCharPointCountValueLabel = Label::createWithTTF(sPointsAccumulator,fontLevelAddCharValueLabel, valueLabel_fnt_size);
    pAddCharPointCountValueLabel->retain();
    pAddCharPointCountValueLabel->setColor(RemoveCharPointCount_color);
    pAddCharPointCountValueLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    //Size PointsCountFrameSize = pPointsCountFrame->getBoundingBox().size;
    
    float midParent = pAddChar->getBoundingBox().size.width/2;

	pAddCharPointCountValueLabel->setPosition(Vec2(midParent,
                                        0.0f));    
    pAddChar->addChild(pAddCharPointCountValueLabel,5);
    this->addChild(pAddChar,4);
}
void ImageExpressionContainer::setRemoveChar()
{
    Size thisBoundingBoxSize = this->getBoundingBox().size;
    pRemoveChar = setRemoveCharIcon();
    pRemoveChar->setAnchorPoint(Vec2(1.0f,1.0f));
    float Ypos = thisBoundingBoxSize.height;
    float Xpos = thisBoundingBoxSize.width;
    pRemoveChar->setPosition(Xpos,Ypos);
    std::string sPointsAccumulator = String::createWithFormat("%d",getRemoveCharCount())->getCString();
    //Level progress font
	pRemoveCharPointCountValueLabel = Label::createWithTTF(sPointsAccumulator,fontLevelRemoveCharValueLabel, valueLabel_fnt_size);
    pRemoveCharPointCountValueLabel->retain();
    pRemoveCharPointCountValueLabel->setColor(RemoveCharPointCount_color);
    pRemoveCharPointCountValueLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    //Size PointsCountFrameSize = pPointsCountFrame->getBoundingBox().size;    
    float midParent = pRemoveChar->getBoundingBox().size.width/2;
    
	pRemoveCharPointCountValueLabel->setPosition(Vec2(midParent,
                                        0.0f));
    pRemoveChar->addChild(pRemoveCharPointCountValueLabel,5);
    this->addChild(pRemoveChar,4);
}

void ImageExpressionContainer::setPointsIntoLabel(int p,Label* &lbl)
{    
    lbl->setString(String::createWithFormat("%d",p)->getCString());  
}

void ImageExpressionContainer::setAddCharCount(int cCount)
{
    setPointsIntoLabel(cCount,pAddCharPointCountValueLabel);
}

void ImageExpressionContainer::setRemoveCharCount(int cCount)
{
    setPointsIntoLabel(cCount,pRemoveCharPointCountValueLabel);
}

int ImageExpressionContainer::getAddCharCount()
{
    return ScoreManager::getInstance()->getAddCharAccumulator();
}

int ImageExpressionContainer::getRemoveCharCount()
{
    return ScoreManager::getInstance()->getRemoveCharAccumulator();
}

void ImageExpressionContainer::setSpriteExtra()
{
	setAllIconsInPlace();
	float thisContentSizeWidth = this->getBoundingBox().size.width;
    float thisContentSizeHeight = this->getBoundingBox().size.height;
    m_ImageFrame = ImageFrame::create();
    m_ImageFrame->setAnchorPoint(Vec2(0.0,0.0));  
    m_ImageFrame->setTextureRect(Rect(0,0,thisContentSizeWidth-20 , thisContentSizeHeight - ImageFrameToImageExpressionOffsetHeight));
    m_ImageFrame->setColor(ImageFrame_bk_color);
    Size ImageFrameBoundingBoxSize = m_ImageFrame->getBoundingBox().size;
    float ImageFrameXpos = (thisContentSizeWidth /2 ) - ImageFrameBoundingBoxSize.width /2 ;
    float ImageFrameYpos = (thisContentSizeHeight /2 ) - m_ImageFrame->getBoundingBox().size.height /2 ;
    ImageFrameYpos+=ImageFrameToImageExpressionOffsetHeight/2;
    this->addChild(m_ImageFrame,2);
    m_ImageFrame->setPosition(Vec2(ImageFrameXpos,ImageFrameYpos)); 
}

void ImageExpressionContainer::setCurrentLavelImageExpressionContainer()
{
    std::string ExpressionImage  =  LevelsManager::getInstance()->getImageExpressionCurrentImage();
    setImageFrame(ExpressionImage);
}

void ImageExpressionContainer::setImageFrame(const std::string& imageframe)
{
    Sprite *pCurrentImage = Sprite::createWithSpriteFrameName(imageframe);
    pCurrentImage->setScale(core::Settings::getInstance()->ImageScaleFactor);
    m_ImageFrame->addChild(pCurrentImage,1);
    float contentSizeWidth = m_ImageFrame->getContentSize().width; 
    float contentSizeHeight = m_ImageFrame->getContentSize().height; 
    pCurrentImage->setPosition(contentSizeWidth/2,contentSizeHeight/2);
}

ImageExpressionContainer* ImageExpressionContainer::create()
{
        auto sprite = new ImageExpressionContainer;
        sprite->init();
        sprite->autorelease();
        return sprite;
} 