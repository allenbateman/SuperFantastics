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

	// MOVEMENT??????????????????????????

}

void Mouse::Update()
{
	//do
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
	Direction avaibleDirections[4];
	int avaibleCount = 0;
	int randDirection = 0;
	bool canContinue = false;

	int x = (colliderPosition.x - 24) / 16;
	int y = (colliderPosition.y - 32) / 16;

	if (y != 10) {
		if (App->sceneLevel2->grid[y + 1][x] == SceneLevel2::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = DOWN;
			avaibleCount++;
		}
	}
	if (y != 0)
	{
		if (y != 5 && x != 6)
		{
			if (App->sceneLevel2->grid[y - 1][x] == SceneLevel2::GridType::EMPTY)
			{
				avaibleDirections[avaibleCount] = UP;
				avaibleCount++;
			}
		}
	}
	if (x != 0)
	{
		if (App->sceneLevel2->grid[y][x - 1] == SceneLevel2::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = LEFT;
			avaibleCount++;
		}
	}
	if (x != 12) {
		if (App->sceneLevel2->grid[y][x + 1] == SceneLevel2
			::GridType::EMPTY)
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
