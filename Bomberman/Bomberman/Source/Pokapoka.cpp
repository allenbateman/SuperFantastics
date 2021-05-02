#include "Pokapoka.h"

#include "Application.h"
#include "ModuleCollisions.h"

Pokapoka::Pokapoka(int x, int y) : Enemy(x, y)
{
	position.x = x;
	position.y = y;

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
	collider = App->collisions->AddCollider({ 0, 16, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Pokapoka::Update()
{

	Enemy::Update();
}