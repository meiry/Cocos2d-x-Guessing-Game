#include "FacebookAPI.h"
#include "HelloWorldScene.h"
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
 
 
 


FacebookAPI::FacebookAPI():m_currentCapturedImagePath("")
{
     
     
   
}
FacebookAPI::~FacebookAPI()
{
    
    
}

void FacebookAPI::init(HelloWorld* const & parent)
{
    
    m_Parent = parent;
    InitFacebookFlow();
    
      
}

std::string FacebookAPI::getcurrentCapturedImagePath()
{
    return m_currentCapturedImagePath;
}

void FacebookAPI::setcurrentCapturedImagePath(std::string imagepath)
{
    m_currentCapturedImagePath = imagepath;
}
 
void FacebookAPI::InitFacebookFlow()
{

    
#if defined(USE_FACEBOOK_INTEGRATION)
    EventListenerCustom *listener;
    EventDispatcher *dispatcher = Director::getInstance()->getEventDispatcher();
    listener = EventListenerCustom::create(FacebookLoginStatusChangedNotification, [=](EventCustom *event){
        this->onSessionStateChanged(event);
    });
    dispatcher->addEventListenerWithSceneGraphPriority(listener,m_Parent);
    
    listener = EventListenerCustom::create(FacebookPublishWithPhotoNotification, [=](EventCustom *event){
        this->onPublishWithPhoto(event);
    });
    dispatcher->addEventListenerWithSceneGraphPriority(listener,m_Parent);
    
    
#endif
}


void FacebookAPI::onSessionStateChanged(EventCustom *event) {
    // If session is opened and no user detail found
#if defined(USE_FACEBOOK_INTEGRATION)
    if (Session::getActiveSession()->isOpened() && !Facebook::getInstance()->getUser()) {
        this->fetchUserDetail();
    }
    
    //this->updateUI();
#endif
}
void FacebookAPI::fetchUserDetail()
{
#if defined(USE_FACEBOOK_INTEGRATION)
    if (Session::getActiveSession()->isOpened()) {
        Facebook::getInstance()->fetchUserDetails(nullptr);
    } else {
        Notification::getInstance()->show("Login first");
    }
#endif
}

void FacebookAPI::login() {
#if defined(USE_FACEBOOK_INTEGRATION)
    if (Session::getActiveSession()->isOpened())
    {
        
        
    } else {
        Session::getActiveSession()->open(true, {"user_friends"},
                                          DefaultAudience::PUBLIC,
                                          LoginBehavior::WITH_FALLBACK_TO_WEBVIEW);
    }
#endif
}

void FacebookAPI::requestPublish() {
#if defined(USE_FACEBOOK_INTEGRATION)
    if (Session::getActiveSession()->isOpened()) {
        if (Session::getActiveSession()->hasPermission("publish_actions")) {
            //Notification::getInstance()->show("Publish action already granted");
        } else {
            Session::getActiveSession()->requestPublishPermissions({"publish_actions"});
        }
    } else {
        //Notification::getInstance()->show("Login first");
        login();
    }
#endif
}



void FacebookAPI::shareStatus()
{
#if defined(USE_FACEBOOK_INTEGRATION)
    ShareDialogParams *params = ShareDialogParams::create();
        params->setDescription("Some description");
        params->setLink("http://www.cocos2d-x.org/");
        params->setCaption("Caption");
        params->setDescription("Description");
    //    params->setFriends({"100008211700580", "100008307900261"});
         params->setDataFailuresFatal(false);
    
    if (Dialog::canPresent(params)) {
        Dialog::present(params, [](GraphObject *result, int error){
            CCLOG("Share status dialog callback: result = %s\nerror = %d", result ? result->getValue().getDescription().c_str() : "(null)", error);
        });
    } else {
        CCLOG("Cannot show share dialog, fallback to webview");
        FeedDialogBuilder *fbd = new FeedDialogBuilder();
        fbd->setDescription("Some description");
        fbd->setLink("http://www.cocos2d-x.org/");
        fbd->setCaption("Caption");
        fbd->setDescription("Description");
        fbd->setCallback([](int error, const string &rid){
            CCLOG("Share status web dialog result: error = %d, rid = %s", error, rid.c_str());
        });
        
        fbd->build()->show();
        delete fbd;
    }
#endif
}

void FacebookAPI::shareLink() {
#if defined(USE_FACEBOOK_INTEGRATION)
    ShareDialogParams *params = ShareDialogParams::create();
    params->setLink("http://www.cocos2d-x.org/");
    //    params->setName("A name");
    //    params->setCaption("A caption");
    //    params->setDescription("A description");
    //    params->setFriends({"100008289311268"});
    //    params->setDataFailuresFatal(false);
    
    if (Dialog::canPresent(params)) {
        Dialog::present(params, [](GraphObject *result, int error){
            CCLOG("Share link dialog callback: result = %s\nerror = %d", result ? result->getValue().getDescription().c_str() : "(null)", error);
        });
    } else {
        CCLOG("Cannot show share dialog, fallback to webview");
        FeedDialogBuilder *fbd = new FeedDialogBuilder();
        fbd->setLink(params->getLink())->setDescription(params->getDescription());
        fbd->setTo("100008289311268");
        
        fbd->setCallback([](int error, const string &rid){
            CCLOG("Share link web dialog result: error = %d, rid = %s", error, rid.c_str());
        });
        
        fbd->build()->show();
        delete fbd;
    }
#endif
}

/* @doc https://developers.facebook.com/docs/ios/open-graph/ */
void FacebookAPI::shareOpenGraph()
{
#if defined(USE_FACEBOOK_INTEGRATION)
    OpenGraphActionShareDialogParams *params = OpenGraphActionShareDialogParams::create();
    params->setActionType("screwfb:catch");
    params->setPreviewPropertyName("fish");
    
    GraphObject *fish = GraphObject::createForPost();
    fish->set("type", "screwfb:fish");
    fish->set("title", "Selfish");
    fish->set("description", "The biggest fish in the sea!!!");
    //    fish->set("url", "http://samples.ogp.me/344468272304428");
    //    fish->set("image", "http://i.imgur.com/g3Qc1HN.png");
    
    OpenGraphAction *action = OpenGraphAction::create();
    action->set("fish", fish->getValue());
    //    action->set("fish", "773781669301483"); //For catching a fish with its id
    params->setAction(action);
    if (Dialog::canPresent(params)) {
        Dialog::present(params, [=](GraphObject *result, int error){
            CCLOG("Share status dialog callback: result = %s\nerror = %d", result ? result->getValue().getDescription().c_str() : "(null)", error);
            if (result && result->getString("completionGesture") == "post")
            {
            }
        });
    }
#endif
}

void FacebookAPI::publishWithPhoto(std::string imgPath,const std::string& txt) 
{
#if defined(USE_FACEBOOK_INTEGRATION)
    if (Session::getActiveSession()->isOpened()) {
         
        Facebook::getInstance()->publishWithPhotoGraphAPI(nullptr,imgPath,txt);
    } else {
        Notification::getInstance()->show("Login first");
    }
#endif  
}

void FacebookAPI::onPublishWithPhoto(EventCustom *event) {
#if defined(USE_FACEBOOK_INTEGRATION)
       CCLOG("FacebookAPI::onPublishWithPhoto");
#endif   
}



 