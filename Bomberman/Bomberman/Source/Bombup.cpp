#include "Bombup.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Bombup::Bombup(int x, int y) : Entity(x, y)
{
	position.x = x;
	position.y = y;

	idleAnim.PushBack({ 64, 288, 16, 16 });	
	currentAnim = &idleAnim;
}

void Bombup::Update()
{

}

void Bombup::OnCollision(Collider* collider)
{	
	if(MAX_BOMBS > App->player->currentBombs)
	App->player->currentBombs++;

	SetToDelete();
}
