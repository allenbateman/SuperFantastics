#include "Bananacher.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleLevel.h"
#include "ModulePlayer.h"
#include "Saru.h"
#include <ctime>

Bananacher::Bananacher(int x, int y) : Entity(x, y)
{
	position.x = x;
	position.y = y;


	// down
	downAnim.PushBack({ 512,0,48,64 });
	downAnim.PushBack({ 560,0,48,64 });
	downAnim.PushBack({ 608,0,48,64 });
	downAnim.PushBack({ 656,0,48,64 });
	downAnim.PushBack({ 704,0,48,64 });
	downAnim.PushBack({ 752,0,48,64 });
	downAnim.PushBack({ 800,0,48,64 });
	downAnim.PushBack({ 848,0,48,64 });
	downAnim.loop = true;
	downAnim.mustFlip = false;
	downAnim.speed = 0.1f;

	// left
	leftAnim.PushBack({ 512,64,48,64 });
	leftAnim.PushBack({ 560,64,48,64 });
	leftAnim.PushBack({ 608,64,48,64 });
	leftAnim.PushBack({ 656,64,48,64 });
	leftAnim.PushBack({ 704,64,48,64 });
	leftAnim.PushBack({ 752,64,48,64 });
	leftAnim.PushBack({ 800,64,48,64 });
	leftAnim.PushBack({ 848,64,48,64 });
	leftAnim.loop = true;
	leftAnim.mustFlip = false;
	leftAnim.speed = 0.1f;

	// right
	rightAnim.PushBack({ 512,64,48,64 });
	rightAnim.PushBack({ 560,64,48,64 });
	rightAnim.PushBack({ 608,64,48,64 });
	rightAnim.PushBack({ 656,64,48,64 });
	rightAnim.PushBack({ 704,64,48,64 });
	rightAnim.PushBack({ 752,64,48,64 });
	rightAnim.PushBack({ 800,64,48,64 });
	rightAnim.PushBack({ 848,64,48,64 });
	rightAnim.loop = true;
	rightAnim.mustFlip = true;
	rightAnim.speed = 0.1f;

	// up
	upAnim.PushBack({ 512,128,48,64 });
	upAnim.PushBack({ 560,128,48,64 });
	upAnim.PushBack({ 608,128,48,64 });
	upAnim.PushBack({ 656,128,48,64 });
	upAnim.PushBack({ 704,128,48,64 });
	upAnim.PushBack({ 752,128,48,64 });
	upAnim.PushBack({ 800,128,48,64 });
	upAnim.loop = true;
	upAnim.mustFlip = false;
	upAnim.speed = 0.1f;

	// death
	deathAnim.PushBack({ 112,272,64,80 });
	deathAnim.PushBack({ 176,272,64,80 });
	deathAnim.PushBack({ 240,272,64,80 });
	deathAnim.PushBack({ 304,272,64,80 });
	deathAnim.PushBack({ 368,272,64,80 });
	deathAnim.PushBack({ 432,272,64,80 });
	deathAnim.PushBack({ 496,272,64,80 });
	deathAnim.PushBack({ 560,272,64,80 });
	deathAnim.PushBack({ 624,272,64,80 });
	deathAnim.PushBack({ 688,272,64,80 });
	deathAnim.PushBack({ 752,272,64,80 });
	deathAnim.PushBack({ 816,272,64,80 });

	deathAnim.PushBack({ 112,352,64,80 });
	deathAnim.PushBack({ 176,352,64,80 });
	deathAnim.PushBack({ 240,352,64,80 });
	deathAnim.PushBack({ 304,352,64,80 });
	deathAnim.PushBack({ 368,352,64,80 });
	deathAnim.PushBack({ 432,352,64,80 });
	deathAnim.PushBack({ 496,352,64,80 });
	deathAnim.PushBack({ 560,352,64,80 });
	deathAnim.PushBack({ 624,352,64,80 });
	deathAnim.PushBack({ 688,352,64,80 });
	deathAnim.PushBack({ 752,352,64,80 });

	deathAnim.loop = false;
	deathAnim.mustFlip = false;
	upAnim.speed = 0.1f;


	currentAnim = &downAnim;
	state = MOVE;
	direction = DOWN;

	// must put better the colliders
	collider = App->collisions->AddCollider({ 16, 48, 16, 16 }, Collider::Type::ENEMY, (Module*)App->entities);
	colliderPosition.x = position.x + 16;
	colliderPosition.y = position.y + 48;
	App->levelManager->grid[(colliderPosition.x - 24) / 16][(colliderPosition.y - 32) / 16] = Module::GridType::EMPTY;
}


