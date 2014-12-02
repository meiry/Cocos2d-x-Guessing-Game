//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "BonusContainer.h"
#include "VisibleRect.h"
#include "config/ConstAppDefine.h"
#include "Settings.h"
#include "ScoreContainer.h"




 
BonusContainer::BonusContainer(ScoreContainer* pScoreContainer) 
{
    BonusInterval =0;
    m_pScoreContainer = pScoreContainer;
    stopTouchesInBonusContainer = true;
}

BonusContainer::~BonusContainer() {}

BonusContainer* BonusContainer::create(ScoreContainer* pScoreContainer)
{
    BonusContainer* pSprite = new BonusContainer(pScoreContainer);

    if (pSprite->init())
    {
        pSprite->autorelease();

        Size winSize = Director::getInstance()->getWinSize();
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Rect visibleRect =  VisibleRect::getVisibleRect();
        float offsetWidth = pScoreContainer->getOffsetWidth();
        float width = visibleRect.size.width - (offsetWidth*2);
        float offsetHeight = pScoreContainer->getOffsetHeight();
        float height = visibleRect.size.height - (offsetHeight*2);
        pSprite->setTextureRect(Rect(0, 0,width,height));
		pSprite->setColor(BounsContainer_bk_color); 
		pSprite->setOpacity(150.0f);
        pSprite->setAnchorPoint(Vec2(0.0f,0.0f));
        pSprite->initOptions(width,height);
        pSprite->addEvents();
         
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}


Size BonusContainer::getBonusContainerSize()
{
    Size s;
    s.width = thisWidth;
    s.height = thisHeight;
    return s;
}

void BonusContainer::initOptions(float width,float height)
{
    thisWidth = width;
    thisHeight = height;
    Size thisSize = this->getBoundingBox().size;   
    setBonusSprite(pBonusTopRight);
    Size BonusSize = pBonusTopRight->getBoundingBox().size;
    float pBonusTopRightW = thisSize.width - BonusSize.width;
    float pBonusTopRightH = thisSize.height - BonusSize.height;
    pBonusTopRight->setPosition(pBonusTopRightW,pBonusTopRightH);
     
    setBonusSprite(pBonusTopRight);
    pBonusTopRight->setPosition(0.0f,pBonusTopRightH);
    
    setBonusSprite(pBonusButtomLeft);
    pBonusButtomLeft->setPosition(0.0f,0.0f);
    
    setBonusSprite(pBonusButtomRight);
    pBonusButtomRight->setPosition(pBonusTopRightW,0.0f);


    pDoneAndCloseButt = Sprite::createWithSpriteFrameName(sDoneAndClose_icon);
    pDoneAndCloseButt->retain();
	pDoneAndCloseButt->setTag(buttons_tags::DONEANDCLOSE);
    pDoneAndCloseButt->setScale(0.8f);
    pDoneAndCloseButt->setAnchorPoint(Vec2(0.5f,0.0f));
    pDoneAndCloseButt->setPosition(this->getBoundingBox().size.width / 2.0f,0.0f);
    this->addChild(pDoneAndCloseButt,1);
    pDoneAndCloseButt->setVisible(false);



    pBonusValueLabel = Label::createWithTTF("0" ,"fonts/Marker Felt.ttf",BonusValueLabel_fnt_size);
    pBonusValueLabel->retain();
    pBonusValueLabel->setColor(BonusValueLabel_bk_color);
    pBonusValueLabel->setAnchorPoint(Vec2(0.5f, 0.5f));	
	pBonusValueLabel->setPosition(Vec2(this->getBoundingBox().size.width / 2.0f, this->getBoundingBox().size.height / 2.0f));
    this->addChild(pBonusValueLabel,1);
     
}

void BonusContainer::setBonusSprite(Sprite* &pbonus)
{
    pbonus  = Sprite::createWithSpriteFrameName(sPresent_box_icon);
    pbonus->retain();
	pbonus->setTag(buttons_tags::BONUS);
    pbonus->setScale(0.8f);
    pbonus->setAnchorPoint(Vec2(0.0f,0.0f));
    this->addChild(pbonus,1);

}
void BonusContainer::addEvents()
{
    listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&]( Touch* touch,  Event* event)
    {   
        
        bool touched = false;
        if(!stopTouchesInBonusContainer)
        {
            Vec2 p = touch->getLocation();
            Rect rect = this->getBoundingBox();
            Vector<Node *> thisSelectionChildren = this->getChildren(); 
            for (auto iter = thisSelectionChildren.begin(); iter != thisSelectionChildren.end(); ++iter) 
            {
                Node *childNode = *iter;
                if(childNode->getTag() == DONEANDCLOSE)
                {
                    Point thisTouchPositionFontSelection = this->convertTouchToNodeSpace(touch);  
                    Sprite* DoneButton = static_cast<Sprite*>(*iter); 
                    if(DoneButton->getBoundingBox().containsPoint(thisTouchPositionFontSelection))
                    {

                        core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);                      
                        touched = true;
                        break;
                    }
                }
				if(childNode->getTag() == BONUS)
				{
					Point thisTouchPositionFontSelection = this->convertTouchToNodeSpace(touch);  
                    Sprite* DoneButton = static_cast<Sprite*>(*iter); 
                    if(DoneButton->getBoundingBox().containsPoint(thisTouchPositionFontSelection))
                    {

                        core::Settings::getInstance()->getSoundManager().playSoundEffect(SINGLE_CLICK_1);                      
                        touched = true;
                        break;
                    }
				}
            }
        }
        return touched;
        
    };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        if(!stopTouchesInBonusContainer)
        {
            BonusContainer::touchEvent(touch);
        }
    };
    AddEventListener();
     
}

