#pragma once
#include "Enemy.h"
class Bombup :  public Enemy
{
public:
	Bombup(int x, int y);
	void Update() override;
	void OnCollision(Collider* collider) override;
	bool pickedUp;
private:
	Animation idleAnim;
};

