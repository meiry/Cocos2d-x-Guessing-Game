//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "LevelsManager.h"
#include "SignFactory.h"
#include <algorithm>
#include "UT.h"
#include "Sign.h"
#include "HelloWorldScene.h"
#include "ScoreManager.h"
#include "config/ConstAppDefine.h"
#include "ScoreManager.h"
 

LevelsManager::LevelsManager() :LevelsCount(0),
								isInitSet(false),
                                destinationCount(0)
{
    setExpressionsMap(); 
    pUT = new UT();
    visibleSize = Director::getInstance()->getVisibleSize();
    solutionSignVec = new std::vector<Sign*>();
    
    if(visibleSize.width <= 960)
    {
         
        
    } 
}

 LevelsManager::~LevelsManager()
{
    ;
}

//must be init somewhere in the application once
void LevelsManager::init(HelloWorld* const & parent)
{    
    isInitSet = true;
    m_Parent = parent;
}

void LevelsManager::getLevel()
{
    CCASSERT(isInitSet, "LevelsManager::init must be called first  should not be null"); 
    setLevel(false);
}

void LevelsManager::moveNextLevel()
{
    CCASSERT(isInitSet, "LevelsManager::init must be called first  should not be null"); 
    
    setLevel(false,true);
}

void LevelsManager::InitFirstGameLavel()
{
    //setLevel(true);
    setLevel(false,false);   
}

//invoked only if its not strat game
void LevelsManager::setLevelNumber(int levelNumber)
{    
    int levelCount = levelNumber;//getLevelsCount();
    if(levelCount>=1)
    {        
        core::Settings::getInstance()->SetIntegerForKey("score",0); 
        //here the trick if LevelsCount == 0 and levelNumber > 1 it means the user quit the game so we need to start the game from last level
        if(getLevelsCount()>0)
        {
            ScoreManager::getInstance()->setAllToZero();
            m_Parent->pFontSelectionContainer->invokeRemoveLettersAnimation();
            
        }
        setLevelsCount(levelNumber);
        setLevel(false,false);       
        
    }
    else
    {
        CCASSERT((levelCount<1), "LevelsManager:: Level number must be above 0 ");   
    }
}

// if there is match we need to handle few stuff befor continuing
void LevelsManager::LevelComplete(LevelDataHolder &levelDataHolder)
{
    m_Parent->pSolutionContainer->LevelFinishedSuccessfully();
    m_Parent->pFontSelectionContainer->invokeRemoveLettersAnimation();
    core::Settings::getInstance()->getSoundManager().playSoundEffect(CORRECT_ANSWER);
    //Level succesed set points 
	ScoreManager::getInstance()->setGlobalPositiveScroe(LevelsCount,levelDataHolder);
}


// set all the maps and vars to the current level  
void LevelsManager::setLevel(bool bStartGame,bool bCleanPreviousLevel)
{
    if(bCleanPreviousLevel)
    {
        //also means we are in middle of agame 
        cleanPreviousLevel();
         // triggered from the the next level button 
        int lvl =  ++LevelsCount;
        setLevelsCount(lvl);
      
    }    
    setLevel(bStartGame);
    
 }
// set all the maps and vars to the current level 
void LevelsManager::setLevel(bool bStartGame)
{
    CCASSERT(isInitSet, "LevelsManager::init must be called first  should not be null");    
    //increase the levels increase 1 each time 
    if(bStartGame)
    {
        int level = UserDefault::getInstance()->getIntegerForKey("level",1);
        setLevelsCount(level);
    }
    else
    {       
        //its not first timee to start the game so continue flow
        if(!isGameOver())
        {       
            startGame(bStartGame);
        }
        else
        {         
		    GameOver();
        }
        
        
    }
}

void LevelsManager::startGame(bool bStartTheGame)
{
     //Randomize the expr string 
    randomizeSigns();    
	m_Parent->pFontSelectionContainer->StartGame(bStartTheGame);
}

void  LevelsManager::GameOver()
{
    log("Game is Over!!!");
}

bool LevelsManager::isGameOver()
{
    //check if there is moe string to process 
    if(LevelsCount <= expressionsMap.size())
    {
        return false;
    }
    return true;
}

void  LevelsManager::cleanPreviousLevel()
{
    Vector<Node *> SolutionContainerChildren = m_Parent->pSolutionContainer->getChildren();
    for (auto iter = SolutionContainerChildren.begin(); iter != SolutionContainerChildren.end(); ++iter) 
    {
        Sign* pSign = static_cast<Sign*>(*iter); 
        if(pSign->getTag() == sign_tags::LETTER_SIGH)
        {
            m_Parent->pSolutionContainer->removeChild(pSign,true);
        }
    }
    m_Parent->pSolutionContainer->cleanPreviousLevel();
    Vector<Node *> ParentContainerChildren = m_Parent->getChildren();
    for (auto iter = ParentContainerChildren.begin(); iter != ParentContainerChildren.end(); ++iter) 
    {
        Sign* pSign = static_cast<Sign*>(*iter); 
        if(pSign->getTag() == sign_tags::LETTER_SIGH)
        {
            m_Parent->removeChild(pSign,true);
        }
    }
    
    m_Parent->pImageExpressionContainer->m_ImageFrame->removeAllChildren();
    solutionSignVec->clear();
    randomedSignVec.clear();
    charIntMap.clear();
    RandCharsIntMap.clear();
    RandCharsIntVec.clear();
    charIntVec.clear();
}

