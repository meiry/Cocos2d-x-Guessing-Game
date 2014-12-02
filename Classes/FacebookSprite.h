#ifndef _FacebookSprite_
#define _FacebookSprite_

#include "cocos2d.h"

 
class UT;
class HelloWorld;
 
USING_NS_CC;

class FacebookSprite : public Sprite
{
    public:
        FacebookSprite(HelloWorld* const & parent);
        ~FacebookSprite();
        static FacebookSprite* create(HelloWorld* const &parent);
        //virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
        virtual bool init();
        std::string getTextForFacebook();
    
        HelloWorld* m_Parent;
        Size visibleSize;

    protected:
        //void onDraw(const Mat4 &transform, uint32_t flags);

    private:
    
        void setCapturedImage(Sprite* &butt);
        void setButtons();
        void setTextField(Sprite* &img);
        Size thisSize;
        float m_buttonsScalFacor;
        Sprite* pSendToFacebookButt;
        Sprite* pCancelSendToFacebookButt;
        Sprite* pCaturedImage;
        Label* pFacebookValueLabel;
        Label* pFacebookWarningValueLabel;
        float fOffSetFromButtom;
        float fCaturedImageOffSetFromButtom;
        UT *pUT;
        float thisPopupWidth;
        float thisPopupHeight;
        CustomCommand _customCommand;
        
        
};


#endif