//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "SolutionContainer.h"
#include "SignFactory.h"
#include "LevelsManager.h"
#include "UT.h"
#include "Sign.h"
#include "SimpleAudioEngine.h"
#include "config/ConstAppDefine.h"
#include "HelloWorldScene.h"
 #include "ScoreManager.h"
#include "Settings.h"
 



inline float getNextButtenPositionY(Sprite* &NextButton)
{
    float NextButtonTopOffset = 5.0f;
    float NextBheightHalf =  NextButton->getBoundingBox().size.height/2;
    float pNextButtenPositionY =  NextButton->getPositionY() + NextBheightHalf +NextButtonTopOffset;
    return pNextButtenPositionY;
}



bool SolutionContainer::bSetMatch = false;
int  SolutionContainer::iCoinsToScoreCount = 0;
int  SolutionContainer::iNumberOfCoinsCount = 0;
int SolutionContainer::iHinSignLettersCount =0;
int SolutionContainer::iNumberOfBlankSignLettersCount =0;
SolutionContainer::SolutionContainer(HelloWorld* const & parent):numberOfLettersOnlyInPlace(0),
                                       numberOfMatchedLatters(0),
                                       numberOfFontsPlacedIntoHolders(0),
                                       gameInterval(0.0f),
                                       iTouchCounterInLevel(0)
{
     pUT = new UT();
     m_Parent = parent;
    
     
     
      
}

SolutionContainer::~SolutionContainer()
{
    for(std::vector<ParticleSystemQuad*>::size_type i = 0; i != m_pStarParticlesEmitterVector.size(); i++) {
       CC_SAFE_RELEASE( m_pStarParticlesEmitterVector[i]);
    }
    
}

bool SolutionContainer::init()
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Sprite::init() )
    {
        return false;
    }
   
    visibleSize = Director::getInstance()->getVisibleSize();
    
 	return true;
}


void SolutionContainer::createNextButton()
{
    pNextButten = Sprite::createWithSpriteFrameName(sNext_bt);
    pNextButten->retain();
	pNextButten->setTag(buttons_tags::NEXT_BT);
    float gesturePosX = m_sizeContent.width/2;
    float gesturePosY = this->getPositionY()-pNextButten->getBoundingBox().size.height;//this->getPositionY() + (m_sizeContent.height);
    pNextButten->setPosition(gesturePosX,gesturePosY);
    pNextButten->setVisible(false);
}

void SolutionContainer::createNoNoOneFinger()
{
     pNoNoOneFinger= Sprite::createWithSpriteFrameName(sNoNoFinger_bt);
     float gesturePosY = this->getPositionY() + (m_sizeContent.height);
     float gesturePosX = m_sizeContent.width/2;
     pNoNoOneFinger->setPosition(gesturePosX,gesturePosY);
     m_Parent->addChild(pNoNoOneFinger,91);
     pNoNoOneFinger->setVisible(false);
}

void SolutionContainer::createClock()
{
    pClock = Sprite::createWithSpriteFrameName(sClock_icone);
    pClock->setAnchorPoint(Vec2(0.0f,0.0f));
    pClock->retain();
    pClock->setScale(0.4f);
}

void SolutionContainer::createYesThumbUp()
{
    pYesThumbUp = Sprite::createWithSpriteFrameName(sYesYesFinger_bt);
    float gesturePosY = this->getPositionY() + (m_sizeContent.height);
    float gesturePosX = m_sizeContent.width/2;
    pYesThumbUp->setPosition(gesturePosX,gesturePosY);
    m_Parent->addChild(pYesThumbUp,91);
    pYesThumbUp->setVisible(false);
}

void SolutionContainer::setSpriteExtra()
{
    //visibleSize = Director::getInstance()->getVisibleSize();
    //Size m_sizeContent = this->getBoundingBox().size;
    //pClock = Sprite::createWithSpriteFrameName(sClock_icone);
    //pClock->setAnchorPoint(Vec2(0.0f,0.0f));
    //pClock->retain();
    //pClock->setScale(0.4f);
    //pYesThumbUp = Sprite::createWithSpriteFrameName(sYesYesFinger_bt);
    //pNoNoOneFinger= Sprite::createWithSpriteFrameName(sNoNoFinger_bt);
    m_sizeContent = this->getBoundingBox().size;
    createNextButton();
    createNoNoOneFinger();
	//pNextButten = Sprite::createWithSpriteFrameName(sNext_bt);
    //pNextButten->retain();
	//pNextButten->setTag(buttons_tags::NEXT_BT);
    //gesturePosY = this->getPositionY() + (m_sizeContent.height);
    //gesturePosX = m_sizeContent.width/2;
    //pYesThumbUp->setPosition(gesturePosX,gesturePosY);
    //pNoNoOneFinger->setPosition(gesturePosX,gesturePosY);
	//pNextButten->setPosition(gesturePosX,gesturePosY-(m_sizeContent.height));
   
    //m_Parent->addChild(pYesThumbUp,91);
    //m_Parent->addChild(pNoNoOneFinger,91);	
	//pNextButten->setVisible(false);
   // pNoNoOneFinger->setVisible(false);
    //pYesThumbUp->setVisible(false);
    
   
    m_starParticlesPosY = this->getPositionY() + (m_sizeContent.height);
    m_starParticlesPosX = m_sizeContent.width/2;

    setLevelTimeIntervalContainer();
    setLevelNumberOfMoves();
    setScoreCoinsContainer();

	
   
}



