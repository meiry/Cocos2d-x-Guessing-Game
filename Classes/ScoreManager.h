//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _ScoreManager_
#define _ScoreManager_
#include "cocos2d.h"
#include "Settings.h"
#include "Singleton.h"
USING_NS_CC;
class HelloWorld;

enum SCORE_TYPE
{
    DECREASE_ADDCHAR_FROM_FONT,
    DECREASE_REMOVECHAR_FROM_FONT,
    INCREASE_ADDCHAR_FROM_FONT,
    INCREASE_REMOVECHAR_FROM_FONT

};
class ScoreManager  : public Singleton<ScoreManager>
{
     friend class Singleton<ScoreManager>;
 
     
    public:
		void init(HelloWorld* const & parent);
       
        ~ScoreManager();
         
        void setGlobalPositiveScroe(int level,LevelDataHolder &levelDataHolder); 
		void setScoring(int points);
        void setLevelNumberAccumulator(int points);
		void setPercentage();
        int getPointsAccumulator();
        void setAllToZero();
        int getAddCharAccumulator();
        int getRemoveCharAccumulator();
        int getLevelNumberAccumulator();
        int increaseAddCharAccumulator(SCORE_TYPE scoreType);
        int decreaseAddCharAccumulator(SCORE_TYPE scoreType);
        int increaseRemoveCharAccumulator(SCORE_TYPE scoreType);
        int decreaseRemoveCharAccumulator(SCORE_TYPE scoreType);
    private:
		ScoreManager();
        int setAccumulatorByType(SCORE_TYPE scoreType);
		void setPointsAccumulator(int points);
		void setPercentageAccumulator(int points);
        int getPointsByScore(LevelDataHolder &levelDataHolder);
        HelloWorld* m_Parent;
		int m_PointsAccumulator;
		int m_LevelPercentageAccumulator;
        int m_LevelNumberAccumulator;
        int m_AddCharAccumulator;
        int m_RemoveCharAccumulator;
          
};


#endif