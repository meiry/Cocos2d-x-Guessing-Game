//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _SignFactory_
#define _SignFactory_

#include "Singleton.h"
#include "cocos2d.h"
class Sign;
class UT;
class HelloWorld;
USING_NS_CC;

typedef std::map<int,Sign* > SignMap;
typedef std::map<std::string,int > SignToNumMap;

class SignFactory : public Singleton<SignFactory>
{
    friend class Singleton<SignFactory>;
public:
    Sign* getSign(int s);
    void init(HelloWorld* const & parent);
    std::string getLaterByIndex(int inx);
    std::vector<std::string> getLaterFromVec();
    int getIndexByLatter(std::string later);
    void setLatterScaleFactor(float scaleFactor);
    void setLatterScalledWidth(float width);
    void setLatterScalledHeight(float height);
    float getLatterScaleFactor();
    float getScalledLatterWidth();
    float getScalledLatterHeight();
    void setLatterScalledSize(Size size);
    Size getLatterScalledSize();

private:
    SignFactory();
    ~SignFactory();
    
    void fillSignMap();
    void setLattersToVec();
    SignMap m_SignMap;
    SignToNumMap m_SignToNumMap;
    //std::string m_LatersStr;
    std::vector<std::string> m_LatersStrVector;
    Size visibleSize;
    std::string LatterfileNameByRez;
    std::string LatterContainerfileNameByRez;
    float m_latterScaleFactor;
    float m_latterScalledWidth;
    float m_latterScalledHeight;
    Size m_latterScalledSize;
    UT* pUT;
    HelloWorld* m_Parent;
     
    


};

#endif