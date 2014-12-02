//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _ImageFrame_
#define _ImageFrame_

#include "cocos2d.h"
 
USING_NS_CC;

class ImageFrame : public Sprite
{
    public:
        ImageFrame();
        ~ImageFrame();
        static ImageFrame* create();
        virtual bool init(); 

    private:
       
};


#endif