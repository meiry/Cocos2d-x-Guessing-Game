//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "FontSelectionContainer.h"
#include "SignFactory.h"
#include "LevelsManager.h"
#include "Sign.h"
#include "UT.h"
#include "HelloWorldScene.h"
#include "Settings.h"
#include "config/ConstAppDefine.h"
#include "ScoreManager.h"



FontSelectionContainer::FontSelectionContainer(HelloWorld* const & parent) 
{
    visibleSize = Director::getInstance()->getVisibleSize();
    pUT = new UT();
    m_Parent = parent;
    
     
}

FontSelectionContainer::~FontSelectionContainer()
{

}

bool FontSelectionContainer::init()
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Sprite::init() )
    {
        return false;
    }
    
	return true;
}

/*
//TODO move it to more logical place in code 
Game init in this order :
1. fonts container 
2. sulotion container 
3. image container 
4. score container <-- this one initiats from main class decupled from the rest 

*/
void FontSelectionContainer::StartGame(bool bStartGame)
{
    //1. fonts container 
    Sprite* fbBt = setThirdPartyIcones();
    float fOpperButtonPositionY = fbBt->getPositionY();
    setFontsSignsInToView(bStartGame,fOpperButtonPositionY);
    //2. sulotion container 
    //place the solution container sign's
     m_Parent->pSolutionContainer->setCurrentLavelSolutionContainer();
    //3. image container     
    m_Parent->pImageExpressionContainer->setCurrentLavelImageExpressionContainer();
    //animate the signs in FontSelectionContainer moving into place
    if(!bStartGame)
    {
        invokeAddLettersAnimation();
    }
}

// place the letters signs into view 
void FontSelectionContainer::setFontsSignsInToView(bool bStartGame,float OpperButtonHight)
{
    float winWidth = visibleSize.width;
    Sign* pSign =  SignFactory::getInstance()->getSign(1);
    //calculate the scale of the latter sign
    float LatterWidth = winWidth/10;
    float LatterSidesOffSet = LatterWidth/10;
    //Size LatterOrigSize = SignFactory::getInstance()->getSign(1)->getBoundingBox().size;
    // must be set first TODO fix this... 
    float latterScaleFactor = SignFactory::getInstance()->getLatterScaleFactor();
    //pSign->setScale(latterScaleFactor);
    pSign->setScale(latterScaleFactor, latterScaleFactor+fSignScaleAddition);
    
    float signWidth = pSign->getBoundingBox().size.width;
    float signHeight = pSign->getBoundingBox().size.height;
   
    
    float offsetInBetweenLetters = core::Settings::getInstance()->offsetInBetweenLetters;
    
    float rowLetersHight = (signHeight*2) + offsetInBetweenLetters;
    float offsetFromButtom = OpperButtonHight - rowLetersHight;//this->getBoundingBox().size.height - rowLetersHight;

   
    float xSignPos = LatterSidesOffSet/2; 
    float ySignPos = offsetFromButtom;
    int iFontSelectionLettersCount = core::Settings::getInstance()->FontSelectionLettersCount;
    float thisSpriteHeight = this->boundingBox().size.height;
    for(int i=0;i<iFontSelectionLettersCount;i++)
    {
       int index = i;
       Sign* pSign =  LevelsManager::getInstance()->getFontSelectionLettersVecIndex(index);
       if(i==(iFontSelectionLettersCount/2)) //set postion to second row
       {
            xSignPos = LatterSidesOffSet/2; 
           ySignPos+= signHeight ;//+ LatterSidesOffSet+foffsetInBetweenFirstAndSecoundRowsLetters;
       }        
       if(bStartGame)
       {
            pSign->setPosition(xSignPos,ySignPos);
       }
       else //start level
       {
           //thisSpriteHeight + pSign->getBoundingBox().size.height;
           pSign->setPosition(xSignPos,thisSpriteHeight);
       }
       pSign->setFinalDestinationY(ySignPos);
       pSign->setFinalDestinationX(xSignPos);
       //pSign->setScale(latterScaleFactor);
       pUT->setSignScalefactor(pSign);
       
       pSign->retain();
       //CCLOG("%s",pSign->getLatter().c_str());
       Vector<Node *> thisChildrenTest =this->getChildren();
       this->addChild(pSign,1); 
       xSignPos+=signWidth+LatterSidesOffSet;
  
    }
}

void FontSelectionContainer::setFontSelectionAnimation(Sign* &pSelectionFontSign,
                                                        Node* &pMasterParent)
{
   Vec2 origWorldPosOfSelectionFromSolution = pSelectionFontSign->originalWorldPos;
    //the global char's counter 
    m_Parent->pSolutionContainer->reduceNumberOfFontsPlacedIntoHolders();
    auto action1 = Sequence::create(
        MoveTo::create(core::Settings::getInstance()->FontToFontDurationSpeed,origWorldPosOfSelectionFromSolution),
                        CallFunc::create( std::bind(&FontSelectionContainer::SelectionAnimationCallback,
                                                                            this,
                                                                            pSelectionFontSign,
                                                                            pMasterParent) ),
                        NULL);
     
    pSelectionFontSign->runAction(action1);
}

