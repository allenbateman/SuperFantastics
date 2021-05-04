#pragma once
#include "Enemy.h"

class Bomb : public Enemy {
public:

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Bomb(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void OnCollision(Collider* collider) override;


private:
	Animation idleAnim, leftAnim, rightAnim, upAnim, downAnim, centerAnim;

	enum State {
		IDLE,
		EXPLOSION
	};

	State state = IDLE;

};