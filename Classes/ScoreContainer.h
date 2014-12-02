//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _ScoreContainer_
#define _ScoreContainer_

#include "cocos2d.h"
class HelloWorld; 
class BonusContainer;
USING_NS_CC;

enum actionTags
{
    REPEAT_FOREVER_ACTION,
    CALL_FUNC_N_INCREASEBONUS,
    SCORECONTAINER_REPEAT_FOREVER_ACTION,
    SCORECONTAINER_CALL_FUNC_N_INCREASEBONUS,
    SCORECONTAINER_SEQ,
    SEQ
};


class ScoreContainer : public Sprite
{
    friend class BonusContainer;
    public:
        ScoreContainer(HelloWorld* const & parent);
        ~ScoreContainer();
        static ScoreContainer* create(HelloWorld* const & parent);
        virtual bool init();
       
        void setSpriteExtra();
        void setPoints(int p);
        int getPoints();
        void setProgress(int p);
        void setLevelNumber(int l);
        int getProgress();
        void decreasePoints(int p);
        void decreaseProgress(int p);
        void increasePoints(int p);
        void increaseProgress(int p);
        void increaseLevelNumber(int l);
        Sprite* getCoinsSprite();
        Sprite* getPointsCountFrameSprite();
        void setSoundButtonSpriteFrame(bool state);
        void invokeBonusToScoreAnime(int BonusInterval);
        void BonusToScoreIncreaseAnimCallback(Node* sender,int iBonusInterval);
        void setPopupContainerInitPos(bool fromPopup);
        void setPointCountValueLabelValue(int iPointsAccumulator);
        float getOffsetHeight();
        float getOffsetWidth();
        Sprite* pCoins;
        Node* pPointsContainerNode;
		Sprite* pPointsCountFrame;
        Vec2 ProgressBarValueLabelWorldSpaceVec;
        Vec2 CoinsLabelWorldSpaceVec;

    private:
        void BonusContainerDoneAnimCallback(Node* sender);
		void setLevelsProgreesSprite();
		void setPointsProgreesSprite();
		void setBackButtonSprite();
        void setSoundButtonSprite();
        void setEmailButtonSprite();
        void setTrophyButtonSprite();
        void setConfigButtonSprite();
		void setBonus();
        
		 
		 
        void invokeBonusPopupAnimation();
        Sprite* setPointsCountFrame();
        Sprite* setProgressBarFrame();
        Size visibleSize ;
		Size sizeContent;
		Node* pProgressBarContainerNode ;
		ProgressTimer* pProgressBarTimer;
		Sprite* pProgressBarFrame;
		Sprite* star ;
		Label* pProgressBarValueLabel;
        Label* pLevelNumberValueNumberLabel;
		Label* pPointCountValueLabel;

        Sprite* pTrophyButten;
        Sprite* pEmailButten;
        Sprite* pSoundButten;
        Sprite* pConfigButton;

		Sprite* pBackButten;
         
        BonusContainer* pBonusContainer;
        
        
		float WidthSideOffSet;
        float StarToBarOffset;
        float CoinsToBarOffset;
        float ProgressBarPosX;   
	    float ProgressBarPosY;
        float PointsContainerPosX;   
	    float PointsContainerPosY;
        float BackButtenPosX;
	    float BackButtenPosY;
        float EmailButtenPosX;
	    float EmailButtenPosY;
        float SoundButtenPosX;
	    float SoundButtenPosY;
        float TrophyButtenPosX;
	    float TrophyButtenPosY;
        float ConfigButtonPosX;
        float ConfigButtonPosY;

        int progressAccumulator;
        int pointAccumulator;
        int levelNumberAccumulator;
        bool isSoundOff;
		HelloWorld* m_Parent;
        int BonusToScore;
        
};


#endif