#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"

#define LVL_ONE_HEIGHT 11
#define LVL_ONE_WIDTH 13
struct SDL_Texture;

class SceneLevel1 : public Module
{
private:
	

public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

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

	void OnDisable();

	GridType GetGridType(int y, int x, int yIteration = 0, int xIterantion = 0);
	GridType SetGridType(GridType type, int y, int x, int yIteration = 0, int xIterantion = 0);
	GridType Scene();

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	const int gridHeight= LVL_ONE_HEIGHT, gridWidth = LVL_ONE_WIDTH;
	GridType grid[LVL_ONE_HEIGHT][LVL_ONE_WIDTH];
	bool middleStructureIsSet = false;
	int timeLevel = 240;

	SDL_Rect levelBounds = { 0,0,256,224 };
};

#endif