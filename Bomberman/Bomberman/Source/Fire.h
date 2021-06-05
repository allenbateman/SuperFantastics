#pragma once
#include "Entity.h"
class Fire : public Entity
{
public:
	Fire(int x, int y);
	void Update() override;
	void OnCollision(Collider* collider) override;
	int timeOut;
	int range = 1;

	uint upgrade = 0;

private:
	Animation idleAnim;
};

