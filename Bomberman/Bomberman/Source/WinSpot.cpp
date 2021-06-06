#include "WinSpot.h"

#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleLevel.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"


WinSpot::WinSpot(int x, int y) : Entity(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 32 + (y * 16);
}

WinSpot::~WinSpot()
{

}

void WinSpot::Update()
{
	if (winCollider == nullptr)
	{
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < App->levelManager->activeLevelWidth; j++) {
				if (App->levelManager->grid[i][j] == Module::WIN_SPOT)
				{
					winCollider = App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::WIN, (Module*)App->entities);
					winCollider->SetPos(24 + (j * 16), 32 + (i * 16));
				}
			}
		}
	}
}

void WinSpot::SetToDelete()
{
	if (winCollider != nullptr) winCollider->pendingToDelete = true;
}
