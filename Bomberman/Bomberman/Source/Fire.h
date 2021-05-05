#pragma once
#include "Enemy.h"
class Fire :
    public Enemy
{
public:
	Fire(int x, int y);
	void Update() override;
	void OnCollision(Collider* collider) override;
	bool pickedUp;
	int timeOut;
	int range = 2;
private:
	Animation idleAnim;
};