void BonusContainer::RemoveEventListener()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
     
}
void BonusContainer::AddEventListener()
{
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}


void BonusContainer::touchEvent(Touch* touch)
{
    //CCLOG("touched BonusContainer");
    m_pScoreContainer->setPopupContainerInitPos(true);
    core::Settings::getInstance()->stopTouchesInMainLayer = false;
    stopTouchesInBonusContainer = false;
}
void BonusContainer::StartTimer()
{
	BonusInterval = 0; 
    int maxBonus = 50;
    //this->schedule(schedule_selector(BonusContainer::tick), 1.0f); 
    Vector<FiniteTimeAction *> allActions;
    auto t1 = CallFuncN::create( CC_CALLBACK_1(BonusContainer::BonusContainerIncreaseBonusAnimCallback,this,maxBonus));
    t1->setTag(CALL_FUNC_N_INCREASEBONUS);
    auto t2 = DelayTime::create(0.02f);
    auto targetedAction1 = TargetedAction::create(this, t1);
    auto targetedAction2 = TargetedAction::create(this, t2);
    allActions.pushBack(targetedAction1);
    allActions.pushBack(targetedAction2);
    auto seq = Sequence::create(allActions);
    seq->setTag(SEQ);
    auto always = RepeatForever::create(seq);
    always->setTag(REPEAT_FOREVER_ACTION);
  	this->runAction(always);

}

void BonusContainer::BonusContainerIncreaseBonusAnimCallback(Node* sender,int maxBonus)
{
    if(this->BonusInterval > maxBonus)
    {
        this->BonusInterval-=1;
        this->StopTimer();
    }
    else if(this->BonusInterval <= maxBonus)
    {
        this->setBonusPointsInToLabel(BonusInterval);
        if(this->BonusInterval<=maxBonus)
        {
            this->BonusInterval+=1;
        }
    }
}

void BonusContainer::StopTimer()
{
	
     this->stopActionByTag(CALL_FUNC_N_INCREASEBONUS);
     this->stopActionByTag(REPEAT_FOREVER_ACTION);
     this->stopActionByTag(SEQ);
     m_pScoreContainer->invokeBonusToScoreAnime(BonusInterval);
     this->BonusInterval = 0;
}

 
float BonusContainer::getBonusInterval()
{
	return BonusInterval;
}
void BonusContainer::setBonusPointsInToLabel(float BonusPoints)
{
    unsigned int points;
    points = static_cast<int>(BonusPoints);
    std::string sBonusPoints = String::createWithFormat("%d",points)->getCString();     
    pBonusValueLabel->setString(sBonusPoints);  
}

void BonusContainer::invokeBonusPointsInToLabelAnim()
{
   
    StartTimer();

}