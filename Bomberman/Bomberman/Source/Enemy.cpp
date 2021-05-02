#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(colliderPosition.x, colliderPosition.y);
}

void Enemy::Draw()
{
	if (currentAnim != nullptr) {
		if (currentAnim->mustFlip==false) App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		else App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()), 1.0f, true, Horizontal);
	}
}

void Enemy::OnCollision(Collider* collider)
{
	//if(collider->type==BOMB){
	//	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	//	App->audio->PlayFx(destroyedFx);
	//}

	//if(collider->type==WALL) pues q cambie de direccion

	SetToDelete();
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}
