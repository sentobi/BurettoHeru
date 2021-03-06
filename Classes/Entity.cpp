#include "Entity.h"
#include "AnimationHandler.h"
Entity::Entity()
{
	_eSprite = Sprite::create("Blue_Front1.png");
	//_eSprite->setAnchorPoint(Vec2(1.f, 1.f));
    _eSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	_eSprite->setScale(0.5);
	_hp = 100;
	_active = false;
	DamagedRenderTimer=0.1f;
	DamagedRenderTempTimer=0.f;
	TakenDamage = false;
	auto physicsBody = PhysicsBody::createCircle(100,
		//Size(_eSprite->getContentSize().width, _eSprite->getContentSize().height),
		PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setCategoryBitmask(4);
	physicsBody->setCollisionBitmask(131);
	physicsBody->setContactTestBitmask(131);
	physicsBody->setTag(2);

	//physicsBody->setPositionOffset(Vec2(_eSprite->getContentSize().width, _eSprite->getContentSize().height*1.8f));
	_eSprite->addComponent(physicsBody);


}

void Entity::TakeDamage(int dmg)
{
 	if (!TakenDamage)
	TakenDamage = true;
    _hp -= dmg;
}

bool Entity::IsDead()
{
    return (_hp <= 0);
}

Entity::~Entity()
{

}
Sprite* Entity::GetSprite()
{
	return _eSprite;
}

void Entity::SetEntity(EnemyData data)
{
	_waveNum = data._waveNum;
	_spawnPos = data._spawnPos;
	_destination = data._destination;
	_exitDestination = data._exitDestination;

	switch (data._type)
	{

	case(1) :
		_type = CAPULE; break;
	case(2) :
		_type = PLATONIC; break;
	default:
		_type = NUM_TYPE; break;

	}
	//_eSprite->setAnchorPoint(Vec2::ZERO);
	//SetActive();
}

void Entity::SetInactive()
{
	//_eSprite->pause();
	//_eSprite->setVisible(false);
	_active = false;
}

void Entity::SetActive()
{
	//_eSprite->resume();
	//_eSprite->setVisible(true);
	_active = true;
}

void Entity::SettoSpawn()
{	
	_eSprite->setPosition(_spawnPos.x, _spawnPos.y);
	//AnimHandler::getInstance()->setAnimation(this_eSprite, AnimHandler::CAPULE_SPAWN, true);
	switch (_type)
	{
		case(CAPULE) : AnimHandler::GetInstance()->setAnimation(_eSprite, AnimHandler::CAPULE_SPAWN, false);
		break;
		case(PLATONIC) : AnimHandler::GetInstance()->setAnimation(_eSprite, AnimHandler::PLATONIC_SPAWN, false);
		break;
	}
	auto moveTo = MoveTo::create(1,_destination);
	//_eSprite->runAction(moveTo);//simple moveto
	auto setactive = CallFunc::create([this](){SettoAttack();});
	_eSprite->runAction(CCSequence::create(moveTo, CallFunc::create(CC_CALLBACK_0(Entity::SettoAttack, this)), NULL));//this is for the attack state
}

void Entity::SettoAttack()
{
	switch (_type)
	{
	case(CAPULE) : AnimHandler::GetInstance()->setAnimation(_eSprite, AnimHandler::CAPULE_ACTIVE, true);
		break;
	case(PLATONIC) : AnimHandler::GetInstance()->setAnimation(_eSprite, AnimHandler::PLATONIC_ACTIVE, true);
		break;
	}
	_active = true;

	//do sum attack code here


}

void Entity::SettoDespawn()
{
	auto moveTo = MoveTo::create(2, _exitDestination);
	if (_active == false)
		return;

	_eSprite->runAction(moveTo);//simple moveto
	_active = false;
	//auto deactivate = CallFunc::create([this](){SetInactive(); });
	//_eSprite->runAction(CCSequence::create(moveTo,deactivate));//this is for the attack state
}

void Entity::DoAttack(float dt)
{

}
