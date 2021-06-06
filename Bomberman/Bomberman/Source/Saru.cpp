#include "Saru.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleLevel.h"
#include "ModulePlayer.h"
#include "Bananacher.h"
#include <ctime>

Saru::Saru(int x, int y) : Entity(x, y)
{
	position.x = x;
	position.y = y;


	// idle
	idleAnim.PushBack({ 192, 96, 32, 32 });
	idleAnim.PushBack({ 224, 96, 32, 32 });
	idleAnim.PushBack({ 256, 96, 32, 32 });
	idleAnim.PushBack({ 288, 96, 32, 32 });
	idleAnim.PushBack({ 192, 128, 32, 32 });
	idleAnim.PushBack({ 224, 128, 32, 32 });
	idleAnim.PushBack({ 256, 128, 32, 32 });
	idleAnim.PushBack({ 288, 128, 32, 32 });
	idleAnim.loop = true;
	idleAnim.mustFlip = false;
	idleAnim.speed = 0.1f;

	// down
	downAnim.PushBack({ 192, 160, 32, 32 });
	downAnim.PushBack({ 224, 160, 32, 32 });
	downAnim.loop = true;
	downAnim.mustFlip = false;
	downAnim.speed = 0.1f;

	// right
	rightAnim.PushBack({ 192, 192, 32, 32 });
	rightAnim.PushBack({ 224, 192, 32, 32 });
	rightAnim.loop = true;
	rightAnim.mustFlip = false;
	rightAnim.speed = 0.1f;

	// left
	leftAnim.PushBack({ 192, 192, 32, 32 });
	leftAnim.PushBack({ 224, 192, 32, 32 });
	leftAnim.loop = true;
	leftAnim.mustFlip = true;
	leftAnim.speed = 0.1f;

	// up
	upAnim.PushBack({ 192, 224, 32, 32 });
	upAnim.PushBack({ 224, 224, 32, 32 });
	upAnim.loop = true;
	upAnim.mustFlip = true;
	upAnim.speed = 0.1f;

	currentAnim = &downAnim;
	state = IDLE;
	direction = RIGHT;

	// must put better the colliders
	collider = App->collisions->AddCollider({ 8, 16, 16, 16 }, Collider::Type::ENEMY, (Module*)App->entities);
	colliderPosition.x = position.x + 8;
	colliderPosition.y = position.y + 16;
	App->levelManager->grid[(colliderPosition.x - 24) / 16][(colliderPosition.y - 32) / 16] = Module::GridType::EMPTY;
}


void Saru::Update()
{
	Entity::Update();

	if (life <= 0)
	{
		App->player->defeatedBoss = true;
		state = DEATH;
	}
	else {
		if (App->player->defeatedBoss == true) state = DEATH;
	}

	switch (state)
	{
	case Entity::IDLE:

		//currentAnim = &idleAnim;
		if (PlayerNear() == true) state = MOVE;
		currentAnim = &idleAnim;
		break;

	case Entity::MOVE:
		//awakeCount++;
		if ((App->frameCounter % 2) && canStop == false) {

			if ((colliderPosition.x - 24) % 16 == 0 && (colliderPosition.y - 32) % 16 == 0) {
				bool exampleVar = PlayerNear();
				CheckDirection();
			}

			if (state != IDLE)
			{
				if (upAnim.HasFinished() == true) upAnim.mustFlip = !upAnim.mustFlip;
				if (downAnim.HasFinished() == true) downAnim.mustFlip = !downAnim.mustFlip;

				//App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::EMPTY;
				switch (direction)
				{
				case Entity::UP:
					currentAnim = &upAnim;
					position.y--;
					break;
				case Entity::DOWN:
					currentAnim = &downAnim;
					position.y++;
					break;
				case Entity::RIGHT:
					currentAnim = &rightAnim;
					position.x++;
					break;
				case Entity::LEFT:
					currentAnim = &leftAnim;
					position.x--;
					break;
				case Entity::NONE:
					break;
				default:
					break;
				}

				colliderPosition.x = position.x + 8;
				colliderPosition.y = position.y + 16;

				//App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::SARU;
			}
		}

		if (canStop == true) state = IDLE;

		break;
	case Entity::DEATH:
		currentAnim = nullptr;//&deathAnim;
		if (collider != nullptr) {
			collider->pendingToDelete = true;
			collider = nullptr;
		}
		SetToDelete();
		break;
	default:
		break;
	}


}


void Saru::CheckDirection()
{
	Direction avaibleDirections[4];
	int avaibleCount = 0;
	int randDirection = 0;
	bool canContinue = false;

	int x = (colliderPosition.x - 24) / 16;
	int y = (colliderPosition.y - 32) / 16;

	if (y != 10) {
		if (App->levelManager->grid[y + 1][x] == Module::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = DOWN;
			avaibleCount++;
		}
	}
	if (y != 0)
	{
		if (y != 5 && x != 6)
		{
			if (App->levelManager->grid[y - 1][x] == Module::GridType::EMPTY)
			{
				avaibleDirections[avaibleCount] = UP;
				avaibleCount++;
			}
		}
	}
	if (x != 0)
	{
		if (App->levelManager->grid[y][x - 1] == Module::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = LEFT;
			avaibleCount++;
		}
	}
	if (x != 12) {
		if (App->levelManager->grid[y][x + 1] == Module::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = RIGHT;
			avaibleCount++;
		}
	}

	//---------------------------Saru movement----------------------------------------------------
	iPoint playerPos = App->player->position;
	iPoint diff;

	diff.x = colliderPosition.x - playerPos.x;
	diff.y = colliderPosition.y - playerPos.y;
	if (diff.x < 0) diff.x *= -1;
	if (diff.y < 0) diff.y *= -1;

	if (avaibleCount >= 3) {
		if (diff.x < diff.y) {
			if (colliderPosition.y > playerPos.y) direction = DOWN;
			else direction = UP;
			if (colliderPosition.x > playerPos.x) direction = RIGHT;
			else direction = LEFT;
		}
		else
		{
			if (colliderPosition.x > playerPos.x) direction = RIGHT;
			else direction = LEFT;
			if (colliderPosition.y > playerPos.y) direction = DOWN;
			else direction = UP;
		}
	}


	

	switch (direction)
	{
	case Entity::UP:
		if (y <= 0) direction = DOWN;
		break;
	case Entity::DOWN:
		if (y >= 10) direction = RIGHT;
		break;
	case Entity::RIGHT:
		if (x >= 12) direction = LEFT;
		break;
	case Entity::LEFT:
		if (x <= 0) direction = RIGHT;
		break;
	case Entity::NONE:
		break;
	default:
		break;
	}


	if (avaibleCount >= 3) canStop = true;
	else false;
}

bool Saru::PlayerNear() {
	bool ret;
	iPoint playerPos = App->player->position;
	int difX = colliderPosition.x - playerPos.x;
	int difY = colliderPosition.y - playerPos.y;



	if ((difX < 48 && difX>-48) && (difY < 48 && difY>-48))
	{
		canStop = false;
		ret = true;

		if (difX < 0) difX *= -1;
		if (difY < 0) difY *= -1;

	}
	else ret = false;

	return ret;
}

void Saru::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION && inmunity == false) {
		//state = DEATH;
		inmunity = true;
		count = 0;
		life--;
		//currentAnim = &deathAnim;
	}
}
