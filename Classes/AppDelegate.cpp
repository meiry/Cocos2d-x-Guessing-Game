#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"
//#include "config/ConstAppDefine.h"

#if defined(USE_FACEBOOK_INTEGRATION)
#include "screw/screw.h"
#include "screw/Notification.h"
USING_NS_SCREW_FACEBOOK;
#endif


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    core::Settings::destroyInstance();
    CocosDenshion::SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching() {
    
#if defined(USE_FACEBOOK_INTEGRATION)
    screw::facebook::Session::start();
#endif
    
    
    
    // initialize director
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
         //glview = cocos2d::GLView::createWithRect(APP_NAME, Rect(0, 0, 640, 960));
         glview = GLView::create(APP_NAME);
         //glview->setFrameSize(640, 1136);
         glview->setFrameSize(640, 960);
         director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    auto screenSize = glview->getFrameSize();
#if defined(USE_FACEBOOK_INTEGRATION)
    Facebook::getInstance()->start();
    director->setNotificationNode(Notification::getInstance());
#endif    
    cocos2d::FileUtils* fileUtils = cocos2d::FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    ResolutionPolicy resolutionPolicy = ResolutionPolicy::NO_BORDER;//ResolutionPolicy::SHOW_ALL;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameZoomFactor(0.5f);
#endif
    if (screenSize.width == 2048 || screenSize.height == 2048)
    {
        glview->setDesignResolutionSize(1536, 2048,resolutionPolicy);
        searchPaths.push_back("ipadhd");
        searchPaths.push_back("ipadsd");
        searchPaths.push_back("iphone5");
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
    }
    else if (screenSize.width == 1024 || screenSize.height == 1024)
    {
        glview->setDesignResolutionSize(768, 1024,resolutionPolicy);
        searchPaths.push_back("ipadsd");
        searchPaths.push_back("iphone5");
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
        
    }
    else if (screenSize.width == 1136 || screenSize.height == 1136)
    {
        glview->setDesignResolutionSize(640, 1136,resolutionPolicy);
        searchPaths.push_back("iphone5");
        //searchPaths.push_back("iphonehd");
        //searchPaths.push_back("iphonesd");
        
    }
    else if (screenSize.width == 960 || screenSize.height == 960)
    {
        glview->setDesignResolutionSize(640, 960,resolutionPolicy);
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
    }
    else
    {
        searchPaths.push_back("iphonesd");
        glview->setDesignResolutionSize(320, 480,resolutionPolicy);
    }
    
    fileUtils->setSearchPaths(searchPaths);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    cocos2d::Director::getInstance()->stopAnimation();
    

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
 
    cocos2d::Director::getInstance()->startAnimation();
     

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
