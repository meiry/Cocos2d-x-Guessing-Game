//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "ScoreContainer.h"
#include "Settings.h"
#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "config/ConstAppDefine.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "BonusContainer.h"


float ScoreContainer::getOffsetHeight()
{
   float h =  (40.0f / 100.0f) * VisibleRect::getVisibleRect().size.height;
   return h;
}

float ScoreContainer::getOffsetWidth()
{
   float w = (20.0f / 100.0f) * VisibleRect::getVisibleRect().size.width;
   return w;
}


void ScoreContainer::invokeBonusToScoreAnime(int BonusInterval)
{
    
    BonusToScore = 0;
    Vector<FiniteTimeAction *> allActions;
    auto t1 = CallFuncN::create( CC_CALLBACK_1(ScoreContainer::BonusToScoreIncreaseAnimCallback,this,BonusInterval));
    t1->setTag(SCORECONTAINER_CALL_FUNC_N_INCREASEBONUS);
    auto t2 = DelayTime::create(0.02f);
    auto targetedAction1 = TargetedAction::create(this, t1);
    auto targetedAction2 = TargetedAction::create(this, t2);
    allActions.pushBack(targetedAction1);
    allActions.pushBack(targetedAction2);
    auto seq = Sequence::create(allActions);
    seq->setTag(SCORECONTAINER_SEQ);
    auto always = RepeatForever::create(seq);
    always->setTag(SCORECONTAINER_REPEAT_FOREVER_ACTION);
  	this->runAction(always);
}

void ScoreContainer::BonusToScoreIncreaseAnimCallback(Node* sender,int iBonusInterval)
{
    
    if(this->BonusToScore >= iBonusInterval)
    {
        this->stopActionByTag(SCORECONTAINER_REPEAT_FOREVER_ACTION);
        this->stopActionByTag(SCORECONTAINER_CALL_FUNC_N_INCREASEBONUS); 
        this->stopActionByTag(SCORECONTAINER_SEQ);
        this->BonusToScore = 0;
        pBonusContainer->stopTouchesInBonusContainer = false;
        pBonusContainer->pDoneAndCloseButt->setVisible(true);
    }
    else if(this->BonusToScore < (iBonusInterval))
    {
         
         this->increasePoints(1); 
         this->BonusToScore+=1;
    }
    
}

void  ScoreContainer::setPopupContainerInitPos(bool fromPopup)
{
    ProgressBarValueLabelWorldSpaceVec = star->convertToWorldSpace(pProgressBarValueLabel->getPosition());
    float width = this->getBoundingBox().size.width - pBonusContainer->getBoundingBox().size.width;
    pBonusContainer->setPosition(ProgressBarValueLabelWorldSpaceVec);
    pBonusContainer->setScale(0.0f);
    if(fromPopup)
    {
        setProgress(0);
    }
}


void ScoreContainer::setBonus()
{
	
	pBonusContainer = BonusContainer::create(this);
    setPopupContainerInitPos(false);
 	m_Parent->addChild(pBonusContainer,94);
    
}
 
void ScoreContainer::invokeBonusPopupAnimation()
{
    
    
    core::Settings::getInstance()->getSoundManager().playSoundEffect(BONUS_WINDOWS_POPUP);
    Size BonusSize =  pBonusContainer->getBonusContainerSize();
    
    float width = this->getBoundingBox().size.width - BonusSize.width;
    
    float offsetWidth = getOffsetWidth();
    float spriteW =  (width/2);
	//pBonusContainer->setPosition(width/2,v.y/2);
    Vector<FiniteTimeAction *> allActions;
    auto t1 = MoveTo::create( 0.5, Vec2(spriteW,ProgressBarValueLabelWorldSpaceVec.y/2));
    auto t2 = ScaleTo::create(0.5f,1.0f);
    auto targetedAction1 = TargetedAction::create(pBonusContainer, t1);
    auto targetedAction2 = TargetedAction::create(pBonusContainer, t2);
    allActions.pushBack(targetedAction1);
    allActions.pushBack(targetedAction2);    
    auto actionSpawn = Spawn::create(allActions);
    
     auto action = Sequence::create(actionSpawn,
        CallFuncN::create( CC_CALLBACK_1(ScoreContainer::BonusContainerDoneAnimCallback,this)),
        nullptr); 

	pBonusContainer->runAction(action);
}


