#pragma once
#include "Entity.h"
#include "Powerup.h"
class Fire :
    public Powerup
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