void SolutionContainer::InnerCleanPreviousLevel()
{
  
   stopParticalse();
   if(this->m_Parent->getChildByTag(buttons_tags::NEXT_BT) !=NULL)
    {
        this->m_Parent->removeChildByTag(buttons_tags::NEXT_BT);
   }
   setNextLevelButtonVisible(false);
   //ThumbUpAnimation(false);
   signPlacmentRowsVec.clear();
   pLevelNumberOfMovesIntervalLabel->setVisible(false);
   pLevelTimeIntervalContainer->setVisible(false);
   pScoreCoinsLabel->setVisible(false);
   iTouchCounterInLevel = 0;
   bSetMatch = false;
   m_LevelDataHolder.resetAll();
   numberOfMatchedLatters=0;
   numberOfLettersOnlyInPlace=0;   
   numberOfFontsPlacedIntoHolders =0;
   iCoinsToScoreCount = 0;
   iNumberOfCoinsCount =0;
  
  
}
void SolutionContainer::cleanPreviousLevel()
{
    InnerCleanPreviousLevel(); 
	invokeCoinsToScoreViewAnimation();
  
}

void SolutionContainer::invokeCoinsToScoreViewAnimation()
{
    
    Vec2 vec = m_Parent->pScoreContainer->CoinsLabelWorldSpaceVec;
    Vector<Node*> OnlyCoinsContainertChildren = this->pOnlyCoinsContainer->getChildren();
	iNumberOfCoinsCount = OnlyCoinsContainertChildren.size();
	int counter =1;
	float speedDoration = 0.0;
	if(iNumberOfCoinsCount <=2)
	{
		speedDoration = 0.1f;
	}
	else if(iNumberOfCoinsCount >2)
	{
		speedDoration = 0.1f;
	}
    int innerLoopCounter = 0;
    for (auto iter = OnlyCoinsContainertChildren.begin(); iter != OnlyCoinsContainertChildren.end(); ++iter) 
    {
        Sign* pCoin = static_cast<Sign*>(*iter); 
        if(innerLoopCounter==0)
        {
            CoinsPosVec = m_Parent->pScoreContainer->convertToWorldSpace(m_Parent->pScoreContainer->pCoins->getPosition());
            Vec2 dCoinsPosVec = pScoreCoinsContainer->getPosition();
            vec.x=0;//vec.x*-1;
            vec.y=vec.y-dCoinsPosVec.y;
          
            innerLoopCounter++;
        }

       // Vec2 vvv= pCoin->getPosition();
        if(pCoin->getTag() == COIN)
        {
             auto action1 = Sequence::create(
                     MoveTo::create(speedDoration * counter,vec),
                    // DelayTime::create(1.0f),
                     CallFunc::create( std::bind(&SolutionContainer::CoinsToScoreDoneAnimCallback,
                                                                                            this,
                                                                                            pCoin)),
                    //RemoveSelf::create(),
                    NULL);


             pCoin->runAction(action1);


         
			 counter++;
        }
    }
   
}

void SolutionContainer::CoinsToScoreDoneAnimCallback(Node* sender)
{
    std::string signName = ((Sign*)(sender))->getName();
    log("name:%s,%d,%d,%f",signName.c_str(),
            this->iNumberOfCoinsCount,
            this->iCoinsToScoreCount,
            sender->getPositionY());
    pOnlyCoinsContainer->removeChild(sender,true);
    sender->release();
    ScoreManager::getInstance()->setScoring(1);
    this->iCoinsToScoreCount++;
    if(this->iNumberOfCoinsCount==this->iCoinsToScoreCount)
	{
		// log("iNumberOfCoinsCount == iCoinsToScoreCount, %s,%f",sender->getName().c_str(),currentY);
        ScoreManager::getInstance()->setPercentage(); 
         
	 
           
	}
}

void SolutionContainer::CoinsToScoreViewAnimationCallback(Node* sender)
{
    
    //log("%d,%d",this->iNumberOfCoinsCount,this->iCoinsToScoreCount);
    float currentY = sender->getPositionY();
    log("%f,%f,sender:%s",currentY,this->CoinsPosVec.y,sender->getName().c_str());
    if(currentY == this->CoinsPosVec.y)
    {
        ScoreManager::getInstance()->setScoring(1);
        this->iCoinsToScoreCount++;
        if(sender!=NULL)
        {
           // log("%s,%f",sender->getName().c_str(),currentY);
           sender->stopAllActions();            
           pOnlyCoinsContainer->removeChild(sender,true);
           sender->release();
        }
        if(this->iNumberOfCoinsCount==this->iCoinsToScoreCount)
	    {
		   // log("iNumberOfCoinsCount == iCoinsToScoreCount, %s,%f",sender->getName().c_str(),currentY);
            ScoreManager::getInstance()->setPercentage();             
		    this->removeCoinsContent();
         
	    }
    }
	 
}

