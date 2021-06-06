#include "RedFlower.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleLevel.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"

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

	score.PushBack({ 25,248,13,8 });
	score.loop = true;
	score.mustFlip = false;
	score.speed = 0.1f;

	scorePoints = 100;
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
		if (deathAnim.HasFinished() == true) {
			state = SCORE;
			currentAnim = nullptr;
			count = 0;
			position.y += 4;
		}
		break;
	case Entity::SCORE:
		currentAnim = &score;
		if (count > 30)
		{
			scorePoints = 100/2;
			App->player->score += scorePoints;
			App->levelManager->SetGridType(Module::GridType::EMPTY, position.y, position.x, 0, 0);
			count = 0;
			SetToDelete();
		}
		else count++;
	}
}

void RedFlower::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION) {
		state = DEATH;
		if (collider != nullptr) {
			collider->pendingToDelete = true;
			collider = nullptr;
		}
	}
}