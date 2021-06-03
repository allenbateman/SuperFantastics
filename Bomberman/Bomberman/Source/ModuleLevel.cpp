#include "ModuleLevel.h"
#include <string>
#include <iostream>

ModuleLevel::ModuleLevel(bool StartEnabled) : Module(StartEnabled)
{

}

ModuleLevel::~ModuleLevel()
{
}

bool ModuleLevel::Start()
{
	transitionFinish = true;
	gameState = INTRO;
	currentScene = (Module*)App->sceneInit;
	return true;
}

Update_Status ModuleLevel::PreUpdate()
{

	switch (gameState)
	{
	case INTRO:
		if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN && transitionFinish)
		{
			gameState = MAIN_MENU;
			transitionFinish = false;
		}
		break;
	case MAIN_MENU:
		if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN && transitionFinish)
		{
			gameState = LEVEL1;
			transitionFinish = false;
		}
		break;
	case LEVEL1:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && transitionFinish)
		{
			gameState = LEVEL2;
			transitionFinish = false;
		}
		break;
	case LEVEL2:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && transitionFinish)
		{
			gameState = LEVEL3;
			transitionFinish = false;
		}
		break;
	case LEVEL3:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && transitionFinish)
		{
			gameState = BOSS;
			transitionFinish = false;
		}
		break;
	case BOSS:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && transitionFinish)
		{
			gameState = MAIN_MENU;
			transitionFinish = false;
		}
		break;
	default:
		break;
	}


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleLevel::Update()
{

	switch (gameState)
	{
	case INTRO:
		if (currentScene == nullptr && !transitionFinish) {
			currentScene = (Module*)App->sceneInit;
			transitionFinish = true;
		}
		break;
	case MAIN_MENU:
		if (currentScene != (Module*)App->sceneIntro && !transitionFinish) {

			LOG("Loading MainMenu");
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneIntro, 60);
			currentScene = (Module*)App->sceneIntro;
			transitionFinish = true;
		}
		break;
	case LEVEL1:

		if (currentScene != (Module*)App->sceneLevel1 && !transitionFinish )
		{
			//Load level
			LOG("Loading Level 1");
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel1, 60);
			currentScene = (Module*)App->sceneLevel1;
			transitionFinish = true;
		}
		break;
	case LEVEL2:

		if (currentScene != (Module*)App->sceneLevel2 && !transitionFinish) {
			//Load level
			LOG("Loading Level 2");
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel2, 60);
			currentScene = (Module*)App->sceneLevel2;
			transitionFinish = true;
		}
		break;
	case LEVEL3:
		if (currentScene != (Module*)App->sceneLevel3 && !transitionFinish) {
			//Load level
			LOG("Loading Level 3");
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel3, 60);
			currentScene = (Module*)App->sceneLevel3;
			transitionFinish = true;
		}
		break;
	case BOSS:
		if (currentScene != (Module*)App->sceneBossFight && !transitionFinish) {
			//Load level
			LOG("Loading Level Boss");
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneBossFight, 60);
			currentScene = (Module*)App->sceneBossFight;
			transitionFinish = true;
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

ModuleLevel::GridType ModuleLevel::GetGridType(int y, int x, int yIteration, int xIterantion)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIterantion];
}

ModuleLevel::GridType ModuleLevel::SetGridType(GridType type, int y, int x, int yIteration, int xIterantion)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIterantion] = type;
}