//calculate the string middle pos
float SolutionContainer::calculateXposForString(const std::string& str)
{
    float xSignPos = 0;
    float signWidth = SignFactory::getInstance()->getScalledLatterWidth();
    float LatterSidesOffSet = signWidth/10;
    //calculate middle width 
   
    int solutionStrSize =  pUT->split(str,',').size();
    int isStrOddNumber = solutionStrSize % 2;
    if(isStrOddNumber == 1) //TODO we can do it 1 if 
    {
        //get the middle elemet
        int solutionStrSizehalf = solutionStrSize/2;
        //int middelElm = (solutionStrSizehalf) +1;
        //half of string array * latter width + latter offset + half of latter if its OddNumber
        float totalSizeOfHalfLatters = (solutionStrSizehalf * (signWidth + LatterSidesOffSet))+ (signWidth/2);
        //half of screen
        float visibleSizeWidthHalf = (visibleSize.width / 2);
        //set the init x position of the latters holdders
        xSignPos = visibleSizeWidthHalf - totalSizeOfHalfLatters;
         
    }
    else
    {
        //devide to 2 the string 
        int solutionStrSizehalf = solutionStrSize/2;
        //half of string array * latter width + latter offset
        float totalSizeOfHalfLatters = (solutionStrSizehalf * (signWidth + LatterSidesOffSet));
        //half of screen
        float visibleSizeWidthHalf = (visibleSize.width / 2);
        //set the init x position of the latters holdders
        xSignPos = visibleSizeWidthHalf - totalSizeOfHalfLatters;
    }

    return xSignPos;
}
//Blank Sign handller
//place each blank sign in the currect place
void SolutionContainer::placeStringIn(const float xpos,
                                      const float ypos,
                                      const float factor,
                                      const int strCounter,
                                      const std::vector<std::string>& strLineOfChrsVec)
{
    float xSignPos = xpos; 
    float ySignPos = ypos;
    float latterScaleFactor = factor;
    Size size = SignFactory::getInstance()->getLatterScalledSize();
    float signWidth = size.width;
    float LatterSidesOffSet = signWidth/10;
    std::vector<Node* > lineVec;
    
    //position all the latters 
    for(int i=0;i<strLineOfChrsVec.size();i++)
    {
        //keep the index of the sign's from the master level vector
        int index = i + strCounter;
        Sign* pSign =   LevelsManager::getInstance()->getSolutionSignLettersVecIndex(index);
        
        //check if its space / sperator 
        if(pSign->getTag() == sign_tags::LETTER_SIGH )
        {
            pSign->setPosition(xSignPos,ySignPos);
            pUT->setSignScalefactor(pSign);
            //pSign->setScale(latterScaleFactor);
            pSign->setIsEmpty(true);
            //CCLOG("%s",pSign->getLatter().c_str());
            this->addChild(pSign,1); 
			lineVec.push_back(pSign);
            //count how meny letters are in place without spaces and without line breaks
            numberOfLettersOnlyInPlace++;
            iNumberOfBlankSignLettersCount++;
        }
        //calculate the X position 
        xSignPos+=signWidth+LatterSidesOffSet;
		//represent the rows in the screen 
		
    }
	signPlacmentRowsVec.push_back(lineVec);
}

/*
    set up the blank Sign's
*/
void SolutionContainer::setCurrentLavelSolutionContainer()
{
    
	setupParticles();
    //start level timer 
    StartTimer();
    //get the string we will work with 
    std::string solutionStr = LevelsManager::getInstance()->getSolutionLettersCurrentString();
    float latterScaleFactor =   SignFactory::getInstance()->getLatterScaleFactor();
    Size size = SignFactory::getInstance()->getLatterScalledSize();
    float LatterSidesOffSet = size.width/10;
    
    float offsetFromButtom = this->getContentSize().height - (size.height + LatterSidesOffSet) ;
    //split the string to find line breaks 
    std::vector<std::string> stringsVec = pUT->split(solutionStr,",|,");
    int strCounter = 0;
    iNumberOfBlankSignLettersCount =0;
    //the result of the split will be calculated to be placed on sprite
    for (auto & element : stringsVec) {
          float xPos = calculateXposForString(element);
          std::vector<std::string> elementVec = pUT->split(element,',');
          placeStringIn(xPos,
                        offsetFromButtom,
                        latterScaleFactor,
                        strCounter,
                        elementVec);
          //calculate Y from top to buttom 
          offsetFromButtom-=size.height + LatterSidesOffSet;
          strCounter += elementVec.size()+1;
    }
    
    LevelsManager::getInstance()->PostActionDispatcher(LETTERS_ANIM_SCALE_HINT);  
}

 // invoke short hint for N time 
