//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _Settings_
#define _Settings_
#include "Singleton.h"
#include "cocos2d.h"
#include "SoundManager.h"
class Sign;
class UT;
class HelloWorld;



USING_NS_CC;
enum children_tags {
        FONTSELECTIONCONTAINER,
        SOLUTIONCONTAINER,
        IMAGEEXPRESSIONCONTAINER,
        SCORECONTAINER 
};

enum sign_tags {
        
        LETTER_SIGH=99,
        CONTAINER_SIGH,
        SEPERATOR_SIGH,
        NONE
};

enum buttons_tags {
    NONE_,
	BACK_BT,
    SOUND_BT,
    EMAIL_BT,
    TROPHY_BT,
    COINS_IMG_BT,
    COINS_COUNT_FRAME,
    POINTS_CONTAINER_NODE,
	NEXT_BT,
    GAME_END_DURATION_LABEL,
    GAME_END_DURATION_CONTAINER,
    LEVEL_NUMBER_OF_MOVES,
    SCORE_COIN_LABEL,
    SCORE_COIN_CONTAINER,
    COIN,
    ONLY_COINS_CONTAINER,
	BONUS,
    REPEAT_FOREVER_COINSTOSCORE_ACTION,
    DONEANDCLOSE,
    CONFIG_BT,
    FACEBOOK_POST_TO_WALL,
    HELP_BT,
    REMOVE_CHAR,
    ADD_CHAR,
    BUY_FOR099,
    BUY_FOR999,
    BUY_FOR1999,
    GET_REMOVECHAR_FOR5,
    GET_ADDCHAR_FOR5,
    SEND_TO_FACEBOOK,
    CANCEL_SEND_TO_FACEBOOK,
    TEXT_FACEBOOK_LAYER,
    TEXT_FACEBOOKWARNING_LAYER,
    CAPTURED_IMAGE,


};

enum layer_tages {
    POP_UP_BASE
};





struct LevelDataHolder 
{
    
    void resetAll()
    {
        iHours = 0;
        iMinutes = 0;
        iSeconds = 0;
        iMoves = 0;
        iOrigExpLength = 0;
    }
    LevelDataHolder()
    {
        iHours = 0;
        iMinutes = 0;
        iSeconds = 0;
        iMoves =0;
        iOrigExpLength = 0;
    }
    int iHours;
    int iMinutes;
    int iSeconds;
    int iMoves;
    int iOrigExpLength;
};


namespace core {
    


class Settings : public Singleton<Settings>
{
     friend class Singleton<Settings>;
      
    
     public:
        ~Settings();
        void init(HelloWorld* const & parent);
        float FontToFontDurationSpeed;
        float FontSelectionOffsetFromButtom;
        float offsetInBetweenLetters;
        int FontSelectionLettersCount;
        float InitStartAnimDuration;
        float InitStartAnimDurationAddition;
        int SignsIn1raw;
        float LevelTimeIntervalFontSize;
        float ScorePointsFontSize;
        float ImageScaleFactor;
        float CoinsFromConfigButtunsOffset;
        float FontScaleHintDurationSpeed;
        std::string LettersDir;
        SoundManager&  getSoundManager();
        void SetIntegerForKey(std::string key,int ival);
        void SetIntegerForKey(std::string key,bool bval);
        bool stopTouchesInMainLayer;
        int score;
        int addchar;
        int removechar;
        int levelnumber;
    
     private:
         Settings();
         void createConfigFileWithDefaultValues();
         void loadConfigFromFile();
         SoundManager soundManager;
         HelloWorld* m_Parent;
		
};
    
}
#endif



