//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _LevelsManager_
#define _LevelsManager_

#include "Singleton.h"
#include "cocos2d.h"
#include "Settings.h"
class Sign;
class UT;
class HelloWorld;
class ScoreManager;
USING_NS_CC;

enum PostActionType 
{
    LETTERS_ANIM_SCALE_HINT
};

struct PhraseHolder
{
    PhraseHolder(std::string _sPhrase,std::string _ImageName)
    {
        sPhrase = _sPhrase;
        ImageName = _ImageName;
        
    }

    std::string sPhrase;
    std::string ImageName;
     
};
 
typedef std::map<int,PhraseHolder> ExpressionsMap;
//typedef std::map<int,std::string> ImagessMap;
typedef std::set<int> CharIntMap;

class LevelsManager : public Singleton<LevelsManager>  
{
    friend class Singleton<LevelsManager>;
    
public:
   
    void init(HelloWorld* const & parent);
    int getLevelsCount();
    void setLevelsCount(int level);
    Sign* getFontSelectionLettersVecIndex(int i);
    Sign* getSolutionSignLettersVecIndex(int i);
    std::string getSolutionLettersVecIndex(int i);
    std::string getSolutionLettersCurrentString();
    std::string getImageExpressionCurrentImageIndex(int i);
    std::string getImageExpressionCurrentImage();
    void getLevel();
    void moveNextLevel();
    void LevelComplete(LevelDataHolder &levelDataHolder);
    void InitFirstGameLavel();
	void setLevelNumber(int levelNumber);
    void PostActionDispatcher(PostActionType postActionType);
    bool checkAndRemoveExpIndexFromSet(int inx); 
    bool checkExpIndexInSet(int inx);
    bool checkAndRemoveExpIndexInRandfillerCharsSet(int inx);
    int getRandCharsIntMapCount();
    int getRandCharsFirstElm();
    int getCharIntVecFirstElm();
    

private:

    LevelsManager();
    ~LevelsManager(); 
    bool isGameOver();
    void GameOver();
    void cleanPreviousLevel();
    void setExpressionsMap();
    void randomizeSigns();
    void setFontSelection();
    void setSolution();
    void setImageExpression();
    void setLevel(bool bStartGame);
    void setLevel(bool bStartGame,bool bCleanPreviousLevel);
    void startGame(bool bStartTheGame);
    Size visibleSize;
    int LevelsCount;
    ExpressionsMap expressionsMap; 
    //ImagessMap imagessMap;
    std::vector<Sign*> randomedSignVec;
    std::vector<Sign*>* solutionSignVec;
    //used to save the index number of the expretion in the level for Compare later if needed ( remove char function for example )
    CharIntMap charIntMap;
    //the indexs of the random chars that fill the expretion
    CharIntMap RandCharsIntMap;
    std::vector<int> RandCharsIntVec;
    std::vector<int> charIntVec;
    UT* pUT;
    HelloWorld* m_Parent;
    bool isInitSet;
    int destinationCount;
	


};

#endif