void SolutionContainer::setPostActionSulotionHint()
{
     core::Settings::getInstance()->stopTouchesInMainLayer = true;
	 setSignLettersIntoBlankSignsHint();
}

void SolutionContainer::setSignLettersIntoBlankSignsHint()
{
     //iterate view all sulotion blank signs 
    iHinSignLettersCount =0;
    float scaleDelayFactor = SignLettersIntoBlankSignsHint_ScaleUpAnimInitDelayFactor;
    float scaleInitDelay = SignLettersIntoBlankSignsHint_ScaleUpAnimInitDelay;
	for(auto iter = signPlacmentRowsVec.begin(); iter != signPlacmentRowsVec.end(); ++iter)
	{
		
        std::vector<Node* > signVector = static_cast<std::vector<Node* > >(*iter); 
	#if LETTERS_DIR == DIR_LEFT 
		for(auto iter1 = signVector.begin(); iter1 != signVector.end(); ++iter1)
	#elif LETTERS_DIR == DIR_RIGHT 
		for(auto iter1 = signVector.rbegin(); iter1 != signVector.rend(); ++iter1)
	#endif
		{
			Sign* pSign = static_cast<Sign*>(*iter1);         
			if(pSign->getIsEmpty())
			{
                int iLatterInx = pSign->getLatterInx();
                Sign* pSignLetter =   SignFactory::getInstance()->getSign(iLatterInx);

                Sign* pSignLetterHint = Sign::create(pSignLetter->getFrameName());
                pSignLetterHint->setScale(0.0f);
                //pSignLetterHint->setAnchorPoint(pSignLetter->getAnchorPoint());
                this->addChild(pSignLetterHint,2);                
                pSignLetterHint->setPosition(pSign->getPosition().x+pSign->getBoundingBox().size.width/2,
                                              pSign->getPosition().y+pSign->getBoundingBox().size.height/2);
                pSignLetterHint->setAnchorPoint(Vec2(0.5f,0.5f));
                scaleInitDelay =  scaleDelayFactor + scaleInitDelay;
                  auto action = Sequence::create(
                                DelayTime::create(scaleInitDelay),
                                ScaleTo::create(core::Settings::getInstance()->FontScaleHintDurationSpeed,
                                                                    SignFactory::getInstance()->getLatterScaleFactor()),
                                DelayTime::create(SignLettersIntoBlankSignsHint_ScaleDownDelay),
                                ScaleTo::create(core::Settings::getInstance()->FontScaleHintDurationSpeed,
                                                                    0.0f),
                                CallFunc::create( std::bind(&SolutionContainer::HintSignAnimationCallback,
                                                                                this,
                                                                                pSignLetterHint)), 
                                RemoveSelf::create(true),
                                 NULL);


                 pSignLetterHint->runAction(action);  
				
               
			}
		}

		 
	} 
}

void SolutionContainer::HintSignAnimationCallback(Node* sender)
{
    ++iHinSignLettersCount;
    if(iHinSignLettersCount == iNumberOfBlankSignLettersCount)
    {
        iHinSignLettersCount = 0;
        core::Settings::getInstance()->stopTouchesInMainLayer = false;
    }
}

void SolutionContainer::ThumbUpAnimation(bool state)
{
    
    if(state)
    {
        pYesThumbUp->setVisible(true);
        auto actionBy = RotateBy::create(0.5f,45);
        auto actionByBack = actionBy->reverse();
        auto sequence = Sequence::create(actionBy, actionByBack, nullptr);
        auto repeat = RepeatForever::create(sequence);
        repeat->setTag(ANIM::THUMBUPANIMATION);
        pYesThumbUp->setAnchorPoint(Vec2(0.0f,0.2f));
        pYesThumbUp->runAction(repeat);
    }
    else
    {
        pYesThumbUp->stopActionByTag(ANIM::THUMBUPANIMATION);
        pYesThumbUp->setRotation(0.0f);
        pYesThumbUp->setVisible(false);

    }
    //pYesThumbUp->runAction( Sequence::create(actionBy, actionByBack, nullptr));
    // this->addChild(pYesThumbUp,100);
   
}

void SolutionContainer::ThumbDownAnimation(bool state)
{
    
    if(state)
    {
        
        pNoNoOneFinger->setVisible(true);
        auto actionBy = RotateBy::create(0.3f,45);
        auto actionByBack = actionBy->reverse();
        auto actionBy2 = RotateBy::create(0.3f,-45);
        auto actionByBack2 = actionBy2->reverse();
        auto sequence = Sequence::create(actionBy,actionByBack,actionBy2,actionByBack2, nullptr);
        auto repeat = RepeatForever::create(sequence);
        repeat->setTag(ANIM::THUMBDOWNANIMATION);
        pNoNoOneFinger->setAnchorPoint(Vec2(0.5f,0.0f));
        pNoNoOneFinger->runAction(repeat);
    }
    else
    {
        
        pNoNoOneFinger->stopActionByTag(ANIM::THUMBDOWNANIMATION);
        pNoNoOneFinger->setRotation(0.0f);
        pNoNoOneFinger->setVisible(false);

    }
}