//Randomize the expr string 
void  LevelsManager::randomizeSigns()
{
    destinationCount =0;
    CCASSERT(isInitSet, "LevelsManager::init must be called first  should not be null"); 
    //get the string expression we are playing for the level , the count starts from 1
    ExpressionsMap::iterator iter = expressionsMap.find(LevelsCount);
    PhraseHolder phraseHolder = iter->second;     
    std::vector<std::string> expressionVec = pUT->split(phraseHolder.sPhrase,',');
    std::vector<std::string> solutionVec;
    std::vector<std::string> optional = SignFactory::getInstance()->getLaterFromVec();
    std::vector<std::string> destination;
    int expretionCount = 0;
    //build string removing "-" sparator 
    Sign* pSignSeperator =   SignFactory::getInstance()->getSign(sign_tags::CONTAINER_SIGH);
    Sign* pSignLineBreak =   SignFactory::getInstance()->getSign(sign_tags::SEPERATOR_SIGH);
    for(int i= 0; i < expressionVec.size();i++)
    {
        //char ch = expressionVec.at(i);
        //std::string s(1,ch);
        //solutionVec.push_back(ch);
        std::string ch = expressionVec.at(i);
        Sign* pSolutionNewSign = NULL;
        Sign* pSignOrig_1 = NULL;
        
        if(ch=="-")
        {
            pSolutionNewSign = Sign::create(pSignSeperator->getFrameName());
            pSolutionNewSign->retain();
            pSolutionNewSign->setLatter(pSignSeperator->getLatter());
            pSolutionNewSign->setLatterInx(-1); //space
            pSolutionNewSign->setAnchorPoint(pSignSeperator->getAnchorPoint());
            pSolutionNewSign->setTag(pSignSeperator->getTag());
			pSolutionNewSign->setSolutionToFontSound(pSignSeperator->getSolutionToFontSound());
			pSolutionNewSign->setFontToSolutionSound(pSignSeperator->getFontToSolutionSound());
        }
        else if(ch=="|")
        {
            pSolutionNewSign = Sign::create(pSignLineBreak->getFrameName());
            pSolutionNewSign->retain();
            pSolutionNewSign->setLatter(pSignLineBreak->getLatter());
            pSolutionNewSign->setLatterInx(-2); //line break
            pSolutionNewSign->setAnchorPoint(pSignLineBreak->getAnchorPoint());
            pSolutionNewSign->setTag(pSignLineBreak->getTag());
			pSolutionNewSign->setSolutionToFontSound(pSignLineBreak->getSolutionToFontSound());
			pSolutionNewSign->setFontToSolutionSound(pSignLineBreak->getFontToSolutionSound());
        }
        else if(ch!="-")
        {
            expretionCount++;
            
             //TODO <- need to check if need to remove the vector 
            //build the start of the char's vector 
            destination.push_back(ch);
            int inx = SignFactory::getInstance()->getIndexByLatter(ch);
            pSignOrig_1 = SignFactory::getInstance()->getSign(inx);
            pSolutionNewSign = Sign::create(pSignSeperator->getFrameName());
            pSolutionNewSign->retain();
            pSolutionNewSign->setLatter(pSignOrig_1->getLatter());
            pSolutionNewSign->setLatterInx(pSignOrig_1->getLatterInx());
            pSolutionNewSign->setAnchorPoint(pSignOrig_1->getAnchorPoint());
            pSolutionNewSign->setTag(pSignOrig_1->getTag());
			pSolutionNewSign->setSolutionToFontSound(pSignOrig_1->getSolutionToFontSound());
			pSolutionNewSign->setFontToSolutionSound(pSignOrig_1->getFontToSolutionSound());
            //keep the letters indexs 
            charIntMap.insert(pSolutionNewSign->getLatterInx());
            charIntVec.push_back(pSolutionNewSign->getLatterInx());
           
        }
        solutionSignVec->push_back(pSolutionNewSign);
    }
    
    //calculate the remaining vector element and fill them with random chars 
    destinationCount = FONT_SELECTION_LETTERS_COUNT - expretionCount;
    for(int j= 0; j<destinationCount;j++)
    {
        int num = pUT->getRandomWithInRange(0,LETTERS_LENGTH-1);
        //log("random:%d",num);
        RandCharsIntMap.insert(num);
        RandCharsIntVec.push_back(num);
        std::string ch = optional[num];
        destination.push_back(ch);
    }
    
    //randomize the final string  
    srand(time(0));     
    std::random_shuffle(RandCharsIntVec.begin(), RandCharsIntVec.end());
    std::random_shuffle(destination.begin(), destination.end());
    std::random_shuffle(charIntVec.begin(), charIntVec.end());
    
    //create Sign objects vector
    for(int i=0;i<destination.size();i++)
	{
        std::string s = destination.at(i);
        //CCLOG("%s",s.c_str());
        int inx = SignFactory::getInstance()->getIndexByLatter(s);
        Sign* pSignOrig = SignFactory::getInstance()->getSign(inx);
        Sign* pNewSign = Sign::create(pSignOrig->getFrameName());
        pNewSign->setLatter(pSignOrig->getLatter());
        pNewSign->setLatterInx(pSignOrig->getLatterInx());
        pNewSign->setAnchorPoint(pSignOrig->getAnchorPoint());
        pNewSign->setTag(pSignOrig->getTag());
		pNewSign->setSolutionToFontSound(pSignOrig->getSolutionToFontSound());
		pNewSign->setFontToSolutionSound(pSignOrig->getFontToSolutionSound());
        pNewSign->retain();
        //final string to use in FontSelectionContainer 
        randomedSignVec.push_back(pNewSign);
    }
}

