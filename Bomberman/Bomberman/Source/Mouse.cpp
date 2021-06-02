#include "Mouse.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel2.h"
#include <ctime>

Mouse::Mouse(int x, int y) : Entity(x, y)
{
	position.x = x;
	position.y = y;

	// animations

	// idle
	moveAnim.PushBack({ 0, 64, 32, 32 });
	moveAnim.loop = true;
	moveAnim.mustFlip = false;
	moveAnim.speed = 0.1f;

	// move
	moveAnim.PushBack({ 0, 64, 32, 32 });
	moveAnim.PushBack({ 33, 64, 32, 32 });
	moveAnim.loop = true;
	moveAnim.mustFlip = false;
	moveAnim.speed = 0.1f;

	
	// death
	deathAnim.PushBack({ 65, 64 , 32, 32 });
	deathAnim.PushBack({ 97, 64 , 32, 32 });
	deathAnim.loop = false;
	deathAnim.mustFlip = false;
	deathAnim.speed = 0.1f;

	currentAnim = &moveAnim;
	state = IDLE;
	direction = RIGHT;
	collider = App->collisions->AddCollider({ 0, 16, 16, 16 }, Collider::Type::ENEMY, (Module*)App->entities);
	colliderPosition.x = position.x;
	colliderPosition.y = position.y + 16;
	App->sceneLevel2->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = SceneLevel2::GridType::EMPTY;

}

void Mouse::Update()
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
				App->sceneLevel2->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = SceneLevel2::GridType::EMPTY;
				if (direction == UP) position.y--;
				else if (direction == DOWN) position.y++;
				else if (direction == LEFT) position.x--;
				else if (direction == RIGHT) position.x++;

				colliderPosition.x = position.x;
				colliderPosition.y = position.y + 16;

				App->sceneLevel2->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = SceneLevel2::GridType::POKAPOKA;
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

void Mouse::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::BOMB) {
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
			currentAnim = &moveAnim;
			direction = DOWN;
			break;

		case DOWN:
			direction = UP;
			currentAnim = &moveAnim;
			break;

		case RIGHT:
			direction = LEFT;
			currentAnim = &moveAnim;
			break;

		case LEFT:

			direction = RIGHT;
			currentAnim = &moveAnim;
			break;
		}
	}
}

void Mouse::CheckDirection()
{
	Direction availableDirections[4];
	int availableCount = 0;
	int randDirection = 0;
	bool canContinue = false;

	int x = (colliderPosition.x - 24) / 16;
	int y = (colliderPosition.y - 32) / 16;

	if (y != 10) {
		if (App->sceneLevel2->grid[y + 1][x] == SceneLevel2::GridType::EMPTY)
		{
			availableDirections[availableCount] = DOWN;
			availableCount++;
		}
	}
	if (y != 0)
	{
		if (y != 5 && x != 6)
		{
			if (App->sceneLevel2->grid[y - 1][x] == SceneLevel2::GridType::EMPTY)
			{
				availableDirections[availableCount] = UP;
				availableCount++;
			}
		}
	}
	if (x != 0)
	{
		if (App->sceneLevel2->grid[y][x - 1] == SceneLevel2::GridType::EMPTY)
		{
			availableDirections[availableCount] = LEFT;
			availableCount++;
		}
	}
	if (x != 12) {
		if (App->sceneLevel2->grid[y][x + 1] == SceneLevel2
			::GridType::EMPTY)
		{
			availableDirections[availableCount] = RIGHT;
			availableCount++;
		}
	}

	for (int i = 0; i < availableCount; i++) {
		if (availableDirections[i] == direction) canContinue = true;
	}

	if (canContinue == true)
	{
		int randnum = rand() % (100);

		if (randnum < 90) {
			canContinue = false;
		}
	}

	if (availableCount > 0 && canContinue == false)
	{
		randDirection = rand() % availableCount;
		direction = availableDirections[randDirection];


		switch (direction)
		{
		case Entity::UP: currentAnim = &moveAnim;
			break;
		case Entity::DOWN: currentAnim = &moveAnim;
			break;
		case Entity::RIGHT: currentAnim = &moveAnim;
			break;
		case Entity::LEFT: currentAnim = &moveAnim;
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
