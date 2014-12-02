//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _ImageExpressionContainer_
#define _ImageExpressionContainer_

#include "cocos2d.h"
#include "ImageFrame.h"
class LevelsManager;
class UT;
USING_NS_CC;

class ImageExpressionContainer : public Sprite
{
    friend class LevelsManager;
    friend class PopupLayer;
    public:
        ImageExpressionContainer();
        ~ImageExpressionContainer();
        static ImageExpressionContainer* create();
        virtual bool init(); 
        void setSpriteExtra();
        void setCurrentLavelImageExpressionContainer();
        void setAllIconsInPlace();
        void setImageFrame(const std::string& imageframe);
        void setPointsIntoLabel(int p,Label* &lbl);
        void setAddCharCount(int cCount);
        void setRemoveCharCount(int cCount);
        int getAddCharCount();
        int getRemoveCharCount();
    private:
         void setRemoveChar();
         void setAddChar();
         Sprite* setThirdPartyIcones();
         void setRightSideIcons();
         Sprite* setFacebookIcon();
         Sprite* setHelpIcon();
         Sprite* setRemoveCharIcon();
         Sprite* setAddCharIcon();
         ImageFrame* m_ImageFrame;
         //Sprite* pFaceBook_PostToWall;
         //Sprite* pHelp;
         Sprite* pRemoveChar;
         Sprite* pAddChar;
         Label* pRemoveCharPointCountValueLabel;
         Label* pAddCharPointCountValueLabel;
         float  ImageFrameToImageExpressionOffsetHeight;
         UT *pUT;
         
};


#endif