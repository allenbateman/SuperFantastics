#include "Entity.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

Entity::Entity(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Entity::~Entity()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Entity::GetCollider() const
{
	return collider;
}

void Entity::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(colliderPosition.x, colliderPosition.y);
}

void Entity::Draw()
{
	if (currentAnim != nullptr) {
		if (currentAnim->mustFlip==false) App->render->Blit(texture, position.x + drawOffset.x, position.y + drawOffset.y, &(currentAnim->GetCurrentFrame()));
		else App->render->Blit(texture, position.x + drawOffset.x, position.y + drawOffset.y, &(currentAnim->GetCurrentFrame()), 1.0f, true, Horizontal);
	}
}

void Entity::OnCollision(Collider* collider)
{
	SetToDelete();
}

void Entity::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
	App->player->score += scorePoints;
}
