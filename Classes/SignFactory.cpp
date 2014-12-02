//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "SignFactory.h"
#include "Settings.h"
#include "UT.h"
#include "Sign.h"
#include "HelloWorldScene.h"
#include "config/ConstAppDefine.h"
 
 


SignFactory::SignFactory():m_latterScaleFactor(0.0f),
                            m_latterScalledWidth(0.0f),
                            m_latterScalledHeight(0.0f) 
{
    //m_LatersStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    visibleSize = Director::getInstance()->getVisibleSize();
    pUT= new UT();
    if(visibleSize.width <= 960)
    {
        LatterfileNameByRez = sLetterfileNameByRez;
        LatterContainerfileNameByRez = sLetterContainerfileNameByRez;        
    }
    else
    {
         //need to change this to handle resulotions
         LatterfileNameByRez = sLetterfileNameByRez;
         LatterContainerfileNameByRez = sLetterContainerfileNameByRez;
    }  
}

SignFactory::~SignFactory()
{
    ;
}

//must be init somewhere in the application once
void SignFactory::init(HelloWorld* const & parent)
{    
    m_Parent = parent;
    //convert to vector
    setLattersToVec();
    //fill map
    fillSignMap();
}

void SignFactory::setLattersToVec()
{
   for(int i=0;i<LETTERS_LENGTH;i++)
    {
        std::string ch = pUT->int_to_string(i);        
        m_LatersStrVector.push_back(ch);        
    }      
}

std::vector<std::string> SignFactory::getLaterFromVec()
{
    return m_LatersStrVector;
}
//invoke only once
void SignFactory::fillSignMap()
{
    int soundType = SIGN_SOUND_DEFAULT;
    //latters 
    for(int i=0;i<LETTERS_LENGTH;i++)
    {
        char stringSignName[20] = { 0 };
        sprintf(stringSignName,"%s%d.png",LatterfileNameByRez.c_str(), i);
        Sign* pSign = Sign::create(stringSignName);
        pSign->setAnchorPoint(Vec2(0.0,0.0));        
        //char ch = m_LatersStr[i-1];
        std::string latter = pUT->int_to_string(i);
        pSign->setLatterInx((i));
        pSign->setLatter(latter);
        pSign->setTag(sign_tags::LETTER_SIGH);

        if(soundType == IS_FALSE)
        {
            char stringSignSoundName[50] = { 0 };
            sprintf(stringSignSoundName,"%s/%s%d.mp3",lang_sound.c_str(),
                                                      sLetterfileSounds_fnt_to_slc.c_str(),
                                                      i);

			//std::string stringSignSoundName ="x";
            std::string stdstringSignSoundName(stringSignSoundName);
            pSign->setFontToSolutionSound(stdstringSignSoundName);
            pSign->setSolutionToFontSound(core::Settings::getInstance()->getSoundManager()
                                                .soundEffectClick_FromSolutionToFont);

			//delete stringSignSoundName;
        }
        else
        {
            pSign->setSolutionToFontSound(core::Settings::getInstance()->getSoundManager()
                                                .soundEffectClick_FromSolutionToFont);
            pSign->setFontToSolutionSound(core::Settings::getInstance()->getSoundManager()
                                                .soundEffectClick_FromSolutionToFont);
        }



        pSign->retain();         
        m_SignMap.insert(std::pair<int, Sign*>((i),pSign));
        //m_SignToNumMap.insert(std::pair<std::string,int>(latter,(i-1)));
         
    }
    //image container
    Sign* pSignContainer = Sign::create(LatterContainerfileNameByRez);
    pSignContainer->setAnchorPoint(Vec2(0.0,0.0)); 
    pSignContainer->setLatterInx(sign_tags::CONTAINER_SIGH);
    pSignContainer->retain();
    m_SignMap.insert(std::pair<int, Sign*>(sign_tags::CONTAINER_SIGH,pSignContainer));
    
    

    //line break
    Sign* pSignLineBreak = Sign::create(LatterContainerfileNameByRez);
    pSignLineBreak->setAnchorPoint(Vec2(0.0,0.0)); 
    pSignLineBreak->setLatterInx(sign_tags::SEPERATOR_SIGH);
    pSignLineBreak->retain();
    m_SignMap.insert(std::pair<int, Sign*>(sign_tags::SEPERATOR_SIGH,pSignLineBreak));


    //scalefactor
    Sign* SignTest = getSign(1);
    Size LatterOrigSize = SignTest->getBoundingBox().size;
    // must be set first TODO fix this... 
    float winWidth =  m_Parent->pFontSelectionContainer->visibleSize.width;
    float locallatterScaleFactor = pUT->getScaleFactorBasedOnWinWidth(winWidth,LatterOrigSize);
    setLatterScaleFactor(locallatterScaleFactor);
    //SignTest->setScale(getLatterScaleFactor());
    pUT->setSignScalefactor(SignTest);
    setLatterScalledSize(SignTest->getBoundingBox().size);
}
 
int SignFactory::getIndexByLatter(std::string later)
{
    //SignToNumMap::iterator iter = m_SignToNumMap.find(later);
    //int inx = iter->second;
    int i = atoi( later.c_str() );
    return i;
}

std::string SignFactory::getLaterByIndex(int inx)
{
    SignMap::iterator iter = m_SignMap.find(inx);
    Sign* pSign = iter->second;
    std::string latter = pSign->getLatter();
    return latter;
}
 
Sign* SignFactory::getSign(int s)
{
    SignMap::iterator iter = m_SignMap.find(s);
    return iter->second;
}

float SignFactory::getLatterScaleFactor()
{
    return m_latterScaleFactor;
}

void SignFactory::setLatterScaleFactor(float scaleFactor)
{
    m_latterScaleFactor = scaleFactor;
}

void SignFactory::setLatterScalledWidth(float width)
{
    m_latterScalledWidth = width;
}

void SignFactory::setLatterScalledHeight(float height)
{
    m_latterScalledHeight = height;
}

float SignFactory::getScalledLatterWidth()
{
    return m_latterScalledWidth;
}

float SignFactory::getScalledLatterHeight()
{
    return m_latterScalledHeight;
}

void SignFactory::setLatterScalledSize(Size size)
{   
    m_latterScalledSize = size;
    setLatterScalledHeight(size.height);
    setLatterScalledWidth(size.width);
}

Size SignFactory::getLatterScalledSize()
{
    return m_latterScalledSize;
}