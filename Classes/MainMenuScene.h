#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class MainMenu : public cocos2d::Layer
{
private:
    GLProgram* proPostProcess;
    RenderTexture* rendtex;
    Sprite* rendtexSprite;

	Label* StartText;
	Label* OptionsText;
	Label* ExitText;

	Sprite* StartButton;
	Sprite* OptionsButton;
	Sprite* ExitButton;

    bool touchBegan;
	bool startGame;
	bool OptionSelected;
	
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


	bool TouchCollideWithLabel(Node* NodeA , Vec3 TouchPos);

    // callback functions
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onMouseDown(Event*);
    virtual void onMouseUp(Event*);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event * event);

	const float currentWidth = 1920;
	const float currentHeight = 1080;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void update(float dt);
    //bool isKeyHeld(EventKeyboard::KeyCode keyCode);

    Size playingSize;
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
	//float
    Sprite *bg_sprite;
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__
