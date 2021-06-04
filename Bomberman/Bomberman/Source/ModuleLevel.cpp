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
	// Get gamepad info
	GamePad& pad = App->input->pads[0];

	switch (gameState)
	{
	case INTRO:
		if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN || pad.a==true)
		{
			gameState = MAIN_MENU;
		}
		break;
	case MAIN_MENU:
		if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN || pad.a == true)
		{
			gameState = LEVEL1;
		}
		break;
	case LEVEL1:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN )
		{
			gameState = LEVEL2;
		}
		break;
	case LEVEL2:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
		{
			gameState = LEVEL3;
		}
		break;
	case LEVEL3:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
		{
			gameState = LEVEL3X1;
		}
		break;
	case LEVEL3X1:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
		{
			gameState = BOSS;
		}
		break;
	case BOSS:
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

Update_Status ModuleLevel::Update()
{

	switch (gameState)
	{
	case INTRO:
		if (currentScene == nullptr ) {
			currentScene = (Module*)App->sceneInit;
		}
		break;
	case MAIN_MENU:
		if (currentScene != (Module*)App->sceneIntro ) {

			LOG("Loading MainMenu");
			for (int y = 0; y < MAX_SIZE; y++)
			{
				for (int x = 0; x < MAX_SIZE; x++)
				{
					grid[y][x] = GridType::EMPTY;
				}
			}
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneIntro, 60);
			currentScene = (Module*)App->sceneIntro;
		}
		break;
	case LEVEL1:

		if (currentScene != (Module*)App->sceneLevel1  )
		{
			//Load level
			LOG("Loading Level 1");
			for (int y = 0; y < MAX_SIZE; y++)
			{
				for (int x = 0; x < MAX_SIZE; x++)
				{
					grid[y][x] = GridType::EMPTY;
				}
			}
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel1, 60);
			currentScene = (Module*)App->sceneLevel1;
		}
		break;
	case LEVEL2:

		if (currentScene != (Module*)App->sceneLevel2 ) {
			//Load level
			LOG("Loading Level 2");
			for (int y = 0; y < MAX_SIZE; y++)
			{
				for (int x = 0; x < MAX_SIZE; x++)
				{
					grid[y][x] = GridType::EMPTY;
				}
			}
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel2, 60);
			currentScene = (Module*)App->sceneLevel2;
		}
		break;
	case LEVEL3:
		if (currentScene != (Module*)App->sceneLevel3 ) {
			//Load level
			LOG("Loading Level 3");
			for (int y = 0; y < MAX_SIZE; y++)
			{
				for (int x = 0; x < MAX_SIZE; x++)
				{
					grid[y][x] = GridType::EMPTY;
				}
			}
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel3, 60);
			currentScene = (Module*)App->sceneLevel3;
		}
		break;
	case LEVEL3X1:
		if (currentScene != (Module*)App->sceneLevel3x1) {
			//Load level
			LOG("Loading Level 3.1");
			for (int y = 0; y < MAX_SIZE; y++)
			{
				for (int x = 0; x < MAX_SIZE; x++)
				{
					grid[y][x] = GridType::EMPTY;
				}
			}
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel3x1, 60);
			currentScene = (Module*)App->sceneLevel3x1;
		}
		break;
	case BOSS:
		if (currentScene != (Module*)App->sceneBossFight) {
			//Load level
			LOG("Loading Level Boss");
			for (int y = 0; y < MAX_SIZE; y++)
			{
				for (int x = 0; x < MAX_SIZE; x++)
				{
					grid[y][x] = GridType::EMPTY;
				}
			}
			App->fade->FadeToBlack(currentScene, (Module*)App->sceneBossFight, 60);
			currentScene = (Module*)App->sceneBossFight;
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

ModuleLevel::GridType ModuleLevel::GetGridType(int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration];
}

ModuleLevel::GridType ModuleLevel::SetGridType(GridType type, int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration] = type;
}
