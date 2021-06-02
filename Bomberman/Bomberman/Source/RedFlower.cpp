#include "RedFlower.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"

RedFlower::RedFlower(int x, int y) : Entity(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 32 + (y * 16);
	

	collider = App->collisions->AddCollider({ position.x,position.y,16,16 }, Collider::Type::RED_FLOWER, (Module*)App->entities);
	collider->SetPos(position.x, position.y);


	state = IDLE;
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
		collider->SetPos(position.x, position.y);
		break;
	case Entity::DEATH:
		currentAnim = &deathAnim;
		if (deathAnim.HasFinished() == true)
		{
			SetToDelete();
			App->sceneLevel1->SetGridType(SceneLevel1::GridType::EMPTY, position.y, position.x, 0, 0);
		}
		break;
	}
}

void RedFlower::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION) {
		state = DEATH;
	}
}