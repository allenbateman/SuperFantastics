#include "Bananacher.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleLevel.h"
#include "ModulePlayer.h"
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
	leftAnim.PushBack({ 512,128,48,64 });
	leftAnim.PushBack({ 560,128,48,64 });
	leftAnim.PushBack({ 608,128,48,64 });
	leftAnim.PushBack({ 656,128,48,64 });
	leftAnim.PushBack({ 704,128,48,64 });
	leftAnim.PushBack({ 752,128,48,64 });
	leftAnim.PushBack({ 808,128,48,64 });
	leftAnim.loop = true;
	leftAnim.mustFlip = false;
	leftAnim.speed = 0.1f;

	//improve death anim spritesheet pq que pereza


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



	switch (state)
	{
	case Entity::MOVE:
		//awakeCount++;
		if ((App->frameCounter % 2)) {

			if ((colliderPosition.x - 24) % 16 == 0 && (colliderPosition.y - 32) % 16 == 0) CheckDirection();
			if (upAnim.HasFinished() == true) upAnim.mustFlip = !upAnim.mustFlip;
			if (downAnim.HasFinished() == true) downAnim.mustFlip = !downAnim.mustFlip;

			//App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::EMPTY;
			if (direction == UP) position.y--;
			else if (direction == DOWN) position.y++;
			else if (direction == LEFT) position.x--;
			else if (direction == RIGHT) position.x++;

			colliderPosition.x = position.x + 16;
			colliderPosition.y = position.y + 48;

			//App->levelManager->grid[(colliderPosition.y - 32) / 16][(colliderPosition.x - 24) / 16] = Module::GridType::BANANACHER;
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

		break;
	case Entity::DEATH:
		if (deathAnim.HasFinished() == true) SetToDelete();
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

	//----------------------------BANANACHER MOVEMENT---------------------------

	iPoint playerPos = App->player->position;
	int difX = colliderPosition.x - playerPos.x;
	int difY = colliderPosition.y - playerPos.y;

	//HORIZONTAL
	if (difX > 0) {
		for (int i = 0; i < avaibleCount; i++)
			if (avaibleDirections[avaibleCount] == LEFT) direction = avaibleDirections[avaibleCount];
	}
	else {
		for (int i = 0; i < avaibleCount; i++)
			if (avaibleDirections[avaibleCount] == RIGHT) direction = avaibleDirections[avaibleCount];
	}

	//VERTICAL
	if (difY > 0) {
		for (int i = 0; i < avaibleCount; i++)
			if (avaibleDirections[avaibleCount] == UP) direction = avaibleDirections[avaibleCount];
	}
	else {
		for (int i = 0; i < avaibleCount; i++)
			if (avaibleDirections[avaibleCount] == DOWN) direction = avaibleDirections[avaibleCount];
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


}

void Bananacher::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION) {
		//state = DEATH;
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