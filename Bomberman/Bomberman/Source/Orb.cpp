#include "Orb.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleLevel.h"

Orb::Orb(int x, int y) : Entity(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 24 + (y * 16);

	collider = App->collisions->AddCollider({ 24 + (x * 16),32 + (y * 16),16,16 }, Collider::Type::ORB,( Module*)App->entities);

	idleAnim.PushBack({ 452, 72, 15, 27 });

	score.PushBack({ 112,248,16,8 });
	score.loop = true;
	score.mustFlip = false;
	score.speed = 0.1f;

	currentAnim = &idleAnim;
	scorePoints = 800;
}

void Orb::Update()
{
	switch (state)
	{
	case Entity::SCORE:
		currentAnim = &score;
		if (count > 30)
		{
			scorePoints = 800 / 2;
			App->player->score += scorePoints;
			App->levelManager->SetGridType(Module::GridType::EMPTY, position.y, position.x, 0, 0);
			count = 0;
			SetToDelete();
		}
		else count++;
	}
}

void Orb::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION) {
		App->levelManager->orbsLeft--;
		state = SCORE;
		count = 0;
		position.y += 4+8;
		if (collider != nullptr) {
			collider->pendingToDelete = true;
			collider = nullptr;
		}
	}
}