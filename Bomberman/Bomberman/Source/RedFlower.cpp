#include "RedFlower.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"

RedFlower::RedFlower(int x, int y) : Enemy(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 32 + (y * 16);

	App->collisions->AddCollider({ 24 + (x * 16),32 + (y * 16),16,16 }, Collider::Type::RED_FLOWER);

	idleAnim.PushBack({ 400, 16, 16, 16 });

	deathAnim.PushBack({ 304, 0, 16, 16 });
	deathAnim.PushBack({ 320, 0, 16, 16 });
	deathAnim.PushBack({ 336, 0, 16, 16 });
	deathAnim.PushBack({ 356, 0, 16, 16 });
	idleAnim.loop = false;
	idleAnim.mustFlip = false;
	idleAnim.speed = 0.1f;
}

void RedFlower::Update()
{
	Enemy::Update();

	switch (state)
	{
	case Enemy::DEATH:
		currentAnim = &idleAnim;
		break;
	case Enemy::IDLE:
		currentAnim = &deathAnim;
		break;
	}
	

}

void RedFlower::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::BOMB) {
		state = DEATH;
		SetToDelete();
	}
}