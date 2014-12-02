//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "Settings.h"
#include "HelloWorldScene.h"
#include "SignFactory.h"
#include "config/ConstAppDefine.h"
#include "LevelsManager.h"
#include "ScoreManager.h"



core::Settings::Settings()
{
    //SolutionContainer offset from configuration button to coins icon
    FontScaleHintDurationSpeed = 1.0f;
    CoinsFromConfigButtunsOffset = 25.0f;
    FontToFontDurationSpeed = 0.1f;
    FontSelectionOffsetFromButtom = fFontSelectionOffsetFromButtom;
    offsetInBetweenLetters = foffsetInBetweenLetters;
    InitStartAnimDuration  = 0.1f;
    InitStartAnimDurationAddition = 0.03f;
    ImageScaleFactor = 1.0f;
    LevelTimeIntervalFontSize =50.0f;
    ScorePointsFontSize = 50.0f;
    FontSelectionLettersCount = FONT_SELECTION_LETTERS_COUNT;
    LettersDir = LETTERS_DIR;
    SignsIn1raw = FONT_SELECTION_LETTERS_COUNT/2;
    stopTouchesInMainLayer = false;
     
   
}
core::Settings::~Settings()
{
    int level = LevelsManager::getInstance()->getLevelsCount();    
    int score = ScoreManager::getInstance()->getPointsAccumulator();
    int addchar = ScoreManager::getInstance()->getAddCharAccumulator();
    int removechar = ScoreManager::getInstance()->getRemoveCharAccumulator();   
    SetIntegerForKey("level",level);
    SetIntegerForKey("score",score);    
    SetIntegerForKey("addchar",addchar);
    SetIntegerForKey("removechar",removechar);
}

void core::Settings::init(HelloWorld* const & parent)
{
    
    m_Parent = parent;
    loadConfigFromFile(); 
      
}

SoundManager& core::Settings::getSoundManager()
{
    return soundManager;
}

void core::Settings::loadConfigFromFile()
{
    bool bisXMLFileExist = UserDefault::getInstance()->isXMLFileExist();
    if(!bisXMLFileExist)
    {
        createConfigFileWithDefaultValues();
        bool bisXMLFileExist1 = UserDefault::getInstance()->isXMLFileExist();
        std::string xmlPath = UserDefault::getInstance()->getXMLFilePath();
//        std::string data = CCFileUtils::getInstance()->getStringFromFile(xmlPath);
//        log("%s",data.c_str());
    }
    
    
    //log("xml path:%s",xmlPath.c_str());
    score = UserDefault::getInstance()->getIntegerForKey("score",-1);
    if(score<0)
    {
        SetIntegerForKey("score",iDefaultScore);
    }
    addchar = UserDefault::getInstance()->getIntegerForKey("addchar",-1);
    if(addchar<0)
    {
        SetIntegerForKey("addchar",iDefaultAddChar);
    }
    removechar = UserDefault::getInstance()->getIntegerForKey("removechar",-1);
    if(removechar<0)
    {
        SetIntegerForKey("removechar",iDefaultRemoveChar);

    }
    levelnumber = UserDefault::getInstance()->getIntegerForKey("level",-1);
    if(levelnumber<0)
    {
        SetIntegerForKey("level",iDefaultlevel);
        
    } 
}

void core::Settings::createConfigFileWithDefaultValues()
{
    SetIntegerForKey("level",iDefaultlevel);
    SetIntegerForKey("score",iDefaultScore);
    SetIntegerForKey("score",iDefaultScore);
    SetIntegerForKey("addchar",iDefaultAddChar);
    SetIntegerForKey("removechar",iDefaultRemoveChar);
     
}


void core::Settings::SetIntegerForKey(std::string key,int ival)
{
    UserDefault::getInstance()->setIntegerForKey(key.c_str(),ival);
}

void core::Settings::SetIntegerForKey(std::string key,bool bval)
{
     UserDefault::getInstance()->setIntegerForKey(key.c_str(),bval);
}


