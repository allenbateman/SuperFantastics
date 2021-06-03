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

			LOG("Loading MainMenu");
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
			//Load level
			LOG("Loading Level 1");
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
			//Load level
			LOG("Loading Level 2");
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
			//Load level
			LOG("Loading Level 3");
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
			//Load level
			LOG("Loading Level Boss");
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

ModuleLevel::GridType ModuleLevel::GetGridType(int y, int x, int yIteration, int xIterantion)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIterantion];
}

ModuleLevel::GridType ModuleLevel::SetGridType(GridType type, int y, int x, int yIteration, int xIterantion)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIterantion] = type;
}