void Bananacher::Update()
{
	Entity::Update();

	//App->sceneBossFight->
	if (life <= 0)
	{
		App->player->defeatedBoss = true;
		state = DEATH;
	}
	else {
		if (App->player->defeatedBoss == true) state = DEATH;
	}

	if (inmunity == true) {
		count++;
		if (count > 60) inmunity = false;
	}

	switch (state)
	{
	case Entity::MOVE:
		//awakeCount++;
		if ((App->frameCounter % 2)) {

			if ((colliderPosition.x - 24) % 16 == 0 && (colliderPosition.y - 32) % 16 == 0) CheckDirection();

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

			colliderPosition.x = position.x + 16;
			colliderPosition.y = position.y + 48;

			//App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::BANANACHER;
		}

		break;
	case Entity::DEATH:
		currentAnim = &deathAnim;
		if (deathAnim.HasFinished() == true) {
			SetToDelete();
			// METER WIN CONDITION
		}
		if (collider != nullptr) {
			collider->pendingToDelete = true;
			collider = nullptr;
		}
		break;
	default:
		break;
	}


}


void Bananacher::CheckDirection()
{
	Direction avaibleDirections[4];
	int avaibleCount = 0;
	int randDirection = 0;
	bool canContinue = false;

	int x = (colliderPosition.x - 24) / 16;
	int y = (colliderPosition.y - 32) / 16;

	if (y <= 10) {
		if (App->levelManager->grid[y + 1][x] == Module::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = DOWN;
			avaibleCount++;
		}
	}
	if (y >= 0)
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
	if (x >= 0)
	{
		if (App->levelManager->grid[y][x - 1] == Module::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = LEFT;
			avaibleCount++;
		}
	}
	if (x <= 12) {
		if (App->levelManager->grid[y][x + 1] == Module::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = RIGHT;
			avaibleCount++;
		}
	}

	//----------------------------BANANACHER MOVEMENT---------------------------
	iPoint playerPos = App->player->position;
	iPoint diff;

	diff.x = colliderPosition.x - playerPos.x;
	diff.y = colliderPosition.y - playerPos.y;
	if (diff.x < 0) diff.x *= -1;
	if (diff.y < 0) diff.y *= -1;

	if (avaibleCount >= 3) {
		if (diff.x > diff.y) {
			if (colliderPosition.y < playerPos.y) direction = DOWN;
			else direction = UP;
			if (colliderPosition.x < playerPos.x) direction = RIGHT;
			else direction = LEFT;
		}
		else
		{
			if (colliderPosition.x < playerPos.x) direction = RIGHT;
			else direction = LEFT;
			if (colliderPosition.y < playerPos.y) direction = DOWN;
			else direction = UP;
		}
	}


	switch (direction)
	{
	case Entity::UP:
		if (y <= 0) {
			if (colliderPosition.x < playerPos.x) direction = RIGHT;
			else direction = LEFT;
		}
		break;
	case Entity::DOWN:
		if (y >= 10)
		{
			if (colliderPosition.x < playerPos.x) direction = RIGHT;
			else direction = LEFT;
		}
		break;
	case Entity::RIGHT:
		if (x >= 12)
		{
			if (colliderPosition.y < playerPos.y) direction = DOWN;
			else direction = UP;
		}
		break;
	case Entity::LEFT:
		if (x <= 0) {
			if (colliderPosition.y < playerPos.y) direction = DOWN;
			else direction = UP;
		}
		break;
	case Entity::NONE:
		break;
	default:
		break;
	}

 
}

void Bananacher::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION && inmunity == false) {
		//state = DEATH;
		inmunity = true;
		count = 0;
		life--;
		//currentAnim = &deathAnim;
	}
}

void Bananacher::SetToDelete() {
	if (collider != nullptr)
	{
		collider->pendingToDelete = true;
		collider = nullptr;
	}
}