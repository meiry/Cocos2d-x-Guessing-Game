//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _ParticleFactory_
#define _ParticleFactory_

#include "Singleton.h"
#include "cocos2d.h"
class Sign;
class UT;
class HelloWorld;
USING_NS_CC;

enum particaleType
{
    STAR_FIREWORKS,
    HEART_FIREWORKS,
    EXPLOSION_FIREWORKS,
    EXPLOSION_FIREWORKS_RING_FROM_FILE
};

enum particaleTagName
{
    STAR_FIREWORKS_TAG = 200,
    HEART_FIREWORKS_TAG,
    EXPLOSION_FIREWORKS_TAG,
    EXPLOSION_FIREWORKS_RING_FROM_FILE_TAG
};

class ParticleFactory : public Singleton<ParticleFactory>
{
    friend class Singleton<ParticleFactory>;
public:
    std::vector<ParticleSystemQuad*> getParticleSystemQuad(particaleType type);
    void init(HelloWorld* const & parent);
    void StartParticals(ParticleSystemQuad* &emitter);
    void StopAndRemoveParticals(ParticleSystemQuad* &emitter);
    std::vector<ParticleSystemQuad*> setupParticles(particaleType typeOf);
    void invokeParticals(particaleType typeOf,std::vector<ParticleSystemQuad*> vec);
    void runParticalsEveryN(float dt);
    bool getRunParticales();
    void setRunParticales(bool b);
    

private:
    ParticleFactory();
    virtual ~ParticleFactory();
    void setupParticalesByType(particaleType pType,std::vector<ParticleSystemQuad*> vec);
    void invokeFireWorksParticals();
    Size visibleSize;    
    UT* pUT;
    HelloWorld* m_Parent;
    float widthForParticals;
    float heightForParticals;
    float particalsOffSet;
    bool bRunParticales;
    int timeCOunter;
    int isZero;
    std::vector<ParticleSystemQuad*> FireWorksVec;
    

    
     
    


};







#endif