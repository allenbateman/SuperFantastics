#pragma once
#include "Entity.h"

#define COLLIDERS 8

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

};