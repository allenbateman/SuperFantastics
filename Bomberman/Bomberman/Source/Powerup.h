#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleEnemies.h"

struct SDL_Texture;
struct Collider;


class Powerup
{
public:
	Powerup(int x, int y);
	virtual ~Powerup();

	virtual void Update();
	virtual void Draw();
	virtual void OnCollision(Collider* collider);
	const Collider* GetCollider() const;
	virtual void SetToDelete();

public:

	iPoint position;
	iPoint colliderPosition;
	SDL_Texture* texture = nullptr;
	bool pendingToDelete = false;
	Enemy_Type type;
	int destroyedFx = 0;

	enum State {
		ENABLED,
		DISABLED,
	};

	State state;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;

};

#endif // __POWERUP_H__