#include "MiddleStructure.h"

#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleLevel.h"
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
			if (App->levelManager->grid[i][j] == Module::STRUCTURE)
			{
				for (int n = 0; n < COLLIDERS; n++)
				{
					if (colliders[n] == nullptr)
					{
	
						colliders[n] = App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::STRUCTURE, (Module*)App->entities);
			
						break;
					}
				}

			}

		/*	if (App->sceneLevel1->grid[i][j] == SceneLevel1::WIN_SPOT )
			{
				for (int n = 0; n < 8; n++)
				{
					if (colliders[n] == nullptr)
					{
						colliders[n] = App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::WIN, (Module*)App->entities);
						break;
					}
				}
				//winCollider = App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::WIN, (Module*)App->entities);
				//winCollider->SetPos(24 + (j * 16), 32 + (i * 16));
				winColliderSet = true;
			}
			*/
		}
	}
}

MiddleStructure::~MiddleStructure()
{
}

void MiddleStructure::Update()
{
	currentAnim->Update();
	if (App->player->CollectedOrbs && !winColliderSet)
	{
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 13; j++) {

				if (App->levelManager->grid[i][j] == Module::WIN_SPOT && winCollider == nullptr)
				{
					winCollider = App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::WIN, (Module*)App->entities);
					winCollider->SetPos(24 + (j * 16), 32 + (i * 16));
					winColliderSet = true;
				}
			}
		}
	}
	
}
void MiddleStructure::Draw() {
	SDL_Rect rect = idleAnim.GetCurrentFrame();
	if (winColliderSet)
	{
		//draw destroyed anim

	}
	else {
		App->render->Blit(texture, 104, 64, &rect);
	}

}

void MiddleStructure::SetToDelete()
{
	if(winCollider != nullptr) winCollider->pendingToDelete = true;

	for (int i = 0; i < COLLIDERS; i++)
	{
		if (colliders[i] != nullptr)
		{
			colliders[i]->pendingToDelete = true;
		}
	}
}
