//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
//External app product
#ifndef _ConstAppDefine_
#define _ConstAppDefine_
#include "cocos2d.h"
USING_NS_CC;

 
inline std::string concatenat(std::string A,std::string B,std::string C)
{
    std::string param = A+B+C;
    return param;
}

#define APP_NAME "GuessGame"

#define EN_LEN 26
#define HEB_LEN 27
// how many letters are N+1
//#define LETTERS_LENGTH EN_LEN
#define LETTERS_LENGTH EN_LEN
 
// 1 == left
// 2 == right

#define DIR_LEFT 1
#define DIR_RIGHT 2
// which is the writing direction 
//#define LETTERS_DIR DIR_LEFT
#define LETTERS_DIR DIR_LEFT

// how much letters in the Fonts section
#define FONT_SELECTION_LETTERS_COUNT 20
// use default sounds or not
#define IS_TRUE   1
#define IS_FALSE   2
//#define SIGN_SOUND_DEFAULT IS_TRUE 
#define SIGN_SOUND_DEFAULT IS_TRUE 

//sounds directorys
#define HEB_SOUND_B "heb_sound_b"
#define HEB_SOUND_G "heb_sound_g"
#define EN_SOUND_GAME "default_sound"
#define SOUND_TYPE  EN_SOUND_GAME

//sounds
#define FNT_TO_SELECTION_SOUND_B_HEB "as_"
#define FNT_TO_SELECTION_SOUND_G_HEB "s_"
#define FNT_TO_SELECTION_SOUND FNT_TO_SELECTION_SOUND_B_HEB

//letters 
#define LETTER_B_HEB_PREFIX "la_"
#define LETTER_G_HEB_PREFIX "l_"
#define LETTER_DEFAULT_EN_PREFIX "l_100_"
//#define LETTER_PREFIX LETTER_DEFAULT_EN_PREFIX
#define LETTER_PREFIX LETTER_DEFAULT_EN_PREFIX

#define EXT_TYPE_WHITE "_white"
#define EXT_TYPE_EMPTY ""
#define LETTER_EXT EXT_TYPE_WHITE


//ScorContainer
#undef SET_POINTSCOUNTFRAME_AS_IMG
#undef SET_PROGRESSBARFRAME_AS_IMG


//particles
static const char s_stars1[]  = "particles/stars1.png";
static const char s_hart1[]  = "particles/heart.png";
static const std::string particle_fireworks_ring  ="particles/particle_ring_1.plist";

static const std::string sounds  = "common_sounds";
static const std::string lang_sound  = SOUND_TYPE;
static const std::string sLetterfileNameByRez = LETTER_PREFIX ;    
static const std::string sLetterfileSounds_fnt_to_slc = FNT_TO_SELECTION_SOUND;
static const std::string sLetterContainerfileNameByRez ="latter_100_container.png";

//static const std::string sNext_bt = "Next_bt_clean.png";
static const std::string sNext_bt = "Next_bt_clean_black.png";
static const std::string sNoNoFinger_bt = concatenat("NoNo-One-Finger",LETTER_EXT,".png"); 
static const std::string sYesYesFinger_bt = concatenat("Yes-Thumb-Up",LETTER_EXT,".png");
static const std::string sClock_icone = concatenat("clock",LETTER_EXT,".png"); 
static const std::string sSingleCoin_icon = "Gold_Coin_-_Single.png";
//popup layer
static const std::string sOpenclose_icon = "close_box_red_64.png";

//ScoreManager
static const int iDefaultScore = 0;
static const int iDefaultAddChar = 100;
static const int iDefaultRemoveChar = 10;
static const int iDefaultlevelnumber = 1;
static const int iDefaultlevel = 1;


