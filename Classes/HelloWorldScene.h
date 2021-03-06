#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "WaveSpawner.h"
#include "GUI.h"
#define COCOS2D_DEBUG 1;
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
private:
    GLProgram* proPostProcess;
    RenderTexture* rendtex;
    Sprite* rendtexSprite;
	Node* spriteNode;
	ParticleSystemQuad* _emitter;
   // Node* projectieNode;

	Sprite* PauseButton;
	Sprite* SpecialAttackButton;
	GUI* playerGui;

	bool SpecialButtonPressed;
    bool timeStopped;
	bool freezeAnimationChange;
    bool freezeAttack;
    float freezeAttackTimer;
    float freezeAttackDashDuration; // duration of this dash - based off length of line
	float default_scale;
    Vec2 screenMin, screenMax;
    float xPos, yPos;
    float widthX, heightY;
    //float minX, maxX, minY, maxY;

    void UpdateFreezeAnimation(float dt);
    void UpdateFreezeAttack(float dt);
	 float currentWidth = 1920;
	 float currentHeight = 1080;
public:
	Node* pwNode;
    Node* laserNode;    // node for laser sprite

	enum GO_TYPE
	{
		PLAYER=0,
		PLAYERPROJ=1,
		ENEMY=2,
		ENEMYPROJ=3,
		POWERUP=4,
        PLAYERSHIELD=5,
        ENEMYSHIELD=6,
		LASERPOWERUP=7,
	};
    static cocos2d::Scene* createScene();

    GUI* GetGUI()
    {
        return playerGui;
    }

    void SetGrayscale();

    virtual bool init();
    void ExitScene();
    
    // callback functions
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onMouseDown(Event*);
    virtual void onMouseUp(Event*);
	virtual bool onContactBegin(PhysicsContact& contact);
    virtual bool onContactSeparate(PhysicsContact& contact);
	/*virtual bool onContactPreSolve(PhysicsContact& contact);
	virtual bool onContactPostSolve(PhysicsContact& contact);*/
	//virtual void tick(float dt);
    // a selector callback
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event * event);
    void onTouchEnded(Touch* touch ,Event * event);
    void menuCloseCallback(cocos2d::Ref* pSender);
	Vec2 ScreenToWorld(Vec2 pos);

	void update(float dt);

    // For Special Attack
    void ExecuteFreezeTime();
    void SetPlayerDashPoints(const std::vector<Vec2>& points);
	void LoadEnemies();

    //bool isKeyHeld(EventKeyboard::KeyCode keyCode);

	Size playingSize;
	
    // World objects
    Player* mainPlayer;
    //Player* GetPlayer() { return mainPlayer; }

	Node* getSpriteNode();
    Node* getProjectileNode();
    // Enemy stuff
    WaveSpawner* waveSpawner;
	
	Sprite *bg_sprite1, *bg_sprite2;
	bool currbg;
	float GetScreenHeightPercentage(float percentage)
	{
		return playingSize.height *(percentage / 100);
	}
	float  GetScreenWidthPercentage(float percentage)
	{
		return playingSize.width *(percentage / 100);
	}
	float ScaleWithScreen()
	{
		return (Director::getInstance()->getWinSizeInPixels().height / currentHeight);
	}
	Sprite* GetSpecialAttackButton()
	{
		return SpecialAttackButton;
	}
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	private:
	cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);
};

#endif // __HELLOWORLD_SCENE_H__
