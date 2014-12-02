//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _SoundManager_
#define _SoundManager_
#include "cocos2d.h"
class Sign;

USING_NS_CC;

enum soundType
{
    FONT_TO_SOLUTION,
    SOLUTION_TO_FONT,
    WRONG_ANSWER_BUZZER,
    CORRECT_ANSWER,
    BONUS_WINDOWS_POPUP,
    SINGLE_CLICK_1,
    FIREWORKS_1,
    FIREWORKS_2

};


class SoundManager
{
public:
	SoundManager();
	~SoundManager();
   
    void setSoundOffState(bool state);
    bool getSoundOffState();
    unsigned int playSoundEffect(soundType type);
    unsigned int playSoundEffect(Sign* sign,soundType type);
	void preloadSoundEffect(const std::string& soundName);
    std::string soundEffectClick_FromFontToSolution;
    std::string soundEffectClick_FromSolutionToFont;
    std::string soundEffectCorrectAnswer;
    std::string soundEffectWrongAnswerBuzzer;
    std::string soundEffectBonusWindowsPopup;
    std::string soundEffectSingleClick_1;
    std::string soundEffectFireWorks_1;
    std::string soundEffectFireWorks_2;
    
private:
     std::string getSoundEffectByType(soundType type);
     bool bSoundOffStatus;
    
    

};
#endif