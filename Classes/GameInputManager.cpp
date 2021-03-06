#include "GameInputManager.h"
#include "SceneManager.h"
#include "HelloWorldScene.h"

void GameInputManager::Init()
{
    keyControls.insert(std::pair<string, KEYCODE>("MoveRight", KEY_RIGHT));
    keyControls.insert(std::pair<string, KEYCODE>("MoveLeft", KEY_LEFT));
    keyControls.insert(std::pair<string, KEYCODE>("MoveUp", KEY_UP));
    keyControls.insert(std::pair<string, KEYCODE>("MoveDown", KEY_DOWN));
    keyControls.insert(std::pair<string, KEYCODE>("Shoot", KEY_SPACE));
    keyControls.insert(std::pair<string, KEYCODE>("ResetScene", KEY_R));
	//keyControls.insert(std::pair<string, KEYCODE>("FireLaser", KEY_ALT));
    keyControls.insert(std::pair<string, KEYCODE>("FreezeTime", KEY_SHIFT));
}

void GameInputManager::WhenKeyPressed(KEYCODE keyCode, Player* player)
{
    if (!player->b_movement)
        return;
    
    if (keyCode == KEYS_TOTAL)
        return;

    Input::OnKeyPressed(keyCode);



    if (keyCode == keyControls["MoveRight"]) {
        player->AnimatePlayer(KEY_RIGHT);
        player->SetMoveCharX(1);
    }
    else if (keyCode == keyControls["MoveLeft"]) {
        player->AnimatePlayer(KEY_LEFT);
        player->SetMoveCharX(-1);
    }
    else if (keyCode == keyControls["MoveUp"]) {
        player->AnimatePlayer(KEY_UP);
        player->SetMoveCharY(1);
    }
    else if (keyCode == keyControls["MoveDown"]) {
        player->AnimatePlayer(KEY_DOWN);
        player->SetMoveCharY(-1);
    }
    else if (keyCode == keyControls["Shoot"]) {
        if (player->b_movement) {
            if (player->GetAttackSystems()->IsLaserMode())
                player->FireLaser();
            else
                player->FireBasicBullet();
        }
    }
	//else if (keyCode == keyControls["FireLaser"]) {
	//	// player shoot here
	//	player->FireLaser();
	//}
    else if (keyCode == keyControls["ResetScene"]) {
        Input::OnKeyPressed(KEY_R);
        //SceneManager::GetInstance()->ChangeScene("HelloWorld");
    }
    else if (keyCode == keyControls["FreezeTime"]) {
        Input::OnKeyPressed(KEY_SHIFT);
        if (player->b_movement && player->GetAttackSystems()->IsChargeBarMax())
        {
            auto scene = Director::getInstance()->getRunningScene();
            auto layer = scene->getChildByTag(999);
            HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
            helloLayer->ExecuteFreezeTime();
        }
    }

}

void GameInputManager::WhenKeyReleased(KEYCODE keyCode, Player* player)
{
    if (keyCode == KEYS_TOTAL)
        return;

    Input::OnKeyReleased(keyCode);

    if (keyCode == keyControls["MoveRight"]) {
        if (Input::IsKeyHeld(KEY_LEFT))
            player->SetMoveCharX(-1);
        else
            player->SetMoveCharX(0);
        //	mainPlayer->setLeftOrRight(1, false);
        //RightPressed = false;
    }
    else if (keyCode == keyControls["MoveLeft"]) {
        if (Input::IsKeyHeld(KEY_RIGHT))
            player->SetMoveCharX(1);
        else
            player->SetMoveCharX(0);
        //	mainPlayer->setLeftOrRight(-1, false);//LeftPressed = false;
    }
    else if (keyCode == keyControls["MoveUp"]) {
        if (Input::IsKeyHeld(KEY_DOWN))
            player->SetMoveCharY(-1);
        else
            player->SetMoveCharY(0);
        //mainPlayer->setUpOrDown(1, false);
    }
    else if (keyCode == keyControls["MoveDown"]) {
        if (Input::IsKeyHeld(KEY_UP))
            player->SetMoveCharY(1);
        else
            player->SetMoveCharY(0);
        //mainPlayer->setUpOrDown(-1, false);
    }
    else if (keyCode == keyControls["Shoot"]) {
        if (player->b_movement) {
            if (player->GetAttackSystems()->IsLaserMode())
                player->StopFiringLaser();
        }
    }

	//else if (keyCode == keyControls["FireLaser"]) {
	//	// player shoot here
	//	player->StopFiringLaser();
	//}
    else if (keyCode == keyControls["ResetScene"]) {
        if (player->getLives() < 0 || player->IsGameWon()) {

            player->SetTouchBegan(false);

            auto scene = Director::getInstance()->getRunningScene();
            auto layer = scene->getChildByTag(999);
            HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);

            helloLayer->ExitScene();

            SceneManager::GetInstance()->ChangeScene("FacebookScene");
        }
    }
    else if (keyCode == keyControls["FreezeTime"]) {

    }

}

bool GameInputManager::IsKeyHeld(string key)
{
    return Input::IsKeyHeld(keyControls[key]);
}