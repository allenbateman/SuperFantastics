#include "Snail.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleLevel.h"
#include <ctime>

Snail::Snail(int x, int y) : Entity (x, y)
{
	position.x = x;
	position.y = y;

	idleAnim.PushBack({ 0,32,32,32 });
	idleAnim.loop = true;
	idleAnim.mustFlip = false;
	idleAnim.speed = 0.1f;

	// move down
	downAnim.PushBack({ 0,32,32,32 });
	downAnim.PushBack({ 32,32,32,32 });
	downAnim.PushBack({ 64,32,32,32 });
	downAnim.loop = true;
	downAnim.mustFlip = false;
	downAnim.speed = 0.1f;

	// move left
	leftAnim.PushBack({ 96,32,32,32 });
	leftAnim.PushBack({ 128,32,32,32 });
	leftAnim.PushBack({ 160,32,32,32 });
	leftAnim.loop = true;
	leftAnim.mustFlip = false;
	leftAnim.speed = 0.1f;

	// move up
	upAnim.PushBack({ 192,32,32,32 });
	upAnim.PushBack({ 224,32,32,32 });
	upAnim.PushBack({ 256,32,32,32 });
	upAnim.loop = true;
	upAnim.mustFlip = false;
	upAnim.speed = 0.1f;

	// move right
	rightAnim.PushBack({ 96,32,32,32 });
	rightAnim.PushBack({ 128,32,32,32 });
	rightAnim.PushBack({ 160,32,32,32 });
	rightAnim.loop = true;
	rightAnim.mustFlip = true;
	rightAnim.speed = 0.1f;

	// death
	deathAnim.PushBack({ 288,32,32,32 });
	deathAnim.PushBack({ 320,32,32,32 });
	deathAnim.loop = false;
	deathAnim.mustFlip = false;
	deathAnim.speed = 0.1f;

	currentAnim = &rightAnim;
	state = IDLE;
	direction = RIGHT;
	collider = App->collisions->AddCollider({ 0, 16, 16, 16 }, Collider::Type::ENEMY, (Module*)App->entities);
	colliderPosition.x = position.x;
	colliderPosition.y = position.y + 16;
	drawOffset.x = -8;
	App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::EMPTY;
	scorePoints = 100;
}

void Snail::Update()
{
	Entity::Update();


	switch (state)
	{
	case Entity::IDLE:

		currentAnim = &idleAnim;
		CheckDirection();
		break;

	case Entity::MOVE:
		if ((App->frameCounter % 2)) {

			if ((colliderPosition.x - 24) % 16 == 0 && (colliderPosition.y - 32) % 16 == 0) CheckDirection();

			if (state != IDLE)
			{
				App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::EMPTY;
				if (direction == UP) position.y--;
				else if (direction == DOWN) position.y++;
				else if (direction == LEFT) position.x--;
				else if (direction == RIGHT) position.x++;

				colliderPosition.x = position.x;
				colliderPosition.y = position.y + 16;

				App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::SNAIL;
			}
		}

		break;

	case Entity::DEATH:
		if (deathAnim.HasFinished() == true) SetToDelete();
		break;
	default:
		break;
	}


}

void Snail::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION) {
		state = DEATH;
		currentAnim = &deathAnim;
	}
	if (collider->type == Collider::Type::ENEMY)
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

void Snail::CheckDirection()
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

		if (randnum < 90) {
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
