#include "Pokapoka.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"
#include <ctime>

Pokapoka::Pokapoka(int x, int y) : Enemy(x, y)
{
	position.x = x;
	position.y = y;

	idleAnim.PushBack({ 0,0,16,32 });
	idleAnim.loop = true;
	idleAnim.mustFlip = false;
	idleAnim.speed = 0.1f;

	// atack
	atackAnim.PushBack({ 176,0,16,32 });
	atackAnim.PushBack({ 192,0,16,32 });
	atackAnim.PushBack({ 208,0,16,32 });
	atackAnim.PushBack({ 224,0,16,32 });
	atackAnim.PushBack({ 240,0,16,32 });
	upAnim.loop = true;
	upAnim.mustFlip = false;
	upAnim.speed = 0.1f;

	// move up
	upAnim.PushBack({ 112,0,16,32 });
	upAnim.PushBack({ 128,0,16,32 });
	upAnim.PushBack({ 144,0,16,32 });
	upAnim.PushBack({ 160,0,16,32 });
	upAnim.loop = true;
	upAnim.mustFlip = false;
	upAnim.speed = 0.1f;

	// move down
	downAnim.PushBack({ 0,0,16,32 });
	downAnim.PushBack({ 16,0,16,32 });
	downAnim.PushBack({ 32,0,16,32 });
	downAnim.PushBack({ 48,0,16,32 });
	downAnim.loop = true;
	downAnim.mustFlip = false;
	downAnim.speed = 0.1f;

	// move left
	leftAnim.PushBack({ 16,0,16,32 });
	leftAnim.PushBack({ 64,0,16,32 });
	leftAnim.PushBack({ 80,0,16,32 });
	leftAnim.PushBack({ 96,0,16,32 });
	leftAnim.loop = true;
	leftAnim.mustFlip = false;
	leftAnim.speed = 0.1f;

	// move right
	rightAnim.PushBack({ 16,0,16,32 });
	rightAnim.PushBack({ 64,0,16,32 });
	rightAnim.PushBack({ 80,0,16,32 });
	rightAnim.PushBack({ 96,0,16,32 });
	rightAnim.loop = true;
	rightAnim.mustFlip = true;
	rightAnim.speed = 0.1f;

	// death
	deathAnim.PushBack({ 256,0,16,32 });
	deathAnim.PushBack({ 272,0,16,32 });
	deathAnim.PushBack({ 288,0,16,32 });
	deathAnim.PushBack({ 304,0,16,32 });
	deathAnim.PushBack({ 320,0,16,32 });
	deathAnim.PushBack({ 336,0,16,32 });
	deathAnim.PushBack({ 352,0,16,32 });
	deathAnim.PushBack({ 368,0,16,32 });
	deathAnim.loop = false;
	deathAnim.mustFlip = false;
	deathAnim.speed = 0.1f;
	
	currentAnim = &rightAnim;
	state = IDLE;
	direction = RIGHT;
	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
	colliderPosition.x = position.x;
	colliderPosition.y = position.y + 16;
	App->sceneLevel_1->grid[(colliderPosition.x - 24) / 16][(colliderPosition.y - 32) / 16] = SceneLevel1::GridType::EMPTY;
}


void Pokapoka::Update()
{
	Enemy::Update();


	switch (state)
	{
	case Enemy::IDLE:
		
		currentAnim = &idleAnim;
		CheckDirection();
		break;

	case Enemy::MOVE:
		if ((App->frameCounter % 2)) {

			if ((colliderPosition.x - 24) %16==0 && (colliderPosition.y - 32) % 16==0) CheckDirection();
			
			if (state != IDLE)
			{
				App->sceneLevel_1->grid[(colliderPosition.x - 24) / 16][(colliderPosition.y - 32) / 16] = SceneLevel1::GridType::EMPTY;
				if (direction == UP) position.y--;
				else if (direction == DOWN) position.y++;
				else if (direction == LEFT) position.x--;
				else if (direction == RIGHT) position.x++;

				colliderPosition.x = position.x;
				colliderPosition.y = position.y + 16;

				App->sceneLevel_1->grid[(colliderPosition.x - 24) / 16][(colliderPosition.y - 32) / 16] = SceneLevel1::GridType::POKAPOKA;
			}
		}
		
		break;

	case Enemy::ATACK:
		currentAnim = &atackAnim;
		if (atackAnim.HasFinished() == true) state = IDLE;
		break;
	case Enemy::DEATH:
		if (deathAnim.HasFinished()==true) SetToDelete();
		break;
	default:
		break;
	}
	

}


void Pokapoka::CheckDirection()
 {
	Direction avaibleDirections[4];
	int avaibleCount = 0;
	int randDirection = 0;
	bool canContinue = false;

	int x = (colliderPosition.x - 24) / 16;
	int y = (colliderPosition.y - 32) / 16;

	if (y != 10) {
		if (App->sceneLevel_1->grid[y + 1][x] == SceneLevel1::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = DOWN;
			avaibleCount++;
		}
	}
	if (y != 0)
	{
		if (App->sceneLevel_1->grid[y - 1][x] == SceneLevel1::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = UP;
			avaibleCount++;
		}
	}
	if (x != 0)
	{
		if (App->sceneLevel_1->grid[y][x - 1] == SceneLevel1::GridType::EMPTY)
		{
			avaibleDirections[avaibleCount] = LEFT;
			avaibleCount++;
		}
	}
	if (x != 12) {
		if (App->sceneLevel_1->grid[y][x + 1] == SceneLevel1::GridType::EMPTY)
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
		case Enemy::UP: currentAnim = &upAnim;
			break;
		case Enemy::DOWN: currentAnim = &downAnim;
			break;
		case Enemy::RIGHT: currentAnim = &rightAnim;
			break;
		case Enemy::LEFT: currentAnim = &leftAnim;
			break;
		case Enemy::NONE:
			break;
		default:
			break;
		}
		state = MOVE;
	}
	else state = IDLE;

}

void Pokapoka::OnCollision(Collider* collider)
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
