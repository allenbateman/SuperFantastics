#include "Fire.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"

Fire::Fire(int x, int y) : Entity(x, y)
{
	position.x = x;
	position.y = y;

	idleAnim.PushBack({ 64,304, 16, 16 });
	currentAnim = &idleAnim;

	collider = App->collisions->AddCollider({ position.x,position.y,16,16 }, Collider::Type::POWER_UP, (Module*)App->entities);
}

void Fire::Update()
{

}

void Fire::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER)
	{
		if (MAX_RANGE_EXPLOSION > App->player->rangeExplosion)
		{
			App->player->rangeExplosion += range;
		}
		SetToDelete();
	}
	
}