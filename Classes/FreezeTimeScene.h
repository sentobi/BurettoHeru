#ifndef __FREEZETIME_SCENE_H__
#define __FREEZETIME_SCENE_H__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;

class FreezeTime : public Layer
{
private:
    //Label* descriptionLabel;

    Sprite* playerDash;
    Sprite* playerDashLine;

    Sprite* rendtexSprite;

    //int drawCount;

    bool touchBegan;
    bool freezeTimeDone;

    float drawPointTimer;

public:
    static cocos2d::Scene* createScene(Sprite* rendtexSprite);
    float dashDistance;
    float maxDashDistance;

    virtual bool init();

    // callback functions
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*);
    //virtual void onMouseDown(Event*);
    //virtual void onMouseMove(Event*);
    //virtual void onMouseUp(Event*);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event * event);
    void onTouchEnded(Touch* touch, Event * event);

    static std::vector<Vec2> dashLinePoints;
    static bool chargeUsed;

    void update(float dt);
    //bool isKeyHeld(EventKeyboard::KeyCode keyCode);

    Size playingSize;

    // implement the "static create()" method manually
    CREATE_FUNC(FreezeTime);
};

#endif // __MAINMENU_SCENE_H__