/*

invoked from selection sprite back to font sprite

*/
void FontSelectionContainer::SelectionAnimationCallback(Node* sender,
                                                        Node* pmasterParent)
{
    // set the new solution font world position
    ((Sign*)sender)->getSignEmptyPair()->setIsEmpty(true); // mark the Solution empty to go back to it empty state
    if(((Sign*)sender)->getbMatchStatus())
    {
        //Only matched charecters cousing the reduce of the counter 
        m_Parent->pSolutionContainer->reduceNumberOfMatchedLatters();
    }
    ((Sign*)sender)->setSignEmptyPairToNull(); 
    ((Sign*)sender)->solutionWorldPos.y = 0; 
    ((Sign*)sender)->solutionWorldPos.x = 0; 
    pmasterParent->removeChild(((Sign*)sender));   
    this->addChild(((Sign*)sender),1);
 
}

void FontSelectionContainer::removeFromMainParantAndSetInSprite(Sign* &node)
{
    Node* masterParent = node->getParent();
    setFontSelectionAnimation(node,masterParent);
    //pMasterParent->removeChild(node);
    //this->addChild(node,1)
}

FontSelectionContainer* FontSelectionContainer::create(HelloWorld* const & parent)
{
        auto sprite = new FontSelectionContainer(parent);
        sprite->init();
        sprite->autorelease();
        return sprite;
} 

void FontSelectionContainer::invokeAddLettersAnimation()
{
    int counter = 0;     
    float startAnimDuration = core::Settings::getInstance()->InitStartAnimDuration;
    Vector<Node *> FontSelectionContainerChildren = this->getChildren();
    for (auto iter = FontSelectionContainerChildren.begin(); iter != FontSelectionContainerChildren.end(); ++iter) 
    {
        Sign* pSign = static_cast<Sign*>(*iter); 
        if(pSign->getTag() == sign_tags::LETTER_SIGH)
        {
           
           SignAddToContainerAnimation(pSign,startAnimDuration);
           if(counter <core::Settings::getInstance()->SignsIn1raw)
           {
                startAnimDuration+=core::Settings::getInstance()->InitStartAnimDurationAddition;
                counter++; 
           }
           else
           {
                startAnimDuration = core::Settings::getInstance()->InitStartAnimDuration;
                counter =0;
           }
             
        }
    }
}

void FontSelectionContainer::SignAddToContainerAnimation(Sign* &pSignToAdd,float fStartAnimDuration)
{
     
        float removblePointY = pSignToAdd->getFinalDestinationY();
        float removblePointX = pSignToAdd->getFinalDestinationX();
        auto action = Sequence::create(		 
		                MoveTo::create(fStartAnimDuration, Vec2(removblePointX,removblePointY)),
		                nullptr);
        pSignToAdd->runAction(action);
}

void FontSelectionContainer::invokeRemoveLettersAnimation()
{
    int counter = 0;     
    float startAnimDuration = core::Settings::getInstance()->InitStartAnimDuration;
    Vector<Node *> FontSelectionContainerChildren = this->getChildren();
    nodesToRemove = FontSelectionContainerChildren.size();
    nodesToRemoveCounter = 0;
    for (auto iter = FontSelectionContainerChildren.rbegin(); iter != FontSelectionContainerChildren.rend(); ++iter) 
    {
        Sign* pSign = static_cast<Sign*>(*iter); 
        if(pSign->getTag() == sign_tags::LETTER_SIGH)
        {
           
           SignRemovFromContainerAnimation(pSign,startAnimDuration);
           if(counter <core::Settings::getInstance()->SignsIn1raw)
           {
                startAnimDuration+=core::Settings::getInstance()->InitStartAnimDurationAddition;
                counter++; 
           }
           else
           {
                startAnimDuration = core::Settings::getInstance()->InitStartAnimDuration;
                counter =0;
           }
             
        }
    }
}

