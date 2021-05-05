#include "MiddleStructure.h"

#include "Application.h"
#include "ModuleCollisions.h"

MiddleStructure::MiddleStructure(int x, int y) : Entity(x, y)
{
	position.x = 24 + (x * 16);
	position.y = 32 + (y * 16);

	idleAnim.PushBack({ 49, 98, 48, 64 });
	idleAnim.PushBack({ 97, 98, 48, 64 });
	idleAnim.PushBack({ 145, 98, 48, 64 });

	currentAnim = &idleAnim;
}

void MiddleStructure::Update()
{
}