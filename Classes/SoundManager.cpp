//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "SoundManager.h"
#include "config/ConstAppDefine.h"
#include "Sign.h"

SoundManager::SoundManager():bSoundOffStatus(false)
{
    
    std::string soundDir = sounds;
    
    soundEffectClick_FromFontToSolution = soundDir+"/CLICK2A.mp3";
	soundEffectClick_FromSolutionToFont = soundDir+"/CLICK20A.mp3";
    soundEffectCorrectAnswer = soundDir+"/TheCorrectAnswerShortCompact.mp3";
    soundEffectWrongAnswerBuzzer = soundDir+"/WrongAnswerBuzzerShortCompact.mp3";
    soundEffectBonusWindowsPopup = soundDir+"/BonusWindowsPopup.mp3";
    soundEffectSingleClick_1 = soundDir+"/SingleClick-1.mp3";
    soundEffectFireWorks_1 = soundDir+"/bottle_rocket_firework_launch_and_explode_2.mp3";
    soundEffectFireWorks_2 = soundDir+"/firework_explosion_with_fizz_005.mp3";
   
    preloadSoundEffect(soundEffectFireWorks_1);
    preloadSoundEffect(soundEffectFireWorks_2);
	preloadSoundEffect(soundEffectClick_FromFontToSolution);
	preloadSoundEffect(soundEffectClick_FromSolutionToFont);
    preloadSoundEffect(soundEffectCorrectAnswer);
    preloadSoundEffect(soundEffectWrongAnswerBuzzer);
    preloadSoundEffect(soundEffectBonusWindowsPopup);
    preloadSoundEffect(soundEffectSingleClick_1);
    
    // set default volume
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
}
SoundManager::~SoundManager()
{
	;
}

void SoundManager::preloadSoundEffect(const std::string& soundName)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(soundName.c_str());
}

void SoundManager::setSoundOffState(bool state)
{
	UserDefault::getInstance()->setBoolForKey("sound", state);
    bSoundOffStatus = state;
}

bool SoundManager::getSoundOffState()
{
	return bSoundOffStatus;
}


unsigned int SoundManager::playSoundEffect(Sign* sign,soundType type)
{
    std::string FontToSolutionSound = sign->getFontToSolutionSound();
    std::string SolutionToFontSound = sign->getSolutionToFontSound();
    unsigned int _soundId = 0;
    std::string clickSound = "";
    if(type == FONT_TO_SOLUTION)
    {
        clickSound = FontToSolutionSound;
    }
    else if(type == SOLUTION_TO_FONT)
    {
        clickSound = SolutionToFontSound;
    }
     

    if(!getSoundOffState())
    {
       
        _soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                                                                            clickSound.c_str(),
                                                                            false);
    }
    
    return _soundId;
}



unsigned int SoundManager::playSoundEffect(soundType type)
{
    unsigned int _soundId = 0;
    std::string clickSound = "";
    if(!getSoundOffState())
    {
        clickSound = getSoundEffectByType(type);
        _soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                                                                            clickSound.c_str(),
                                                                            false);
    }
    
    return _soundId;
}


std::string SoundManager::getSoundEffectByType(soundType type)
{
    std::string soundEffect ="";
    switch(type)
    {
        case  FONT_TO_SOLUTION:
        {
            soundEffect = soundEffectClick_FromFontToSolution;
            break;
        }
        case  SOLUTION_TO_FONT:
        {
            soundEffect = soundEffectClick_FromSolutionToFont;
            break;
        }
        case  CORRECT_ANSWER:
        {
            soundEffect = soundEffectCorrectAnswer;
            break;
        }
        case  WRONG_ANSWER_BUZZER:
        {
            soundEffect = soundEffectWrongAnswerBuzzer;
            break;
        }
        case  BONUS_WINDOWS_POPUP:
        {
            soundEffect = soundEffectBonusWindowsPopup;
            break;
        }
        case  SINGLE_CLICK_1:
        {
            soundEffect = soundEffectSingleClick_1;
            break;
        }
        case  FIREWORKS_1:
        {
            soundEffect = soundEffectFireWorks_1;
            break;
        }
        case  FIREWORKS_2:
        {
            soundEffect = soundEffectFireWorks_2;
            break;
        }
    }
    return soundEffect;
}