//ScoreContainer
static const std::string sConfiguration_icon = concatenat("configuration_100",LETTER_EXT,".png");
static const std::string sSound_off_icon = concatenat("Sound_off_100",LETTER_EXT,".png");
static const std::string sSound_On_icon = concatenat("Sound_On_100",LETTER_EXT,".png");
static const std::string sSenvelope_email_icon = concatenat("envelope_email_100",LETTER_EXT,".png");
static const std::string sTrophy_icon = concatenat("trophy_100",LETTER_EXT,".png");
static const std::string sBack_bn_icon = "back_bn.png";
static const std::string sPresent_box_icon = "present_box1.png";
static const std::string sCoins_icon = "coins_100.png";
static const std::string sStarFull_icon = "StarFull_100.png";
//this when SET_PROGRESSBARFRAME_AS_IMG is defined 
static const std::string sStatus_bar_container_icon = "status_bar_container.png";
//this when SET_POINTSCOUNTFRAME_AS_IMG is defined 
static const std::string sPoints_bar_container_icon = "points_bar_container.png";
//BounsContainer
static const std::string sDoneAndClose_icon = "notification_done.png";
static const Color3B BounsContainer_bk_color = Color3B(134.0f,224.0f,255.0f);
//FacebookContainer
static const std::string sFacebookContainerDoneAndClose_icon = "notification_done.png";
//static const std::string sSendTofacebook_icon = "facebook_send.png";
//static const std::string sCancelSendTofacebook_icon = "facebook_cancel.png";
static const std::string sSendTofacebook_icon = "facebook_send_ft40.png";
static const std::string sCancelSendTofacebook_icon = "facebook_cancel_ft40.png";
static const std::string sImageCapturedName_icon = "TestCapturedImage.png";
static const Color3B FacebookContainer_bk_color = Color3B(175.0f,189.0f,212.0f);
static const Color3B FacebookWarningContainer_bk_color = Color3B(175.0f,189.0f,212.0f);
static const Color3B FacebookMSG_bk_color = Color3B(0.0f,0.0f,0.0f);
static const Color3B FacebookMSGWarning_bk_color = Color3B(214.0f,15.0f,61.0f);
static const float fFacebookInputTextSize = 32.0f;
static const float fFacebookInputWarningTextSize = 32.0f;
static const float fFacebookInputFromImageOffSize = 3.0f;
static const std::string sFacebookMSG = "Please help me to solve this\n pazzle";
static const std::string sFacebookWarningMSG = "Clicking 'Send' will post to your\n Facebook wall";


//popuplayer
static const std::string buy_for099_icon  =  "buy_for099.png";
static const std::string buy_for999_icon   = "buy_for999.png";
static const std::string buy_for1999_icon  = "buy_for1999.png";
static const std::string get_removechar_for5_icon  = "get_removechar_for5.png";
static const std::string get_addchar_for5_icon  = "get_addchar_for5.png";
static const int buy_for099_points      = 10;
static const int buy_for999_points      = 130;
static const int buy_for1999_points     = 190;
static const int buy_removechar_points  = 5;
static const int buy_addchar_points     = 5;
//colors
//http://www.bumblemonkey.com/picker/picker.html
static const Color3B FontSelectionContainer_bk_color = Color3B(0.0f, 0.0f, 0.0f);
static const Color3B SolutionContainer_bk_color = Color3B(255.0f, 255.0f, 255.0f);
static const Color3B ImageExpressionContainer_bk_color = Color3B(255.0f, 255.0f, 255.0f);
static const Color3B ImageFrame_bk_color = Color3B(255.0f, 255.0f, 255.0f);
static const Color3B ScoreContainer_bk_color = Color3B(0.0f, 0.0f, 0.0f);
static const Color3B PopupLayer_bk_color = Color3B(122.0f,15.0f,0.0f);
static const Color3B ProgressBarFrame_bk_color = Color3B(255.0f, 255.0f, 255.0f);
static const Color3B ProgressTimerSprite_bk_color  = Color3B(255.0f, 0.0f, 0.0f);

static const Color3B PointsCountFrame_bk_color = Color3B(255.0f, 255.0f, 255.0f);


