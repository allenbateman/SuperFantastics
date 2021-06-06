#ifndef __MODULE_LEVEL_H__
#define __MODULE_LEVEL_H__
#include "Module.h"


#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "SceneLevel3.1.h"
#include "SceneSelectLevel.h"
#include "sceneBossFight.h"
#include "ModuleRender.h"
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
	void PassedLevel();
	void RetunrToMainMenu();
	void RetunrToLevelSelection();
	void RestartLevel();

	enum GameState {
		NONE = 0,
		INTRO = 1,
		MAIN_MENU = 2,
		LEVEL_SELECTION = 3,
		LEVEL1 = 4,
		LEVEL2 = 5,
		LEVEL3 = 6,
		LEVEL3X1 = 7,
		BOSS = 8,
		GAMEOVER = 9
	};
	GameState gameState;
	GridType grid[MAX_SIZE][MAX_SIZE];
	int activeLevelWidth = 0;
	int orbCount = 0;
	int orbsLeft = 0;
	GridType GetGridType(int y, int x, int yIteration = 0, int xIterantion = 0);
	GridType SetGridType(GridType type, int y, int x, int yIteration = 0, int xIterantion = 0);
	int frameCounter = 0;
	int delayTime = 100;
	int levelsPassed = 0;
};
#endif // __MODULE_LEVEL_H__
