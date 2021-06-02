#pragma once
#include "Entity.h"
#include "SceneLevel1.h"

#define COLLIDERS 7

class MiddleStructure : public Entity
{
public:
	MiddleStructure(int x, int y);
	~MiddleStructure();
	void Update() override;
	void Draw() override;
	void SetToDelete() override;

private:

	Animation idleAnim, winAnim;

	Collider* colliders[COLLIDERS] = {nullptr};
	Collider* winCollider = nullptr;
	bool winColliderSet = false;

};