#ifndef PLAYER_H
#define PLAYER_H

#include "Input.h"
#include "cocos2d.h"
#include "Attack.h"

#include "pfunnel.h"
using namespace cocos2d;

class Player
{
private:
    // for touch movement
    bool touchBegan = false;

	int lives;
	int score,upgrade,missiles,powerup_max;
	float scoreMultiplier;

	pfunnel* funnel_list[4];
	float funnel_spacing = 20;
	float iFrameTimer;
	float iFrameTempTimer;
	float iFrameRenderTimer;
	float iFrameRenderTempTimer;
	float RespawnTimer;
	float RespawnTempTimer;
	float bullet_rtime, missile_rtime;
	bool bullet_fire, missile_fire;
	bool Death;
	bool iFrameEnabled;
	//int score;

	// shader stuff
	//GLProgram* charEffect;
	//LightEffect* lightEffect;
	
	//Sprite* mainSprite;
	int intDirX, intDirY;	// direction just to determine +ve or -ve movement
    float screenWidth, screenHeight;
	float fSpeed;
	Attack* AttackSystems;
	Node* actionnode;
    bool b_winGame;

    Vec2 startingPos;

	//ParticleFireworks* TrailParticles;
	//GUI* playerGUI;

    void DeleteFunnels();   // delete all funnels (when player dies)

public:
    // Touch Movement
	ParticleSystemQuad* _emitter;
    void SetTouchBegan(bool touch)
    {
        touchBegan = touch;
    }
    bool IsTouchBegan()
    {
        return touchBegan;
    }
	//ParticleFireworks* GetTrailParticleSystem()
	//{
	//	return TrailParticles;
	//}
	
	
    Vec2 prevTouchPosition;

    void SetMovementConstrain(Vec2& destination);


    bool b_shooting, b_movement;
	Sprite* mainSprite;
	void Init(const char* imgSource, const char* playerName, float X, float Y, Size playingSize);
	void Update(float dt);
	void AnimatePlayer(KEYCODE key);	// KEY_INPUT for direction
	
    void Die();
    void StopAnimation();
    void Respawn();
    void SetiFrames();
    bool GetiFrames();

	void iFrameUpdate(float dt);
	void SetMoveCharX(int dirX);	// keyboard
	void SetMoveCharY(int dirY);	// keyboard
	void MoveCharByCoord(float X, float Y);		// mouse

	void FireBasicBullet();
	void FireMissile();
	void FireLaser();
	void StopFiringLaser();

	void Upgrade();
	void UpgradeMissiles();
	void UpdateFunnels();

	int getLives();
	void setLives(int lives);

	int getScore();
	void AddScore()
	{
		score += 100 * scoreMultiplier;
	}

	//void SetLightEffect(LightEffect* _effect)
	//{
	//	lightEffect = _effect;
	//}
	void AddScoreMultiplier(float multipler)
	{
		scoreMultiplier += multipler;
	}
	float GetScoreMultiplier()
	{
		return scoreMultiplier;
	}
    Attack* GetAttackSystems()
    {
        return AttackSystems;
    }
	Sprite* GetSprite(void)
	{
		return mainSprite;
	}
	void SetDeath(bool death)
	{
		Death = death;
	}
	bool IsDead()
	{
		return Death;
	}
	//void SetPlayerGUI(GUI* gui)
	//{
	//	playerGUI = gui;
	//}
    void CompleteRespawn();


    void SetWinGame(bool win) { b_winGame = win; }
    bool IsGameWon() { return b_winGame; }
};

#endif