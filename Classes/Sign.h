//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _Sign_
#define _Sign_

#include "cocos2d.h"
 
USING_NS_CC;

class Sign : public Sprite
{
    public:
        Sign();
        ~Sign();
        static Sign* create(const std::string& frameName);
        virtual bool init(const std::string& frameName); 
        void setLatter(const std::string& l);
        std::string getLatter();
        void setLatterInx(int i);
        int getLatterInx();
        const std::string getFrameName();
        void setSignEmptyPair(Sign* &pair);
        void setSignEmptyPairToNull();
        Sign* getSignEmptyPair();
        //TODO need to create sign interface , those 2 are only for container signs
        void setIsEmpty(bool b);
        bool getIsEmpty();
        void setbMatchStatus(bool b);
        bool getbMatchStatus();
        std::string getSolutionToFontSound();
        std::string getFontToSolutionSound();
        void setSolutionToFontSound(std::string name);
        void setFontToSolutionSound(std::string name);
 
        Vec2 originalPos;
        Vec2 originalWorldPos;
        Vec2 solutionWorldPos;
        virtual void setPosition(float x, float y) override;
        unsigned int soundId;

        float getFinalDestinationY();
        float getFinalDestinationX();
        void setFinalDestinationY(float y);
        void setFinalDestinationX(float x);


    private:
        std::string m_Letter;
        int m_LatterInx;
        std::string m_frameName;
        Sign* pSignEmptyPair;
        
        //TODO need to create sign interface , those 2 are only for container signs
        bool isEmpty;
        bool bMatchStatus;
        std::string fontToSolutionSound;
        std::string solutionToFontSound;

        //Sign position
        float finalDestinationY;
        float finalDestinationX;
};


#endif