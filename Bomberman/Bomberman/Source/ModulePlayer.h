#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

#define MAX_BOMBS 5
#define MAX_RANGE_EXPLOSION 9

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;
	void Draw();
	// Info on the scoreboard
	void DrawScoreboard();

public:
	int lastKeyPressed = 0;
	bool isStuck=false;
	// Position of the player in the map
	iPoint position;
	iPoint lastPos;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation upAnim, downAnim, leftAnim, rightAnim;
	Animation upIdleAnim, downIdleAnim, leftIdleAnim, rightIdleAnim, currentIdleAnim;
	Animation deathAnim, winAnim;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint bombIsPlaced = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };
	int lifes = 3;
	bool death = false;

	enum class PlayerState {
		ALIVE,
		DEAD,
		WINING
	};
	PlayerState currentState;
	// Player powers
	int currentBombs = 1;
	int rangeExplosion = 2;

	bool bombPlaced = false;
};

#endif //!__MODULE_PLAYER_H__