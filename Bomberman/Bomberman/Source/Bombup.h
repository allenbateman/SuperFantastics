#pragma once
#include "Entity.h"

class Bombup :  public Entity
{
public:
	Bombup(int x, int y);
	void Update() override;
	void OnCollision(Collider* collider) override;
	int timeOut;

	uint upgrade = 0;

private:
	Animation idleAnim;
};

