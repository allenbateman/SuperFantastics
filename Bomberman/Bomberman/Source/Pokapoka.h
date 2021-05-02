#pragma once
#include "Enemy.h"

class Pokapoka : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Pokapoka(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void OnCollision (Collider* collider) override;

	
	bool atack = false;

private:
	// The path that will define the position in the world


	// Enemy animations
	Animation upAnim, downAnim, leftAnim, rightAnim, atackAnim, deathAnim;
	void ChangeDirection(bool opositeDirection);
};

