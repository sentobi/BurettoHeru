#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include "cocos2d.h"
using namespace cocos2d;


class AnimHandler : public cocos2d::Layer
{


private:
	//static AnimHandler *s_instance;
	float animSpeed;
	//AnimHandler();
	~AnimHandler();


public:
	
	enum ANIMATION_TYPE
	{
		//0
		SHIP_SPAWN,
		SHIP_IDLE,
		SHIP_BACK,
		SHIP_FUNNEL,
		
		//1
		CAPULE_SPAWN,
		CAPULE_ACTIVE,
		
		//2
		PLATONIC_SPAWN,
		PLATONIC_ACTIVE,


		//?? [1st boss(construct)]
		CONSTRUCTFUNNEL_SPAWN,
		CONSTRUCTFUNNEL_ACTIVE,
		CONSTRUCT_ACTIVE,
		CONSTRUCT_ACTIVEP2,
		CONSTRUCT_TPHASE,





		//powerups
		POWERUP_BULLET,
		POWERUP_LASER,
		POWERUP_LIVES,
		POWERUP_MISSILE,
		POWERUP_SHIELD,

		//explosion
		EXPLOSION_CLEAR,
		EXPLOSION,

		NUM_ANIM,

	};
	Animation* animList[NUM_ANIM];

	void Init();
	void Update(float dt);
	void setAnimation(Sprite* sprite, ANIMATION_TYPE  name, bool loop = false);
	void setCCAnimation(Sprite* sprite, ANIMATION_TYPE  name,CallFunc* cfunction);
	void addAnimation(const char* plist,const char* format, int framecount ,ANIMATION_TYPE  name);
    void setAnimframe(Sprite* sprite, ANIMATION_TYPE  name);
	Animation* getAnimAction(ANIMATION_TYPE  name);
	cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);

	//static AnimHandler* getInstance();
    static AnimHandler* GetInstance()
    {
        
        static AnimHandler s_instance;
        s_instance.Init();
        return &s_instance;
        
    };



};

#endif