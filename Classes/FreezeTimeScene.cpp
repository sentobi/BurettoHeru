#include "FreezeTimeScene.h"
#include "HelloWorldScene.h"

#include "SceneManager.h"
#include "AudioManager.h"
#include "Input.h"
//#include "AnimationHandler.h"

using namespace cocos2d;

USING_NS_CC;

std::vector<Vec2> FreezeTime::dashLinePoints;
bool FreezeTime::chargeUsed = false;

Scene* FreezeTime::createScene(Sprite* rendtexSprite)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = FreezeTime::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 997);

    // set background
    Sprite* rendTexture = Sprite::createWithTexture(rendtexSprite->getTexture());
    rendTexture->setTextureRect(Rect(0, 0, rendTexture->getTexture()->getContentSize().width, rendTexture->getTexture()->getContentSize().height + 10.f));
    rendTexture->setAnchorPoint(Point::ZERO);
    rendTexture->setPosition(Point::ZERO);
    rendTexture->setFlippedY(true);
    scene->addChild(rendTexture, -1);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FreezeTime::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    //this->schedule(schedule_selector(HelloWorld::update), 1.0);
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

    auto label = Label::createWithTTF("Click & Drag To Dash", "fonts/Batman.ttf", 32);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + 0.6f * visibleSize.height));

    // add the label as a child to this layer
    this->addChild(label, 2);

    // Keyboard Listener
    auto keyboardlistener = EventListenerKeyboard::create();
    keyboardlistener->onKeyPressed = CC_CALLBACK_2(FreezeTime::onKeyPressed, this);
    keyboardlistener->onKeyReleased = CC_CALLBACK_2(FreezeTime::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

    // Mouse Listener
    //auto mouseListener = EventListenerMouse::create();
    //mouseListener->onMouseDown = CC_CALLBACK_1(FreezeTime::onMouseDown, this);
    //mouseListener->onMouseMove = CC_CALLBACK_1(FreezeTime::onMouseMove, this);
    //mouseListener->onMouseUp = CC_CALLBACK_1(FreezeTime::onMouseUp, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // Touch Listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(FreezeTime::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(FreezeTime::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(FreezeTime::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    touchBegan = false;
    freezeTimeDone = false;
    drawPointTimer = 0.f;

    maxDashDistance = visibleSize.width * 1.7f; // slightly less than 2x width (2x width would be dash forward, then loop back)

    return true;
}

// Keyboard input
void FreezeTime::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_SHIFT:
        if (dashLinePoints.empty())
            freezeTimeDone = true;
        break;
    }
}

void FreezeTime::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}

// Touch Input
// Mouse input
bool FreezeTime::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 touchLocation = touch->getLocation();
    dashLinePoints.push_back(touchLocation);

    touchBegan = true;

    return true;
}

void FreezeTime::onTouchMoved(Touch* touch, Event * event)
{
    //EventMouse* mouseEvent = (EventMouse*)event;

    if (touchBegan && drawPointTimer > 0.1f)
    {
        if (dashDistance < maxDashDistance)
        {
            Vec2 touchLocation = touch->getLocation();

            dashLinePoints.push_back(touchLocation);

            std::vector<Vec2>::iterator prevPoint = dashLinePoints.end() - 2;

            DrawNode* draw = DrawNode::create();
            draw->drawLine(*prevPoint, touchLocation, Color4F::BLUE);
            addChild(draw, 1);

            drawPointTimer = 0.f;

            // add to dash distance
            dashDistance += (*prevPoint - touchLocation).length();
        }
    }
}

void FreezeTime::onTouchEnded(Touch* touch, Event * event)
{
    touchBegan = false;
    freezeTimeDone = true;
}


// Mouse input
/*void FreezeTime::onMouseDown(Event* event)
{
    EventMouse* mouseEvent = (EventMouse*)event;
    TOUCH_TYPE mousetype;

    switch (mouseEvent->getMouseButton())
    {
    case 0: // left mouse
        mousetype = TOUCH_MOUSELEFT;
        break;
    case 1: // right mouse
        mousetype = TOUCH_MOUSERIGHT;
        break;
    }

    Input::SetMouseState(mousetype, TOUCH_HELD);

    Vec2 point;
    point.set(mouseEvent->getCursorX(), mouseEvent->getCursorY());

    dashLinePoints.push_back(point);
}

void FreezeTime::onMouseMove(Event* event)
{
    EventMouse* mouseEvent = (EventMouse*)event;

    if (Input::GetTouchState(TOUCH_MOUSELEFT) == TOUCH_HELD
        && drawPointTimer > 0.1f)
    {
        if (dashDistance < maxDashDistance)
        {
            Vec2 point;
            point.setPoint(mouseEvent->getCursorX(), mouseEvent->getCursorY());

            dashLinePoints.push_back(point);

            std::vector<Vec2>::iterator prevPoint = dashLinePoints.end() - 2;

            DrawNode* draw = DrawNode::create();
            draw->drawLine(*prevPoint, point, Color4F::BLUE);
            addChild(draw, 1);

            drawPointTimer = 0.f;

            // add to dash distance
            dashDistance += (*prevPoint - point).length();
        }
    }
}

void FreezeTime::onMouseUp(Event* event)
{
    EventMouse* mouseEvent = (EventMouse*)event;
    TOUCH_TYPE mousetype;

    switch (mouseEvent->getMouseButton())
    {
    case 0: // left mouse
        mousetype = TOUCH_MOUSELEFT;
        break;
    case 1: // right mouse
        mousetype = TOUCH_MOUSERIGHT;
        break;
    }

    Input::SetMouseState(mousetype, TOUCH_RELEASED);
    Input::SetMousePos(mousetype, Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY()));

    freezeTimeDone = true;
}*/

void FreezeTime::update(float dt)
{
    drawPointTimer += dt;

    if (freezeTimeDone)
    {
        CCDirector::getInstance()->popScene();

        //if (dashLinePoints.size() > 1)    // don't use number of points to determine; use distance instead
        if (dashDistance > 10.f)    // moved certain distance
            chargeUsed = true;
        else
            chargeUsed = false;

        //auto scene = Director::getInstance()->getRunningScene();
        //auto layer = scene->getChildByTag(999);
        //HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
        //helloLayer->SetPlayerDashPoints(dashLinePoints);
    }
}