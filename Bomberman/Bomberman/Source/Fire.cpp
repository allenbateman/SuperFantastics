#include "Fire.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Fire::Fire(int x, int y) : Powerup(x, y)
{
	position.x = x;
	position.y = y;

	idleAnim.PushBack({ 64,300, 16, 16 });
	currentAnim = &idleAnim;
}

void Fire::Update()
{

}

void Fire::OnCollision(Collider* collider)
{
	if (collider->PLAYER)
	{
		if (MAX_RANGE_EXPLOSION > App->player->rangeExplosion)
		{
			App->player->rangeExplosion += range;
		}
		SetToDelete();
	}
	
}