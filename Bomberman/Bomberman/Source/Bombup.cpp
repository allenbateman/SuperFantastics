#include "Bombup.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleLevel.h"

Bombup::Bombup(int x, int y) : Entity(x, y)
{
	position.x = x;
	position.y = y;

	idleAnim.PushBack({ 64, 288, 16, 16 });	
	currentAnim = &idleAnim;

	collider = App->collisions->AddCollider({ position.x,position.y,16,16 },Collider::Type::POWER_UP,(Module*)App->entities);
}

void Bombup::Update()
{

}

void Bombup::OnCollision(Collider* collider)
{	
	if (collider->type == Collider::Type::PLAYER)
	{
		if (MAX_BOMBS > App->player->currentBombs)
		{
			App->player->currentBombs++;

			upgrade = App->audio->LoadFx("Assets/Fx/21UpgradeAcquired.wav");
			App->audio->PlayFx(upgrade, 0);
		}
		App->levelManager->SetGridType(Module::GridType::EMPTY, position.y, position.x, 0, 0);
		SetToDelete();
	}
}
