#include "Platonic.h"
#include "Attack/Projectile.h"
Platonic::Platonic()
{
	timer = 0;
}

Platonic::~Platonic()
{

}

void Platonic::DoAttack(float dt)
{
	timer += dt;
	if (timer > 1.2)
	{
		for (int i = 0; i < 3; i++)
		{
			Vec2 dir(-3, -1);
			dir.y += i;
			Projectile* projectile = new Projectile();
			projectile->InitBasicBullet("Projectiles/enemy_bullet.png", _eSprite->getPosition(), dir.getNormalized(),1200,true,10);
		}
		timer = 0;
	}
}