void ScoreContainer::BonusContainerDoneAnimCallback(Node* sender)
{
    
    ((BonusContainer*)sender)->invokeBonusPointsInToLabelAnim();
}


ScoreContainer::ScoreContainer(HelloWorld* const & parent) : isSoundOff(false)
{
    visibleSize = Director::getInstance()->getVisibleSize();
	m_Parent = parent;
    
}

ScoreContainer::~ScoreContainer()
{

}

bool ScoreContainer::init()
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Sprite::init() )
    {
        return false;
    }
    
    progressAccumulator =0;
    pointAccumulator=0; 
	return true;
}

void ScoreContainer::setSpriteExtra()
{
    WidthSideOffSet = 10.0f;
	sizeContent = this->getContentSize();
	//setBackButtonSprite();
    setSoundButtonSprite();
    setEmailButtonSprite();
    setTrophyButtonSprite();
    setConfigButtonSprite();
    setPointsProgreesSprite();
    setLevelsProgreesSprite();
	setBonus();
}

void ScoreContainer::setLevelsProgreesSprite()
{	
	StarToBarOffset = 40.0f;
    star = Sprite::createWithSpriteFrameName(sStarFull_icon);
	star->retain();
    star->setScale(0.8f);
    star->setAnchorPoint(Vec2(0.0f,0.0f));
    Size starBoundingBoxSize = star->getBoundingBox().size;
    this->addChild(star,3);

    //create Level numbers 
    
    pLevelNumberValueNumberLabel = Label::createWithTTF("",
                                                "fonts/Marker Felt.ttf",LevelNumberValueLabel_fnt_size);
    pLevelNumberValueNumberLabel->retain();
    pLevelNumberValueNumberLabel->setColor(LevelNumberValueLabel_bk_color);
    pLevelNumberValueNumberLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    int levelNo = ScoreManager::getInstance()->getLevelNumberAccumulator();  
    setLevelNumber(levelNo);
     
    
    //create Progressbar frame
    pProgressBarFrame = setProgressBarFrame();
    float ProgressBarFrameHeight = pProgressBarFrame->getBoundingBox().size.height;
    pProgressBarFrame->setPosition(Vec2(star->getBoundingBox().size.width-StarToBarOffset,
                                        (star->getBoundingBox().size.height/2)-(ProgressBarFrameHeight/2)));
    
    Sprite* ProgressTimerSprite = Sprite::create();
    ProgressTimerSprite->setTextureRect(Rect(0, 0,200.0f ,33.0f));
    ProgressTimerSprite->setColor(ProgressTimerSprite_bk_color); 
	ProgressTimerSprite->retain();

    pProgressBarTimer = ProgressTimer::create(ProgressTimerSprite);
	pProgressBarTimer->retain();
    pProgressBarTimer->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the left since the midpoint is 0 for the x
    pProgressBarTimer->setMidpoint(Vec2(0.0f,0.0f));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    pProgressBarTimer->setBarChangeRate(Vec2(1.0f,0.0f));
    
    
    pProgressBarFrame->addChild(pProgressBarTimer,1);
    Size progressBarFrameSize = pProgressBarFrame->getContentSize();
    pProgressBarTimer->setPosition(Vec2(progressBarFrameSize.width/2,progressBarFrameSize.height/2));
    pProgressBarTimer->setPercentage(0);

	//Level progress font
	pProgressBarValueLabel = Label::createWithTTF("0/100" ,"fonts/Marker Felt.ttf",ProgressBarValueLabel_fnt_size);
    pProgressBarValueLabel->retain();
    pProgressBarValueLabel->setColor(ProgressBarValueLabel_bk_color);
    pProgressBarValueLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	//pProgressBarContainerNode->addChild(pProgressBarValueLabel,4);
	pProgressBarValueLabel->setPosition(Vec2(pProgressBarFrame->getBoundingBox().size.width / 2.0f, 
        pProgressBarFrame->getBoundingBox().size.height / 2.0f));
    //star->addChild(pProgressBarValueLabel,3);

    pProgressBarFrame->addChild(pProgressBarValueLabel,1);
	//set the node that holds all of this position
	Size barSize = pProgressBarFrame->getContentSize();
	Size stSize = star->getContentSize();
    Size stBoundingBoxSize = star->getBoundingBox().size;
	 
	//total size of the widget 
	float totalSizeWidth = stSize.width + (barSize.width-StarToBarOffset);
	float totalSizeHight = stSize.height;
	//total container width
    //set global pos 
    Vec2 CoinsPos = pCoins->convertToWorldSpace(pPointsCountFrame->getPosition());
    float PointsCountFrameBoundingBoxWidth = pPointsCountFrame->getBoundingBox().size.width;
    ProgressBarPosX =  CoinsPos.x+PointsCountFrameBoundingBoxWidth;   
	ProgressBarPosY =  (sizeContent.height/2) - (stBoundingBoxSize.height/2);
    star->addChild(pProgressBarFrame,-1);
    star->setPosition(ProgressBarPosX,ProgressBarPosY);
    star->addChild(pLevelNumberValueNumberLabel,1);    
    pLevelNumberValueNumberLabel->setPosition(stBoundingBoxSize.width/2,barSize.height/2);
}

