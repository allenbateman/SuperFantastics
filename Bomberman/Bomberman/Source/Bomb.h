#pragma once
#include "Entity.h"
#include "p2Point.h"

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
	int ChooseArrayIndex();
private:

	int upCount, downCount, leftCount, rightCount;

	int frameCounter = 0;

	Animation idleAnim, centerAnim, horSideAnim, leftExtrAnim, rightExtrAnim, vertSideAnim, upExtrAnim, downExtrAnim;

	enum State {
		IDLE,
		PLACING_COLLIDERS,
		EXPLOSION
	};
	enum ExplosionType {
		CENTER,
		VERTICAL,
		HORIZONTAL,
		END_UP,
		END_DOWN,
		END_LEFT,
		END_RIGHT,
		NONE
	};
	struct Particle {
		ExplosionType type = NONE;
		int x;
		int y;
	};

	State state = IDLE;
	int frameSpawn = 0;
	bool withColliders = false;
	int collidingCounter = 0;
	int lastVal;

	Collider* colliderList[MAX_BOMB_COLLIDERS] = { nullptr };
	Particle particle[MAX_BOMB_COLLIDERS];
};