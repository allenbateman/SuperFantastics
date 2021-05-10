#pragma once
#include "Entity.h"

#define MAX_BOMB_COLLIDERS 30

class Bomb : public Entity {
public:

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Bomb(int x, int y);

	// The Entitie is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void Draw() override;
	void OnCollision(Collider* collider) override;
	void SetToDelete() override;

private:

	int upCount, downCount, leftCount, rightCount;

	int bombTimer = 300;
	int explosionTimer = 150;
	int frameExplode;

	Animation idleAnim, centerAnim, horSideAnim, leftExtrAnim, rightExtrAnim, vertSideAnim, upExtrAnim, downExtrAnim;

	enum State {
		IDLE,
		EXPLOSION
	};

	State state = IDLE;
	int frameSpawn = 0;

	Collider* colliderList[MAX_BOMB_COLLIDERS] = { nullptr };

};