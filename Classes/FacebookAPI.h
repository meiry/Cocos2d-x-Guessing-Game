//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _FacebookAPI_
#define _FacebookAPI_
#include "Singleton.h"
#include "cocos2d.h"
#include "config/ConstAppDefine.h"
#if defined(USE_FACEBOOK_INTEGRATION)
#include <iostream>
#include "screw/screw.h"
#include "network/HttpClient.h"
#include "settings/Settings.h"
#include "screw/Notification.h"
USING_NS_SCREW;
USING_NS_SCREW_FACEBOOK;
using namespace cocos2d::network;
#endif

class UT;
class HelloWorld;
class FacebookAPI  : public Singleton<FacebookAPI>
{
     friend class Singleton<FacebookAPI>;
     public:
        ~FacebookAPI();
        void init(HelloWorld* const & parent);
    
         void InitFacebookFlow();
         std::string getcurrentCapturedImagePath();
         void setcurrentCapturedImagePath(std::string imagepath);
         void onSessionStateChanged(EventCustom *event);
         void onUserDetailFetched(EventCustom *event);
         void onFriendsFetched(EventCustom *event);
         void onPhotoDownloaded(EventCustom *event);
         void login();
         void logout();
         void fetchUserDetail();
         void shareLink();
         void shareStatus();
         void shareOpenGraph();
         void requestPublish();
         void deauthorize();
         void onPublishWithPhoto(EventCustom *event);
         void publishWithPhoto(std::string imgPath,const std::string& txt);
         Sprite *_avatar;
 
      private:
         FacebookAPI();
         void loadConfigFromFile();
         HelloWorld* m_Parent;
         std::string m_currentCapturedImagePath;
};


#endif 