void SolutionContainer::setFontSelectionAnimation(Sign* &pSelectionFontSign,
                                                  Sign* &pSolutionEmptyFontSign)
{
    
    Vec2 newWorldPosOfSelectionFromSolution = this->convertToWorldSpaceAR(pSolutionEmptyFontSign->getPosition());
    Vec2 newWorldPosOfSelection = pSelectionFontSign->getParent()->convertToWorldSpaceAR(pSelectionFontSign->getPosition());
    //set the world solution font world position to use when we animating back the sign
    pSelectionFontSign->originalWorldPos.x = newWorldPosOfSelection.x;
    pSelectionFontSign->originalWorldPos.y = newWorldPosOfSelection.y;
    pSolutionEmptyFontSign->setIsEmpty(false);
    

    //remove the selection font from the parant and move it to the top sprite
    Node* p1 = pSelectionFontSign->getParent();   
    Node* Master = p1->getParent();
    p1->removeChild(pSelectionFontSign);
    //Master->addChild(pSelectionFontSign,99);
    m_Parent->addChild(pSelectionFontSign,90);
    func = CallFunc::create( std::bind(&SolutionContainer::SelectionWrongAnswerAnimationCallback,
                                                                         this));
    func->setTag(ANIM::HANDLEMATCH);
    auto MatchAction = Sequence::create(
                        MoveTo::create(core::Settings::getInstance()->FontToFontDurationSpeed,newWorldPosOfSelectionFromSolution),
                        CallFunc::create( std::bind(&SolutionContainer::SelectionAnimationCallback,
                                                                        this,
                                                                        pSelectionFontSign,
                                                                        newWorldPosOfSelectionFromSolution)), 
                                                                        func,
                                                                        NULL);
     pSelectionFontSign->runAction(MatchAction);
    

}

//fire in the end of selecting all the slots 
void SolutionContainer::SelectionWrongAnswerAnimationCallback()
{
    if(numberOfFontsPlacedIntoHolders==numberOfLettersOnlyInPlace && 
        !(numberOfMatchedLatters==numberOfLettersOnlyInPlace))
    {
        core::Settings::getInstance()->getSoundManager().playSoundEffect(WRONG_ANSWER_BUZZER);
        this->ThumbDownAnimation(true);
    }
    
}

void SolutionContainer::SelectionAnimationCallback(Node* sender, Vec2 data)
{
    // set the new solution font world position
    ((Sign*)sender)->solutionWorldPos.x = data.x;
    ((Sign*)sender)->solutionWorldPos.y = data.y;      
    this->handleMatch();
}

void SolutionContainer::handleMatch()
{
    //CCLOG("numberOfMatchedLatters:%d numberOfLettersOnlyInPlace:%d",numberOfMatchedLatters,numberOfLettersOnlyInPlace);
    increaseNumberOfFontsPlacedIntoHolders();
    if(this->numberOfMatchedLatters==this->numberOfLettersOnlyInPlace && bSetMatch == false)
    {
        //CCLOG("There is match");       
        m_LevelDataHolder.iOrigExpLength = numberOfLettersOnlyInPlace;
        LevelsManager::getInstance()->LevelComplete(m_LevelDataHolder);
    } 
}


void SolutionContainer::LevelFinishedSuccessfully()
{
    bSetMatch = true;
    this->stopActionByTag(ANIM::HANDLEMATCH);
    //TODO remove this animation from code
    //this->ThumbUpAnimation(true);
    invokeParticals();       
	this->setNextLevelButtonVisible(true);
}

void SolutionContainer::setNextLevelButtonVisible(bool state)
{
    m_Parent->setNextButtonIsVisible(state);
    if(state)
    {
        //stop level timer 
        StopTimer();
        m_Parent->addChild(pNextButten,92);
        this->pNextButten->setVisible(state);
        setLevelTimeIntervalContainerValue();
        setLevelNumberOfMovesValue(iTouchCounterInLevel);
         
    }
    else
    {        
        // TODO , if state is false
    }
}

void SolutionContainer::setLevelNumberOfMoves()
{
    float fLevelNumberOfMovesIntervalFontSize = core::Settings::getInstance()->LevelTimeIntervalFontSize;
    pLevelNumberOfMovesIntervalLabel = Label::createWithTTF("0" ,fontLevelNumberOfMovesIntervalLabel,fLevelNumberOfMovesIntervalFontSize);
    pLevelNumberOfMovesIntervalLabel->retain();
    pLevelNumberOfMovesIntervalLabel->setTag(buttons_tags::LEVEL_NUMBER_OF_MOVES);
    pLevelNumberOfMovesIntervalLabel->setColor(LevelNumberOfMovesIntervalLabel_bk_color);
    pLevelNumberOfMovesIntervalLabel->setAnchorPoint(Vec2(0.5f,0.0f));
    pLevelNumberOfMovesIntervalLabel->setVisible(false);
    m_Parent->addChild(pLevelNumberOfMovesIntervalLabel,92);
}

