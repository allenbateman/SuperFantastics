#include "Pokapoka.h"

#include "Application.h"
#include "ModuleCollisions.h"

Pokapoka::Pokapoka(int x, int y) : Enemy(x, y)
{
	position.x = x;
	position.y = y;

	//move left 
	leftAnim.PushBack({ 32, 25, 15, 22 });
	leftAnim.PushBack({ 16, 25, 16, 22 });
	leftAnim.PushBack({ 0, 25, 15, 22 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;
	//move right
	rightAnim.PushBack({ 32, 25, 15, 22 });
	rightAnim.PushBack({ 16, 25, 16, 22 });
	rightAnim.PushBack({ 0, 25, 15, 22 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;
	//move down
	downAnim.PushBack({ 1, 4, 15, 27 });
	downAnim.PushBack({ 17, 4, 15, 26 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;
	//move up
	upAnim.PushBack({ 81,4, 15, 27 });
	upAnim.PushBack({ 97, 4, 15, 26});
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Pokapoka::Update()
{

	Enemy::Update();
}