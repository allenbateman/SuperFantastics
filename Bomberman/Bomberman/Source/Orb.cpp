#include "Orb.h"

#include "Application.h"
#include "ModuleCollisions.h"

Orb::Orb(int x, int y) : Enemy(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 32 + (y * 16);

	App->collisions->AddCollider({ 24 + (x * 16),32 + (y * 16),16,16 }, Collider::Type::STRUCTURE);

	idleAnim.PushBack({ 400, 0, 16, 16 });
	currentAnim = &idleAnim;
}

void Orb::Update()
{
}