#include "YellowFlower.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"

YellowFlower::YellowFlower(int x, int y) : Entity(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 32 + (y * 16);

	collider = App->collisions->AddCollider({ 24 + (x * 16),32 + (y * 16),16,16 }, Collider::Type::YELLOW_FLOWER, (Module*)App->entities);

	collider->SetPos(position.x,position.y);

	idleAnim.PushBack({ 400, 0, 16, 16 });
	currentAnim = &idleAnim;
}

void YellowFlower::Update()
{

}

void YellowFlower::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION) {
		App->sceneLevel1->SetGridType(SceneLevel1::GridType::EMPTY, position.y, position.x, 0, 0);
		SetToDelete();
	}
}

