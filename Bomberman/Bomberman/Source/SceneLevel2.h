#ifndef __SCENE_LEVEL2_H__
#define __SCENE_LEVEL2_H__

#include "Module.h"
#include "Animation.h"

#define LVL_TWO_HEIGHT 11
#define LVL_TWO_WIDTH 29

struct SDL_Texture;

class SceneLevel2 : public Module
{
private:


public:
	//Constructor
	SceneLevel2(bool startEnabled);

	//Destructor
	~SceneLevel2();

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
	const int gridHeight = LVL_TWO_HEIGHT, gridWidth = LVL_TWO_WIDTH;
	GridType grid[LVL_TWO_HEIGHT][LVL_TWO_WIDTH];
	bool middleStructureIsSet = false;
	int timeLevel = 240;
	SDL_Rect levelBounds = { 0,0,1024,224 };
	int numScene = 2;
	int orbs = 2;
};
#endif