//fonts
static const Color3B LevelNumberOfMovesIntervalLabel_bk_color = Color3B(255.0f, 255.0f, 255.0f);
static const Color3B ScoreCoinsLabel_bk_color = Color3B(255.0f, 255.0f, 255.0f);
static const Color3B LevelTimeIntervalValueLabel_bk_color = Color3B(255.0f, 255.0f, 255.0f);
static const Color3B ProgressBarValueLabel_bk_color = Color3B(0.0f, 0.0f, 0.0f);
static const int ProgressBarValueLabel_fnt_size =  32;
static const Color3B PointCountValueLabel_bk_color = Color3B(0.0f, 0.0f, 0.0f);
static const int PointCountValueLabel_fnt_size =  32;
static const Color3B BonusValueLabel_bk_color = Color3B(0.0f, 0.0f, 0.0f);
static const int BonusValueLabel_fnt_size =  72;
static const Color3B RemoveCharPointCount_color  = Color3B(255.0f, 255.0f, 255.0f);
static const int RemoveCharPointCount_fnt_size =  32;
static const Color3B LevelNumberValueLabel_bk_color = Color3B(0.0f, 0.0f, 0.0f);
static const int LevelNumberValueLabel_fnt_size =  32;
//fonts type
static const std::string sGlobal_font = "fonts/Marker Felt.ttf";
static const std::string fontLevelNumberOfMovesIntervalLabel = sGlobal_font;
static const std::string fontScoreCoinsLabel = sGlobal_font;
static const std::string fontLevelTimeIntervalValueLabel = sGlobal_font;
//fonts scale
static const float fSignScaleAddition = 0.3f;

//ImageExpressionContainer
static const float fOffSetBetweenIcones =  5.0f;
static const float fglobal_scale =  0.4f;
static const float ImageExpressionContainerToImageFrameOffset =  0.0f;
static const int valueLabel_fnt_size =  100;
//static const std::string sRemove_char_icon = "remove_char.png";
//static const std::string sAdd_char_icon = "add_char.png";
static const std::string sRemove_char_icon = "remove_char_simple.png";
static const float fRemove_char_icon_scale =  fglobal_scale;
static const std::string sAdd_char_icon = "add_char_simple.png";
static const float fAdd_char_icon_scale =  fglobal_scale;
static const std::string fontLevelAddCharValueLabel = sGlobal_font;
static const std::string fontLevelRemoveCharValueLabel = sGlobal_font;

 



//PostActions
//Letters scale animation
static const bool bPostActionSulotionHint_letters_scale_anim =  false;
//SulotionContainer -> PostActionSulotionHint , scale speed 
static const float SignLettersIntoBlankSignsHint_ScaleUpAnimInitDelay =  0.2f;
static const float SignLettersIntoBlankSignsHint_ScaleUpAnimInitDelayFactor =  0.2f;
static const float SignLettersIntoBlankSignsHint_ScaleDownDelay =  3.0f;


//FontSelectionContainer
static const float fFontSelectionOffsetFromButtom =  150.0f;
static const float foffsetInBetweenLetters = 20.0f;
static const float foffsetInBetweenFirstAndSecoundRowsLetters = 0.0f;

//screans divide from top to buttom 
// first
static const int iScoreContainerHeightPercentage = 10;
// secound
static const int iImageExpressionContainerHeightPercentage = 30;
// thired
static const int iSolutionContainerHeightPercentage = 25;
// forth
static const int iFontSelectionContainerHeightPercentage = 35;





//USE Facebook NOTE if enabled  USE_HELP_INTEGRATION must be enabled also
#define USE_ONLY_FACEBOOK_ICON 1
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #define USE_FACEBOOK_INTEGRATION 1
#endif
 
//static const std::string sFacebook_post_to_wall_icon = "FB-f-Logo__blue_100.png";
static const std::string sFacebook_post_to_wall_icon = "ask_facebook.png";
static const float fFacebook_post_to_wall_icon_scale =  0.7f;


//USE Help 
#define USE_HELP_INTEGRATION 1
 
//static const std::string sHelp_icon = "Help.png";
static const std::string sHelp_icon = "use_hint.png";
static const float fHelp_icon_scale =  0.7f;
#endif
 


 