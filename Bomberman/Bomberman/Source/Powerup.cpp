#include "Powerup.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Powerup::Powerup(int x, int y)
{
	spawnPos = position;
}

Powerup::~Powerup()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

void Powerup::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(colliderPosition.x, colliderPosition.y);
}

void Powerup::Draw()
{
	if (currentAnim != nullptr) {
		if (currentAnim->mustFlip == false) App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		else App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()), 1.0f, true, Horizontal);
	}
}

void Powerup::OnCollision(Collider* collider)
{
	if (collider->PLAYER)
	{
		//Add stats
		SetToDelete();
	}
}

const Collider* Powerup::GetCollider() const
{
	return collider;
}

void Powerup::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}
