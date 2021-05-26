#include "Orb.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Orb::Orb(int x, int y) : Entity(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 24 + (y * 16);

	collider = App->collisions->AddCollider({ 24 + (x * 16),32 + (y * 16),16,16 }, Collider::Type::STRUCTURE,( Module*)App->entities);

	idleAnim.PushBack({ 452, 72, 15, 25 });
	currentAnim = &idleAnim;
}

void Orb::Update()
{
	if (collider->type == Collider::Type::EXPLOSION) {
		App->player->nOrbs++;
		SetToDelete();
	}
}