//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _SolutionContainer_
#define _SolutionContainer_

#include "cocos2d.h"
#include "Settings.h"
#include "ParticleFactory.h"
class UT;
class Sign;
class HelloWorld;
USING_NS_CC;

enum ANIM
{
    THUMBUPANIMATION,
    THUMBDOWNANIMATION,
    HANDLEMATCH
};

class SolutionContainer : public Sprite
{
    public:
		typedef std::vector<std::vector<Node*> > SignPlacmentRowsVec;
        SolutionContainer(HelloWorld* const & parent);
        ~SolutionContainer();
        static SolutionContainer* create(HelloWorld* const & parent);
        void setSpriteExtra();
        virtual bool init(); 
        void setCurrentLavelSolutionContainer();
        void setFontSelectionToSulotionFont(Sign* &pSelectionFontSign);
        void setFontSelectionToSulotionFontAtRandom(Sign* &pSelectionFontSign);
        void handleMatch();
        void reduceNumberOfMatchedLatters();
        void reduceNumberOfFontsPlacedIntoHolders();
        void increaseNumberOfFontsPlacedIntoHolders();
        void ThumbUpAnimation(bool state);
        void ThumbDownAnimation(bool state);
        void setNextLevelButtonVisible(bool state); 
        void cleanPreviousLevel();
        void setGameDurationInterval(float sec);
        void StartTimer();
	    void StopTimer();
	    float getEndGameLevelInterval();
        void setScoringOnView(int numOfConins,int levelProgress);
        void InnerCleanPreviousLevel();
        void setPostActionSulotionHint();
        void increaseTouchCounterInLevel();
        void invokeParticals();
        void stopParticalse();
        void LevelFinishedSuccessfully();
        std::vector<ParticleSystemQuad*> getStarParticlesEmitterVector();
    private:
         
         void setupParticalesByType(particaleType pType);
         void setupParticles();
         void tick(float dt);
         void SelectionAnimationCallback(Node* sender, Vec2 data);
         void SelectionWrongAnswerAnimationCallback();
         float calculateXposForString(const std::string& str);
         void setFontSelectionAnimation(Sign* &pSelectionFontSign,Sign* &pSolutionFontSign);
         void setCoins(int num);
         void setScoreCoinsContainer();
         void removeCoinsContent();
         void setLevelTimeIntervalContainer();
         void setLevelTimeIntervalContainerValue();
         void setLevelNumberOfMovesValue(int numberOfMoves);
         void setLevelNumberOfMoves();
         void placeStringIn(const float xpos,
                                 const float ypos,
                                 const float factor,
                                 const int strCounter,
                                 const std::vector<std::string>& strLineOfChrsVec);
         void invokeCoinsToScoreViewAnimation();
         void CoinsToScoreViewAnimationCallback(Node* sender);
         void CoinsToScoreDoneAnimCallback(Node* sender);
         void HintSignAnimationCallback(Node* sender);
         void setSignLettersIntoBlankSignsHint();
         void createNextButton();
         void createNoNoOneFinger();
         void createClock();
         void createYesThumbUp();
         std::vector<ParticleSystemQuad*> m_pStarParticlesEmitterVector;        
         HelloWorld* m_Parent;
         Size visibleSize;
         UT *pUT;
         Sprite* pYesThumbUp;
         Sprite* pNoNoOneFinger;
		 Sprite* pNextButten;
		 
         std::vector<Sign*> SolutionFollowingVec;
         CallFunc* func;
         //count how many blank letters are in place without line breaks and without spaces
         int numberOfLettersOnlyInPlace;
         //count how many matches between the blank font and the touched fonts 
         int numberOfMatchedLatters;
         //count how many fonts are placed inside the blank holders
         int numberOfFontsPlacedIntoHolders;
         Size m_sizeContent;
         float m_starParticlesPosY;
         float m_starParticlesPosX; 
		 SignPlacmentRowsVec signPlacmentRowsVec;
         Label* pLevelTimeIntervalValueLabel;
         Sprite* pLevelTimeIntervalContainer;
         Sprite* pScoreCoinsContainer;
         Sprite* pOnlyCoinsContainer;
         Label*  pScoreCoinsLabel;
         Label* pLevelNumberOfMovesIntervalLabel;
         Sprite* pClock;
         int iTouchCounterInLevel;
         float gameInterval;
         //float gesturePosY;
         //float gesturePosX;
         static bool bSetMatch;
         static int iCoinsToScoreCount;
		 static int iNumberOfCoinsCount;
         static int iNumberOfBlankSignLettersCount;
         static int iHinSignLettersCount;
         LevelDataHolder m_LevelDataHolder;
         Vec2 CoinsPosVec;
         
         
    
};


#endif