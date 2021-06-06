#include "CoreMechaWalker.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleLevel.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include <ctime>

CoreMechaWalker::CoreMechaWalker(int x, int y) : Entity(x, y)
{
	position.x = x;
	position.y = y;


	// idle
	idleAnim.PushBack({ 128, 64,32,32 });
	idleAnim.loop = true;
	idleAnim.mustFlip = false;
	idleAnim.speed = 0.1f;

	// move up
	upAnim.PushBack({ 192, 64,32,32 });
	upAnim.PushBack({ 224, 64,32,32 });
	upAnim.loop = true;
	upAnim.mustFlip = false;
	upAnim.speed = 0.1f;

	// move down
	downAnim.PushBack({ 128, 64,32,32 });
	downAnim.PushBack({ 160, 64,32,32 });
	downAnim.loop = true;
	downAnim.mustFlip = false;
	downAnim.speed = 0.1f;

	// move left
	leftAnim.PushBack({ 256, 64,32,32 });
	leftAnim.PushBack({ 288, 64,32,32 });
	leftAnim.PushBack({ 320, 64,32,32 });
	leftAnim.loop = true;
	leftAnim.mustFlip = false;
	leftAnim.speed = 0.1f;

	// move right
	rightAnim.PushBack({ 256, 64,32,32 });
	rightAnim.PushBack({ 288, 64,32,32 });
	rightAnim.PushBack({ 320, 64,32,32 });
	rightAnim.loop = true;
	rightAnim.mustFlip = true;
	rightAnim.speed = 0.1f;

	// death
	deathAnim.PushBack({ 352, 64,32,32 });
	deathAnim.loop = false;
	deathAnim.mustFlip = false;
	deathAnim.speed = 0.1f;

	score.PushBack({ 80,248,16,8 });

	currentAnim = &idleAnim;
	state = IDLE;
	direction = RIGHT;
	collider = App->collisions->AddCollider({ 8, 16, 16, 16 }, Collider::Type::ENEMY, (Module*)App->entities);
	colliderPosition.x = position.x + 8;
	colliderPosition.y = position.y + 16;
	App->levelManager->grid[(colliderPosition.x - 24) / 16][(colliderPosition.y - 32) / 16] = Module::GridType::EMPTY;

	scorePoints = 400;
}


void CoreMechaWalker::Update()
{
	Entity::Update();


	switch (state)
	{
	case Entity::IDLE:

		currentAnim = &idleAnim;
		CheckDirection();
		break;

	case Entity::MOVE:
		count++;
		if ((App->frameCounter % 2) && count > 30) {

			if ((colliderPosition.x - 24) % 16 == 0 && (colliderPosition.y - 32) % 16 == 0) CheckDirection();

			if (state != IDLE)
			{
				if (upAnim.HasFinished() == true) upAnim.mustFlip = !upAnim.mustFlip;
				if (downAnim.HasFinished() == true) downAnim.mustFlip = !downAnim.mustFlip;

				App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::EMPTY;
				if (direction == UP) position.y--;
				else if (direction == DOWN) position.y++;
				else if (direction == LEFT) position.x--;
				else if (direction == RIGHT) position.x++;

				colliderPosition.x = position.x + 8;
				colliderPosition.y = position.y + 16;

				App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::MECHA_WALKER;
			}
		}

		break;
	case Entity::DEATH:
		if (deathAnim.HasFinished() == true) {
			state = SCORE;
			count = 0;
			position.y = colliderPosition.y + 8 + 4;
			position.x = colliderPosition.x;
		}
		break;
	case Entity::SCORE:
		count++;
		currentAnim = &score;
		if (count > 30)
		{
			scorePoints = 400 / 2;
			App->player->score += scorePoints;
			App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::EMPTY;
			SetToDelete();
		}
		break;
	default:
		break;
	}


}


void CoreMechaWalker::CheckDirection()
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

	for (int i = 0; i < avaibleCount; i++) {
		if (avaibleDirections[i] == direction) canContinue = true;
	}

	if (canContinue == true)
	{
		int randnum = rand() % (100);

		if (randnum < 60) {
			canContinue = false;
		}
	}

	if (avaibleCount > 0 && canContinue == false)
	{
		randDirection = rand() % avaibleCount;
		direction = avaibleDirections[randDirection];


		switch (direction)
		{
		case Entity::UP: currentAnim = &upAnim;
			break;
		case Entity::DOWN: currentAnim = &downAnim;
			break;
		case Entity::RIGHT: currentAnim = &rightAnim;
			break;
		case Entity::LEFT: currentAnim = &leftAnim;
			break;
		case Entity::NONE:
			break;
		default:
			break;
		}
		state = MOVE;
	}
	else state = IDLE;

}

void CoreMechaWalker::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION) {
		if (collider != nullptr) {
			collider->pendingToDelete = true;
			collider = nullptr;
		}
		state = DEATH;
		currentAnim = &deathAnim;
	}
	if (collider != nullptr) if (collider->type == Collider::Type::ENEMY)
	{
		/*if (direction == UP) position.y++;
		else if (direction == DOWN) position.y--;
		else if (direction == LEFT) position.x++;
		else if (direction == RIGHT) position.x--;*/
		switch (direction)
		{
		case UP:
			currentAnim = &downAnim;
			direction = DOWN;
			break;

		case DOWN:
			direction = UP;
			currentAnim = &upAnim;
			break;

		case RIGHT:
			direction = LEFT;
			currentAnim = &leftAnim;
			break;

		case LEFT:
			direction = RIGHT;
			currentAnim = &rightAnim;
			break;
		}
	}
}