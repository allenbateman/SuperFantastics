#pragma once
#include "Entity.h"
class Saru :
	public Entity
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Saru(int x, int y);

	// The Entitie is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void OnCollision(Collider* collider) override;
	void CheckDirection();

	bool PlayerNear();

private:
	// The path that will define the position in the world
	int life = 4;
	bool canStop = true;

	enum Priority
	{
		VERTICAL,
		HORIZONTAL,
		NONE
	};

	Priority priority = NONE;

	// Entitie animations
	Animation idleAnim, upAnim, downAnim, leftAnim, rightAnim, deathAnim;
};