#include "Saru.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"
#include "ModulePlayer.h"
#include <ctime>

Saru::Saru(int x, int y) : Entity(x, y)
{
	position.x = x;
	position.y = y;


	// push back all animations






	currentAnim = &downAnim;
	state = IDLE;
	direction = DOWN;

	// must put better the colliders
	collider = App->collisions->AddCollider({ 8, 16, 16, 16 }, Collider::Type::ENEMY, (Module*)App->entities);
	colliderPosition.x = position.x + 8;
	colliderPosition.y = position.y + 16;
	App->sceneLevel1->grid[(colliderPosition.x - 24) / 16][(colliderPosition.y - 32) / 16] = SceneLevel1::GridType::EMPTY;
}


void Saru::Update()
{
	Entity::Update();


	switch (state)
	{
	case Entity::IDLE:

		//currentAnim = &idleAnim;
		if (PlayerNear() == true) state = MOVE;

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
				//if (upAnim.HasFinished() == true) upAnim.mustFlip = !upAnim.mustFlip;
				//if (downAnim.HasFinished() == true) downAnim.mustFlip = !downAnim.mustFlip;
				// FLIP ALL REQUIRED ANIMATIONS


				App->sceneLevel1->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = SceneLevel1::GridType::EMPTY;
				if (direction == UP) position.y--;
				else if (direction == DOWN) position.y++;
				else if (direction == LEFT) position.x--;
				else if (direction == RIGHT) position.x++;

				colliderPosition.x = position.x + 8;
				colliderPosition.y = position.y + 16;

				App->sceneLevel1->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = SceneLevel1::GridType::MECHA_WALKER;
			}
		}

		if (canStop == true) state = IDLE;

		break;
	case Entity::DEATH:
		currentAnim = &deathAnim;
		if (deathAnim.HasFinished() == true) SetToDelete();
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
		if (App->sceneLevel1->grid[y + 1][x] == SceneLevel1::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = DOWN;
			avaibleCount++;
		}
	}
	if (y != 0)
	{
		if (y != 5 && x != 6)
		{
			if (App->sceneLevel1->grid[y - 1][x] == SceneLevel1::GridType::EMPTY)
			{
				avaibleDirections[avaibleCount] = UP;
				avaibleCount++;
			}
		}
	}
	if (x != 0)
	{
		if (App->sceneLevel1->grid[y][x - 1] == SceneLevel1::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = LEFT;
			avaibleCount++;
		}
	}
	if (x != 12) {
		if (App->sceneLevel1->grid[y][x + 1] == SceneLevel1::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = RIGHT;
			avaibleCount++;
		}
	}

	//---------------------------Saru movement----------------------------------------------------
	iPoint playerPos = App->player->position;
	int difX = colliderPosition.x - playerPos.x;
	int difY = colliderPosition.y - playerPos.y;

	if (priority == HORIZONTAL) {
		if (difX > 0) {
			for (int i = 0; i < avaibleCount; i++)
				if (avaibleDirections[avaibleCount] == RIGHT) direction = avaibleDirections[avaibleCount];
		}
		else {
			for (int i = 0; i < avaibleCount; i++)
				if (avaibleDirections[avaibleCount] == LEFT) direction = avaibleDirections[avaibleCount];
		}
	}
	if (priority == VERTICAL) {
		if (difY > 0) {
			for (int i = 0; i < avaibleCount; i++)
				if (avaibleDirections[avaibleCount] == DOWN) direction = avaibleDirections[avaibleCount];
		}
		else {
			for (int i = 0; i < avaibleCount; i++)
				if (avaibleDirections[avaibleCount] == UP) direction = avaibleDirections[avaibleCount];
		}
	}

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
	
	if (avaibleCount >= 3) canStop = true;
	else false;
}

bool Saru::PlayerNear() {
	iPoint playerPos = App->player->position;
	int difX = colliderPosition.x - playerPos.x;
	int difY = colliderPosition.y - playerPos.y;

	if (difX < 0) difX *= -1;
	if (difY < 0) difY *= -1;
	
	if (difX < difY) priority = HORIZONTAL;
	else priority = VERTICAL;

	if (difX < 32 || difY < 32) return true;
	else return false;
}

void Saru::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION) {
		//state = DEATH;
		//currentAnim = &deathAnim;
		life--;
	}
}