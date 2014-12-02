//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _PopupSprite_
#define _PopupSprite_

#include "cocos2d.h"

 
class UT;
class HelloWorld;
 
USING_NS_CC;

class PopupSprite : public Sprite
{
    public:
        PopupSprite(HelloWorld* const & parent);
        ~PopupSprite();
        static PopupSprite* create(HelloWorld* const &parent);
        virtual bool init(); 
        
        HelloWorld* m_Parent;
        Size visibleSize;
    private:
    
        void setButtPos(Sprite* &pSprite,int rawNum);
        void creatBUY_FOR099(int rawNum);
        void creatBUY_FOR999(int rawNum);
        void creatBUY_FOR1999(int rawNum);
        void creatGET_REMOVECHARFOR5(int rawNum);
        void creatGET_ADDCHARFOR5(int rawNum);
        Sprite* pbutton_BUY_FOR099;
        Sprite* pbutton_BUY_FOR999;  
        Sprite* pbutton_BUY_FOR1999;  
        Sprite* pbutton_GET_REMOVECHAR_FOR5;  
        Sprite* pbutton_GET_ADDCHAR_FOR5; 
        Size thisSize;
        float m_buttonsScalFacor;
        UT *pUT;
        
        
};


#endif