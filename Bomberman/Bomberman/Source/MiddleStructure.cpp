#include "MiddleStructure.h"

#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"


MiddleStructure::MiddleStructure(int x, int y) : Entity(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 32 + (y * 16);

	//Structure Animation
	idleAnim.PushBack({ 48, 98, 48, 64 });
	idleAnim.PushBack({ 96, 98, 48, 64 });
	idleAnim.PushBack({ 144, 98, 48, 64 });
	idleAnim.loop = true;
	idleAnim.speed = 0.05f;

	currentAnim = &idleAnim;
	winColliderSet = false;

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 13; j++){
			if (App->sceneLevel_1->grid[i][j] == SceneLevel1::STRUCTURE)
			{
				for (int n = 0; n < 7; n++)
				{
					if (colliders[n] == nullptr)
					{
						colliders[n] = App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::STRUCTURE, (Module*)App->entities);
						break;
					}
				}
			}
		}
	}
}

MiddleStructure::~MiddleStructure()
{
}

void MiddleStructure::Update()
{
	currentAnim->Update();
	//change to when player has collected all orbs instead of player state
	if (App->player->currentState == ModulePlayer::PlayerState::WINING && !winColliderSet)
	{
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 13; j++) {

				if (App->sceneLevel_1->grid[i][j] == SceneLevel1::WIN_SPOT)
				{
					collider = App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::WIN, (Module*)App->entities);
					winColliderSet = true;
				}
			}
		}
	}
}
void MiddleStructure::Draw() {
	SDL_Rect rect = idleAnim.GetCurrentFrame();
	App->render->Blit(texture, 104, 64, &rect);
}

void MiddleStructure::SetToDelete()
{
	collider->pendingToDelete = true;
	for (int i = 0; i < 7; i++)
	{
		if (colliders[i] != nullptr)
		{
			colliders[i]->pendingToDelete = true;
		}
	}
}
