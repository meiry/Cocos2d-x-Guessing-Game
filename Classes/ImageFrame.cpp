//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "ImageFrame.h"

ImageFrame::ImageFrame()
{

}

ImageFrame::~ImageFrame()
{

}
bool ImageFrame::init()
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Sprite::init() )
    {
        return false;
    }
   
    
     
	return true;
}
ImageFrame* ImageFrame::create()
{
        auto sprite = new ImageFrame;
        sprite->init();
        sprite->autorelease();
        return sprite;
} 