void LevelsManager::setFontSelection()
{
}

void LevelsManager::setSolution()
{

}
//final string to use in FontSelectionContainer 
Sign* LevelsManager::getFontSelectionLettersVecIndex(int i)
{
    return randomedSignVec.at(i);
}
//final string to use in solutionSignVec 
Sign* LevelsManager::getSolutionSignLettersVecIndex(int i)
{
    return solutionSignVec->at(i);
}
std::string LevelsManager::getSolutionLettersVecIndex(int i)
{
    ExpressionsMap::iterator iter = expressionsMap.find(i);
    PhraseHolder phraseHolder = iter->second;
    std::string expressionStr = phraseHolder.sPhrase;
    return expressionStr;
}

std::string LevelsManager::getSolutionLettersCurrentString()
{    
    return getSolutionLettersVecIndex(LevelsCount);
}


std::string LevelsManager::getImageExpressionCurrentImageIndex(int i)
{
    ExpressionsMap::iterator iter = expressionsMap.find(i);
    std::string expressionImageStr = iter->second.ImageName;
    return expressionImageStr;
}

std::string LevelsManager::getImageExpressionCurrentImage()
{
    return getImageExpressionCurrentImageIndex(LevelsCount);
}
void LevelsManager::setImageExpression()
{

}

int LevelsManager::getLevelsCount()
{
    return LevelsCount;
}
void  LevelsManager::setLevelsCount(int level)
{
    LevelsCount = level;
}

void LevelsManager::PostActionDispatcher(PostActionType postActionType)
{
    switch(postActionType)
    {
        case LETTERS_ANIM_SCALE_HINT:
        {
            if(bPostActionSulotionHint_letters_scale_anim)
            {
                m_Parent->pSolutionContainer->setPostActionSulotionHint();
            }
            break;
        }
    }
}

bool LevelsManager::checkAndRemoveExpIndexFromSet(int inx)
{    
    std::set<int>::iterator it;
    it = charIntMap.find (inx);
    if (it == charIntMap.end())
    {
        return false;
    }
    charIntMap.erase(it);
    return true;
}

bool LevelsManager::checkExpIndexInSet(int inx)
{    
    std::set<int>::iterator it;
    it = charIntMap.find (inx);
    if (it == charIntMap.end())
    {
        return false;
    }
    
    return true;
}

bool LevelsManager::checkAndRemoveExpIndexInRandfillerCharsSet(int inx)
{    
    std::set<int>::iterator it;
    it = RandCharsIntMap.find (inx);
    if (it == RandCharsIntMap.end())
    {
        return false;
    }
    RandCharsIntMap.erase(it);
    return true;
}
int LevelsManager::getRandCharsIntMapCount()
{
    return RandCharsIntMap.size();
}

int LevelsManager::getRandCharsFirstElm()
{
    int val = -1;
    if(RandCharsIntVec.size() > 0)
    {
        val = RandCharsIntVec.at(0);
        RandCharsIntVec.erase( RandCharsIntVec.begin() );
    }
    return val;
}

int LevelsManager::getCharIntVecFirstElm()
{
    int val = -1;
    if(charIntVec.size() > 0)
    {
        val = charIntVec.at(0);
        charIntVec.erase(charIntVec.begin());
    }
    return val;
}
void  LevelsManager::setExpressionsMap()
{
    #include "config/ExpressionsMapDefine.h"    
}



 