Sprite* ScoreContainer::setProgressBarFrame()
{
#if SET_PROGRESSBARFRAME_AS_IMG 
    Sprite* ptmpProgressBarFrame = Sprite::createWithSpriteFrameName(sStatus_bar_container_icon);
     
#else
    Sprite* ptmpProgressBarFrame = Sprite::create();
    ptmpProgressBarFrame->setTextureRect(Rect(0, 0,200.0f ,33.0f));
    ptmpProgressBarFrame->setColor(ProgressBarFrame_bk_color); 
#endif
  	ptmpProgressBarFrame->retain();    
    ptmpProgressBarFrame->setAnchorPoint(Vec2(0.0f,0.0f));
    return ptmpProgressBarFrame;
}

 
 
void ScoreContainer::setPointsProgreesSprite()
{
    CoinsToBarOffset = core::Settings::getInstance()->CoinsFromConfigButtunsOffset;
     
    pCoins = Sprite::createWithSpriteFrameName(sCoins_icon);
    pCoins->retain();
	pCoins->setTag(buttons_tags::COINS_IMG_BT);
    pCoins->setScale(0.8f);
    Size coinsBoundingBoxSize = pCoins->getBoundingBox().size;
    pCoins->setAnchorPoint(Vec2(0.0f,0.0f));
	 
    this->addChild(pCoins,2);
    
     
    pPointsCountFrame = setPointsCountFrame();
    float totalSizeWidth = coinsBoundingBoxSize.width + (pPointsCountFrame->getBoundingBox().size.width/2);
     //set global pos 
    //PointsContainerPosX =  ProgressBarPosX - totalSizeWidth-WidthSideOffSet;   
	PointsContainerPosY =  (sizeContent.height/2) - (coinsBoundingBoxSize.height/2); 

    //pPointsContainerNode->addChild(pPointsCountFrame,2);
    pCoins->addChild(pPointsCountFrame,-1);
    PointsContainerPosX = pConfigButton->getPositionX()+pConfigButton->getBoundingBox().size.width+CoinsToBarOffset;//star->getPositionX() - totalSizeWidth;
    pPointsCountFrame->setPosition(Vec2(coinsBoundingBoxSize.width/2,
                                        coinsBoundingBoxSize.height/2));
    
    pCoins->setPosition(PointsContainerPosX,PointsContainerPosY);
    CoinsLabelWorldSpaceVec = this->convertToWorldSpace(pCoins->getPosition());
    
    
    std::string sPointsAccumulator = "0";//String::createWithFormat("%d",ScoreManager::getInstance()->getPointsAccumulator())->getCString();
   
    //Level progress font
	pPointCountValueLabel = Label::createWithTTF(sPointsAccumulator,"fonts/Marker Felt.ttf", PointCountValueLabel_fnt_size);
    pPointsCountFrame->addChild(pPointCountValueLabel,3);
    pPointCountValueLabel->retain();
    pPointCountValueLabel->setColor(PointCountValueLabel_bk_color);
    pPointCountValueLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    Size PointsCountFrameSize = pPointsCountFrame->getBoundingBox().size;
	pPointCountValueLabel->setPosition(Vec2(PointsCountFrameSize.width / 2.0f, 
                                        PointsCountFrameSize.height / 2.0f));
    setPointCountValueLabelValue(ScoreManager::getInstance()->getPointsAccumulator());


}

void ScoreContainer::setPointCountValueLabelValue(int iPointsAccumulator)
{
    setPoints(iPointsAccumulator);
}

