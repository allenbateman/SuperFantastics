#ifndef __SCENE_SELECT_H__
#define __SCENE_SELECT_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

#define MAX_STAGES 3

class SceneSelectLevel : public Module
{
public:
	//Constructor
	SceneSelectLevel(bool startEnabled);

	//Destructor
	~SceneSelectLevel();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* sheetTexture = nullptr;
	SDL_Rect backgroundRect = {0,0,256,232};
	SDL_Rect selectLevelRect = {0,224,112,80};
	SDL_Rect selectedLevelRect = {112,224,32,24};

	iPoint selectedLevelPoints[3];

	SDL_Rect stageRect = {0,304,72,64};
	SDL_Rect stageExitRect = { 0,368,80,16 };
	SDL_Rect stageTitleRect = { 0,384,80,16 };
	SDL_Rect stageNumberRect = {0,400,16,16};

	Animation partAnimation;

	int selectedStage = 0;
	int maxStage = 1;
	bool exit = false;

	bool showSelectedLevel = true;
};

#endif