// count how much moves i take us to solve the pazzel 
void SolutionContainer::setLevelNumberOfMovesValue(int numberOfMoves)
{
    m_LevelDataHolder.iMoves = numberOfMoves;
    std::string moves = String::createWithFormat("%d",numberOfMoves)->getCString();
    std::string movesCaption = " Moves";
    std::string finalStr = moves+movesCaption;
    pLevelNumberOfMovesIntervalLabel->setString(finalStr);     
    float xPos = visibleSize.width/2;//pLevelTimeIntervalContainer->getBoundingBox().size.width/2;
    float fLevelNumberOfMovesIntervalLabelH = pLevelNumberOfMovesIntervalLabel->getBoundingBox().size.height;
    float fLevelTimeIntervalContainerYPos = pLevelTimeIntervalContainer->getPositionY();
    float YPos = fLevelTimeIntervalContainerYPos - fLevelNumberOfMovesIntervalLabelH;
    float YoffSet = 5.0f;
    pLevelNumberOfMovesIntervalLabel->setPosition(xPos,YPos-YoffSet);
    //m_Parent->addChild(pLevelNumberOfMovesIntervalLabel,92);
    pLevelNumberOfMovesIntervalLabel->setVisible(true);
    //setting the points label position
    float pLevelNumberOfMovesIntervalLabelPositionY = pLevelNumberOfMovesIntervalLabel->getPositionY();
    float pLevelNumberOfMovesIntervalLabelHeight = pLevelNumberOfMovesIntervalLabel->getBoundingBox().size.height;
    float fLevelNumberOfMovesIntervalLabelPositionY = pLevelNumberOfMovesIntervalLabelPositionY - pLevelNumberOfMovesIntervalLabelHeight;
    pScoreCoinsContainer->setPosition(0.0f,fLevelNumberOfMovesIntervalLabelPositionY);
}

