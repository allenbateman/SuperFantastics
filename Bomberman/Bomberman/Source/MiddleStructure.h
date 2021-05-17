#pragma once
#include "Entity.h"

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
	Collider* colliders[7] = {nullptr};
	

};