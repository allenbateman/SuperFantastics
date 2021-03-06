#include "ModuleLevel.h"
#include "ModulePlayer.h"
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
	LOG("Loading LevelManager....");
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
		if ((App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN || pad.a==true) && currentScene->IsEnabled())
		{
			
			gameState = MAIN_MENU;
		}
		break;
	case MAIN_MENU:
		if ((App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN || pad.a == true) && currentScene->IsEnabled())
		{
			gameState = LEVEL_SELECTION;
		}
		break;
	case LEVEL_SELECTION:

		break;
	case LEVEL1:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && currentScene->IsEnabled())
		{
			gameState = LEVEL2;
		}
		break;
	case LEVEL2:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && currentScene->IsEnabled())
		{
			gameState = LEVEL3;
		}
		break;
	case LEVEL3:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && currentScene->IsEnabled())
		{
			gameState = LEVEL3X1;
		}
		break;
	case LEVEL3X1:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && currentScene->IsEnabled())
		{
			gameState = BOSS;
		}
		break;
	case BOSS:
		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && currentScene->IsEnabled())
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

			LOG("Loading Scene Intro");
			currentScene = (Module*)App->sceneInit;
		}
		break;
	case MAIN_MENU:
		if (currentScene != (Module*)App->sceneIntro ) {

		

			if (App->fade->FadeToBlack(currentScene, (Module*)App->sceneIntro, 45))
			{
				LOG("Loading MainMenu");
				for (int y = 0; y < MAX_SIZE; y++)
				{
					for (int x = 0; x < MAX_SIZE; x++)
					{
						grid[y][x] = GridType::EMPTY;
					}
				}
				currentScene = (Module*)App->sceneIntro;
			}
		}
		break;
	case LEVEL_SELECTION:
		if (currentScene != (Module*)App->sceneSelectLevel) {
			
			if (App->fade->FadeToBlack(currentScene, (Module*)App->sceneSelectLevel, 45))
			{
				LOG("Loading Level Selection");
				currentScene = (Module*)App->sceneSelectLevel;
			}
		}
		break;
	case LEVEL1:

		if (currentScene != (Module*)App->sceneLevel1  )
		{
			//Load level

			if (App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel1, 45))
			{
				LOG("Loading Level 1");
				for (int y = 0; y < MAX_SIZE; y++)
				{
					for (int x = 0; x < MAX_SIZE; x++)
					{
						grid[y][x] = GridType::EMPTY;
					}
				}
				App->render->ResetScrollBoxPositions();
				currentScene = (Module*)App->sceneLevel1;
			}
		}
		break;
	case LEVEL2:

		if (currentScene != (Module*)App->sceneLevel2 ) {
			//Load level


			if (App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel2, 45))
			{
				LOG("Loading Level 2");
				for (int y = 0; y < MAX_SIZE; y++)
				{
					for (int x = 0; x < MAX_SIZE; x++)
					{
						grid[y][x] = GridType::EMPTY;
					}
				}
				App->render->ResetScrollBoxPositions();
				currentScene = (Module*)App->sceneLevel2;
			}
		}
		break;
	case LEVEL3:
		if (currentScene != (Module*)App->sceneLevel3 ) {
			//Load level
			if (App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel3, 45))
			{
				LOG("Loading Level 3");
				for (int y = 0; y < MAX_SIZE; y++)
				{
					for (int x = 0; x < MAX_SIZE; x++)
					{
						grid[y][x] = GridType::EMPTY;
					}
				}
				App->render->ResetScrollBoxPositions();
				currentScene = (Module*)App->sceneLevel3;
			}
		}
		break;
	case LEVEL3X1:
		if (currentScene != (Module*)App->sceneLevel3x1) {
			//Load level


			if (App->fade->FadeToBlack(currentScene, (Module*)App->sceneLevel3x1, 45))
			{
				LOG("Loading Level 3.1");
				for (int y = 0; y < MAX_SIZE; y++)
				{
					for (int x = 0; x < MAX_SIZE; x++)
					{
						grid[y][x] = GridType::EMPTY;
					}
				}
				App->render->ResetScrollBoxPositions();
				currentScene = (Module*)App->sceneLevel3x1;
			}
		}
		break;
	case BOSS:
		if (currentScene != (Module*)App->sceneBossFight) {
			//Load level


			if (App->fade->FadeToBlack(currentScene, (Module*)App->sceneBossFight, 45))
			{
				LOG("Loading Level Boss");
				for (int y = 0; y < MAX_SIZE; y++)
				{
					for (int x = 0; x < MAX_SIZE; x++)
					{
						grid[y][x] = GridType::EMPTY;
					}
				}
				App->render->ResetScrollBoxPositions();
				currentScene = (Module*)App->sceneBossFight;
			}
		}
		break;
	default:
		break;
	}
	frameCounter++;
	return Update_Status::UPDATE_CONTINUE;
}


void ModuleLevel::PassedLevel()
{
	switch (gameState) {
		case GameState::LEVEL1:
			if (levelsPassed < 1) {
				levelsPassed++;
			}
			RetunrToLevelSelection();
			break;
		case GameState::LEVEL2:
			if (levelsPassed < 2) {
				levelsPassed++;
			}	
			RetunrToLevelSelection();
			break;
		case GameState::LEVEL3:
			gameState = GameState::LEVEL3X1;
			break;
		case GameState::LEVEL3X1:
			if (levelsPassed < 3) {
				levelsPassed++;	
			}
			gameState = GameState::BOSS;
		case GameState::BOSS:
			gameState = GameState::MAIN_MENU;
			break;
			break;
	}

	App->sceneSelectLevel->selectedStage = levelsPassed;
}

void ModuleLevel::RetunrToMainMenu()
{
	LOG("RETURN TO MAIN MENU")
	if(gameState != MAIN_MENU)
		gameState = MAIN_MENU;
}

void ModuleLevel::RetunrToLevelSelection()
{
	LOG("RETURN TO LEVEL SELECTION")
	if (gameState != LEVEL_SELECTION)
		gameState = LEVEL_SELECTION;

}

void ModuleLevel::RestartLevel()
{
	if (App->player->lifes < 0)
	{
		gameState = GAMEOVER;

		App->fade->FadeToBlack(currentScene, (Module*)App->sceneGameOver, 60.0f);
	}
	else {
		App->fade->FadeToBlack(currentScene, currentScene, 60.0f);
	}
}

ModuleLevel::GridType ModuleLevel::GetGridType(int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration];
}

ModuleLevel::GridType ModuleLevel::SetGridType(GridType type, int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration] = type;
}


bool ModuleLevel::CleanUp()
{
	if (currentScene != nullptr)
	{
		currentScene = nullptr;
	}
	return true;
}
