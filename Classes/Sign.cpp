//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "Sign.h"
#include "Settings.h"

Sign::Sign() : m_LatterInx(0),
               m_Letter(""),
               isEmpty(true),
               pSignEmptyPair(NULL)
{
    setSignEmptyPairToNull();
    setbMatchStatus(false);
}

 

Sign::~Sign()
{

}

void Sign::setPosition(float x, float y)
{
    originalPos.x = x;
    originalPos.y = y;
    Sprite::setPosition(x,y);
}


bool Sign::init(const std::string& frameName)
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Sprite::initWithSpriteFrameName(frameName) )
    {
        return false;
    }
   
    m_frameName = frameName;
     
	return true;
}

const std::string Sign::getFrameName()
{
    return m_frameName;
}

Sign* Sign::create(const std::string& frameName)
{
        auto sprite = new Sign();
        sprite->init(frameName);
        sprite->autorelease();
        return sprite;
} 


void Sign::setLatter(const std::string& l)
{
    m_Letter = l;
}
std::string Sign::getLatter()
{
    return m_Letter;
}


void Sign::setLatterInx(int i)
{
    m_LatterInx = i;
}
int Sign::getLatterInx()
{
    return m_LatterInx;
}

//set temporary the corespanding blank sign pair 
// check if they are match
void Sign::setSignEmptyPair(Sign* &pair)
{
    if(this->getLatter()==pair->getLatter())
    {
        setbMatchStatus(true);
        pair->setbMatchStatus(true);
    }
    else
    {
         setbMatchStatus(false);
         pair->setbMatchStatus(false);
    }
    pSignEmptyPair = pair;
}

Sign* Sign::getSignEmptyPair()
{
    return pSignEmptyPair;
}
//if the blank font are without the font on top 
void Sign::setIsEmpty(bool b)
{
    isEmpty = b;
}
//if the font and the blank container are matched
void Sign::setbMatchStatus(bool b)
{
    bMatchStatus = b;
}
bool Sign::getbMatchStatus()
{
    return bMatchStatus;
}
bool Sign::getIsEmpty()
{
    return isEmpty;
}

void Sign::setSignEmptyPairToNull()
{
    //must be first 
    if(pSignEmptyPair!= NULL)
    {
        pSignEmptyPair->setbMatchStatus(false);
    }
    pSignEmptyPair = NULL;
    setbMatchStatus(false);

   
}


std::string Sign::getSolutionToFontSound()
{
    return solutionToFontSound;
}

std::string Sign::getFontToSolutionSound()
{
    return fontToSolutionSound;
}

void Sign::setSolutionToFontSound(std::string name)
{      
     solutionToFontSound = name;
     core::Settings::getInstance()->getSoundManager().preloadSoundEffect(solutionToFontSound);
}

void Sign::setFontToSolutionSound(std::string name)
{
     fontToSolutionSound = name;
	 core::Settings::getInstance()->getSoundManager().preloadSoundEffect(solutionToFontSound);
}


float Sign::getFinalDestinationY()
{
    return finalDestinationY;
}
float Sign::getFinalDestinationX()
{
     return finalDestinationX;
}
void Sign::setFinalDestinationY(float y)
{
    finalDestinationY = y;
}
void Sign::setFinalDestinationX(float x)
{
    finalDestinationX = x;
}
 