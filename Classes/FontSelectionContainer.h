//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _FontSelectionContainer_
#define _FontSelectionContainer_

#include "cocos2d.h"

 
class UT;
class HelloWorld;
class SolutionContainer;
class Sign;
class ImageExpressionContainer;
USING_NS_CC;

class FontSelectionContainer : public Sprite
{
    public:
        FontSelectionContainer(HelloWorld* const & parent);
        ~FontSelectionContainer();
        static FontSelectionContainer* create(HelloWorld* const &parent);
        virtual bool init(); 
        void StartGame(bool bStartGame);
        void removeFromMainParantAndSetInSprite(Sign* &node);
        void invokeRemoveLettersAnimation();
        void invokeAddLettersAnimation();
        bool removeChar();
        bool AddChar();
        //TODO duplicate from ImageExpressionContainer
        Sprite* setThirdPartyIcones();
        HelloWorld* m_Parent;
        Size visibleSize;
    private:
        void setFontsSignsInToView(bool bStartGame,float OpperButtonHight);
        void setFontSelectionAnimation(Sign* &pSelectionFontSign,
                                                  Node* &pMasterParent);
        void SelectionAnimationCallback(Node* sender, Node* pmasterParent);
        void SignAddToContainerAnimation(Sign* &pSignToAdd,float fStartAnimDuration);
        void SignRemovFromContainerAnimation(Sign* &pSignToRemove,float fStartAnimDuration);
        void removeSignCallback(Node* sender);
        UT *pUT;
        //SolutionContainer* pSolutionContainer;
        //ImageExpressionContainer* pImageExpressionContainer;
        int nodesToRemove;
        int nodesToRemoveCounter;
        
};


#endif