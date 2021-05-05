#ifndef __ENTITIE_H__
#define __ENTITIE_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleEntities.h"

struct SDL_Texture;
struct Collider;

class Entitie
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Entitie(int x, int y);

	// Destructor
	virtual ~Entitie();

	// Returns the Entitie's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEntities' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	//virtual void ChangeDirection();
	//virtual void CheckDirection();

public:
	// The current position in the world
	iPoint position;
	iPoint colliderPosition;

	Entitie_Type type;

	// The Entitie's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the Entitie removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	enum Direction
	{
		UP,
		DOWN,
		RIGHT,
		LEFT,
		NONE
	};
	enum State
	{
		IDLE,
		MOVE,
		ATACK,
		DEATH
	};

	State state;
	Direction direction;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The Entitie's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENTITIE_H__