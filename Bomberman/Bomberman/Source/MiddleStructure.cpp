#include "MiddleStructure.h"

#include "Application.h"
#include "ModuleCollisions.h"
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
}

MiddleStructure::~MiddleStructure()
{
}

void MiddleStructure::Update()
{
	currentAnim->Update();
}
void MiddleStructure::Draw() {
	SDL_Rect rect = idleAnim.GetCurrentFrame();
	App->render->Blit(texture, 104, 64, &rect);
}