#pragma once
#include "Entitie.h"
class Bombup :  public Entitie
{
public:
	Bombup(int x, int y);
	void Update() override;
	void OnCollision(Collider* collider) override;
	bool pickedUp;
	int timeOut;
private:
	Animation idleAnim;
};

