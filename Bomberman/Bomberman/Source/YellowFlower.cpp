#include "YellowFlower.h"

#include "Application.h"
#include "ModuleCollisions.h"

YellowFlower::YellowFlower(int x, int y) : Enemy(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 32 + (y * 16);

	App->collisions->AddCollider({ 24 + (x * 16),32 + (y * 16),16,16 }, Collider::Type::YELLOW_FLOWER);

	idleAnim.PushBack({ 400, 0, 16, 16 });
	currentAnim = &idleAnim;
}

void YellowFlower::Update()
{
}
