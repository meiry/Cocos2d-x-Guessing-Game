//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _BonusContainer_
#define _BonusContainer_

#include "cocos2d.h"
class HelloWorld; 
class ScoreContainer;
USING_NS_CC;


class BonusContainer : public Sprite
{
	 //friend class ScoreContainer;
    public:
        BonusContainer(ScoreContainer* pScoreContainer);
        ~BonusContainer();
        static BonusContainer* create(ScoreContainer* pScoreContainer);
         void invokeBonusPointsInToLabelAnim();
        void initOptions(float width,float height);
        void addEvents();
        void touchEvent(Touch* touch);
        Size getBonusContainerSize();
        bool stopTouchesInBonusContainer;
        void RemoveEventListener();
        void AddEventListener();
        Sprite* pDoneAndCloseButt;

    private:
        void StartTimer();
	    void StopTimer();
	    float getBonusInterval();
        void BonusContainerIncreaseBonusAnimCallback(Node* sender,int maxBonus);
         
        void setBonusSprite(Sprite* &pbonus);
        void setBonusPointsInToLabel(float BonusPoints);
        Sprite* pBonusTopRight;
        Sprite* pBonusTopLeft;
        Sprite* pBonusButtomLeft;
        Sprite* pBonusButtomRight;
        
        Label* pBonusValueLabel;
        float BonusInterval;
        float thisWidth;
        float thisHeight;
        ScoreContainer* m_pScoreContainer;
        EventListenerTouchOneByOne* listener;
        
};

#endif 