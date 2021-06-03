#ifndef __MODULE_LEVEL_H__
#define __MODULE_LEVEL_H__
#include "Module.h"


#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "sceneBossFight.h"
#include "SceneIntro.h"
#include "ModuleInput.h"

#define MAX_SIZE 28
class ModuleLevel : public Module
{
public:
	ModuleLevel(bool StartEnabled);
	~ModuleLevel();
	bool Start() override;
	Update_Status PreUpdate() override;
	Update_Status Update() override;
	bool CleanUp() override;
	Module* currentScene = nullptr;

	enum GameState {
		NONE = 0,
		INTRO = 1,
		MAIN_MENU = 2,
		LEVEL1 = 3,
		LEVEL2 = 4,
		LEVEL3 = 5,
		BOSS = 6	
	};
	GameState gameState;


	GridType grid[MAX_SIZE][MAX_SIZE];
	GridType GetGridType(int y, int x, int yIteration = 0, int xIterantion = 0);
	GridType SetGridType(GridType type, int y, int x, int yIteration = 0, int xIterantion = 0);

};
#endif // __MODULE_LEVEL_H__
