#include "SceneBossFight.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleUI.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleEntities.h"
#include "ModulePlayer.h"
#include "MiddleStructure.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel.h"

#include <ctime>

SceneBossFight::SceneBossFight(bool startEnabled) : Module(startEnabled)
{

}

SceneBossFight::~SceneBossFight()
{

}

// Load assets
bool SceneBossFight::Start()
{
	App->player->Enable();
	App->entities->Enable();
	App->collisions->Enable();
	App->UI->Enable();

	App->UI->timeLeft = timeLevel;
	App->UI->timeLevel = timeLevel;

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/FinalBossMap.png");
	App->audio->PlayMusic("Assets/Music/SceneBossFight.ogg", 1.0f);

	//add bounding colliders
	//Left collider
	App->collisions->AddCollider({ 0,23,24,223 }, Collider::Type::BOUNDS);
	//Right Collider
	App->collisions->AddCollider({ 232,23,24,223 }, Collider::Type::BOUNDS);
	//Top Collider
	App->collisions->AddCollider({ 24,23,208,8 }, Collider::Type::BOUNDS);
	//Bot collider 
	App->collisions->AddCollider({ 24,208,208,8 }, Collider::Type::BOUNDS);

	// Fixed positions

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			grid[i][j] = EMPTY;
		}
	}

	for (int i = 1; i < 11; i += 2)
	{
		for (int j = 1; j < 13; j += 2)
		{
			grid[i][j] = ROCK;
		}
	}

	grid[7][6] = PLAYER;
	grid[2][8] = SARU;
	grid[2][6] = BANANACHER;

	middleStructureIsSet = false;

	// generate scene elements or rock collisions
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 13; j++)
		{
			if (grid[i][j] == PLAYER)
			{
				iPoint pos;
				pos.x = 24 + j * 16;
				pos.y = 32 + i * 16;
				App->player->position = pos;
			}
			else if (grid[i][j] == ROCK)
			{
				App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::WALL);
			}
			else if (grid[i][j] == SARU)
			{
				App->entities->AddEntity(Entity_Type::SARU, 24 + (j * 16), 32 - 16 + (i * 16));
			}
			else if (grid[i][j] == BANANACHER)
			{
				App->entities->AddEntity(Entity_Type::BANANACHER, 24 + (j * 16), 32 - 16 + (i * 16));
			}
		}
	}
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			App->levelManager->grid[y][x] = grid[y][x];
		}
	}
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneBossFight::Update()
{
	//if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
	//{
	//	App->player->Disable();
	//	App->entities->Disable();
	//	App->collisions->Disable();
	//	App->UI->Disable();

	//	App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 60);
	//}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneBossFight::PostUpdate()
{
	//Draw background
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneBossFight::CleanUp()
{
	App->player->Disable();
	App->entities->Disable();
	App->collisions->Disable();
	App->UI->Disable();

	return true;
}

SceneBossFight::GridType SceneBossFight::GetGridType(int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration];
}

SceneBossFight::GridType SceneBossFight::SetGridType(GridType type, int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration] = type;
}