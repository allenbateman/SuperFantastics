#include "Pokapoka.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"

Pokapoka::Pokapoka(int x, int y) : Enemy(x, y)
{
	position.x = x;
	position.y = y;

	Animation atackAnim;



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
	
	currentAnim = &rightAnim;
	direction = RIGHT;
	collider = App->collisions->AddCollider({ 1, 1, 14, 14 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Pokapoka::Update()
{
	Enemy::Update();

	int x = (colliderPosition.x - 24) / 16;
	int y = (colliderPosition.y - 32) / 16;
	if ((App->sceneLevel_1->grid[x - 1][y - 1] == 0 || App->sceneLevel_1->grid[x - 1][y - +1]) ||
		(App->sceneLevel_1->grid[x + 1][y - 1] == 0 || App->sceneLevel_1->grid[x + 1][y - +1])) canMove = true;

	if ((App->frameCounter % 2) == 1 && canMove && atack == false) {
		if (currentAnim == &upAnim) position.x--;
		else if (currentAnim == &downAnim) position.y++;
		else if (currentAnim == &leftAnim) position.x--;
		else if (currentAnim == &rightAnim) position.x++;
	}

	colliderPosition.x = position.x+1;
	colliderPosition.y = position.y + 17;

}


void Pokapoka::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::WALL || collider->type == Collider::Type::ENEMY)
	{
		if (direction == UP) position.x++;
		else if (direction == DOWN) position.y--;
		else if (direction == LEFT) position.x++;
		else if (direction == RIGHT) position.x--;
		ChangeDirection(true);
	}
}

void Pokapoka::ChangeDirection(bool opositeDirection)
{
	if (opositeDirection == true)
	{
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
	else
	{
		switch (direction)
		{
		case UP:
			break;
		case DOWN:
			break;
		case RIGHT:
			break;
		case LEFT:
			break;
		}
	}

}