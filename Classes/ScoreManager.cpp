//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "ScoreManager.h"
#include "HelloWorldScene.h"
#include "LevelsManager.h"
#include "Settings.h"

enum Score
{
	MAX_SCORE_PER_LEVEL = 5,
	MIN_SCORE_PER_LEVEL = 1,
	SUB_LEVEL_PERCENTAGE =50
};

ScoreManager::ScoreManager()
{
    m_PointsAccumulator = 0;
	m_LevelPercentageAccumulator =0;
    m_AddCharAccumulator = 0;
    m_RemoveCharAccumulator = 0;
    m_LevelNumberAccumulator =0;
    
}
ScoreManager::~ScoreManager()
{
}

void ScoreManager::init(HelloWorld* const & parent)
{
    m_Parent = parent;
    int score = UserDefault::getInstance()->getIntegerForKey("score",0);     
    m_PointsAccumulator = score;
    int addchar = UserDefault::getInstance()->getIntegerForKey("addchar",0);
    m_AddCharAccumulator = addchar;
    int removechar = UserDefault::getInstance()->getIntegerForKey("removechar",0);
    m_RemoveCharAccumulator = removechar;
    int levelnumber = UserDefault::getInstance()->getIntegerForKey("level",1);
    m_LevelNumberAccumulator = levelnumber;
   
}

 void ScoreManager::setGlobalPositiveScroe(int level,LevelDataHolder &levelDataHolder)
{
    if(level>=1)
    {
        int points = getPointsByScore(levelDataHolder);
        //m_Parent->pScoreContainer->increaseProgress(20);
        m_Parent->pSolutionContainer->setScoringOnView(points,20);         
    }
}

int ScoreManager::getPointsByScore(LevelDataHolder &levelDataHolder)
{
    int points = 0;
    if(levelDataHolder.iOrigExpLength == levelDataHolder.iMoves)
    {
        points= MAX_SCORE_PER_LEVEL;
    }
    else if((levelDataHolder.iOrigExpLength*2) > levelDataHolder.iMoves && levelDataHolder.iMoves > levelDataHolder.iOrigExpLength)
    {
       points= MAX_SCORE_PER_LEVEL - 2;
    }
    else if((levelDataHolder.iOrigExpLength*2) <= levelDataHolder.iMoves)
    {
        points=MIN_SCORE_PER_LEVEL;
    }
    else
    {
        CCASSERT((levelDataHolder.iMoves>0), "ScoreManager:: levelDataHolder.iMoves 0 ");   
    }
    return points;

}

void ScoreManager::setScoring(int points)
{
	setPointsAccumulator(points);
	m_Parent->pScoreContainer->increasePoints(points);
}

void ScoreManager::setPointsAccumulator(int points)
{
	m_PointsAccumulator+=points;
	 
}

void ScoreManager::setLevelNumberAccumulator(int points)
{
	m_LevelNumberAccumulator+=points;
	 
}

int ScoreManager::getPointsAccumulator()
{
	return m_PointsAccumulator;
	 
} 

int ScoreManager::getAddCharAccumulator()
{
    return m_AddCharAccumulator;
}

int ScoreManager::getRemoveCharAccumulator()
{
    return m_RemoveCharAccumulator;
}

int ScoreManager::getLevelNumberAccumulator()
{
    return m_LevelNumberAccumulator;
}

void ScoreManager::setPercentageAccumulator(int points)
{
	if(m_LevelPercentageAccumulator == 100) 
	{
		m_LevelPercentageAccumulator =0;        
		m_Parent->pScoreContainer->increaseProgress(0);
         
	}
	else
	{
		m_LevelPercentageAccumulator+=points;
		m_Parent->pScoreContainer->increaseProgress(points);
        if(m_LevelPercentageAccumulator == 100)
        {
            setLevelNumberAccumulator(1);
            m_Parent->pScoreContainer->increaseLevelNumber(1);
        }
	}
	
}

void ScoreManager::setPercentage()
{
	setPercentageAccumulator(SUB_LEVEL_PERCENTAGE);
}

void ScoreManager::setAllToZero()
{
    m_PointsAccumulator =0; 
    m_LevelPercentageAccumulator =0;
    m_LevelNumberAccumulator = 0;
	m_Parent->pScoreContainer->increaseProgress(0);
    m_Parent->pScoreContainer->increaseLevelNumber(0);
    m_Parent->pScoreContainer->increasePoints(0);
}


int ScoreManager::increaseAddCharAccumulator(SCORE_TYPE scoreType)
{
    setAccumulatorByType(scoreType);
    m_Parent->pImageExpressionContainer->setAddCharCount(m_AddCharAccumulator);
    return m_AddCharAccumulator;
}
int ScoreManager::decreaseAddCharAccumulator(SCORE_TYPE scoreType)
{
    if(setAccumulatorByType(scoreType)>=0)
    {
        m_Parent->pImageExpressionContainer->setAddCharCount(m_AddCharAccumulator);
    }
    return m_AddCharAccumulator;
}

int ScoreManager::increaseRemoveCharAccumulator(SCORE_TYPE scoreType)
{
    setAccumulatorByType(scoreType);
    m_Parent->pImageExpressionContainer->setRemoveCharCount(m_RemoveCharAccumulator);
    return m_RemoveCharAccumulator;
}

int ScoreManager::decreaseRemoveCharAccumulator(SCORE_TYPE scoreType)
{
    if(setAccumulatorByType(scoreType)>=0)
    {
       m_Parent->pImageExpressionContainer->setRemoveCharCount(m_RemoveCharAccumulator);
    }
    return m_RemoveCharAccumulator;
}
 
int ScoreManager::setAccumulatorByType(SCORE_TYPE scoreType)
{
    int ret = -1;
    switch(scoreType)
    {
        case DECREASE_ADDCHAR_FROM_FONT:
        {
            m_AddCharAccumulator = m_AddCharAccumulator - 1;
            if(m_AddCharAccumulator<0)
            {
                m_AddCharAccumulator=0;
            }
            ret = m_AddCharAccumulator;
            break;
        }
        case DECREASE_REMOVECHAR_FROM_FONT:
        {
            m_RemoveCharAccumulator = m_RemoveCharAccumulator - 1;
            if(m_RemoveCharAccumulator<0)
            {
                m_RemoveCharAccumulator=0;
            }
            ret = m_RemoveCharAccumulator;
            break;
        }
        case INCREASE_ADDCHAR_FROM_FONT:
        {
            m_AddCharAccumulator = m_AddCharAccumulator + 1;
            ret = m_AddCharAccumulator;
            break;
        }
        case INCREASE_REMOVECHAR_FROM_FONT:
        {
            m_RemoveCharAccumulator = m_RemoveCharAccumulator + 1;
            ret = m_RemoveCharAccumulator;
            break;
        }
    }
    return ret;
}