void FontSelectionContainer::SignRemovFromContainerAnimation(Sign* &pSignToRemove,float fStartAnimDuration)
{
    
    float signPosY = pSignToRemove->getPositionY();
    float signH = pSignToRemove->getBoundingBox().size.height;
    float removblePointH = (signPosY + signH) * -1 ;
    auto action = Sequence::create(		 
        MoveBy::create(fStartAnimDuration, Vec2(pSignToRemove->getFinalDestinationX(),removblePointH)),		 
		                CallFunc::create( CC_CALLBACK_0(FontSelectionContainer::removeSignCallback,this,pSignToRemove)),
		                nullptr);
    pSignToRemove->runAction(action);
}

 void FontSelectionContainer::removeSignCallback(Node* sender)
 {
     this->removeChild(sender,true);
     nodesToRemoveCounter++;
     if(this->nodesToRemoveCounter==this->nodesToRemove)
     {
         //this->StartGame(false);
     }    
 }
 
 
 bool FontSelectionContainer::AddChar()
 {
     if(ScoreManager::getInstance()->getAddCharAccumulator()==0)
     {
         return false;
     }

     Vector<Node *> FontSelectionContainerChildren = this->getChildren();
     int iRandCharIntVecFirstElm = LevelsManager::getInstance()->getCharIntVecFirstElm();
     if(iRandCharIntVecFirstElm>=0)
     {
        for (auto iter = FontSelectionContainerChildren.begin(); iter != FontSelectionContainerChildren.end(); ++iter) 
        {
            Node *childNode = *iter;                  
            Sign* pSign = static_cast<Sign*>(*iter); 
            int iLatterInx = pSign->getLatterInx();
            //check if the index is included in the exprestion , if not remove the char
            if(iLatterInx == iRandCharIntVecFirstElm)
            {
                m_Parent->pSolutionContainer->setFontSelectionToSulotionFontAtRandom(pSign);
                m_Parent->pSolutionContainer->increaseTouchCounterInLevel();
                ScoreManager::getInstance()->decreaseAddCharAccumulator(DECREASE_ADDCHAR_FROM_FONT);
                break;
            }
         }
     }
     else
     {
        return false;
     }
     return true;
 }

 bool FontSelectionContainer::removeChar()
 {
    if(ScoreManager::getInstance()->getRemoveCharAccumulator()==0)
    {
         return false;
    } 
    Vector<Node *> FontSelectionContainerChildren = this->getChildren();
    int iRandCharsFirstElm = LevelsManager::getInstance()->getRandCharsFirstElm();
    if(iRandCharsFirstElm>=0)
    {
        for (auto iter = FontSelectionContainerChildren.begin(); iter != FontSelectionContainerChildren.end(); ++iter) 
        {
            Node *childNode = *iter;                  
            Sign* pSign = static_cast<Sign*>(*iter); 
            int iLatterInx = pSign->getLatterInx();
            //check if the index is included in the exprestion , if not remove the char
            //log("iLatterInx:%d ,randIndexNum:%d",iLatterInx,iRandCharsFirstElm);
            if(iLatterInx == iRandCharsFirstElm)
            {
                //log("iLatterInx:%d ,randIndexNum:%d",iLatterInx,iRandCharsFirstElm);
                this->removeChild(pSign,true);
                LevelsManager::getInstance()->checkAndRemoveExpIndexInRandfillerCharsSet(iRandCharsFirstElm);
                ScoreManager::getInstance()->decreaseRemoveCharAccumulator(DECREASE_REMOVECHAR_FROM_FONT);
                break;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
 }

Sprite* FontSelectionContainer::setThirdPartyIcones()
{
    float iconesOffSet = 10.0f;
    float iconsWidth = 0.0f;
    float iconeXstartPos = 0.0f;
    float iconeYstartPos  = 0.0f;
    float HelpXPosition = 0.0f;
    Sprite* pFaceBook_PostToWall = NULL;
    Sprite* pHelp = NULL;
#if defined(USE_HELP_INTEGRATION)
     pHelp = pUT->setHelpIcon(); 
     #if defined(USE_ONLY_FACEBOOK_ICON) || defined(USE_FACEBOOK_INTEGRATION)
        pFaceBook_PostToWall = pUT->setFacebookIcon();
        iconsWidth = pFaceBook_PostToWall->getBoundingBox().size.width + iconesOffSet + pHelp->getBoundingBox().size.width;
        iconeXstartPos = (this->boundingBox().size.width/2) - (iconsWidth/2);
        iconeYstartPos = (this->boundingBox().size.height) - pFaceBook_PostToWall->getBoundingBox().size.height;
        pFaceBook_PostToWall->setPosition(iconeXstartPos,
                                            iconeYstartPos);
        this->addChild(pFaceBook_PostToWall,4);
        HelpXPosition = iconeXstartPos+pFaceBook_PostToWall->getBoundingBox().size.width + iconesOffSet;
        
        #undef USE_ONLY_FACEBOOK_ICON
     #else
         iconsWidth = pHelp->getBoundingBox().size.width;
         iconeXstartPos = (this->boundingBox().size.width/2) - (iconsWidth/2);
         HelpXPosition = iconeXstartPos;
     #endif
     pHelp->setPosition(HelpXPosition,iconeYstartPos); 
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