#include "ModuleLevel.h"



ModuleLevel::ModuleLevel(bool StartEnabled) : Module(StartEnabled)
{

}

ModuleLevel::~ModuleLevel()
{
}

bool ModuleLevel::Start()
{
	gameState = INTRO;
	currentScene = (Module*)App->sceneInit;
	return true;
}

Update_Status ModuleLevel::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleLevel::Update()
{

	switch (gameState)
	{
	case INTRO:
		if (currentScene == nullptr) {
			currentScene = (Module*)App->sceneInit;
		}
		//change level
		if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN)
		{
			gameState = MAIN_MENU;
		}
		break;
	case MAIN_MENU:
		if (currentScene != (Module*)App->sceneIntro) {
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneIntro, 60);
			currentScene = (Module*)App->sceneIntro;
		}		
		//change level
		if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN)
		{
			gameState = LEVEL1;
		}
		break;
	case LEVEL1:

		if (currentScene != (Module*)App->sceneLevel1)
		{
			//Copy level grid to general grid
			for (int y = 0; y < App->sceneLevel1->gridHeight; y++)
			{
				for (int x = 0; x < App->sceneLevel1->gridWidth; x++)
				{
					grid[y][x] = App->sceneLevel1->grid[y][x];
				}
			}
			//Load level
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel1, 60);
			currentScene = (Module*)App->sceneLevel1;
		}
		//change level
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
		{
			gameState = LEVEL2;
		}
		break;
	case LEVEL2:

		if (currentScene != (Module*)App->sceneLevel2) {
			//Copy level grid to general grid
			for (int y = 0; y < App->sceneLevel2->gridHeight; y++)
			{
				for (int x = 0; x < App->sceneLevel2->gridWidth; x++)
				{
					grid[y][x] = App->sceneLevel2->grid[y][x];
				}
			}
			//Load level
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel2, 60);
			currentScene = (Module*)App->sceneLevel2;
		}
		//change level
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
		{
			gameState = LEVEL3;
		}
		break;
	case LEVEL3:
		if (currentScene != (Module*)App->sceneLevel3) {
			//Copy level grid to general grid
			for (int y = 0; y < App->sceneLevel3->gridHeight; y++)
			{
				for (int x = 0; x < App->sceneLevel3->gridWidth; x++)
				{
					grid[y][x] = App->sceneLevel3->grid[y][x];
				}
			}
			//Load level
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel3, 60);
			currentScene = (Module*)App->sceneLevel3;
		}
		//change level
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
		{
			gameState = BOSS;
		}
		break;
	case BOSS:
		if (currentScene != (Module*)App->sceneBossFight) {
			for (int y = 0; y < App->sceneBossFight->gridHeight; y++)
			{
				for (int x = 0; x < App->sceneBossFight->gridWidth; x++)
				{
					grid[y][x] = App->sceneBossFight->grid[y][x];
				}
			}
			//Load level
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneBossFight, 60);
			currentScene = (Module*)App->sceneBossFight;
		}
		//change level
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
		{
			gameState = MAIN_MENU;
		}
		break;
	default:
		break;
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleLevel::CleanUp()
{
	if (currentScene != nullptr)
	{
		currentScene = nullptr;
	}
	return true;
}
