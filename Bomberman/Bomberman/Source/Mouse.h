#pragma once
#include "Entity.h"

class Mouse : public Entity
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Mouse(int x, int y);

	// The Entitie is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void OnCollision(Collider* collider) override;
	void CheckDirection();

	bool atack = false;

private:
	// The path that will define the position in the world


	// Entitie animations
	Animation moveAnim, deathAnim;
};