Sprite* ScoreContainer::setPointsCountFrame()
{
#if SET_POINTSCOUNTFRAME_AS_IMG 
    pPointsCountFrame = Sprite::createWithSpriteFrameName(sPoints_bar_container_icon);
#else
    Sprite* ptmpPointsCountFrame = Sprite::create();
    ptmpPointsCountFrame->setTextureRect(Rect(0, 0,150.0f ,33.0f));
    ptmpPointsCountFrame->setColor(PointsCountFrame_bk_color); 
#endif
  	ptmpPointsCountFrame->retain();
    ptmpPointsCountFrame->setTag(buttons_tags::COINS_COUNT_FRAME);
    ptmpPointsCountFrame->setAnchorPoint(Vec2(0.0f,0.5f));
    return ptmpPointsCountFrame;
}
//sound helper function 
void ScoreContainer::setSoundButtonSpriteFrame(bool state)
{
   
    SpriteFrame* pSpriteFrame = NULL;
    auto cache = SpriteFrameCache::getInstance();
    if(!isSoundOff)
    {
        isSoundOff = true;
		core::Settings::getInstance()->getSoundManager().setSoundOffState(isSoundOff);
        pSpriteFrame = cache->spriteFrameByName(sSound_off_icon);
        pSoundButten->setSpriteFrame(pSpriteFrame);
    }
    else
    {
        pSpriteFrame = cache->spriteFrameByName(sSound_On_icon);
        pSoundButten->setSpriteFrame(pSpriteFrame);
        isSoundOff = false;
		core::Settings::getInstance()->getSoundManager().setSoundOffState(isSoundOff);
    }
}

void ScoreContainer::setConfigButtonSprite()
{
    pConfigButton = Sprite::createWithSpriteFrameName(sConfiguration_icon);
    pConfigButton->retain();
    pConfigButton->setTag(buttons_tags::CONFIG_BT);
    pConfigButton->setScale(0.5);
    Size ConfigBtSize = pConfigButton->getBoundingBox().size;
    Size ConfigBoundingBoxSize = pConfigButton->getBoundingBox().size;
	pConfigButton->setAnchorPoint(Vec2(0.0f,0.0f));
	this->addChild(pConfigButton,3);
    ConfigButtonPosX =  TrophyButtenPosX + pTrophyButten->getBoundingBox().size.width;
	ConfigButtonPosY =  (sizeContent.height/2)- (ConfigBoundingBoxSize.height/2);
	pConfigButton->setPosition(ConfigButtonPosX,ConfigButtonPosY);

}

void ScoreContainer::setSoundButtonSprite()
{
    pSoundButten = Sprite::createWithSpriteFrameName(sSound_On_icon); //Sound_On_100.png
	pSoundButten->retain();
    pSoundButten->setTag(buttons_tags::SOUND_BT);
    pSoundButten->setScale(0.5);
    Size backBtSize = pSoundButten->getBoundingBox().size;
    Size backBtBoundingBoxSize = pSoundButten->getBoundingBox().size;
	pSoundButten->setAnchorPoint(Vec2(0.0f,0.0f));
	this->addChild(pSoundButten,3);
	SoundButtenPosX =  (0.0f+WidthSideOffSet);
	SoundButtenPosY =  (sizeContent.height/2)- (backBtBoundingBoxSize.height/2);
	pSoundButten->setPosition(SoundButtenPosX,SoundButtenPosY);

    //get the prev sound config from file 
    bool b = UserDefault::getInstance()->getBoolForKey("sound");
    if (b)
    {
        setSoundButtonSpriteFrame(b);
    }
    
}

void ScoreContainer::setEmailButtonSprite()
{
    pEmailButten = Sprite::createWithSpriteFrameName(sSenvelope_email_icon);
	pEmailButten->retain();
    pEmailButten->setScale(0.5);
    pEmailButten->setTag(buttons_tags::EMAIL_BT);
    Size backBtSize = pEmailButten->getBoundingBox().size;
    Size backBtBoundingBoxSize = pEmailButten->getBoundingBox().size;
	pEmailButten->setAnchorPoint(Vec2(0.0f,0.0f));
	this->addChild(pEmailButten,3);
    EmailButtenPosX =  (0.0f+WidthSideOffSet) + pSoundButten->getPositionX() + pSoundButten->getBoundingBox().size.width;
	EmailButtenPosY =  (sizeContent.height/2)- (backBtBoundingBoxSize.height/2);
	pEmailButten->setPosition(EmailButtenPosX,EmailButtenPosY);
}

