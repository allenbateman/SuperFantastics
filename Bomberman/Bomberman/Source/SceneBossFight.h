#ifndef __SCENE_BOSS_FIGHT_H__
#define __SCENE_BOSS_FIGHT_H__

#include "Module.h"
#include "Animation.h"

#define LVL_BOSS_HEIGHT 11
#define LVL_BOSS_WIDTH 13

struct SDL_Texture;

class SceneBossFight : public Module
{
private:


public:
	//Constructor
	SceneBossFight(bool startEnabled);

	//Destructor
	~SceneBossFight();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();
	GridType GetGridType(int y, int x, int yIteration = 0, int xIterantion = 0);
	GridType SetGridType(GridType type, int y, int x, int yIteration = 0, int xIterantion = 0);

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	const int gridHeight = LVL_BOSS_HEIGHT, gridWidth = LVL_BOSS_WIDTH;
	GridType grid[LVL_BOSS_HEIGHT][LVL_BOSS_WIDTH];
	bool middleStructureIsSet = false;
	int timeLevel = 240;
	SDL_Rect levelBounds = { 0,0,256,224 };
};

#endif