void SolutionContainer::setScoreCoinsContainer()
{
    float fScoreCoinsFontSize = core::Settings::getInstance()->ScorePointsFontSize;
    pScoreCoinsLabel = Label::createWithTTF("0" ,fontScoreCoinsLabel, fScoreCoinsFontSize,
                                    Size::ZERO,TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    pScoreCoinsLabel->retain();
    pScoreCoinsLabel->setColor(ScoreCoinsLabel_bk_color);
    pScoreCoinsLabel->setTag(buttons_tags::SCORE_COIN_LABEL);
    pScoreCoinsLabel->setAnchorPoint(Vec2(0.0f,0.0f));
    pScoreCoinsLabel->setVisible(false);


    pScoreCoinsContainer = Sprite::create();
    pScoreCoinsContainer->setTextureRect(Rect(0, 0,this->boundingBox().size.width,fScoreCoinsFontSize));
    pScoreCoinsContainer->retain();
    pScoreCoinsContainer->setTag(buttons_tags::SCORE_COIN_CONTAINER);
    pScoreCoinsContainer->setAnchorPoint(Vec2(0.0f,0.0f));
   // pScoreCoinsContainer->setColor(Color3B::WHITE);
    pScoreCoinsContainer->setOpacity(0.0f);
    pScoreCoinsContainer->addChild(pScoreCoinsLabel,1);
    m_Parent->addChild(pScoreCoinsContainer,92);
    
   

}

void SolutionContainer::setScoringOnView(int numOfConins,int levelProgress)
{
   std::string sNumOfConins= String::createWithFormat("%d",numOfConins)->getCString();
   std::string slevelProgress= String::createWithFormat("%d",levelProgress)->getCString();
   bool bOnce = true; 
   Size coinSize ; 
   float coinPosX = 0;
   pOnlyCoinsContainer = Sprite::create();
   pOnlyCoinsContainer->removeAllChildren();
   pOnlyCoinsContainer->setTag(ONLY_COINS_CONTAINER);
   pScoreCoinsLabel->setVisible(true);
   pScoreCoinsContainer->setVisible(true);
   pScoreCoinsLabel->setVisible(true);
   pOnlyCoinsContainer->setAnchorPoint(Vec2(0.0f,0.0f));
    
   for(int i=0;i<numOfConins;i++)
   {
       Sprite* coin = Sprite::createWithSpriteFrameName(sSingleCoin_icon);
       if(bOnce)
       {
            coinSize = coin->getBoundingBox().size;
            bOnce=false;
       }
       coin->setScale(0.6f);
       coin->retain();
       coin->setAnchorPoint(Vec2(0.0f,0.5f));
       coin->setPosition(coinPosX,pScoreCoinsContainer->getBoundingBox().size.height/2); 
       coin->setTag(COIN);
       std::string sNumOf= String::createWithFormat("%d",i)->getCString();
       coin->setName(sNumOf);
       
       pOnlyCoinsContainer->addChild(coin,1);
       coinPosX+=coin->getBoundingBox().size.width/2;
   }


  
  std::string finalStr = "+"+sNumOfConins;
  pScoreCoinsLabel->setString(finalStr);

  pScoreCoinsContainer->addChild(pOnlyCoinsContainer,1);
  float posXcenter = (pScoreCoinsContainer->getBoundingBox().size.width/2)-(coinPosX/2);
  pOnlyCoinsContainer->setPosition(posXcenter,0.0f);
  float ScoreCoinsLabelPosX = pOnlyCoinsContainer->getPositionX()+coinPosX+(coinSize.width/2);
  pScoreCoinsLabel->setPosition(ScoreCoinsLabelPosX,0.0f);

} 

void SolutionContainer::removeCoinsContent()
{
    //pScoreCoinsContainer->removeChildByTag(COIN);    
    pScoreCoinsLabel->setVisible(false);
    pScoreCoinsContainer->setVisible(false);
}

void SolutionContainer::setLevelTimeIntervalContainer()
{
    float fLevelTimeIntervalFontSize = core::Settings::getInstance()->LevelTimeIntervalFontSize;
    pLevelTimeIntervalValueLabel = Label::createWithTTF("0" ,fontLevelTimeIntervalValueLabel, fLevelTimeIntervalFontSize,
                                    Size::ZERO,TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    pLevelTimeIntervalValueLabel->retain();
    pLevelTimeIntervalValueLabel->setColor(LevelTimeIntervalValueLabel_bk_color);
    pLevelTimeIntervalValueLabel->setTag(buttons_tags::GAME_END_DURATION_LABEL);
    pLevelTimeIntervalValueLabel->setAnchorPoint(Vec2(0.0f,0.0f));
    
     
    pLevelTimeIntervalContainer = Sprite::create();
    pLevelTimeIntervalContainer->setTextureRect(Rect(0, 0,this->boundingBox().size.width,fLevelTimeIntervalFontSize));
    pLevelTimeIntervalContainer->retain();
    pLevelTimeIntervalContainer->setTag(buttons_tags::GAME_END_DURATION_CONTAINER);
    pLevelTimeIntervalContainer->setAnchorPoint(Vec2(0.0f,0.0f));
    //pLevelTimeIntervalContainer->setPosition(gesturePosX,gesturePosY-(m_sizeContent.height+pNextButten->getBoundingBox().size.height));
    float ContainerBoundingBoxHeight = pLevelTimeIntervalContainer->getBoundingBox().size.height;
    float halfNextB = (pNextButten->getBoundingBox().size.height/2);
    float pNextButtenPositionY = pNextButten->getPositionY()-halfNextB;
    float Ypos = pNextButtenPositionY - ContainerBoundingBoxHeight;
    pLevelTimeIntervalContainer->setPosition(0.0f,Ypos);
    pLevelTimeIntervalContainer->setVisible(false);
    pLevelTimeIntervalContainer->addChild(pLevelTimeIntervalValueLabel,2);
    //pLevelTimeIntervalContainer->addChild(pClock,2);
    m_Parent->addChild(pLevelTimeIntervalContainer,92);
}
void SolutionContainer::setLevelTimeIntervalContainerValue()
{
    float fEndGameLevelInterval = getEndGameLevelInterval();
    setGameDurationInterval(fEndGameLevelInterval);
    float middleSprit = (m_Parent->getBoundingBox().size.width/2) -  (pLevelTimeIntervalValueLabel->boundingBox().size.width/2);
    pLevelTimeIntervalValueLabel->setPosition(middleSprit,-10.0f);
    pLevelTimeIntervalContainer->setOpacity(0.0f);   
    //pClock->setPosition(pLevelTimeIntervalValueLabel->getPositionX()+pLevelTimeIntervalValueLabel->boundingBox().size.width,0.0f);
    pLevelTimeIntervalContainer->setVisible(true);
}

//when the char is moving back to font sprite 
void SolutionContainer::reduceNumberOfFontsPlacedIntoHolders()
{
   int Local_numberOfFontsPlacedIntoHolders = this->numberOfFontsPlacedIntoHolders;
   int Local_numberOfLettersOnlyInPlace = this->numberOfLettersOnlyInPlace;
   if(Local_numberOfFontsPlacedIntoHolders==Local_numberOfLettersOnlyInPlace)
   {
        this->ThumbDownAnimation(false);
   }
    this->numberOfFontsPlacedIntoHolders--;
    
}
//when the char is moving from font to selection sprite
void SolutionContainer::increaseNumberOfFontsPlacedIntoHolders()
{
    ++numberOfFontsPlacedIntoHolders;
}

//reduce the times there is latters match
void SolutionContainer::reduceNumberOfMatchedLatters()
{
    if(numberOfMatchedLatters>0)
    {
        
        --numberOfMatchedLatters;
    }
    //CCLOG("numberOfMatchedLatters:%d numberOfLettersOnlyInPlace:%d",numberOfMatchedLatters,numberOfLettersOnlyInPlace);
}

/*
    get called from FontSelectionContainer
    sending font that has touched to be moved to the right blank sign
    that is the first that is empty in the list 
*/
void SolutionContainer::setFontSelectionToSulotionFont(Sign* &pSelectionFontSign)
{
    increaseTouchCounterInLevel();
	bool outerloopBreker = false;
	for(auto iter = signPlacmentRowsVec.begin(); iter != signPlacmentRowsVec.end(); ++iter)
	{
		std::vector<Node* > signVector = static_cast<std::vector<Node* > >(*iter); 
	#if LETTERS_DIR == DIR_LEFT 
		for(auto iter1 = signVector.begin(); iter1 != signVector.end(); ++iter1)
	#elif LETTERS_DIR == DIR_RIGHT 
		for(auto iter1 = signVector.rbegin(); iter1 != signVector.rend(); ++iter1)
	#endif
		{
			Sign* pSign = static_cast<Sign*>(*iter1);         
            //check if the first or next blank char holder is empty , 
            //that is next to be handled and filled with touched char from Fontselection
			if(pSign->getIsEmpty())
			{
				pSelectionFontSign->setSignEmptyPair(pSign);
				//the blank and the touch fonts are alike
				if(pSelectionFontSign->getbMatchStatus())
				{
					++numberOfMatchedLatters;
				}
				setFontSelectionAnimation(pSelectionFontSign,pSign);
				outerloopBreker =true;
				break;
			}
		}
		if(outerloopBreker)
		{
			break;
		}
	}
}

//place the Matched Sign at random places 
void SolutionContainer::setFontSelectionToSulotionFontAtRandom(Sign* &pSelectionFontSign)
{
    bool outerloopBreker = false;
	for(auto iter = signPlacmentRowsVec.begin(); iter != signPlacmentRowsVec.end(); ++iter)
	{
		std::vector<Node* > signVector = static_cast<std::vector<Node* > >(*iter); 
	#if LETTERS_DIR == DIR_LEFT 
		for(auto iter1 = signVector.begin(); iter1 != signVector.end(); ++iter1)
	#elif LETTERS_DIR == DIR_RIGHT 
		for(auto iter1 = signVector.rbegin(); iter1 != signVector.rend(); ++iter1)
	#endif
		{
			Sign* pSign = static_cast<Sign*>(*iter1);         
            //check if the first or next blank char holder is empty , 
            //that is next to be handled and filled with touched char from Fontselection
            //log("%d - %d",pSign->getLatterInx(),pSelectionFontSign->getLatterInx());
            if((pSign->getLatterInx()==pSelectionFontSign->getLatterInx()) && pSign->getIsEmpty())
            {
                pSelectionFontSign->setSignEmptyPair(pSign);
				//the blank and the touch fonts are alike
				if(pSelectionFontSign->getbMatchStatus())
				{
					++numberOfMatchedLatters;
				}
				setFontSelectionAnimation(pSelectionFontSign,pSign);
				outerloopBreker =true;
				break;
            }
			 
		}
		if(outerloopBreker)
		{
			break;
		}
	}
}

void SolutionContainer::setGameDurationInterval(float sec)
{    
    std::string sSec = pUT->ConstractTimeView(sec,m_LevelDataHolder);
    std::string sSeccaption="Total Time:";
    std::string sFinalString = sSeccaption+sSec;
    pLevelTimeIntervalValueLabel->setString(sSeccaption+sSec);  
}

SolutionContainer* SolutionContainer::create(HelloWorld* const & parent)
{
        auto sprite = new SolutionContainer(parent);
        sprite->init();
        sprite->autorelease();
        return sprite;  
} 

// how much moved i take us to solve the pazzle
void SolutionContainer::increaseTouchCounterInLevel()
{
    ++iTouchCounterInLevel;
}

void SolutionContainer::StartTimer()
{
	gameInterval =0; 
    this->schedule(schedule_selector(SolutionContainer::tick), 1.0f);  
}

void SolutionContainer::StopTimer()
{
	this->unschedule(schedule_selector(SolutionContainer::tick)); 	 
}

void SolutionContainer::tick(float dt)
{
	gameInterval+=dt;
}

float SolutionContainer::getEndGameLevelInterval()
{
	return gameInterval;
}

void SolutionContainer::setupParticles()
{
     m_pStarParticlesEmitterVector = ParticleFactory::getInstance()->setupParticles(particaleType::EXPLOSION_FIREWORKS_RING_FROM_FILE);
}
 
void SolutionContainer::invokeParticals()
{
    ParticleFactory::getInstance()->invokeParticals(particaleType::EXPLOSION_FIREWORKS_RING_FROM_FILE,m_pStarParticlesEmitterVector);
}

void SolutionContainer::stopParticalse()
{
     for(std::vector<ParticleSystemQuad*>::size_type i = 0; i != m_pStarParticlesEmitterVector.size(); i++) {
        ParticleFactory::getInstance()->StopAndRemoveParticals(m_pStarParticlesEmitterVector[i]);
     }
}


std::vector<ParticleSystemQuad*> SolutionContainer::getStarParticlesEmitterVector()
{
    return m_pStarParticlesEmitterVector;
}