void ScoreContainer::setTrophyButtonSprite()
{
    pTrophyButten = Sprite::createWithSpriteFrameName(sTrophy_icon);
	pTrophyButten->retain();
    pTrophyButten->setScale(0.5);
    pTrophyButten->setTag(buttons_tags::TROPHY_BT);
    Size backBtSize = pTrophyButten->getBoundingBox().size;
    Size backBtBoundingBoxSize = pTrophyButten->getBoundingBox().size;
	pTrophyButten->setAnchorPoint(Vec2(0.0f,0.0f));
	this->addChild(pTrophyButten,3);
	TrophyButtenPosX =  (0.0f+WidthSideOffSet)+ pEmailButten->getPositionX() + pEmailButten->getBoundingBox().size.width;;
	TrophyButtenPosY =  (sizeContent.height/2)- (backBtBoundingBoxSize.height/2);
	pTrophyButten->setPosition(TrophyButtenPosX,TrophyButtenPosY);
}

void ScoreContainer::setBackButtonSprite()
{
	pBackButten = Sprite::createWithSpriteFrameName(sBack_bn_icon);
	pBackButten->retain();
	pBackButten->setTag(buttons_tags::BACK_BT);
    Size backBtSize = pBackButten->getBoundingBox().size;
    Size backBtBoundingBoxSize = pBackButten->getBoundingBox().size;
	pBackButten->setAnchorPoint(Vec2(0.0f,0.0f));
	this->addChild(pBackButten,3);
	BackButtenPosX =  (0.0f+WidthSideOffSet);
	BackButtenPosY =  (sizeContent.height/2)- (backBtBoundingBoxSize.height/2);
	pBackButten->setPosition(BackButtenPosX,BackButtenPosY);

}

void ScoreContainer::setPoints(int p)
{
    pointAccumulator =p;
    pPointCountValueLabel->setString(String::createWithFormat("%d",p)->getCString());  
}

int ScoreContainer::getPoints()
{
    
    return pointAccumulator; 
}

void ScoreContainer::setProgress(int p)
{
    pProgressBarTimer->setPercentage(p);
    pProgressBarValueLabel->setString(String::createWithFormat("%d/100",p)->getCString());  
    if(p == 100)
    {
         
        core::Settings::getInstance()->stopTouchesInMainLayer = true;
        invokeBonusPopupAnimation();
    }
}

void ScoreContainer::setLevelNumber(int l)
{
    pLevelNumberValueNumberLabel->setString(String::createWithFormat("%d",l)->getCString());
    levelNumberAccumulator = l;
}

int ScoreContainer::getProgress()
{
   return  progressAccumulator ;
     
}

void ScoreContainer::decreasePoints(int p)
{
    pointAccumulator = pointAccumulator - p;
    setPoints(pointAccumulator);
}

void ScoreContainer::decreaseProgress(int p)
{
    progressAccumulator = progressAccumulator - p;
    setProgress(progressAccumulator);
}

void ScoreContainer::increasePoints(int p)
{
    if(p==0)
    {
        pointAccumulator =0;
    }
    else
    {
        pointAccumulator = pointAccumulator + p;
    }
    setPoints(pointAccumulator);
}

void ScoreContainer::increaseProgress(int p)
{   
	if(p==0)
	{
		progressAccumulator =0;
	}
	else
	{
		progressAccumulator = progressAccumulator + p;
	}
    setProgress(progressAccumulator);
}

void ScoreContainer::increaseLevelNumber(int l)
{
    if(l==0)
	{
		levelNumberAccumulator =0;
	}
    else
    {
        levelNumberAccumulator = levelNumberAccumulator + l;
    }
    setLevelNumber(levelNumberAccumulator);
}

ScoreContainer* ScoreContainer::create(HelloWorld* const & parent)
{
        auto sprite = new ScoreContainer(parent);
        sprite->init();
        sprite->autorelease();
        return sprite;
} 

//getters 
Sprite* ScoreContainer::getCoinsSprite()
{
     return pCoins;
}
Sprite* ScoreContainer::getPointsCountFrameSprite()
{
    return pPointsCountFrame;
}