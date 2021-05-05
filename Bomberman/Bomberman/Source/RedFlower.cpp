#include "RedFlower.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"

RedFlower::RedFlower(int x, int y) : Entity(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 32 + (y * 16);
	state = IDLE;

	App->collisions->AddCollider({ 24 + (x * 16),32 + (y * 16),16,16 }, Collider::Type::RED_FLOWER);

	idleAnim.PushBack({ 400, 16, 16, 16 });

	deathAnim.PushBack({ 416, 0, 16, 16 });
	deathAnim.PushBack({ 432, 0, 16, 16 });
	deathAnim.PushBack({ 448, 0, 16, 16 });
	deathAnim.PushBack({ 464, 0, 16, 16 });
	deathAnim.loop = false;
	deathAnim.mustFlip = false;
	deathAnim.speed = 0.1f;
}

void RedFlower::Update()
{
	Entity::Update();

	switch (state)
	{
	case Entity::IDLE:
		currentAnim = &idleAnim;
		break;
	case Entity::DEATH:
		currentAnim = &deathAnim;
		if (deathAnim.HasFinished() == true) SetToDelete();
		break;
	}
}

void RedFlower::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::BOMB) {
		state = DEATH;
	}
}