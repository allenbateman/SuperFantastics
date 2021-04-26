#include "Pokapoka.h"

#include "Application.h"
#include "ModuleCollisions.h"

Pokapoka::Pokapoka(int x, int y) : Enemy(x, y)
{
	
	
	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Pokapoka::Update()
{

	Enemy::Update();
}