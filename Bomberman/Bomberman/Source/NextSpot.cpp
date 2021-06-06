#include "NextSpot.h"

#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleLevel.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"


NextSpot::NextSpot(int x, int y) : Entity(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 32 + (y * 16);
}

NextSpot::~NextSpot()
{

}

void NextSpot::Update()
{
	if (collider == nullptr&& App->levelManager->orbsLeft == 0)
	{
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < App->levelManager->activeLevelWidth; j++) {
				if (App->levelManager->grid[i][j] == Module::NEXT_SPOT)
				{
					collider = App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::NEXT, (Module*)App->entities);
					collider->SetPos(24 + (j * 16), 32 + (i * 16));
				}
			}
		}
	}
}

void NextSpot::SetToDelete()
{
	if (collider != nullptr) collider->pendingToDelete = true;
}