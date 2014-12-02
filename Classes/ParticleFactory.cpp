//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "ParticleFactory.h"
#include "Settings.h"
#include "UT.h" 
#include "HelloWorldScene.h"
#include "config/ConstAppDefine.h"
#include "ParticleManager.h"
#include "VisibleRect.h"
 
ParticleFactory::ParticleFactory() :bRunParticales(false),isZero(0),timeCOunter(0)
{
    
    
    visibleSize = Director::getInstance()->getVisibleSize();
    pUT= new UT();
    Rect rec = VisibleRect::getVisibleRect();
    particalsOffSet = 100.0f;
    widthForParticals = rec.size.width-particalsOffSet;
    heightForParticals = rec.size.height-particalsOffSet;
    if(visibleSize.width <= 960)
    {
        
        
    }
  
}

ParticleFactory::~ParticleFactory()
{
  
}

//must be init somewhere in the application once
void ParticleFactory::init(HelloWorld* const & parent)
{
    m_Parent = parent;     
}
    
std::vector<ParticleSystemQuad*> ParticleFactory::getParticleSystemQuad(particaleType type)
{    
    ParticleSystemQuad* _emitter = NULL;   
    std::vector<ParticleSystemQuad*> _emitterVector;
    switch(type)
    {
        case STAR_FIREWORKS:
        {
           
             _emitter = coreParticle::ParticleFireworks::create();
			 _emitter->setTag(STAR_FIREWORKS_TAG);
             _emitter->retain();
             _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage(s_stars1));
           

            // size, in pixels
            _emitter->setStartSize(10.0f);
            _emitter->setStartSizeVar(12.0f);
            _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);
            _emitter->stopSystem();
            _emitter->unscheduleUpdate();
            _emitter->scheduleUpdate();
            _emitterVector.push_back(_emitter);
            break;
        }
        case HEART_FIREWORKS:
        {
            _emitter = coreParticle::ParticleFireworks::create();
			_emitter->setTag(HEART_FIREWORKS_TAG);
            _emitter->retain();
            _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage(s_hart1));
            
           
            // size, in pixels
            _emitter->setStartSize(10.0f);
            _emitter->setStartSizeVar(12.0f);
            _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);
            
            _emitter->stopSystem();
            _emitter->unscheduleUpdate();
            _emitter->scheduleUpdate();
            _emitterVector.push_back(_emitter);
            break;
        }
        case EXPLOSION_FIREWORKS:
        {
            _emitter = coreParticle::ParticleExplosion::createFireWorksRing();
            _emitter->setTag(EXPLOSION_FIREWORKS_TAG);
            _emitter->retain();
            _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage(s_stars1));
            _emitter->stopSystem();
            _emitter->unscheduleUpdate();
            _emitter->scheduleUpdate();
            _emitterVector.push_back(_emitter);
            break;
        }
        case EXPLOSION_FIREWORKS_RING_FROM_FILE:
        {
            
            std::vector<std::string> StringNamesVec;
            int plistCount = 3;
            for(int j=0;j<plistCount;j++)
            {
                char stringPilstName[40] = { 0 };
                sprintf(stringPilstName,"particles/particle_ring_%d.plist",j);
                std::string pilstName(stringPilstName);
                StringNamesVec.push_back(pilstName);
            }
            
            int strCount = 0;
            for(int i=0;i<5;i++)
            {
                 if(i==plistCount)
                 {
                     strCount =0;
                 }
                 ParticleSystemQuad* _emitterLocal = NULL;
                 _emitterLocal = coreParticle::ParticleFromFile::create(StringNamesVec.at(strCount));
                 _emitterLocal->setTag(EXPLOSION_FIREWORKS_RING_FROM_FILE_TAG);
                 _emitterLocal->retain();
                 _emitterLocal->stopSystem();
                 _emitterLocal->unscheduleUpdate();
                 _emitterLocal->scheduleUpdate();
                 _emitterVector.push_back(_emitterLocal);
                strCount++;
            }
            break;
        }
    }

    return _emitterVector;
}
//helpers

std::vector<ParticleSystemQuad*> ParticleFactory::setupParticles(particaleType typeOf)
{
    
    std::vector<ParticleSystemQuad*> pStarParticlesEmitterVector;
    particaleType particaleTypeGenral;
    if(typeOf == particaleType::EXPLOSION_FIREWORKS_RING_FROM_FILE)
    {
        particaleTypeGenral = particaleType::EXPLOSION_FIREWORKS_RING_FROM_FILE;
        pStarParticlesEmitterVector = getParticleSystemQuad(particaleTypeGenral);
        setupParticalesByType(particaleTypeGenral,pStarParticlesEmitterVector);

    }
    return pStarParticlesEmitterVector;
}

void ParticleFactory::setupParticalesByType(particaleType pType,std::vector<ParticleSystemQuad*> vec)
{
    if(pType == particaleType::EXPLOSION_FIREWORKS_RING_FROM_FILE)
    {
        for(std::vector<ParticleSystemQuad*>::size_type i = 0; i != vec.size(); i++)
        {
            
            m_Parent->addChild(vec[i],93);
        }
    }
}

void ParticleFactory::StartParticals(ParticleSystemQuad* &emitter)
{
     core::Settings::getInstance()->getSoundManager().playSoundEffect(FIREWORKS_1);
     emitter->resetSystem();
}

void ParticleFactory::StopAndRemoveParticals(ParticleSystemQuad* &emitter)
{
	 
	if(emitter!= NULL)
    {        
		 
		m_Parent->removeChildByTag(emitter->getTag());
    }
}

//start anim
//TODO need to fix logix its 1:48 am at night ....
void ParticleFactory::invokeParticals(particaleType typeOf,std::vector<ParticleSystemQuad*> vec)
{
    //  FireWorksVec = vec;
    FireWorksVec.assign(vec.begin(), vec.end());
    setRunParticales(true);
    
}


void ParticleFactory::invokeFireWorksParticals()
{
    for(std::vector<ParticleSystemQuad*>::size_type i = 0; i != FireWorksVec.size(); i++)
    {
        float randomPosX =  pUT->getRandomWithInRange((int)particalsOffSet,widthForParticals-1);
        float randomPosY =  pUT->getRandomWithInRange((int)particalsOffSet,heightForParticals-1);
        FireWorksVec[i]->setPosition(Vec2(randomPosX,randomPosY));
        log("innerCounter:%lu,x:%f,y:%f,widthForParticals:%f,heightForParticals:%f",i,randomPosX,randomPosY,widthForParticals,heightForParticals);
        StartParticals(FireWorksVec[i]);
    }

}


void ParticleFactory::runParticalsEveryN(float dt)
{
    if(bRunParticales && (isZero == 0))
    {
        invokeFireWorksParticals();
        timeCOunter++;
    }
    else if(!bRunParticales)
    {
        timeCOunter = 0;
        isZero = 0;
    }
    if(isZero>0)
    {
        timeCOunter++;
    }
    isZero = timeCOunter%2;
    //log("isZero%d ",isZero);

}

bool ParticleFactory::getRunParticales()
{
    return bRunParticales;
}

void ParticleFactory::setRunParticales(bool b)
{
    bRunParticales = b;
}
 